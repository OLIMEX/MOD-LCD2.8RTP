/***************************************************
  This is an example made by Adafruit and modifed by Olimex for MOD-LCD2.8RTP
  This demo was tested with Olimex MOD-LCD2.8RTP and ESP32-EVB and OLIMEXINO-2560.
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


#include "Board_Pinout.h"
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "Wire.h"
#include "Adafruit_STMPE610.h"

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 290
#define TS_MINY 285
#define TS_MAXX 7520
#define TS_MAXY 7510
#define TS_I2C_ADDRESS 0x4d


Adafruit_STMPE610 ts = Adafruit_STMPE610();

// Size of the color selection boxes and the paintbrush size
#define BOXSIZE 40

#ifdef  ARDUINO_OLIMEXINO_STM32F3
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
#else
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
#endif

uint8_t tp[5];

void setup() {
        // TODO: Power Up UEXT if 32U4

   delay(1000);
   Serial.begin (115200);
   //while (!Serial);
   Serial.print ("Demo started");

  tft.begin();

   Wire.begin();
   pinMode(TFT_DC, OUTPUT);
  // read diagnostics (optional but can help debug problems)
  //uint8_t x = tft.readcommand8(ILI9341_RDMODE);
   delay(1000);

   ts.begin(TS_I2C_ADDRESS);


}


void loop(void) {

// This is just a draw some data Demo

// Clear Screen
tft.fillScreen(ILI9341_BLACK);
// Set some fancy background
testFastLines(ILI9341_DARKGREY,ILI9341_DARKCYAN);

// Print "current date and time"
tft.setCursor(5,5);
tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(2);
tft.println("29-05-18      11:28"); //TODO: Print the real date and time


// Print "room temperature"
tft.setCursor(85,50);
tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(4);
tft.println("22");//TODO: Print the real room temperature
tft.setCursor(148,50);
tft.println("C");
tft.drawCircle(138, 54, 4, ILI9341_GREEN);
tft.drawCircle(138, 54, 5, ILI9341_GREEN);
tft.setCursor(78,85);
tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(1);
tft.println("ROOM TEMPERATURE");


// Now print Message box wit two yes/no buttons
tft.fillRoundRect(10,120, 220, 190, 8, ILI9341_OLIVE);
tft.drawRoundRect(10,120, 220, 190, 8, ILI9341_WHITE);

tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(2);
tft.fillRoundRect(20,150, 200, 80,8, ILI9341_BLUE);
tft.setCursor(90, 165);
tft.println("Save");
tft.setCursor(40, 190);
tft.println("new settings?");
tft.drawRoundRect(20,150, 200, 80, 8, ILI9341_WHITE);
// Get the choise
bool answer = Get_yes_no();

if (answer == true)
{
  // Some animation while "write to eeprom"
testFilledRects(ILI9341_DARKGREEN,ILI9341_DARKCYAN);
tft.setCursor(80, 150);
tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(3);
tft.println("Done!");
} else   tft.fillScreen(ILI9341_RED);
// fill screen red to show negative choise
delay(1000);
}


unsigned long testFastLines(uint16_t color1, uint16_t color2) {
  unsigned long start;
  int           x, y, w = tft.width(), h = tft.height();

  tft.fillScreen(ILI9341_BLACK);
  start = micros();
  for(y=0; y<h; y+=5) tft.drawFastHLine(0, y, w, color1);
  for(x=0; x<w; x+=5) tft.drawFastVLine(x, 0, h, color2);

  return micros() - start;
}

unsigned long testFilledRects(uint16_t color1, uint16_t color2) {
  unsigned long start, t = 0;
  int           n, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  n = min(tft.width(), tft.height());
  for(i=n; i>0; i-=6) {
    i2    = i / 2;
    start = micros();
    tft.fillRect(cx-i2, cy-i2, i, i, color1);
    t    += micros() - start;
    // Outlines are not included in timing results
    tft.drawRect(cx-i2, cy-i2, i, i, color2);
    yield();
  }

  return t;
}

bool Get_yes_no(void){
TS_Point p;
    tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(3);

    tft.fillRoundRect(20,250, 100, 50,8, ILI9341_RED);
    tft.setCursor(56, 265);
    tft.println("NO");
    tft.drawRoundRect(20,250, 100, 50, 8, ILI9341_WHITE);

    tft.fillRoundRect(120,250, 100, 50,8, ILI9341_GREEN);
    tft.setCursor(144, 265);
    tft.println("YES");
    tft.drawRoundRect(120,250, 100, 50, 8, ILI9341_WHITE);


while (1){
      delay(50);
    p = ts.getPoint();

    if (p.z != 129){


      p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
      p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
      p.y = 320 - p.y;

      //  tft.fillCircle(p.x, p.y, 5, ILI9341_YELLOW);


    if ((p.y > 250) && (p.y<300)){

      if ((p.x> 20) && (p.x < 220))
            if (p.x>120)
            {
              tft.fillRoundRect(120,250, 100, 50,8, ILI9341_OLIVE);
              tft.setCursor(144, 265);
              tft.println("YES");
              tft.drawRoundRect(120,250, 100, 50, 8, ILI9341_WHITE);

              delay(500);
              return true;
            }
                   else{

                     tft.fillRoundRect(20,250, 100, 50,8, ILI9341_OLIVE);
                     tft.setCursor(56, 265);
                     tft.println("NO");
                     tft.drawRoundRect(20,250, 100, 50, 8, ILI9341_WHITE);

                        delay(500);
                     return false;
                   }

    }

  }
}
}
