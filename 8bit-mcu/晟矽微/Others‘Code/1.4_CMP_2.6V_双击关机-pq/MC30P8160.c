//;****************************************************************************
/******************************************************************************
  * MC30P8160 �����ο�����
  * ˵����
  * 1.��ʵ��4�����أ������Demo����
  * 2.�������ŵ�TK�����ϣ�ͨ���ִ�����LED�����
  * 3.ģ�⴮�ڴ�ӡTK���ݹ���
  *	  �ͻ���ͨ����Ӵ��ڹ��ߣ�ʹ�ܴ��ں���Uart_Process()����TK���ݴ�ӡ��������
  ******************************************************************************
  * ��������ָ���÷�
  *	   	stopָ� Stop();
  *	   	�幷ָ� Clrwdt();
  *	   	��ָ�   Nop();
  ******************************************************************************
 ******************************************************************************/

#include "MC30P8160_include.h"
#include "MC30P8160_MAIN.h"

//#define  Uart

#define  PWM_Max_Value     200 // 200 100%
#define  PWM_Min_Value     58  // 200 10%

//#define  Hall_IN     	  P14D  // 1�� �������� ����Ч  ���ռ��
//#define  Hall_EN_IN      	P11D  // 6�� ����ѡ��� ����Ч  ��������

// ����Ƶ  4.8M
#define	   	TK_SENS_LEVEL_H1  0x13     	   	   //;TK0���������ȼ���1
#define	   	TK_SENS_LEVEL_H2  0x13     	   	//;TK0���������ȼ���2
#define	   	TK_SENS_LEVEL_H3  0x15     	   	//;TK0���������ȼ���3
#define	   	TK_SENS_LEVEL_L   0xFF     	   	//;TK0���������ȼ���


#define FilterCnt_Value    	8
#define Const_SEN_T_Key0   	40
//#define Const_SEN_T_Key0_Release  60

// ����
// λ����
#define    	T_Key0_Signal      	flag1.bits.bit0    	   	 // ��־λ
#define    	Pre_T_Key0_Release  flag1.bits.bit1	   	 // ��־λ
#define    	TK0_Release_Flag    flag1.bits.bit2	   	 // ��־λ
#define    	TK0_Filter_Flag     flag1.bits.bit3	   	 // ��־λ
#define    	T0_5ms_Flag        	flag1.bits.bit4	   	 // ��־λ
#define    	T0_25ms_Flag        flag1.bits.bit5	   	 // ��־λ
#define    	T_Long_press_Flag   flag1.bits.bit6	   	 // ��־λ
#define    	PWM_Flag_key        flag1.bits.bit7	   	 // ��־λ

#define    	Power_ONOFF_Flag       	flag2.bits.bit0    // ��־λ
#define    	PWM_Change_KeyFlg      	flag2.bits.bit1    // ��־λ
#define    	TK0_Key_Release_Flag    flag2.bits.bit2    // ��־λ
#define     T0_5ms_Flag_PWM        	   	flag2.bits.bit3    // ��־λ
#define     T0_10ms_Flag_PWM       	   	flag2.bits.bit4    // ��־λ
#define    	BAT_Low_V_Flag         	flag2.bits.bit5    // ��־λ
#define    	SW1_Short_2_Flag           	  flag2.bits.bit6    // ��־λ

//uint8_t T_Key0_Signal;
//uint8_t Pre_T_Key0_Release;
//uint8_t TK0_Release_Flag;

uint16_t u16_TK_Cnt; // ������

uint16_t u16_get_val;      	   	//��ȡֵ
uint16_t u16_Press_val;     //����
uint16_t u16_release_val;      	//�ɿ�
uint16_t u16_release_val_TK0;
uint16_t u16_temp_val;
uint16_t u16_get_val_Temp;
uint16_t u16_get_val_Min;

uint16_t u16_TK0_environment_val;
uint32_t u16_TK0_environment_val_Sum;

///////////////////////////////////////

unsigned char TK0_Filter_Cnt;
//unsigned char TK0_Filter_Flag;
//unsigned char TK0_Release_Cnt;
unsigned char FilterCnt_TK0;
unsigned char SleepCnt = 00;  //˯�߼���


// PWM
//uint8_t PWM_Duty_Temp;
uint8_t PWM_Duty_W;
//uint8_t PWM_Duty_Y;
uint8_t PWM_Duty_WY;
uint8_t PWM_Duty_WY_Temp;
uint8_t T_key_Value; // 0 1 2 3 
uint8_t TK0_Key_Cnt;
uint8_t Power_Low_V_OFF_Cnt;

// ����
//uint8_t Hall_Flag;
//uint8_t Hall_5ms_Cnt_1 = 0;
//uint8_t Hall_5ms_Cnt_2 = 0;


uint8_t T0_5ms_Cnt;


// ����
#define  Uart_TX     P14D

//#define Uart // �رմ���

unsigned char uart_send_c = 0;


/************************************************
������:   	Init_Sys
˵��:
************************************************/

void TOUCH_TK0_OUT(void);

void Delay_us_2(uint16_t i)
{
   	for(; i>0; i--)
    {
   	   	WDT_Clear();
    }
}


void Delay_us(unsigned char i)
{
   	while(i--);
}
  
#ifdef Uart    	
   	   	
void Uart_Send_One_Byte(void) // 19200  52us delay(10) 4M
{
   	Uart_TX = 0;   	   	   	//��ʼλ  	   	
   	Delay_us(11);

   	unsigned char bit_cnt = 0;

   	while(bit_cnt < 8) 	   	//8������λ���ȷ���λ�ٷ���λ
   	{  	   	   	   	   	
   	   	if(uart_send_c & 0x01)
   	   	{
   	   	   	Uart_TX = 1;
   	   	}
   	   	else
   	   	{
   	   	   	Uart_TX = 0;
   	   	}

   	   	uart_send_c >>= 1; 	//����һλ

   	   	bit_cnt ++;

   	   	Delay_us(10);
   	}
   	Uart_TX = 1;   	   	   	//ֹͣλ
   	Delay_us(10);
}


void Uart_Send_Data(void) // 19200  P14
{
       	uart_send_c = u16_get_val & 0x00FF;
       	Uart_Send_One_Byte();
       	uart_send_c =  (u16_get_val & 0xff00) >> 8; 
       	Uart_Send_One_Byte();

       	uart_send_c = u16_TK0_environment_val & 0x00FF;
       	 Uart_Send_One_Byte();
       	uart_send_c =  (u16_TK0_environment_val & 0xff00) >> 8; 
       	Uart_Send_One_Byte();

   	uart_send_c = u16_TK_Cnt & 0x00FF;
   	Uart_Send_One_Byte();
   	uart_send_c =  (u16_TK_Cnt & 0xff00) >> 8; 
   	Uart_Send_One_Byte();

  //   	uart_send_c = u16_TK_Cnt & 0x00FF;
  //   	Uart_Send_One_Byte();
  //   	uart_send_c =  (u16_TK_Cnt & 0xff00) >> 8; 
  //   	Uart_Send_One_Byte();


}
#endif

void  Init_Sys(void)
{  	   	   	
   	__asm
SET_OPTION:
   	MOVAI   00001111B  	   	//;I/O�����ֹ����趨,0����Ч
   	MOVRA   P1ADCR
   	MOVAI   00111111B  	   	//;P10,P11,P12,P12����ڣ�P14,P15����ڣ�1Ϊ���룬0Ϊ���
   	MOVRA   DDR1
   	MOVAI   00000000B  	   	//; �˿�д0
   	MOVRA   P1
   	
   	MOVAI   0xFF   	   	   	//;��������,1����Ч
   	MOVRA   PDCON

   	MOVAI   0xFF   	   	   	//; ��������,1����Ч
   	MOVRA   PUCON  	   	   	//;

   	MOVAI   0x00   	   	   	//;��©����,1�ǿ�©,0������
   	MOVRA   ODCON

//;��ʱ���趨 
//; T0     	   	   	   	011 256��Ƶ(ϵͳʱ����256��Ƶ)
    MOVAI   00000111B  	   	//;��ʱ��0����,BIT0-2:��ʱ����Ƶ,BIT3��ʱ������:1-WDT,0-TC0
    MOVRA   T0CR   	   	   	//;BIT4:0-�����ؼ���1-�½��ؼ���,BIT5:ʱ��Դ0-FCPU,1-�ⲿ;BIT6:1-�����ش���0-�½��ش���
    MOVAI   217    	   	   	  //;131
    CLRR   	T0CNT  	   	   	//;�嶨ʱ��0����ֵ;T0û���Զ������������Լ���ֵ��256Ϊ��׼���������ж���ı�T0CNTֵ

//; T1 
   	MOVAI   00000000B  	   	//;��ʱ��1����,BIT7=T1EN, BIT6=PWM1AOE,1����PWM, BIT5=PWM1AEN,1ʹ��PWM1A
   	MOVRA   T1CR   	   	   	//;BIT4.3:T1ʱ��Դѡ��,BIT2-0:T1��Ƶ
   	CLRR   	T1CNT  	   	   	//;�嶨ʱ��1����ֵ
   	CLRR   	T1LOAD
   	MOVAI  	00000000B
   	MOVRA  	TMRCR  	   	   	//;BIT6=T0TBS,BIT3=T2IE,BIT2=T2IF,BIT1=T1IE,BIT0=T1IF
   	MOVAI  	00000000B
   	MOVRA  	PWM1CR0	   	   	//;�ر�PWM
   	MOVAI  	00000000B
   	MOVRA  	PWM1CR1
   	MOVAI  	00000000B
   	MOVRA  	PWM1CR2
   	CLRR   	T1DATA
   	CLRR   	T1DATB
   	CLRR   	T1DATC
   	CLRR   	T1DATD

//; T2  ����
//;	MOVAI   00000010B  	   	//;��ʱ��2����,BIT0-2:��ʱ����Ƶ,BIT3��ʱ������:1-WDT,0-TC0
//;	MOVRA   T2CR   	   	   	//;BIT4:0-������1-�½���,BIT5:��
//;	MOVAI   0XF0
//;	MOVRA  	T2CNTL 	   	   	//;�嶨ʱ��2����ֵ
//;	MOVRA  	T2LOADL	   	   	//;�嶨ʱ��2����ֵ
//;	MOVAI   0X6D
//;	MOVRA  	T2LOADH	   	   	//;�嶨ʱ��2����ֵ
   	
   	MOVAI   00000001B
   	MOVRA   INTECON	   	   	//;BIT7=GIE,���ж�,BIT0=T0IE,BIT1=KBIE,BIT2=INT0IE,1-�ж�ʹ��
   	BSET   	INTECON,7  	   	//;GIE
 //    	BSET   	T0IE   	   	   	//;
   	MOVAI   0x00
   	MOVRA   INTFLAG	   	   	//;BIT0=T0IF,BIT1=KBIF,BIT2=INT0IF,1-�жϷ���
   	MOVAI   0x00   	   	   	//;P14,P15,P13�����жϹ��ܿ�
   	MOVRA   KBIM
   	RETURN
    __endasm;
} 
/************************************************
������:   	Clr_Ram
˵��:
************************************************/
void  Clr_Ram(void)
{
   	__asm
CLR_RAM:
   	MOVAI  	0X4F
   	MOVRA  	FSR
   	MOVAI  	0X3F
   	MOVRA  	0X4F   	   	   	;//�ѼĴ������������浽���һ���Ĵ�����
CLR_RAM_LOOP:
   	DECR   	FSR
   	CLRR   	INDF
   	DJZR   	0X4F
   	GOTO   	CLR_RAM_LOOP
   	RETURN
    __endasm;
}   


void T1_PWM_Init(void)
{
    T1CR = 0x89;    // 100_01_001 ʹ��T1��ʱ��ΪFOSC��2��Ƶ
    T1CNT = PWM_Max_Value - 1;
    T1LOAD = PWM_Max_Value - 1;    	   	//30k
//    T1DATA = 0;
//    T1DATB = 0;
//    T1DATC = 0;
// 	  T1DATD = 0;

   	T1DATD = 0;
   	PWM1DOE = 0; //��ֹ�˿����������Ʋ��Σ�
   	PWM1DEN = 0; //�ر� PWM1D ���ܣ�

   	T1DATC = 0;
   	PWM1COE = 0; //��ֹ�˿����������Ʋ��Σ�
   	PWM1CEN = 0; //�ر� PWM1C ���ܣ�

   	T1DATB = 0;
   	PWM1BOE = 0; //��ֹ�˿����������Ʋ��Σ�
   	PWM1BEN = 0; //�ر� PWM1B ���ܣ�

    // �ߵ�ƽʱ�� =��T2DATx�� �� T2CNT ����ʱ������
    // ���ڣ�T2 ��������ڣ� =��T2LOAD+1�� �� T2CNT ����ʱ������
    // ռ�ձ� = �ߵ�ƽʱ�� / ���� =��T2DATx�� /��T2LOAD+1��
    //  PWM1CR0 = 0x03;   //PWM1A�˿����PWM���������
                          //PWM1B�˿����PWM���������
}



void IO_Init(void)
{
   	P1 = 0x00; //  	P1nD �C P1n �˿�����λ��n=5-0��

   	//xx11_1011;   	0 ���   1����
   	DDR1 = 0x33;   	   // DR1n �C P1n �˿ڷ������λ��n=5-0��  0�� �˿���Ϊ�����
   	//  P12   �����  P10 P11 P13 P14 P15����


   	// xx11_0011
   	P1ADCR = 0x33;   // 0 ʹ�ܶ˿ڵ����� I/O ���ܣ� 1 �رն˿ڵ����� I/O ���ܣ�
   	
   	// 1111_1101 P11
   	PUCON = 0xFF; //  1���˿��ڲ�����������Ч��  0���˿��ڲ�����������Ч
   	PDCON = 0xFF; //  1���˿��ڲ�����������Ч��  0���˿��ڲ�����������Ч

   	ODCON = 0x00; // 0�� �˿����ʱΪ�������   1 ��©���
}


//void TK_Sens_Threshold_value_Detection(void)
//{
//     	u16_TK_Cnt = 0;
//
//     	DDR1 &= 0xDF; // P15 ����� 0 ���
//     	PUCON |= 0x20; //  1���˿��ڲ�����������Ч��  0���˿��ڲ�����������Ч
//     	PDCON |= 0x20; //  1���˿��ڲ�����������Ч��  0���˿��ڲ�����������Ч
//     	P15D = 0;
//
//     	Delay_us(0xff); //
//
//     	DDR1 |= 0x20; // P15 �����  1 ����
//     	
//     	P1ADCR &= 0xDF;   // 0 ʹ�ܶ˿ڵ����� I/O ���ܣ� 1 �رն˿ڵ����� I/O ���ܣ�
//     	PUCON &= 0xDF; 	  //  1���˿��ڲ�����������Ч��  0���˿��ڲ�����������Ч
//
//     	while(P15D == 0)
//    {
//     	   	u16_TK_Cnt ++;
//     	 //   if(u16_TK_Cnt == 20000)
//      //  {
//     	  //       	   	break;
//      //  }
//     	 //    	WDT_Clear();
//    }
//     	   	   	   	   	   	   	   	   	// LDO 3.3V
//     	if(u16_TK_Cnt > 250) // 47nF
//    {
//     	   	T2LOADH = TK_SENS_LEVEL_H3;
//     	   	T2LOADL = TK_SENS_LEVEL_L;
//    }
//    else if(u16_TK_Cnt > 180)// 27nF
//    {
//     	   	T2LOADH = TK_SENS_LEVEL_H2;
//     	   	T2LOADL = TK_SENS_LEVEL_L;
//    }
//    else if(u16_TK_Cnt > 50) //10NF
//    {
//     	   	T2LOADH = TK_SENS_LEVEL_H1;
//     	   	T2LOADL = TK_SENS_LEVEL_L;
//    }
//     	else //if(u16_TK_Cnt > )
//    {
//     	   	T2LOADH = TK_SENS_LEVEL_H1;
//     	   	T2LOADL = TK_SENS_LEVEL_L;
//    }
//     	
//     	Delay_us(0xff); //
//     	Delay_us(0xff); //
//
//     	PUCON |= 0x20;  //  1���˿��ڲ�����������Ч��  0���˿��ڲ�����������Ч
//     	DDR1 &= 0xDF;   // P15 ����� 0 ���
//}

/************************************************
������:������ʼ��
˵��:
************************************************/
void TOUCH_Init(void)
{
__asm 

//SET_TOUCH_OPTION:
//    MOVAI   0x01;    	   	   	   	//;00000011B
//     	MOVRA   P1ADCR 	   	   	   	   	//;�趨��Ӧ��TK��Ϊ�����ֹ��ܣ�1Ϊ�����ֹ���
//     	ORRA   	DDR1   	   	   	   	   	//;ֻ�趨TK��Ϊ����ģʽ���������䡣����/�����1Ϊ���룬0Ϊ���
  //   	MOVRA  	TOUCH_FLAG
  //   	SWAPR  	TOUCH_FLAG 	   	   	   	//;����Ӧ��TK ʹ�ܴ�����Ҫˢ�»�׼���ݣ�TOUCH_NEW_FLAG��
   	BCLR   	_T2IE  	   	   	   	   	//;����ҪT2�жϣ�TK����ɨ�跽ʽ
  //   	MOVAI  	11001000B  	   	   	   	//;��ʱ��0����,BIT7Ϊ��ʱ��2����,BIT6Ϊ��ʱ��2����/���μ���ģʽ,BIT4-3:ʱ��Դѡ��,BIT0-2:��ʱ����Ƶ
  //   	ORRA   	T2CR   	   	   	   	   	//;����T2��ʱ��������Ϊ���μ�ʱģʽ
   	MOVAI  	00000000B
   	MOVRA  	TKCR0  	   	   	   	   	//;TK��������,BIT7=1����TK,BIT6=1��������ŵ�,BIT5/4ΪTKʱ���˲�,BIT3:TK��Ƶ,BIT2-0:TK��Ƶ��ѡ��
   	MOVAI   11111111B  	   	   	   	//;ѡ��ͨ��0
   	MOVRA  	TKCR2  	   	   	   	   	//;TK��������,BIT7=1ʹ��TK����,BIT6:TKM�����ж�,BIT2/0:ѡ������ͨ��
   	RETURN
__endasm;
}

void TK0_Init(void)
{

   	TKCR1 = 0x00; // �رմ���
   	TKCNTH = 0;
   	TKCNTL = 0;

   	T2MOD = 1;   // ���μ�ʱģʽ������ģʽ��
   // T2CR = 0x49; // 01_0_01_000 FOSC 2��Ƶ
   	T2CR = 0x4A;   // 01_0_01_010 FOSC 16M 4��Ƶ 4M

//     	T2LOADH = 0x08;
//     	T2LOADL = 0xFF;

       	T2LOADH = TK_SENS_LEVEL_H1;
       	T2LOADL = TK_SENS_LEVEL_L;
//     	T2LOADH = 0x52; // 101:5 ��Ƶ  400 1024
//     	T2LOADL = 0xFF;

   	TKCR1 &= 0xFC; // д0000_0000 bit0-1: 00 TK0 ѡ����Ӧ��������ͨ��

   	TKCR0 = 0xF4;  // д1111_0000 bit0-3: 000 TK0 ѡ�� 4.8MHz

 //    	TKCFL = 0; 	   // TKM ����ʱ���˲�ʱ�䣨����ֵ��Ϊ 10ns��
   	TKCFL = 1; 	 // TKM ����ʱ���˲�ʱ�䣨����ֵ��Ϊ 50ns��

 //    	TKFJE = 1; 	// ���� TKM �Զ���Ƶ����
   	TKFJE = 0; 	// �ر� TKM �Զ���Ƶ����
   	T2EN = 1;  	// ������ʱ�� T2
   	TKCON = 1; 	// ���� TKM ���ݳ�ż���
   	TKEN = 1;  	// ���� TKM      	   	
   	
}

void TK0_release_(void)
{
   	T_Key0_Signal = 0;

   	Pre_T_Key0_Release = 1;	   	   	   	   	
   	u16_TK0_environment_val = u16_get_val;
   	TK0_Filter_Cnt = 0;
   	u16_TK0_environment_val_Sum = 0;

   	TK0_Release_Flag = 1;

   	u16_get_val_Min = 0xFFFF;
}

void TK0_Scan(void)
{
   	// P10 ��Ϊ���룬�ر�����IO����
   	DDR1 |= 0x01;     // 1�� �˿���Ϊ�����          0�� �˿���Ϊ�����
   	P1ADCR |= 0x01;   // 0 ʹ�ܶ˿ڵ����� I/O ���ܣ� 1 �رն˿ڵ����� I/O ���ܣ�

   	TK0_Init();

   	while(TKCF == 1)
    {
   	   	WDT_Clear();
    }
    u16_get_val =  (TKCNTH << 8) | TKCNTL;

   	TKCON = 0;  // �ر� TKM ���ݳ�ż�����
   	TKCNTH = 0; // ��TOUCH����,�����ֹ�����
   	TKCNTL = 0;

   	// P10 ��Ϊ�����������IO����
   	DDR1 &= 0xFE;     // 1�� �˿���Ϊ�����         0�� �˿���Ϊ�����
   	P1ADCR &= 0xFE;   // 1 �رն˿ڵ����� I/O ���ܣ� 0 ʹ�ܶ˿ڵ����� I/O ���ܣ� 
   	P10D = 0;

   	u16_temp_val = u16_get_val + Const_SEN_T_Key0 - 10;
   	if(u16_temp_val < u16_TK0_environment_val)
    {
   	   	SleepCnt = 0xff;
   	}

   	u16_temp_val = u16_get_val_Temp << 2;
   	u16_temp_val -= u16_get_val_Temp;
   	u16_temp_val += u16_get_val;
   	u16_get_val_Temp = u16_temp_val >> 2;

    u16_get_val = u16_get_val_Temp;

   	if(Pre_T_Key0_Release) 
   	{
   	   	u16_Press_val = u16_get_val + Const_SEN_T_Key0;
   	   	
   	   	if(u16_Press_val < u16_TK0_environment_val)	 //����
   	   	{
   	   	   	SleepCnt = 0xFF;
   	   	   	FilterCnt_TK0 ++;
   	   	   	if(FilterCnt_TK0 > FilterCnt_Value)
   	   	   	{
   	   	   	    T_Key0_Signal = 1;
   	   	   	   	Pre_T_Key0_Release = 0;
   	   	   	   	u16_release_val_TK0 = u16_TK0_environment_val - Const_SEN_T_Key0; //
   	   	   	}
   	   	}
   	   	else //���»���ֵ
   	   	{
   	   	   	FilterCnt_TK0 = 0;

   	   	   	if(SleepCnt)
   	   	   	{
   	   	   	   	if(TK0_Filter_Flag)
   	   	   	   	{
   	   	   	   	   	TK0_Filter_Flag = 0;
   	   	   	   	}
   	   	   	   	else
                {
   	   	   	   	   	TK0_Filter_Flag = 1;
   	   	   	   	   	u16_TK0_environment_val_Sum += u16_get_val;
   	   	   	   	   	TK0_Filter_Cnt++;
                }
   	   	   	   	
   	   	   	   	if(TK0_Filter_Cnt > 15)
   	   	   	   	{
   	   	   	   	   	TK0_Filter_Cnt = 0;
   	   	   	   	   	u16_TK0_environment_val = u16_TK0_environment_val_Sum >> 4;
   	   	   	   	   	u16_TK0_environment_val_Sum = 0;

   	   	   	   	   	if(TK0_Release_Flag)
   	   	   	   	   	{
   	   	   	   	   	   	TK0_Release_Flag = 0;
   	   	   	   	   	   	u16_TK0_environment_val = u16_get_val;
   	   	   	   	   	}
   	   	   	   	}
   	   	   	}
   	   	   	else
   	   	   	{
   	   	   	   	u16_TK0_environment_val = u16_get_val;
   	   	   	   	u16_TK0_environment_val_Sum = 0;
   	   	   	   	TK0_Filter_Cnt = 0;
   	   	   	}
   	   	   	
   	   	   	if(TK0_Release_Flag == 1)
   	   	   	{
   	   	   	   	if(u16_get_val > u16_TK0_environment_val)
   	   	   	   	{
   	   	   	   	   	u16_TK0_environment_val = u16_get_val;
   	   	   	   	}
   	   	   	}
   	   	}
   	}
   	else  
   	{
   	  //   	FilterCnt_TK0 = 0;

   	   	TK0_Filter_Cnt++;

   	   	if(TK0_Filter_Cnt >= 2) // 10ms
   	   	{
   	   	   	TK0_Filter_Cnt = 0;

   	   	   	if(u16_get_val <= u16_TK0_environment_val) //����С�ڵ��ڣ�����ֻС��
   	   	   	{
   	   	   	   	u16_TK0_environment_val = u16_get_val;
   	   	   	}
   	   	   	else
   	   	   	{
   	   	   	   	u16_TK0_environment_val ++;
   	   	   	}

   	   	   	if(u16_get_val < u16_get_val_Min)
            {
   	   	   	   	u16_get_val_Min = u16_get_val;
            }
   	   	}

   //  	   	if(u16_get_val > u16_TK0_environment_val)
   //  	   	{
   //  	   	   	u16_release_val = u16_get_val - u16_TK0_environment_val;   	
   //  	   	}
   //  	   	else
   //  	   	{
   //  	   	   	u16_release_val = 0;
   //  	   	}
   	   	u16_temp_val = u16_release_val_TK0 + Const_SEN_T_Key0 + u16_get_val_Min;
   	   	u16_temp_val = u16_temp_val >> 1;

   	   	if(u16_get_val > u16_release_val_TK0 || u16_get_val > u16_temp_val)	//�ɿ�
   	   	{
   	   	   	FilterCnt_TK0 ++;
   	   	   	if(FilterCnt_TK0 >= 4) //�����ɿ��˲� 20ms
   	   	   	{
   	   	   	   	FilterCnt_TK0 = 0;

   	   	   	   	TK0_release_();
   	   	   	}
   	   	}
   	   	else
   	   	{
   	   	   	FilterCnt_TK0 = 0;
   	   	}  	
    }  	
}
///////////////////////////////////////////////

void PWM_Direction_Judgment(void)
{
   	if(PWM_Duty_W > 100) // 200 max
   	{
   	   	PWM_Flag_key = 1;  //����������־λ״̬�任
   	}
   	else
   	{
   	   	PWM_Flag_key = 0;  //����������־λ״̬�任
   	} 
}

uint8_t Key1PressCnt_Short;
//uint8_t SW1_Short_2_Flag;

void T_Key_value_Read(void)
{
   	if(T_Key0_Signal && TK0_Key_Release_Flag == 0) //�а�������
   	{
   	   	TK0_Key_Cnt ++;

   	   	if(TK0_Key_Cnt == 100 && Power_ONOFF_Flag) //500ms
   	   	{
   	   	   	TK0_Key_Release_Flag = 1;

   	      //   	TK0_Key_Cnt = 60;  	
       	   	TK0_Key_Release_Flag = 1; 

   	       	if(T_Long_press_Flag == 0)
   	       	{
       	   	   	T_Long_press_Flag = 1; 	//������־λ��1

       	   	   	PWM_Change_KeyFlg = 1;

       	   	   	PWM_Flag_key = !PWM_Flag_key;  	//����������־λ״̬�任
   	       	 }
   	   	}
   	}
   	else if(!T_Key0_Signal)
   	{
   	   	T_Long_press_Flag = 0; 	//������־λ��0

   	   	if(TK0_Key_Cnt > 1 && TK0_Key_Cnt < 100) // 500ms 
   	   	{  	   	
   	   	   	SW1_Short_2_Flag = 1;  	  

   	   	   	if(Key1PressCnt_Short > 0 && Key1PressCnt_Short < 50) //���μ��С��0.35s��  ˫��
   	   	   	{
   	   	   	   	SW1_Short_2_Flag = 0;
   	   	
           	   	Power_ONOFF_Flag = 0;  // ˫���ػ� 
   	   	   	   	PWM_Change_KeyFlg = 1;         	  
   	   	   	   	   	
   	   	   	  //   	PWM_Direction_Judgment();  	   	   	   	   	   	   	   	
   	   	   	}

   	   	   	Key1PressCnt_Short = 0;
   	   	}

   	   	TK0_Key_Cnt = 0;   	// �����ۼ�ֵ��0
   	   	TK0_Key_Release_Flag = 0;

   	   	if(SW1_Short_2_Flag == 1)  // �̰��ɿ���ʱ
   	   	{
   	   	   	Key1PressCnt_Short ++; 

   	   	   	if(Key1PressCnt_Short >= 10 && Power_ONOFF_Flag == 0 ) //���ΰ��´�Լ0.4s���޲�����  ����
   	   	   	{
   	   	   	   	Power_ONOFF_Flag = 1;    // �̰�����
   	   	   	   	Key1PressCnt_Short = 0;
   	   	   	   	SW1_Short_2_Flag = 0;

   	   	   	   	PWM_Change_KeyFlg = 1;
   	   	   	   	PWM_Direction_Judgment();
   	   	   	}

   	   	   	if(Key1PressCnt_Short >= 50 ) //���ΰ��´�Լ0.4s���޲�����  ����
   	   	   	{
   	   	   	   	SW1_Short_2_Flag = 0;
   	   	   	   	Key1PressCnt_Short = 0;
   	   	   	   	
   	   	   	   	if(Power_ONOFF_Flag == 0)
                {
   	   	   	   	   	Power_ONOFF_Flag = 1; // �̰�����
                }
                else 
                {  	   	   	   	
       	   	   	   	T_key_Value ++;
       	   	   	   	if(T_key_Value > 3) // ��ɫ
       	   	   	   	{
       	   	   	   	   	T_key_Value = 1;
       	   	   	   	}
   	   	   	   	}
   	   	   	   	
   	   	   	   	PWM_Change_KeyFlg = 1;
   	   	   	   	PWM_Direction_Judgment();
   	   	   	}
   	   	}
   	   	
   	   	TK0_Key_Release_Flag = 0;
   	   	TK0_Key_Cnt = 0;   	//���������ۼ�ֵ��0
   	}
}

void PWM_W_OFF(void)
{
   	T1DATD = 0;
   	PWM1DOE = 0; //��ֹ�˿����������Ʋ��Σ�
   	PWM1DEN = 0; //�ر� PWM1D ���ܣ�
}

void PWM_Y_OFF(void)
{
   	T1DATC = 0;
   	PWM1COE = 0; //��ֹ�˿����������Ʋ��Σ�
   	PWM1CEN = 0; //�ر� PWM1C ���ܣ�
}


void LED_PWM_Control(void)
{
   	if(PWM_Change_KeyFlg == 1)     	//����ֵ�ı����״̬
   	{

   	    PWM_Change_KeyFlg = 0;

   	   	if(Power_ONOFF_Flag == 0) //ȫ��
   	   	{
   //  	   	   	PWM_Duty_W = 127; // �������ȼ���
   //  	   	   	if(PWM_Duty_Temp)
   //         {
   //  	   	   	   	PWM_Duty_Temp --;
   //  	   	   	   	T1DATD = PWM_Duty_Temp; //PWM_Duty_W
   //         }
   //  	   	   	else
   //         {
   //  	   	   	   	PWM_W_OFF();
   //  	   	   	   	PWM_Change_KeyFlg = 0;
   //         }
   	   	   	PWM_W_OFF();
   	   	   	PWM_Y_OFF();
   	   	}
   	   	else if(T_key_Value == 3)      	// W
   	   	{
   	   	  //   	PWM_W_OFF();
   	   	   	PWM_Y_OFF();

   	   	  //   	T1DATD = PWM_Duty_Temp; //PWM_Duty_W
   	   	  //   	   	PWM_Duty_Temp = 150;
   	   	  //   	   	PWM_Duty_W = 178;
   	   	  //   	   	u16_temp_val = PWM_Duty_Temp * PWM_Duty_W;
   	   	  //   	    PWM_Duty_Temp =    	u16_temp_val >> 8;

   	   	   	u16_temp_val = PWM_Duty_W * 108; //42% x 0XFF
   	   	    PWM_Duty_WY_Temp = u16_temp_val >> 8;

   	   	   	T1DATD = PWM_Duty_WY_Temp; //PWM_Duty_W
   	   	   	PWM1DOE = 1; //�򿪶˿����������Ʋ���
   	   	   	PWM1DEN = 1; //�� PWM1D ���� 	
   	   	}

   	   	else if(T_key_Value == 2)      	// Y
   	   	{
   	   	       	PWM_W_OFF();
   	   	  //   	PWM_Y_OFF();
   	   	 //    	u16_temp_val = PWM_Duty_W * 108; //42% x 0XFF
   	   	    PWM_Duty_WY_Temp = u16_temp_val >> 8;

   	       	 T1DATC = PWM_Duty_WY_Temp; 
   	       	  PWM1COE = 1; //�򿪶˿����������Ʋ���
   	       	  PWM1CEN = 1; //�� PWM1D ����   	
   	   	}

   	   	else if(T_key_Value == 1)      	// WY  50%
   	   	{
   	   	 //    	PWM_W_OFF();
   	   	  //   	PWM_Y_OFF();
   	   	 //    	PWM_WY_OFF();
   	
   	   	 //    	  PWM_Duty_WY_Temp = 167; // 80% 255
   	   	      u16_temp_val = PWM_Duty_W * 132; //51% x 0XFF
   	   	      PWM_Duty_WY_Temp = u16_temp_val >> 8;

       	   	//     	PWM_Duty_WY_Temp = PWM_Duty_WY >> 1;

       	   	   	T1DATD = PWM_Duty_WY_Temp;
       	   	   	PWM1DOE = 1; //�򿪶˿����������Ʋ���
       	   	   	PWM1DEN = 1; //�� PWM1D ���� 	 

       	   	   	T1DATC = PWM_Duty_WY_Temp;
       	   	   	PWM1COE = 1; //�򿪶˿����������Ʋ���
       	   	   	PWM1CEN = 1; //�� PWM1D ���� 	   	
   	   	}
   	}


   	if(T_Long_press_Flag) //�����޼����⣨255����
   	{
   	   	PWM_Change_KeyFlg = 1;

   	   	if(PWM_Flag_key )  	//�𽥱䰵
   	   	{
   	   	   	
   	   	   	if(PWM_Duty_W < PWM_Max_Value) //������� 100%
   	   	   	{
   	   	   	   	PWM_Duty_W ++;
   	   	   	}
   	   	   	
   	   	   	
   	   	}
   	   	else   	//�𽥱���
   	   	{  	   	   	   	
   	   	   	if(PWM_Duty_W > PWM_Min_Value ) //��С����PWMֵ��255 * 8%��
   	   	   	{
   	   	   	   	PWM_Duty_W --; 
   	   	   	}  	   	  
   	   	}
   	}
}

void TK_3S_Reset(void)
{
   	if(T_Key0_Signal)
    {
   	   	Power_Low_V_OFF_Cnt ++;

   	   	if(Power_Low_V_OFF_Cnt >= 255) // 25ms 6S
        {
   	   	   	Power_Low_V_OFF_Cnt = 0;

   	   	   	TK0_release_();
        }
    }
    else
    {
   	   	Power_Low_V_OFF_Cnt = 0;
    }
}

// ˯��ģʽ

void Sleep_mode(void)
{
   	if(SleepCnt) 
   	{
   	   	SleepCnt--;
   	}

   	if(T_key_Value || T_Key0_Signal)
   	{
   	   	SleepCnt = 0xFF; // 
   	}


   	if(!SleepCnt)
   	{

   	   	TKEN = 0;       //�ر�TK
   	 //    	CMPCR0 = 0x00;  //�ر�CMP

   	   	SLEEP();   //�������ֱ�д��ʽ(��ʽ��)

   	 //    	Timer16_Init(); //1ms  //�л���ʱ����ʱ��

   	   	TKEN = 1;  	   //��TK
   	 //    	CMPCR0 = 0x81;//����CMP ����VIR ��:VDD��ѹ���� ����CMP�˿���� ����޻���

   	//     	T0_5ms_Flag = 1;
   //  	   	T0_25ms_Flag = 1;

   	}
}

/************************************************
;  *    @������            : CMP_Init
;  *    @˵��              : �Ƚ�����ʼ��
;  *    @�������          :
;  *    @���ز���          :
;  ***********************************************/
void CMP_Init(void)
{
    CMPCR0 = 0x80;//����CMP ����VIR ��:VDD��ѹ���� ����CMP�˿���� ����޻���
    CMPCR1 = 0x1E;//���ֵ2.6V 
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    CMPCR2 = 0x02;           //�ж�,�����ش���    ��ѹ�ߵ���
  //   	CMPCR2 = 0x06;           //�ж�,�½��ش���  ��ѹ�͵���
}
   	
/************************************************
������:������
˵��:
************************************************/
void main()
{      	                 
   	   	Clr_Ram();
   	   	Init_Sys();

   	   	IO_Init();

   	   	Delay_us_2(0x8003); // 4M Լ100ms

   	//     	TK_Sens_Threshold_value_Detection();

   	   	TOUCH_Init(); // ���ô����Ĵ��� 

   	   	T1_PWM_Init();
   	   	SleepCnt = 0xff;
   	 //    	PWM_Duty = 0xff;

   	   	PWM_Flag_key = 1;
   	   	PWM_Duty_W = PWM_Max_Value; // 
   	//     	PWM_Duty_Y = PWM_Max_Value;
   	//     	PWM_Duty_WY = PWM_Max_Value;

   	   	Power_ONOFF_Flag = 0;
   	   	T_key_Value = 1; // Power_ONOFF_Flag

   	   	Pre_T_Key0_Release = 1;
   	   	u16_get_val_Min = 0xffff;

   	//     	CMP_Init();

   	   	while(1) 
   	   	{    
   	   	   	if(T0_5ms_Flag)
            {
   	   	   	   	T0_5ms_Flag = 0;

   	   	   	   	TK0_Scan();

   	   	   	 //   Uart_Send_Data();

   	   	   	   	T_Key_value_Read();

            }

   	   	   	if(T0_25ms_Flag) 
            {
   	   	   	   	T0_25ms_Flag = 0;
   	   	   	   	
   	   	   	   	LED_PWM_Control(); 
   	   	   	   	
   	   	   	   	TK_3S_Reset();
   	   	   	   	
   	   	   //      	Sleep_mode();
            }      	   	   	   	

   	   	   	WDT_Clear();
   	   	  //  TOUCH_TK0_OUT();

   	   	}
}


/************************************************
������:�жϳ���
˵��:
************************************************/
void int_isr(void) __interrupt
{
   	__asm
   	MOVRA  	SAVE_ACC
   	SWAPAR 	STATUS
   	MOVRA  	SAVE_STATUS
   	__endasm;


//========= CMP�ж� ==============  
    if ((CMPIE) && (CMPIF))
        {
           // P11D = !P11D;
            CMPIF = 0;

   	   	   	  //    CMPCR2 = 0x02;           //�ж�,�����ش���    ��ѹ�ߵ���
   	   	   	//     	CMPCR2 = 0x06;           //�ж�,�½��ش���  ��ѹ�͵���

   	   	   	if(BAT_Low_V_Flag == 0)
            {
   	   	   	   	BAT_Low_V_Flag = 1;
   	   	   	    CMPCR2 = 0x06;           //�ж�,�½��ش���  ��ѹ�͵��� 	
            }
   	   	   	else if(BAT_Low_V_Flag)
            {
   	   	   	   	BAT_Low_V_Flag = 0;
   	   	   	    CMPCR2 = 0x02;           //�ж�,�½��ش���  ��ѹ�͵��� 	
            }
   	   	

   	   	  //   	Power_ONOFF_Flag = 0;
   	   	  //   	PWM_Change_KeyFlg = 1;
        }

//========= T0/T1�ж� ==============     	
       	if(T0IF)
       	{      	       	
   	   	   	T0IF   = 0; 
   	   	   	T0CNT = 217; // T0û���Զ���������

   	   	   	T0_5ms_Flag = 1;
   	   	 //    	T0_5ms_Flag_PWM = 1;

   	   	   	T0_5ms_Cnt ++;
   	   	   	if(T0_5ms_Cnt >= 5)
            {
               	T0_5ms_Cnt = 0;
               	T0_25ms_Flag = 1;
   	   	  //   	   	T0_10ms_Flag_PWM = 1;
            }
       	}

       	if(T1IF)
       	{      	       	
   	   	   	T1IF   = 0; 
//;--------------------------
   	   	  //   	UART_SUB();    	   	   	   	//;�����жϴ���
//;--------------------------
       	}

   	__asm
   	SWAPAR 	SAVE_STATUS
   	MOVRA  	STATUS
   	SWAPR  	SAVE_ACC
   	SWAPAR 	SAVE_ACC
   	__endasm;
}

/************************************************
������:������Ӧ�������
˵��:
************************************************/
//void TOUCH_TK0_OUT(void)
//{
////-----------------TK0 -------------------
//     	if(T_Key0_Signal)
//    {
//     	   	LED_R = 1;
//    }
//     	else
//    {
//     	   	LED_R = 0;
//    }
//
//}

//;****************************************************************************
//;****************************************************************************

