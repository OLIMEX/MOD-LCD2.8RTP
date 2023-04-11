#ifndef _NS2009_H_
#define _NS2009_H_

#define DEFAULT_NS2009_ADDR 0x48 //10010000

#define THRESHOLD_Z 150  // this is a sensitivity threshold value on how hard the touch screen must be touched to react

#define NS2009_READ_X 0xC0
#define NS2009_READ_Y 0xD0
#define NS2009_READ_Z 0xE0

#define CALIBRATE_MIN_X  200
#define CALIBRATE_MIN_Y  400
#define CALIBRATE_MAX_X  3850
#define CALIBRATE_MAX_Y  3920

#define SCREEN_SIZE_X 240
#define SCREEN_SIZE_Y 320

#define MIN(A,B)  (A<B?A:B)
#define MAX(A,B)  (A>B?A:B)

class NS2009
{
  int Address, MinX=CALIBRATE_MIN_X, MinY=CALIBRATE_MIN_Y, MaxX=CALIBRATE_MAX_X, MaxY=CALIBRATE_MAX_Y;
  bool FlipX, FlipY;
  unsigned int ReadRegister (unsigned char Command);
public:
  int RawX, X, RawY, Y, RawZ;
  bool Touched;
  NS2009 (void);
  NS2009 (unsigned char _Address);
  NS2009 (bool _FlipX, bool _FlipY);
  NS2009 (unsigned char _Address, bool _FlipX, bool _FlipY);
  void Calibrate ();
  void Calibrate (int _MinX, int _MaxX, int _MinY, int _MaxY);
  bool CheckTouched ();
  void Scan ();
  void ScanBlocking ();
};
#endif
