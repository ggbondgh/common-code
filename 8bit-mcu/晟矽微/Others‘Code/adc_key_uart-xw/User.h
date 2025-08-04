                
#ifndef USER_H
#define USER_H



//===============Global Function===============
void Sys_Init(void);
void CLR_RAM(void);
void IO_Init(void);
void TIMER0_INT_Init(void);
void TIMER1_INT_Init(void);
void TIMER2_INT_Init(void);
void TIMER3_INT_Init(void);
void TIMER0_PWM_Init(void);
void TIMER1_PWM_Init(void);
void TIMER2_PWM_Init(void);
void ADC_Init(void);
void Scan_ADC(void);
void Set_ADC_Channel(u8 CHX);
uint ADC_Get_Value_Average(void);
void Scan_Key(void);
void Sleep_Func(void);
void delay(uint16_t num);


//extern   	u8;
//volatile u8 abuf;

extern uint16_t adc_data;






#endif


/**************************** end of file *********************************************/
