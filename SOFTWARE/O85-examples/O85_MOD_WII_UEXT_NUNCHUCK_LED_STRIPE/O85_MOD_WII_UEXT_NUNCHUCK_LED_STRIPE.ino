/**
Connection:

------|
  #0  | - SDA
  #1  | - LED-STRIPE
  #2  | - SCL
  #3  | - NC
  #4  | - NC
------|

 */

#include <USI_TWI_Master.h>
#include <TinyWireM.h>
#include <ArduinoNunchuk.h>
#include <Adafruit_NeoPixel.h>

int R = 255;
int G = 0;
int B = 0;
float bright = 1.0;
uint32_t color;

ArduinoNunchuk nunchuk = ArduinoNunchuk();
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, 1, NEO_GRB + NEO_KHZ800);

void setup()
{
    pinMode(1, OUTPUT);
    nunchuk.init();
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
}

void loop()
{
    nunchuk.update();
    color = strip.Color((int)(G * bright), (int)(R * bright), (int)(B * bright));
    for(int i = 0; i < strip.numPixels(); i++)
        strip.setPixelColor(i, color);
    strip.show();
    // Shot
    if(nunchuk.zButton)
    {
        for(int j = 0; j < strip.numPixels(); j++)
        {
            for (int i = 0; i < strip.numPixels(); i++)
            {
                if(i == j)
                    strip.setPixelColor(i, strip.Color(255, 255, 255));
                else
                    strip.setPixelColor(i, color);
            }
            strip.show();
            delay(40);
        }
        while(nunchuk.zButton)
        {
            nunchuk.update();
        }
    }
    else if(nunchuk.cButton)
    {
        colorWipe(strip.Color(255, 0, 0), 50); // Red
        colorWipe(strip.Color(0, 255, 0), 50);
        colorWipe(strip.Color(0, 0, 255), 50);
        theaterChase(strip.Color(127, 127, 127), 50); // White
        theaterChase(strip.Color(127,   0,   0), 50); // Red
        theaterChase(strip.Color(  0,   0, 127), 50); // Blue
        while(nunchuk.cButton)
        {
            nunchuk.update();
        }
    }
    // Increase bright
    else if(nunchuk.analogY > 200)
    {
        if(bright < 1.0)
            bright += 0.01;
        if(bright > 1)
            bright = 1;
    }
    // Decrease bright
    else if(nunchuk.analogY < 50)
    {
        if(bright > 0)
            bright -= 0.01;
        if(bright < 0)
            bright = 0;
    }
    else if(nunchuk.analogX > 200)
    {
        if(R == 255 && G == 0 && B == 0)
            G += 15;
        else if(R == 255 && G > 0 && G < 255 && B == 0)
            G += 15;
        else if(R == 255 && G == 255 && B == 0)
            R -= 15;
        else if(R > 0 && G == 255 && B == 0)
            R -= 15;
        else if(R == 0 && G == 255 && B == 0)
            B += 15;
        else if(R == 0 && G == 255 && B > 0 && B < 255)
            B += 15;
        else if(R == 0 && G == 255 && B == 255)
            G -= 15;
        else if(R == 0 && G > 0 && B == 255)
            G -= 15;
        else if(R == 0 && G == 0 && B == 255)
            R += 15;
        else if(R > 0 && R < 255 && G == 0 && B == 255)
            R += 15;
        else if(R == 255 && G == 0 && B == 255)
            B -= 15;
        else if(R == 255 && G == 0 && B > 0)
            B -= 15;
    }
    else if(nunchuk.analogX < 50)
    {
        if(R == 255 && G == 0 && B == 0)
            B += 15;
        else if(R == 255 && B > 0 && B < 255 && G == 0)
            B += 15;
        else if(R == 255 && B == 255 && G == 0)
            R -= 15;
        else if(R > 0 && B == 255 && G == 0)
            R -= 15;
        else if(R == 0 && B == 255 && G == 0)
            G += 15;
        else if(R == 0 && B == 255 && G > 0 && G < 255)
            G += 15;
        else if(R == 0 && B == 255 && G == 255)
            B -= 15;
        else if(R == 0 && B > 0 && G == 255)
            B -= 15;
        else if(R == 0 && B == 0 && G == 255)
            R += 15;
        else if(R > 0 && R < 255 && B == 0 && G == 255)
            R += 15;
        else if(R == 255 && B == 0 && G == 255)
            G -= 15;
        else if(R == 255 && B == 0 && G > 0)
            G -= 15;
    }
    delay(5);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait)
{
    for(uint16_t i=0; i<strip.numPixels(); i++)
    {
        strip.setPixelColor(i, c);
        strip.show();
        delay(wait);
    }
}

void rainbow(uint8_t wait)
{
    uint16_t i, j;
    for(j=0; j<256; j++)
    {
        for(i=0; i<strip.numPixels(); i++)
        {
            strip.setPixelColor(i, Wheel((i+j) & 255));
        }
        strip.show();
        delay(wait);
    }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait)
{
    uint16_t i, j;
    for(j=0; j<256*5; j++)   // 5 cycles of all colors on wheel
    {
        for(i=0; i< strip.numPixels(); i++)
        {
            strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
        }
        strip.show();
        delay(wait);
    }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait)
{
    for (int j=0; j<10; j++)    //do 10 cycles of chasing
    {
        for (int q=0; q < 3; q++)
        {
            for (int i=0; i < strip.numPixels(); i=i+3)
            {
                strip.setPixelColor(i+q, c);    //turn every third pixel on
            }
            strip.show();
            delay(wait);
            for (int i=0; i < strip.numPixels(); i=i+3)
            {
                strip.setPixelColor(i+q, 0);        //turn every third pixel off
            }
        }
    }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait)
{
    for (int j=0; j < 256; j++)       // cycle all 256 colors in the wheel
    {
        for (int q=0; q < 3; q++)
        {
            for (int i=0; i < strip.numPixels(); i=i+3)
            {
                strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
            }
            strip.show();
            delay(wait);
            for (int i=0; i < strip.numPixels(); i=i+3)
            {
                strip.setPixelColor(i+q, 0);        //turn every third pixel off
            }
        }
    }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos)
{
    if(WheelPos < 85)
    {
        return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
    else if(WheelPos < 170)
    {
        WheelPos -= 85;
        return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    else
    {
        WheelPos -= 170;
        return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
}

