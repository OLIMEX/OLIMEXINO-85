/**********************************************************************************/
/*    Demo Program for:          						  */
/*	  Board: Olimexino-85                 					  */
/*    Manufacture: OLIMEX                                                   	  */
/*	  COPYRIGHT (C) 2014							  */
/*    Designed by:  Penko T. Bozhkov                                              */
/*    Revision       :  1.0.0 (initial)                                           */
/*    Date           :  03.02.2014                                                */
/*   Built with Arduino C/C++ Compiler, version: 1.0.4                            */
/**********************************************************************************/
// Very important!!!!! Change the I2C buffer size from 16 to 30!!!!!!!!!!!!!!!!!!!!
// Goto Digispark-Arduino-1.0.4\libraries\TinyWireM_Digispark\TinyWire.h and chage:
// #define USI_BUF_SIZE    30              // bytes in message buffer
// In other case, the demo will not work correctly
/*
  Action:
  =======
  Writes long string to the MOD-LCD-1x9 display.
  https://www.olimex.com/Products/Modules/LCD/MOD-LCD-1x9/open-source-hardware
  
  Notes: 
    1. Beware VCC not to exceed (3.6~3.8)V!!!!!
    2. Don't forget to connect external 2.2k Ohm pull-ups to the I2C line as shown below!
       This is vital as well!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 
  Simple Schematic:                    ------|2k2|----->VCC
  =================                   |    --|2k2|----->VCC
                                      |   |
  |---------------------------|       |   |       |----------------------|
  |                    |  #0  |-------|---o-------| UEXT<6>          | D |
  |                    |  #1  |       |           |                  | I |
  |                    |  #2  |-------o-----------| UEXT<5>          | S |
  |    OLIMEXINO-85    |  #3  |                   |                  | P |
  |                    |  #4  |                   |   MOD-LCD-1x9    | L |
  |                    | #RST |                   |                  | A |
  |                    | GND  |-------------------| UEXT<2>          | Y |
  |                    | VCC  |-------o-----------| UEXT<1>          |---|
  |---------------------------|       |           |----------------------|
                                      ----------------->VCC

  To upload to your Olimexino-85:
  1) Select the proper board from the Tools->Board Menu->Digispark 8mhz - NO USB(Tiny Core)
  2) Select Digispark from the Tools->Programmer
  3) Press the Upload button
  4) When you see the message: "Plug in device now... (will timeout in 60 seconds)", Plug in the Olimexino-85
*/
#include <USI_TWI_Master.h>
#include <TinyWireM.h>      // By default: SCL -> PB2(#2), SDA -> PB0(#0)
#include <avr/pgmspace.h>
#include <LCD1x9.h>
#include <inttypes.h>

#define LED1_PIN         1              // ATtiny85 Pin 6, PB1(#1)
#define LED2_PIN         4              // ATtiny85 Pin 3, PB4(#4)

char LongString[] PROGMEM = ("This is MOD-LCD-1x9 demo program. Hope you will enjoy this simple demo software! :-> ");
char TempValue[9] = {'#','I','N','I','T','I','A','L','#'};


/****************************************************/
/*  Function name: LCD_Write_LongString             */
/*  Parameters                                      */
/*    Input   :  *strp                              */
/*    Output  :  No                                 */
/*    Action: Writes the string to the LCD.         */
/****************************************************/
void LCD_Write_LongString(PGM_P strp){
  PGM_P tempp;
  
  tempp = strp;
  
  while(pgm_read_byte(strp)){
    for(unsigned char p=0; p<9; p++){
      TempValue[p] = pgm_read_byte(tempp);
      tempp++;
    }
    strp++;
    tempp = strp;
    lcd.write(TempValue);
    //delay(1000);
    Blink(LED1_PIN,2);
  }
  
  //Clear display
  lcd.write("         ");
  //delay(1000);
  Blink(LED1_PIN,2);
}


/****************************************************/
/*  Function name: Blink                            */
/*  Parameters                                      */
/*    Input   :  led, times                         */
/*    Output  :  No                                 */
/*    Action: Blinks the selected led.              */
/****************************************************/
void Blink(byte led, byte times){
  for (byte i=0; i<(times); i++){
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
  
  // Display the string
  LCD_Write_LongString(LongString);
  
}
 
 
 
