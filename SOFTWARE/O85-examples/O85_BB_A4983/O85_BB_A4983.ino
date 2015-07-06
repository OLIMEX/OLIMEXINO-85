/**********************************************************************************/
/*    Demo Program for:          						  */
/*	  Board: Olimexino-85                    				  */
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
  This simple program is designed by using Olimexino-85 board and BB-A4983 connected to it.
  A4983 is a complete microstepping motor driver with built-in translator for easy operation. 
  A 12VDC 2-phase step engine was connected to the BB-A4983 board's connectors OUT1 ans OUT2.
  When the program is running, the motor makes one 360 degree clockwise rotation(if connected correctly) and stops.
  Then one 360 degree counterclockwise rotation and stops. Afterwards the described cycle is constantly repeated.
  The step engine must be connected as follows: Coil<1>*(Begin) to OUT1A;  Coil<1>(End) to OUT1B
                                                Coil<2>*(Begin) to OUT2A;  Coil<2>(End) to OUT2B

  Simple Schematic:
  =================
  |---------------------------|              |----------------------------------------|
  |                    |  #0  |------------->| CTRL<5>,  SLEEP     B         OUT2<B>  |---------> Step engine Coil<2>(End)
  |                    |  #1  |------------->| CTRL<6>,  STEP      B         OUT2<A>  |---------> Step engine Coil<2>*(Begin)
  |                    |  #2  |------------->| CTRL<7>,  DIR       |                  |
  |    OLIMEXINO-85    |  #3  |      |------>| CTRL<2>,  MS1       A         OUT1<A>  |---------> Step engine Coil<1>*(Begin)
  |                    |  #4  |------o------>| CTRL<3>,  MS2   BB-A4983      OUT1<B>  |---------> Step engine Coil<1>(End)
  |                    | #RST |      |------>| CTRL<4>,  MS3       9                  |
  |                    | GND  |------------->| CTRL<10>, GND       8     PWR<2>, GND  |<--------- GND   from External power supply
  |                    | VCC  |------------->| CTRL<1>,  VDD       3     PWR<1>, VIN  |<--------- 12VDC from External power supply
  |---------------------------|              |----------------------------------------|

  To upload to your Olimexino-85:
  1) Select the proper board from the Tools->Board Menu->Digispark 8mhz - NO USB(Tiny Core)
  2) Select Digispark from the Tools->Programmer
  3) Press the Upload button
  4) When you see the message: "Plug in device now... (will timeout in 60 seconds)", Plug in the Olimexino-85

*/


// Select pin numbers:
#define    Sleep       0        // Mode of operation: Active/Sleep
#define    STEP        1        // A low-to-high transition on the STEP input sequences the translator and advances the motor one increment.
#define    DIR         2        // Direction of rotation
#define    MSx         4        // Microstep Select

#define    Threshold   640


// Variables will change:
int StepState = LOW;            // StepState used to set the STEP
long previousMillis = 0;        // will store last time STEP was updated
int counter = 0;
volatile int index = 0;
long interval = 0.1;            // interval at which to make a STEP

void setup() {
  // set the digital pin as output:
  pinMode(STEP, OUTPUT); 
  pinMode(DIR, OUTPUT);
  pinMode(Sleep, OUTPUT);
  pinMode(MSx, OUTPUT);       // MS1..3 Inputs Step control
  
  //Set the state
  digitalWrite(STEP, LOW);      
  digitalWrite(DIR, LOW);     // direction will be clockwise
  //digitalWrite(DIR, HIGH);    // direction will be counterclockwise
  //digitalWrite(Sleep, LOW);     // A4983 into Sleep mode.
  digitalWrite(Sleep, HIGH);    // A4983 into normal operation
  digitalWrite(MSx, HIGH);  // Sixteenth Step  
  //digitalWrite(MSx, LOW);     // Full Step 
}

void loop()
{
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;   

    // if the STEP is off turn it on and vice-versa:
    if (StepState == LOW)
      StepState = HIGH;
    else
      StepState = LOW;

    // set the STEP with the StepState of the variable:
    digitalWrite(STEP, StepState);
    
    counter++;
    
    if(counter >= Threshold){
      counter = 0;
      index++;   
      if(index == 1){
        digitalWrite(Sleep, LOW);     // A4983 into Sleep mode.
      } 
      else if(index == 2){
        digitalWrite(DIR, HIGH);      // direction will be counterclockwise
        digitalWrite(Sleep, HIGH);    // A4983 into normal operation
        digitalWrite(STEP, LOW);
      }
      else if(index == 3){
        digitalWrite(Sleep, LOW);     // A4983 into Sleep mode.
      }
      else{
        index = 0;
        digitalWrite(STEP, LOW);
        digitalWrite(DIR, LOW);       // direction will be clockwise
        digitalWrite(Sleep, HIGH);    // A4983 into normal operation
      }
    }
    
  }
}

