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

//#define  Uart

//#define  LED_R     P15D



// 不跳频  4.8M
#define	   	TK_SENS_LEVEL_H1  0x0E     	   	//;TK0触摸灵敏度级别1
#define	   	TK_SENS_LEVEL_L   0xFF     	   	//;TK0触摸灵敏度级别


#define FilterCnt_Value    	11
#define Const_SEN_T_Key0   	45
#define Const_SEN_T_Key0_Release  60

#define Const_SEN_T_Key1   	45
//#define Const_SEN_T_Key1_Release  60

// 触摸
// 位定义
#define    	T_Key0_Signal      	flag1.bits.bit0    	 // 标志位
#define    	Pre_T_Key0_Release  flag1.bits.bit1	   	 // 标志位
#define    	TK0_Release_Flag    flag1.bits.bit2	   	 // 标志位
#define     TK1_Long_press_Flag   flag1.bits.bit3  	 // 标志位
#define    	T0_5ms_Flag        	flag1.bits.bit4	   	 // 标志位
#define    	T0_10ms_Flag        flag1.bits.bit5	   	 // 标志位
#define    	TK0_Long_press_Flag   flag1.bits.bit6  	   	 // 标志位
#define    	W_AS_Flag          flag1.bits.bit7 	   	 // 标志位

#define    	W_Power_Flag       	    flag2.bits.bit0    // 标志位
#define    	PWM_Change_KeyFlg      	flag2.bits.bit1    // 标志位
#define    	TK0_Key_Release_Flag    flag2.bits.bit2    // 标志位
#define     T_Key1_Signal          	flag2.bits.bit3    // 标志位
#define     Pre_T_Key1_Release      flag2.bits.bit4    // 标志位
#define    	Y_Power_Flag           	flag2.bits.bit5    // 标志位
#define    	TK1_Release_Flag        flag2.bits.bit6    // 标志位
#define    	TK1_Key_Release_Flag    flag2.bits.bit7    // 标志位

#define    	Y_AS_Flag                flag3.bits.bit0    // 标志位

//uint8_t T_Key0_Signal;
//uint8_t Pre_T_Key0_Release;
//uint8_t TK0_Release_Flag;


uint16_t u16_get_val;      	   	//读取值
uint16_t u16_release_val;      	//
uint16_t u16_temp_val;

uint16_t u16_release_val_TK0;
uint16_t u16_release_val_TK1;
//uint16_t u16_TK0_get_val_Temp;
//uint16_t u16_TK1_get_val_Temp;
uint16_t u16_TK1_get_val_Min;
uint16_t u16_TK0_get_val_Min;

uint16_t u16_TK0_environment_val;
uint16_t u16_TK0_environment_val_Sum;
uint16_t u16_TK1_environment_val;
uint16_t u16_TK1_environment_val_Sum;

///////////////////////////////////////

uint8_t TK0_Filter_Cnt;
uint8_t TK0_Filter_Cnt_T;
uint8_t TK1_Filter_Cnt;
uint8_t TK1_Filter_Cnt_T;

uint8_t FilterCnt_TK0;
uint8_t FilterCnt_TK1;

uint8_t SleepCnt;  //睡眠计数

// PWM
//uint8_t PWM_Duty_Temp;
uint8_t PWM_Duty_W;
uint8_t PWM_Duty_Y;

uint8_t T_key_Value; // 0 1 2 3 
uint8_t TK1_Key_Cnt;
uint8_t TK0_Key_Cnt;


uint8_t T0_5ms_Cnt;
uint16_t u8_TK_Reset_Cnt;
uint16_t u16_TK0_get_val_Temp;
uint16_t u16_TK1_get_val_Temp;
// 串口
#define  Uart_TX     P14D

#define Uart // 关闭串口
unsigned char uart_send_c = 0;

/************************************************
函数名:   	Init_Sys
说明:
************************************************/


void Delay_us_2(uint8_t i)
{
   	for(; i>0; i--)
    {
   	   	WDT_Clear();
   	    Nop();
        Nop();
   	   	Nop();
        Nop();
    }
}
  
#ifdef Uart    	
   	   	
void Uart_Send_One_Byte(void) // 19200  52us delay(10) 4M
{
   	Uart_TX = 0;   	   	   	//起始位  	   	
   	Delay_us(11);

   	unsigned char bit_cnt = 0;

   	while(bit_cnt < 8) 	   	//8个数据位，先发低位再发高位
   	{  	   	   	   	   	
   	   	if(uart_send_c & 0x01)
   	   	{
   	   	   	Uart_TX = 1;
   	   	}
   	   	else
   	   	{
   	   	   	Uart_TX = 0;
   	   	}

   	   	uart_send_c >>= 1; 	//右移一位

   	   	bit_cnt ++;

   	   	Delay_us(10);
   	}
   	Uart_TX = 1;   	   	   	//停止位
   	Delay_us(10);
}
void Uart_Send_Data(void) // 19200  P14
{
       	uart_send_c = u16_get_val & 0x00FF;
       	Uart_Send_One_Byte();
       	uart_send_c =  (u16_get_val & 0xff00) >> 8; 
       	Uart_Send_One_Byte();

       	uart_send_c = u16_TK0_environment_val & 0x00FF;
       	 Uart_Send_One_Byte();
       	uart_send_c =  (u16_TK0_environment_val & 0xff00) >> 8; 
       	Uart_Send_One_Byte();
}
#endif 

void  Init_Sys(void)
{  	   	   	
   	__asm
SET_OPTION:

//;定时器设定 
//; T0     	   	   	   	011 256分频(系统时钟再256分频)
    MOVAI   00000111B  	   	//;定时器0配置,BIT0-2:定时器分频,BIT3定时器分配:1-WDT,0-TC0
    MOVRA   T0CR   	   	   	//;BIT4:0-上升沿计数1-下降沿计数,BIT5:时钟源0-FCPU,1-外部;BIT6:1-上升沿触发0-下降沿触发
    MOVAI   217    	   	   	  //;131
    CLRR   	T0CNT  	   	   	//;清定时器0计数值;T0没有自动重载器，所以计数值以256为基准，或者在中断里改变T0CNT值

//; T1 
   //  	MOVAI   00000000B  	   	//;定时器1配置,BIT7=T1EN, BIT6=PWM1AOE,1允许PWM, BIT5=PWM1AEN,1使能PWM1A
   //  	MOVRA   T1CR   	   	   	//;BIT4.3:T1时钟源选择,BIT2-0:T1分频
   //  	CLRR   	T1CNT  	   	   	//;清定时器1计数值
   //  	CLRR   	T1LOAD
   //  	MOVAI  	00000000B
   //  	MOVRA  	TMRCR  	   	   	//;BIT6=T0TBS,BIT3=T2IE,BIT2=T2IF,BIT1=T1IE,BIT0=T1IF
   //  	MOVAI  	00000000B
   //  	MOVRA  	PWM1CR0	   	   	//;关闭PWM
   //  	MOVAI  	00000000B
   //  	MOVRA  	PWM1CR1
   //  	MOVAI  	00000000B
   //  	MOVRA  	PWM1CR2
   //  	CLRR   	T1DATA
   //  	CLRR   	T1DATB
   //  	CLRR   	T1DATC
   //  	CLRR   	T1DATD

//; T2  触摸
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
 //    	BSET   	T0IE   	   	   	//;
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
   	MOVRA  	0X4F   	   	   	;//把寄存器的数量保存到最后一个寄存器上
CLR_RAM_LOOP:
   	DECR   	FSR
   	CLRR   	INDF
   	DJZR   	0X4F
   	GOTO   	CLR_RAM_LOOP
   	RETURN
    __endasm;
}   


void T1_PWM_Init(void)
{
    T1CR = 0x89;    // 100_01_001 使能T1、时钟为FOSC、2分频
    T1CNT = 255-1;
    T1LOAD = 255-1;    	   	//31k
}


void IO_Init(void)
{
   	P1 = 0x00; //  	P1nD – P1n 端口数据位（n=5-0）

   	//xx11_1011;   	0 输出   1输入
   	DDR1 = 0x33;   	   // DR1n – P1n 端口方向控制位（n=5-0）  0： 端口作为输出口
   	//  P12   输出口  P10 P11 P14 P15输入

   	// xx11_0011
   	P1ADCR = 0x33;   // 0 使能端口的数字 I/O 功能； 1 关闭端口的数字 I/O 功能；
   	
   	// 1111_1101 P11
   	PUCON = 0xFF; //  1：端口内部上拉电阻无效；  0：端口内部上拉电阻有效
   	PDCON = 0xFF; //  1：端口内部下拉电阻无效；  0：端口内部下拉电阻有效

   	ODCON = 0x00; // 0： 端口输出时为推挽输出   1 开漏输出


}

/************************************************
函数名:触摸初始化
说明:
************************************************/
void TOUCH_Init(void)
{
__asm 

//SET_TOUCH_OPTION:
//    MOVAI   0x01;    	   	   	   	//;00000011B
//     	MOVRA   P1ADCR 	   	   	   	   	//;设定对应的TK口为非数字功能，1为非数字功能
//     	ORRA   	DDR1   	   	   	   	   	//;只设定TK脚为输入模式，其它不变。输入/输出；1为输入，0为输出
  //   	MOVRA  	TOUCH_FLAG
  //   	SWAPR  	TOUCH_FLAG 	   	   	   	//;将对应的TK 使能触摸点要刷新基准数据（TOUCH_NEW_FLAG）
   	BCLR   	_T2IE  	   	   	   	   	//;不需要T2中断，TK采用扫描方式
  //   	MOVAI  	11001000B  	   	   	   	//;定时器0配置,BIT7为定时器2开启,BIT6为定时器2连续/单次计数模式,BIT4-3:时钟源选定,BIT0-2:定时器分频
  //   	ORRA   	T2CR   	   	   	   	   	//;开启T2定时器，并且为单次计时模式
   	MOVAI  	00000000B
   	MOVRA  	TKCR0  	   	   	   	   	//;TK触摸配置,BIT7=1开启TK,BIT6=1允许触摸充放电,BIT5/4为TK时钟滤波,BIT3:TK跳频,BIT2-0:TK振荡频率选择
   	MOVAI   11111111B  	   	   	   	//;选择通道0
   	MOVRA  	TKCR2  	   	   	   	   	//;TK触摸配置,BIT7=1使能TK计数,BIT6:TKM计数中断,BIT2/0:选定触摸通道
   	RETURN
__endasm;
}

void TK_Init(void)
{
    //
   	TKCR1 &= 0x03; // 关闭触摸, 不改变通道选择位 bit 0-1
   	TKCNTH = 0;
   	TKCNTL = 0;

   	T2MOD = 1;   // 单次计时模式（触摸模式）
   // T2CR = 0x49; // 01_0_01_000 FOSC 2分频
   	T2CR = 0x4A;   // 01_0_01_010 FOSC 16M 4分频 4M

   	T2LOADH = TK_SENS_LEVEL_H1;
   	T2LOADL = TK_SENS_LEVEL_L;


   //  	TKCR1 &= 0xFC; // 写0000_0000 bit0-1: 00 TK0 选择相应按键输入通道

   	TKCR0 = 0xF4;  // 写1111_0000 bit0-3: 000 TK0 选择 4.8MHz

 //    	TKCFL = 0; 	   // TKM 计数时钟滤波时间（典型值）为 10ns；
   	TKCFL = 1; 	 // TKM 计数时钟滤波时间（典型值）为 50ns；

 //    	TKFJE = 1; 	// 开启 TKM 自动跳频功能
   	TKFJE = 0; 	// 关闭 TKM 自动跳频功能
   	T2EN = 1;  	// 开启定时器 T2
   	TKCON = 1; 	// 允许 TKM 电容充放计数
   	TKEN = 1;  	// 开启 TKM      	       	
}

void Get_TK_Value(void)
{
   	while(TKCF == 1)
    {
   	   	WDT_Clear();
    }

    u16_get_val =  (TKCNTH << 8) | TKCNTL;

   	TKCON = 0;  // 关闭 TKM 电容充放计数；
   	TKCNTH = 0; // 清TOUCH读数,必须手工清零
   	TKCNTL = 0;
}

void TK0_Release_(void)
{
   	FilterCnt_TK0 = 0;
   	T_Key0_Signal = 0;
   	Pre_T_Key0_Release = 1;	   	   	   	   	
   	u16_TK0_environment_val = u16_TK0_get_val_Temp;;
   	TK0_Filter_Cnt = 0;
   	u16_TK0_environment_val_Sum = 0;

   	TK0_Release_Flag = 1;
   	u16_TK0_get_val_Min = 0xFFFF;
}

void TK0_Scan(void)
{
   	// P10 设为输入，关闭数字IO功能
   	DDR1 |= 0x01;     // 1： 端口作为输入口          0： 端口作为输出口
   	P1ADCR |= 0x01;   // 0 使能端口的数字 I/O 功能； 1 关闭端口的数字 I/O 功能；

   	TKCR1 = 0x00; // 写0000_0000 bit0-1: 00 TK0 选择相应按键输入通道
   	TK_Init();

   	Get_TK_Value();

   	// P10 设为输出，打开数字IO功能
   	DDR1 &= 0xFE;     // 1： 端口作为输入口         0： 端口作为输出口
   	P1ADCR &= 0xFE;   // 1 关闭端口的数字 I/O 功能； 0 使能端口的数字 I/O 功能； 
   	P10D = 0;

   //  	u16_temp_val = u16_get_val + Const_SEN_T_Key0 + 10;
   //  	if(u16_temp_val < u16_TK0_environment_val)
   // {
   //  	   	SleepCnt = 0xff;
   //  	}
    u16_TK0_get_val_Temp = u16_get_val;
   //  	u16_temp_val = u16_TK0_get_val_Temp << 2;
   //  	u16_temp_val -= u16_TK0_get_val_Temp;
   //  	u16_temp_val += u16_get_val;
   //  	u16_TK0_get_val_Temp = u16_temp_val >> 2;
   // u16_get_val = u16_TK0_get_val_Temp;

   	if(Pre_T_Key0_Release) 
   	{
   	   	u16_temp_val = u16_get_val + Const_SEN_T_Key0;
   	   	
   	   	if(u16_temp_val < u16_TK0_environment_val) 	 //按下
   	   	{
   	   	   	SleepCnt = 0xFF;
   	   	   	FilterCnt_TK0 ++;
   	   	   	if(FilterCnt_TK0 > FilterCnt_Value)
   	   	   	{
   	   	   	    T_Key0_Signal = 1;
   	   	   	   	Pre_T_Key0_Release = 0;
   	   	   	   	u16_release_val_TK0 = u16_TK0_environment_val - Const_SEN_T_Key0; //
   	   	   	}
   	   	}
   	   	else //更新环境值
   	   	{
   	   	   	FilterCnt_TK0 = 0;

   	   	   	if(SleepCnt)
   	   	   	{

   	   	   	   	TK0_Filter_Cnt_T ++;
   	   	   	   	
   	   	   	   	if(TK0_Filter_Cnt_T >= 4)
                {
   	   	   	   	   	TK0_Filter_Cnt_T = 0;
   	   	   	   	   	u16_TK0_environment_val_Sum += u16_get_val;

   	   	   	   	   	TK0_Filter_Cnt ++;                 	   	   	   	
       	   	   	   	if(TK0_Filter_Cnt > 7)
       	   	   	   	{
       	   	   	   	   	TK0_Filter_Cnt = 0;
       	   	   	   	   	u16_TK0_environment_val = u16_TK0_environment_val_Sum >> 3;
       	   	   	   	   	u16_TK0_environment_val_Sum = 0;

       	   	   	   	   	if(TK0_Release_Flag)
       	   	   	   	   	{
       	   	   	   	   	   	TK0_Release_Flag = 0;
       	   	   	   	   	   	u16_TK0_environment_val = u16_get_val;
       	   	   	   	   	}
       	   	   	   	}
   	   	   	   	}
   	   	   	}
   	   	   	else
   	   	   	{
   	   	   	   	u16_TK0_environment_val = u16_get_val;
   	   	   	   	u16_TK0_environment_val_Sum = 0;
   	   	   	   	TK0_Filter_Cnt = 0;
   	   	   	}
   	   	   	
   	   	   	if(TK0_Release_Flag == 1)
   	   	   	{
   	   	   	   	if(u16_get_val > u16_TK0_environment_val)
   	   	   	   	{
   	   	   	   	   	u16_TK0_environment_val = u16_get_val;
   	   	   	   	}
   	   	   	}
   	   	}
   	}
   	else  
   	{
   	  //   	FilterCnt_TK0 = 0;

   	   	if(u16_get_val < u16_TK0_get_val_Min)
        {
   	   	   	u16_TK0_get_val_Min = u16_get_val;
        }
   	
   	   	u16_temp_val = u16_release_val_TK0 + Const_SEN_T_Key0 + u16_TK0_get_val_Min;
   	   	u16_temp_val = u16_temp_val >> 1;

   	   	if(u16_get_val > u16_release_val_TK0 || u16_get_val > u16_temp_val)	//松开
   	   	{
   	   	   	FilterCnt_TK0 ++;
   	   	   	if(FilterCnt_TK0 >= 4) //触摸松开滤波 20ms
   	   	   	{
   	   	   	   TK0_Release_(); 	
   	   	   	}
   	   	}
   	   	else
   	   	{
   	   	   	FilterCnt_TK0 = 0;
   	   	}  	
    }  	
}
///////////////////////////////////////////////
void TK1_Release_(void)
{
   	FilterCnt_TK1 = 0;

   	T_Key1_Signal = 0;

   	Pre_T_Key1_Release = 1;	   	   	   	   	
   	u16_TK1_environment_val = u16_TK1_get_val_Temp;
   	TK1_Filter_Cnt = 0;
   	u16_TK1_environment_val_Sum = 0;

   	TK1_Release_Flag = 1;

   	u16_TK1_get_val_Min = 0xFFFF;
}

void TK1_Scan(void)
{
   	// P11 设为输入，关闭数字IO功能
   	DDR1 |= 0x02;     // 1： 端口作为输入口          0： 端口作为输出口
   	P1ADCR |= 0x02;   // 0 使能端口的数字 I/O 功能； 1 关闭端口的数字 I/O 功能；

   	TKCR1 = 0x01; // 写0000_0000 bit0-1: 01 TK1 选择相应按键输入通道
   	TK_Init();

   	Get_TK_Value();

   	// P11 设为输出，打开数字IO功能
   	DDR1 &= 0xFD;     // 1： 端口作为输入口         0： 端口作为输出口
   	P1ADCR &= 0xFD;   // 1 关闭端口的数字 I/O 功能； 0 使能端口的数字 I/O 功能； 
   	P10D = 0;

   //  	u16_temp_val = u16_get_val + Const_SEN_T_Key1 + 10;
   //  	if(u16_temp_val < u16_TK1_environment_val)
   // {
   //  	   	SleepCnt = 0xff;
   //  	}
    u16_TK1_get_val_Temp = u16_get_val;
     //	u16_temp_val = u16_TK1_get_val_Temp << 2;
     //	u16_temp_val -= u16_TK1_get_val_Temp;
     //	u16_temp_val += u16_get_val;
     //	u16_TK1_get_val_Temp = u16_temp_val >> 2;
     // u16_get_val = u16_TK1_get_val_Temp;

   	if(Pre_T_Key1_Release) 
   	{
   	   	u16_temp_val = u16_get_val + Const_SEN_T_Key1;
   	   	
   	   	if(u16_temp_val < u16_TK1_environment_val) 	 //按下
   	   	{
   	   	   	SleepCnt = 0xFF;
   	   	   	FilterCnt_TK1 ++;
   	   	   	if(FilterCnt_TK1 > FilterCnt_Value)
   	   	   	{
   	   	   	    T_Key1_Signal = 1;
   	   	   	   	Pre_T_Key1_Release = 0;
   	   	   	   	u16_release_val_TK1 = u16_TK1_environment_val - Const_SEN_T_Key1; //
   	   	   	}
   	   	}
   	   	else //更新环境值
   	   	{
   	   	   	FilterCnt_TK1 = 0;

   	   	   	if(SleepCnt)
   	   	   	{
   	   	   	   	TK1_Filter_Cnt_T ++;
   	   	   	   	
   	   	   	   	if(TK1_Filter_Cnt_T >= 4)
                {
   	   	   	   	   	TK1_Filter_Cnt_T = 0;
   	   	   	   	   	u16_TK1_environment_val_Sum += u16_get_val;
   	   	   	   	   	TK1_Filter_Cnt++;
                }
   	   	   	   	
   	   	   	   	if(TK1_Filter_Cnt > 7)
   	   	   	   	{
   	   	   	   	   	TK1_Filter_Cnt = 0;
   	   	   	   	   	u16_TK1_environment_val = u16_TK1_environment_val_Sum >> 3;
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
   	   	if(u16_get_val < u16_TK1_get_val_Min)
        {
   	   	   	u16_TK1_get_val_Min = u16_get_val;
        }
   	
   	   	u16_temp_val = u16_release_val_TK1 + Const_SEN_T_Key1 + u16_TK1_get_val_Min;
   	   	u16_temp_val = u16_temp_val >> 1;

   	   	if(u16_get_val > u16_release_val_TK1 || u16_get_val > u16_temp_val)	//松开
   	   	{
   	   	   	FilterCnt_TK1 ++;
   	   	   	if(FilterCnt_TK1 >= 4) //触摸松开滤波 20ms
   	   	   	{
   	   	   	   	TK1_Release_();    	   	   	   	
   	   	   	}
   	   	}
   	   	else
   	   	{
   	   	   	FilterCnt_TK1 = 0;
   	   	}  	
    }  	
}


void TK1_value_Read(void)
{
   	if(T_Key1_Signal && TK1_Key_Release_Flag == 0) //有按键按下
   	{ 
   	   	TK1_Key_Cnt ++;
   	   	   	
        PWM_Change_KeyFlg = 1;

   	   	if(TK1_Key_Cnt == 60) //600ms
   	   	{
   	   	   	TK0_Key_Release_Flag = 1;
   	      //   	TK1_Key_Cnt = 60;  	

   	       	if(TK1_Long_press_Flag == 0)
   	       	{
                TK1_Long_press_Flag = 1;   	//长按标志位置1

       	   	   	PWM_Change_KeyFlg = 1;

                Y_AS_Flag = !Y_AS_Flag;    	//调亮调暗标志位状态变换
   	       	 }
   	   	}  	   	
   	   	
   	}
   	else if(T_Key1_Signal == 0)
    {
        TK1_Long_press_Flag = 0;   	//长按标志位清0

   	   	if(TK1_Key_Cnt > 1 && TK1_Key_Cnt < 60)
   	   	{
            PWM_Change_KeyFlg = 1;

            if (Y_Power_Flag)
            {
                Y_Power_Flag = 0;
            }
            else
            {
                Y_Power_Flag = 1;
            }
   	   	}
   	   	TK1_Key_Release_Flag = 0;
   	   	TK1_Key_Cnt = 0;
    }
}


void TK0_value_Read(void)
{
   	if(T_Key0_Signal && TK0_Key_Release_Flag == 0) //有按键按下
   	{
        TK0_Key_Cnt++;

        PWM_Change_KeyFlg = 1;

         if (TK0_Key_Cnt == 60) //600ms
         {
             TK1_Key_Release_Flag = 1;
             //    	TK1_Key_Cnt = 60;  	

             if (TK0_Long_press_Flag == 0)
             {
                 TK0_Long_press_Flag = 1;  	//长按标志位置1

                 PWM_Change_KeyFlg = 1;

                 W_AS_Flag = !W_AS_Flag;   	//调亮调暗标志位状态变换
             }
         }     	   	           	   	 
   	}
   	else if(T_Key0_Signal == 0)
   	{  	   	
        TK0_Long_press_Flag = 0;

        if (TK0_Key_Cnt > 1 && TK0_Key_Cnt < 60)
        {
            PWM_Change_KeyFlg = 1;
            
            if (W_Power_Flag)
            {
                W_Power_Flag = 0;
            }
            else
            {
                W_Power_Flag = 1;
            }
        }

   	   	TK0_Key_Release_Flag = 0;
        TK0_Key_Cnt = 0;
   	}
}

void PWM_W_OFF(void)
{
   	T1DATD = 0;
   	PWM1DOE = 0; //禁止端口输出脉宽调制波形；
   	PWM1DEN = 0; //关闭 PWM1D 功能；
}

void PWM_Y_OFF(void)
{
   	T1DATC = 0;
   	PWM1COE = 0; //禁止端口输出脉宽调制波形；
   	PWM1CEN = 0; //关闭 PWM1C 功能；
}


void LED_PWM_Control(void)
{
   	if(PWM_Change_KeyFlg == 1)     	//按键值改变更新状态
   	{
   	   	PWM_Change_KeyFlg = 0;

   	   	if(W_Power_Flag == 0)
   	   	{
   	   	   	PWM_W_OFF();   	   	   	
   	   	}
        else
        {
            T1DATD = PWM_Duty_W; //PWM_Duty_W
            PWM1DOE = 1; //打开端口输出脉宽调制波形
            PWM1DEN = 1; //打开 PWM1D 功能 	
        }

        if (Y_Power_Flag == 0)
        {
            PWM_Y_OFF();
        }
        else
        {
            T1DATC = PWM_Duty_Y;
            PWM1COE = 1; //打开端口输出脉宽调制波形
            PWM1CEN = 1; //打开 PWM1D 功能  
        }
   	}


   	if(TK1_Long_press_Flag) //长按无极调光（255极）
   	{
   	   	if(Y_AS_Flag && Y_Power_Flag)      	//逐渐变暗
   	   	{
   	   	   	if(PWM_Duty_Y < 255) //最大亮度 100%
   	   	   	{
   	   	   	   	PWM_Duty_Y ++;
   	   	   	}  	   	   	
   	   	}
   	   	else if(Y_Power_Flag)  	//逐渐变亮
   	   	{  	  
   	   	   	if(PWM_Duty_Y > 12 ) //最小亮度PWM值：255 * 5%，
   	   	   	{
   	   	   	   	PWM_Duty_Y --; 
   	   	   	}
   	   	}
   	}

    if (TK0_Long_press_Flag) //长按无极调光（255极）
    {
        if (W_AS_Flag && W_Power_Flag)     	//逐渐变暗
        {
            if (PWM_Duty_W < 255) //最大亮度 100%
            {
                PWM_Duty_W++;
            }
        }
        else if(W_Power_Flag)  	//逐渐变亮
        {
            if (PWM_Duty_W > 12) //最小亮度PWM值：255 * 8%，
            {
                PWM_Duty_W--;
            }
        }
    }
}


void TK_10S_Reset(void)
{
    if (T_Key0_Signal || T_Key1_Signal)
    {
        u8_TK_Reset_Cnt++;
        if (u8_TK_Reset_Cnt >= 1000) // 10s
        {
            //u8_TK_Reset_Cnt = 0;
            TK0_Release_();
            TK1_Release_();
        }
    }
    else
    {
        u8_TK_Reset_Cnt = 0;
    }

}

// 睡眠模式

void Sleep_mode(void)
{
   	if(SleepCnt) 
   	{
   	   	SleepCnt--;
   	}

   	if(W_Power_Flag || Y_Power_Flag)
   	{
   	   	SleepCnt = 0xFF; // 2.55s
   	}


   	if(!SleepCnt)
   	{

   	   	TKEN = 0;       //关闭TK
   	 //    	CMPCR0 = 0x00;  //关闭CMP

   	   	SLEEP();   //休眠两种编写方式(方式二)

   	 //    	Timer16_Init(); //1ms  //切换定时唤醒时间

   	   	TKEN = 1;  	   //打开TK
   	 //    	CMPCR0 = 0x81;//开启CMP 正：VIR 负:VDD分压电阻 允许CMP端口输出 输出无回滞

   	   	T0_5ms_Flag = 1;
   	   	T0_10ms_Flag = 1;

   	}
}

   	
/************************************************
函数名:主函数
说明:
************************************************/
void main()
{      	                 
   	   	Clr_Ram();
   	   	Init_Sys();

   	   	IO_Init();

   	   	Delay_us_2(0x5020); // 4M 约100ms

   	   	TOUCH_Init(); // 设置触摸寄存器 

   	   	T1_PWM_Init();
   	   	SleepCnt = 0xff;

   	   	PWM_Duty_W = 0xff; // 
   	   	PWM_Duty_Y = 0xff; // 

        W_AS_Flag = 1;
        Y_AS_Flag = 1;
   	   	Pre_T_Key0_Release = 1;
   	   	u16_TK0_get_val_Min = 0xFFFF;
   	   	u16_TK1_get_val_Min = 0xFFFF;

   	   	while(1) 
   	   	{    
   	   	   	if(T0_5ms_Flag)
            {
   	   	   	   	T0_5ms_Flag = 0;

   	   	   	   	TK0_Scan();                                
   	   	   	   	TK1_Scan();    	   	   	   	
                
                
   	   	   	 //   Uart_Send_Data();
            }

   	   	   	if(T0_10ms_Flag) 
            {
   	   	   	   	T0_10ms_Flag = 0;

                TK0_value_Read();
                TK1_value_Read();
 
   	   	   	   	LED_PWM_Control();     	   	   	 
   	   	   	   	                
                TK_10S_Reset();
   	   	       	Sleep_mode();
            }      	   	   	   	

   	   	   	WDT_Clear();
   	   	  //  TOUCH_TK0_OUT();
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
   	   	   	T0CNT = 217; // T0没有自动重载器，

   	   	   	T0_5ms_Flag = 1;
   	   	 //    	T0_5ms_Flag_PWM = 1;

   	   	   	T0_5ms_Cnt ++;
   	   	   	if(T0_5ms_Cnt >= 2)
            {
               	T0_5ms_Cnt = 0;
               	T0_10ms_Flag = 1;
   	   	  //   	   	T0_10ms_Flag_PWM = 1;
            }
       	}

       	if(T1IF)
       	{      	       	
   	   	   	T1IF   = 0; 
//;--------------------------
   	   	  //   	UART_SUB();    	   	   	   	//;串口中断处理
//;--------------------------
       	}

   	__asm
   	SWAPAR 	SAVE_STATUS
   	MOVRA  	STATUS
   	SWAPR  	SAVE_ACC
   	SWAPAR 	SAVE_ACC
   	__endasm;
}



//;****************************************************************************
//;****************************************************************************

