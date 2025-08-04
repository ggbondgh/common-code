#include "Define.h"
#include "User.h"

/* 函数名
CLR_RAM(void)
IO_Init(void)
TIMER0_INT_Init(void)
TIMER1_INT_Init(void)
TIMER2_INT_Init(void)
TIMER3_INT_Init(void)
ADC_Init(void)
delay(uint16_t num)
*/

//分频定义
#define  PRS_1   0
#define  PRS_2   1
#define  PRS_4   2
#define  PRS_8   3
#define  PRS_16  4
#define  PRS_32  5
#define  PRS_64  6
#define  PRS_128 7

/************************************************
;  *    @函数名          : CLR_RAM
;  *    @说明            : 清RAM
;  *    @输入参数        :
;  *    @返回参数        :
;  ***********************************************/
void CLR_RAM(void)
{
    for (FSR0 = 0; FSR0 < 0xff; FSR0++)
    {
        INDF0 = 0x00;
    }
    FSR0 = 0xFF;
    INDF0 = 0x00;
}
/************************************************
;  *    @函数名            : IO_Init
;  *    @说明              : IO初始化
;  *    @输入参数          :
;  *    @返回参数          :
;  ***********************************************/
void IO_Init(void)
{
    IOP0 = 0x00;                       //io口数据位
    OEP0 = 0xff;                       //io口方向 1:out  0:in
    PUP0 = 0x00;                       //io口上拉电阻   1:enable  0:disable
    PDP0 = 0x00;                       //io口下拉电阻   1:enable  0:disable
   
    IOP1 = 0x00;                       //io口数据位
    OEP1 = 0xF7;                       //io口方向 1:out  0:in
    PUP1 = 0x00;                       //io口上拉电阻   1:enable  0:disable
    PDP1 = 0x00;                       //io口下拉电阻   1:enable  0:disable
    
    PMOD = 0x07;                       //bit2-bit0 P13、P01、P00 io端口输出模式  1:推挽输出 0:开漏输出
                                       
    DRVCR = 0x00;                      //普通驱动

    P1KBCR = 0x08;                      //P1才有IO唤醒功能  P17~P10
}

/************************************************
;  *    @函数名            : TIMER0_INT_Init
;  *    @说明              : 定时器0初始化
;  *    @输入参数          :
;  *    @返回参数          :
使用Fcpu，中断时间= T0LOAD*（分频/Fcpu）=100*(4/4) =100us
;  ***********************************************/
void TIMER0_INT_Init(void)
{
    T0CR = PRS_4; //CPU,4分频
    T0CNT = 104-1;
    T0LOAD = 104 -1;                 
    T0EN = 1;
    T0IE = 1;
}

/************************************************
;  *    @函数名            : TIMER1_INT_Init
;  *    @说明              : 定时器1初始化
;  *    @输入参数          :
;  *    @返回参数          :
使用Fcpu，中断时间= T1LOAD*（分频/Fcpu）=250*(32/4) =2ms
;  ***********************************************/
void TIMER1_INT_Init(void)
{
    T1CR = PRS_32; //定时模式,CPU,32分频
    T1CNT = 250 -1;                 
    T1LOAD = 250 -1;
    T1EN = 1;
    T1IE = 1;
}

/************************************************
;  *    @函数名            : TIMER2_INT_Init
;  *    @说明              : 定时器2初始化
;  *    @输入参数          :
;  *    @返回参数          :
使用Fcpu，中断时间= T2LOAD*（分频/Fcpu）=100*(8/4) =200us
;  ***********************************************/
void TIMER2_INT_Init(void)
{
    T2CR = PRS_8;   //CPU,8分频
    T2CNT = 100 - 1;
    T2LOAD = 100 - 1;                 
    T2EN = 1;
    T2IE = 1;
}

/************************************************
;  *    @函数名            : TIMER3_INT_Init
;  *    @说明              : 定时器3初始化
;  *    @输入参数          :
;  *    @返回参数          :
使用Fcpu，中断时间= T3LOAD*（分频/Fcpu）=250*(128/4) =8ms
;  ***********************************************/
void TIMER3_INT_Init(void)
{
    T3CR = PRS_128;               //CPU,128分频
    T3CNT = 250 - 1;
    T3LOAD = 250 - 1;                  
    T3EN = 1; 
    T3IE = 1;
}

/************************************************
;  *    @函数名            : TIMER0_PWM_Init
;  *    @说明              : 定时器0,PWM初始化
;  *    @输入参数          :
;  *    @返回参数          :
;  PWM频率 =Fpcu/分频/T0CNT =4000/4/100 = 10KHz
;  PWM占空比 =T0DATA/T0CNT = 25/100 = 25%
;  PWM0: P02/P16
;  ***********************************************/
void TIMER0_PWM_Init(void)
{
    T0CR = DEF_SET_BIT6 | PRS_4;     //使能PWM,CPU,4频
    T0CNT = 100-1;
    T0LOAD = 100-1;                                        
    T0DATA = 25;
    PWMCR0 = 0x00;                                         //正向输出
    PWMCR1 = 0x00;                                         //普通模式
    //PWMCR3 = DEF_SET_BIT2;                                 //P02端口输出
    PWMCR3 = DEF_CLR_BIT2;                                 //P16端口输出
    T0EN = 1;
}

/************************************************
;  *    @函数名            : TIMER1_PWM_Init
;  *    @说明              : 定时器1,PWM初始化
;  *    @输入参数          :
;  *    @返回参数          :
;  PWM频率 =Fpcu/分频/T1CNT =4000/4/100 = 10KHz
;  PWM占空比 =T1DATA/T1CNT = 25/100 = 25%
;  PWM1: P17
;  FPWM1: P16
;  ***********************************************/
void TIMER1_PWM_Init(void)
{
    T1CR = DEF_SET_BIT6 | PRS_4;                    //使能PWM,CPU,4分频
    T1CNT = 100-1;
    T1LOAD = 100-1;                                                  
    T1DATA = 25;
    //PWMCR0 |= DEF_SET_BIT7 | DEF_SET_BIT3 | DEF_SET_BIT2 | DEF_SET_BIT0;  //使能FPWM，正向输出，死区4个时钟

    PWMCR1 = 0x00;                                                        //普通模式
    T1EN = 1;
}

/************************************************
;  *    @函数名            : TIMER2_PWM_Init
;  *    @说明              : 定时器2,PWM初始化
;  *    @输入参数          :
;  *    @返回参数          :
;  PWM频率 =Fpcu/分频/T2CNT =4000/4/100 = 10KHz
;  PWM占空比 =T2DATA/T2CNT = 25/100 = 25%
;  PWM2: P15
;  FPWM2: P14
;  NPWM1: P11
;  NFPWM1: P12
;  ***********************************************/
void TIMER2_PWM_Init(void)
{
    T2CR = DEF_SET_BIT6 | PRS_1 | DEF_SET_BIT3;     //使能PWM,CPU,4分频
    T2CNT = 159-1;
    T2LOAD = 159-1;                                     
    T2DATA = 25;
    PWMCR1 = DEF_SET_BIT4; 
    PWMCR2 = 0x03;                                         //4个时钟
    PWMCR3 |= 0x00;//DEF_SET_BIT6 | DEF_SET_BIT5 | DEF_SET_BIT4;  //使能FPWM,NPWM,正向输出
    T2EN = 1;
}

/************************************************
;  *    @函数名            : ADC_Init
;  *    @说明              : ADC初始化
;  *    @输入参数          :
;  *    @返回参数          :
;  ***********************************************/
void ADC_Init(void)
{
    //OEP1 &= DEF_CLR_BIT0;                        //P10为输入口
    OEP0 &= DEF_CLR_BIT4;                        //P01为输入口 

    ADIOS0 = 0x08;                     //io类型选择  1:模拟输入  0:通用io
//bit7~0  P12 P11 P10 P05 P04 P03 P02 P00

   	ADIOS1 = 0x00;                     //io类型选择  1:模拟输入  0:通用io
//bit1~0  P15 P14 

    PMOD = 0x07;                       //bit7-bit5 P17、P13、P01 io类型选择 1:模拟输入  0:通用io 
                                       //bit2-bit0 P13、P01、P00 io端口输出模式  1:推挽输出 0:开漏输出

    ADCR0 = 0xfb;                                //使能ADC、12位数据H8L4
    ADCR1 = 0x80;                                //32分频、内部2V 
    ADCR2 = 0xff;                                //固定为15ADCLK 
    Set_ADC_Channel(3);         // ADC 使能  AD转换通道开启  通道  CHX
}

/*
ADCHS[3:0]   ADC模拟输入通道
0000  0          AN0    P00
0001  1          AN1    P02
0010  2          AN2    P03
0011  3          AN3    P04
0100  4          AN4    P05
0101  5          AN5    P10
0110  6          AN6    P11
0111  7          AN7    P12
1000  8          AN8    P14
1001  9          AN9    P15
1010  10         VDD/4  
1011  11         EVN0/4 P01
1100  12         EVN1/4 P13
1101  13
1110  14         GND
1111  15         AN10   P17
*/

/************************************************
;  *    @函数名            : delay
;  *    @说明              : 不精确延时函数
;  *    @输入参数          :
;  *    @返回参数          :
;  ***********************************************/
void delay(uint16_t num)
{
   	u16 i;
    for (i = 0; i < num; i ++)
    {
        Nop();
    }
}

