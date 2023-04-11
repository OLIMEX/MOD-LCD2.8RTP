/***************************************************
  This is an example made by Adafruit and modifed by Olimex for MOD-LCD2.8RTP
  This demo was tested with Olimex MOD-LCD2.8RTP and ESP32-EVB.
  The boards were connected via UEXT connector and cable.
  
  Make sure to establish proper hardware connections with your board.
  The display requires SPI, the touschreen I2C. Refer to Board_Pinout.h.
  
  The original example is a GFX example for the Adafruit ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the link above for Adafruit's tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing the open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

 // In order to work you have to install Adafruit GFX Library
 // To do so go to:
 // Main menu --> Sketch --> Inlcude Librariy --> Manage Libraries...
 // In the search box filter "Adafruit GFX Library" and install it
 // Tested with version 1.2.3 of the library

#include "Wire.h"
#include "Board_Pinout.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "NS2009.h"


#ifdef  ARDUINO_OLIMEXINO_STM32F3
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
#else
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
#endif

#define MODE_DRAW_PIXELS    0
#define MODE_DRAW_RECTANGLE 1
#define MODE_DRAW_CIRCLE    2

#define TEXT_HEIGHT 8
#define TEXT_WIDTH  6

NS2009  TS(false, true);
int Mode=MODE_DRAW_PIXELS, ActiveColor = ILI9341_WHITE;

void Print_Text (int X, int Y, int TextColor, int TextSize, char Text[])
{
  tft.setCursor(X, Y);
  tft.setTextColor(TextColor);
  tft.setTextSize(TextSize);
  tft.println(Text);
}

void Print_Text_In_Box (int X, int Y, int W, int H, int TextColor, int TextSize, char Text[])
{
  int Len = strlen (Text)*TEXT_WIDTH;
  Print_Text (X+(W-Len)/2, Y+(H-TEXT_HEIGHT)/2, TextColor, TextSize, Text);
}

void Draw_Outlined_Rectangle(int X, int Y, int W, int H, int OutlineColor, int InsideColor)
{
  tft.fillRoundRect (X, Y, W, H, 0, InsideColor);
  tft.drawRoundRect (X, Y, W, H, 0, OutlineColor);
}

void Draw_Palette ()
{
  Draw_Outlined_Rectangle (  0,   0,  30,  30, ILI9341_BLACK, ILI9341_WHITE);
  Draw_Outlined_Rectangle ( 30,   0,  30,  30, ILI9341_BLACK, ILI9341_RED);
  Draw_Outlined_Rectangle ( 60,   0,  30,  30, ILI9341_BLACK, ILI9341_YELLOW);
  Draw_Outlined_Rectangle ( 90,   0,  30,  30, ILI9341_BLACK, ILI9341_GREEN);
  Draw_Outlined_Rectangle (120,   0,  30,  30, ILI9341_BLACK, ILI9341_CYAN);
  Draw_Outlined_Rectangle (150,   0,  30,  30, ILI9341_BLACK, ILI9341_BLUE);
  Draw_Outlined_Rectangle (180,   0,  30,  30, ILI9341_BLACK, ILI9341_MAGENTA);
  Draw_Outlined_Rectangle (210,   0,  30,  30, ILI9341_BLACK, ILI9341_BLACK);
}

void Draw_ActiveColor ()
{
  // active color
  Draw_Outlined_Rectangle (  0,  30, 240,  30, ILI9341_BLACK, ActiveColor);
  Print_Text_In_Box       (  0,  30, 240,  30, ~ActiveColor, 1, "Fill Screen");
}

void Draw_Modes ()
{
  // modes
  Draw_Outlined_Rectangle (  0,  60,  80,  30, ILI9341_BLACK, ILI9341_LIGHTGREY);
  Print_Text_In_Box       (  0,  60,  80,  30, ILI9341_BLACK, 1, "Pixel");
  Draw_Outlined_Rectangle ( 80,  60,  80,  30, ILI9341_BLACK, ILI9341_DARKCYAN);
  Print_Text_In_Box       ( 80,  60,  80,  30, ILI9341_BLACK, 1, "Rectangle");
  Draw_Outlined_Rectangle (160,  60,  80,  30, ILI9341_BLACK, ILI9341_ORANGE);
  Print_Text_In_Box       (160,  60,  80,  30, ILI9341_BLACK, 1, "Circle");

  // outline the active mode
  tft.drawFastHLine       (  0,  90, 240, ILI9341_BLACK);
  switch (Mode)
  {
    case MODE_DRAW_PIXELS:
      tft.drawRoundRect (  0,  60, 80, 30, 0, ILI9341_WHITE);
      Serial.printf ("Drawing pixels option selected!\n\r");
    break;
    case MODE_DRAW_RECTANGLE:
      tft.drawRoundRect ( 80,  60, 80, 30, 0, ILI9341_WHITE);
      Serial.printf ("Drawing a rectangle option selected!\n\r");
    break;
    case MODE_DRAW_CIRCLE:
      tft.drawRoundRect (160,  60, 80, 30, 0, ILI9341_WHITE);
      Serial.printf ("Drawing a circle option selected!\n\r");
    break;
  }
}

void Draw_Frame ()
{
  Draw_Palette ();
  Draw_ActiveColor ();
  Draw_Modes ();
}

void Handle_Touch ()
{
  if (TS.Y<90)  // frame area
  {
    if (TS.Y<30)  // palette area
    {
      if      (TS.X< 30)  // white color area
        ActiveColor = ILI9341_WHITE;
      else if (TS.X< 60)  // red color area
        ActiveColor = ILI9341_RED;
      else if (TS.X< 90)  // yellow color area
        ActiveColor = ILI9341_YELLOW;
      else if (TS.X<120)  // green color area
        ActiveColor = ILI9341_GREEN;
      else if (TS.X<150)  // cyan color area
        ActiveColor = ILI9341_CYAN;
      else if (TS.X<180)  // blue color area
        ActiveColor = ILI9341_BLUE;
      else if (TS.X<210)  // magenta color area
        ActiveColor = ILI9341_MAGENTA;
      else if (TS.X<240)  // black color area
        ActiveColor = ILI9341_BLACK;
      Draw_ActiveColor ();
      Serial.printf ("New color selected!\n\r");
    }
    else if (TS.Y<60) // fill screen area
    {
      tft.fillRoundRect (0, 90, 240, 230, 0, ActiveColor);
      Serial.printf ("Screen area filled with the selected color!\n\r");
    }
    else if (TS.Y<90) // mode area
    {
      if      (TS.X <  80)  // pixel mode area
        Mode = MODE_DRAW_PIXELS;
      else if (TS.X < 160)  // rectangle mode area
        Mode = MODE_DRAW_RECTANGLE;
      else if (TS.X < 240)  // circle mode area
        Mode = MODE_DRAW_CIRCLE;
      Draw_Modes ();
    }
  }
  else  // drawing area
  {
    int PX=TS.X, PY=TS.Y, R;
    switch (Mode)
    {
      case MODE_DRAW_PIXELS:
        while (TS.Touched)
        {
          if (TS.Y>=90)
          {
            tft.drawPixel (TS.X, TS.Y, ActiveColor);
            Serial.printf ("Drawn pixel at %d %d!\n\r", TS.X, TS.Y);
          }
          else
            Serial.printf ("Invalid coordinates!\n\r", TS.X, TS.Y);
          TS.Scan();
        }
      break;
      case MODE_DRAW_RECTANGLE:
        Serial.printf ("First corner of the rectangle is at %d %d. Touch to again to point the opposite corner!\n\r", TS.X, TS.Y);
        while (TS.CheckTouched ());
        TS.ScanBlocking ();
        tft.fillRoundRect (min(PX, TS.X), min(PY, TS.Y), abs(TS.X-PX), abs(TS.Y-PY), 0, ActiveColor);
        Draw_Frame ();
        Serial.printf ("Rectangle drawn!\n\r");
      break;
      case MODE_DRAW_CIRCLE:
        Serial.printf ("Center of the circle is at %d %d. Touch to again to point a point of the circle!\n\r", TS.X, TS.Y);
        while (TS.CheckTouched ());
        TS.ScanBlocking ();
        R = sqrt( (PX-TS.X) * (PX-TS.X) + (PY-TS.Y) * (PY-TS.Y) );
        tft.drawCircle (PX, PY, R, ActiveColor);
        Draw_Frame ();
        Serial.printf ("Circle drawn!\n\r");
      break;
    };
  }
}

void setup()
{
  Serial.begin (115200);
  Wire.begin();
  pinMode(TFT_DC, OUTPUT);
  tft.begin();
  tft.fillScreen(ILI9341_WHITE);
  Draw_Frame ();
}

void loop ()
{
  TS.ScanBlocking ();
  Serial.printf ("Screen touched!\n\r");
  Handle_Touch ();
  while (TS.CheckTouched ());
  Serial.printf ("Screen released!\n\r");
}
