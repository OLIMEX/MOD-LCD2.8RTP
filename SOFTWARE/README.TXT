##Arduino example:

Tested with Arduino boards with ATmega2560 and ESP32 boards (Olimex ESP32-EVB). Refer to the comments in the .ino sketch - make sure to download all the files (library and header files; and not just the .ino).

If you use the demo with an ESP32 boards remember to prepare your Arduino IDE environment according to the arduino for ESP32 repository here: https://github.com/espressif/arduino-esp32#installation-instructions

NOTE OTHER BOARDS: You might need to edit the pins in board_pinout.h - for example, if you use ESP32-POE instead of ESP32-EVB, you need to change TFT_CS from 17 to 5 (since ESP32-POE uses pin #5 for chip select).

##PlatformIO example:

Made and tested with Olimex ESP32-EVB using PlatformIO 3.6.0a3