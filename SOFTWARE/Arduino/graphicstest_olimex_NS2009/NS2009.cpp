#include <Wire.h>
#include <Arduino.h>
#include "NS2009.h"

int Map_Data (int Data, int InMin, int InMax, int OutMin, int OutMax)
{
  if (Data < InMin)
    Data = InMin;
  if (Data > InMax)
    Data = InMax;
  return ((Data-InMin)*(OutMax-OutMin))/(InMax-InMin)+OutMin;
}

NS2009::NS2009 (void)
{
  Address = DEFAULT_NS2009_ADDR;
  FlipX = false;
  FlipY = false;
}

NS2009::NS2009 (unsigned char _Address)
{
  Address = _Address;
  FlipX = false;
  FlipY = false;
}

NS2009::NS2009 (bool _FlipX, bool _FlipY)
{
  Address = DEFAULT_NS2009_ADDR;
  FlipX = _FlipX;
  FlipY = _FlipY;
}

NS2009::NS2009 (unsigned char _Address, bool _FlipX, bool _FlipY)
{
  Address = _Address;
  FlipX = _FlipX;
  FlipY = _FlipY;
}

unsigned int NS2009::ReadRegister (unsigned char Command)
{
  unsigned char ReadData[2], i=0;
  Wire.beginTransmission(Address);
  Wire.write(&Command, 1);
  Wire.endTransmission();
  Wire.requestFrom(Address, 2);
  while (Wire.available())
    ReadData[i++] = Wire.read();
  return (ReadData[0] << 4) | (ReadData[1] >> 4);
}

void NS2009::Calibrate ()
{
  int P1X, P1Y, P2X, P2Y;
  Serial.println ("Touch corner of the screen\n\r");
  ScanBlocking ();
  P1X = RawX;
  P1Y = RawY;
  Serial.println ("Touch registered! Touch an opposite corner!\n\r");
  while (CheckTouched ());

  // opposite corner
  ScanBlocking ();
  P2X = RawX;
  P2Y = RawY;
  Serial.println ("Second touch registered!\n\r");
  while (CheckTouched ());

  MinX = MIN(P1X, P2X);
  MaxX = MAX(P1X, P2X);
  MinY = MIN(P1Y, P2Y);
  MaxY = MAX(P1Y, P2Y);
}

void NS2009::Calibrate (int _MinX, int _MaxX, int _MinY, int _MaxY)
{
  MinX = _MinX;
  MaxX = _MaxX;
  MinY = _MinY;
  MaxY = _MaxY;
}

bool NS2009::CheckTouched ()
{
  do
  {
    RawZ = ReadRegister(NS2009_READ_Z);
  }
  while (RawZ == 0xFFF);  // sometimes the I2C reading gives a false positive by returning only ones ==> 0xFFF = 4095
  Touched = (RawZ > THRESHOLD_Z);
  return Touched;
}

void NS2009::Scan ()
{
  CheckTouched ();
  RawX = ReadRegister(NS2009_READ_X);
  X = Map_Data (RawX, MinX, MaxX, 0, SCREEN_SIZE_X);
  RawY = ReadRegister(NS2009_READ_Y);
  Y = Map_Data (RawY, MinY, MaxY, 0, SCREEN_SIZE_Y);
  if (FlipX)
    X = SCREEN_SIZE_X - X;
  if (FlipY)
    Y = SCREEN_SIZE_Y - Y;
}

void NS2009::ScanBlocking ()
{
  do
  {
    CheckTouched ();
  }
  while (!Touched);
  RawX = ReadRegister(NS2009_READ_X);
  X = Map_Data (RawX, MinX, MaxX, 0, SCREEN_SIZE_X);
  RawY = ReadRegister(NS2009_READ_Y);
  Y = Map_Data (RawY, MinY, MaxY, 0, SCREEN_SIZE_Y);
  if (FlipX)
    X = SCREEN_SIZE_X - X;
  if (FlipY)
    Y = SCREEN_SIZE_Y - Y;
}
