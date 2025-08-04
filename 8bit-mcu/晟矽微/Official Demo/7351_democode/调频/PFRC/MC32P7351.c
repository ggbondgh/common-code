/******************************************************************************
;  *       @型号                 : MC32P7351
;  *       @创建日期             : 2022.12.16
;  *       @公司/作者            : sinomcu.com-FAE
;  *       @晟矽微技术支持       : 2048615934
;  *       @晟矽微官网           : http://www.sinomcu.com/
;  *       @版权                 : 2022 sinomcu.com公司版权所有.
;  *----------------------摘要描述---------------------------------
;  *                PFRC 调频 微调T1时钟
;  *                (例程仅作为参考，一直在调频)
;  *                T0   P10 10mS翻转 并修改PFRCCAL 
;  *                T1   P11 100uS翻转                                 
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
    for (FSR0 = 0; FSR0 < 0xff; FSR0 ++)
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
    OEP0 = 0x3F;                       //io口方向 1:out  0:in
    PUP0 = 0x00;                       //io口上拉电阻   1:enable  0:disable
    PDP0 = 0x00;                       //io口下拉电阻   1:enable  0:disable
    ADIOS0 = 0x00;                     //io类型选择  1:模拟输入  0:通用io

    IOP1 = 0x00;                       //io口数据位
    OEP1 = 0xFF;                       //io口方向 1:out  0:in
    PUP1 = 0x00;                       //io口上拉电阻   1:enable  0:disable
    PDP1 = 0x00;                       //io口下拉电阻   1:enable  0:disable
    ADIOS1 = 0x00;                     //io类型选择  1:模拟输入  0:通用io

    PMOD = 0x07;                       //bit7-bit5 P17、P13、P01 io类型选择 1:模拟输入  0:通用io 
                                       //bit2-bit0 P13、P01、P00 io端口输出模式  1:推挽输出 0:开漏输出
    DRVCR = 0x80;                      //普通驱动
}
/************************************************
;  *    @函数名            : TIMER0_INT_Init
;  *    @说明              : 定时器0初始化
;  *    @输入参数          :
;  *    @返回参数          :
;  ***********************************************/
void TIMER0_INT_Init(void)
{
    T0CR = DEF_SET_BIT0 | DEF_SET_BIT2;//CPU,32分频
    T0CNT = 250 - 1;
    T0LOAD = 250 - 1;                  //1ms
    T0EN = 1;
    T0IE = 1;
}
/************************************************
;  *    @函数名            : TIMER1_INT_Init
;  *    @说明              : 定时器1初始化
;  *    @输入参数          :
;  *    @返回参数          :
;  ***********************************************/
void TIMER1_INT_Init(void)
{
    T1CR = DEF_SET_BIT2;               //定时模式,Fcpu,16分频
    T1CNT = 100 - 1;                   //100us
    T1LOAD = 100 - 1;
    T1EN = 1;
    T1IE = 1;
}
/************************************************
;  *    @函数名            : delay_us
;  *    @说明              : 不精确延时函数
;  *    @输入参数          :
;  *    @返回参数          :
;  ***********************************************/
void delay_us(uint8_t num)             //CPU=8M
{
    for (i = 0; i < num; i ++)
    {
        Nop();
        Nop();
    }
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
    PFRCCR = DEF_SET_BIT7 | DEF_SET_BIT2;//使能PFRC，T1时钟源为PFRC/2
    delay_us(20);                        //PFRCEN开启后，延时20uS以上才能应用
    g_pfrc_back = PFRCCAL;               //备份频率微调校准位
    g_pfrc_temp = PFRCCAL;
    IO_Init();
    TIMER0_INT_Init();
    TIMER1_INT_Init();
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
        if (FLAG_TIMER0_10MS)          //10mS修改一次
        {
            FLAG_TIMER0_10MS = 0;
            PFRC_User();               //PFRC微调
        }
    }
}
/************************************************
;  *    @函数名            : PFRC_User
;  *    @说明              : PFRC微调
;  *    @输入参数          :
;  *    @返回参数          :
;  ***********************************************/
void PFRC_User(void)
{
    PFRCCAL = g_pfrc_temp;             //修改微调寄存器
    if (FLAG_PFRCR_ADD_DEC)
    {
        g_pfrc_temp ++;
        if (g_pfrc_temp >= 7)          //减到0  开始递增
        {
            FLAG_PFRCR_ADD_DEC = 0;
        }
    }
    else
    {
        g_pfrc_temp --;
        if (g_pfrc_temp == 0)          //加到255   开始递减
        {
            FLAG_PFRCR_ADD_DEC = 1;
        }
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
    //=======T0========================
    if(T0IF&T0IE)
    {
        g_timer0_cnt1 ++;
        if (g_timer0_cnt1 >= 10)
        {
            P10D =! P10D;
            g_timer0_cnt1 = 0;
            FLAG_TIMER0_10MS = 1;
        }
        T0IF = 0;
    }
    //=======T1========================
    if ((T1IF) && (T1IE))
    {
        P11D = !P11D;
        T1IF = 0;
    }
__asm 
    swapar _statusbuf
    movra _PFLAG
    swapr _abuf
    swapar _abuf
__endasm;
}

/**************************** end of file *********************************************/
