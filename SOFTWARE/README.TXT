##Arduino IDE example:

Tested with Olimex boards - OLIMEXINO-2560, OLIMEXINO-STM32F3, and Olimex ESP32 boards (Olimex ESP32-EVB, ESP32-POE, ESP32-POE-ISO). Refer to the comments in the .ino sketch - make sure to download all the files (library and header files; and not just the .ino).

Folder "graphicstest_olimex_NS2009" contains demo for NS2009 touchscreen.

Folder "graphicstest_olimex" contains demo for STMPE610 touchscreen component.

Basically if touch is not working try the demo in the other folder.

If you use the demo with an ESP32 boards remember to prepare your Arduino IDE environment according to the arduino for ESP32 repository here: https://github.com/espressif/arduino-esp32#installation-instructions

NOTE: You might need to edit the pins in board_pinout.h - for example, if you use ESP32-POE instead of ESP32-EVB, you need to change TFT_CS from 17 to 5 (since ESP32-POE uses pin #5 for chip select).

##PlatformIO example:

Made and tested with Olimex ESP32-EVB using PlatformIO 3.6.0a3
