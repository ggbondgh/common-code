#ifndef __ADC_H_
#define __ADC_H_

//#include "MC32P7351.h"
#include "Define.h"

void Set_ADC_Channel(u8 CHX);
uint ADC_Get_Value_Average(void);
void Scan_ADC(void);
uint8_t ADC_Zero_ADJ(void);
void ADC_Power_On_Stability(void);


#endif
