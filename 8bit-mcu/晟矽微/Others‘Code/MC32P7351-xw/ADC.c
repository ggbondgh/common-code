
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
;  *    @������            : Scan_ADC
;  *    @˵��              : ��ѯɨ��ADCͨ��
;  *    @�������          : 
;  *    @���ز���          :     
;  ***********************************************/
void Scan_ADC(void)
{
   	switch(adc_star)
   	{
   	case 0:
        //P11D = 0;
   	   	adc_data = ADC_Get_Value_Average();	//����+��ƽ��ʱ�䣬Լ1ms
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
;  *    @������            : Set_ADC_Channel
;  *    @˵��              : �趨ADCģ��ͨ��
;  *    @�������          : ͨ��
;  *    @���ز���          :     
;  ***********************************************/
void Set_ADC_Channel(u8 CHX)
{
    ADCR0 = (ADCR0 & 0x0f) | (CHX << 4); 
}

/************************************************
;  *    @������            : ADC_Get_Value_Average
;  *    @˵��              : ����ת��
;  *    @�������          : ͨ��
;  *    @���ز���          : ����ADC��ֵ
;  *    ����ռ���ڴ�ϴ�   
�� ����20�Σ�ǰ2�β�Ҫ���ۼ�18�Σ���ȥ���ֵ����Сֵ���ڳ���16���õ�ƽ��ֵ     
;  ***********************************************/
uint ADC_Get_Value_Average(void)
{
    g_adcsum = 0;
    g_adcmax = 0;
    g_adcmin = 0xffff;
    
    for (g_channel = 0; g_channel < 20; g_channel ++)
    {
        ADEOC = 0;
        while (!ADEOC);                         //�ȴ�ת�����
        g_temp_value = ADRH;
        g_temp_value = g_temp_value << 4 | (ADRL & 0x0f);
   	   	if (g_channel < 2)
            continue;                            //����ǰ���β�����

        if (g_temp_value > g_adcmax)
            g_adcmax = g_temp_value;             //���
        if (g_temp_value < g_adcmin)
            g_adcmin = g_temp_value;             //��С
        g_adcsum += g_temp_value;  	   	
    }
    g_adcsum -= g_adcmax;                       //ȥ��һ�����
    g_adcsum -= g_adcmin;                       //ȥ��һ����С
    g_temp_value = (g_adcsum >> 4);             //����16��ȡƽ��ֵ
    return g_temp_value;
}


/************************************************
;  *    @������            : ADC_Zero_ADJ
;  *    @˵��              : ADC���У׼
;  *    @�������          :
;  *    @���ز���          :0 У׼�ɹ�  1У׼ʧ��
;  *    �û���������ѡ���Ƿ�У׼
;  ***********************************************/
uint8_t ADC_Zero_ADJ(void)
{
    ADCR0 = 0xeb;                                //ʹ��ADC��12λ����H8L4��GNDͨ��
    ADCR1 = 0x80;                                //32��Ƶ���ڲ�2V
    ADCR2 = 0xff;                                //�̶�Ϊ15ADCLK
    OSADJCR |= DEF_SET_BIT7;                     //ʹ�����У׼�������޵�
    ADEOC = 0;
    while (!ADEOC);
    if ((ADRH == 0) && ((ADRL & 0x0F) == 0))     //����Ƿ�Ϊ0
    {
        OSADJTD = 1;                             //�����޵�
        OSADJCR |= 0x3F;
        ADEOC = 0;
        while (!ADEOC);
        if ((ADRH == 0) && ((ADRL & 0x0F) == 0)) //����Ƿ�Ϊ0
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
                    if ((ADRH == 0) && ((ADRL & 0x0F) == 0))//����Ƿ�Ϊ0
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
                if ((ADRH == 0) && ((ADRL & 0x0F) == 0))//����Ƿ�Ϊ0
                {
                    ADEN = 0;
                    return PASS;
                }
            }
        }
    }
}