                
#ifndef USER_H
#define USER_H
#include "define.h"


//===============Global Function===============
void Sys_Init(void);
void CLR_RAM(void);
void IO_Init(void);
void ADC_Init(void);
void delay(uint16_t num);
void TIMER0_INT_Init(void);
void TIMER1_INT_Init(void);
void TIMER2_INT_Init(void);
void TIMER3_INT_Init(void);
void TIMER0_PWM_Init(void);
void TIMER1_PWM_Init(void);
void TIMER2_PWM_Init(void);
void Sleep_Func(void);
void Scan_Key(void);

// ADC.c
uint16_t ADC_Get_Value_Average(u8 CHX);
uint8_t ADC_Zero_ADJ(void);
void ADC_Power_On_Stability(void);

// Nixie.c
//void LED_IO_in(void);
//void Data_Display_Conversion(uint16_t num_in);
//void LED_Scan_Display_6COM(uint16_t num_in);
//void Set_Bits(void);




#endif


/**************************** end of file *********************************************/
