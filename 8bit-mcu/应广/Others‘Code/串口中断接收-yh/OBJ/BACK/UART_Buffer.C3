#include	"extern.h"

byte	bit_cnt = 0;
//byte	bit_step = 0;
byte	Byte_Cnt = 0;

byte	uart_data1 = 0;
byte	uart_data2 = 0;
byte	uart_data3 = 0;
byte	uart_check = 0;

#define	uart_rx			PA.5
#define LED_Data 		PA.3
#define	TK_State_Out	PA.4

eword	RGB;
byte	Check_Sum;
#define	G_num 	RGB$2
#define	R_num 	RGB$1
#define	B_num 	RGB$0

bit	STATE_WAITE;
bit	STATE_START;
bit	STATE_STOP;
bit	STATE_TRANFER;

bit	ERR_WAITE_HIGH_SIGN;

word	T16_250ms_HighSign_Cnt = 0;

#define MPIXEL		12

bit		T16_5ms_Flag;
byte	T16_100us_Cnt = 0;
//-------------------------------------------------
word u16_get_val;		//读取值
word u16_Press_val;     //按下
word u16_release_val;	//松开

bit TK1_Release_Flag;

word u16_TK1_environment_val = 0;

eword u16_TK1_environment_val_Sum = 0;

word u16_release_val_TK1 = 0;

word u16_get_val_Temp_TK1 = 0;

byte FilterCnt_TK1 = 0;

byte TK1_Filter_Cnt = 0;

byte TK1_Release_Cnt = 0;

word u16_temp_val = 0;
word u16_Press_val_Sleep = 0;

byte Pre_T_Key_Release = 0xFF;
bit Pre_T_Key1_Release : Pre_T_Key_Release.1;

bit T_Key_Signal;

word SleepCnt = 2000;  //睡眠计数
byte Sleep_Mode_Flag = 0;
word RestCnt = 0;	//复位计数

byte TK_Press_Flag = 0; //触摸按下标志位 1 2 3 4

byte Const_Env_Dw_Fix_Speed = 3; // 按下环境值修正速率

#define FilterCnt_Value    9 // 60ms
#define Release_Cnt_Value  4  // 18ms

#define  Const_SEN_TK1   35

#define Const_SEN_TK1_Release  40

//-------------------------------------------------

word   Reload_T16;
void   Timer16_Init(void)//100us
{
	Reload_T16 = 32768 - 1600;
	stt16 Reload_T16;
	$ T16M IHRC,/1,bit15;
	$ INTEGS BIT_R;
	INTRQ.T16 = 0;
	INTEN.T16 = 1;
	ENGINT;

}

void   Timer2_Init(void)//104us
{
	tm2ct = 0;
	tm2b = 1;
	$ TM2C IHRC,Disable,Period;
	$ TM2S 8bit,/64,/13;
	INTRQ.TM2 = 0;
	INTEN.TM2 = 0;
	//ENGINT;
}


void	IO_Init(void)
{
	$ uart_rx in,ph;
	PADIER = 0B0010_0000;

	$ LED_Data Out,Low;

	$ TK_State_Out out,high;

	$ PB.0 out,low;
}
//-------------------------------------------------
Send_1	MACRO //数据1
{
	SET1 LED_Data;
	.delay 5;
	SET0 LED_Data;
	//.delay 3;
}
ENDM
Send_0	MACRO //数据0
{
	SET1 LED_Data;
	.delay 2;
	SET0 LED_Data;
	.delay 2;
}
ENDM
//-------------------------------------------------

void Send_RGB(void) //LED显示
{
	DISGINT; // 关闭中断
	.FOR bits, <23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0> //24Bit数据发送
		if(RGB.bits == 0)
			Send_0;
		else 
			Send_1;
	.ENDM

	ENGINT; // 开启中断

}
//-------------------------------------------------

byte Pixels;
void LED_Clear(void) //LED全灭
{
	RGB = 0x000000;
	Pixels = MPIXEL;
	while(Pixels--)
		Send_RGB();

	.delay 8*300;
}

void LED_RGB_24bit(void) //LED
{
	Pixels = MPIXEL;

	while(Pixels--)
	{
		Send_RGB();
	}
}

//-------------------------------------------------

#define	Uart_TX		PB.0
byte uart_send_c = 0;
void Uart_Send_One_Byte(void) // 38400
{
		$ Uart_TX out, low;
	//	PA.5 = 0;			//起始位		
		.delay ONE_BIT_DELAY_SYSCLK_CNT//42us

		byte bit_cnt_1 = 0;
		while(bit_cnt_1 < 8)		//8个数据位，先发低位再发高位
		{					
			SR uart_send_c; 	//右移一位

			.swapc_o Uart_TX; 		//进位制C赋给IO端口

			bit_cnt_1++;

			.delay ONE_BIT_DELAY_SYSCLK_CNT
		}

		Uart_TX = 1;			//停止位
		.delay ONE_BIT_DELAY_SYSCLK_CNT

		$ Uart_TX in;
}


void Uart_Send_Data(void) // 2M  38400
{
	uart_send_c = RGB $ 2;
	Uart_Send_One_Byte();
	uart_send_c = RGB $ 1;
	Uart_Send_One_Byte();
	uart_send_c = RGB $ 0;
	Uart_Send_One_Byte();

	uart_send_c = uart_check;
	Uart_Send_One_Byte();
}



/*void	Uart_Recive_Data(byte *data1,byte *data2,byte *data3,byte *data4)
{
	switch(Byte_Cnt)
	{
	case 1:
		if(STATE_START)
		{
			STATE_TRANFER = 1;

			if(bit_cnt < 8)
			{
				*data1 >>= 1;

				if(uart_rx == 0)
				{				
					*data1 &= 0x7f;
				}
				else
				{
					*data1 |= 0x80;
				}

				bit_cnt++;
			}			
		}
		break;
	case 2:
		if(STATE_START)
		{
			STATE_TRANFER = 1;

			if(bit_cnt < 8)
			{
				*data2 >>= 1;

				if(uart_rx == 0)
				{				
					*data2 &= 0x7f;
				}
				else
				{
					*data2 |= 0x80;
				}

				bit_cnt++;
			}			
		}
		break;
	case 3:
		if(STATE_START)
		{
			STATE_TRANFER = 1;

			if(bit_cnt < 8)
			{
				*data3 >>= 1;

				if(uart_rx == 0)
				{				
					*data3 &= 0x7f;
				}
				else
				{
					*data3 |= 0x80;
				}

				bit_cnt++;
			}			
		}
		break;
	case 4:
		if(STATE_START)
		{
			STATE_TRANFER = 1;

			if(bit_cnt < 8)
			{
				*data4 >>= 1;

				if(uart_rx == 0)
				{				
					*data4 &= 0x7f;
				}
				else
				{
					*data4 |= 0x80;
				}

				bit_cnt++;
			}			
		}
		break;
	}

	if(bit_cnt >= 8)
	{
		bit_cnt = 0;

		STATE_STOP = 1;
		STATE_START = 0;
	}
}*/

void	Uart_Recive_Data()
{
	if(PB.0 == 0)
		PB.0 = 1;
	ELSE
		PB.0 = 0;

	switch(Byte_Cnt)
	{
	case 1:
		if(STATE_START)
		{
			//STATE_TRANFER = 1;

			if(bit_cnt < 8)
			{
				uart_data1 >>= 1;

				if(uart_rx == 0)
				{				
					uart_data1 &= 0x7f;
				}
				else
				{
					uart_data1 |= 0x80;
				}

				bit_cnt++;
			}			
		}
		break;
	case 2:
		if(STATE_START)
		{
			//STATE_TRANFER = 1;

			if(bit_cnt < 8)
			{
				uart_data2 >>= 1;

				if(uart_rx == 0)
				{				
					uart_data2 &= 0x7f;
				}
				else
				{
					uart_data2 |= 0x80;
				}

				bit_cnt++;
			}			
		}
		break;
	case 3:
		if(STATE_START)
		{
			//STATE_TRANFER = 1;

			if(bit_cnt < 8)
			{
				uart_data3 >>= 1;

				if(uart_rx == 0)
				{			
					uart_data3 &= 0x7f;
				}
				else
				{
					uart_data3 |= 0x80;
				}

				bit_cnt++;
			}			
		}
		break;
	case 4:
		if(STATE_START)
		{
		//	STATE_TRANFER = 1;

			if(bit_cnt < 8)
			{
				uart_check >>= 1;

				if(uart_rx == 0)
				{				
					uart_check &= 0x7f;
				}
				else
				{
					uart_check |= 0x80;
				}

				bit_cnt++;
			}			
		}
		break;
	}

	if(bit_cnt >= 8)
	{
		bit_cnt = 0;

		STATE_STOP = 1;
		STATE_START = 0;

		STATE_TRANFER = 0;
	}
}

void	Uart_Recive_Handle(void)
{
	if(bit_cnt == 0 && uart_rx == 1)
	{
		if(ERR_WAITE_HIGH_SIGN == 0)
			STATE_WAITE = 1;
	}

	if(!STATE_START && STATE_WAITE)
	{
		if(uart_rx == 0)
		{
			STATE_WAITE = 0;

			Byte_Cnt ++;
			STATE_START = 1;
			STATE_STOP = 0;
			
			.delay 8*52;

			bit_cnt = 0;

			tm2ct = 0;
			INTRQ.TM2 = 0;
			INTEN.TM2 = 1;	

			STATE_TRANFER = 1;
		}
	}

	if(STATE_STOP)
	{		
		STATE_STOP = 0;
		//STATE_TRANFER = 0;

		tm2ct = 0;
		INTRQ.TM2 = 0;
		INTEN.TM2 = 0;
		
		STATE_START = 0;

		if(Byte_Cnt == 4)
		{		
			Byte_Cnt = 0;

			R_num = uart_data1;
			G_num = uart_data2;
			B_num = uart_data3;

			Check_Sum = 0;

			Check_Sum = uart_data1 + uart_data2 + uart_data3;

			if(Check_Sum == uart_check)
			{
				LED_RGB_24bit();
				//.printf("%x%x\n",RGB,uart_check);

				//Uart_Send_Data();
			}
			else
			{
				bit_cnt = 0;

				STATE_WAITE = 0;
				STATE_START = 0;
				//STATE_TRANFER = 0;
				STATE_STOP = 0;

				ERR_WAITE_HIGH_SIGN = 1;
			}

			Uart_Send_Data();

			uart_data1 = 0;
			uart_data2 = 0;
			uart_data3 = 0;
			uart_check = 0;
		}
	}
}


void TK_Init(void)
{
	TS   = 0b_0011_00_11; 	// IHRC/8, 0.5*VCC, 128*CLK
	TKE1 = 0b_0000_000_0;
	TKE2 = 0b_0000_000_0;

//	TPS2 = 0x01; // CS 接VDD

}

void TK1_Release_(void)
{
	TK1_Filter_Cnt = 0;

	T_Key_Signal = 0;
	Pre_T_Key1_Release = 1;
	u16_TK1_environment_val_Sum = 0;
	u16_TK1_environment_val = u16_get_val_Temp_TK1;

	TK_Press_Flag = 0; //触摸按下标志位清0

	TK1_Release_Flag = 1;
}

void	Long_Press_Reset(void)
{
	if(T_Key_Signal)
	{
		RestCnt++;
		if(RestCnt >= 3200)//16s
		{
			RestCnt = 0;

			TK1_Release_();
		}
	}
	else
	{
		RestCnt = 0;
	}
}

void Get_TK_Value(void)
{
	$ TCC TK_RUN;
	while(A != 0x00) 
	{
		A = TCC & 0x70;
	}
	u16_get_val =  (TKCH << 8) | TKCL;
}

void TK1_Scan_(void)
{	
	$ TKE PA.6;

	Get_TK_Value();

	u16_Press_val_Sleep = u16_get_val + Const_SEN_TK1;
	if(u16_Press_val_Sleep < u16_TK1_environment_val)
	{
		SleepCnt = 2000;
		Sleep_Mode_Flag = 0;
	}

	u16_temp_val = u16_get_val_Temp_TK1 << 2;
	u16_temp_val -= u16_get_val_Temp_TK1;
	u16_temp_val += u16_get_val;
	u16_get_val_Temp_TK1 = u16_temp_val >> 2;

	u16_get_val = u16_get_val_Temp_TK1;

	//if(TK_Press_Flag == 0 || TK_Press_Flag == 1)
	//{

	if(Pre_T_Key1_Release) 
	{
		u16_Press_val = u16_get_val + Const_SEN_TK1;
		
		if(u16_Press_val < u16_TK1_environment_val)	 //按下
		{
			SleepCnt = 2000;

			FilterCnt_TK1 ++;
			if(FilterCnt_TK1 > FilterCnt_Value)
			{
				//TK_Press_Flag = 1; //触摸按下标志位置1

		//		TK_Value = 0x01;   //按键值
		//		Sleep_Mode_Flag = 0;

				T_Key_Signal = 1;
				Pre_T_Key1_Release = 0;
				u16_release_val_TK1 = u16_TK1_environment_val - Const_SEN_TK1; //
			}
		}
		else //更新环境值
		{
			FilterCnt_TK1 = 0;
			if(SleepCnt)
			{
				TK1_Filter_Cnt ++;
				u16_TK1_environment_val_Sum += u16_get_val;

				if(TK1_Filter_Cnt > 31)
				{
					TK1_Filter_Cnt = 0;
					u16_TK1_environment_val = u16_TK1_environment_val_Sum >> 5;
					u16_TK1_environment_val_Sum = 0;

					if(TK1_Release_Flag)
					{
						TK1_Release_Flag = 0;
						u16_TK1_environment_val = u16_get_val;
					}
				}
			}
			else
			{
				u16_TK1_environment_val = u16_get_val;
				u16_TK1_environment_val_Sum = 0;
				TK1_Filter_Cnt = 0;
			}
			
			if(TK1_Release_Flag)
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
		FilterCnt_TK1 = 0;

		TK1_Filter_Cnt ++;

		if(TK1_Filter_Cnt >= Const_Env_Dw_Fix_Speed)
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

		if(u16_get_val > u16_release_val_TK1 || u16_release_val > Const_SEN_TK1_Release)	//松开
		{
			TK1_Release_Cnt ++;
			if(TK1_Release_Cnt >= Release_Cnt_Value) //触摸松开滤波
			{
				TK1_Release_Cnt = 0;

				TK1_Release_();

			}
		}
		else
		{
			TK1_Release_Cnt = 0;
		}	
    }	
	//}
}

void	TK1_Func()
{
	if(T_Key_Signal)
	{
		$ TK_State_Out out,low;
	}
	else
	{
		$ TK_State_Out out,high;
	}
}

void	FPPA0 (void)
{
	.ADJUST_IC	SYSCLK=IHRC/2, IHRC=16MHz, VDD=5V, Init_RAM;

	Wdreset; //	WatchDog Reset
	Clkmd.En_WatchDog = 1;		// WatchDog Enable
	$ MISC WDT_8K;			//看门狗时钟超时时间设定

	IO_Init();

	.delay 8*6000;

	Timer16_Init();

	Timer2_Init();

	TK_Init();

	LED_Clear();
	
	while (1)
	{
		if(STATE_TRANFER == 0)
			Uart_Recive_Handle();
		
		if(T16_5ms_Flag)
		{
			T16_5ms_Flag = 0;

			TK1_Scan_();

			TK1_Func();

			Long_Press_Reset();
		}

		Wdreset; //	WatchDog Reset
	}
}

void	Interrupt (void)
{
	pushaf;

	if((INTEN.T16) && (INTRQ.T16))
	{	
		stt16	Reload_T16;
		Intrq.T16	=	0;

		T16_100us_Cnt++;
		if(T16_100us_Cnt >= 50)
		{
			T16_100us_Cnt = 0;

			T16_5ms_Flag = 1;			
		}

		if(ERR_WAITE_HIGH_SIGN == 1)
		{
			if(uart_rx)
			{
				T16_250ms_HighSign_Cnt++;

				if(T16_250ms_HighSign_Cnt >= 2500)
				{
					T16_250ms_HighSign_Cnt = 0;

					ERR_WAITE_HIGH_SIGN = 0;

					bit_cnt = 0;
				}
			}
			else
			{
				T16_250ms_HighSign_Cnt = 0;
			}
		}
	}


	if(Intrq.TM2 && Inten.TM2)
	{
		Intrq.TM2 = 0;		

		//Uart_Recive_Data(&uart_data1,&uart_data2,&uart_data3,&uart_check);//R,G,B
		Uart_Recive_Data();
	}

	popaf;
}