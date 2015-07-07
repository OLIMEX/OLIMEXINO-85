The firmware binaries are suitable for the following boards that feature ATtiny85: OLIMEXINO-85-KIT, OLIMEXINO-85-ASM, OLIMEXINO-85BC, OLIMEXINO-85S, FOSDEM-85, and FOSDEM-85-KIT

The OLIMEXINO-85 boards come programmed with the "Micronucleus" bootloader version 1.06. The offical "Micronucleus" repository can be found at the following address: https://github.com/micronucleus/micronucleus 

We used the Bluebie fork available here: https://github.com/Bluebie/micronucleus/tree/master/firmware/releases

NOTE: We are not supporting upgrading the firmware - the only suggested firmware is the bootloader version 1.06. It is provided in the respective folder.

1) Use AVR/Atmel Studio or AVRDude to upload respectivley the .elf or the .hex to the target ATtiny85.

The .elf file contains the proper fuses and configuration bits.

2) If you use AVRDude then you need to pass the fuse settings as command line:

lfuse:w:0xE1:m -U hfuse:w:0xDD:m -U efuse:w:0xFE:m

Usually the command to program the board via AVRDude looks like:

avrdude -c stk500v2 -P com26 -p t85 -U flash:w:Olimexino-85_ProductionTest_v_1_0_0.hex -U lfuse:w:0xE1:m -U hfuse:w:0xDD:m -U efuse:w:0xFE:m

,where

stk500v2 is the programmer's interface abriviation as per AVRdude's documentation
com26 is the serial interface in Windows; it would be something like ttyACM0 or similar
t85 is the abriviation of the name of the target microcontroller as per AVRdude's documentation
Olimexino-85_ProductionTest_v_2_0_0.hex is the name of our binary code

3) About the ATTINY85 Fuses
========================
FUSE - HEX value - Value description

Extended fuse - 0xFE – this value enables self programming and keeps the serial programming enabled

High fuse - 0xDD – this values sets PLL Clock; start-up time PWRDWN/RESET: 1K CK/14 CK + 64 ms

Low fuse - 0xE1 – this values sets brown-out detection at VCC=2.7 V

Refer to the user's manual of OLIMEXINO-85 for more information.