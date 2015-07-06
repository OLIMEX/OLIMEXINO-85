#include <Wire.h>
#include <IRDA.h>

IRDA irda(0x24);
void setup(){
  Serial.begin(9600);
  irda.setMode(irda.RC5);
}
void loop()
{
  unsigned int data = irda.readData();
  if(data != 0xFFFF){
    unsigned char device = 0;
    unsigned char command = 0;
    unsigned char toggle = 0;
    
    command = data & 0x3F;
    device = (data >> 6) & 0x1F;
    toggle = (data >> 11) & 0x01;
    
    Serial.print("TOGGLE: ");
    Serial.println(toggle, DEC);
    Serial.print("COMMAND: ");
    Serial.println(command, DEC);
    Serial.print("DEVICE: ");
    Serial.println(device, DEC);
    Serial.println("--------------");
  }
  delay(10);  
}

