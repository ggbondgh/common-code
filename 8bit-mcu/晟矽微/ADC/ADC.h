#ifndef __ADC_H_
#define __ADC_H_
#include "Define.h"

void delay(uint16_t num);
uint16_t ADC_Get_Value_Average(u8 CHX);
uint8_t ADC_Zero_ADJ(void);
void ADC_Power_On_Stability(void);


#endif

