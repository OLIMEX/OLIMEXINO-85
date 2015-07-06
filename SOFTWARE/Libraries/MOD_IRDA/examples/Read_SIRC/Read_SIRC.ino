#include <Wire.h>
#include <IRDA.h>

IRDA irda(0x24);

unsigned char Reverse(unsigned char data, unsigned char len){
  unsigned char reverse = 0;
  for(int i = 0; i < len; i++){
    reverse <<= 1;
    reverse |= !!(data & (1 << i));
  }
  return reverse;
}
void setup(){
  Serial.begin(9600);
  irda.setMode(irda.SIRC);
}
void loop()
{
  unsigned int data = irda.readData();
  if(data != 0xFFFF){
    unsigned char device = 0;
    unsigned char command = 0;
    device = Reverse(data & 0x1F, 5);
    command = Reverse((data >> 5) & 0x7F, 7);
    
    Serial.print("COMMAND: ");
    Serial.println(command, DEC);
    Serial.print("DEVICE: ");
    Serial.println(device, DEC);
    Serial.println("--------------");
  }
  delay(500);  
}

