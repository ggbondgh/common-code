/********************************************************************************
								单点触摸
---------------------------------------------------------------------------------
使用方法：
    1.在主循环前调用：
    
	TK_Init();

	2.在主循环-定时5ms-中调用：
	
	if(T16_5ms_Flag_TK)
	{
		T16_5ms_Flag_TK = 0;
		TK11_Scan();
		TK11_OUT_Control();
		Long_Press_Reset();
	}

	3.中断中需要做个5ms定时，标志位是：T16_5ms_Flag_TK(已定义)

	4.TK11_OUT_Control里面就是触摸后要执行的User Code，也可以将其放在主文件中便于改动

	5.需要把该文件最下方的“extern.h”内容加到extern.h
---------------------------------------------------------------------------------
注意：
	1.例程用的是Key11，如果用其他触摸脚需要把“11”全部改成相应数字
********************************************************************************/

#include	"extern.h"


#define FilterCnt_Value  8 
#define Const_SEN_T_Key11  30 //按下阈值
#define Const_SEN_T_Key11_Release  40 //松开阈值

word u16_get_val;		//读取值
word u16_Press_val;     //按下后的读取值
word u16_release_val;	//松开后的读取值

eword u16_TK11_environment_val_Sum = 0; //用于暂时存取累加值
word u16_TK11_environment_val;			//环境值（用于跟随读取值）
word u16_release_val_TK11 = 0;  		//按下后的 “环境值-按下阈值”
bit  TK11_Release_Flag;

word u16_temp_val = 0;  //一阶滤波用到的临时变量

byte TK11_Filter_Cnt = 0;
byte TK11_Release_Cnt = 0;
byte Pre_T_Key11_Release = 1; //松开前标志位，1为松开前检测按下，0为按下后检测松开
byte FilterCnt_TK11;
word u16_get_val_Temp_TK11 = 0;

bit  T_Key11_Signal; //状态标志位：1为按下的状态，0为松开的状态

word RestCnt;	//长按复位计数

bit T16_5ms_Flag_TK;


void	TK_Init(void)
{
	TS   = 0b_0011_00_11; 	// IHRC/8, 0.5*VCC, 128*CLK
	TKE1 = 0b_0000_000_0;
	TKE2 = 0b_0000_000_0;

	TPS2 = 0x01; // CS 接VDD
}

void	TK_Release_(void)
{
	//清零松开的计数值，置相关标志位
	TK11_Release_Cnt = 0;

	T_Key11_Signal = 0;
	Pre_T_Key11_Release = 1;					
	u16_TK11_environment_val = u16_get_val;
	TK11_Filter_Cnt = 0;
	u16_TK11_environment_val_Sum = 0;

	TK11_Release_Flag = 1;
}

void	TK11_Scan(void) //*********
{	
	TKE2 = 0b_0000_1000;	//使能TK11，PB.0
	
	//获取触摸值
	$ TCC TK_RUN;
	while(A != 0x00) 
	{
		A = TCC & 0x70;
	}
	u16_get_val =  (TKCH << 8) | TKCL;

	//一阶滤波
	u16_temp_val = u16_get_val_Temp_TK11 << 2;
	u16_temp_val -= u16_get_val_Temp_TK11;
	u16_temp_val += u16_get_val;
	u16_get_val_Temp_TK11 = u16_temp_val >> 2;

	u16_get_val = u16_get_val_Temp_TK11;


	if(Pre_T_Key11_Release) //检测是否按下
	{
		u16_Press_val = u16_get_val + Const_SEN_T_Key11;
		
		if(u16_Press_val < u16_TK11_environment_val)	 //按下，跟随值>读取值+按下阈值
		{
		//	Const_Env_Dw_Fix_Speed = 5;

			FilterCnt_TK11 ++;
			if(FilterCnt_TK11 >= FilterCnt_Value)  //滤波，检测到连续多次才视为按下
			{
				T_Key11_Signal = 1;
				Pre_T_Key11_Release = 0;
				u16_release_val_TK11 = u16_TK11_environment_val - Const_SEN_T_Key11; //留取，给后面松开检测用
			}
		}
		else //更新环境值，跟随读取值
		{
			FilterCnt_TK11 = 0;

			// 检测多次读取值取平均值
			TK11_Filter_Cnt ++;
			u16_TK11_environment_val_Sum += u16_get_val; //读取值累加
			if(TK11_Filter_Cnt > 31) //累加32次
			{
				TK11_Filter_Cnt = 0;
				u16_TK11_environment_val = u16_TK11_environment_val_Sum >> 5; //除以2^5=32
				u16_TK11_environment_val_Sum = 0;

				if(TK11_Release_Flag)
				{
					TK11_Release_Flag = 0;
					u16_TK11_environment_val = u16_get_val;
				}
			}

			if(TK11_Release_Flag == 1) //累加中执行此判别
			{
				if(u16_get_val > u16_TK11_environment_val)
				{
					u16_TK11_environment_val = u16_get_val;
				}
			}
		}
	}
	else   //检测是否松开
	{
		FilterCnt_TK11 = 0; //清零上面按下的计数值

		//环境值跟随读取值
		TK11_Filter_Cnt++;

		if(TK11_Filter_Cnt >= 3) // 15ms
		{
			TK11_Filter_Cnt = 0;

			if(u16_get_val <= u16_TK11_environment_val)
			{
				u16_TK11_environment_val = u16_get_val;
			}
			else
			{
				u16_TK11_environment_val ++;
			}
		}

		//松开检测
		if(u16_get_val > u16_TK11_environment_val)
		{
			u16_release_val = u16_get_val - u16_TK11_environment_val;
		}
		else
		{
			u16_release_val = 0;
		}

		if(u16_get_val > u16_release_val_TK11 || u16_release_val > Const_SEN_T_Key11_Release)	//松开
		{
			TK11_Release_Cnt ++;
			if(TK11_Release_Cnt >= 4) //触摸松开滤波 20ms
			{
				TK_Release_();
			}
		}
		else
		{
			TK11_Release_Cnt = 0;
		}	
    }	
}

void	Long_Press_Reset(void)
{
	if(T_Key11_Signal)	//有按键按下
	{
		RestCnt ++;
		if(RestCnt > 1000) //约 10S
		{
			RestCnt = 0;
			TK_Release_();
		}
	}
	else
	{
		RestCnt = 0;
	}
}

void	TK11_OUT_Control(void)
{
	if(T_Key11_Signal)
	{
		//User Code
		//$ PA.3 out, high;
	}
	else
	{
		//User Code
		//$ PA.3 out, low;
	}
}

/*---------------------------------extern.h-----------------------------------

#ifndef	extern_h
#define	extern_h


SysClock_DIV => 8

Const_Sleep_WakeUp       	=>  3580  //3680 80MS

System_Clock	EQU	8000000	//	Used at UART, PS2, ...
PMS164	=>	0x164
Chip_Name	=>	PMS164
#if	defined(ADCC)
	#if defined(ADCR)
		ADCRH	EQU		ADCR
		ADCRL	EQU		0
	#else
		ADCR	EQU		ADCRH
	#endif
#endif





	Const_Touch_Source_CLK	=>	3;	//Touch Pad clock selection,取值0-8
									//0:reserved, 1:reserved, 2:IHRC/4, 3:IHRC/8,
									//4:IHRC/16, 5:IHRC/32, 6:IHRC/64, 7:IHRC/128, 8:ILRC
									//default:2
	Const_Touch_VRef		=>  0;	//0:0.5*VCC, 1:0.4*VCC, 2:0.3*VCC, 3:0.2*VCC
									//CS电容参考电压设定 0.2VCC-0.5VCC
									//对CS电容大小和触摸灵敏度有影响
									//此处提高可降低外部基准电容
									//default:0
	Const_Touch_Discharge	=>	3;	
									//0:reserved, 1:CLK_32, 2:CLK_64, 3:CLK_128	
									//default:1
#endif

---------------------------------------------------------------------------*/
