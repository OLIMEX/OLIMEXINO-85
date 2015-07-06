/*
 * IRDA.cpp
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
 

#include "IRDA.h"
#include <TinyWireM.h>



/*
 * Class variables
 */
 uint8_t IRDA::address = 0x24;

 
 uint8_t IRDA::SIRC = 0x01;
 uint8_t IRDA::RC5 = 0x00;
 uint8_t IRDA::ID = 0x54;


/*
 * Constructors
 */
IRDA::IRDA(){
}

IRDA::IRDA(uint8_t addr){
    address = addr;
}

void IRDA::setAddress(uint8_t newAddress){
    TinyWireM.begin();
    TinyWireM.beginTransmission(address);
    TinyWireM.send(SET_ADDRESS);
    TinyWireM.send(newAddress);
    TinyWireM.endTransmission();
}
uint8_t IRDA::getID(void){
    unsigned char data;  
    TinyWireM.begin();
    TinyWireM.beginTransmission(address);
    TinyWireM.send(GET_ID);
    TinyWireM.endTransmission();
    TinyWireM.requestFrom((int)address, 1);
    data = TinyWireM.receive();
    
    return data;    
}
void IRDA::setMode(uint8_t mode){
  TinyWireM.begin();
  TinyWireM.beginTransmission(address);
  TinyWireM.send(SET_MODE);
  TinyWireM.send(mode);
  TinyWireM.endTransmission();
}
void IRDA::sendData(uint8_t device, uint8_t command){
  TinyWireM.begin();
  TinyWireM.beginTransmission(address);
  TinyWireM.send(WRITE);
  TinyWireM.send(device);
  TinyWireM.send(command);
  TinyWireM.endTransmission();
}
uint16_t IRDA::readData(){
  uint8_t data[2];
  TinyWireM.begin();
  TinyWireM.beginTransmission(address);
  TinyWireM.send(READ);
  TinyWireM.endTransmission();
  TinyWireM.requestFrom((int)address, 2);
  data[0] = TinyWireM.receive();
  data[1] = TinyWireM.receive();
  
  return (data[0] << 8) | data[1];
}
