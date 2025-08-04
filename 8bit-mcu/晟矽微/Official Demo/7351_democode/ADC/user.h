/******************************************************************************
;  *       @型号                   : MC32P7351
;  *       @创建日期               : 2022.12.16
;  *       @公司/作者              : sinomcu.com-FAE
;  *       @晟矽微技术支持         : 2048615934
;  *       @晟矽微官网             : http://www.sinomcu.com/
;  *       @版权                   : 2022 sinomcu.com公司版权所有.
;  *---------------------- 建议 ---------------------------------
;  *                   变量定义时使用全局变量                       
******************************************************************************/
#ifndef USER
#define USER
#include "mc32-common.h"
#include "MC32P7351.h"

/*****************************************************************
;       Function : Define variables
;*****************************************************************/

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

//===============Field Protection Variables===============
u8 abuf;
u8 statusbuf;

//===============Global Variable===============
uint16_t i;
uint16_t g_adc_value0_temp;

uint16_t g_temp_value;
uint8_t g_channel;
uint32_t g_tmpbuff;
uint16_t g_adcmax;
uint16_t g_adcmin;

//===============Global Function===============
void Sys_Init(void);
void CLR_RAM(void);
void IO_Init(void);
void ADC_Power_On_Stability(void);
uint8_t ADC_Zero_ADJ(void);
void ADC_Init(void);
uint ADC_Get_Value_Average(u8 CHX);
void TIMER0_INT_Init(void);

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
volatile bit_flag flag1;

#endif


/**************************** end of file *********************************************/
