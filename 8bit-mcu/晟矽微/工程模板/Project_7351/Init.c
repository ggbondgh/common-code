#include "define.h"
#include "user.h"

/************************************************
 * @brief Function for clear RAM
 *
 * @param[\] void.
 * 
 * @return  void.
*************************************************/
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
 * @brief Function for IO init
 *
 * @param[\] void.
 * 
 * @return  void.
*************************************************/
void IO_Init(void)
{
    IOP0 = 0x00;                       //io������λ
    OEP0 = 0xff;                       //io�ڷ��� 1:out  0:in  �������ã�PxxOE
    PUP0 = 0x00;                       //io����������   1:enable  0:disable
    PDP0 = 0x00;                       //io����������   1:enable  0:disable
   
    IOP1 = 0x00;                       //io������λ
    OEP1 = 0xF7;                       //io�ڷ��� 1:out  0:in
    PUP1 = 0x08;                       //io����������   1:enable  0:disable
    PDP1 = 0x00;                       //io����������   1:enable  0:disable
    
    PMOD = 0x07;                       //bit2-bit0 P13��P01��P00 io�˿����ģʽ  1:������� 0:��©���
                                       
    DRVCR = 0x80;                      //bit7:1��ͨ����,0��ǿ����

    P1KBCR = 0x08;                     //P1����IO���ѹ���  P17~P10
}

/************************************************
 * @brief Function for TIMER0 interrupt init
 *
 * @param[\] void.
 * 
 * @return  void.
 * 
 * Describe: Use Fcpu��time = T0LOAD*(PRS/Fcpu) = 250*(16/4) = 1ms
*************************************************/
void TIMER0_INT_Init(void)
{
    T0CR = PRS_16; // CPU,16div
    T0CNT = 250 -1;
    T0LOAD = 250 -1;                 
    T0EN = 1;
    T0IE = 1;
}

/************************************************
 * @brief Function for TIMER1 interrupt init
 *
 * @param[\] void.
 * 
 * @return  void.
 * 
 * Describe: Use Fcpu��time = T1LOAD*(PRS/Fcpu) = 250*(32/4) = 2ms
*************************************************/
void TIMER1_INT_Init(void)
{
    T1CR = PRS_32; // CPU,32div
    T1CNT = 250 -1;                 
    T1LOAD = 250 -1;
    T1EN = 1;
    T1IE = 1;
}

/************************************************
 * @brief Function for TIMER2 interrupt init
 *
 * @param[\] void.
 * 
 * @return  void.
 * 
 * Describe: Use Fcpu��time = T2LOAD*(PRS/Fcpu) = 100*(8/4) = 200us
*************************************************/
void TIMER2_INT_Init(void)
{
    T2CR = PRS_8;   //CPU,8��Ƶ
    T2CNT = 100 - 1;
    T2LOAD = 100 - 1;                 
    T2EN = 1;
    T2IE = 1;
}

/************************************************
 * @brief Function for TIMER3 interrupt init
 *
 * @param[\] void.
 * 
 * @return  void.
 * 
 * Describe: Use Fcpu��time = T3LOAD*(PRS/Fcpu) = 250*(128/4) = 8ms
*************************************************/
void TIMER3_INT_Init(void)
{
    T3CR = PRS_128;               //CPU,128��Ƶ
    T3CNT = 250 - 1;
    T3LOAD = 250 - 1;                  
    T3EN = 1; 
    T3IE = 1;
}

/************************************************
 * @brief Function for TIMER0 PWM init
 *
 * @param[\] void.
 * 
 * @return  void.
 * 
 * Describe: 
 *  1, PWM freq = Fpcu/PRS/T0CNT = 4000/4/100 = 10KHz
 *  2, PWM Duty = T0DATA/T0CNT = 25/100 = 25%
 *  3, PWM0: P02/P16
*************************************************/
void TIMER0_PWM_Init(void)
{
    T0CR = DEF_SET_BIT6 | PRS_4;     //ʹ��PWM,CPU,4Ƶ
    T0CNT = 100-1;
    T0LOAD = 100-1;                                        
    T0DATA = 25;
    PWMCR0 = 0x00;                                         //�������
    PWMCR1 = 0x00;                                         //��ͨģʽ
    //PWMCR3 = DEF_SET_BIT2;                                 //P02�˿����
    PWMCR3 = DEF_CLR_BIT2;                                 //P16�˿����
    T0EN = 1;
}

/************************************************
 * @brief Function for TIMER1 PWM init
 *
 * @param[\] void.
 * 
 * @return  void.
 * 
 * Describe: 
 *  . PWM freq = Fpcu/PRS/T1CNT = 4000/4/100 = 10KHz
 *  . PWM Duty = T1DATA/T1CNT = 25/100 = 25%
 *  . PWM1: P17
 *  . FPWM1: P16 
*************************************************/
void TIMER1_PWM_Init(void)
{
    T1CR = DEF_SET_BIT6 | PRS_4;                    //ʹ��PWM,CPU,4��Ƶ
    T1CNT = 100-1;
    T1LOAD = 100-1;                                                  
    T1DATA = 25;
    //PWMCR0 |= DEF_SET_BIT7 | DEF_SET_BIT3 | DEF_SET_BIT2 | DEF_SET_BIT0;  //ʹ��FPWM���������������4��ʱ��

    PWMCR1 = 0x00;                                                        //��ͨģʽ
    T1EN = 1;
}

/************************************************
 * @brief Function for TIMER2 PWM init
 *
 * @param[\] void.
 * 
 * @return  void.
 * 
 * Describe: 
 *  . PWM freq = Fpcu/PRS/T2CNT = 4000/4/100 = 10KHz
 *  . PWM Duty = T2DATA/T2CNT = 25/100 = 25%
 *  . PWM2: P15
 *  . FPWM2: P14 
 *  . NPWM1: P11
 *  . NFPWM1: P12 
*************************************************/
void TIMER2_PWM_Init(void)
{
    T2CR = DEF_SET_BIT6 | PRS_4;     //ʹ��PWM,CPU,4��Ƶ
    T2CNT = 100-1;
    T2LOAD = 100-1;                                     
    T2DATA = 25;
    PWMCR1 = 0x00; 
    PWMCR2 = 0x03;                                         //4��ʱ��
    PWMCR3 |= DEF_SET_BIT6 | DEF_SET_BIT5 | DEF_SET_BIT4;  //ʹ��FPWM,NPWM,�������
    T2EN = 1;
}

/************************************************
 * @brief Function for ADC init
 *
 * @param[\] void.
 * 
 * @return  void.
*************************************************/
void ADC_Init(void)
{
    OEP1 &= DEF_CLR_BIT0;                        //P10Ϊ�����
    OEP0 &= DEF_CLR_BIT1;                        //P01Ϊ����� 

    ADIOS0 = 0x20;                     //io����ѡ��  1:ģ������  0:ͨ��io
//bit7~0  P12 P11 P10 P05 P04 P03 P02 P00

   	ADIOS1 = 0x00;                     //io����ѡ��  1:ģ������  0:ͨ��io
//bit1~0  P15 P14 

    PMOD = 0x20 | 0x07;                       //bit7-bit5 P17��P13��P01 io����ѡ�� 1:ģ������  0:ͨ��io 
                                       //bit2-bit0 P13��P01��P00 io�˿����ģʽ  1:������� 0:��©���

    ADCR0 = 0xfb;                                //ʹ��ADC��12λ����H8L4
    ADCR1 = 0x80;                                //32��Ƶ��000�ڲ�2V��001�ڲ�3V��010�ڲ�4V��011VDD
    ADCR2 = 0xff;                                //�̶�Ϊ15ADCLK 
    //Set_ADC_Channel(5);         // ADC ʹ��  ADת��ͨ������  ͨ��  CHX
}

/*
ADCHS[3:0]   ADCģ������ͨ��
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
 * @brief Function for delay(not accurate)
 *
 * @param[\] void.
 * 
 * @return  void.
*************************************************/
void delay(uint16_t num)
{
   	u16 i;
    for (i = 0; i < num; i ++)
    {
        Nop();
    }
}
