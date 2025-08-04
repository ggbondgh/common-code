#ifndef __dasdasdad__
#define	 __dasdasdad__


#include "MC30P8160_include.h"
#include "MC30P8160_MAIN.h"

// 不跳频  4.8M
#define	   	TK_SENS_LEVEL_H1  0x0E     	   	//;TK0触摸灵敏度级别1
#define	   	TK_SENS_LEVEL_L   0xFF     	   	//;TK0触摸灵敏度级别


#define FilterCnt_Value    	11
#define Const_SEN_T_Key0   	45
#define Const_SEN_T_Key0_Release  60

#define Const_SEN_T_Key1   	45
//#define Const_SEN_T_Key1_Release  60

// 触摸
// 位定义
#define    	T_Key0_Signal      	flag1.bits.bit0    	 // 标志位
#define    	Pre_T_Key0_Release  flag1.bits.bit1	   	 // 标志位
#define    	TK0_Release_Flag    flag1.bits.bit2	   	 // 标志位
#define     TK1_Long_press_Flag   flag1.bits.bit3  	 // 标志位
#define    	T0_5ms_Flag        	flag1.bits.bit4	   	 // 标志位
#define    	T0_10ms_Flag        flag1.bits.bit5	   	 // 标志位
#define    	TK0_Long_press_Flag   flag1.bits.bit6  	   	 // 标志位
#define    	W_AS_Flag          flag1.bits.bit7 	   	 // 标志位

#define    	W_Power_Flag       	    flag2.bits.bit0    // 标志位
#define    	PWM_Change_KeyFlg      	flag2.bits.bit1    // 标志位
#define    	TK0_Key_Release_Flag    flag2.bits.bit2    // 标志位
#define     T_Key1_Signal          	flag2.bits.bit3    // 标志位
#define     Pre_T_Key1_Release      flag2.bits.bit4    // 标志位
#define    	Y_Power_Flag           	flag2.bits.bit5    // 标志位
#define    	TK1_Release_Flag        flag2.bits.bit6    // 标志位
#define    	TK1_Key_Release_Flag    flag2.bits.bit7    // 标志位

#define    	Y_AS_Flag                flag3.bits.bit0    // 标志位

//uint8_t T_Key0_Signal;
//uint8_t Pre_T_Key0_Release;
//uint8_t TK0_Release_Flag;


uint16_t u16_get_val;      	   	//读取值
uint16_t u16_release_val;      	//
uint16_t u16_temp_val;

uint16_t u16_release_val_TK0;
uint16_t u16_release_val_TK1;
//uint16_t u16_TK0_get_val_Temp;
//uint16_t u16_TK1_get_val_Temp;
uint16_t u16_TK1_get_val_Min;
uint16_t u16_TK0_get_val_Min;

uint16_t u16_TK0_environment_val;
uint16_t u16_TK0_environment_val_Sum;
uint16_t u16_TK1_environment_val;
uint16_t u16_TK1_environment_val_Sum;

///////////////////////////////////////

uint8_t TK0_Filter_Cnt;
uint8_t TK0_Filter_Cnt_T;
uint8_t TK1_Filter_Cnt;
uint8_t TK1_Filter_Cnt_T;

uint8_t FilterCnt_TK0;
uint8_t FilterCnt_TK1;

uint8_t SleepCnt;  //睡眠计数

// PWM
//uint8_t PWM_Duty_Temp;
uint8_t PWM_Duty_W;
uint8_t PWM_Duty_Y;

uint8_t T_key_Value; // 0 1 2 3 
uint8_t TK1_Key_Cnt;
uint8_t TK0_Key_Cnt;


uint8_t T0_5ms_Cnt;
uint16_t u8_TK_Reset_Cnt;
uint16_t u16_TK0_get_val_Temp;
uint16_t u16_TK1_get_val_Temp;
// 串口
#define  Uart_TX     P14D


void IO_Init(void);

#endif 	