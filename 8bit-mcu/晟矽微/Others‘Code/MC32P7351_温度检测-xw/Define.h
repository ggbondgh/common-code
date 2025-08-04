#ifndef Define_H
#define Define_H


#include "mc32-common.h"
#include "MC32P7351.h"

#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long int
#define uint8_t  unsigned char
#define uint16_t unsigned int
#define uint32_t unsigned long int

#define DEF_SET_BIT0                0x01
#define DEF_SET_BIT1                0x02
#define DEF_SET_BIT2                0x04
#define DEF_SET_BIT3                0x08
#define DEF_SET_BIT4                0x10
#define DEF_SET_BIT5                0x20
#define DEF_SET_BIT6                0x40
#define DEF_SET_BIT7                0x80

#define DEF_CLR_BIT0                0xFE
#define DEF_CLR_BIT1                0xFD
#define DEF_CLR_BIT2                0xFB
#define DEF_CLR_BIT3                0xF7
#define DEF_CLR_BIT4                0xEF
#define DEF_CLR_BIT5                0xDF
#define DEF_CLR_BIT6                0xBF
#define DEF_CLR_BIT7                0x7F

#define FAIL                        1
#define PASS                        0

#define Key                         0x08

//============Define  Flag=================
typedef union {
    unsigned char byte;
    struct
    {
        u8 bit0 : 1;
        u8 bit1 : 1;
        u8 bit2 : 1;
        u8 bit3 : 1;
        u8 bit4 : 1;
        u8 bit5 : 1;
        u8 bit6 : 1;
        u8 bit7 : 1;
    } bits;
}bit_flag;

extern volatile bit_flag Flag1,flag2;

#define   T0_flag        Flag1.bits.bit0   
#define   T1_flag        Flag1.bits.bit1   
#define   T2_flag        Flag1.bits.bit2   
#define   T3_flag        Flag1.bits.bit3  

#define   ON_flag        Flag2.bits.bit0   

/**********Òý½Å¶¨Òå***********/
#define      P_LED                  P11D


#define      LED_ON                 P_LED = 0;
#define      LED_OFF                P_LED = 1;






#endif