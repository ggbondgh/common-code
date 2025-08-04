#include "Define.h"
#include "User.h"

uint16_t g_temp_value;
uint8_t  g_channel;
uint32_t g_adcsum;
uint16_t g_adcmax;
uint16_t g_adcmin;
uint32_t g_tmpbuff;


/************************************************
;  *    @������            : ADC_Get_Value_Average
;  *    @˵��              : ����ת��
;  *    @�������          : ͨ��
;  *    @���ز���          : ����ADC��ֵ
;  *    ����ռ���ڴ�ϴ�
;  ***********************************************/
uint16_t ADC_Get_Value_Average(u8 CHX)
{
    g_temp_value = 0;
    g_channel = 0;
    g_tmpbuff = 0;
    g_adcmax = 0;
    g_adcmin = 0xffff;
    ADCR0 = (ADCR0 & 0x0f) | (CHX << 4); // ADC ʹ��  ADת��ͨ������  ͨ��  CHX
    delay(300);                          // �л�ͨ����ʱ200uS����
    for (g_channel = 0; g_channel < 20; g_channel++)
    {
        ADEOC = 0;
        while (!ADEOC)
            ; // �ȴ�ת�����
        g_temp_value = ADRH;
        g_temp_value = g_temp_value << 4 | (ADRL & 0x0f);
        if (g_channel < 2)
            continue; // ����ǰ���β�����
        if (g_temp_value > g_adcmax)
            g_adcmax = g_temp_value; // ���
        if (g_temp_value < g_adcmin)
            g_adcmin = g_temp_value; // ��С
        g_tmpbuff += g_temp_value;
    }
    g_tmpbuff -= g_adcmax;           // ȥ��һ�����
    g_tmpbuff -= g_adcmin;           // ȥ��һ����С
    g_temp_value = (g_tmpbuff >> 4); // ����16��ȡƽ��ֵ
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

/************************************************
;  *    @������            : ADC_Power_On_Stability
;  *    @˵��              : ADC�ϵ��ȶ�
;  *    @�������          :
;  *    @���ز���          :
;  ***********************************************/
void ADC_Power_On_Stability(void)
{
    uint8_t cnt;
    ADCR0 = 0xab; // ʹ��ADC��12λ����H8L4��VDD/4ͨ��
    ADCR1 = 0x83; // 32��Ƶ���ڲ�VDD
    ADCR2 = 0xff; // �̶�Ϊ15ADCLK
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
            return; // �û�������ӷ���ֵ,��ʾ����
    }
}

//// ADC
//uint16_t ADC_Get_Value_Average(u8 CHX);
//uint8_t ADC_Zero_ADJ(void);
//void ADC_Power_On_Stability(void);
