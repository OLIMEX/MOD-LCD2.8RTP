# MOD-LCD2.8RTP
TFT COLOR LCD module with UEXT connector for ESP32-EVB

Using MOD-LCD2.8RTP requires non-standard SPI for the display and I2C for the touch screen. The non-standrd part of the SPI is the lack of MISO which is D/C (refer to controller's datasheet) which has to be set as output.

UEXT pinout:

|UEXT column 1|UEXT column 2|Function|
|---|---|---|
|1 - 3.3V |2 - GND|Power pins|
|3 - NOT USED|4 - NOT USED|UART pins not used|
|5 - SCL|6 - SDA|I2C pins used for touch component|
|7 - D/C|8 - MOSI|SPI pins sans MISO used for display|
|9 - CLK|10 - CS|SPI CLK/CS for display|
