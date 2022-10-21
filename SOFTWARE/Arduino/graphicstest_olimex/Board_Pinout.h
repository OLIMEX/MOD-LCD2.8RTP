#ifndef	_BOARD_PINOUT_H
#define	_BOARD_PINOUT_H

#if (defined ARDUINO_ESP32_POE) || (defined ARDUINO_ESP32_POE_ISO)
	// This is pinouts for ESP32-PoE(-ISO)
	#define TFT_DC 15
	#define TFT_CS 5
	#define TFT_MOSI 2
	#define TFT_CLK 14
  #define TFT_MISO -1
  #define TFT_RST -1
#elif defined ARDUINO_ESP32_EVB
	// This is pinouts for ESP32-EVB
	#define TFT_DC 15
	#define TFT_CS 17
	#define TFT_MOSI 2
	#define TFT_CLK 14
  #define TFT_MISO -1
  #define TFT_RST -1
#elif defined ARDUINO_ESP32_DEV
//This is if you select ESP32 Wrover Module
	#define TFT_DC 12
	#define TFT_CS 15
	#define TFT_MOSI 13
	#define TFT_CLK 14
	#define TFT_MISO -1
	#define TFT_RST -1

#elif defined ARDUINO_ESP32_WROVER_KIT
//This is if you select ESP32 Wrover Kit (All versions)
	#define TFT_DC 12
	#define TFT_CS 15
	#define TFT_MOSI 13
	#define TFT_CLK 14
	#define TFT_MISO -1
	#define TFT_RST -1
#elif defined ARDUINO_AVR_OLIMEXINO_2560
	// This is pinouts for Olimexino 2560
	// Important!!! If using UEXT connector you need
	// to UEXT Connect p34 to p50 with a wire !!!
	#warning If display is connected to UEXT Connect p34 to p50 with a wire !!!

	#define TFT_DC 34
	#define TFT_CS 53
	#define TFT_MOSI 51
	#define TFT_CLK 52
  #define TFT_MISO -1
  #define TFT_RST -1
#elif defined ARDUINO_AVR_MEGA2560
	#warning You need to connect the respective SPI and I2C pins to the AVR_MEGA256

	#define TFT_DC 34
	#define TFT_CS 53
	#define TFT_MOSI 51
	#define TFT_CLK 52
  #define TFT_MISO -1
  #define TFT_RST -1
#elif defined ARDUINO_OLIMEXINO_STM32F3
  #define TFT_DC 12
  #define TFT_CS 4
  #define TFT_MOSI 11
  #define TFT_CLK 13
  #define TFT_MISO -1
  #define TFT_RST -1

#else
	#error This demo does not support selected board.

	#define TFT_DC 0
	#define TFT_CS 0
	#define TFT_MOSI 0
	#define TFT_CLK 0
  #define TFT_MISO 0
  #define TFT_RST 0
#endif

#endif	// #ifndef	_BOARD_PINOUT_H
