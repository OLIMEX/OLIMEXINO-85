//==================
//LCD1x9 Source File
//==================
#include <TinyWireM.h>
#include "LCD1x9.h"


/****************************************************/
/*  Function name: LCD1x9_init                      */
/*  Parameters                                      */
/*    Input   :  No                                 */
/*    Output  :  No                                 */
/*    Action: Initialize the LCD.                   */
/****************************************************/
void LCD1x9::init(void){
    
    TinyWireM.begin();
    
    TinyWireM.beginTransmission(address);
    TinyWireM.send(0xC8);
    TinyWireM.send(0xF0);
    TinyWireM.send(0xE0);
    TinyWireM.send(0x00);
    for(int i = 0; i < 20; i++){
        TinyWireM.send(0xFF);
        lcdBitmap[i] = 0xFF;
    }
    TinyWireM.endTransmission();
}


/****************************************************/
/*  Function name: LCD1x9_enableSegment             */
/*  Parameters                                      */
/*    Input   :  comIndex, bitIndex                 */
/*    Output  :  No                                 */
/*    Action: Enables the pointed LCD segment.      */
/****************************************************/
void LCD1x9::enableSegment(char comIndex, char bitIndex){
    if(bitIndex >= 40)
        return;
        
    comIndex &= 0x3;
    
    if(bitIndex & 0x1)
        comIndex |= 0x4;
        
    bitIndex >>= 1;
    
    lcdBitmap[bitIndex] |= 0x80 >> comIndex;
}


/****************************************************/
/*  Function name: LCD1x9_disableSegment            */
/*  Parameters                                      */
/*    Input   :  comIndex, bitIndex                 */
/*    Output  :  No                                 */
/*    Action: Disables the pointed LCD segment.     */
/****************************************************/
void LCD1x9::disableSegment(char comIndex, char bitIndex){
    if(bitIndex >= 40)
        return;
        
    comIndex &= 0x3;
    
    if(bitIndex & 0x1)
        comIndex |= 0x4;
        
    bitIndex >>= 1;
    
    lcdBitmap[bitIndex] &= ~(0x80 >> comIndex);
}


/****************************************************/
/*  Function name: LCD1x9_update                    */
/*  Parameters                                      */
/*    Input   :  No                                 */
/*    Output  :  No                                 */
/*    Action: Updates the LCD's data shown.         */
/****************************************************/
void LCD1x9::update(void){
    
    TinyWireM.beginTransmission(address);
    TinyWireM.send(0xE0);
    TinyWireM.send(0x00);
    for(int i=0; i < 20; i++){
        TinyWireM.send(lcdBitmap[i]);
    }
    TinyWireM.endTransmission();
}


/****************************************************/
/*  Function name: LCD1x9_send                     */
/*  Parameters                                      */
/*    Input   :  str                                */
/*    Output  :  No                                 */
/*    Action: Writes string to the LCD.             */
/****************************************************/
void LCD1x9::write(const char *str){
    
    uint8_t com, bitn, data, len;
    int16_t bitfield;
    
    len = strlen(str);
    if(len > 9)
        return;
        
    for(int i = 0; i < 9; i++){
        if (i < len){
            data = str[i];
        } else {
            data = 0x20;
        }
        
        data -= 0x20;
		
        //bitfield = LCDAlphabet[data];
		 bitfield = pgm_read_word((LCDAlphabet+data));
        
        for(int j = 0; j < 16; j++){
            //bitn = LCD.Text[i].bitt[j];
            //com = LCD.Text[i].com[j];
			bitn = pgm_read_byte(Table+(i*32+j+16));
            com = pgm_read_byte(Table+(i*32+j));
            
            if(bitfield & ((int)1 << j)){
                enableSegment(com, bitn);
            } else {
                disableSegment(com, bitn);
            }
        }
    }
    update();
    
}
LCD1x9 lcd;




