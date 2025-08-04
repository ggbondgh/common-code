
/*--------------------------- 固定搭配 -----------------------------*/

// 引脚定义方式
#define Key PA.3
Key		=>	PA.3
Key	   equ	   PA.3
Rx     bit     PA.0
bit    Rx  :   PA.0

// LED
byte LED1_Flag = 0x00;
bit  LED_0_Flag :   LED1_Flag.0;
bit  LED_1_Flag :   LED1_Flag.1;
bit  LED_2_Flag :   LED1_Flag.2;
bit  LED_3_Flag :   LED1_Flag.3;
bit  LED_4_Flag :   LED1_Flag.4;

.tog PA.x

.printf("%d\n",Data);

// if-mode
if(Mode == 0)
{
}
else if(Mode == 1)
{
}
else if(Mode == 2)
{
}
else if(Mode == 3)
{
}
Mode++;
if(Mode > 3)
{
	Mode = 0;
}

// Switch-case
switch(N)
{
	case 1:
		xx;
		break;
	case 2:
		xx;
		break;
	case 3:
		xx;
		break;
	default:
		break;
}


/*--------------------------- Main.c -----------------------------*/
#include "extern.h"


/***************** Var definition *************************/
bit  T16_1ms_Flag;
byte _1ms_Cnt;

/***************** IO_Init *************************/
void IO_Init(void)
{
	// PA		=	0b0000_0000;
	// PAC		=	0b0000_0000;
	// PAPH		=	0b0000_0000;
	// PAPL	 	=	0b0000_0000;

	// PB		=	0b0000_0000;
	// PBC		=	0b0000_0000;
	// PBPH		=	0b0000_0000;
	// PBPL  	=	0b0000_0000;

	// PADIER	=	0b0000_0000;
	// PBDIER	=	0b0000_0000;

	// $ PA.3 out,low;	// $ KEY in,pull;

}

/***************** Timer_Init ************************/
// 1ms定时
word Reload_T16;
void Timer16_Init(void)
{
	Reload_T16 = 32768 - 16000;
	stt16 Reload_T16;
	$ T16M IHRC, / 1, bit15;
	$ INTEGS BIT_R;
	INTRQ.T16 = 0;
	INTEN.T16 = 1;
	ENGINT;
}

/***************** PWM_Init **************************/
// void TM2_PWM_Init(void)
// {
// 	TM2CT = 0;
// 	//	TM2B = 127;		            // Duty: 50%
// 	//	$ TM2C IHRC,PA4,PWM;		// Open PWM
// 	//	$ TM2C STOP;				// Close PWM
// 	$ TM2S 8BIT, / 1, / 1; 			// Resolution, prescaler, divider, the frequency here is 3906.25Hz
// }





/***************** Sys_Init **************************/
void System_Init(void)
{
	/* Func_Init */
	IO_Init();
	Timer16_Init();
	// TM2_PWM_Init();

	/* Var_Init */

}

/************** Main & Interrupt *********************/
void FPPA0 (void)
{
	.ADJUST_IC	SYSCLK=IHRC/SYSClK_DIV, IHRC=16MHz, VDD=3.3V, Init_RAM;

	System_Init();

	while (1)
	{

		if(T16_1ms_Flag)
		{
			T16_1ms_Flag = 0;
			_1ms_Cnt++;
			if(_1ms_Cnt >= 10)
			{
				_1ms_Cnt = 0;
			}
		}

	}
}

void Interrupt (void)
{
	pushaf;

	if(Intrq.T16)
	{	//	T16 Trig
		Intrq.T16 = 0;
		stt16 Reload_T16;
		
		// T16_1ms_Flag = 1;

		// T16_100us_Cnt1 ++;	
		// if(T16_100us_Cnt1 >= 100)
		// {
		// 	T16_100us_Cnt1 = 0;
		// 	Time_10ms_Flag = 1;
		// }

	}

	popaf;
}

/*--------------------------- extern.h -----------------------------*/
/*
* 
* 
* 
* 
* 
* 
*/
/****************** Pin definition *************************/
TK1         =>     PA.3 // 
TK2         =>     PB.3 // 


/********************** Macro ******************************/
#define SYSClK_DIV 4
#define SLEEP_EN 0

/***************** Var declaration *************************/



/***************** Func declaration ************************/



/*--------------------------- 系统设定相关 -----------------------------*/
byte CLKMD_BK;
CLKMD_BK = CLKMD; // 保存休眠前的时钟

$ CLKMD ILRC/1,En_IHRC,En_ILRC;	// 系统时钟选择，是否启用IHRC，是否启用ILRC，（En_IHRC和En_ILRC不写为停用，写为启用）
CLKMD.En_IHRC = 0;				// 关闭高频IHRC

CLKMD = CLKMD_BK; // 恢复休眠前的时钟

//$ MISC	WDT_64K,Fast_Wake_Up,LVR_Disable;

eoscr = 0x00; // 开LVR
eoscr = 0x01; // 关LVR

// 看门狗
//CLKMD.En_ILRC = 1; // 打开低频
.wdreset; // 看门狗清零
CLKMD.En_WatchDog = 1; // 打开看门狗功能，当看门狗超时溢出，程序会复位并重新运行程序。置0则关闭看门狗
$ MISC WDT_256K;	   // 看门狗时钟超时时间设定


/*--------------------------- 低功耗 -----------------------------*/
/* Low-power mode_1 */
/***************** Sleep *************************/
#define Const_SleepCnt 1000 // 定义多长时间无操作即进入睡眠
word SleepCnt = Const_SleepCnt;

void Sleep_Mode(void)
{
	if(SleepCnt)
	{
		SleepCnt --;
	}
	if(OPERATION) // OPERATION not sleep
	{
		SleepCnt = Const_SleepCnt;
	}

	if(!SleepCnt)
	{
		$ CLKMD ILRC/1,En_IHRC,En_ILRC;										
		CLKMD.En_IHRC = 0;	
		nop;			
		while(1)
		{
			stopsys;					
			if() // Out sleep condition			
			{
				SleepCnt = Const_SleepCnt;
				break;
			}
		}
		$ CLKMD ILRC/1,En_IHRC,En_ILRC;	
		$ CLKMD IHRC/SYSClK_DIV,EN_IHRC,EN_ILRC;		
	}
}
/* Low-power mode_2 */
/***************** Sleep *************************/
byte CLKMD_BK;
void Power_Down(void)
{
	/* USER CODE - BEFORE SLEEP BEGIN */
	
	/* USER CODE - BEFORE SLEEP END */

	CLKMD_BK = CLKMD;					// Save the CLK
	$ CLKMD ILRC/1,En_IHRC,En_ILRC;	
	CLKMD.En_IHRC = 0;	
	nop;
	while(1)
	{
		stopsys;						// Power down

		if(!PA.0)						// USER CODE, Awake condition
		{								
			break;
		}
	}
	$ CLKMD ILRC/SYSClK_DIV,EN_IHRC,EN_ILRC;
	nop;
	CLKMD = CLKMD_BK;					// Restore the CLK

	/* USER CODE - AFTER SLEEP BEGIN */
	
	/* USER CODE - AFTER SLEEP END */
}
/* Low-power mode_3 for touch */
/***************** Sleep *************************/
#define Const_Sleep_WakeUp  3680  		// 3680 ?80MS
byte SleepCnt;

void Sleep_Mode(void)
{
	if(SleepCnt)
	{
		SleepCnt --;
	}

	if() // Unsleep condition
	{
		SleepCnt = 200;
	}

	if(!SleepCnt)
	{
		// $ MISC Fast_Wake_Up;

		Reload_T16 = 32768 - Const_Sleep_WakeUp;  //
		STT16 Reload_T16;

		$ T16M	ILRC,/1,BIT15;

		INTRQ.T16 = 0;

		//eoscr = 0x01; // 关LVR，减少电流

		//$ CLKMD	 ILRC/1, En_IHRC, En_ILRC, EN_Watchdog;
		$ CLKMD	 ILRC/1, En_IHRC, En_ILRC;
		//CLKMD.EN_Watchdog	=	0;
		CLKMD.En_IHRC	=	0;

		stopexe;

		if() // Unsleep condition
			SleepCnt = 200;

		//$ CLKMD	IHRC/SysClock_DIV, En_IHRC, En_ILRC, EN_Watchdog;
		$ CLKMD	IHRC/SYSClK_DIV, En_IHRC, En_ILRC;

		//eoscr = 0x00; // 开LVR

		Timer16_Init(); //100us  //切换定时唤醒时间

		T16_1ms_Flag = 1;
	}
}
