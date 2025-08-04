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

#define Key             P00D
#define Color_R         P15D
#define Color_G         P17D
#define Color_B         P16D
#define Color_W         P13D

#define Key_State                 flag1.bits.bit0
#define Key_Updata_Flag           flag1.bits.bit1
#define RGB_Breath_Flag           flag1.bits.bit2
#define Timer_10ms_Flag           flag1.bits.bit3
#define Switch_Swap_Flag          flag1.bits.bit4

uint8_t  adc_star;
uint16_t g_temp_value;
uint8_t g_channel;
uint32_t g_adcsum;
uint16_t g_adcmax;
uint16_t g_adcmin;
uint16_t adc_data;

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
������:   	��ʱ����
************************************************/

void delay_52us(uint   	us)
{
   	while(us)
   	{
   	   	us--;
   	}
}

/************************************************
;  *    @������            : uart
;  *    @˵��              : �������
;  *    @�������          :
;  *    @���ز���          :
;  ***********************************************/
#define  UART     P05D

uint   	bit_out;   	   	   	   	//���ڴ�����8λ������
uint   	data_bit;  	   	   	   	//���͵�λ��
uint   	send_data; 	   	   	   	//����ֵ��8λ������

void   	UART_send(void)	   	   	   	   	//����������Ч��
{
   	uint   	send_cnt = 8;  	   	   	   	//���巢��8λ
   	bit_out = send_data;   	   	       	//��ֵ

   	UART = 0;  	   	   	   	   	   	   	//��ʼ����
   	delay_52us(17);        	   	       	   	//��ʱ52us

   	while(send_cnt)    	   	   	   	   	//������һλһλ�ط���ѭ��8��
   	{
   	   	send_cnt--;
   	   	data_bit = bit_out & 0x01;
   	   	if(data_bit)
   	   	{
   	   	   	UART = 1;  	   	   	   	   	 //ȡ��λֵ�������P01,����λΪ1ʱ��P01 = 1,����P01 = 0
   	   	}
   	   	else   	UART = 0;
   	   	bit_out = bit_out >> 1;    	   	 //����һλ������һλ��ֵ����һ������ֵ
   	   	delay_52us(17);        	   	   	   	 //��ʱ52us
   	}
   	UART = 1;  	   	   	   	   	   	   	 //ֹͣ����
   	delay_52us(17);        	   	   	   	   	 //��ʱ52us
   	delay_52us(50);
}

void Uart_Send_Data(void) // 19200  P14
{
    send_data = g_adc_value0_temp & 0x00FF;
   	UART_send();
   	send_data =  (g_adc_value0_temp & 0xff00) >> 8; 
   	UART_send();
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
    OEP0 = 0xFE;                       //io�ڷ��� 1:out  0:in  P00����
    PUP0 = 0x01;                       //io����������   1:enable  0:disable  P00������Ч
    PDP0 = 0x00;                       //io����������   1:enable  0:disable
    ADIOS0 = 0x00;                     //io����ѡ��  1:ģ������  0:ͨ��io P00��������

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
;  *    @������            : ADC_Init
;  *    @˵��              : ADC��ʼ��
;  *    @�������          :
;  *    @���ز���          :
;  ***********************************************/
void ADC_Init(void)
{
    OEP0 &= 0xEF;                                //P04Ϊ�����
    ADIOS0 |= 0x08;                              //ʹ��P04ģ�⹦��
    ADCR0 = 0x3f;                                //ʹ��ADC��12λ����H8L4  P04 AN3
    ADCR1 = 0x83;                                //32��Ƶ��VDD�ο�
    ADCR2 = 0xff;                                //�̶�Ϊ15ADCLK 
}

/************************************************
;  *    @������            : ADC_mea
;  *    @˵��              : ����ת��
;  *    @�������          : ͨ��
;  *    @���ز���          : 
;  *    ����ռ���ڴ�ϴ�        
;  ***********************************************/
void   	ADC_mea(void)//�������ݣ�����ƽ��ֵ��ʽ�˲�
{
    g_temp_value = 0;
    g_tmpbuff = 0;

    uint8_t	Icnt = 16;//����16������

    while (Icnt--)
    {
        ADEOC = 0; 	   	//��ʼADCת��
        while (!ADEOC) 	   	//�ȴ�ADCת�����
            //    NULL;
            //��AD_DONE�ߵ�λʱ��ȡADC���
            //ע�⣺8λ�ֱ��ʶ�ȡADCRֵ��9~12Ϊ�ֱ��ʶ�ȡADCRH��ADCRL
        // 	data = ADCR;   	   	//��ADC��ֵ����data
            g_temp_value = ADRH;
        g_temp_value = g_temp_value << 4 | (ADRL & 0x0f);
        g_tmpbuff += g_temp_value;
    }
    g_adc_value0_temp = g_tmpbuff >> 4;//ȡƽ��ֵ��2^4 = 16��
}


uint16_t ADC_Get_Value_Average(void)
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
;  *    @������            : TIMER0_INT_Init
;  *    @˵��              : ��ʱ��0��ʼ��
;  *    @�������          :
;  *    @���ز���          :
;  ***********************************************/
void TIMER0_INT_Init(void)
{
    T0CR = 0x00;                        //CPU = 32M/16 = 2M,1��Ƶ = 2M
    T0CNT = 50-1;
    T0LOAD = 50-1;                               //25us
    T0EN = 1;                                    //������ʱ��
    T0IE = 1;                                    //���жϱ�־

    GIE = 1;                                     //�ж���ʹ�ܱ�־
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
    //ADC_Power_On_Stability();
    //while (ADC_Zero_ADJ());                      //demo��ʾ,У׼ʧ��һֱУ׼���û���������ѡ���Ƿ�У׼
    ADC_Init();
    TIMER0_INT_Init();
    
}

void    Key_Function(void)
{
    if (Key == 0 && Key_State == 0)
    {
        Key_State = 1;

        Key_Updata_Flag = 1;

        Key_Value++;

        if (Key_Value > 4)
            Key_Value = 0;
   	   	
   	   	Key_Value_Temp = Key_Value;
    }
    else if(Key == 1)
    {
        Key_State = 0;
    }
}

void    RGB_Mode_Control(void)
{
    if (Key_Updata_Flag)
    {
        Key_Updata_Flag = 0;

        Duty_Wait_Cnt = 0;
        Breath_Setp_Cnt = 0;
        num = 0;
        duty = 0;

   	   	if (Key_Value == 4)
        {
            RGB_Breath_Flag = 1;
        }
        else
        {
            RGB_Breath_Flag = 0;
        }

        if (Key_Value == 0)
        {
            Color_W = 1;
            Color_R = 0;
            Color_G = 0;
            Color_B = 0;

        }
        else if (Key_Value == 1)
        {
            Color_W = 0;
            Color_R = 1;
            Color_G = 0;
            Color_B = 0;

        }
        else if (Key_Value == 2)
        {
            Color_W = 0;
            Color_R = 0;
            Color_G = 1;
            Color_B = 0;

        }
        else if (Key_Value == 3)
        {
            Color_W = 0;
            Color_R = 0;
            Color_G = 0;
            Color_B = 1;

        }       

        if (Key_Value == 5)
        {
            Color_W = 0;
            Color_R = 0;
            Color_G = 0;
            Color_B = 0;
           
            Duty_Wait_Cnt = 0;
            Breath_Setp_Cnt = 0;
            num = 0;
            duty = 0;
        }
    }
}

void    LDR_Control(void)
{
    if (ADC_Get_Value_Average() >= 2048 && !Switch_Swap_Flag)//off   2.5V
    {
        Switch_Swap_Flag = 1;

        Key_Value = 5;

        Key_Updata_Flag = 1;

        AD_Judement_Cnt = 0;
    }
    else if (ADC_Get_Value_Average() <= 1638 && Switch_Swap_Flag)//on   2V
    {
        AD_Judement_Cnt++;

        if (AD_Judement_Cnt >= 100)//1000ms
        {
            Switch_Swap_Flag = 0;

            Key_Value = Key_Value_Temp;

            Key_Updata_Flag = 1;

            AD_Judement_Cnt = 0;
        }
    }

    //RGB_Mode_Control();
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

    //P16D = 0;
    Switch_Swap_Flag = 0;

    duty = 0;

    Color_Value = 0x01;
    Key_Value = 0;
   	Key_Value_Temp = 0;

    Key_Updata_Flag = 1;

    while (1)
    {
        if (Timer_10ms_Flag)
        {
            Timer_10ms_Flag = 0;

            //ADC_mea();

            LDR_Control();

            if (Switch_Swap_Flag == 0)
            {
                Key_Function();

                

                //Color_OFFON_Control();
            }

            RGB_Mode_Control();
        }
   	   	//Uart_Send_Data();
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

    if (T0IF && T0IE)                                //25us
    {
        T0IF = 0;

        Time_25us_Cnt++;
        if (Time_25us_Cnt >= 400)
        {
            Time_25us_Cnt = 0;

            Timer_10ms_Flag = 1;
        }

        if (RGB_Breath_Flag)
        {
            num++; 	   	   	//���ϵ����ӽ���
            if (num >= 200)    	//�������ﵽ�趨��ֵ����
            {
                num = 0;

                Duty_Wait_Cnt++;

                if (Duty_Wait_Cnt >= 3)
                {
                    Duty_Wait_Cnt = 0;

                    duty++;
                }

                if (duty > 203)
                {
                    duty = 0;

                    Breath_Setp_Cnt++;

                    if (Breath_Setp_Cnt >= 3)
                    {
                        Breath_Setp_Cnt = 0;
                    }
                }

            }
            //������ƺ����ƵĽ����������Ӷ�����LED�����ȵ�ǿ��
            if (duty <= num)   	//ռ�ձ�С�ڽ���ʱ���
            {
                //RGB_High_Breath_Control(Breath_Setp_Cnt);
                if (Breath_Setp_Cnt == 0)
                {
                    Color_W = 0;
                    Color_R = 1;
                    Color_G = 0;
                    Color_B = 0;
                }
                else if (Breath_Setp_Cnt == 1)
                {
                    Color_W = 0;
                    Color_R = 0;
                    Color_G = 0;
                    Color_B = 1;
                }
                else if (Breath_Setp_Cnt == 2)
                {
                    Color_W = 0;
                    Color_R = 0;
                    Color_G = 1;
                    Color_B = 0;
                }
            }
            else   	   	   	//ռ�ձȴ��ڽ���ʱ����
            {
                //RGB_Low_Breath_Control(Breath_Setp_Cnt);

                if (Breath_Setp_Cnt == 0)
                {
                    Color_W = 0;
                    Color_R = 0;
                    Color_G = 0;
                    Color_B = 1;
                }
                else if (Breath_Setp_Cnt == 1)
                {
                    Color_W = 0;
                    Color_R = 0;
                    Color_G = 1;
                    Color_B = 0;
                }
                else if (Breath_Setp_Cnt == 2)
                {
                    Color_W = 0;
                    Color_R = 1;
                    Color_G = 0;
                    Color_B = 0;
                }
            }
        }
    }


__asm 
    swapar _statusbuf
    movra _PFLAG
    swapr _abuf
    swapar _abuf
__endasm;
}

/**************************** end of file *********************************************/
