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
  Switches over Olimexino-85's STAT led, i.e. pin #1

  To upload to your Olimexino-85:
  1) Select the proper board from the Tools->Board Menu->Digispark 8mhz - NO USB(Tiny Core)
  2) Select Digispark from the Tools->Programmer
  3) Press the Upload button
  4) When you see the message: "Plug in device now... (will timeout in 60 seconds)", Plug in the Olimexino-85
*/

#define  Delay_time_ms    250
#define  Led              1  // Select the pin where the led is attached. Options: from 0 to 4

// This function switches over the Led when is called
void Toggle_Led(void){
  if(digitalRead(Led)==HIGH){ digitalWrite(Led, LOW);   }
  else{                       digitalWrite(Led, HIGH);  }
}

// The setup routine is executed once when you power-on the board or press the RST button later
void setup() {
  
  pinMode(Led, OUTPUT);    // initialize the digital pin as an output.
  digitalWrite(Led, LOW);  // Set it in Low state
  
}

// The loop routine runs over and over again until power-off the board or interrupt occure:
void loop() {
  
  Toggle_Led();
  delay(Delay_time_ms);
  
}


