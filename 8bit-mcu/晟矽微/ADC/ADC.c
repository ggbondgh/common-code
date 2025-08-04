#include "Define.h"
#include "User.h"

uint16_t g_temp_value;
uint8_t  g_channel;
uint32_t g_adcsum;
uint16_t g_adcmax;
uint16_t g_adcmin;
uint32_t g_tmpbuff;


/************************************************
;  *    @函数名            : ADC_Get_Value_Average
;  *    @说明              : 连续转换
;  *    @输入参数          : 通道
;  *    @返回参数          : 返回ADC的值
;  *    函数占用内存较大
;  ***********************************************/
uint16_t ADC_Get_Value_Average(u8 CHX)
{
    g_temp_value = 0;
    g_channel = 0;
    g_tmpbuff = 0;
    g_adcmax = 0;
    g_adcmin = 0xffff;
    ADCR0 = (ADCR0 & 0x0f) | (CHX << 4); // ADC 使能  AD转换通道开启  通道  CHX
    delay(300);                          // 切换通道延时200uS以上
    for (g_channel = 0; g_channel < 20; g_channel++)
    {
        ADEOC = 0;
        while (!ADEOC)
            ; // 等待转换完成
        g_temp_value = ADRH;
        g_temp_value = g_temp_value << 4 | (ADRL & 0x0f);
        if (g_channel < 2)
            continue; // 丢弃前两次采样的
        if (g_temp_value > g_adcmax)
            g_adcmax = g_temp_value; // 最大
        if (g_temp_value < g_adcmin)
            g_adcmin = g_temp_value; // 最小
        g_tmpbuff += g_temp_value;
    }
    g_tmpbuff -= g_adcmax;           // 去掉一个最大
    g_tmpbuff -= g_adcmin;           // 去掉一个最小
    g_temp_value = (g_tmpbuff >> 4); // 除以16，取平均值
    return g_temp_value;
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
;  *    @函数名            : ADC_Power_On_Stability
;  *    @说明              : ADC上电稳定
;  *    @输入参数          :
;  *    @返回参数          :
;  ***********************************************/
void ADC_Power_On_Stability(void)
{
    uint8_t cnt;
    ADCR0 = 0xab; // 使能ADC、12位数据H8L4、VDD/4通道
    ADCR1 = 0x83; // 32分频、内部VDD
    ADCR2 = 0xff; // 固定为15ADCLK
    ADEOC = 0;
    while (!ADEOC)
        ;
    cnt = 0;
    while (!(((ADRH >> 2) == 0x10) || ((ADRH >> 2) == 0x0F)))
    {
        ADEOC = 0;
        while (!ADEOC)
            ;
        cnt++;
        if (cnt >= 200)
            return; // 用户可以添加返回值,提示错误
    }
}

//// ADC
//uint16_t ADC_Get_Value_Average(u8 CHX);
//uint8_t ADC_Zero_ADJ(void);
//void ADC_Power_On_Stability(void);
