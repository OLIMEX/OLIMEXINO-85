#include <Wire.h>
#include <IRDA.h>

const int buttonPin = 2;
IRDA irda(0x24);
void setup(){
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
}
void loop(){
  if(digitalRead(buttonPin) == LOW){
     Serial.print("Reading ID: ");
     unsigned char id = irda.getID();
     Serial.println(id, HEX);
     // Check if the ID match
     Serial.print("Checking ID: ");
     if(id == irda.ID)
       Serial.println("OK");
     else
       Serial.println("FAIL");
       
     Serial.println("---------------");
     while(digitalRead(buttonPin) == LOW);
     delay(1000);       
  }
}

