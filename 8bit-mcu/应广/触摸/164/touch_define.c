#include	"MACRO.C"

//更改宏定义按键个数 1-11
//更改Const_SEN_T_Keyx按键灵敏度
//更改Touch_x按键pin
//
//	Touch_Init()		初始化函数
//	Touch_Func()		调用函数，信号为Tk_Signal0~A

#define Touch_sum 11 //按键个数
#if Touch_sum == 0 || Touch_sum > 11
.error Touch_sum  donot set0 or set more then11
#endif
//#define	Touch_SEN_T = 35

#if Touch_sum >=1
	#define Touch_1 TK4
#endif
#if Touch_sum >=2
	#define Touch_2 TK1
#endif
#if Touch_sum >=3
	#define Touch_3	TK0
#endif
#if Touch_sum >=4
	#define Touch_4	TK5
#endif
#if Touch_sum >=5
	#define Touch_5 TK6
#endif
#if Touch_sum >=6
	#define Touch_6 TK7
#endif
#if Touch_sum >=7
	#define Touch_7	TK8
#endif
#if Touch_sum >=8
	#define Touch_8	TK9
#endif
#if Touch_sum >=9
	#define Touch_9 TK10
#endif
#if Touch_sum >=10
	#define Touch_10 TK11
#endif
#if Touch_sum >=11
	#define Touch_11 TK12
#endif

extern byte	sleep;
extern word sleep_Cnt;
Count   EQU    Touch_sum

Const_Env_Fix_Cnt => 4
Const_Fliter_cnt  => 3

#if Touch_sum >=1
	Const_SEN_T_Key0 => 20
#endif
#if Touch_sum >=2
	Const_SEN_T_Key1 => 35
#endif
#if Touch_sum >=3
	Const_SEN_T_Key2 => 35
#endif
#if Touch_sum >=4
	Const_SEN_T_Key3 => 35
#endif
#if Touch_sum >=5
	Const_SEN_T_Key4 => 35
#endif
#if Touch_sum >=6
	Const_SEN_T_Key5 => 35
#endif
#if Touch_sum >=7
	Const_SEN_T_Key6 => 35
#endif
#if Touch_sum >=8
	Const_SEN_T_Key7 => 35
#endif
#if Touch_sum >=9
	Const_SEN_T_Key8 => 35
#endif
#if Touch_sum >=10
	Const_SEN_T_Key9 => 35
#endif
#if Touch_sum >=11
	Const_SEN_T_KeyA => 35
#endif


#ifdef Touch_sum
#if Touch_sum >=1
#define TK0Environment TKEnvironment[0]
#define	TK0ProcessEvironment TKProcessEvironment[0]
#endif
#if Touch_sum >=2
#define TK1Environment TKEnvironment[1]
#define	TK1ProcessEvironment TKProcessEvironment[1]
#endif
#if Touch_sum >=3
#define TK2Environment TKEnvironment[2]
#define	TK2ProcessEvironment TKProcessEvironment[2]
#endif
#if Touch_sum >=4
#define TK3Environment TKEnvironment[3]
#define	TK3ProcessEvironment TKProcessEvironment[3]
#endif

#if Touch_sum >=5
#define TK4Environment TKEnvironment[4]
#define	TK4ProcessEvironment TKProcessEvironment[4]
#endif
#if Touch_sum >=6
#define TK5Environment TKEnvironment[5]
#define	TK5ProcessEvironment TKProcessEvironment[5]
#endif
#if Touch_sum >=7
#define TK6Environment TKEnvironment[6]
#define	TK6ProcessEvironment TKProcessEvironment[6]
#endif
#if Touch_sum >=8
#define TK7Environment TKEnvironment[7]
#define	TK7ProcessEvironment TKProcessEvironment[7]
#endif
#if Touch_sum >=9
#define TK8Environment TKEnvironment[8]
#define	TK8ProcessEvironment TKProcessEvironment[8]
#endif
#if Touch_sum >=10
#define TK9Environment TKEnvironment[9]
#define	TK9ProcessEvironment TKProcessEvironment[9]
#endif
#if Touch_sum >=11
#define TK10Environment TKEnvironment[10]
#define	TK10ProcessEvironment TKProcessEvironment[10]
#define TKAEnvironment TKEnvironment[10]
#define	TKAProcessEvironment TKProcessEvironment[10]
#endif

#endif // Touch_sum

word TKEnvironment[Touch_sum] = { 0 };
word TKProcessEvironment[Touch_sum] = { 0 };

word u16_TK_val = 0, u16_temp_val = 0;

//word TK1Value = 0;
#if Touch_sum <=8
	byte	Pre_T_Key_Release = 0;
	byte	T_Key_Signal1 = 0;
#else
	word	Pre_T_Key_Release = 0;
	word	T_Key_Signal1 = 0;
#endif

#if Touch_sum >=1
	bit Tk_Signal0 : T_Key_Signal1.0
	bit	Pre_T_Key_Release0 : Pre_T_Key_Release.0
#endif
#if Touch_sum >=2
	bit Tk_Signal1 : T_Key_Signal1.1
	bit	Pre_T_Key_Release1 : Pre_T_Key_Release.1
#endif
#if Touch_sum >=3
	bit Tk_Signal2 : T_Key_Signal1.2
	bit	Pre_T_Key_Release2 : Pre_T_Key_Release.2
#endif
#if Touch_sum >=4
	bit Tk_Signal3 : T_Key_Signal1.3
	bit	Pre_T_Key_Release3 : Pre_T_Key_Release.3
#endif
#if Touch_sum >=5
	bit Tk_Signal4 : T_Key_Signal1.4
	bit	Pre_T_Key_Release4 : Pre_T_Key_Release.4
#endif
#if Touch_sum >=6
	bit Tk_Signal5 : T_Key_Signal1.5
	bit	Pre_T_Key_Release5 : Pre_T_Key_Release.5
#endif
#if Touch_sum >=7
	bit Tk_Signal6 : T_Key_Signal1.6
	bit	Pre_T_Key_Release6 : Pre_T_Key_Release.6
#endif
#if Touch_sum >=8
	bit Tk_Signal7 : T_Key_Signal1.7
	bit	Pre_T_Key_Release7 : Pre_T_Key_Release.7
#endif
#if Touch_sum >=9
	bit Tk_Signal8 : T_Key_Signal1.8
	bit	Pre_T_Key_Release8 : Pre_T_Key_Release.8
#endif
#if Touch_sum >=10
	bit Tk_Signal9 : T_Key_Signal1.9
	bit	Pre_T_Key_Release9 : Pre_T_Key_Release.9
#endif
#if Touch_sum >=11
	bit Tk_SignalA : T_Key_Signal1.10
	bit	Pre_T_Key_ReleaseA : Pre_T_Key_Release.10
#endif


.forc CC #Count
	byte	Fliter_cnt#CC;
	BYTE	Env_Fix_Cnt#CC;
	word	TK_Release_Value#CC;
	
.endm
/*
byte	Fliter_cnt0;
BYTE	Env_Fix_Cnt0;
word	TK_Release_Value0;
*/

void Touch_Init()
{
	byte cnt = 4;
#if Touch_sum >=1
	Pre_T_Key_Release.0 = 1;
#endif
#if Touch_sum >=2
	Pre_T_Key_Release.1 = 1;
#endif
#if Touch_sum >=3
	Pre_T_Key_Release.2 = 1;
#endif
#if Touch_sum >=4
	Pre_T_Key_Release.3 = 1;
#endif
#if Touch_sum >=5
	Pre_T_Key_Release.4 = 1;
#endif
#if Touch_sum >=6
	Pre_T_Key_Release.5 = 1;
#endif
#if Touch_sum >=7
	Pre_T_Key_Release.6 = 1;
#endif
#if Touch_sum >=8
	Pre_T_Key_Release.7 = 1;
#endif
#if Touch_sum >=9
	Pre_T_Key_Release.8 = 1;
#endif
#if Touch_sum >=10
	Pre_T_Key_Release.9 = 1;
#endif
#if Touch_sum >=11
	Pre_T_Key_Release.10 = 1;
#endif
	do
	{
#if Touch_sum >=1
		Touch_X Touch_1,TK_Math,0;
		TK0Environment = TK_Math;
#endif 
#if Touch_sum >=2
		Touch_X Touch_2,TK_Math,0;
		TK1Environment = TK_Math;
#endif
#if Touch_sum >=3
		Touch_X Touch_3,TK_Math,0;
		TK2Environment = TK_Math;
#endif
#if Touch_sum >= 4
		Touch_X Touch_4,TK_Math,0;
		TK3Environment = TK_Math;
#endif 
#if Touch_sum >=5
		Touch_X Touch_5,TK_Math,0;
		TK4Environment = TK_Math;
#endif 
#if Touch_sum >=6
		Touch_X Touch_6,TK_Math,0;
		TK5Environment = TK_Math;
#endif
#if Touch_sum >=7
		Touch_X Touch_7,TK_Math,0;
		TK6Environment = TK_Math;
#endif
#if Touch_sum >= 8
		Touch_X Touch_8,TK_Math,0;
		TK7Environment = TK_Math;
#endif 
#if Touch_sum >=9
		Touch_X Touch_9,TK_Math,0;
		TK8Environment = TK_Math;
#endif 
#if Touch_sum >=10
		Touch_X Touch_10,TK_Math,0;
		TK9Environment = TK_Math;
#endif
#if Touch_sum >=11
		Touch_X Touch_11,TK_Math,0;
		TK10Environment = TK_Math;
#endif 
	} while (--cnt);
	//	TK1ProcessEvironment=TK1Environment;
	//	TK2ProcessEvironment=TK2Environment ;
	//	TK3ProcessEvironment=TK3Environment;
	//	TK8ProcessEvironment=TK8Environment;
}


void Touch_Get_val()
{
#if Touch_sum >= 1
	Touch_X Touch_1, TK_Math, 0

	u16_TK_val = TK0Environment << 2;
	u16_TK_val -= TK0Environment;
	u16_TK_val += TK_Math;
	TK0Environment = (u16_TK_val >> 2);
#endif
#if Touch_sum >= 2
	Touch_X Touch_2, TK_Math, 0

	u16_TK_val = TK1Environment << 2;
	u16_TK_val -= TK1Environment;
	u16_TK_val += TK_Math;
	TK1Environment = (u16_TK_val >> 2);
#endif
#if Touch_sum >= 3
	Touch_X Touch_3, TK_Math, 0;

	u16_TK_val = TK2Environment << 2;
	u16_TK_val -= TK2Environment;
	u16_TK_val += TK_Math;
	TK2Environment = (u16_TK_val >> 2);
#endif
#if Touch_sum >= 4
	Touch_X Touch_4, TK_Math, 0;

	u16_TK_val = TK3Environment << 2;
	u16_TK_val -= TK3Environment;
	u16_TK_val += TK_Math;
	TK3Environment = (u16_TK_val >> 2);
#endif
#if Touch_sum >= 5
	Touch_X Touch_5, TK_Math, 0

	u16_TK_val = TK4Environment << 2;
	u16_TK_val -= TK4Environment;
	u16_TK_val += TK_Math;
	TK4Environment = (u16_TK_val >> 2);
#endif
#if Touch_sum >= 6
	Touch_X Touch_6, TK_Math, 0

	u16_TK_val = TK5Environment << 2;
	u16_TK_val -= TK5Environment;
	u16_TK_val += TK_Math;
	TK5Environment = (u16_TK_val >> 2);
#endif
#if Touch_sum >= 7
	Touch_X Touch_7, TK_Math, 0;

	u16_TK_val = TK6Environment << 2;
	u16_TK_val -= TK6Environment;
	u16_TK_val += TK_Math;
	TK6Environment = (u16_TK_val >> 2);
#endif
#if Touch_sum >= 8
	Touch_X Touch_8, TK_Math, 0;

	u16_TK_val = TK7Environment << 2;
	u16_TK_val -= TK7Environment;
	u16_TK_val += TK_Math;
	TK7Environment = (u16_TK_val >> 2);
#endif
#if Touch_sum >= 9
	Touch_X Touch_9, TK_Math, 0

	u16_TK_val = TK8Environment << 2;
	u16_TK_val -= TK8Environment;
	u16_TK_val += TK_Math;
	TK8Environment = (u16_TK_val >> 2);
#endif
#if Touch_sum >= 10
	Touch_X Touch_10, TK_Math, 0

	u16_TK_val = TK9Environment << 2;
	u16_TK_val -= TK9Environment;
	u16_TK_val += TK_Math;
	TK9Environment = (u16_TK_val >> 2);
#endif
#if Touch_sum >= 11
	Touch_X Touch_11, TK_Math, 0;

	u16_TK_val = TK10Environment << 2;
	u16_TK_val -= TK10Environment;
	u16_TK_val += TK_Math;
	TK10Environment = (u16_TK_val >> 2);
#endif
}
/*
void Get_vale(void)
{
	.forc CC #10
//	Touch_X Touch_#CC, TK_Math, 0

	u16_TK_val = TKEnvironment[CC] << 2;
	u16_TK_val -= TK1Environment;
	u16_TK_val += TK_Math;
	TK1Environment = (u16_TK_val >> 2);
	.endm
}
*/
void TKHandleproess()
{
	.forc CC #Count
		if (!Pre_T_Key_Release#CC)
		{
			if (TK#CC#Environment < TK#CC#ProcessEvironment)
			{
				Env_Fix_Cnt#CC++;
				if (Env_Fix_Cnt#CC >= Const_Env_Fix_Cnt)
				{
					Env_Fix_Cnt#CC = 0;
					TK#CC#ProcessEvironment--;
				}
			}
			else
			{
				Env_Fix_Cnt#CC = 0;
				TK#CC#ProcessEvironment = TK#CC#Environment;
			}
			u16_temp_val = TK#CC#Environment + Const_SEN_T_Key#CC;
			if (u16_temp_val < TK#CC#ProcessEvironment)
			{

				Fliter_cnt#CC++;
/*
				if (sleep)
				{
					Sleep = 0; Sleep_Cnt = 0;
					T_Key_Signal1.CC = 1;
					//	Tkey1 = 1;

					TK_Release_Value#CC = TKProcessEvironment[CC] - Const_SEN_T_Key#CC;
					//	LongKeyRestCount=0;
				//		TK1_res_cnt = 0;
					Pre_T_Key_Release.CC = 1;
				}
*/	
				//		SleepCnt=Const_Wakeup_Timing;
				/*		if(sleep)
						{
							if(Fliter_cnt#CC>=1)
							{
								Fliter_cnt#CC=0;
							//	Sleep_In = 0;
							T_Key_Signal1.CC=1;
						//	Tkey1 = 1;

							TK_Release_Value#CC=TKProcessEvironment[CC]-Const_SEN_T_Key#CC;
						//	LongKeyRestCount=0;
					//		TK1_res_cnt = 0;
							Pre_T_Key_Release.CC=1;
							}
						}*/
				if (Fliter_cnt#CC >= Const_Fliter_cnt)
				{
					Fliter_cnt#CC = 0;
					TK_signal#CC = 1;
					//	Tkey1 = 1;
					/*	#if TO#cc#_ACTIVE
								#if	TO#cc#_GPIO >= 2
								$ p_TO#cc#	High, Out;
								#else
								$ p_TO#cc#	In;
								#endif
						#else
								#if	TO#cc#_GPIO <= 2
								$ p_TO#cc#	Low, Out;
								#else
								$ p_TO#cc#	In;
								#endif
						#endif*/
					TK_Release_Value#CC = TK#CC#ProcessEvironment - Const_SEN_T_Key#CC;
					//					LongKeyRestCount=0;
					//					TK1_res_cnt = 0;
					Pre_T_Key_Release#CC = 1;
				}
			}
			else
			{
				TK_signal#CC = 0;
				Fliter_cnt#CC = 0;
			}
		}
		else
		{
			if (TK#CC#Environment > TK#CC#ProcessEvironment)
			{
				Env_Fix_Cnt#CC++;
				if (Env_Fix_Cnt#CC >= Const_Env_Fix_Cnt)
				{
					Env_Fix_Cnt#CC = 0;
					TK#CC#ProcessEvironment++;
				}
			}
			else
			{
				Env_Fix_Cnt#CC = 0;
				TK#CC#ProcessEvironment = TK#CC#Environment;
			}
			u16_temp_val = TK#CC#Environment - Const_SEN_T_Key#CC;
			if (TK#CC#Environment > TK_Release_Value#CC || u16_temp_val > TK#CC#ProcessEvironment)
			{
				Fliter_cnt#CC++;

				if (Fliter_cnt#CC >= Const_Fliter_cnt)
				{
					Fliter_cnt#CC = 0;
					//	Tkey1 = 0;
					/*	#if TO#cc#_ACTIVE
								#if	TO#cc#_GPIO <= 2
								$ p_TO#cc#	Low, Out;
								#else
								$ p_TO#cc#	In;
								#endif
						#else
								#if	TO#cc#_GPIO >= 2
								$ p_TO#cc#	High, Out;
								#else
								$ p_TO#cc#	In;
								#endif
						#endif*/
					TK_signal#CC = 0;
					Pre_T_Key_Release#CC = 0;
					//					SleepCnt=Const_Wakeup_Timing;
				}
			}
			else Fliter_cnt#CC = 0;
		}
	.endm
}

void Touch_Func(void)
{
	Touch_Get_val();
//	Get_vale();
	TKHandleproess();
/*	if(TK_signal1)
	{
		nop;
	}
	else
	{
		;
	}*/
}