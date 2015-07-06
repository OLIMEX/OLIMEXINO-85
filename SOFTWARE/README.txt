There are three sub-folders:

1. O85-examples
2. Libraries
3. Firmware

To be able to use the demos:

0. You need an Arduino IDE configured for DIGISPARK. You can configure Arduino IDE for ATtiny85 (OLIMEXINO-85-ASM, OLIMEXINO-85-KIT, FOSDEM-85, SIMON-85, SIMON-85-KIT, OLIMEXINO-85BC, OLIMEXINO-85S) following the advice here:

http://digistump.com/wiki/digispark/tutorials/connecting

1. Copy the contents of the first folder of this archive "O85_examples" to xxx\arduino-x.x.x\examples\ folder.

2. Copy the contents of folder "libaries" to xxx\arduino-x.x.x\libraries. It is extremely important to paste only the contents there (do not create new folders in it else libraries would not be found).

3. You can now load the examples via Open->Examples or Open -> File in the Arduino IDE

Note that each example has a readme file in its folder detailing furhter how to use it and how it works.

Folder "Firmware" contains the bootloaders that can be used to flash the board via any compatible AVR programmer in case of electrical failure or bootloader override.
 
