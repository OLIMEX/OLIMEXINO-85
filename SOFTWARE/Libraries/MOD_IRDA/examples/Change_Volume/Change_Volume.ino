#include <Wire.h>
#include <IRDA.h>

IRDA irda(0x24);
void setup(){
  irda.setMode(irda.RC5);  
}
void loop(){
  //VOLUME+
  irda.sendData(0x01, 16);
  delay(100);
  //VOLUE+
  irda.sendData(0x01, 17);
  delay(100);
}



