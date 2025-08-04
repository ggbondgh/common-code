#include "Define.h"
#include "User.h"

/* ������
CLR_RAM(void)
IO_Init(void)
TIMER0_INT_Init(void)
TIMER1_INT_Init(void)
TIMER2_INT_Init(void)
TIMER3_INT_Init(void)
ADC_Init(void)
delay(uint16_t num)
*/

//��Ƶ����
#define  PRS_1   0
#define  PRS_2   1
#define  PRS_4   2
#define  PRS_8   3
#define  PRS_16  4
#define  PRS_32  5
#define  PRS_64  6
#define  PRS_128 7

/************************************************
;  *    @������          : CLR_RAM
;  *    @˵��            : ��RAM
;  *    @�������        :
;  *    @���ز���        :
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
;  *    @������            : IO_Init
;  *    @˵��              : IO��ʼ��
;  *    @�������          :
;  *    @���ز���          :
;  ***********************************************/
void IO_Init(void)
{
    IOP0 = 0x00;                       //io������λ
    OEP0 = 0xff;                       //io�ڷ��� 1:out  0:in
    PUP0 = 0x00;                       //io����������   1:enable  0:disable
    PDP0 = 0x00;                       //io����������   1:enable  0:disable
   
    IOP1 = 0x00;                       //io������λ
    OEP1 = 0xF7;                       //io�ڷ��� 1:out  0:in
    PUP1 = 0x00;                       //io����������   1:enable  0:disable
    PDP1 = 0x00;                       //io����������   1:enable  0:disable
    
    PMOD = 0x07;                       //bit2-bit0 P13��P01��P00 io�˿����ģʽ  1:������� 0:��©���
                                       
    DRVCR = 0x00;                      //��ͨ����

    P1KBCR = 0x08;                      //P1����IO���ѹ���  P17~P10
}

/************************************************
;  *    @������            : TIMER0_INT_Init
;  *    @˵��              : ��ʱ��0��ʼ��
;  *    @�������          :
;  *    @���ز���          :
ʹ��Fcpu���ж�ʱ��= T0LOAD*����Ƶ/Fcpu��=100*(4/4) =100us
;  ***********************************************/
void TIMER0_INT_Init(void)
{
    T0CR = PRS_4; //CPU,4��Ƶ
    T0CNT = 104-1;
    T0LOAD = 104 -1;                 
    T0EN = 1;
    T0IE = 1;
}

/************************************************
;  *    @������            : TIMER1_INT_Init
;  *    @˵��              : ��ʱ��1��ʼ��
;  *    @�������          :
;  *    @���ز���          :
ʹ��Fcpu���ж�ʱ��= T1LOAD*����Ƶ/Fcpu��=250*(32/4) =2ms
;  ***********************************************/
void TIMER1_INT_Init(void)
{
    T1CR = PRS_32; //��ʱģʽ,CPU,32��Ƶ
    T1CNT = 250 -1;                 
    T1LOAD = 250 -1;
    T1EN = 1;
    T1IE = 1;
}

/************************************************
;  *    @������            : TIMER2_INT_Init
;  *    @˵��              : ��ʱ��2��ʼ��
;  *    @�������          :
;  *    @���ز���          :
ʹ��Fcpu���ж�ʱ��= T2LOAD*����Ƶ/Fcpu��=100*(8/4) =200us
;  ***********************************************/
void TIMER2_INT_Init(void)
{
    T2CR = PRS_8;   //CPU,8��Ƶ
    T2CNT = 100 - 1;
    T2LOAD = 100 - 1;                 
    T2EN = 1;
    T2IE = 1;
}

/************************************************
;  *    @������            : TIMER3_INT_Init
;  *    @˵��              : ��ʱ��3��ʼ��
;  *    @�������          :
;  *    @���ز���          :
ʹ��Fcpu���ж�ʱ��= T3LOAD*����Ƶ/Fcpu��=250*(128/4) =8ms
;  ***********************************************/
void TIMER3_INT_Init(void)
{
    T3CR = PRS_128;               //CPU,128��Ƶ
    T3CNT = 250 - 1;
    T3LOAD = 250 - 1;                  
    T3EN = 1; 
    T3IE = 1;
}

/************************************************
;  *    @������            : TIMER0_PWM_Init
;  *    @˵��              : ��ʱ��0,PWM��ʼ��
;  *    @�������          :
;  *    @���ز���          :
;  PWMƵ�� =Fpcu/��Ƶ/T0CNT =4000/4/100 = 10KHz
;  PWMռ�ձ� =T0DATA/T0CNT = 25/100 = 25%
;  PWM0: P02/P16
;  ***********************************************/
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
;  *    @������            : TIMER1_PWM_Init
;  *    @˵��              : ��ʱ��1,PWM��ʼ��
;  *    @�������          :
;  *    @���ز���          :
;  PWMƵ�� =Fpcu/��Ƶ/T1CNT =4000/4/100 = 10KHz
;  PWMռ�ձ� =T1DATA/T1CNT = 25/100 = 25%
;  PWM1: P17
;  FPWM1: P16
;  ***********************************************/
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
;  *    @������            : TIMER2_PWM_Init
;  *    @˵��              : ��ʱ��2,PWM��ʼ��
;  *    @�������          :
;  *    @���ز���          :
;  PWMƵ�� =Fpcu/��Ƶ/T2CNT =4000/4/100 = 10KHz
;  PWMռ�ձ� =T2DATA/T2CNT = 25/100 = 25%
;  PWM2: P15
;  FPWM2: P14
;  NPWM1: P11
;  NFPWM1: P12
;  ***********************************************/
void TIMER2_PWM_Init(void)
{
    T2CR = DEF_SET_BIT6 | PRS_1 | DEF_SET_BIT3;     //ʹ��PWM,CPU,4��Ƶ
    T2CNT = 159-1;
    T2LOAD = 159-1;                                     
    T2DATA = 25;
    PWMCR1 = DEF_SET_BIT4; 
    PWMCR2 = 0x03;                                         //4��ʱ��
    PWMCR3 |= 0x00;//DEF_SET_BIT6 | DEF_SET_BIT5 | DEF_SET_BIT4;  //ʹ��FPWM,NPWM,�������
    T2EN = 1;
}

/************************************************
;  *    @������            : ADC_Init
;  *    @˵��              : ADC��ʼ��
;  *    @�������          :
;  *    @���ز���          :
;  ***********************************************/
void ADC_Init(void)
{
    //OEP1 &= DEF_CLR_BIT0;                        //P10Ϊ�����
    OEP0 &= DEF_CLR_BIT4;                        //P01Ϊ����� 

    ADIOS0 = 0x08;                     //io����ѡ��  1:ģ������  0:ͨ��io
//bit7~0  P12 P11 P10 P05 P04 P03 P02 P00

   	ADIOS1 = 0x00;                     //io����ѡ��  1:ģ������  0:ͨ��io
//bit1~0  P15 P14 

    PMOD = 0x07;                       //bit7-bit5 P17��P13��P01 io����ѡ�� 1:ģ������  0:ͨ��io 
                                       //bit2-bit0 P13��P01��P00 io�˿����ģʽ  1:������� 0:��©���

    ADCR0 = 0xfb;                                //ʹ��ADC��12λ����H8L4
    ADCR1 = 0x80;                                //32��Ƶ���ڲ�2V 
    ADCR2 = 0xff;                                //�̶�Ϊ15ADCLK 
    Set_ADC_Channel(3);         // ADC ʹ��  ADת��ͨ������  ͨ��  CHX
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
;  *    @������            : delay
;  *    @˵��              : ����ȷ��ʱ����
;  *    @�������          :
;  *    @���ز���          :
;  ***********************************************/
void delay(uint16_t num)
{
   	u16 i;
    for (i = 0; i < num; i ++)
    {
        Nop();
    }
}

