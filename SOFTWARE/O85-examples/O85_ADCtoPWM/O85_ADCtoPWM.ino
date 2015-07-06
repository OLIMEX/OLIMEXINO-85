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
  Reads the voltage peresent at Analog 1(digital pin #2) and sets the STAT led's brightness, i.e. pin #1, according to it. 
  The PWM signal is with frequency approximately 250Hz
  This example requires a trimmer with approximately value of 10k that must be connected as shown to the bottom schematic.
  Note:
  You can read an analog voltage from digital #2 (called Analog 1), digital #3 (called Analog 3) and digital #4 (called Analog 2)
  For example, to read an analog voltage on pin #2, you would call analogRead(1) to read an analog voltage on pin #4 call analogRead(2)
  This is a bit confusing because the analog pins are numbered differently than the digital pins!
  
  Simple Schematic:
  =================
  |---------------------------|                    -------------|vcc
  |                    |  #0  |                    |
  |                    |  #1  |              ------o------
  |                    |  #2  |-------------| Trimmer 10k |
  |    OLIMEXINO-85    |  #3  |              ------o------
  |                    |  #4  |                    |
  |                    | #RST |                    |
  |                    | GND  |--------------------o------------|gnd
  |                    | VCC  |---------------------------------|vcc
  |---------------------------|     

  To upload to your Olimexino-85:
  1) Select the proper board from the Tools->Board Menu->Digispark 8mhz - NO USB(Tiny Core)
  2) Select Digispark from the Tools->Programmer
  3) Press the Upload button
  4) When you see the message: "Plug in device now... (will timeout in 60 seconds)", Plug in the Olimexino-85
*/
 
#define  Led              1
#define  Trimmer          1    // Analog pin 1(digital pin #2)
#define  Delay_time_ms    10

int ADC_Value = 0;

// The setup routine is executed once when you power-on the board or press the RST button later
void setup() {
  
  pinMode(Led, OUTPUT);    // initialize the digital pin as an output.
  digitalWrite(Led, LOW);  // Set it in Low state
  
}

// The loop routine runs over and over again until power-off the board or interrupt occure:
void loop() {
  
  ADC_Value = analogRead(Trimmer);    // read the input pin. The value is 0..1023
  analogWrite(Led, (ADC_Value/4));    // PWM the LED from 0 to 255 (max)
  delay(Delay_time_ms);
  
}


