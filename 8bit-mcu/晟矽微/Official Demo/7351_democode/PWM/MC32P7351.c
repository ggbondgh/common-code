/******************************************************************************
;  *       @型号                 : MC32P7351
;  *       @创建日期             : 2022.12.16
;  *       @公司/作者            : sinomcu.com-FAE
;  *       @晟矽微技术支持       : 2048615934
;  *       @晟矽微官网           : http://www.sinomcu.com/
;  *       @版权                 : 2022 sinomcu.com公司版权所有.
;  *----------------------摘要描述---------------------------------
;  *               TIMER0 P02输出波形，F=10k,D=25%
;  *               TIMER1 P16、P17输出互补波形，F=10k,D=25%,DT=4us
;  *               TIMER2 P11、P12、P14、P15输出两组互补波形，F=10k,D=25%,DT=4us                                              
******************************************************************************/

#include "user.h"

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
    OEP0 = 0xFF;                       //io口方向 1:out  0:in
    PUP0 = 0x00;                       //io口上拉电阻   1:enable  0:disable
    PDP0 = 0x00;                       //io口下拉电阻   1:enable  0:disable
    ADIOS0 = 0x00;                     //端口的数字功能    1：disable

    IOP1 = 0x00;                       //io口数据位
    OEP1 = 0xFF;                       //io口方向 1:out  0:in
    PUP1 = 0x00;                       //io口上拉电阻   1:enable  0:disable
    PDP1 = 0x00;                       //io口下拉电阻   1:enable  0:disable
    ADIOS1 = 0x00;                     //端口的数字功能    1：disable

    PMOD = 0x07;                       //bit7-bit5 P17、P13、P01 io类型选择 1:模拟输入  0:通用io 
                                       //bit2-bit0 P13、P01、P00 io端口输出模式  1:推挽输出 0:开漏输出
    DRVCR = 0x80;                      //普通驱动
}
/************************************************
;  *    @函数名            : TIMER0_PWM_Init
;  *    @说明              : 定时器0,PWM初始化
;  *    @输入参数          :
;  *    @返回参数          :
;  ***********************************************/
void TIMER0_PWM_Init(void)
{
    T0CR = DEF_SET_BIT6 | DEF_SET_BIT0 | DEF_SET_BIT1;     //使能PWM,CPU,8频
    T0CNT = 100-1;
    T0LOAD = 100-1;                                        //100us
    T0DATA = 25;
    PWMCR0 = 0x00;                                         //正向输出
    PWMCR1 = 0x00;                                         //普通模式
    PWMCR3 = DEF_SET_BIT2;                                 //P02端口输出
    T0EN = 1;
}

/************************************************
;  *    @函数名            : TIMER1_PWM_Init
;  *    @说明              : 定时器1,PWM初始化
;  *    @输入参数          :
;  *    @返回参数          :
;  ***********************************************/
void TIMER1_PWM_Init(void)
{
    T1CR = DEF_SET_BIT6 | DEF_SET_BIT1 | DEF_SET_BIT0;                    //使能PWM,CPU,8分频
    T1CNT = 100-1;
    T1LOAD = 100-1;                                                       //100us
    T1DATA = 25;
    PWMCR0 |= DEF_SET_BIT7 | DEF_SET_BIT3 | DEF_SET_BIT2 | DEF_SET_BIT0;  //使能FPWM，正向输出，死区4个时钟
    PWMCR1 = 0x00;                                                        //普通模式
    T1EN = 1;
}
/************************************************
;  *    @函数名            : TIMER2_PWM_Init
;  *    @说明              : 定时器2,PWM初始化
;  *    @输入参数          :
;  *    @返回参数          :
;  ***********************************************/
void TIMER2_PWM_Init(void)
{
    T2CR = DEF_SET_BIT6 | DEF_SET_BIT0 | DEF_SET_BIT1;     //使能PWM,CPU,8分频
    T2CNT = 100-1;
    T2LOAD = 100-1;                                        //100us
    T2DATA = 25;
    PWMCR1 = 0x00; 
    PWMCR2 = 0x03;                                         //4个时钟
    PWMCR3 |= DEF_SET_BIT6 | DEF_SET_BIT5 | DEF_SET_BIT4;  //使能FPWM,NPWM,正向输出
    T2EN = 1;
}
/************************************************
;  *    @函数名            : Sys_Init
;  *    @说明              : 系统初始化
;  *    @输入参数          :
;  *    @返回参数          :
;  ***********************************************/
void Sys_Init(void)
{
    GIE = 0;
    CLR_RAM();
    IO_Init();
    TIMER0_PWM_Init();
    TIMER1_PWM_Init();
    TIMER2_PWM_Init();
    GIE = 1;
}
/************************************************
;  *    @函数名            : main
;  *    @说明              : 主程序
;  *    @输入参数          :
;  *    @返回参数          :
;  ***********************************************/
void main(void)
{
    Sys_Init();
    while (1)
    {

    }
}
/************************************************
;  *    @函数名            : interrupt
;  *    @说明              : 中断函数
;  *    @输入参数          :
;  *    @返回参数          :
;  ***********************************************/
void int_isr(void) __interrupt
{
__asm 
    movra _abuf
    swapar _PFLAG
    movra _statusbuf
__endasm;
   
__asm 
    swapar _statusbuf
    movra _PFLAG
    swapr _abuf
    swapar _abuf
__endasm;
}

/**************************** end of file *********************************************/
