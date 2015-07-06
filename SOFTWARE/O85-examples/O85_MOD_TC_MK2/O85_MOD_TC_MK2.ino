/**********************************************************************************/
/*    Demo Program for:          						  */
/*	  Board: Olimexino-85                 					  */
/*    Manufacture: OLIMEX                                                   	  */
/*	  COPYRIGHT (C) 2014							  */
/*    Designed by:  Penko T. Bozhkov                                              */
/*    Revision       :  1.0.0 (initial)                                           */
/*    Date           :  27.01.2014                                                */
/*   Built with Arduino C/C++ Compiler, version: 1.0.4                            */
/**********************************************************************************/
/*
  Action:
  =======
  Reads the temperature via MOD-TC-MK2-31855 and display the value to the LED1 and LED2.
  https://www.olimex.com/Products/Modules/Sensors/MOD-TC-MK2-31855/open-source-hardware
  https://www.olimex.com/Products/Components/Misc/TC-K-TYPE/
  LED1 refers to Olimexino-85's Stat Led and via number of its blinkings displays the 10's of the temperature [C]
  LED2 should be attached to Olimexino-85 as is shown below and via number of its blinkings displays the 1's of the temperature [C]
  So for instance: 24[C] will be displayed via 2 LED1 blinks and 4 LED2 blinks.
  Note: Beware VCC not to exceed (3.6~3.8)V!!!!!
 
  
  Simple Schematic:
  =================
  |---------------------------|                     |----------------------|
  |                    |  #0  |---------------------| UEXT<6>              |
  |                    |  #1  |                     |                      |
  |                    |  #2  |---------------------| UEXT<5>              |
  |    OLIMEXINO-85    |  #3  |                     |                    T+|------\  +
  |                    |  #4  |-|560R|--|>|--|      |   MOD-TC-MK2-31855   |       o Thermocouple(TC-K-TYPE)
  |                    | #RST |         LED  |      |                    T-|------/  -
  |                    | GND  |--------------o------| UEXT<2>              |
  |                    | VCC  |---------------------| UEXT<1>              |
  |---------------------------|                     |----------------------|

  To upload to your Olimexino-85:
  1) Select the proper board from the Tools->Board Menu->Digispark 8mhz - NO USB(Tiny Core)
  2) Select Digispark from the Tools->Programmer
  3) Press the Upload button
  4) When you see the message: "Plug in device now... (will timeout in 60 seconds)", Plug in the Olimexino-85
*/
#include <TinyWireM.h>      // By default: SCL -> PB2(#2), SDA -> PB0(#0) 
#include <inttypes.h>

#define MOD_TC_MK2_ADDR   0x23 
#define SET_ADDRESS 	  0xF0
#define GET_ID		  0x20
#define GET_TEMP	  0x21

#define LED1_PIN         1              // ATtiny85 Pin 6, PB1(#1)
#define LED2_PIN         4              // ATtiny85 Pin 3, PB4(#4)

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
  for (byte i=0; i< times; i++){
    digitalWrite(led,HIGH);
    delay (400);
    digitalWrite(led,LOW);
    delay (175);
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
  
  digitalWrite(LED1_PIN,LOW);
  digitalWrite(LED2_PIN,LOW);
  
  delay (3000);
}


/****************************************************/
/*  Function name: loop                             */
/*  Parameters                                      */
/*    Input   :  No	                            */
/*    Output  :  No                                 */
/*    Action: Reads and displays the temperature.   */
/****************************************************/ 
void loop() {
 
  uint32_t c = TC_MK2_temperatureRead();
  
  // Check for fault
  if(c & 0x00010000){
    // Fault detected
  }
  else{
    float ex_f;
    unsigned char ex_s = !!(c & 0x80000000);  // Take the Sign bit value: 0 positive,  1 negative temperature
    /* Convert external temperature */
    uint16_t ext = (c >> 16 );                // Get the thermocouple temperature data(external temperature) 
    ext &= (0x7FFF);                          // Mask the Sign bit
    ext >>= 2;                                // Ignore the D17(reserved) and D16(Fault) bits
    ex_f = (ext >> 2) + (ext & 0x03) * 0.25;  // Calculate the temperature
    if(ex_s)
      ex_f = 2048 - ex_f;
      
    tempC = (uint16_t)ex_f;                   // get the temperature
    //tempF = tempC * 9 / 5 + 32;               // convert to Fahrenheit 
  }
  
  Blink(LED1_PIN,tempC/10);             // blink 10's of temperature on LED 1
  delay (1000);
  Blink(LED2_PIN,tempC%10);             // blink 1's of temperature on LED 2
  delay (4000);                         // wait a few sec before next reading
  
}
 
