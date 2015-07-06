OLIMEXINO-85-ASM, OLIMEXINO-85-KIT, OLIMEXINO-85BC, OLIMEXINO-85S and FOSDEM-85 library package

1. Hardware and software prerequisites:

1x OLIMEXINO-85-ASM or OLIMEXINO-85-KIT or OLIMEXINO-85BC or OLIMEXINO-85S or FOSDEM-85 board
1x cable to connect the board and your PC
1x properly installed Arduino IDE configured for DIGISPARK(please note that the examples won't work with stock Arduino IDE!)

Each library is archived as zip. Please extract it to the libraries folder in the Digispark's Arduino IDE. Inside each library there is also an example!

The libraries require additional hardware! Each library has explanation in the code comments!

2. The library list is:

Adafruit_NeoPixel_master - contains two examples for controlling RGB LED strip with 1 data line

LCD1x9 - library for LC1x9 and contains an example for using LCD1x9, this library requires TinyWireM also

MOD_IO2_Library - contains example for MOD-IO2 (with firmware 3) board relay switch

TinyWireM - I2C library used for LCD1x9 control

3. Remember:

- you need an Arduino IDE configured for DIGISPARK
- you need to click "Upload" button first, wait for the program to compile and THEN plug the board (this is because the bootloader implementation runs for the first few seconds after power up and then the user program is executed. If you plug the board before programming the bootloader won't be available and uploading will fail. Disconnect the board, click "Upload" again and then connect the board). 

There are detailed instructions in the manual and the digispark's wiki pages.