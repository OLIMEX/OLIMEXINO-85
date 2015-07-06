//==================
//LCD1x9 Header File
//==================
#ifndef LCD1x9_H
#define LCD1x9_H

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

//#error 1

//#include "../Wire/Wire.h"
#include <TinyWireM.h>
//#include "../TinyWireM_Digispark/TinyWireM.h"
#include <avr/pgmspace.h>
#include <inttypes.h>


/**************************************************************************//**
 * @brief
 * Defines each text symbol's segment in terms of COM and BIT numbers,
 * in a way that we can enumerate each bit for each text segment in the
 * following bit pattern:
 * @verbatim
 *  -------0------
 *
 * |   \7  |8  /9 |
 * |5   \  |  /   |1
 *
 *  --6---  ---10--
 *
 * |    /  |  \11 |
 * |4  /13 |12 \  |2
 *
 *  -------3------  .(14)
 *  ------15------
 *
 * @endverbatim
 * E.g.: First text character bit pattern #3 (above) is
 *  Segment 1D for Display
 *  Location COM 3, BIT 0
 *****************************************************************************/
#define address		0x38			// The LCD1x9 I2C address


/**************************************************************************//**
 * @brief Working instance of LCD display
 *****************************************************************************/
volatile const uint8_t Table[] PROGMEM = 
{
  3,3,0,0,2,1,1,3,1,3,1,2,2,2,0,0,                  // com
  34,32,32,34,35,35,34,35,33,33,32,32,33,34,33,35,  // bit    
  3,3,0,0,2,1,1,3,1,3,1,2,2,2,0,0,                  // com
  30,28,28,30,31,31,30,31,29,29,28,28,29,30,29,31,  // bit    
  3,3,0,0,2,1,1,3,1,3,1,2,2,2,0,0,                  // com
  26,24,24,26,27,27,26,27,25,25,24,24,25,26,25,27,  // bit    
  3,3,0,0,2,1,1,3,1,3,1,2,2,2,0,0,                  // com
  22,20,20,22,23,23,22,23,21,21,20,20,21,22,21,23,  // bit    
  3,3,0,0,2,1,1,3,1,3,1,2,2,2,0,0,                  // com
  18,16,16,18,19,19,18,19,17,17,16,16,17,18,17,19,  // bit    
  3,3,0,0,2,1,1,3,1,3,1,2,2,2,0,0,                  // com
  14,12,12,14,15,15,14,15,13,13,12,12,13,14,13,15,  // bit    
  3,3,0,0,2,1,1,3,1,3,1,2,2,2,0,0,                  // com
  10,8,8,10,11,11,10,11,9,9,8,8,9,10,9,11,          // bit    
  3,3,0,0,2,1,1,3,1,3,1,2,2,2,0,0,                  // com
  6,4,4,6,7,7,6,7,5,5,4,4,5,6,5,7,                  // bit    
  3,3,0,0,2,1,1,3,1,3,1,2,2,2,0,0,                  // com
  2,0,0,2,3,3,2,3,1,1,0,0,1,2,1,3                   // bit    
};


/**************************************************************************//**
 * @brief
 * Defines higlighted segments for the alphabet, starting from "blank" (SPACE)
 * Uses bit pattern as defined for text segments above.
 * E.g. a capital O, would have bits 0 1 2 3 4 5 => 0x003f defined
 *****************************************************************************/
volatile const  uint16_t LCDAlphabet[] PROGMEM = {
  // |---------|----|----|----|----|----|----|---|---|---|---|---|---|---|---|---|---|
  // |WORD bit | 15 | 14 | 13 | 12 | 11 | 10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
  // |---------|----|----|----|----|----|----|---|---|---|---|---|---|---|---|---|---| 
  // | Segment | Px |COLx|  M |  L | K  | G2 | J | I | H | G1| F | E | D | C | B | A |
  // |---------|----|----|----|----|----|----|---|---|---|---|---|---|---|---|---|---|
  // |---------|       High        |        Low      |      High     |      Low      |
  // |---------|----|----|----|----|----|----|---|---|---|---|---|---|---|---|---|---|  
  0x0000, /* space */
  0x1100, /* ! */
  0x0280, /* " */
  0x2640, /* # */
  0x156D, /* $ */
  0x2EE4, /* % */
  0x0463, /* & ->> modified to a degree symbol*/
  0x0000, /* £ */
  0x0039, /* ( */
  0x000f, /* ) */
  0x3FC0, /* * */ 
  0x1540, /* + */
  0x0000, /* , */
  0x0440, /* - */
  0x3808, /* . */
  0x2200, /* / */

  0x003f, /* 0 */
  0x0006, /* 1 */
  0x045b, /* 2 */
  0x044f, /* 3 */
  0x0466, /* 4 */
  0x046d, /* 5 */
  0x047d, /* 6 */
  0x0007, /* 7 */
  0x047f, /* 8 */
  0x046f, /* 9 */

  0x3B89, /* : */
  0x0000, /* ; */
  0x0a00, /* < */
  0x0000, /* = */
  0x2080, /* > */
  0x0000, /* ? */
  0xffff, /* @ */

  0x0477, /* A */
  0x0a79, /* B */
  0x0039, /* C */
  0x20b0, /* D */
  0x0079, /* E */
  0x0071, /* F */
  0x043d, /* G edited */
  0x0476, /* H */
  0x1109, /* I edited */
  0x000e, /* J */
  0x0a70, /* K */
  0x0038, /* L */
  0x02b6, /* M */
  0x08b6, /* N */
  0x003f, /* O */
  0x0473, /* P */
  0x083f, /* Q */
  0x0c73, /* R */
  0x046d, /* S */
  0x1101, /* T */
  0x003e, /* U */
  0x2230, /* V */
  0x2836, /* W */
  0x2a80, /* X */
  0x046e, /* Y */
  0x2209, /* Z */

  0x0039, /* [ */
  0x0880, /* backslash */
  0x000f, /* ] */
  0x0001, /* ^ */
  0x0008, /* _ */
  0x0100, /* ` */

  0x1058, /* a */
  0x047c, /* b */
  0x0058, /* c */
  0x045e, /* d */
  0x2058, /* e */
  0x0471, /* f */
  0x0c0c, /* g */
  0x0474, /* h */
  0x1000, /* i edited */
  0x000e, /* j */
  0x0c70, /* k */
  0x20B8, /* l edited */
  0x1454, /* m */
  0x0454, /* n */
  0x045c, /* o */
  0x0473, /* p */
  0x0467, /* q */
  0x0450, /* r */
  0x0c08, /* s */
  0x0078, /* t */
  0x001c, /* u */
  0x2010, /* v */
  0x2814, /* w */
  0x2a80, /* x */
  0x080c, /* y */
  0x2048, /* z */

  0x0000
};


class LCD1x9
{
  public:
    void init(void);
    void write(const char *str);

    
  private:
    uint8_t lcdBitmap[20];
    
    void enableSegment(char comIndex, char bitIndex);
    void disableSegment(char comIndex, char bitIndex);
    void update(void);
};

extern LCD1x9 lcd;

#endif

