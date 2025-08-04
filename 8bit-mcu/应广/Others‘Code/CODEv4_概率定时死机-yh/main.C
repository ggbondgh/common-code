#include	"extern.h"
/*未初始化全局变量，运行后编译器会初始赋值为 0 */
#define T_500us		977

#define SysClock_DIV  8 // 16M/8 = 2MHz 系统时钟

#define FilterCnt_Value  2 			// 按下滤波次数 5*10 = 50ms 

#define Const_SEN_T_Key  20			// 按下阈值 
#define Const_SEN_T_Key_Release  25	// 中途松开阈值 不回到触发点

#define Const_Sleep_WakeUp  3680  		// 3680 约80MS

word u16_get_val;		//读取值
word u16_Press_val;     //按下
word u16_release_val;	//松开

eword u16_TK1_environment_val_Sum = 0,u16_TK2_environment_val_Sum = 0,u16_TK3_environment_val_Sum = 0,u16_TK4_environment_val_Sum = 0;	//按键环境值之和
word u16_TK1_environment_val = 0,u16_TK2_environment_val = 0,u16_TK3_environment_val = 0,u16_TK4_environment_val = 0;		//按键环境值
word u16_get_val_Temp_TK1 = 0,u16_get_val_Temp_TK2 = 0,u16_get_val_Temp_TK4 = 0,u16_get_val_Temp_TK3 = 0;
word u16_release_val_TK = 0;
word u16_temp_val = 0;

byte TK1_environment_val_FilterCnt = 0,TK2_environment_val_FilterCnt = 0,TK4_environment_val_FilterCnt = 0,TK3_environment_val_FilterCnt = 0;	//按键环境值滤波计数
byte TK1_Filter_Cnt = 0,TK2_Filter_Cnt = 0,TK4_Filter_Cnt = 0,TK3_Filter_Cnt = 0;
byte TK1_Release_Cnt = 0,TK2_Release_Cnt = 0,TK4_Release_Cnt = 0,TK3_Release_Cnt = 0;

bit	 Pre_T_Key1_Release,Pre_T_Key2_Release,Pre_T_Key4_Release,Pre_T_Key3_Release;	// 触摸抬起标志位；1检测按下  0 判断松开
bit  TK1_Release_Flag,TK2_Release_Flag,TK4_Release_Flag,TK3_Release_Flag;

//----------------------------------------------------------------------------------------------------------

bit  T_Key1_Signal,T_Key2_Signal,T_Key3_Signal,T_Key4_Signal; 			// 触摸状态标志位； 1按下 0松开
//----------------------------------------------------------------------------------------------------------
byte  SleepCnt = 200;
bit   TK1_status,TK3_status,TK4_status;	//按键未按下状态

bit   	T16_10ms_Flag_Sleep;
bit   	T16_10ms_Flag_TK;
byte	Time1_100us = 0;
byte  	Time2_100us = 0;
word  	Time3_100us = 0;
byte  	Time4_100us = 0;
word  	Time5_100us = 0;
byte	TK_press_cnt = 0;

bit		Pow_Switch_Flag;
bit		IR_Key_Long_Press;
bit		TK_Key_Release_Flag;
bit		TK_Mode_Flag;
bit		Duty_PM_Flag;
//-------------------------------------------
bit		TK_UpDate_Flag;
bit		TK_Pow_UpDate_Flag;
bit		Flash_AS_Flag;
byte	level = 0,level_temp = 0,Mode_Value = 0;
byte	Level_duty_Temp = 42,Tomato_Flash_duty_Temp = 42;
byte	duty_Buff = 0,swap_duty = 0;

bit		TK_LongPress_CntFlag;
//-------------------------------------------
bit		Read_Write_Flag;
bit		RW_UpDate_Flag;
byte	RW_duty = 76;
//-------------------------------------------
bit		Long_Sign;
byte	icnt;
byte	IR_Sign;
byte	IR_Mode;
byte	Time_20ms;
Dword	IR_Data;
byte	i;
dword	data;
bit		IR_Key_Press;
bit		Receive_Over_Flag;
//-------------------------------------------
bit		Tomato_UpDate_Flag;
bit		Tomato_Switch_Flag;
bit		Tomato_Flash_Flag;

word	Timer_1s_Cnt = 0;
//-------------------------------------------
#define	Level_1		42
#define	Level_2		85
#define	Level_3		127
#define	Level_4		170
#define	Level_5		212
#define	Level_6		255

SW_LED =>	PB.1;
RW_LED =>	PB.0;
TM_LED =>	PB.2;

IR	 =>	PB.6;

Word	Reload_T16;

void   Timer16_Init(void) // T16 100us 中断
{
	Reload_T16 = 32768 - 1600;
	stt16 Reload_T16;
	$ T16M IHRC,/1,bit15;
	$ INTEGS BIT_R;
	INTRQ.T16 = 0;
	INTEN.T16 = 1;
	ENGINT;
}
//-------------------------------------------
void PWM2_Init()//W
{
	TM2B = 42;
	$ TM2S 8BIT,/1,/3;
//	$ TM2C IHRC,PB4,PWM;
	$ TM2C stop;
}

void PWM3_Init()//Y
{
	TM3B = 42;
	$ TM3S 8BIT,/1,/3;
//	$ TM3C IHRC,PB7,PWM;
	$ TM3C stop;
}
//-------------------------------------------
void TK_Value_Read()
{
//	$ TCC TK_RUN;
//	while(A != 0x00) 
//	{
//		A = TCC & 0x70;
//	}
	$ TCC	OV_Enable,TK_RUN;
	f_TK_END = 0;

	Do
	{
		if(f_TK_OV)
		{
			f_TK_OV	=	0;
			//u16_get_val	+=	4096;
		}
	}
	while(f_TK_END==0);

	u16_get_val =  (TKCH << 8) | TKCL;//高8与低8合并成16位（左移高位存放至16位高八位）
}



void TK1_Scan() //********* TK6 PA.4**************
{	

		$ TKE PA.0;

		TK_Value_Read();

		u16_temp_val = u16_get_val + Const_SEN_T_Key; // 睡眠唤醒
		if(u16_temp_val < u16_TK1_environment_val)
		{
			SleepCnt = 200; // 10S
		}

		// 读到的触摸值消抖， 一阶8倍滤波
		u16_temp_val = u16_get_val_Temp_TK1 << 2; // 上次滤波的8倍
		u16_temp_val -= u16_get_val_Temp_TK1;
		u16_temp_val += u16_get_val; 			  // 上次滤波的7倍与本次滤波之和
		u16_get_val_Temp_TK1 = u16_temp_val >> 2; // 取平均，作为本次滤波值

		u16_get_val = u16_get_val_Temp_TK1; 	  // 滤波后的触摸值

		if(Pre_T_Key1_Release) 
		{
			u16_Press_val = u16_get_val + Const_SEN_T_Key;
			
			if(u16_Press_val < u16_TK1_environment_val)	 // 大于触摸设定阈值，有按下
			{
				TK1_Filter_Cnt ++;
				if(TK1_Filter_Cnt > FilterCnt_Value) // 按下滤波，大于滤波次数(50ms  10次)判断为按下
				{
					TK1_Filter_Cnt = 0;
					T_Key1_Signal = 1; // 触摸按下，标志位置1
					Pre_T_Key1_Release = 0;
					u16_release_val_TK = u16_TK1_environment_val - Const_SEN_T_Key; // 提前松开判断值
				}
			}
			else // 无触摸时，更新环境值
			{
				TK1_Filter_Cnt = 0;

				if(SleepCnt) // 正常扫描状态，5ms一次
				{
					TK1_environment_val_FilterCnt ++;
					u16_TK1_environment_val_Sum += u16_get_val;
					if(TK1_environment_val_FilterCnt >= 16) 					// 32次取值求平均
					{
						TK1_environment_val_FilterCnt = 0;
						u16_TK1_environment_val = u16_TK1_environment_val_Sum >> 4;
						u16_TK1_environment_val_Sum = 0;

						if(TK1_Release_Flag)
						{
							TK1_Release_Flag = 0;
							u16_TK1_environment_val = u16_get_val;
						}
					}
				}
				else // 睡眠状态
				{
					u16_TK1_environment_val = u16_get_val;
					u16_TK1_environment_val_Sum = 0;
					TK1_Filter_Cnt = 0;
				}

				if(TK1_Release_Flag == 1)
				{
					if(u16_get_val > u16_TK1_environment_val)
					{
						u16_TK1_environment_val = u16_get_val;
					}
				}
			}
		}
		else  
		{
			TK1_Filter_Cnt++;
			if(TK1_Filter_Cnt >= 2) // 15ms  触摸按下后环境值修正
			{
				TK1_Filter_Cnt = 0;
				if(u16_get_val <= u16_TK1_environment_val)
				{
					u16_TK1_environment_val = u16_get_val;
				}
				else
				{
					u16_TK1_environment_val ++;
				}
			}

			if(u16_get_val > u16_TK1_environment_val)
			{
				u16_release_val = u16_get_val - u16_TK1_environment_val;
			}
			else
			{
				u16_release_val = 0;
			}

			if(u16_get_val > u16_release_val_TK || u16_release_val > Const_SEN_T_Key_Release)	//松开
			{
				TK1_Release_Cnt ++;
				if(TK1_Release_Cnt >= 2) //触摸松开滤波 20ms
				{
					TK1_Release_Cnt = 0;

					T_Key1_Signal = 0; 	// 触摸松开，标志位置0
					Pre_T_Key1_Release = 1;					
					u16_TK1_environment_val = u16_get_val;
					TK1_environment_val_FilterCnt = 0;
					u16_TK1_environment_val_Sum = 0;

					TK1_Release_Flag = 1;
				}
			}
			else
			{
				TK1_Release_Cnt = 0;
			}
	    }
}

void TK2_Scan() //********* TK8 PA.6**************
{	

		$ TKE PA.4;

		TK_Value_Read();

		u16_temp_val = u16_get_val + Const_SEN_T_Key; // 睡眠唤醒

		// 读到的触摸值消抖， 一阶8倍滤波
		u16_temp_val = u16_get_val_Temp_TK2 << 2; // 上次滤波的8倍
		u16_temp_val -= u16_get_val_Temp_TK2;
		u16_temp_val += u16_get_val; 			  // 上次滤波的7倍与本次滤波之和
		u16_get_val_Temp_TK2 = u16_temp_val >> 2; // 取平均，作为本次滤波值

		u16_get_val = u16_get_val_Temp_TK2; 	  // 滤波后的触摸值

		if(Pre_T_Key2_Release) 
		{
			u16_Press_val = u16_get_val + Const_SEN_T_Key;
			
			if(u16_Press_val < u16_TK2_environment_val)	 // 大于触摸设定阈值，有按下
			{
				TK2_Filter_Cnt ++;
				if(TK2_Filter_Cnt > FilterCnt_Value) // 按下滤波，大于滤波次数(50ms  10次)判断为按下
				{
					TK2_Filter_Cnt = 0;
					T_Key2_Signal = 1; // 触摸按下，标志位置1
					Pre_T_Key2_Release = 0;
					u16_release_val_TK = u16_TK2_environment_val - Const_SEN_T_Key; // 提前松开判断值
				}
			}
			else // 无触摸时，更新环境值
			{
				TK2_Filter_Cnt = 0;

				TK2_environment_val_FilterCnt ++;
				u16_TK2_environment_val_Sum += u16_get_val;
				if(TK2_environment_val_FilterCnt >= 16) 					// 32次取值求平均
				{
					TK2_environment_val_FilterCnt = 0;
					u16_TK2_environment_val = u16_TK2_environment_val_Sum >> 4;
					u16_TK2_environment_val_Sum = 0;

					if(TK2_Release_Flag)
					{
						TK2_Release_Flag = 0;
						u16_TK2_environment_val = u16_get_val;
					}
				}
				
				if(TK2_Release_Flag == 1)
				{
					if(u16_get_val > u16_TK2_environment_val)
					{
						u16_TK2_environment_val = u16_get_val;
					}
				}
			}
		}
		else  
		{
			TK2_Filter_Cnt++;
			if(TK2_Filter_Cnt >= 2) // 15ms  触摸按下后环境值修正
			{
				TK2_Filter_Cnt = 0;
				if(u16_get_val <= u16_TK2_environment_val)
				{
					u16_TK2_environment_val = u16_get_val;
				}
				else
				{
					u16_TK2_environment_val ++;
				}
			}

			if(u16_get_val > u16_TK2_environment_val)
			{
				u16_release_val = u16_get_val - u16_TK2_environment_val;
			}
			else
			{
				u16_release_val = 0;
			}

			if(u16_get_val > u16_release_val_TK || u16_release_val > Const_SEN_T_Key_Release)	//松开
			{
				TK2_Release_Cnt ++;
				if(TK2_Release_Cnt >= 2) //触摸松开滤波 20ms
				{
					TK2_Release_Cnt = 0;

					T_Key2_Signal = 0; 	// 触摸松开，标志位置0
					Pre_T_Key2_Release = 1;					
					u16_TK2_environment_val = u16_get_val;
					TK2_environment_val_FilterCnt = 0;
					u16_TK2_environment_val_Sum = 0;

					TK2_Release_Flag = 1;
				}
			}
			else
			{
				TK2_Release_Cnt = 0;
			}
	    }
}


void TK3_Scan() //********* TK3 PB.6**************
{	
		$ TKE PA.3;

		TK_Value_Read();

		u16_temp_val = u16_get_val + Const_SEN_T_Key; // 睡眠唤醒		

		// 读到的触摸值消抖， 一阶8倍滤波
		u16_temp_val = u16_get_val_Temp_TK4 << 2; // 上次滤波的8倍
		u16_temp_val -= u16_get_val_Temp_TK4;
		u16_temp_val += u16_get_val; 			  // 上次滤波的7倍与本次滤波之和
		u16_get_val_Temp_TK4 = u16_temp_val >> 2; // 取平均，作为本次滤波值

		u16_get_val = u16_get_val_Temp_TK4; 	  // 滤波后的触摸值

		if(Pre_T_Key4_Release) 
		{
			u16_Press_val = u16_get_val + Const_SEN_T_Key;
			
			if(u16_Press_val < u16_TK3_environment_val)	 // 大于触摸设定阈值，有按下
			{
				TK4_Filter_Cnt ++;
				if(TK4_Filter_Cnt > FilterCnt_Value) // 按下滤波，大于滤波次数(50ms  10次)判断为按下
				{
					TK4_Filter_Cnt = 0;
					T_Key3_Signal = 1; // 触摸按下，标志位置1
					Pre_T_Key4_Release = 0;
					u16_release_val_TK = u16_TK3_environment_val - Const_SEN_T_Key; // 提前松开判断值
				}
			}
			else // 无触摸时，更新环境值
			{
				TK4_Filter_Cnt = 0;
				
				TK4_environment_val_FilterCnt ++;
				u16_TK3_environment_val_Sum += u16_get_val;
				if(TK4_environment_val_FilterCnt >= 16) 					// 32次取值求平均
				{
					TK4_environment_val_FilterCnt = 0;
					u16_TK3_environment_val = u16_TK3_environment_val_Sum >> 4;
					u16_TK3_environment_val_Sum = 0;

					if(TK4_Release_Flag)
					{
						TK4_Release_Flag = 0;
						u16_TK3_environment_val = u16_get_val;
					}
				}
								
				if(TK4_Release_Flag == 1)
				{
					if(u16_get_val > u16_TK3_environment_val)
					{
						u16_TK3_environment_val = u16_get_val;
					}
				}
			}
		}
		else  
		{
			TK4_Filter_Cnt++;
			if(TK4_Filter_Cnt >= 2) // 15ms  触摸按下后环境值修正
			{
				TK4_Filter_Cnt = 0;
				if(u16_get_val <= u16_TK3_environment_val)
				{
					u16_TK3_environment_val = u16_get_val;
				}
				else
				{
					u16_TK3_environment_val ++;
				}
			}

			if(u16_get_val > u16_TK3_environment_val)
			{
				u16_release_val = u16_get_val - u16_TK3_environment_val;
			}
			else
			{
				u16_release_val = 0;
			}

			if(u16_get_val > u16_release_val_TK || u16_release_val > Const_SEN_T_Key_Release)	//松开
			{
				TK4_Release_Cnt ++;
				if(TK4_Release_Cnt >= 2) //触摸松开滤波 20ms
				{
					TK4_Release_Cnt = 0;

					T_Key3_Signal = 0; 	// 触摸松开，标志位置0
					Pre_T_Key4_Release = 1;					
					u16_TK3_environment_val = u16_get_val;
					TK4_environment_val_FilterCnt = 0;
					u16_TK3_environment_val_Sum = 0;

					TK4_Release_Flag = 1;
				}
			}
			else
			{
				TK4_Release_Cnt = 0;
			}	
	    }	
}

void TK4_Scan() //********* TK10 PB.3**************
{	

		$ TKE PB.3;

		TK_Value_Read();

		u16_temp_val = u16_get_val + Const_SEN_T_Key; // 睡眠唤醒

		// 读到的触摸值消抖， 一阶8倍滤波
		u16_temp_val = u16_get_val_Temp_TK3 << 2; // 上次滤波的8倍
		u16_temp_val -= u16_get_val_Temp_TK3;
		u16_temp_val += u16_get_val; 			  // 上次滤波的7倍与本次滤波之和
		u16_get_val_Temp_TK3 = u16_temp_val >> 2; // 取平均，作为本次滤波值

		u16_get_val = u16_get_val_Temp_TK3; 	  // 滤波后的触摸值

		if(Pre_T_Key3_Release) 
		{
			u16_Press_val = u16_get_val + Const_SEN_T_Key;
			
			if(u16_Press_val < u16_TK4_environment_val)	 // 大于触摸设定阈值，有按下
			{
				TK3_Filter_Cnt ++;
				if(TK3_Filter_Cnt > FilterCnt_Value) // 按下滤波，大于滤波次数(50ms  10次)判断为按下
				{
					TK3_Filter_Cnt = 0;
					T_Key4_Signal = 1; // 触摸按下，标志位置1
					Pre_T_Key3_Release = 0;
					u16_release_val_TK = u16_TK4_environment_val - Const_SEN_T_Key; // 提前松开判断值
				}
			}
			else // 无触摸时，更新环境值
			{
				TK3_Filter_Cnt = 0;

				TK3_environment_val_FilterCnt ++;
				u16_TK4_environment_val_Sum += u16_get_val;
				if(TK3_environment_val_FilterCnt >= 16) 					// 32次取值求平均
				{
					TK3_environment_val_FilterCnt = 0;
					u16_TK4_environment_val = u16_TK4_environment_val_Sum >> 4;
					u16_TK4_environment_val_Sum = 0;

					if(TK3_Release_Flag)
					{
						TK3_Release_Flag = 0;
						u16_TK4_environment_val = u16_get_val;
					}
				}
				
				if(TK3_Release_Flag == 1)
				{
					if(u16_get_val > u16_TK4_environment_val)
					{
						u16_TK4_environment_val = u16_get_val;
					}
				}
			}
		}
		else  
		{
			TK3_Filter_Cnt++;
			if(TK3_Filter_Cnt >= 2) // 15ms  触摸按下后环境值修正
			{
				TK3_Filter_Cnt = 0;
				if(u16_get_val <= u16_TK4_environment_val)
				{
					u16_TK4_environment_val = u16_get_val;
				}
				else
				{
					u16_TK4_environment_val ++;
				}
			}

			if(u16_get_val > u16_TK4_environment_val)
			{
				u16_release_val = u16_get_val - u16_TK4_environment_val;
			}
			else
			{
				u16_release_val = 0;
			}

			if(u16_get_val > u16_release_val_TK || u16_release_val > Const_SEN_T_Key_Release)	//松开
			{
				TK3_Release_Cnt ++;
				if(TK3_Release_Cnt >= 2) //触摸松开滤波 20ms
				{
					TK3_Release_Cnt = 0;

					T_Key4_Signal = 0; 	// 触摸松开，标志位置0
					Pre_T_Key3_Release = 1;					
					u16_TK4_environment_val = u16_get_val;
					TK3_environment_val_FilterCnt = 0;
					u16_TK4_environment_val_Sum = 0;

					TK3_Release_Flag = 1;
				}
			}
			else
			{
				TK3_Release_Cnt = 0;
			}
	    }
}

//-------------------------------------------
void	Light_Control();

void	Pow_off_on()
{
	if(TK_Pow_UpDate_Flag)
	{
		TK_Pow_UpDate_Flag = 0;

		//TK_UpDate_Flag = 1;

		if(Pow_Switch_Flag)
		{
			SW_LED = 0;

			level = level_temp;

			TK_UpDate_Flag = 1;

			Light_Control();

			if(Mode_Value == 0)
			{
				$ TM2C IHRC,PB4,PWM;

				$ TM3C IHRC,PB7,PWM;
			}
			else if(Mode_Value == 1)
			{
				$ TM2C stop;

				$ TM3C IHRC,PB7,PWM;
			}
			else if(Mode_Value == 2)
			{
				$ TM2C IHRC,PB4,PWM;

				$ TM3C stop;
			}

			while(duty_Buff < Level_duty_Temp)
			{
				duty_Buff ++;

				TM2B = duty_Buff;
				TM3B = duty_Buff;

				.delay 4*2000;

				if(duty_Buff == Level_duty_Temp)
					break;
			}
		}
		else
		{
			SW_LED = 1;

			TM_LED = 1;

			RW_LED = 1;

			level = 0;

			duty_Buff = 0;

			Tomato_Flash_Flag = 0;//番茄定时闪烁标志清零,防止亮度缓降与闪烁冲突

			Flash_AS_Flag = 0;

			if(Read_Write_Flag)
			{
				while(RW_duty > 0)
				{
					RW_duty --;

					TM2B = RW_duty;
					TM3B = RW_duty;

					.delay 4*2000;

					if(RW_duty == 0)
						break;
				}

				Read_Write_Flag = 0;
			}
			else
			{
				while(Level_duty_Temp > 0)
				{
					Level_duty_Temp --;

					TM2B = Level_duty_Temp;
					TM3B = Level_duty_Temp;

					.delay 4*2000;

					if(Level_duty_Temp == 0)
						break;
				}
			}

			$ TM2C STOP;
			$ TM3C STOP;			
		}
	}
}


void	Light_Control()
{	
	if(TK_UpDate_Flag)
	{
		TK_UpDate_Flag = 0;

		if(level == 0)
		{
			TM2B = Level_1;//16.8
			TM3B = Level_1;

			Level_duty_Temp = Level_1;
			Tomato_Flash_duty_Temp = Level_duty_Temp;
		}
		else if(level == 1)
		{
			TM2B = Level_2;//33.6
			TM3B = Level_2;

			Level_duty_Temp = Level_2;
			Tomato_Flash_duty_Temp = Level_duty_Temp;
		}
		else if(level == 2)
		{
			TM2B = Level_3;//50
			TM3B = Level_3;

			Level_duty_Temp = Level_3;
			Tomato_Flash_duty_Temp = Level_duty_Temp;
		}
		else if(level == 3)
		{
			TM2B = Level_4;//66.88
			TM3B = Level_4;

			Level_duty_Temp = Level_4;
			Tomato_Flash_duty_Temp = Level_duty_Temp;
		}
		else if(level == 4)
		{
			TM2B = Level_5;//83.2
			TM3B = Level_5;

			Level_duty_Temp = Level_5;
			Tomato_Flash_duty_Temp = Level_duty_Temp;
		}
		else if(level == 5)
		{
			TM2B = Level_6;//100
			TM3B = Level_6;

			Level_duty_Temp = Level_6;
			Tomato_Flash_duty_Temp = Level_duty_Temp;
		}

//		duty_temp = Level_duty_Temp;

		if(TK_Mode_Flag)
		{
			TK_Mode_Flag = 0;

			if(Mode_Value == 0)
			{
				$ TM2C IHRC,PB4,PWM;

				$ TM3C IHRC,PB7,PWM;
			}
			else if(Mode_Value == 1)
			{
				$ TM2C stop;

				$ TM3C IHRC,PB7,PWM;
			}
			else if(Mode_Value == 2)
			{
				$ TM2C IHRC,PB4,PWM;

				$ TM3C stop;
			}
		}
	}
}
//-------------------------------------------
void	RW_function()
{
	if(RW_UpDate_Flag)
	{
		RW_UpDate_Flag = 0;

		RW_duty = 76;

		if(Read_Write_Flag)
		{
			Tomato_Flash_duty_Temp = RW_duty;

			RW_LED = 0;

			$ TM2C IHRC,PB4,PWM;

			$ TM3C IHRC,PB7,PWM;

			TM2B = RW_duty;//30
			TM3B = RW_duty;
		}
		else
		{
			RW_LED = 1;

			if(Pow_Switch_Flag)
			{
				TK_UpDate_Flag = 1;

				TK_Mode_Flag = 1;
			}
		}
	}
}

//-------------------------------------------
void Tomato_Flash()
{
	if(Duty_PM_Flag)
	{
		Duty_PM_Flag = 0;

		if(Tomato_Flash_duty_Temp > 0 && Flash_AS_Flag == 0)
		{
			Tomato_Flash_duty_Temp --;

			TM2B = Tomato_Flash_duty_Temp;
			TM3B = Tomato_Flash_duty_Temp;

			if(Tomato_Flash_duty_Temp == 0)
				Flash_AS_Flag = 1;
		}

		if(!Read_Write_Flag)
			swap_duty = Level_duty_Temp;
		else
			swap_duty = RW_duty;

		if(Tomato_Flash_duty_Temp < swap_duty && Flash_AS_Flag == 1)
		{
			Tomato_Flash_duty_Temp ++;

			TM2B = Tomato_Flash_duty_Temp;
			TM3B = Tomato_Flash_duty_Temp;

			if(Tomato_Flash_duty_Temp == swap_duty)
			{
				//Timer_1s_Cnt = 0;
				Tomato_Flash_Flag = 0;

				Flash_AS_Flag = 0;
			}
		}
	}
}


void	Tomato_Timer()
{
	if(Tomato_UpDate_Flag)
	{
		Tomato_UpDate_Flag = 0;

		if(Tomato_Switch_Flag)
		{
			TM_LED = 0;

			Tomato_Flash_Flag = 1;
		}
		else
		{
			TM_LED = 1;

			Time3_100us = 0;//定时计数清零
			Timer_1s_Cnt = 0;
		}
	}
}
//-------------------------------------------
void	Touch_function()
{	
	if(T_Key1_Signal && !TK1_status)   //开关
	{
		TK1_status = 1;

		TK_Pow_UpDate_Flag = 1;

		if(Pow_Switch_Flag)//关机
		{
			Pow_Switch_Flag = 0;	

			if(Read_Write_Flag)
			{
				Read_Write_Flag = 0;
				RW_UpDate_Flag = 1;	
			}

			if(Tomato_Switch_Flag)
			{
				Tomato_UpDate_Flag = 1;
				Tomato_Switch_Flag = 0;
			}
		}
		else //开机
		{
			Pow_Switch_Flag = 1;

			//TK_Mode_Flag = 1;//开机打开PWM			
		}
	}
  	else if(!T_Key1_Signal)
	{
		TK1_status = 0;
	}
//-------------------------------------------
	if(T_Key2_Signal)   //亮度/色温
	{
		TK_press_cnt++;

		if(TK_press_cnt >= 50)//500ms
		{
			TK_press_cnt = 0;
			//TK_Key_Release_Flag = 1;

			RW_UpDate_Flag = 1;

			Read_Write_Flag = 0;

			TK_LongPress_CntFlag = 1;

			TK_Mode_Flag = 1;				

			TK_UpDate_Flag = 1;

			Mode_Value ++;

			if(Mode_Value > 2)
				Mode_Value = 0;
		}
	}
  	else
	{
		if(TK_press_cnt > 1 && TK_press_cnt < 50 && !TK_LongPress_CntFlag)
		{
			TK_UpDate_Flag = 1;

			RW_UpDate_Flag = 1;

			Read_Write_Flag = 0;

			level ++;

			if(level > 5)
				level = 0;

			level_temp = level;
		}

		//TK_Key_Release_Flag = 0;

		TK_press_cnt = 0;

		TK_LongPress_CntFlag = 0;
		//TK_Mode_Flag = 0;
	}
//-------------------------------------------
	if(T_Key3_Signal && !TK3_status)   //读写
	{
		TK3_status = 1;

		RW_UpDate_Flag = 1;

		if(Read_Write_Flag)
			Read_Write_Flag = 0;
		else 
			Read_Write_Flag = 1;

		Flash_AS_Flag = 0;
	}
  	else if(!T_Key3_Signal)
	{
		TK3_status = 0;
	}
//-------------------------------------------
	if(T_Key4_Signal && !TK4_status)   //番茄
	{
		TK4_status = 1;

		Tomato_UpDate_Flag = 1;

		if(Tomato_Switch_Flag)
			Tomato_Switch_Flag = 0;
		else
			Tomato_Switch_Flag = 1;
	}
  	else if(!T_Key4_Signal)
	{
		TK4_status = 0;
	}
	
}
//-------------------------------------------
void	IR_Key_Value()
{
	if(IR_Key_Press)
	{
		IR_Key_Press = 0;

		if(IR_Data == 0x00FF00FF)//开关
		{
			TK_Pow_UpDate_Flag = 1;

			if(Pow_Switch_Flag)
			{
				Pow_Switch_Flag = 0;	

				if(Read_Write_Flag)
				{
					Read_Write_Flag = 0;
					RW_UpDate_Flag = 1;	
				}

				if(Tomato_Switch_Flag)
				{
					Tomato_UpDate_Flag = 1;
					Tomato_Switch_Flag = 0;
				}		
			}
			else 
			{
				Pow_Switch_Flag = 1;

				//TK_Mode_Flag = 1;//开机打开PWM
			}
		}

		if(Pow_Switch_Flag)
		{
			if(IR_Data == 0x00FF40BF)//读写
			{
				RW_UpDate_Flag = 1;

				if(Read_Write_Flag)
					Read_Write_Flag = 0;
				else 
					Read_Write_Flag = 1;

				Flash_AS_Flag = 0;
			}
			else if(IR_Data == 0x00FF20DF)//白
			{
				RW_UpDate_Flag = 1;

				Read_Write_Flag = 0;

				TK_UpDate_Flag = 1;

				Mode_Value = 2;
			}
			else if(IR_Data == 0x00FFA05F)//黄
			{
				RW_UpDate_Flag = 1;

				Read_Write_Flag = 0;

				TK_UpDate_Flag = 1;

				Mode_Value = 1;
			}
			else if(IR_Data == 0x00FF609F)//白黄
			{
				RW_UpDate_Flag = 1;

				Read_Write_Flag = 0;

				TK_UpDate_Flag = 1;

				Mode_Value = 0;
			}
			else if(IR_Data == 0x00FF10EF)//加档
			{
				TK_UpDate_Flag = 1;

				RW_UpDate_Flag = 1;

				Read_Write_Flag = 0;

				if(level != 5)
					level ++;

				level_temp = level;
			}
			else if(IR_Data == 0x00FF50AF)//减档
			{
				TK_UpDate_Flag = 1;

				RW_UpDate_Flag = 1;

				Read_Write_Flag = 0;

				if(level != 0)
					level --;

				level_temp = level;
			}
			else if(IR_Data == 0x00FFA857)//定时
			{
				Tomato_UpDate_Flag = 1;

				if(Tomato_Switch_Flag)
					Tomato_Switch_Flag = 0;
				else
					Tomato_Switch_Flag = 1;
			}
		}
		
		//IR_Data = 0;
	}
}



void	IR_Receive(void)
{
	switch(IR_Mode)
	{
		case 0://初始等待起始码到来
			if(!IR)
			{
				IR_Mode = 1;
				IR_Sign = 1;
			}
			else
			{
				IR_Mode = 0;				
			}
			Time_20ms = 0;
			Time1_100us = 0;
			break;
		case 1://判断起始码是否成立
			if(IR_Sign)
			{
				if(IR)//等待高电平出现准备进入低电平检测
				{
					IR_Sign = 0;
				}
			}
			else
			{
				if(!IR)
				{
					if(Time1_100us >= 120 && Time1_100us <= 140)//判断起始码的时间是否在(9ms+4.5ms)左右
					{
						IR_Mode = 2;//起始码正确，进入下个模式
						IR_Sign = 1;
						Long_Sign = 1;
						icnt = 0;
						Time_20ms = 0;
						Time1_100us = 0;
						i = 0;
					}
					elseif(Time1_100us >= 100 && Time1_100us < 120)//判断起始码的时间是否在(9ms+2.25ms)左右
					{
						IR_Mode = 3;
						icnt++;//重复码出现次数
						if(icnt >= 4 && Long_Sign)
						{
							Long_Sign = 0;
							IR_Mode = 0;
							//.printf("长按\n")

							IR_Key_Long_Press = 1;
						}
						Time_20ms = 0;
						Time1_100us = 0;
					}
					else
					{
						IR_Mode = 0;//起始码错误，重新判断起始码

						//IR_Key_Press = 0;					
					}

				}
			}
			break;
		case 2://判断数据码0或1，并记录
			if(IR_Sign)
			{
				if(IR)//等待高电平出现准备进入低电平检测
				{
					IR_Sign = 0;
				}

				Time5_100us = 0;//未进入高电平前持续清零
			}
			else
			{
				if(!IR)
				{
					if(Time1_100us >= 15)//判断数据码是1
					{
						IR_Mode = 2;
						IR_Sign = 1;
						data <<= 1;	
						data = data | 0x00000001;	
						//data >>= 1;	
						//data = data | 0x80000000;
						Time_20ms = 0;
						Time1_100us = 0;
					}
					else//判断数据码是0
					{
						IR_Mode = 2;
						IR_Sign = 1;
						data <<= 1;
						data = data & 0xfffffffe;
						//data >>= 1;
						//data = data & 0x7fffffff;
						Time_20ms = 0;
						Time1_100us = 0;
					}
					i++;
					if(i==32)//数据全部接受完毕，进入下一个模式
					{
						IR_Mode = 3;
					}
				}
				else
				{
					if(Receive_Over_Flag)//码值发送完毕开始高电平计数
					{
						if(Time5_100us >= 980)//98ms即判断松开长按
						{
							Time5_100us = 0;

							Receive_Over_Flag = 0;

							IR_Key_Long_Press = 0;
						}
					}
				}
			}
			break;
		case 3:
			if(data)//短按操作
			{
				/*IR_Data$0 = data$3;
				IR_Data$1 = data$2;
				IR_Data$2 = data$1;
				IR_Data$3 = data$0;*/	

				IR_Data = data;
				//.printf("%.8X\n",IR_Data);
				data = 0;

				IR_Key_Press = 1;
			}
			if(IR)//等待恢复高电平后回到起始码验证
			{
				IR_Mode = 0;

				Receive_Over_Flag = 1;
			}
			break;
		}
}

//-------------------------------------------

void Sleep_mode()
{

	if(SleepCnt && T16_10ms_Flag_Sleep)
	{
		T16_10ms_Flag_Sleep = 0;
		SleepCnt --;
	}

	if(Pow_Switch_Flag)
	{
		SleepCnt = 200;
	}

	if(!SleepCnt)
	{

		$ MISC Fast_Wake_Up;

		Reload_T16 = 32768 - Const_Sleep_WakeUp;  //
		STT16	Reload_T16;

		$ T16M	ILRC,/1,BIT15;

		INTRQ.T16 = 0;

		//eoscr = 0x01; // 关LVR，减少电流

		//$ CLKMD	 ILRC/1, En_IHRC, En_ILRC, EN_Watchdog;
		$ CLKMD	 ILRC/1, En_IHRC, En_ILRC;
		//CLKMD.EN_Watchdog	=	0;
		CLKMD.En_IHRC	=	0;

		stopexe;

		if(!IR)
			SleepCnt = 200;

		//$ CLKMD	IHRC/SysClock_DIV, En_IHRC, En_ILRC, EN_Watchdog;
		$ CLKMD	IHRC/SysClock_DIV, En_IHRC, En_ILRC;

		//eoscr = 0x00; // 开LVR

		Timer16_Init(); //100us  //切换定时唤醒时间

		T16_10ms_Flag_TK = 1;

	//	IR_Receive();
	}

}

void TK_Init()
{
//	TS   = 0b_0011_00_11; 	// 触摸扫描IHRC/8=2MHz, 0.5*VCC, 128*CLK
	$ TS IHRC/4, TP_05, CLK_128;
	TKE1 = 0b_0000_000_0;
	TKE2 = 0b_0000_000_0;

//	TPS2 = 0x01; // CS接VDD时才开启
	$	TPS2	Type_B,Always_On;
}

byte uart_send_c = 0;
void Uart_Send_One_Byte(void) // 38400
{
		$ PB.5 out, low;
	//	PA.5 = 0;			//起始位		
		.delay ONE_BIT_DELAY_SYSCLK_CNT//42us

		byte bit_cnt = 0;
		while(bit_cnt < 8)		//8个数据位，先发低位再发高位
		{					
			SR uart_send_c; 	//右移一位

			.swapc_o PB.5; 		//进位制C赋给IO端口

			bit_cnt++;

			.delay ONE_BIT_DELAY_SYSCLK_CNT
		}

		PB.5 = 1;			//停止位
		.delay ONE_BIT_DELAY_SYSCLK_CNT

		$ PB.5 in;
}


void Uart_Send_Data(void) // 2M  38400
{

//	uart_send_c = IR_Key_Long_Press $ 0;
//	Uart_Send_One_Byte();
//	uart_send_c = IR_Key_Long_Press	$ 1;
//	Uart_Send_One_Byte();

//	uart_send_c = u16_TK2_environment_val $ 0;
//	Uart_Send_One_Byte();
//	uart_send_c = u16_TK2_environment_val $ 1;
//	Uart_Send_One_Byte();
	
}

void IO_Init()
{
	PA		=	0b0000_0000;
	PAC		=	0b0000_0000;
	PAPH	=	0b0000_0000;

	PB		=	0b0000_0000;
	PBC		=	0b0000_0000;
	PBPH	=	0b0000_0000;

	PADIER	=	0b0000_0000;
	PBDIER	=	0b0100_0000;

	$ PA.0 in;
	$ PA.4 in;
	$ PA.3 in;
	$ PB.3 in;

	$ SW_LED out,high;
	$ RW_LED out,high;
	$ TM_LED out,high;

	$ IR in,pull;
}



void FPPA0()
{
	.ADJUST_IC	SYSCLK = IHRC/SysClock_DIV, IHRC=16MHz, VDD=4.0V,Init_RAM;	// SysClock_DIV=8   2MHz
																
	IO_Init();

	.delay 60*2000; // 上电延时60ms等待电源稳定
//.delay 1000;//500us
	Pre_T_Key1_Release = 1;
	Pre_T_Key2_Release = 1;
	Pre_T_Key3_Release = 1;
	Pre_T_Key4_Release = 1;

	Timer16_Init();	//T16 定时器 1ms

	TK_Init();

	PWM2_Init();
	PWM3_Init();

	IR_Mode = 0;

//	Wdreset; 				//	WatchDog Reset
//	Clkmd.En_WatchDog = 1;	// WatchDog Enable
//	$ MISC Fast_Wake_Up,WDT_256K;		//看门狗时钟超时时间设定
	$ MISC Fast_Wake_Up;

	while(1)
	{		
		if(T16_10ms_Flag_TK)
		{
			T16_10ms_Flag_TK = 0;

			TK1_Scan();
			if(Pow_Switch_Flag)
			{
				TK2_Scan();
				TK3_Scan();
				TK4_Scan();
			}

			IR_Key_Value();
			Touch_function();				
		}

		Light_Control();
		Pow_off_on();			
		RW_function();
		Tomato_Timer();

		//Uart_Send_Data();

		Sleep_mode();		
//		Wdreset; //	WatchDog Reset
		
	}
}

//----------------------------------------------
void Interrupt()
{
	pushaf;
	//----------------------------------------------
	if(Intrq.T16)
	{	//T16 Trig 周期：100us
		STT16	Reload_T16;
		Intrq.T16 = 0;

		if(Receive_Over_Flag)
			Time5_100us++;

		Time1_100us++;
		if(Time1_100us >= 200)
		{			
			Time1_100us = 0;
			Time_20ms++;
			if(Time_20ms >= 10)
			{
				Time_20ms = 0;
			}
		}

		Time2_100us ++;	

		if(Time2_100us >= 100)
		{
			Time2_100us = 0;
			T16_10ms_Flag_TK = 1;
			T16_10ms_Flag_Sleep = 1;
		}

		Time4_100us ++;	
		if(Time4_100us >= 40)//4ms
		{
			Time4_100us = 0;
			Duty_PM_Flag = 1;
		}

		if(Tomato_Switch_Flag)
		{
			Time3_100us ++;

			if(Time3_100us >= 10000)//1s
			{
				Time3_100us = 0;

				Timer_1s_Cnt ++;
				if(Timer_1s_Cnt >= 1500)//25mins
				{
					Timer_1s_Cnt = 0;

					Tomato_Flash_Flag = 1;
				}
			}
		}

		if(Tomato_Flash_Flag)
		{
			Tomato_Flash();
		}

		IR_Receive();
	}

	//----------------------------------------------
	popaf;
}
//----------------------------------------------