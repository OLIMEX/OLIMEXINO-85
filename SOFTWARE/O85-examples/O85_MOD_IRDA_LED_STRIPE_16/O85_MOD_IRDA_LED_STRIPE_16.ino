/**
Connection:

-------
    #0|  -----> SDA*
    #1|  -----> LED-STRIPE
    #2|  -----> SCL*
    #3|  NC
    #4|  NC
------

Important note:
  Use external Pullups to VCC.
  
 Use RIGHT and LEFT on the remote to change color.
 UP and DOWN change brightness.
 1, 2, 3, 4, 5, 6, 7, 8 and 9 to start builtin shows.
 */
#include <USI_TWI_Master.h>
#include <TinyWireM.h>
#include <IRDA.h>
#include <Adafruit_NeoPixel.h>

IRDA irda(0x24);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, 1, NEO_GRB + NEO_KHZ800);

unsigned char R = 255;
unsigned char G = 0;
unsigned char B = 0;
float brightness = 1.0;

void setup()
{
    strip.begin();
    strip.show();
    irda.setMode(irda.RC5);
}
void loop()
{
    uint32_t color = strip.Color((int)(G * brightness), (int)(R * brightness), (int)(B * brightness));
    for(int i = 0; i < strip.numPixels(); i++)
        strip.setPixelColor(i, color);
    strip.show();
    unsigned int data = irda.readData();
    if(data != 0xFFFF)
    {
        unsigned char command = data & 0x3F;
        switch(command)
        {
        case 20:
            brightness += 0.05;
            if(brightness > 1)
                brightness = 1.0;
            break;
        case 19:
            brightness -= 0.05;
            if(brightness < 0)
                brightness = 0.0;
            break;
        case 22:
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
            break;
        case 21:
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
            break;
        case 1:
            colorWipe(strip.Color(255, 0, 0), 50); // Red
            break;
        case 2:
            colorWipe(strip.Color(0, 255, 0), 50); // Green
            break;
        case 3:
            colorWipe(strip.Color(0, 0, 255), 50); // Blue
            break;
        case 4:
            theaterChase(color, 50); // White
            break;
        case 5:
            theaterChase(color, 150); // Red
            break;
        case 6:
            theaterChase(color, 250); // Red
            break;
        case 7:
            rainbow(20);
            break;
        case 8:
            rainbowCycle(20);
            break;
        case 9:
            theaterChaseRainbow(50);
            break;
        default:
            break;
        }
        while(irda.readData() != 0xFFFF);
    }
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

