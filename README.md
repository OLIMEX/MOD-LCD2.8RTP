# MOD-LCD2.8RTP
TFT COLOR LCD module with [UEXT connector](https://www.olimex.com/Products/Modules/) for
[ESP32-EVB](https://www.olimex.com/Products/IoT/ESP32/ESP32-EVB/open-source-hardware) and
[ESP32-POE](https://www.olimex.com/Products/IoT/ESP32/ESP32-POE/open-source-hardware)

**Using MOD-LCD2.8RTP requires non-standard SPI for the display and I2C for the touch screen** 

The non-standard part of the SPI is the lack of MISO which is Data/Command selection pin (refer to controller's datasheet) which has to be set as output.

UEXT pinout:

|UEXT column 1|UEXT column 2|Function|
|---|---|---|
|1 - 3.3V |2 - GND|Power pins|
|3 - NOT USED|4 - NOT USED|UART pins not used|
|5 - SCL|6 - SDA|I2C pins used for touch component|
|7 - D/C|8 - MOSI|SPI pins sans MISO used for display|
|9 - CLK|10 - CS|SPI CLK/CS for display|

If you are using I2C, then the RX wire can also be used to control the brightness. This requires midfying the SJ2 jumper. Refer to the schematic around FET1.
