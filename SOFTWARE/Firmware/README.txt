The firmware binaries are suitable for the following boards that feature ATtiny85: OLIMEXINO-85-KIT, OLIMEXINO-85-ASM, OLIMEXINO-85BC, OLIMEXINO-85S, FOSDEM-85, and FOSDEM-85-KIT

The binary files were built using the sources at the offical Micronucleous repositry, available at the following address: https://github.com/micronucleus/micronucleus

1) Use AVR/Atmel Studio or AVRDude to upload respectivley the .elf or the .hex to the target ATtiny85.

The .elf file contains the proper fuses and configuration bits.

2) If you use AVRDude then you need to pass the fuse settings as command line:

lfuse:w:0xF1:m -U hfuse:w:0xD5:m -U efuse:w:0xFE:m

Usually the command to program the board via AVRDude looks like:

avrdude -c stk500v2 -P com26 -p t85 -U flash:w:Olimexino-85_ProductionTest_v_2_0_0.hex -U lfuse:w:0xF1:m -U hfuse:w:0xD5:m -U efuse:w:0xFE:m

,where

stk500v2 is the programmer's interface abriviation as per AVRdude's documentation
com26 is the serial interface in Windows; it would be something like ttyACM0 or similar
t85 is the abriviation of the name of the target microcontroller as per AVRdude's documentation
Olimexino-85_ProductionTest_v_2_0_0.hex is the name of our binary code

3) About the ATTINY85 Fuses
========================
FUSE - HEX value - Description

EXTENDED - 0xFE - ----

HIGH - 0xDF - RSTDISBL: NO, DWEN: NO, SPIEN: YES, WDTON: NO, EESAVE: Not preserved, BODLEVEL<2..0>: BOD Disabled
								
LOW - 0xE2 - CKDIV8: NO, CKOUT: NO, SUT<1..0>: 6CK/14CK + 64 ms, CKSEL<3..0>: 0010 - 8.0 MHz(Calibrated Internal Oscillator)

Refer to the user's manual of OLIMEXINO-85 for more information.