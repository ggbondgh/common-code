//==========================================//
//			 串口IR逻辑接收函数
//案例为：
//串口接收时序：一位起始码+八位数据(数据类型由占空比决定决定)
//==========================================//
#include	"extern.h"
#define	Rx	PA.0

byte	i;
byte	Rx_Data;
byte	Data_temp;
bit		Rx_Sign;
byte	Rx_Mode = 0;
byte	Time_100us;
byte	Time_lOW_100us;
word	Reload_T16;


//================IO设置======================//
void	IO_init(void)
{
	PADIER	=	0b0000_0001;
	$ Rx in,pull;		
	$ PA.7 out,low;
}

void	UART_Receive(void)
{
	switch(Rx_Mode)
	{
		case 0://初始等待起始码到来
			if(!Rx)
			{
	 			Rx_Mode = 1;
				Rx_Sign = 1;

			}
			else
			{
				Rx_Mode = 0;
			}
			Time_100us = 0;
			break;
		case 1://判断起始码是否成立
			if(Rx_Sign)
			{
				if(Rx)//等待高电平出现准备进入低电平检测
				{
					Rx_Sign = 0;
				}
			}
			else
			{
				if(!Rx)
				{
					if(Time_100us >= 50 && Time_100us <= 70)//判断起始码的时间是否在(6.456ms)左右
					{
						Rx_Mode = 2;//起始码正确，进入下个模式
						Rx_Sign = 1;
		
						Time_lOW_100us = 0;
						i = 0;
					}
					else
					{
						Rx_Mode = 0;//起始码错误，重新判断起始码
					}
				}
			}
			break;
		case 2://判断数据码0或1，并记录
			if(Rx_Sign)
			{
				if(Rx)//检测前面低电平时间长度：小于501us则是1，否则是0
				{


					if(Time_lOW_100us >= 7)//判断数据码是0
					{
						.tog PA.7
						Data_temp <<= 1;
						Data_temp |= 0x00;
						Time_lOW_100us = 0;
					}
					else//判断数据码是1
					{
						Data_temp <<= 1;
						Data_temp |= 0x01;
						Time_lOW_100us = 0;
					}				
					Rx_Sign = 0;
				}
			}
			else
			{
				if(!Rx)
				{
					i++;
					Rx_Mode = 2;
					Rx_Sign = 1;
					if(i==8)//数据全部接受完毕，进入下一个模式
					{
						Rx_Mode = 3;
					}
				}
			}
			break;
		case 3:
	 		Rx_Data = Data_temp;
			.printf("%.2X\n",Rx_Data);//测试代码，查看接收到的数据
			Rx_Mode = 0;
			break;
	}
}

//定时100us
void	Timer16_Init(void)
{
	Reload_T16 = 1024 - 100;
	$ T16M IHRC,/16,bit10;
	stt16 Reload_T16;
	INTEN.T16 = 1;
	INTRQ.T16 = 0;
	ENGINT;
}

void	FPPA0 (void)
{
	.ADJUST_IC	SYSCLK=IHRC/16, IHRC=16MHz, VDD=3.3V;

	Timer16_Init();
	IO_init();

	while (1)
	{
		UART_Receive();
	}
}

void	Interrupt (void)
{
	pushaf;

	if (Intrq.T16)
	{

		Intrq.T16 = 0;
		Stt16 reload_T16;
	
		if(!Rx)
		{
			Time_lOW_100us ++;
		}

		Time_100us ++;		
		
	}

	popaf;
}