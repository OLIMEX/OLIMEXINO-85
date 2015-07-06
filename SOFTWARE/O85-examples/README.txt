OLIMEXINO-85-ASM, OLIMEXINO-85-KIT, OLIMEXINO-85BC, OLIMEXINO-85S and FOSDEM-85 example package

1. Hardware and software prerequisites:

1x OLIMEXINO-85 board
1x cable to connect the board and your PC
1x properly installed Digispark Arduino IDE (please note that the examples won't work with stock Arduino IDE!)

Each example is archived as zip. Please extract it to a suitable folder to be able to load it in Arduino IDE. To prepare the Arduino IDE follow the guide available here:

http://digistump.com/wiki/digispark/tutorials/connecting

Some examples require additional hardware! Each example has explanation in the code comments!

2. The example list consists of:

85_ADCtoPWM.zip
85_BB_A4983.zip
85_BB_VNH3SP30.zip
85_BlinkingLed.zip
85_Button.zip
85_MOD_TC_MK2.zip
85_PWM.zip
85_Thermometer.zip

3. Remember:

- you need an Arduino IDE configured for DIGISPARK

- you need to click "Upload" button first, wait for the program to compile and THEN plug the board (this is because the bootloader implementation runs for the first few seconds after power up and then the user program is executed. If you plug the board before programming the bootloader won't be available and uploading will fail. Disconnect the board, click "Upload" again and then connect the board).

There are detailed instructions in the manual and the digispark's wiki pages.