
#include	"extern.h"
#include	"Touch.srt"
#define		PA7_Check	0
#define		DebugLog	1

#pragma no_chk io

#if (!_SYS(AT_ISP_ICE)) && PA7_Check
void Add_Run (void)
{//pa7/pa6 tie together test
	.wait1	PA.3;	// enter testing (P003 set PA3 high)
	MISC3	=	3;	// set PA7 & PA0 as IO pin
//	paph.7	=	1;	// set PA7 pull high
	pa.7 = 1;
	pac.7 = 1;
	.delay	2 * 160;
	.wait0	PA.3;	// exit testing (P003 set PA3 low)
//	paph.7	=	0;	// restore PA7 as normal
	pac.7 =0;
}
#endif

void	FPPA0 (void)
{
#if (!_SYS(AT_ISP_ICE)) && PA7_Check
	.ADJUST_IC	SYSCLK=IHRC/System_DIV, Init_RAM, BODY=INC, VDD=3.3V, Run=Add_Run:200us;
#else
	.ADJUST_IC	SYSCLK=IHRC/System_DIV, Init_RAM, BODY=INC, VDD=3.3V;
#endif
#if	(_SYS(AT_ISP_ICE)&&DebugLog)
	.DBG_CMD	FORM:WAVE	"S8:L16:Val0:L16:Bas0:L16:Val1:L16:Bas1:P8:State";
#endif

#if	_SYS(IO.defined.OPR)
#if _IOB(LOG) == _IOB(PA.0)
	$ OPR	PA0;
#else _IOB(LOG) == _IOB(PA.5)
	$ OPR	PA5;
#endif
#endif

#if EAR_ACTIVE
	#if	EAR_GPIO <= 2
		$ p_Ear		Low, Out;
	#endif
#else
	#if	EAR_GPIO >= 2
		$ p_Ear		High, Out;
	#endif
#endif
#if TOUCH_ACTIVE
	#if	TOUCH_GPIO <= 2
		$ p_Touch	Low, Out;
	#endif
#else
	#if	TOUCH_GPIO >= 2
		$ p_Touch	High, Out;
	#endif
#endif
#if	EAR_GPIO == 1
	$ p_Ear		Pull;
//#else
//	$ p_Ear		NoPull;
#endif
#if	TOUCH_GPIO == 1
	$ p_Touch	Pull;
//#else
//	$ p_Touch	NoPull;
#endif

#if _SYS(IO.defined.MISC.Fast_Wake_Up)
	$ MISC	WDT_64K, Fast_Wake_Up;
#else
	$ MISC	WDT_64K;
#endif
#if	!_SYS(AT_ISP_ICE)
	wdreset;
	CLKMD.EN_Watchdog	=	1;
#endif

	$ TM2S		8BIT, /16, /1;
	TM2B		=	104;
	$ TM3S		/1, /1;
	TM3B		=	0xFF;
	#if	_SYS(IO.defined.TM3C.En_NILRC)
		$ TM3C	NILRC, En_NILRC;
	#else
		$ TM3C	NILRC;
	#endif

	.forc	cc, # cnt_Touch_Pin
		$ p_Touch_#cc	In, Pull;
	.endm
	.Delay 100
	.forc	cc, # cnt_Touch_Pin
		if (p_Touch_#cc == 0)
			f_Key_Skip_#cc = 1;
		$ p_Touch_#cc	In, NoPull;
	.endm

	INTRQ	=	0;
#if _IOB(p_Touch) == _IOB(LOG)
#if !TOUCH_ACTIVE
	INTEN.0	=	1;
#endif
#elif _IOB(p_Ear) == _IOB(LOG)
#if !EAR_ACTIVE
	INTEN.0	=	1;
#endif
#endif
	INTEN.TM2	=	1;
#if _IOB(LOG) == _IOB(PA.0)
	$ PADIER	0x21;
#elif _IOB(LOG) == _IOB(PA.5)
	$ PADIER	0x20;
#endif
	engint;
	Initial_Touch ();
//	f_Key_Sleep	=	1;
//	f_Key_Skip_0 = 1;
	while (1)
	{
		wdreset;
		if (INTRQ.TM3)		// 20ms / 160ms
		{
			if (CalibrationILRC	==	0)
			{
				$ TM3S	/1, /1;
				T3val	=	0;
				TM3B	=	0xFF;
				TM3CT	=	0;
				.wait1	TM3CT.0;
				do
				{	//	每次判断间隔，需花 4 条指令 = 2 uS (SYSCLK = 2MHz)
					T3val$0++;
					if (! TM3CT.0)	break;
					T3val++;
				} while (TM3CT.0);
				// T16src2 / T16val = T16src * T16val + T16res
				T3cnt			=	0;
				T3res			=	0;
				T3src			=	2500;
				do
				{
					T3src	<<=		1;
					T3res	<<<=	1;
					T3cnt++;
					A	=	(T3res - T3val) >> 8;

					if (! CF)
					{
						T3res$1	=	A;
						T3res$0	-=	T3val$0;
						T3src.0	=	1;
					}
				} while (! T3cnt.4);
				if (f_Key_Sleep)
					$ TM3S	/16, /2;
				else
					$ TM3S	/4, /1;
				TM3B	=	T3src-1;
			}
			CalibrationILRC++;
			INTRQ.TM3	=	0;
			Scan_Touch ();

			if (f_Must_Work)
			{
				Key_Timeout = KEY_TIMEOUT_TIME;
				if (f_Key_Sleep)
				{
					f_Key_Sleep	=	0;
					$ TM3S	/4, /1;
				}
			}
			else if (Key_Timeout)
			{
				Key_Timeout--;
			}
			else if (!f_Key_Sleep)
			{
				f_Key_Sleep	=	1;
				$ TM3S	/16, /2;
			}

			if (Key_Count)
			{
				if (--Key_Count == 0)
				{
					if (f_Key_0 == 0)
					{
						f_Key_Change = 1;
					}
				}
			}
			if (f_Key_Change)	//  触摸状态改变
			{
				f_Key_Change = 0;
				/*
				if (f_Key_0)
				{
					f_Key_Touch = 1;
					Key_Count	= 3;
				}
				else if (Key_Count == 0)
				{
					f_Key_Touch = 0;
				}*/
				if (f_Key_1 ||f_Key_0)
				{
					f_Key_Ear = 1;
				}
				else
				{
					f_Key_Ear = 0;
				}
			}
			if (f_Key_Touch)
			{
				if (--Key_Reset == 0)
					Reset_Touch();
			}
			else
			{
				Key_Reset	=	1000;
			}

#if (_SYS(AT_ISP_ICE) && DebugLog)
			A	=	0x3B;				.DBG_CMD	SAVE_ALU;
			.forc	cc, # cnt_Touch_Pin
				A	=	TC_Now[cc]$0;	.DBG_CMD	SAVE_ALU;
				A	=	TC_Now[cc]$1;	.DBG_CMD	SAVE_ALU;
				A	=	TC_Base[cc]$0;	.DBG_CMD	SAVE_ALU;
				A	=	TC_Base[cc]$1;	.DBG_CMD	SAVE_ALU;
			.endm
			Key_Temp	=	Key_State<<4;
			if (f_Key_Ear)
				Key_Temp	|=	0x02;
			if (f_Key_Touch)
				Key_Temp	|=	0x01;
			A	=	Key_Temp;			.DBG_CMD	SAVE_ALU;
#endif

			if (f_UART_Mode)	// Log模式
			{
				if (Uart_Transmit)
				{
					Uart_Transmit--;
					Key_Temp	=	Key_State<<4;
					if (f_Key_Ear)
						Key_Temp	|=	0x02;
					if (f_Key_Touch)
						Key_Temp	|=	0x01;
					INTEN.0	=	0;
					$ UART_Out	Out;
					A	=	0x3B;				UART_Send();
					.forc	cc, # cnt_Touch_Pin
						A	=	TC_Now[cc]$0;	UART_Send();
						A	=	TC_Now[cc]$1;	UART_Send();
						A	=	TC_Base[cc]$0;	UART_Send();
						A	=	TC_Base[cc]$1;	UART_Send();
					.endm
					A	=	Key_Temp;			UART_Send();
					$ UART_Out	In;
					INTRQ.0	=	0;
					INTEN.0	=	1;
					if (Uart_Transmit == 0)
					{
						$ TM2C		IHRC;
					}
				}
			}
			else if (p_Power)
			{
				Reset_Touch();
#if EAR_ACTIVE
	#if _IOB(p_Ear) == _IOB(LOG)
				INTEN.0		=	0;
	#endif
	#if	EAR_GPIO <= 2
				$ p_Ear	Low, Out;
	#else
				$ p_Ear	In;
	#endif
#else
	#if	EAR_GPIO >= 2
				$ p_Ear	High, Out;
	#else
				$ p_Ear	In;
	#endif
	#if _IOB(p_Ear) == _IOB(LOG)
                if (!INTEN.0)
                {
                    if (UART_In)
                    {
                        INTRQ.0		=	0;
                        INTEN.0		=	1;
                    }
                }
	#endif
#endif
#if TOUCH_ACTIVE
	#if _IOB(p_Touch) == _IOB(LOG)
				INTEN.0		=	0;
	#endif
	#if	TOUCH_GPIO <= 2
				$ p_Touch	Low, Out;
	#else
				$ p_Touch	In;
	#endif
#else
	#if	TOUCH_GPIO >= 2
				$ p_Touch	High, Out;
	#else
				$ p_Touch	In;
	#endif
	#if _IOB(p_Touch) == _IOB(LOG)
                if (!INTEN.0)
                {
                    if (UART_In)
                    {
                        INTRQ.0		=	0;
                        INTEN.0		=	1;
                    }
                }
	#endif
#endif
			}
			else	// 直接输出模式
			{
				if (f_Key_Ear)
				{
#if EAR_ACTIVE
	#if	EAR_GPIO >= 2
					$ p_Ear	High, Out;
	#else
					$ p_Ear	In;
	#endif
	#if _IOB(p_Ear) == _IOB(LOG)
					if (!INTEN.0)
					{
						if (UART_In)
						{
							INTRQ.0		=	0;
							INTEN.0		=	1;
						}
					}
	#endif
#else
	#if _IOB(p_Ear) == _IOB(LOG)
					INTEN.0		=	0;
	#endif
	#if	EAR_GPIO <= 2
					$ p_Ear	Low, Out;
	#else
					$ p_Ear	In;
	#endif
#endif
				}
				else
				{
#if EAR_ACTIVE
	#if _IOB(p_Ear) == _IOB(LOG)
					INTEN.0		=	0;
	#endif
	#if	EAR_GPIO <= 2
					$ p_Ear	Low, Out;
	#else
					$ p_Ear	In;
	#endif
#else
	#if	EAR_GPIO >= 2
					$ p_Ear	High, Out;
	#else
					$ p_Ear	In;
	#endif
	#if _IOB(p_Ear) == _IOB(LOG)
					if (!INTEN.0)
					{
						if (UART_In)
						{
							INTRQ.0		=	0;
							INTEN.0		=	1;
						}
					}
	#endif
#endif
				}
				if (f_Key_Touch)
				{
#if TOUCH_ACTIVE
	#if	TOUCH_GPIO >= 2
					$ p_Touch	High, Out;
	#else
					$ p_Touch	In;
	#endif
	#if _IOB(p_Touch) == _IOB(LOG)
					if (!INTEN.0)
					{
						if (UART_In)
						{
							INTRQ.0		=	0;
							INTEN.0		=	1;
						}
					}
	#endif
#else
	#if _IOB(p_Touch) == _IOB(LOG)
					INTEN.0		=	0;
	#endif
	#if	TOUCH_GPIO <= 2
					$ p_Touch	Low, Out;
	#else
					$ p_Touch	In;
	#endif
#endif
				}
				else
				{
#if TOUCH_ACTIVE
	#if _IOB(p_Touch) == _IOB(LOG)
					INTEN.0		=	0;
	#endif
	#if	TOUCH_GPIO <= 2
					$ p_Touch	Low, Out;
	#else
					$ p_Touch	In;
	#endif
#else
	#if	TOUCH_GPIO >= 2
					$ p_Touch	High, Out;
	#else
					$ p_Touch	In;
	#endif
	#if _IOB(p_Touch) == _IOB(LOG)
					if (!INTEN.0)
					{
						if (UART_In)
						{
							INTRQ.0		=	0;
							INTEN.0		=	1;
						}
					}
	#endif
#endif
				}
			}
		}

#if	!_SYS(AT_ISP_ICE)
		if (!f_Uart_IHRC)
		{
#if	_SYS(AT_ISP_ICE)
			$ CLKMD		ILRC/1, En_IHRC, En_ILRC;
#else
			$ CLKMD		ILRC/1, En_IHRC, En_ILRC, EN_Watchdog;
#endif
			CLKMD.En_IHRC	=	0;
			$ p_Touch	In;//新程序
			wdreset;
#if	_SYS(IO.defined.TM3C.NILRC)
			stopsys;
#else
			stopexe;
#endif
#if	_SYS(AT_ISP_ICE)
			$ CLKMD		IHRC/System_DIV, En_IHRC, En_ILRC;
#else
			$ CLKMD		IHRC/System_DIV, En_IHRC, En_ILRC, EN_Watchdog;
			$ p_Touch	Low, Out;//新程序
#endif
		}
#endif
	}
}


void	Interrupt (void)
{
	pushaf;

	if (INTRQ.TM2)
	{
		INTRQ.TM2	=	0;
		if (Uart_Bit)
		{
			Uart_Shift	>>=	1;
			if (UART_In)
				Uart_Shift.7	=	1;
			if (--Uart_Bit == 0)
			{
				INTRQ.0			=	0;
				INTEN.0			=	1;
				Uart_Timerout	=	0;
				Uart_Receive$1	=	Uart_Receive$0;
				Uart_Receive$0	=	Uart_Shift;
				f_Uart_Receive		=	1;
			}
		}
		else if (++Uart_Timerout$0 == 0)
		{
			if (++Uart_Timerout$1 == 0)
			{
				$ TM2C		Disable;
				f_Uart_IHRC		=	0;
				f_UART_Mode		=	0;
			}
			else if (f_Uart_Receive)
			{
				f_Uart_Receive	=	0;
				$ UART_Out	Out;
				switch (Uart_Receive$1)
				{
				case 0x00:
					if (Uart_Receive$0 == 0x00)
					{
						A	=	0x00;		UART_Send();
					}
					break;
				case 0x02:
					$ TM2C		Disable;
					f_UART_Mode		=	1;
					Uart_Transmit	=	256;
					break;
				case 0x03:
					if (Uart_Receive$0 == 0x01)
					{
						A	=	0xA0 | cnt_Touch_Pin;	UART_Send();
					}
					else if (Uart_Receive$0 == 0x06)
					{
#ifdef KEY_SENSE
						A	=	KEY_SENSE;	UART_Send();
#else
						A	=	KEY_SENSE_0;	UART_Send();
#endif
					}
					break;
#if	_SYS(AT_ISP_ICE)
				default:
					.printf("UART:%04X", Uart_Receive);
					break;
#endif
				}
				$ UART_Out	In;
				INTRQ.0			=	0;
				Uart_Receive	=	0;
			}
		}
	}

	if (INTRQ.0)
	{
		if (INTEN.0)
		{
			f_Uart_IHRC	=	1;
			$ TM2C		IHRC;

			if (!UART_In)
			{
				INTEN.0		=	0;
				Uart_Bit	=	8;
				.Delay 50
				TM2CT		=	0;
				INTRQ.TM2	=	0;
			}
		}
		INTRQ.0	=	0;
	}

	popaf;
}