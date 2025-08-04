//;****************************************************************************
/******************************************************************************
  * MC30P8160 触摸参考程序
  * 说明：
  * 1.可实现4键触控，针对于Demo开发
  * 2.连接引脚到TK焊盘上，通过手触摸，LED会点亮
  * 3.模拟串口打印TK数据功能
  *	  客户可通过外接串口工具，使能串口函数Uart_Process()，把TK数据打印出来分析
  ******************************************************************************
  * 几个特殊指令用法
  *	   	stop指令： Stop();
  *	   	清狗指令： Clrwdt();
  *	   	空指令：   Nop();
  ******************************************************************************
 ******************************************************************************/

#include "MC30P8160_include.h"
#include "MC30P8160_MAIN.h" 

/************************************************
函数名:   	Init_Sys
说明:
************************************************/
void  Init_Sys(void)
{  	   	   	
   	__asm
SET_OPTION:
   	MOVAI   00001111B  	   	//;I/O口数字功能设定,0是有效
   	MOVRA   P1ADCR
   	MOVAI   00001111B  	   	//;P10,P11,P12输出口，P14,P15输入口；1为输入，0为输出(P13只能做输入)
   	MOVRA   DDR1
   	MOVAI   00000000B  	   	//;P10,P11,P12输出，P14,P15输入口低电平触发
   	MOVRA   P1
   	
   	MOVAI   0xFF   	   	   	//;下拉电阻,1是无效
   	MOVRA   PDCON
   	MOVAI   0xFF   	   	   	//;P14,P15开上拉电阻,P13无法设上拉、下拉，均为浮空，做输入口时最好外边加上拉电阻
   	MOVRA   PUCON  	   	   	//;3081/6060的P13有上拉
   	MOVAI   0x00   	   	   	//;开漏推挽,1是开漏,0是推挽
   	MOVRA   ODCON

//;定时器设定   	
//;	MOVAI   00000011B  	   	//;定时器0配置,BIT0-2:定时器分频,BIT3定时器分配:1-WDT,0-TC0
//;	MOVRA   T0CR   	   	   	//;BIT4:0-上升沿计数1-下降沿计数,BIT5:时钟源0-FCPU,1-外部;BIT6:1-上升沿触发0-下降沿触发
//;	MOVAI   6  	;131
//;	CLRR   	T0CNT  	   	   	//;清定时器0计数值;T0没有自动重载器，所以计数值以256为基准，或者在中断里改变T0CNT值

   	MOVAI   00000000B  	   	//;定时器1配置,BIT7=T1EN, BIT6=PWM1AOE,1允许PWM, BIT5=PWM1AEN,1使能PWM1A
   	MOVRA   T1CR   	   	   	//;BIT4.3:T1时钟源选择,BIT2-0:T1分频
   	CLRR   	T1CNT  	   	   	//;清定时器1计数值
   	CLRR   	T1LOAD
   	MOVAI  	00000000B
   	MOVRA  	TMRCR  	   	   	//;BIT6=T0TBS,BIT3=T2IE,BIT2=T2IF,BIT1=T1IE,BIT0=T1IF
   	MOVAI  	00000000B
   	MOVRA  	PWM1CR0	   	   	//;关闭PWM
   	MOVAI  	00000000B
   	MOVRA  	PWM1CR1
   	MOVAI  	00000000B
   	MOVRA  	PWM1CR2
   	CLRR   	T1DATA
   	CLRR   	T1DATB
   	CLRR   	T1DATC
   	CLRR   	T1DATD

//;	MOVAI   00000010B  	   	//;定时器2配置,BIT0-2:定时器分频,BIT3定时器分配:1-WDT,0-TC0
//;	MOVRA   T2CR   	   	   	//;BIT4:0-上升沿1-下降沿,BIT5:：
//;	MOVAI   0XF0
//;	MOVRA  	T2CNTL 	   	   	//;清定时器2计数值
//;	MOVRA  	T2LOADL	   	   	//;清定时器2计数值
//;	MOVAI   0X6D
//;	MOVRA  	T2LOADH	   	   	//;清定时器2计数值
   	
   	MOVAI   00000001B
   	MOVRA   INTECON	   	   	//;BIT7=GIE,总中断,BIT0=T0IE,BIT1=KBIE,BIT2=INT0IE,1-中断使能
   	BSET   	INTECON,7  	   	//;GIE
//;	BSET   	T0IE   	   	   	//;打开T0中断，必须单独设定
   	MOVAI   0x00
   	MOVRA   INTFLAG	   	   	//;BIT0=T0IF,BIT1=KBIF,BIT2=INT0IF,1-中断发生
   	MOVAI   0x00   	   	   	//;P14,P15,P13键盘中断功能开
   	MOVRA   KBIM
   	RETURN
    __endasm;
} 
/************************************************
函数名:   	Clr_Ram
说明:
************************************************/
void  Clr_Ram(void)
{
   	__asm
CLR_RAM:
   	MOVAI  	0X4F
   	MOVRA  	FSR
   	MOVAI  	0X3F
   	MOVRA  	0X4F   	   	   	;把寄存器的数量保存到最后一个寄存器上
CLR_RAM_LOOP:
   	DECR   	FSR
   	CLRR   	INDF
   	DJZR   	0X4F
   	GOTO   	CLR_RAM_LOOP
   	RETURN
    __endasm;
}   
/************************************************
函数名:主函数
说明:
************************************************/
void main()
{      	                 
   	   	Clr_Ram();
   	   	Init_Sys();
   	   	SET_TOUCH_OPTION();
   	   	SET_TOUCH_OPTION2();
 	   	SET_UART_9600BPS();	   	   	   	//;设定串口波特率
   	   	while(1) 
   	   	{      	
   	   	   	WDT_Clear();
   	   	   	SCAN_TOUCH();
   	   	   	TOUCH_OUT();
//;--------------------------- 	   	   	//;串口功能是否使能
			SCAN_UART_OUT();   	   	   	//;串口输出子程序
			if (!(CPLAY_FLAG&0X10))
				{
				OPEN_OUT_UART();   	   	//;开启串口输出
				}
//;---------------------------
   	   	   	if((CTOUCH_FLAG==0X00)&(!(CPLAY_FLAG&0X02)))
   	   	   		{
   	   	   	   	DDR1=0x0F;
   	   	   	   	P1=0x00;
//;需要休眠功能时，需要在上电初始后有1-2秒TOUCH适应环境的过程，就是上电后不要立即进入休眠，需高速运行1-2秒和扫描SCAN_TOUCH。
//;	   	   	   	TK_SLEEP();	   	   	   	   	//休眠两种编写方式(方式一)

   	   	   	   	TKEN=0;	   	   	   	   	   	//关闭TK
   	   	   	   	SLEEP();   	   	   	   	   	//休眠两种编写方式(方式二)
   	   	   	   	SET_TOUCH_OPTION2();
   	   	   		}
   	   	}
}


/************************************************
函数名:中断程序
说明:
************************************************/
void int_isr(void) __interrupt
{
   	__asm
   	MOVRA  	SAVE_ACC
   	SWAPAR 	STATUS
   	MOVRA  	SAVE_STATUS
   	__endasm;

//========= T0/T1中断 ==============     	
       	if(T0IF)
       	{      	       	
			T0IF   = 0; 
       	}

       	if(T1IF)
       	{      	       	
			T1IF   = 0; 
//;--------------------------
			UART_SUB();    	   	   	   	//;串口中断处理
//;--------------------------
       	}

   	__asm
   	SWAPAR 	SAVE_STATUS
   	MOVRA  	STATUS
   	SWAPR  	SAVE_ACC
   	SWAPAR 	SAVE_ACC
   	__endasm;
}

/************************************************
函数名:触摸响应输出程序
说明:
************************************************/
void TOUCH_OUT(void)
{
//-----------------TK0 -------------------
   	   	   	if((CTOUCH_FLAG&0X0F)==0)
   	   	   	   	{
   	   	   	   	PIN_LED1=OFF;
   	   	   	   	}
   	   	   	else
   	   	   	   	{
   	   	   	   	PIN_LED1=ON;
   	   	   	   	}
}

//;****************************************************************************
//;****************************************************************************

