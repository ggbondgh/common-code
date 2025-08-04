
#include	"extern.h"
#include	"164_Touch_Define.C"
//#include	"UART.C"

#define	DBYTE  1   //1为：2字节  0为：1次发送

#define	UART_SEG 1

#define	UART 0
#define	UART_LEN 8

#define	UART_USER_PIN PA.7
#define	UART_INT_PIN PA.5
#define SLEEP_PIN PB.7

byte Uart_ov = 1 , Uart_user_cnt = 0;
byte Uart_send_F = 0;
word Uart_send_buff[4]={0};
byte Uart_send_buff_whitchone = 0;

void Uart_send_Funcation()
{
	Uart_user_cnt++;
	if(Uart_user_cnt <= UART_LEN)
	{
		if(Uart_send_buff[0]&0x8000)
			UART_USER_PIN = 1;
		else
			UART_USER_PIN = 0;
		Uart_send_buff[0] <<=1;
	}
	else if(Uart_user_cnt == UART_LEN+1)
	{
		UART_USER_PIN = 1;
	}
#if  DBYTE
	else if(Uart_user_cnt == UART_LEN+2)
	{
		UART_USER_PIN = 0;
	}
	else if(Uart_user_cnt <= 2*UART_LEN+2)
	{
		if(Uart_send_buff[0]&0x8000)
			UART_USER_PIN = 1;
		else
			UART_USER_PIN = 0;
		Uart_send_buff[0] <<=1;
	}
	else if(Uart_user_cnt == 2*UART_LEN+3)
	{
		UART_USER_PIN = 1;
	}
	else if(Uart_user_cnt == 2*UART_LEN+4)
	{
		Uart_user_cnt = 0;
		Uart_ov = 1;
		UART_INT_PIN = 1;
		INTRQ.TM2 = 0;
		INTEN.TM2 = 0;
	}
#else 
	else if(Uart_user_cnt == UART_LEN+2)
	{
		Uart_user_cnt = 0;
		Uart_ov = 1;
		UART_INT_PIN = 1;
		INTRQ.TM2 = 0;
		INTEN.TM2 = 0;
	}
#endif
	
}

void Uart_User_func()
{
	if(Uart_ov)
	{
		if(Uart_send_F)
		{
			Uart_send_buff[0] = T_Key_Signal1;//T_Key_Signal1
			Uart_send_F = 0;
			Uart_user_cnt = 0;
			Uart_ov = 0;
			UART_INT_PIN = 1;

			UART_USER_PIN = 0;
			tm2ct = 0;
			INTRQ.TM2 = 0;
			INTEN.TM2 = 1;
		}
	}
	else
	{
		if(Uart_send_F)
		{
			if(Uart_send_buff[0])
			Uart_send_buff[1] = T_Key_Signal1;
			Uart_send_F = 0;
		}
	}
}



word   Reload_T16;
void   Timer16_Init(void)
{
	Reload_T16 = 32768 - 10000;
	stt16 Reload_T16;
	$ T16M IHRC,/16,bit15;
	$ INTEGS BIT_R;
	INTRQ.T16 = 0;
	INTEN.T16 = 1;
	ENGINT;
}
void   Timer2_Init(void)
{
	tm2ct = 0;
	tm2b = 5;
	$ TM2C IHRC,Disable,Period;
	$ TM2S 8bit,/16,/17;
	INTRQ.TM2 = 0;
	INTEN.TM2 = 0;
}



byte	Tk_ScanF = 0;

word TK_Signal_memory = 1;
void	TK_Send_get()
{
	if(T_Key_Signal1  != TK_Signal_memory)
	{
		if(!Uart_send_F)
		{
			Uart_send_F = 1;
		}
		else
		{
			;
		}
		TK_Signal_memory = T_Key_Signal1;
	}
}



word reload_T16_S;
void	Save_power(void)
{
	//======User can add code=====
	//进入省电模式前动作，如关灯、关计数器等
	//关闭不需要唤醒的引脚的数字使能，例中只给了PA的设置

	while(1)
	{
		$ CLKMD ILRC/1,En_IHRC,En_ILRC;	//系统时钟选择，是否启用IHRC，是否启用ILRC，（En_IHRC和En_ILRC不写为停用，写为启用）
										//系统时钟可选择IHRC/4, IHRC/16, IHRC/2, IHRC/8, ILRC/16, EOSC/4, IHRC/32, EOSC/2, IHRC/64, EOSC/1, EOSC/8, ILRC/4, ILRC/1
										//选择系统时钟为ILRC/1，启用IHLC和IHRC；（注：两个RC振荡器至少有一个开启，否则会出现宕机）
		CLKMD.En_IHRC = 0;				//关闭高频IHRC，若上条语句没使用低频时钟，此句必须去掉
		nop;
	//========设置T16定时，详情请参考T16=========
		$ T16M ILRC,/1,bit15;
		reload_T16_S = 32768 - 4000;
		stt16 reload_T16_S;
	
		stopexe;						//进入省电模式，T16计时溢出时唤醒

		if(!SLEEP_PIN)
			break;
		$ CLKMD ILRC/1,En_IHRC,En_ILRC;	//打开高频使能，准备切换高频进入唤醒条件判断
		$ CLKMD IHRC/8,EN_IHRC,EN_ILRC;//选择系统时钟为IHRC/64，启用IHLC和IHRC
		nop;
		break;
	//=======编写唤醒条件=========
		//例如num自加超过100后唤醒，该方法针对不是IO脚电平变化的唤醒条件
	}
	Timer16_Init();
	//============================							
}

void	FPPA0 (void)
{
	.ADJUST_IC	SYSCLK=IHRC/4		//	SYSCLK=IHRC/4

	byte	cnt = 4;

#if UART
	$ send out;
#endif
	$ UART_USER_PIN out;
	Timer2_Init();
	Timer16_Init();
	Touch_Init();
	Uart_send_F = 1;
	Uart_User_func();
	while (1)
	{
		
		if(Tk_ScanF)
		{	
			Touch_Func();
#if UART
			Uart_Send_Data();
#endif
			TK_Send_get();
			Tk_ScanF = 0;
		}
		Uart_User_func();

		if(SLEEP_PIN)
		{
			Save_power();
			Tk_ScanF = 1;
		}
//		...
//		wdreset;

	}
}


void	Interrupt (void)
{
	pushaf;

	if (Intrq.T16)
	{	//	T16 Trig
		//	User can add code
		stt16	Reload_T16;
		Intrq.T16	=	0;
		if(!Tk_ScanF)Tk_ScanF = 1;
		//...
	}
	if(Intrq.TM2 && INTEN.TM2)
	{
		Intrq.TM2 = 0;
		Uart_send_Funcation();

	}
	popaf;
}