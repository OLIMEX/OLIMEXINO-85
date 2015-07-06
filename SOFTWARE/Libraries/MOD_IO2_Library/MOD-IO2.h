/*
	MOD-IO2 Library for the MAPLE IDE
	
	If you have any questions, email
	support@olimex.com
	
	https://www.olimex.com
	OLIMEX 2013

 */	



#ifndef MOD_IO2_H
#define MOD_IO2_H

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

#define	SET_TRIS	0x01
#define	SET_LAT		0x02
#define	GET_PORT	0x03
#define	SET_PU		0x04
#define	GET_AN0		0x10
#define	GET_AN1		0x11
#define	GET_AN2		0x12
#define	GET_AN6		0x13
#define	GET_AN7		0x15
#define	GET_ID		0x20
#define	SET_REL		0x40

	
class MOD_IO2
{
private:
	unsigned char pinSDA, pinSCL, SL_READ, SL_WRITE;
	const static char  ACK = 0;
	const static char NACK = 1;
	const static unsigned char RW_MASK  = 0x80;

public:
	MOD_IO2(unsigned char Address, unsigned char nSDA, unsigned char nSCL);
	~MOD_IO2();
	
	void SDA_OUT();
	void SDA_IN();
	void SCL_OUT();
	void SCL_IN();
	
	void Start();
	void Stop();
	char WriteSingle( char data );
	char WriteSingleIadr(unsigned char W_ADDR, char data);
	char WriteMultipleIadr(unsigned char W_ADDR, char * data, unsigned char NumOfBytes);
	char ReadSingle( char ack );
	char ReadSingleIadr(unsigned char R_ADDR, unsigned char &aPtr);
	char ReadMultipleIadr(unsigned char R_ADDR, char * buffer, unsigned char NumOfBytes);
	void WaitMicrosecond(int x);
	unsigned char getSDAnum();
	unsigned char getSCLnum();
};

#endif