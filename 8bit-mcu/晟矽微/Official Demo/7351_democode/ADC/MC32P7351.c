/******************************************************************************
;  *       @型号                 : MC32P7351
;  *       @创建日期             : 2022.12.16
;  *       @公司/作者            : sinomcu.com-FAE
;  *       @晟矽微技术支持       : 2048615934
;  *       @晟矽微官网           : http://www.sinomcu.com/
;  *       @版权                 : 2022 sinomcu.com公司版权所有.
;  *----------------------摘要描述---------------------------------
;  *                  ADC 
;  *                  上电等待AD稳定、零点校准
;  *                  ADC时钟为HIRC32分频1M，12位数据H8L4、内部2V、15ADCLK
;  *                  定时器2MS，P10 采集电压值 
;  *                  采集电压值<  1.5V:P11为低电平;>  1.5V:P11为高电平                                
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
;  *    @函数名            : delay
;  *    @说明              : 不精确延时函数
;  *    @输入参数          :
;  *    @返回参数          :
;  ***********************************************/
void delay(uint16_t num)
{
    for (i = 0; i < num; i ++)
    {
        Nop();
    }
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
;  *    @函数名            : ADC_Power_On_Stability
;  *    @说明              : ADC上电稳定
;  *    @输入参数          :
;  *    @返回参数          :
;  ***********************************************/
void ADC_Power_On_Stability(void)
{
    uint8_t cnt;
    ADCR0 = 0xab;                      //使能ADC、12位数据H8L4、VDD/4通道
    ADCR1 = 0x83;                      //32分频、内部VDD
    ADCR2 = 0xff;                      //固定为15ADCLK
    ADEOC = 0;
    while (!ADEOC);
    cnt = 0;
    while (!(((ADRH >> 2) == 0x10) || ((ADRH >> 2) == 0x0F)))
    {
        ADEOC = 0;
        while (!ADEOC);
        cnt ++;
        if (cnt >= 200)
            return;                    //用户可以添加返回值,提示错误
    }
}
/************************************************
;  *    @函数名            : ADC_Zero_ADJ
;  *    @说明              : ADC零点校准
;  *    @输入参数          :
;  *    @返回参数          :0 校准成功  1校准失败
;  *    用户按照需求选择是否校准
;  ***********************************************/
uint8_t ADC_Zero_ADJ(void)
{
    ADCR0 = 0xeb;                                //使能ADC、12位数据H8L4、GND通道
    ADCR1 = 0x80;                                //32分频、内部2V
    ADCR2 = 0xff;                                //固定为15ADCLK
    OSADJCR |= DEF_SET_BIT7;                     //使能零点校准、负向修调
    ADEOC = 0;
    while (!ADEOC);
    if ((ADRH == 0) && ((ADRL & 0x0F) == 0))     //结果是否为0
    {
        OSADJTD = 1;                             //正向修调
        OSADJCR |= 0x3F;
        ADEOC = 0;
        while (!ADEOC);
        if ((ADRH == 0) && ((ADRL & 0x0F) == 0)) //结果是否为0
        {
            ADEN = 0;
            return PASS;
        }
        else
        {
            while (1)
            {
                if (OSADJCR & 0x3f)
                {
                    OSADJCR --;
                    ADEOC = 0;
                    while (!ADEOC);
                    if ((ADRH == 0) && ((ADRL & 0x0F) == 0))//结果是否为0
                    {
                        ADEN = 0;
                        return PASS;
                    }
                }
                else
                {
                    ADEN = 0;
                    return FAIL;
                }
            }
        }
    }
    else
    {
        while (1)
        {
            if ((OSADJCR & 0x3f) == 0x3f)
            {
                ADEN = 0;
                return FAIL;
            }
            else
            {
                OSADJCR ++;
                ADEOC = 0;
                while (!ADEOC);
                if ((ADRH == 0) && ((ADRL & 0x0F) == 0))//结果是否为0
                {
                    ADEN = 0;
                    return PASS;
                }
            }
        }
    }
}
/************************************************
;  *    @函数名            : ADC_Init
;  *    @说明              : ADC初始化
;  *    @输入参数          :
;  *    @返回参数          :
;  ***********************************************/
void ADC_Init(void)
{
    OEP1 &= DEF_CLR_BIT0;                        //P10为输入口
    ADIOS0 |= DEF_SET_BIT5;                      //使能P10模拟功能
    ADCR0 = 0xfb;                                //使能ADC、12位数据H8L4
    ADCR1 = 0x80;                                //32分频、内部2V 
    ADCR2 = 0xff;                                //固定为15ADCLK 
}
/************************************************
;  *    @函数名            : ADC_Get_Value_Average
;  *    @说明              : 连续转换
;  *    @输入参数          : 通道
;  *    @返回参数          : 返回ADC的值
;  *    函数占用内存较大        
;  ***********************************************/
uint ADC_Get_Value_Average(u8 CHX)
{
    g_temp_value = 0;
    g_channel = 0;
    g_tmpbuff = 0;
    g_adcmax = 0;
    g_adcmin = 0xffff;
    ADCR0 = (ADCR0 & 0x0f) | (CHX << 4);         // ADC 使能  AD转换通道开启  通道  CHX
    delay(300);                                  //切换通道延时200uS以上
    for (g_channel = 0; g_channel < 20; g_channel ++)
    {
        ADEOC = 0;
        while (!ADEOC);                         //等待转换完成
        g_temp_value = ADRH;
        g_temp_value = g_temp_value << 4 | (ADRL & 0x0f);
        if (g_channel < 2)
            continue;                            //丢弃前两次采样的
        if (g_temp_value > g_adcmax)
            g_adcmax = g_temp_value;             //最大
        if (g_temp_value < g_adcmin)
            g_adcmin = g_temp_value;             //最小
        g_tmpbuff += g_temp_value;
    }
    g_tmpbuff -= g_adcmax;                       //去掉一个最大
    g_tmpbuff -= g_adcmin;                       //去掉一个最小
    g_temp_value = (g_tmpbuff >> 4);             //除以16，取平均值
    return g_temp_value;
}
/************************************************
;  *    @函数名            : TIMER0_INT_Init
;  *    @说明              : 定时器0初始化
;  *    @输入参数          :
;  *    @返回参数          :
;  ***********************************************/
void TIMER0_INT_Init(void)
{
    T0CR |= DEF_SET_BIT1 | DEF_SET_BIT2;         //CPU,64分频
    T0CNT = 250-1;
    T0LOAD = 250-1;                              //2ms
    T0EN = 1;
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
    ADC_Power_On_Stability();
    while (ADC_Zero_ADJ());                      //demo演示,校准失败一直校准，用户按照需求选择是否校准
    ADC_Init();
    TIMER0_INT_Init();
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
        if (T0IF)                                //2mS
        {
            T0IF = 0;
            g_adc_value0_temp = ADC_Get_Value_Average(5);
        }
        if (g_adc_value0_temp > 2048+1024)       //>1.5V
        {
            P11D = 1;
        }

        else
        {
            P11D = 0;
        }
      P11D = 1;
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
