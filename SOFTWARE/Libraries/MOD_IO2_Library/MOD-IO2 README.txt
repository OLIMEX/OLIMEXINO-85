	MOD-IO2
	----------
	
1. Description
 MOD-IO2 is stackable development board which adds RELAYs and GPIOs to 
any of our development boards with UEXT. If you work with any of our 
development boards with UEXT connector and you need more GPIOs and/or 
RELAY outputs you can add these by connecting MOD-IO2 to your 
development board. This board allows easy way to interface up to 2 
relays and 7 GPIOs. MOD-IO2 is stackable and addressable, what does this 
means? These boards can stack together so you can add as many input and 
outputs as you want! E.g. 2-4-6-8 etc.! MOD-IO2 has PIC16F1503 
microcontroller and the firmware is available for modification. 

Before continue reading:
	* This file describe operation with the version3 of the firmware.
	* MOD-IO2 works only at 100kHz (or lower) I2C speed.
	* Host must support clock stretching for proper work.
	* When reading, after sending command, STOP-START condition must be
	send, not RESTART.
	
2. I2C Commands:		
		
	* SET_TRIS(0x01):
		Define port direction of the GPIO pins. Can be INPUT or OUTPUT. 
		Note that GPIO3  can be only input with Pull-Up always turned on. 
		This is because the alternative function is #MCLR. To set GPIO
		as INPUT write 1 to the corresponding bitmask, or 0 for output.
	Example:
	--------
		START | ADDRESS | W | ACK | SET_TRIS | ACK | VALUE | ACK | STOP
				
		where:
			ADDRESS = 0x23 (this is the default address)
			SET_TRIS = 0x01
			VALUE = 0b0ddddddd - the bitmask with the corresponding 
			directions. GPIO0 - bit0, GPIO1 - bit1, etc ... 
			0x7F - all input, 0x00 - all outputs)
					
	* SET_LAT(0x02):
		Set the output level of GPIO. In the bitmask 1 correspond to logical
		"1", and 0 - logical "0". Again, GPIO3 can be only input, so the 
		corresponding bit in the mask will be ignored.
	Example:
	--------
		START | ADDRESS | W | ACK | SET_LAT | ACK | VALUE | ACK | STOP
		
		where:
			ADDRESS = 0x23
			SET_LAT = 0x02
			VALUE = 0b0dddxddd	the bitmask, where bit0 is the value for 
								GPIO0, bit1 - GPIO1, etc. bit3 is 
								x - doesn't care.

	
	* GET_PORT(0x03):
		Read current level of the GPIOs. The data will be valid if the 
		GPIO is configured as INPUT. 
	Example:
	--------
		START | ADDRESS | W | ACK | GET_PORT | ACK | STOP | START | ADDRESS | R | DATA | NACK | STOP
		
		where:
			ADDRESS = 0x23 (the default address)
			GET_PORT = 0x03
			DATA = 0x0ddddddd  - the bitmask containing the GPIOs status. bit0 - GPIO0, bit1 - GPIO1, etc.
			
			
	* SET_PU(0x04):
		Turn on or off weak Pull-Up. GPIOs must be configured as INPUTS. Note that only GPIO0 to GPIO4 have Pull-Ups, and GPIO3 is with Pull-Up always enabled.
	Example:
	--------
		START | ADDRESS | W | ACK | SET_PU | ACK | VALUE | ACK | STOP
		
		where:
			ADDRESS = 0x21  (the default address)
			SET_PU = 0x04
			VALUE = 0b000dxddd - bit0 corresponding to GPIO0, as "1" enables the Pull-Up and "0" - disables it.
			
		
	* GET_AN0(0x10) on GPIO0:
	  GET_AN1(0x11) on GPIO1:
	  GET_AN2(0x12) on GPIO2:
	  GET_AN6(0x13) on GPIO3:
	  GET_AN7(0x15) on GPIO5:
		Read the voltage applied on any of the GPIOs mentioned above. If GPIO is configured as output, the execution the the command will set the GPIO as input. After the applied voltage is measured, the GPIO configuration will be as INPUT. After READ the master should read 2 bytes of data: HIGH and LOW byte.
	Example:
	--------
		START | ADDRESS | W | ACK | GET_ANx | ACK | STOP | START | ADDRESS | R | DATA_L | ACK | DATA_H | NACK | STOP
		
		where:
			ADDRESS = 0x23 (the default address)
			GET_ANx = 0x10, 0x11, 0x12, 0x13 or 0x15
			DATA_L = the byte that contains the low 8 bits of the ADC value
			DATA_H = the byte that contains the high bits of the ADC value
			
			
	* GET_ID(0x20):
		Read the ID of the MOD-IO2. By default it must be 0x23.
	Example:
	--------
	
		START | ADDRESS | W | ACK | GET_ID | ACK | STOP | START | ADDRESS | R | ACK | DATA | NACK | STOP
		
		where:
			ADDRESS = 0x21 (the default address)
			GET_ID = 0x20
			DATA = should be 0x23
			
	* SET_REL(0x40):
		Turn on or off the two relays. The data is the state of the relays. Bit0 is the state of RELAY1, and 
		bit1 - RELAY2. If 1 is written the relays is turned on, 0 is off. For example to turn on both relays
		you must write 0x03.
		
		Example:
	--------
	
		START | ADDRESS | W | ACK | SET_REL | ACK | DATA | ACK | STOP
			
			
3.	Release history:
	24 JUL 2013	-	Released version3 firmware
	
4. Support:
	https://www.olimex.com/
	support@olimex.com