#include <Wire.h>
#include <IRDA.h>

const unsigned char defaultAddress = 0x24;
const unsigned char newAddress = 0x30;
const int buttonPin = 2;

IRDA irda(defaultAddress);
void setup(){
}
void loop()
{
  if(digitalRead(buttonPin) == LOW)
    irda.setAddress(newAddress);
    while(digitalRead(buttonPin) == LOW);
}

