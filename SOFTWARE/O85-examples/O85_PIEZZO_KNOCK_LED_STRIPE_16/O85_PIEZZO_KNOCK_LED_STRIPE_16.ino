/**
Connection:

-------|
  #0  | - NC
  #1  | - LED-STRIPE
  #2  | - PIEZZO-KNOCK
  #3  | - NC
  #4  | - NC
 ------|

Just punch the piezzo sensor and see what is going to happen.
 */

#include <Adafruit_NeoPixel.h>


int sensorValue = 0;
int outputValue = 0;


Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, 1, NEO_GRB + NEO_KHZ800);

void setup()
{
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
}

void loop()
{
    sensorValue = analogRead(1);
    outputValue = map(sensorValue, 0, 1023, 0, 15);
    if(outputValue > 0)
    {
        for(int i =0; i < strip.numPixels(); i++)
        {
            if(i <= outputValue)
                strip.setPixelColor(i, strip.Color(255, 255, 255));
            else
                strip.setPixelColor(i, 0);
            strip.show();
            delay(10);
        }
        delay(200);
        for(int i = outputValue; i >= 0; i--)
        {
            strip.setPixelColor(i, 0);
            strip.show();
            delay(20);
        }
    }
    delay(1);
}


