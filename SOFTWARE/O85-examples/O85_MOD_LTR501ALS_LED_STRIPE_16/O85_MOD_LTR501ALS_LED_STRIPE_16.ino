#include <TinyWireM.h>
#include <Adafruit_NeoPixel.h>
/*

Connection guide:
-----|
 #0  | -----------------  SDA*
 #1  | -----------------  LED-STRIPE
 #2  | -----------------  SCL*
 #3  | - NC
 #4  | - NC
-----|

IMPORTANT NOTE:
Add 4.7kOhms to VCC!
*/

unsigned int PS = 0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, 1, NEO_GRB + NEO_KHZ800);

void setup(void)
{
    strip.begin();
    strip.show();
    TinyWireM.begin();
    Write(0x80, 0x03);  //Active mode, 64k lux range
    Write(0x81, 0x03);  //PS active mode, x1 GAIN
    Write(0x82, 0x6B);  //LED 60Hz, 50% duty, 50mA
    Write(0x83, 0x7F);  //127 pulses
    Write(0x84, 0x02);  //PS 100ms measure rate
    Write(0x85, 0x03);  //ALS Integration 100ms, repeat rate 500ms
}

void loop()
{
    unsigned char stat = Read(0x8C);
    if(stat & 0x01)
    {
        unsigned char data[2];
        for(int i = 0; i < 2; i++)
        {
            data[i] = Read(0x8D + i);
        }
        PS = (data[1] << 8) | data[0];
    }
    unsigned char out = map(PS, 410, 2047, 0, 16);
    for(int i = 0; i < strip.numPixels(); i++)
    {
        if(i < out)
            strip.setPixelColor(i, strip.Color(255, 255, 255));
        else
            strip.setPixelColor(i, 0);
    }
    strip.show();
    delay(10);
}

void Write(unsigned char reg, unsigned char data)
{
    TinyWireM.beginTransmission(0x23);
    TinyWireM.send(reg);
    TinyWireM.send(data);
    TinyWireM.endTransmission();
}

byte Read(unsigned char reg)
{
    unsigned char rdata;
    TinyWireM.beginTransmission(0x23);
    TinyWireM.send(reg);   // MSB
    TinyWireM.endTransmission();
    TinyWireM.requestFrom(0x23,1);
    if (TinyWireM.available()) rdata = TinyWireM.receive();
    return rdata;
}
