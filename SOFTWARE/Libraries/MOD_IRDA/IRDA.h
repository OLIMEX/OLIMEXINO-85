/*
 * IRDA.h
 * 
 * Copyright 2013 OLIMEX LTD/Stefan Mavrodiev <support@olimex.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#ifndef IRDA_H
#define IRDA_H

#include <inttypes.h>

#define SET_ADDRESS 	0xF0
#define GET_ID		0x20
#define SET_MODE	0x01
#define WRITE		0x02
#define READ		0x03

class IRDA
{
    private:
        static uint8_t address;	

    public:
        IRDA();
        IRDA(uint8_t addr);
	void setAddress(uint8_t newAddress);
	uint8_t getID(void);	
	void setMode(uint8_t mode);
	void sendData(uint8_t device, uint8_t command);
	uint16_t readData();
	
	static uint8_t SIRC;
	static uint8_t RC5;
	static uint8_t ID;

	
};
#endif
