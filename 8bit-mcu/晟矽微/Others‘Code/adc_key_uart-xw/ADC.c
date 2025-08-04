
#include "Define.h"
#include "User.h"

uint8_t  adc_star;
uint16_t g_temp_value;
uint8_t g_channel;
uint32_t g_adcsum;
uint16_t g_adcmax;
uint16_t g_adcmin;
uint16_t adc_data;


/************************************************
;  *    @函数名            : Scan_ADC
;  *    @说明              : 轮询扫描ADC通道
;  *    @输入参数          : 
;  *    @返回参数          :     
;  ***********************************************/
void Scan_ADC(void)
{
   	switch(adc_star)
   	{
   	case 0:
        //P11D = 0;
   	   	adc_data = ADC_Get_Value_Average();	//采样+求平均时间，约1ms
        //P11D = 1;
        Set_ADC_Channel(11);    //EVN0 P01 
        adc_star++;
   	   	break;

    case 1:
        //P11D = 0;     
        adc_data = ADC_Get_Value_Average();
        //P11D = 1;
        Set_ADC_Channel(5);     //AN5 P10
        adc_star = 0;
        break;
   	}
}

/************************************************
;  *    @函数名            : Set_ADC_Channel
;  *    @说明              : 设定ADC模拟通道
;  *    @输入参数          : 通道
;  *    @返回参数          :     
;  ***********************************************/
void Set_ADC_Channel(u8 CHX)
{
    ADCR0 = (ADCR0 & 0x0f) | (CHX << 4); 
}

/************************************************
;  *    @函数名            : ADC_Get_Value_Average
;  *    @说明              : 连续转换
;  *    @输入参数          : 通道
;  *    @返回参数          : 返回ADC的值
;  *    函数占用内存较大   
； 采样20次，前2次不要，累加18次，减去最大值和最小值，在除以16，得到平均值     
;  ***********************************************/
uint ADC_Get_Value_Average(void)
{
    g_adcsum = 0;
    g_adcmax = 0;
    g_adcmin = 0xffff;
    
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
        g_adcsum += g_temp_value;  	   	
    }
    g_adcsum -= g_adcmax;                       //去掉一个最大
    g_adcsum -= g_adcmin;                       //去掉一个最小
    g_temp_value = (g_adcsum >> 4);             //除以16，取平均值
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