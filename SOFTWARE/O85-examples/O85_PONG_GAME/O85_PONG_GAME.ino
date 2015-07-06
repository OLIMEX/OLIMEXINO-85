#include <Adafruit_NeoPixel.h>

#define Player1 2
#define Player2 0
#define BUZZ 4

#define progression 2

Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, 1, NEO_GRB + NEO_KHZ800);

char cheat = 'N';
char flag = 'N';
char turn = 'A';
char start = 'A';
unsigned char speed = 100;
unsigned char score1 = 0;
unsigned char score2 = 0;

void setup()
{
    strip.begin();
    strip.show();
    pinMode(Player1, INPUT);
    pinMode(Player2, INPUT);
    pinMode(BUZZ, OUTPUT);
}

void loop()
{
    if(flag == 'F')
    {
        chaseForward(strip.Color(0, 127, 0), speed);
        speed -= progression;
    }
    if(flag == 'R')
    {
        chaseReverse(strip.Color(127, 0, 0), speed);
        speed -= progression;
    }
    int AbuttonState = digitalRead(Player1);
    int BbuttonState = digitalRead(Player2);
    //Hold both buttons for reset
    if(AbuttonState == LOW && BbuttonState == LOW)
    {
        delay(2000);
        if(digitalRead(Player1) == LOW && digitalRead(Player2) == LOW)
        {
            score1 = 0;
            score2 = 0;
            clear();
        }
    }
    else
    {
        if(AbuttonState == LOW && turn == 'A' && flag != 'F' && flag != 'R')
        {
            clear();
            chaseForward(strip.Color(0, 127, 0), speed);
            speed -= progression;
        }
        if(BbuttonState == LOW && turn == 'B' && flag != 'F' && flag != 'R')
        {
            clear();
            chaseReverse(strip.Color(127, 0, 0), speed);
            speed -= progression;
        }
    }
    if(flag == 'S')
    {
        for(int i = 0; i < 100; i++)
        {
            digitalWrite(BUZZ, HIGH);
            delay(1);
            digitalWrite(BUZZ, LOW);
            delay(1);
        }
        for(int j = 0; j < 5; j++)
        {
            for(int i = 0; i < strip.numPixels(); i++)
            {
                if(turn == 'A')
                    strip.setPixelColor(i, strip.Color(0, 255, 0));
                else
                    strip.setPixelColor(i, strip.Color(255, 0, 0));
            }
            strip.show();
            delay(20);
            for(int i = 0; i < strip.numPixels(); i++)
            {
                strip.setPixelColor(i, 0);
            }
            strip.show();
            delay(50);
        }
        flag = 'N';
        cheat = 'N';
        speed = 100;
        if(start == 'A')
        {
            start = 'B';
            turn = 'B';
        }
        else
        {
            start = 'A';
            turn = 'A';
        }
        for(int i = 0; i < strip.numPixels(); i++)
        {
            if(i < score1)
                strip.setPixelColor(i, strip.Color(0, 127, 0));
            else if(9-score2 < i)
                strip.setPixelColor(i, strip.Color(127, 0, 0));
            else
                strip.setPixelColor(i, 0);
        }
        strip.show();
        while(digitalRead(Player1) == LOW || digitalRead(Player2) == LOW);
        if(score1 > 5)
        {
            score1 = 0;
            score2 = 0;
            selebrateA();
            clear();
        }
        if(score2 > 5)
        {
            score1 = 0;
            score2 = 0;
            selebrateB();
            clear();
        }
    }
}
void selebrateA()
{
    for(int i = 0; i < strip.numPixels(); i++)
    {
        strip.setPixelColor(i, strip.Color(0, 100, 0));
        strip.show();
        delay(50);
    }
    for(int i = 10; i >= 0; i--)
    {
        strip.setPixelColor(i, strip.Color(50, 0, 0));
        strip.show();
        delay(50);
    }
    for(int i = 0; i < strip.numPixels(); i++)
    {
        strip.setPixelColor(i, strip.Color(0, 100, 0));
        strip.show();
        delay(50);
    }
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            strip.setPixelColor(j, strip.Color(0, 25 * i, 0));
        }
        strip.show();
        delay(100);
    }
    delay(1000);
}
void selebrateB()
{
    for(int i = 0; i < strip.numPixels(); i++)
    {
        strip.setPixelColor(i, strip.Color(100, 0, 0));
        strip.show();
        delay(50);
    }
    for(int i = 10; i >= 0; i--)
    {
        strip.setPixelColor(i, strip.Color(0, 50, 0));
        strip.show();
        delay(50);
    }
    for(int i = 0; i < strip.numPixels(); i++)
    {
        strip.setPixelColor(i, strip.Color(100, 0, 0));
        strip.show();
        delay(50);
    }
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            strip.setPixelColor(j, strip.Color(25 * i,0, 0));
        }
        strip.show();
        delay(100);
    }
    delay(1000);
}
void clear()
{
    for(int i = 0; i < strip.numPixels(); i++)
        strip.setPixelColor(i, 0);
    strip.show();
}

void chaseReverse(uint32_t c, uint8_t wait)
{
    for(int i = 10; i >= 0; i--)
    {
        strip.setPixelColor(i, c);
        strip.show();
        strip.setPixelColor(i, 0);
        delay(wait);
        int BbuttonState = digitalRead(Player1);
        if( BbuttonState == LOW )
        {
            if( i < 2 )
            {
                if(cheat != 'Y')
                {
                    turn = 'A';
                    flag = 'F';
                    return;
                }
            }
            else
            {
                cheat = 'Y';
            }
        }
    }
    flag = 'S';
    cheat = 'N';
    score2++;
}

void chaseForward(uint32_t c, uint8_t wait)
{
    for(int i = 0; i < 10; i++)
    {
        strip.setPixelColor(i, c);
        strip.show();
        strip.setPixelColor(i, 0);
        delay(wait);
        int AbuttonState = digitalRead(Player2);
        if( AbuttonState == LOW )
        {
            if( i > 7 )
            {
                if(cheat != 'Y')
                {
                    turn = 'B';
                    flag = 'R';
                    return;
                }
            }
            else
            {
                cheat = 'Y';
            }
        }
    }
    flag = 'S';
    cheat = 'N';
    score1++;
}

