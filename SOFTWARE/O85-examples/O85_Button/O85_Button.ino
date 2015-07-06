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
  Switches over Olimexino-85's STAT led, i.e. pin #1 when the Button is pressed
  The Button must be connected to Olimexino-85's pin #2
  
  Simple Schematic:
  =================
  |---------------------------|        --------| R=10k |--------|vcc
  |                    |  #0  |        |       
  |                    |  #1  |        |       --------
  |                    |  #2  |--------o------| Button |--------|gnd
  |    OLIMEXINO-85    |  #3  |                --------
  |                    |  #4  |            
  |                    | #RST |
  |                    | GND  |---------------------------------|gnd
  |                    | VCC  |---------------------------------|vcc
  |---------------------------|     

  To upload to your Olimexino-85:
  1) Select the proper board from the Tools->Board Menu->Digispark 8mhz - NO USB(Tiny Core)
  2) Select Digispark from the Tools->Programmer
  3) Press the Upload button
  4) When you see the message: "Plug in device now... (will timeout in 60 seconds)", Plug in the Olimexino-85
*/
 
#define  Led  1
#define  But  2

int Counter = 0;

// This function switches over the Led when is called
void Toggle_Led(void){
  if(digitalRead(Led)==HIGH){ digitalWrite(Led, LOW);   }
  else{                       digitalWrite(Led, HIGH);  }
}

// The setup routine is executed once when you power-on the board or press the RST button later
void setup() {
  
  pinMode(Led, OUTPUT);    // initialize the digital pin as an output.
  digitalWrite(Led, LOW);  // Set it in Low state
  pinMode(But, INPUT); 
  
}

// The loop routine runs over and over again until power-off the board or interrupt occure:
void loop() {
  
  //Scan the button
  if(digitalRead(But)==LOW){
    Counter++;
    if(Counter == 100){
      // When surely recognized as pressed switch over the led
      Toggle_Led();
      Counter = 0;
      // Wait until the Button is not released
      while(digitalRead(But)==LOW){  asm("NOP");  }
    }
  }
  else{
   Counter = 0;
  }
  
}


