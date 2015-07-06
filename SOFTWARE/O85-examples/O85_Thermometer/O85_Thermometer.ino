/**********************************************************************************/
/*    Demo Program for:          						  */
/*	  Board: Olimexino-85                 					  */
/*    Manufacture: OLIMEX                                                   	  */
/*	  COPYRIGHT (C) 2014							  */
/*    Designed by:  Penko T. Bozhkov                                              */
/*    Revision       :  1.0.0 (initial)                                           */
/*    Date           :  31.01.2014                                                */
/*   Built with Arduino C/C++ Compiler, version: 1.0.4                            */
/**********************************************************************************/
// Very important!!!!! Change the I2C buffer size from 16 to 30!!!!!!!!!!!!!!!!!!!!
// Goto Digispark-Arduino-1.0.4\libraries\TinyWireM_Digispark\TinyWire.h and chage:
// #define USI_BUF_SIZE    30              // bytes in message buffer
// In other case, the demo will not work correctly
/*
  Action:
  =======
  Reads the temperature via MOD-TC-MK2-31855 and displays the value to MOD-LCD-1x9.
  https://www.olimex.com/Products/Modules/Sensors/MOD-TC-MK2-31855/open-source-hardware
  https://www.olimex.com/Products/Components/Misc/TC-K-TYPE/
  https://www.olimex.com/Products/Modules/LCD/MOD-LCD-1x9/open-source-hardware
  To connect all boards together we have used one UEXTx5 board as well: 
  https://www.olimex.com/Products/Modules/Interface/UEXTx5/open-source-hardware
  
  Notes: 
    1. Beware VCC not to exceed (3.6~3.8)V!!!!!
    2. Ensure MOD-TC-MK2-31855 I2C pull-ups are not disconnected!
 
  Simple Schematic:
  =================                                                          |----------------------|
  |---------------------------|       |--------------------------|           |   MOD-TC-MK2-31855   |
  |                    |  #0  |-------| UEXT1<6>        UEXT3<6> |-----------| UEXT<6>            T+|------\  +
  |                    |  #1  |       |                 UEXT3<5> |-----------| UEXT<5>              |       o Thermocouple(TC-K-TYPE)
  |                    |  #2  |-------| UEXT1<5>        UEXT3<2> |-----------| UEXT<2>            T-|------/  -
  |    OLIMEXINO-85    |  #3  |       |            U    UEXT3<1> |-----------| UEXT<1>              |
  |                    |  #4  |       |            E             |           |----------------------|
  |                    | #RST |       |            X             |                                
  |                    | GND  |-------| UEXT1<2>   T             |           |------------------| D |
  |                    | VCC  |-------| UEXT1<1>   x    UEXT5<6> |-----------| UEXT<6>          | I |
  |---------------------------|       |            5    UEXT5<5> |-----------| UEXT<5>          | S |
                                      |                 UEXT5<2> |-----------| UEXT<2>          | P |
                                      |                 UEXT5<1> |-----------| UEXT<1>          | L |
                                      |--------------------------|           |    MOD-LCD-1x9   | A |
                                                                             |------------------| Y |

  To upload to your Olimexino-85:
  1) Select the proper board from the Tools->Board Menu->Digispark 8mhz - NO USB(Tiny Core)
  2) Select Digispark from the Tools->Programmer
  3) Press the Upload button
  4) When you see the message: "Plug in device now... (will timeout in 60 seconds)", Plug in the Olimexino-85
*/
#include <USI_TWI_Master.h>
#include <TinyWireM.h>      // By default: SCL -> PB2(#2), SDA -> PB0(#0)
//#include <avr/pgmspace.h>
#include <LCD1x9.h>
#include <inttypes.h>

#define MOD_TC_MK2_ADDR   0x23 
#define GET_TEMP	  0x21

#define LED1_PIN         1              // ATtiny85 Pin 6, PB1(#1)
#define LED2_PIN         4              // ATtiny85 Pin 3, PB4(#4)

char TempValue[9] = {'T','e','m','p',' ',' ',' ','&','C'};
uint16_t count = 1;
uint16_t tempC = 0;                     // holds temp in C
//uint16_t tempF = 0;                     // holds temp in F


/****************************************************/
/*  Function name: TC_MK2_temperatureRead           */
/*  Parameters                                      */
/*    Input   :  No                                 */
/*    Output  :  temp                               */
/*    Action: Returns the MAX31855KASA+'s temp data.*/
/****************************************************/
uint32_t TC_MK2_temperatureRead(){
  uint32_t temp;
  uint8_t data[4];
  uint8_t i = 0;
  
  TinyWireM.beginTransmission(MOD_TC_MK2_ADDR);
  TinyWireM.send(GET_TEMP);
  TinyWireM.endTransmission();
  TinyWireM.requestFrom(MOD_TC_MK2_ADDR,4);
  
  while(TinyWireM.available() > 0)
    data[i++] = TinyWireM.receive();
  
  temp = data[3];
  temp <<= 8;
  temp |= data[2];
  temp <<= 8;
  temp |= data[1];
  temp <<= 8;
  temp |= data[0];
  
  return temp;
}


/****************************************************/
/*  Function name: Blink                            */
/*  Parameters                                      */
/*    Input   :  led, times                         */
/*    Output  :  No                                 */
/*    Action: Blinks the selected led.              */
/****************************************************/
void Blink(byte led, byte times){
  for (byte i=0; i<(times<<2); i++){
    if(digitalRead(led)==LOW){
      digitalWrite(led,HIGH);
      delay (500);
    }
    else{
      digitalWrite(led,LOW);
      delay (100);
    }
  }
}


/****************************************************/
/*  Function name: setup                            */
/*  Parameters                                      */
/*    Input   :  No	                            */
/*    Output  :  No                                 */
/*    Action: Initializes all peripherals           */
/****************************************************/
void setup() {
  
  pinMode(LED1_PIN,OUTPUT);
  pinMode(LED2_PIN,OUTPUT);
  Blink(LED1_PIN,2);         // show it's alive
  
  TinyWireM.begin();         // I2C init
  lcd.init();
  
  digitalWrite(LED1_PIN,HIGH);
  digitalWrite(LED2_PIN,LOW);
  
  delay (100);
  lcd.write("*Welcome*");
  delay (1000);
}


/****************************************************/
/*  Function name: loop                             */
/*  Parameters                                      */
/*    Input   :  No	                            */
/*    Output  :  No                                 */
/*    Action: Reads and displays the temperature.   */
/****************************************************/ 
void loop() {
  float ex_f;
  unsigned char ex_s=0;
  
  uint32_t c = TC_MK2_temperatureRead();
  
  // Check for fault
  if(c & 0x00010000){
    // Fault detected
  }
  else{
    ex_s = !!(c & 0x80000000);  // Take the Sign bit value: 0 positive,  1 negative temperature
    // Convert external temperature
    uint16_t ext = (c >> 16 );                // Get the thermocouple temperature data(external temperature) 
    ext &= (0x7FFF);                          // Mask the Sign bit
    ext >>= 2;                                // Ignore the D17(reserved) and D16(Fault) bits
    ex_f = (ext >> 2) + (ext & 0x03) * 0.25;  // Calculate the temperature when positive
    if(ex_s)
      ex_f = 2048 - ex_f;                     // Calculate the temperature when negative
      
    tempC = (uint16_t)ex_f;                   // get the temperature
    //tempF = tempC * 9 / 5 + 32;             // convert to Fahrenheit
     
  }
  
  //Write LCD String
  if(tempC/100){  
    TempValue[4] = (uint8_t)((tempC/100)+ '0');
    if((tempC%100)<10){
      TempValue[5] = (uint8_t)('0');
      TempValue[6] = (uint8_t)((tempC%100)+ '0');
    }
    else{
      TempValue[5] = (uint8_t)(((tempC%100)/10)+ '0');
      TempValue[6] = (uint8_t)(((tempC%100)%10)+ '0');
    }  
  }
  else{ 
    if(ex_s){
     //The measured temperature is negative
     if(tempC/10){  TempValue[4] = (uint8_t)('-');  }
     else{          TempValue[4] = (uint8_t)(' ');  }
    }
    else{  TempValue[4] = (uint8_t)(' ');  }
    // Check the 10's
    if(tempC/10){
      TempValue[5] = (uint8_t)((tempC/10)+ '0');
      TempValue[6] = (uint8_t)((tempC%10)+ '0');
    }
    else{
      if(ex_s){
        //The measured temperature is negative
        if(tempC){  TempValue[5] = (uint8_t)('-');  }
        else{       TempValue[5] = (uint8_t)(' ');  }
      }
      else{         TempValue[5] = (uint8_t)(' ');  }
      TempValue[6] = (uint8_t)((tempC%10)+ '0');  
    }
  }
  
  // Display the string
  lcd.write(TempValue);
  
 ///* 
  count++;
  if(count==1000){
    count = 0;
    Blink(LED1_PIN,1);
  }
//*/
  
}
 
 
 
