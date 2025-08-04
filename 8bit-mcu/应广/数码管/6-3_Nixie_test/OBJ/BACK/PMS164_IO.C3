//==========================================//
//				Nixie_Timing
//The Nixie Tube is 5-pin for 2-digit
//Couting between 00-99£¬step_time:1s
//==========================================//
#include	"extern.h"
#include	"Nixie_6-3.c"


WORD T16_1ms_Cnt;

bit	T16_1ms_Flag;
bit	T16_2ms_Flag;
// Timed 1ms
word   Reload_T16;
void   Timer16_Init(void)
{
	Reload_T16 = 32768 - 16000;
	stt16 Reload_T16;
	$ T16M IHRC,/1,bit15;
	$ INTEGS BIT_R;
	INTRQ.T16 = 0;
	INTEN.T16 = 1;
	ENGINT;
}


void	FPPA0 (void)
{
	.ADJUST_IC	SYSCLK=IHRC/16, IHRC=16MHz, VDD=3.3V;

	Timer16_Init();
	Num = 138;
	while(1)
	{
		if(T16_1ms_Flag)
		{
			T16_1ms_Flag = 0;

			LED_Scan_Display_6COM(Num);
		}

	}

}


void	Interrupt (void)
{
	pushaf;

	if (Intrq.T16)
	{	

		Intrq.T16	=	0;
		stt16	Reload_T16;		

		T16_1ms_Flag = 1;

		T16_1ms_Cnt ++;
		if(T16_1ms_Cnt > 1) // 1s
		{
			T16_2ms_Flag = 1;
			T16_1ms_Cnt = 0;
		}	

		if(T16_1ms_Cnt > 1000) // 1s
		{
			T16_1ms_Cnt = 0;
			//if(Num >= 999)
			//{
			//	Num = 0;
			//}
			//else
			//{
			//	Num ++;
			//}
		}		
	
	}

	popaf;
}