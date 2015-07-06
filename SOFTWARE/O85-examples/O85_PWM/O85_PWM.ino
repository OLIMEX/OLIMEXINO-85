/**********************************************************************************/
/*    Demo Program for:          						  */
/*	  Board: Olimexino-85                 					  */
/*    Manufacture: OLIMEX                                                   	  */
/*	  COPYRIGHT (C) 2013							  */
/*    Designed by: Engineer Penko T. Bozhkov                                      */
/*    Revision       :  1.0.0 (initial)                                           */
/*    Date           :  31.10.2013                                                */
/*   Built with Arduino C/C++ Compiler, version: 1.0.4                            */
/**********************************************************************************/
/*
  Action:
  =======
  Pulses Olimexino-85's STAT led, i.e. pin #1. The PWM signal is with frequency approximately 250Hz
  Note:
  Other optons is only the pin: #0. Pin #2 has no PWM out function, 
  while #3 and #4 are used by the USB and are not recommended to be used for PWM generation when USB is present!
  See: http://learn.adafruit.com/introducing-trinket/programming-with-arduino-ide

  To upload to your Olimexino-85:
  1) Select the proper board from the Tools->Board Menu->Digispark 8mhz - NO USB(Tiny Core)
  2) Select Digispark from the Tools->Programmer
  3) Press the Upload button
  4) When you see the message: "Plug in device now... (will timeout in 60 seconds)", Plug in the Olimexino-85
*/

#define  Delay_time_ms    5
#define  Led              1  // Select the pin where the led is attached. Options: from 0 to 4

// The setup routine is executed once when you power-on the board or press the RST button later
void setup() {
  
  pinMode(Led, OUTPUT);    // initialize the digital pin as an output.
  digitalWrite(Led, LOW);  // Set it in Low state
  
}

// The loop routine runs over and over again until power-off the board or interrupt occure:
void loop() {
  
  for (int i=0; i<256; i++) {
    analogWrite(Led, i);  // PWM the LED from 0 to 255 (max)
    delay(Delay_time_ms);
  }
  for (int i=255; i>=0; i--) {
    analogWrite(Led, i);  // PWM the LED from 255 (max) to 0
    delay(Delay_time_ms);
  }
  delay(500);
  
}


