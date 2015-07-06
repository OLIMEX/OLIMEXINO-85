/*
  Olimexino-85 and MOD-IO2 example.

  Using the library files you can read data from and write data to the MOD-IO2.
  In this demo you can toggle MOD-IO2's relays when you press the button.

  If you have any questions, email support@olimex.com
  
  https://www.olimex.com
  OLIMEX, 2013
*/

//Definitions for the OLIMEXINO-85
//For detailed information on this product,
//visit https://www.olimex.com
#include "MOD-IO2.h"

#define  MOD_IO2_ADDRESS  0x21
#define  SCL 2
#define  SDA 0

int data = 1;

// Define and initialize (Address value, SCL and SDA pins)
// the MOD-IO2 device. The board connects to the MOD via I2C
// Refer to "MOD-IO2.h" or "MOD-IO README.txt"
// for detailed information on the protocol used.
MOD_IO2 mod_io2(MOD_IO2_ADDRESS, SDA, SCL);

void setup()
{
}

void loop()
{
    data = data ^ 0x03;
    mod_io2.WriteSingleIadr (SET_REL, data);
    delay (2000);
}

