/******************************************************************************
;  *       @�ͺ�                 : MC32P7351
;  *       @��������             : 2022.12.16
;  *       @��˾/����            : sinomcu.com-FAE
;  *       @����΢����֧��       : 2048615934
;  *       @����΢����           : http://www.sinomcu.com/
;  *       @��Ȩ                 : 2022 sinomcu.com��˾��Ȩ����.
;  *----------------------ժҪ����---------------------------------
;  *                  ADC 
;  *                  �ϵ�ȴ�AD�ȶ������У׼
;  *                  ADCʱ��ΪHIRC32��Ƶ1M��12λ����H8L4���ڲ�2V��15ADCLK
;  *                  ��ʱ��2MS��P10 �ɼ���ѹֵ 
;  *                  �ɼ���ѹֵ<  1.5V:P11Ϊ�͵�ƽ;>  1.5V:P11Ϊ�ߵ�ƽ                                
******************************************************************************/

#include "user.h"
/************************************************
;  *    @������          : CLR_RAM
;  *    @˵��            : ��RAM
;  *    @�������        :
;  *    @���ز���        :
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
;  *    @������            : delay
;  *    @˵��              : ����ȷ��ʱ����
;  *    @�������          :
;  *    @���ز���          :
;  ***********************************************/
void delay(uint16_t num)
{
    for (i = 0; i < num; i ++)
    {
        Nop();
    }
}
/************************************************
;  *    @������            : IO_Init
;  *    @˵��              : IO��ʼ��
;  *    @�������          :
;  *    @���ز���          :
;  ***********************************************/
void IO_Init(void)
{
    IOP0 = 0x00;                       //io������λ
    OEP0 = 0x3F;                       //io�ڷ��� 1:out  0:in
    PUP0 = 0x00;                       //io����������   1:enable  0:disable
    PDP0 = 0x00;                       //io����������   1:enable  0:disable
    ADIOS0 = 0x00;                     //io����ѡ��  1:ģ������  0:ͨ��io

    IOP1 = 0x00;                       //io������λ
    OEP1 = 0xFF;                       //io�ڷ��� 1:out  0:in
    PUP1 = 0x00;                       //io����������   1:enable  0:disable
    PDP1 = 0x00;                       //io����������   1:enable  0:disable
    ADIOS1 = 0x00;                     //io����ѡ��  1:ģ������  0:ͨ��io

    PMOD = 0x07;                       //bit7-bit5 P17��P13��P01 io����ѡ�� 1:ģ������  0:ͨ��io 
                                       //bit2-bit0 P13��P01��P00 io�˿����ģʽ  1:������� 0:��©���
    DRVCR = 0x80;                      //��ͨ����
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
    ADCR0 = 0xab;                      //ʹ��ADC��12λ����H8L4��VDD/4ͨ��
    ADCR1 = 0x83;                      //32��Ƶ���ڲ�VDD
    ADCR2 = 0xff;                      //�̶�Ϊ15ADCLK
    ADEOC = 0;
    while (!ADEOC);
    cnt = 0;
    while (!(((ADRH >> 2) == 0x10) || ((ADRH >> 2) == 0x0F)))
    {
        ADEOC = 0;
        while (!ADEOC);
        cnt ++;
        if (cnt >= 200)
            return;                    //�û�������ӷ���ֵ,��ʾ����
    }
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
;  *    @������            : ADC_Init
;  *    @˵��              : ADC��ʼ��
;  *    @�������          :
;  *    @���ز���          :
;  ***********************************************/
void ADC_Init(void)
{
    OEP1 &= DEF_CLR_BIT0;                        //P10Ϊ�����
    ADIOS0 |= DEF_SET_BIT5;                      //ʹ��P10ģ�⹦��
    ADCR0 = 0xfb;                                //ʹ��ADC��12λ����H8L4
    ADCR1 = 0x80;                                //32��Ƶ���ڲ�2V 
    ADCR2 = 0xff;                                //�̶�Ϊ15ADCLK 
}
/************************************************
;  *    @������            : ADC_Get_Value_Average
;  *    @˵��              : ����ת��
;  *    @�������          : ͨ��
;  *    @���ز���          : ����ADC��ֵ
;  *    ����ռ���ڴ�ϴ�        
;  ***********************************************/
uint ADC_Get_Value_Average(u8 CHX)
{
    g_temp_value = 0;
    g_channel = 0;
    g_tmpbuff = 0;
    g_adcmax = 0;
    g_adcmin = 0xffff;
    ADCR0 = (ADCR0 & 0x0f) | (CHX << 4);         // ADC ʹ��  ADת��ͨ������  ͨ��  CHX
    delay(300);                                  //�л�ͨ����ʱ200uS����
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
        g_tmpbuff += g_temp_value;
    }
    g_tmpbuff -= g_adcmax;                       //ȥ��һ�����
    g_tmpbuff -= g_adcmin;                       //ȥ��һ����С
    g_temp_value = (g_tmpbuff >> 4);             //����16��ȡƽ��ֵ
    return g_temp_value;
}
/************************************************
;  *    @������            : TIMER0_INT_Init
;  *    @˵��              : ��ʱ��0��ʼ��
;  *    @�������          :
;  *    @���ز���          :
;  ***********************************************/
void TIMER0_INT_Init(void)
{
    T0CR |= DEF_SET_BIT1 | DEF_SET_BIT2;         //CPU,64��Ƶ
    T0CNT = 250-1;
    T0LOAD = 250-1;                              //2ms
    T0EN = 1;
}
/************************************************
;  *    @������            : Sys_Init
;  *    @˵��              : ϵͳ��ʼ��
;  *    @�������          :
;  *    @���ز���          :
;  ***********************************************/
void Sys_Init(void)
{
    GIE = 0;
    CLR_RAM();
    IO_Init();
    ADC_Power_On_Stability();
    while (ADC_Zero_ADJ());                      //demo��ʾ,У׼ʧ��һֱУ׼���û���������ѡ���Ƿ�У׼
    ADC_Init();
    TIMER0_INT_Init();
    GIE = 1;
}
/************************************************
;  *    @������            : main
;  *    @˵��              : ������
;  *    @�������          :
;  *    @���ز���          :
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
;  *    @������            : interrupt
;  *    @˵��              : �жϺ���
;  *    @�������          :
;  *    @���ز���          :
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
