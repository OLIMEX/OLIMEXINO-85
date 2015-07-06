/*
	MOD-IO2 Library for the MAPLE IDE
	
	If you have any questions, email
	support@olimex.com
	
	https://www.olimex.com
	OLIMEX 2013

 */	

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif
#include "MOD-IO2.h"

MOD_IO2::MOD_IO2 (unsigned char Address, unsigned char nSDA, unsigned char nSCL)
{
	SL_READ  = (Address<<1) | 1;
	SL_WRITE = (Address<<1) | 0;
	pinSDA = nSDA;
	pinSCL = nSCL;
	SCL_OUT();
	SDA_OUT();
}

MOD_IO2::~MOD_IO2 ()
{
}
	
void MOD_IO2::SDA_OUT()
{
	pinMode(pinSDA, OUTPUT);
}

void MOD_IO2::SDA_IN()
{
	pinMode(pinSDA,  INPUT);
}

void MOD_IO2::SCL_OUT()
{
	pinMode(pinSCL, OUTPUT);
}

void MOD_IO2::SCL_IN()
{
	pinMode(pinSCL, INPUT);
} 

void MOD_IO2::Start()
{
	SDA_OUT();
	WaitMicrosecond(1000);
	SCL_OUT();
	WaitMicrosecond(1000);		
}

void MOD_IO2::Stop()
{
	SDA_OUT();
	WaitMicrosecond(1000);
	SCL_IN();
	WaitMicrosecond(1000);
	SDA_IN();
	WaitMicrosecond(1000);
}

char MOD_IO2::WriteSingle( char data )
{
	char i;

	// Send the 8 bits
	for(i = 0; i<8; i++)
	{
		WaitMicrosecond(1000);
		if(data&RW_MASK)
			SDA_IN();
		else
			SDA_OUT();
		data <<= 1;
		WaitMicrosecond(1000);
		SCL_IN();
		WaitMicrosecond(1000);
		SCL_OUT();
	}

	// Read the ACK
	WaitMicrosecond(1000);
	SDA_IN();
	WaitMicrosecond(1000);
	SCL_IN();
	WaitMicrosecond(1000);
	i = digitalRead(pinSDA);
	SCL_OUT();
	WaitMicrosecond(1000);

	return i;		
}
		
char MOD_IO2::WriteSingleIadr(unsigned char W_ADDR, char data)
{
	char aflag=0;
	Start();
	aflag = WriteSingle(SL_WRITE);
	aflag|= WriteSingle (W_ADDR);
	aflag|= WriteSingle (data);
	Stop();
	delay(500);

	return !aflag;
}
	
char MOD_IO2::WriteMultipleIadr(unsigned char W_ADDR, char * data, unsigned char NumOfBytes)
{
	char aflag=0;
	Start();
	for(int i = 0; i<NumOfBytes; i++)
	{
		aflag = WriteSingle (W_ADDR);
		aflag |= WriteSingle (data[i]);
		W_ADDR++;
	}
	Stop();
	delay(500);

	return !aflag;
}
	
char MOD_IO2::ReadSingle( char ack )
{
	char data = 0, i;

	SDA_IN();		
	for(i = 0; i < 8; i++)
	{
		WaitMicrosecond(1000);
		SCL_IN();
		while(digitalRead(pinSCL)==0);
		WaitMicrosecond(1000);
		data |= digitalRead(pinSDA);
		if( i!=7 )
			data<<=1;
		WaitMicrosecond(1000);
		SCL_OUT();
		WaitMicrosecond(1000);
	}

	// send the ACK/NACK
	WaitMicrosecond(1000);
	if(ack)
		SDA_IN();
	else
		SDA_OUT();
	WaitMicrosecond(1000);
	SCL_IN();
	WaitMicrosecond(1000);
	SCL_OUT();
	WaitMicrosecond(1000);

	return data;		
}
	
char MOD_IO2::ReadSingleIadr(unsigned char R_ADDR, unsigned char &aPtr)
{
	unsigned char aflag;
	char data;

	Start();
	aflag = WriteSingle(SL_WRITE);
	aflag|= WriteSingle(R_ADDR);
	Stop();
	Start();
	aflag|= WriteSingle(SL_READ);
	data = ReadSingle(NACK);
	Stop();

	aPtr = aflag;

	return data;
}
	
char MOD_IO2::ReadMultipleIadr(unsigned char R_ADDR, char * buffer, unsigned char NumOfBytes)
{
	unsigned char aflag;
	if(NumOfBytes==1)
	{
		buffer[0] = ReadSingleIadr(R_ADDR, aflag);
		return (!aflag);
	}
	else
	{
		Start();
		aflag = WriteSingle(SL_WRITE);
		aflag|= WriteSingle(R_ADDR);
		Stop();
		Start();
		aflag|= WriteSingle(SL_READ);
		for(int i=0; i<NumOfBytes-1; i++)
			buffer[i] = ReadSingle(ACK);

		buffer[NumOfBytes-1] = ReadSingle(NACK);				
		Stop();

		return (!aflag);
	}
}
		
void MOD_IO2::WaitMicrosecond(int x)
{
	delayMicroseconds(x);
}

unsigned char MOD_IO2::getSDAnum()
{
	return pinSDA;
}

unsigned char MOD_IO2::getSCLnum()
{
	return pinSCL;
}
