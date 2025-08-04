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

#define  PWM_Max_Value     200 // 200 100%
#define  PWM_Min_Value     58  // 200 10%

//#define  Hall_IN     	  P14D  // 1脚 霍尔输入 低有效  浮空检测
//#define  Hall_EN_IN      	P11D  // 6脚 霍尔选项脚 低有效  上拉输入

// 不跳频  4.8M
#define	   	TK_SENS_LEVEL_H1  0x13     	   	   //;TK0触摸灵敏度级别1
#define	   	TK_SENS_LEVEL_H2  0x13     	   	//;TK0触摸灵敏度级别2
#define	   	TK_SENS_LEVEL_H3  0x15     	   	//;TK0触摸灵敏度级别3
#define	   	TK_SENS_LEVEL_L   0xFF     	   	//;TK0触摸灵敏度级别


#define FilterCnt_Value    	8
#define Const_SEN_T_Key0   	40
//#define Const_SEN_T_Key0_Release  60

// 触摸
// 位定义
#define    	T_Key0_Signal      	flag1.bits.bit0    	   	 // 标志位
#define    	Pre_T_Key0_Release  flag1.bits.bit1	   	 // 标志位
#define    	TK0_Release_Flag    flag1.bits.bit2	   	 // 标志位
#define    	TK0_Filter_Flag     flag1.bits.bit3	   	 // 标志位
#define    	T0_5ms_Flag        	flag1.bits.bit4	   	 // 标志位
#define    	T0_25ms_Flag        flag1.bits.bit5	   	 // 标志位
#define    	T_Long_press_Flag   flag1.bits.bit6	   	 // 标志位
#define    	PWM_Flag_key        flag1.bits.bit7	   	 // 标志位

#define    	Power_ONOFF_Flag       	flag2.bits.bit0    // 标志位
#define    	PWM_Change_KeyFlg      	flag2.bits.bit1    // 标志位
#define    	TK0_Key_Release_Flag    flag2.bits.bit2    // 标志位
#define     T0_5ms_Flag_PWM        	   	flag2.bits.bit3    // 标志位
#define     T0_10ms_Flag_PWM       	   	flag2.bits.bit4    // 标志位
#define    	BAT_Low_V_Flag         	flag2.bits.bit5    // 标志位
#define    	SW1_Short_2_Flag           	  flag2.bits.bit6    // 标志位

//uint8_t T_Key0_Signal;
//uint8_t Pre_T_Key0_Release;
//uint8_t TK0_Release_Flag;

uint16_t u16_TK_Cnt; // 灵敏度

uint16_t u16_get_val;      	   	//读取值
uint16_t u16_Press_val;     //按下
uint16_t u16_release_val;      	//松开
uint16_t u16_release_val_TK0;
uint16_t u16_temp_val;
uint16_t u16_get_val_Temp;
uint16_t u16_get_val_Min;

uint16_t u16_TK0_environment_val;
uint32_t u16_TK0_environment_val_Sum;

///////////////////////////////////////

unsigned char TK0_Filter_Cnt;
//unsigned char TK0_Filter_Flag;
//unsigned char TK0_Release_Cnt;
unsigned char FilterCnt_TK0;
unsigned char SleepCnt = 00;  //睡眠计数


// PWM
//uint8_t PWM_Duty_Temp;
uint8_t PWM_Duty_W;
//uint8_t PWM_Duty_Y;
uint8_t PWM_Duty_WY;
uint8_t PWM_Duty_WY_Temp;
uint8_t T_key_Value; // 0 1 2 3 
uint8_t TK0_Key_Cnt;
uint8_t Power_Low_V_OFF_Cnt;

// 霍尔
//uint8_t Hall_Flag;
//uint8_t Hall_5ms_Cnt_1 = 0;
//uint8_t Hall_5ms_Cnt_2 = 0;


uint8_t T0_5ms_Cnt;


// 串口
#define  Uart_TX     P14D

//#define Uart // 关闭串口

unsigned char uart_send_c = 0;


/************************************************
函数名:   	Init_Sys
说明:
************************************************/

void TOUCH_TK0_OUT(void);

void Delay_us_2(uint16_t i)
{
   	for(; i>0; i--)
    {
   	   	WDT_Clear();
    }
}


void Delay_us(unsigned char i)
{
   	while(i--);
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

   	uart_send_c = u16_TK_Cnt & 0x00FF;
   	Uart_Send_One_Byte();
   	uart_send_c =  (u16_TK_Cnt & 0xff00) >> 8; 
   	Uart_Send_One_Byte();

  //   	uart_send_c = u16_TK_Cnt & 0x00FF;
  //   	Uart_Send_One_Byte();
  //   	uart_send_c =  (u16_TK_Cnt & 0xff00) >> 8; 
  //   	Uart_Send_One_Byte();


}
#endif

void  Init_Sys(void)
{  	   	   	
   	__asm
SET_OPTION:
   	MOVAI   00001111B  	   	//;I/O口数字功能设定,0是有效
   	MOVRA   P1ADCR
   	MOVAI   00111111B  	   	//;P10,P11,P12,P12输入口，P14,P15输入口；1为输入，0为输出
   	MOVRA   DDR1
   	MOVAI   00000000B  	   	//; 端口写0
   	MOVRA   P1
   	
   	MOVAI   0xFF   	   	   	//;下拉电阻,1是无效
   	MOVRA   PDCON

   	MOVAI   0xFF   	   	   	//; 上拉电阻,1是无效
   	MOVRA   PUCON  	   	   	//;

   	MOVAI   0x00   	   	   	//;开漏推挽,1是开漏,0是推挽
   	MOVRA   ODCON

//;定时器设定 
//; T0     	   	   	   	011 256分频(系统时钟再256分频)
    MOVAI   00000111B  	   	//;定时器0配置,BIT0-2:定时器分频,BIT3定时器分配:1-WDT,0-TC0
    MOVRA   T0CR   	   	   	//;BIT4:0-上升沿计数1-下降沿计数,BIT5:时钟源0-FCPU,1-外部;BIT6:1-上升沿触发0-下降沿触发
    MOVAI   217    	   	   	  //;131
    CLRR   	T0CNT  	   	   	//;清定时器0计数值;T0没有自动重载器，所以计数值以256为基准，或者在中断里改变T0CNT值

//; T1 
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
    T1CNT = PWM_Max_Value - 1;
    T1LOAD = PWM_Max_Value - 1;    	   	//30k
//    T1DATA = 0;
//    T1DATB = 0;
//    T1DATC = 0;
// 	  T1DATD = 0;

   	T1DATD = 0;
   	PWM1DOE = 0; //禁止端口输出脉宽调制波形；
   	PWM1DEN = 0; //关闭 PWM1D 功能；

   	T1DATC = 0;
   	PWM1COE = 0; //禁止端口输出脉宽调制波形；
   	PWM1CEN = 0; //关闭 PWM1C 功能；

   	T1DATB = 0;
   	PWM1BOE = 0; //禁止端口输出脉宽调制波形；
   	PWM1BEN = 0; //关闭 PWM1B 功能；

    // 高电平时间 =（T2DATx） × T2CNT 计数时钟周期
    // 周期（T2 的溢出周期） =（T2LOAD+1） × T2CNT 计数时钟周期
    // 占空比 = 高电平时间 / 周期 =（T2DATx） /（T2LOAD+1）
    //  PWM1CR0 = 0x03;   //PWM1A端口输出PWM、正向输出
                          //PWM1B端口输出PWM、正向输出
}



void IO_Init(void)
{
   	P1 = 0x00; //  	P1nD – P1n 端口数据位（n=5-0）

   	//xx11_1011;   	0 输出   1输入
   	DDR1 = 0x33;   	   // DR1n – P1n 端口方向控制位（n=5-0）  0： 端口作为输出口
   	//  P12   输出口  P10 P11 P13 P14 P15输入


   	// xx11_0011
   	P1ADCR = 0x33;   // 0 使能端口的数字 I/O 功能； 1 关闭端口的数字 I/O 功能；
   	
   	// 1111_1101 P11
   	PUCON = 0xFF; //  1：端口内部上拉电阻无效；  0：端口内部上拉电阻有效
   	PDCON = 0xFF; //  1：端口内部下拉电阻无效；  0：端口内部下拉电阻有效

   	ODCON = 0x00; // 0： 端口输出时为推挽输出   1 开漏输出
}


//void TK_Sens_Threshold_value_Detection(void)
//{
//     	u16_TK_Cnt = 0;
//
//     	DDR1 &= 0xDF; // P15 设输出 0 输出
//     	PUCON |= 0x20; //  1：端口内部上拉电阻无效；  0：端口内部上拉电阻有效
//     	PDCON |= 0x20; //  1：端口内部下拉电阻无效；  0：端口内部下拉电阻有效
//     	P15D = 0;
//
//     	Delay_us(0xff); //
//
//     	DDR1 |= 0x20; // P15 设输出  1 输入
//     	
//     	P1ADCR &= 0xDF;   // 0 使能端口的数字 I/O 功能； 1 关闭端口的数字 I/O 功能；
//     	PUCON &= 0xDF; 	  //  1：端口内部上拉电阻无效；  0：端口内部上拉电阻有效
//
//     	while(P15D == 0)
//    {
//     	   	u16_TK_Cnt ++;
//     	 //   if(u16_TK_Cnt == 20000)
//      //  {
//     	  //       	   	break;
//      //  }
//     	 //    	WDT_Clear();
//    }
//     	   	   	   	   	   	   	   	   	// LDO 3.3V
//     	if(u16_TK_Cnt > 250) // 47nF
//    {
//     	   	T2LOADH = TK_SENS_LEVEL_H3;
//     	   	T2LOADL = TK_SENS_LEVEL_L;
//    }
//    else if(u16_TK_Cnt > 180)// 27nF
//    {
//     	   	T2LOADH = TK_SENS_LEVEL_H2;
//     	   	T2LOADL = TK_SENS_LEVEL_L;
//    }
//    else if(u16_TK_Cnt > 50) //10NF
//    {
//     	   	T2LOADH = TK_SENS_LEVEL_H1;
//     	   	T2LOADL = TK_SENS_LEVEL_L;
//    }
//     	else //if(u16_TK_Cnt > )
//    {
//     	   	T2LOADH = TK_SENS_LEVEL_H1;
//     	   	T2LOADL = TK_SENS_LEVEL_L;
//    }
//     	
//     	Delay_us(0xff); //
//     	Delay_us(0xff); //
//
//     	PUCON |= 0x20;  //  1：端口内部上拉电阻无效；  0：端口内部上拉电阻有效
//     	DDR1 &= 0xDF;   // P15 设输出 0 输出
//}

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

void TK0_Init(void)
{

   	TKCR1 = 0x00; // 关闭触摸
   	TKCNTH = 0;
   	TKCNTL = 0;

   	T2MOD = 1;   // 单次计时模式（触摸模式）
   // T2CR = 0x49; // 01_0_01_000 FOSC 2分频
   	T2CR = 0x4A;   // 01_0_01_010 FOSC 16M 4分频 4M

//     	T2LOADH = 0x08;
//     	T2LOADL = 0xFF;

       	T2LOADH = TK_SENS_LEVEL_H1;
       	T2LOADL = TK_SENS_LEVEL_L;
//     	T2LOADH = 0x52; // 101:5 抖频  400 1024
//     	T2LOADL = 0xFF;

   	TKCR1 &= 0xFC; // 写0000_0000 bit0-1: 00 TK0 选择相应按键输入通道

   	TKCR0 = 0xF4;  // 写1111_0000 bit0-3: 000 TK0 选择 4.8MHz

 //    	TKCFL = 0; 	   // TKM 计数时钟滤波时间（典型值）为 10ns；
   	TKCFL = 1; 	 // TKM 计数时钟滤波时间（典型值）为 50ns；

 //    	TKFJE = 1; 	// 开启 TKM 自动跳频功能
   	TKFJE = 0; 	// 关闭 TKM 自动跳频功能
   	T2EN = 1;  	// 开启定时器 T2
   	TKCON = 1; 	// 允许 TKM 电容充放计数
   	TKEN = 1;  	// 开启 TKM      	   	
   	
}

void TK0_release_(void)
{
   	T_Key0_Signal = 0;

   	Pre_T_Key0_Release = 1;	   	   	   	   	
   	u16_TK0_environment_val = u16_get_val;
   	TK0_Filter_Cnt = 0;
   	u16_TK0_environment_val_Sum = 0;

   	TK0_Release_Flag = 1;

   	u16_get_val_Min = 0xFFFF;
}

void TK0_Scan(void)
{
   	// P10 设为输入，关闭数字IO功能
   	DDR1 |= 0x01;     // 1： 端口作为输入口          0： 端口作为输出口
   	P1ADCR |= 0x01;   // 0 使能端口的数字 I/O 功能； 1 关闭端口的数字 I/O 功能；

   	TK0_Init();

   	while(TKCF == 1)
    {
   	   	WDT_Clear();
    }
    u16_get_val =  (TKCNTH << 8) | TKCNTL;

   	TKCON = 0;  // 关闭 TKM 电容充放计数；
   	TKCNTH = 0; // 清TOUCH读数,必须手工清零
   	TKCNTL = 0;

   	// P10 设为输出，打开数字IO功能
   	DDR1 &= 0xFE;     // 1： 端口作为输入口         0： 端口作为输出口
   	P1ADCR &= 0xFE;   // 1 关闭端口的数字 I/O 功能； 0 使能端口的数字 I/O 功能； 
   	P10D = 0;

   	u16_temp_val = u16_get_val + Const_SEN_T_Key0 - 10;
   	if(u16_temp_val < u16_TK0_environment_val)
    {
   	   	SleepCnt = 0xff;
   	}

   	u16_temp_val = u16_get_val_Temp << 2;
   	u16_temp_val -= u16_get_val_Temp;
   	u16_temp_val += u16_get_val;
   	u16_get_val_Temp = u16_temp_val >> 2;

    u16_get_val = u16_get_val_Temp;

   	if(Pre_T_Key0_Release) 
   	{
   	   	u16_Press_val = u16_get_val + Const_SEN_T_Key0;
   	   	
   	   	if(u16_Press_val < u16_TK0_environment_val)	 //按下
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
   	   	   	   	if(TK0_Filter_Flag)
   	   	   	   	{
   	   	   	   	   	TK0_Filter_Flag = 0;
   	   	   	   	}
   	   	   	   	else
                {
   	   	   	   	   	TK0_Filter_Flag = 1;
   	   	   	   	   	u16_TK0_environment_val_Sum += u16_get_val;
   	   	   	   	   	TK0_Filter_Cnt++;
                }
   	   	   	   	
   	   	   	   	if(TK0_Filter_Cnt > 15)
   	   	   	   	{
   	   	   	   	   	TK0_Filter_Cnt = 0;
   	   	   	   	   	u16_TK0_environment_val = u16_TK0_environment_val_Sum >> 4;
   	   	   	   	   	u16_TK0_environment_val_Sum = 0;

   	   	   	   	   	if(TK0_Release_Flag)
   	   	   	   	   	{
   	   	   	   	   	   	TK0_Release_Flag = 0;
   	   	   	   	   	   	u16_TK0_environment_val = u16_get_val;
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

   	   	TK0_Filter_Cnt++;

   	   	if(TK0_Filter_Cnt >= 2) // 10ms
   	   	{
   	   	   	TK0_Filter_Cnt = 0;

   	   	   	if(u16_get_val <= u16_TK0_environment_val) //必须小于等于，不能只小于
   	   	   	{
   	   	   	   	u16_TK0_environment_val = u16_get_val;
   	   	   	}
   	   	   	else
   	   	   	{
   	   	   	   	u16_TK0_environment_val ++;
   	   	   	}

   	   	   	if(u16_get_val < u16_get_val_Min)
            {
   	   	   	   	u16_get_val_Min = u16_get_val;
            }
   	   	}

   //  	   	if(u16_get_val > u16_TK0_environment_val)
   //  	   	{
   //  	   	   	u16_release_val = u16_get_val - u16_TK0_environment_val;   	
   //  	   	}
   //  	   	else
   //  	   	{
   //  	   	   	u16_release_val = 0;
   //  	   	}
   	   	u16_temp_val = u16_release_val_TK0 + Const_SEN_T_Key0 + u16_get_val_Min;
   	   	u16_temp_val = u16_temp_val >> 1;

   	   	if(u16_get_val > u16_release_val_TK0 || u16_get_val > u16_temp_val)	//松开
   	   	{
   	   	   	FilterCnt_TK0 ++;
   	   	   	if(FilterCnt_TK0 >= 4) //触摸松开滤波 20ms
   	   	   	{
   	   	   	   	FilterCnt_TK0 = 0;

   	   	   	   	TK0_release_();
   	   	   	}
   	   	}
   	   	else
   	   	{
   	   	   	FilterCnt_TK0 = 0;
   	   	}  	
    }  	
}
///////////////////////////////////////////////

void PWM_Direction_Judgment(void)
{
   	if(PWM_Duty_W > 100) // 200 max
   	{
   	   	PWM_Flag_key = 1;  //调亮调暗标志位状态变换
   	}
   	else
   	{
   	   	PWM_Flag_key = 0;  //调亮调暗标志位状态变换
   	} 
}

uint8_t Key1PressCnt_Short;
//uint8_t SW1_Short_2_Flag;

void T_Key_value_Read(void)
{
   	if(T_Key0_Signal && TK0_Key_Release_Flag == 0) //有按键按下
   	{
   	   	TK0_Key_Cnt ++;

   	   	if(TK0_Key_Cnt == 100 && Power_ONOFF_Flag) //500ms
   	   	{
   	   	   	TK0_Key_Release_Flag = 1;

   	      //   	TK0_Key_Cnt = 60;  	
       	   	TK0_Key_Release_Flag = 1; 

   	       	if(T_Long_press_Flag == 0)
   	       	{
       	   	   	T_Long_press_Flag = 1; 	//长按标志位置1

       	   	   	PWM_Change_KeyFlg = 1;

       	   	   	PWM_Flag_key = !PWM_Flag_key;  	//调亮调暗标志位状态变换
   	       	 }
   	   	}
   	}
   	else if(!T_Key0_Signal)
   	{
   	   	T_Long_press_Flag = 0; 	//长按标志位清0

   	   	if(TK0_Key_Cnt > 1 && TK0_Key_Cnt < 100) // 500ms 
   	   	{  	   	
   	   	   	SW1_Short_2_Flag = 1;  	  

   	   	   	if(Key1PressCnt_Short > 0 && Key1PressCnt_Short < 50) //两次间隔小于0.35s，  双击
   	   	   	{
   	   	   	   	SW1_Short_2_Flag = 0;
   	   	
           	   	Power_ONOFF_Flag = 0;  // 双击关机 
   	   	   	   	PWM_Change_KeyFlg = 1;         	  
   	   	   	   	   	
   	   	   	  //   	PWM_Direction_Judgment();  	   	   	   	   	   	   	   	
   	   	   	}

   	   	   	Key1PressCnt_Short = 0;
   	   	}

   	   	TK0_Key_Cnt = 0;   	// 按下累加值清0
   	   	TK0_Key_Release_Flag = 0;

   	   	if(SW1_Short_2_Flag == 1)  // 短按松开计时
   	   	{
   	   	   	Key1PressCnt_Short ++; 

   	   	   	if(Key1PressCnt_Short >= 10 && Power_ONOFF_Flag == 0 ) //单次按下大约0.4s后无操作，  单击
   	   	   	{
   	   	   	   	Power_ONOFF_Flag = 1;    // 短按开机
   	   	   	   	Key1PressCnt_Short = 0;
   	   	   	   	SW1_Short_2_Flag = 0;

   	   	   	   	PWM_Change_KeyFlg = 1;
   	   	   	   	PWM_Direction_Judgment();
   	   	   	}

   	   	   	if(Key1PressCnt_Short >= 50 ) //单次按下大约0.4s后无操作，  单击
   	   	   	{
   	   	   	   	SW1_Short_2_Flag = 0;
   	   	   	   	Key1PressCnt_Short = 0;
   	   	   	   	
   	   	   	   	if(Power_ONOFF_Flag == 0)
                {
   	   	   	   	   	Power_ONOFF_Flag = 1; // 短按开机
                }
                else 
                {  	   	   	   	
       	   	   	   	T_key_Value ++;
       	   	   	   	if(T_key_Value > 3) // 三色
       	   	   	   	{
       	   	   	   	   	T_key_Value = 1;
       	   	   	   	}
   	   	   	   	}
   	   	   	   	
   	   	   	   	PWM_Change_KeyFlg = 1;
   	   	   	   	PWM_Direction_Judgment();
   	   	   	}
   	   	}
   	   	
   	   	TK0_Key_Release_Flag = 0;
   	   	TK0_Key_Cnt = 0;   	//触摸按下累加值清0
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

   	   	if(Power_ONOFF_Flag == 0) //全关
   	   	{
   //  	   	   	PWM_Duty_W = 127; // 不带亮度记忆
   //  	   	   	if(PWM_Duty_Temp)
   //         {
   //  	   	   	   	PWM_Duty_Temp --;
   //  	   	   	   	T1DATD = PWM_Duty_Temp; //PWM_Duty_W
   //         }
   //  	   	   	else
   //         {
   //  	   	   	   	PWM_W_OFF();
   //  	   	   	   	PWM_Change_KeyFlg = 0;
   //         }
   	   	   	PWM_W_OFF();
   	   	   	PWM_Y_OFF();
   	   	}
   	   	else if(T_key_Value == 3)      	// W
   	   	{
   	   	  //   	PWM_W_OFF();
   	   	   	PWM_Y_OFF();

   	   	  //   	T1DATD = PWM_Duty_Temp; //PWM_Duty_W
   	   	  //   	   	PWM_Duty_Temp = 150;
   	   	  //   	   	PWM_Duty_W = 178;
   	   	  //   	   	u16_temp_val = PWM_Duty_Temp * PWM_Duty_W;
   	   	  //   	    PWM_Duty_Temp =    	u16_temp_val >> 8;

   	   	   	u16_temp_val = PWM_Duty_W * 108; //42% x 0XFF
   	   	    PWM_Duty_WY_Temp = u16_temp_val >> 8;

   	   	   	T1DATD = PWM_Duty_WY_Temp; //PWM_Duty_W
   	   	   	PWM1DOE = 1; //打开端口输出脉宽调制波形
   	   	   	PWM1DEN = 1; //打开 PWM1D 功能 	
   	   	}

   	   	else if(T_key_Value == 2)      	// Y
   	   	{
   	   	       	PWM_W_OFF();
   	   	  //   	PWM_Y_OFF();
   	   	 //    	u16_temp_val = PWM_Duty_W * 108; //42% x 0XFF
   	   	    PWM_Duty_WY_Temp = u16_temp_val >> 8;

   	       	 T1DATC = PWM_Duty_WY_Temp; 
   	       	  PWM1COE = 1; //打开端口输出脉宽调制波形
   	       	  PWM1CEN = 1; //打开 PWM1D 功能   	
   	   	}

   	   	else if(T_key_Value == 1)      	// WY  50%
   	   	{
   	   	 //    	PWM_W_OFF();
   	   	  //   	PWM_Y_OFF();
   	   	 //    	PWM_WY_OFF();
   	
   	   	 //    	  PWM_Duty_WY_Temp = 167; // 80% 255
   	   	      u16_temp_val = PWM_Duty_W * 132; //51% x 0XFF
   	   	      PWM_Duty_WY_Temp = u16_temp_val >> 8;

       	   	//     	PWM_Duty_WY_Temp = PWM_Duty_WY >> 1;

       	   	   	T1DATD = PWM_Duty_WY_Temp;
       	   	   	PWM1DOE = 1; //打开端口输出脉宽调制波形
       	   	   	PWM1DEN = 1; //打开 PWM1D 功能 	 

       	   	   	T1DATC = PWM_Duty_WY_Temp;
       	   	   	PWM1COE = 1; //打开端口输出脉宽调制波形
       	   	   	PWM1CEN = 1; //打开 PWM1D 功能 	   	
   	   	}
   	}


   	if(T_Long_press_Flag) //长按无极调光（255极）
   	{
   	   	PWM_Change_KeyFlg = 1;

   	   	if(PWM_Flag_key )  	//逐渐变暗
   	   	{
   	   	   	
   	   	   	if(PWM_Duty_W < PWM_Max_Value) //最大亮度 100%
   	   	   	{
   	   	   	   	PWM_Duty_W ++;
   	   	   	}
   	   	   	
   	   	   	
   	   	}
   	   	else   	//逐渐变亮
   	   	{  	   	   	   	
   	   	   	if(PWM_Duty_W > PWM_Min_Value ) //最小亮度PWM值：255 * 8%，
   	   	   	{
   	   	   	   	PWM_Duty_W --; 
   	   	   	}  	   	  
   	   	}
   	}
}

void TK_3S_Reset(void)
{
   	if(T_Key0_Signal)
    {
   	   	Power_Low_V_OFF_Cnt ++;

   	   	if(Power_Low_V_OFF_Cnt >= 255) // 25ms 6S
        {
   	   	   	Power_Low_V_OFF_Cnt = 0;

   	   	   	TK0_release_();
        }
    }
    else
    {
   	   	Power_Low_V_OFF_Cnt = 0;
    }
}

// 睡眠模式

void Sleep_mode(void)
{
   	if(SleepCnt) 
   	{
   	   	SleepCnt--;
   	}

   	if(T_key_Value || T_Key0_Signal)
   	{
   	   	SleepCnt = 0xFF; // 
   	}


   	if(!SleepCnt)
   	{

   	   	TKEN = 0;       //关闭TK
   	 //    	CMPCR0 = 0x00;  //关闭CMP

   	   	SLEEP();   //休眠两种编写方式(方式二)

   	 //    	Timer16_Init(); //1ms  //切换定时唤醒时间

   	   	TKEN = 1;  	   //打开TK
   	 //    	CMPCR0 = 0x81;//开启CMP 正：VIR 负:VDD分压电阻 允许CMP端口输出 输出无回滞

   	//     	T0_5ms_Flag = 1;
   //  	   	T0_25ms_Flag = 1;

   	}
}

/************************************************
;  *    @函数名            : CMP_Init
;  *    @说明              : 比较器初始化
;  *    @输入参数          :
;  *    @返回参数          :
;  ***********************************************/
void CMP_Init(void)
{
    CMPCR0 = 0x80;//开启CMP 正：VIR 负:VDD分压电阻 允许CMP端口输出 输出无回滞
    CMPCR1 = 0x1E;//检测值2.6V 
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    CMPCR2 = 0x02;           //中断,上升沿触发    电压高到低
  //   	CMPCR2 = 0x06;           //中断,下降沿触发  电压低到高
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

   	   	Delay_us_2(0x8003); // 4M 约100ms

   	//     	TK_Sens_Threshold_value_Detection();

   	   	TOUCH_Init(); // 设置触摸寄存器 

   	   	T1_PWM_Init();
   	   	SleepCnt = 0xff;
   	 //    	PWM_Duty = 0xff;

   	   	PWM_Flag_key = 1;
   	   	PWM_Duty_W = PWM_Max_Value; // 
   	//     	PWM_Duty_Y = PWM_Max_Value;
   	//     	PWM_Duty_WY = PWM_Max_Value;

   	   	Power_ONOFF_Flag = 0;
   	   	T_key_Value = 1; // Power_ONOFF_Flag

   	   	Pre_T_Key0_Release = 1;
   	   	u16_get_val_Min = 0xffff;

   	//     	CMP_Init();

   	   	while(1) 
   	   	{    
   	   	   	if(T0_5ms_Flag)
            {
   	   	   	   	T0_5ms_Flag = 0;

   	   	   	   	TK0_Scan();

   	   	   	 //   Uart_Send_Data();

   	   	   	   	T_Key_value_Read();

            }

   	   	   	if(T0_25ms_Flag) 
            {
   	   	   	   	T0_25ms_Flag = 0;
   	   	   	   	
   	   	   	   	LED_PWM_Control(); 
   	   	   	   	
   	   	   	   	TK_3S_Reset();
   	   	   	   	
   	   	   //      	Sleep_mode();
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


//========= CMP中断 ==============  
    if ((CMPIE) && (CMPIF))
        {
           // P11D = !P11D;
            CMPIF = 0;

   	   	   	  //    CMPCR2 = 0x02;           //中断,上升沿触发    电压高到低
   	   	   	//     	CMPCR2 = 0x06;           //中断,下降沿触发  电压低到高

   	   	   	if(BAT_Low_V_Flag == 0)
            {
   	   	   	   	BAT_Low_V_Flag = 1;
   	   	   	    CMPCR2 = 0x06;           //中断,下降沿触发  电压低到高 	
            }
   	   	   	else if(BAT_Low_V_Flag)
            {
   	   	   	   	BAT_Low_V_Flag = 0;
   	   	   	    CMPCR2 = 0x02;           //中断,下降沿触发  电压低到高 	
            }
   	   	

   	   	  //   	Power_ONOFF_Flag = 0;
   	   	  //   	PWM_Change_KeyFlg = 1;
        }

//========= T0/T1中断 ==============     	
       	if(T0IF)
       	{      	       	
   	   	   	T0IF   = 0; 
   	   	   	T0CNT = 217; // T0没有自动重载器，

   	   	   	T0_5ms_Flag = 1;
   	   	 //    	T0_5ms_Flag_PWM = 1;

   	   	   	T0_5ms_Cnt ++;
   	   	   	if(T0_5ms_Cnt >= 5)
            {
               	T0_5ms_Cnt = 0;
               	T0_25ms_Flag = 1;
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

/************************************************
函数名:触摸响应输出程序
说明:
************************************************/
//void TOUCH_TK0_OUT(void)
//{
////-----------------TK0 -------------------
//     	if(T_Key0_Signal)
//    {
//     	   	LED_R = 1;
//    }
//     	else
//    {
//     	   	LED_R = 0;
//    }
//
//}

//;****************************************************************************
//;****************************************************************************

