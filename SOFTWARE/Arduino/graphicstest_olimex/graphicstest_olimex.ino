/***************************************************
  This is our GFX example for the Adafruit ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/


#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "Wire.h"
#include <Adafruit_STMPE610.h>

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 290
#define TS_MINY 285
#define TS_MAXX 7520
#define TS_MAXY 7510
#define TS_I2C_ADDRESS 0x4d

/*
// This is pinouts for ESP32-EVB
#define TFT_DC 15
#define TFT_CS 17
#define TFT_MOSI 2
#define TFT_MISO 15
#define TFT_CLK 14
//#define TFT_RST 33 */

// This is pinouts for Olimexino 2560
// Cut jumper SJ3
// If display is connected to UEXT Connect p34 to p50 with a wire !!!

#define TFT_DC 34
#define TFT_CS 53
#define TFT_MOSI 51
#define TFT_MISO 50
#define TFT_CLK 52
#define TFT_BKL 0


Adafruit_STMPE610 ts = Adafruit_STMPE610();



// Size of the color selection boxes and the paintbrush size
#define BOXSIZE 40

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

uint8_t tp[5];

void setup() {
        // Power Up UEXT
//   pinMode(LED_BUILTIN, OUTPUT);
//   digitalWrite(LED_BUILTIN, HIGH);
   delay(1000);
//   digitalWrite(LED_BUILTIN, LOW);
//   delay(500);
  Serial.begin(115200);
  Serial.println("ILI9341 Test!");
  tft.begin();
  pinMode(TFT_DC, OUTPUT);

pinMode(TFT_BKL, OUTPUT);
digitalWrite(TFT_BKL, 0);
  // Wire.begin();
   Wire.begin();

  // read diagnostics (optional but can help debug problems)
  //uint8_t x = tft.readcommand8(ILI9341_RDMODE);
   delay(1000);

  tft.fillScreen(ILI9341_BLACK);
  Serial.println("Touchscreen cleaned");
  // make the color selection boxes

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
tft.println("29-05-18       11:28"); //TODO: Print the real date and time


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

     // tft.fillCircle(p.x, p.y, 5, ILI9341_YELLOW);


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
