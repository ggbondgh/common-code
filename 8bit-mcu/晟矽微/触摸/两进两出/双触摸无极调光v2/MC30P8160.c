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

//#define  LED_R     P15D



// ����Ƶ  4.8M
#define	   	TK_SENS_LEVEL_H1  0x0E     	   	//;TK0���������ȼ���1
#define	   	TK_SENS_LEVEL_L   0xFF     	   	//;TK0���������ȼ���


#define FilterCnt_Value    	11
#define Const_SEN_T_Key0   	45
#define Const_SEN_T_Key0_Release  60

#define Const_SEN_T_Key1   	45
//#define Const_SEN_T_Key1_Release  60

// ����
// λ����
#define    	T_Key0_Signal      	flag1.bits.bit0    	 // ��־λ
#define    	Pre_T_Key0_Release  flag1.bits.bit1	   	 // ��־λ
#define    	TK0_Release_Flag    flag1.bits.bit2	   	 // ��־λ
#define     TK1_Long_press_Flag   flag1.bits.bit3  	 // ��־λ
#define    	T0_5ms_Flag        	flag1.bits.bit4	   	 // ��־λ
#define    	T0_10ms_Flag        flag1.bits.bit5	   	 // ��־λ
#define    	TK0_Long_press_Flag   flag1.bits.bit6  	   	 // ��־λ
#define    	W_AS_Flag          flag1.bits.bit7 	   	 // ��־λ

#define    	W_Power_Flag       	    flag2.bits.bit0    // ��־λ
#define    	PWM_Change_KeyFlg      	flag2.bits.bit1    // ��־λ
#define    	TK0_Key_Release_Flag    flag2.bits.bit2    // ��־λ
#define     T_Key1_Signal          	flag2.bits.bit3    // ��־λ
#define     Pre_T_Key1_Release      flag2.bits.bit4    // ��־λ
#define    	Y_Power_Flag           	flag2.bits.bit5    // ��־λ
#define    	TK1_Release_Flag        flag2.bits.bit6    // ��־λ
#define    	TK1_Key_Release_Flag    flag2.bits.bit7    // ��־λ

#define    	Y_AS_Flag                flag3.bits.bit0    // ��־λ

//uint8_t T_Key0_Signal;
//uint8_t Pre_T_Key0_Release;
//uint8_t TK0_Release_Flag;


uint16_t u16_get_val;      	   	//��ȡֵ
uint16_t u16_release_val;      	//
uint16_t u16_temp_val;

uint16_t u16_release_val_TK0;
uint16_t u16_release_val_TK1;
//uint16_t u16_TK0_get_val_Temp;
//uint16_t u16_TK1_get_val_Temp;
uint16_t u16_TK1_get_val_Min;
uint16_t u16_TK0_get_val_Min;

uint16_t u16_TK0_environment_val;
uint16_t u16_TK0_environment_val_Sum;
uint16_t u16_TK1_environment_val;
uint16_t u16_TK1_environment_val_Sum;

///////////////////////////////////////

uint8_t TK0_Filter_Cnt;
uint8_t TK0_Filter_Cnt_T;
uint8_t TK1_Filter_Cnt;
uint8_t TK1_Filter_Cnt_T;

uint8_t FilterCnt_TK0;
uint8_t FilterCnt_TK1;

uint8_t SleepCnt;  //˯�߼���

// PWM
//uint8_t PWM_Duty_Temp;
uint8_t PWM_Duty_W;
uint8_t PWM_Duty_Y;

uint8_t T_key_Value; // 0 1 2 3 
uint8_t TK1_Key_Cnt;
uint8_t TK0_Key_Cnt;


uint8_t T0_5ms_Cnt;
uint16_t u8_TK_Reset_Cnt;
uint16_t u16_TK0_get_val_Temp;
uint16_t u16_TK1_get_val_Temp;
// ����
#define  Uart_TX     P14D

#define Uart // �رմ���
unsigned char uart_send_c = 0;

/************************************************
������:   	Init_Sys
˵��:
************************************************/


void Delay_us_2(uint8_t i)
{
   	for(; i>0; i--)
    {
   	   	WDT_Clear();
   	    Nop();
        Nop();
   	   	Nop();
        Nop();
    }
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
}
#endif 

void  Init_Sys(void)
{  	   	   	
   	__asm
SET_OPTION:

//;��ʱ���趨 
//; T0     	   	   	   	011 256��Ƶ(ϵͳʱ����256��Ƶ)
    MOVAI   00000111B  	   	//;��ʱ��0����,BIT0-2:��ʱ����Ƶ,BIT3��ʱ������:1-WDT,0-TC0
    MOVRA   T0CR   	   	   	//;BIT4:0-�����ؼ���1-�½��ؼ���,BIT5:ʱ��Դ0-FCPU,1-�ⲿ;BIT6:1-�����ش���0-�½��ش���
    MOVAI   217    	   	   	  //;131
    CLRR   	T0CNT  	   	   	//;�嶨ʱ��0����ֵ;T0û���Զ������������Լ���ֵ��256Ϊ��׼���������ж���ı�T0CNTֵ

//; T1 
   //  	MOVAI   00000000B  	   	//;��ʱ��1����,BIT7=T1EN, BIT6=PWM1AOE,1����PWM, BIT5=PWM1AEN,1ʹ��PWM1A
   //  	MOVRA   T1CR   	   	   	//;BIT4.3:T1ʱ��Դѡ��,BIT2-0:T1��Ƶ
   //  	CLRR   	T1CNT  	   	   	//;�嶨ʱ��1����ֵ
   //  	CLRR   	T1LOAD
   //  	MOVAI  	00000000B
   //  	MOVRA  	TMRCR  	   	   	//;BIT6=T0TBS,BIT3=T2IE,BIT2=T2IF,BIT1=T1IE,BIT0=T1IF
   //  	MOVAI  	00000000B
   //  	MOVRA  	PWM1CR0	   	   	//;�ر�PWM
   //  	MOVAI  	00000000B
   //  	MOVRA  	PWM1CR1
   //  	MOVAI  	00000000B
   //  	MOVRA  	PWM1CR2
   //  	CLRR   	T1DATA
   //  	CLRR   	T1DATB
   //  	CLRR   	T1DATC
   //  	CLRR   	T1DATD

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
    T1CNT = 255-1;
    T1LOAD = 255-1;    	   	//31k
}


void IO_Init(void)
{
   	P1 = 0x00; //  	P1nD �C P1n �˿�����λ��n=5-0��

   	//xx11_1011;   	0 ���   1����
   	DDR1 = 0x33;   	   // DR1n �C P1n �˿ڷ������λ��n=5-0��  0�� �˿���Ϊ�����
   	//  P12   �����  P10 P11 P14 P15����

   	// xx11_0011
   	P1ADCR = 0x33;   // 0 ʹ�ܶ˿ڵ����� I/O ���ܣ� 1 �رն˿ڵ����� I/O ���ܣ�
   	
   	// 1111_1101 P11
   	PUCON = 0xFF; //  1���˿��ڲ�����������Ч��  0���˿��ڲ�����������Ч
   	PDCON = 0xFF; //  1���˿��ڲ�����������Ч��  0���˿��ڲ�����������Ч

   	ODCON = 0x00; // 0�� �˿����ʱΪ�������   1 ��©���


}

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

void TK_Init(void)
{
    //
   	TKCR1 &= 0x03; // �رմ���, ���ı�ͨ��ѡ��λ bit 0-1
   	TKCNTH = 0;
   	TKCNTL = 0;

   	T2MOD = 1;   // ���μ�ʱģʽ������ģʽ��
   // T2CR = 0x49; // 01_0_01_000 FOSC 2��Ƶ
   	T2CR = 0x4A;   // 01_0_01_010 FOSC 16M 4��Ƶ 4M

   	T2LOADH = TK_SENS_LEVEL_H1;
   	T2LOADL = TK_SENS_LEVEL_L;


   //  	TKCR1 &= 0xFC; // д0000_0000 bit0-1: 00 TK0 ѡ����Ӧ��������ͨ��

   	TKCR0 = 0xF4;  // д1111_0000 bit0-3: 000 TK0 ѡ�� 4.8MHz

 //    	TKCFL = 0; 	   // TKM ����ʱ���˲�ʱ�䣨����ֵ��Ϊ 10ns��
   	TKCFL = 1; 	 // TKM ����ʱ���˲�ʱ�䣨����ֵ��Ϊ 50ns��

 //    	TKFJE = 1; 	// ���� TKM �Զ���Ƶ����
   	TKFJE = 0; 	// �ر� TKM �Զ���Ƶ����
   	T2EN = 1;  	// ������ʱ�� T2
   	TKCON = 1; 	// ���� TKM ���ݳ�ż���
   	TKEN = 1;  	// ���� TKM      	       	
}

void Get_TK_Value(void)
{
   	while(TKCF == 1)
    {
   	   	WDT_Clear();
    }

    u16_get_val =  (TKCNTH << 8) | TKCNTL;

   	TKCON = 0;  // �ر� TKM ���ݳ�ż�����
   	TKCNTH = 0; // ��TOUCH����,�����ֹ�����
   	TKCNTL = 0;
}

void TK0_Release_(void)
{
   	FilterCnt_TK0 = 0;
   	T_Key0_Signal = 0;
   	Pre_T_Key0_Release = 1;	   	   	   	   	
   	u16_TK0_environment_val = u16_TK0_get_val_Temp;;
   	TK0_Filter_Cnt = 0;
   	u16_TK0_environment_val_Sum = 0;

   	TK0_Release_Flag = 1;
   	u16_TK0_get_val_Min = 0xFFFF;
}

void TK0_Scan(void)
{
   	// P10 ��Ϊ���룬�ر�����IO����
   	DDR1 |= 0x01;     // 1�� �˿���Ϊ�����          0�� �˿���Ϊ�����
   	P1ADCR |= 0x01;   // 0 ʹ�ܶ˿ڵ����� I/O ���ܣ� 1 �رն˿ڵ����� I/O ���ܣ�

   	TKCR1 = 0x00; // д0000_0000 bit0-1: 00 TK0 ѡ����Ӧ��������ͨ��
   	TK_Init();

   	Get_TK_Value();

   	// P10 ��Ϊ�����������IO����
   	DDR1 &= 0xFE;     // 1�� �˿���Ϊ�����         0�� �˿���Ϊ�����
   	P1ADCR &= 0xFE;   // 1 �رն˿ڵ����� I/O ���ܣ� 0 ʹ�ܶ˿ڵ����� I/O ���ܣ� 
   	P10D = 0;

   //  	u16_temp_val = u16_get_val + Const_SEN_T_Key0 + 10;
   //  	if(u16_temp_val < u16_TK0_environment_val)
   // {
   //  	   	SleepCnt = 0xff;
   //  	}
    u16_TK0_get_val_Temp = u16_get_val;
   //  	u16_temp_val = u16_TK0_get_val_Temp << 2;
   //  	u16_temp_val -= u16_TK0_get_val_Temp;
   //  	u16_temp_val += u16_get_val;
   //  	u16_TK0_get_val_Temp = u16_temp_val >> 2;
   // u16_get_val = u16_TK0_get_val_Temp;

   	if(Pre_T_Key0_Release) 
   	{
   	   	u16_temp_val = u16_get_val + Const_SEN_T_Key0;
   	   	
   	   	if(u16_temp_val < u16_TK0_environment_val) 	 //����
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

   	   	   	   	TK0_Filter_Cnt_T ++;
   	   	   	   	
   	   	   	   	if(TK0_Filter_Cnt_T >= 4)
                {
   	   	   	   	   	TK0_Filter_Cnt_T = 0;
   	   	   	   	   	u16_TK0_environment_val_Sum += u16_get_val;

   	   	   	   	   	TK0_Filter_Cnt ++;                 	   	   	   	
       	   	   	   	if(TK0_Filter_Cnt > 7)
       	   	   	   	{
       	   	   	   	   	TK0_Filter_Cnt = 0;
       	   	   	   	   	u16_TK0_environment_val = u16_TK0_environment_val_Sum >> 3;
       	   	   	   	   	u16_TK0_environment_val_Sum = 0;

       	   	   	   	   	if(TK0_Release_Flag)
       	   	   	   	   	{
       	   	   	   	   	   	TK0_Release_Flag = 0;
       	   	   	   	   	   	u16_TK0_environment_val = u16_get_val;
       	   	   	   	   	}
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

   	   	if(u16_get_val < u16_TK0_get_val_Min)
        {
   	   	   	u16_TK0_get_val_Min = u16_get_val;
        }
   	
   	   	u16_temp_val = u16_release_val_TK0 + Const_SEN_T_Key0 + u16_TK0_get_val_Min;
   	   	u16_temp_val = u16_temp_val >> 1;

   	   	if(u16_get_val > u16_release_val_TK0 || u16_get_val > u16_temp_val)	//�ɿ�
   	   	{
   	   	   	FilterCnt_TK0 ++;
   	   	   	if(FilterCnt_TK0 >= 4) //�����ɿ��˲� 20ms
   	   	   	{
   	   	   	   TK0_Release_(); 	
   	   	   	}
   	   	}
   	   	else
   	   	{
   	   	   	FilterCnt_TK0 = 0;
   	   	}  	
    }  	
}
///////////////////////////////////////////////
void TK1_Release_(void)
{
   	FilterCnt_TK1 = 0;

   	T_Key1_Signal = 0;

   	Pre_T_Key1_Release = 1;	   	   	   	   	
   	u16_TK1_environment_val = u16_TK1_get_val_Temp;
   	TK1_Filter_Cnt = 0;
   	u16_TK1_environment_val_Sum = 0;

   	TK1_Release_Flag = 1;

   	u16_TK1_get_val_Min = 0xFFFF;
}

void TK1_Scan(void)
{
   	// P11 ��Ϊ���룬�ر�����IO����
   	DDR1 |= 0x02;     // 1�� �˿���Ϊ�����          0�� �˿���Ϊ�����
   	P1ADCR |= 0x02;   // 0 ʹ�ܶ˿ڵ����� I/O ���ܣ� 1 �رն˿ڵ����� I/O ���ܣ�

   	TKCR1 = 0x01; // д0000_0000 bit0-1: 01 TK1 ѡ����Ӧ��������ͨ��
   	TK_Init();

   	Get_TK_Value();

   	// P11 ��Ϊ�����������IO����
   	DDR1 &= 0xFD;     // 1�� �˿���Ϊ�����         0�� �˿���Ϊ�����
   	P1ADCR &= 0xFD;   // 1 �رն˿ڵ����� I/O ���ܣ� 0 ʹ�ܶ˿ڵ����� I/O ���ܣ� 
   	P10D = 0;

   //  	u16_temp_val = u16_get_val + Const_SEN_T_Key1 + 10;
   //  	if(u16_temp_val < u16_TK1_environment_val)
   // {
   //  	   	SleepCnt = 0xff;
   //  	}
    u16_TK1_get_val_Temp = u16_get_val;
     //	u16_temp_val = u16_TK1_get_val_Temp << 2;
     //	u16_temp_val -= u16_TK1_get_val_Temp;
     //	u16_temp_val += u16_get_val;
     //	u16_TK1_get_val_Temp = u16_temp_val >> 2;
     // u16_get_val = u16_TK1_get_val_Temp;

   	if(Pre_T_Key1_Release) 
   	{
   	   	u16_temp_val = u16_get_val + Const_SEN_T_Key1;
   	   	
   	   	if(u16_temp_val < u16_TK1_environment_val) 	 //����
   	   	{
   	   	   	SleepCnt = 0xFF;
   	   	   	FilterCnt_TK1 ++;
   	   	   	if(FilterCnt_TK1 > FilterCnt_Value)
   	   	   	{
   	   	   	    T_Key1_Signal = 1;
   	   	   	   	Pre_T_Key1_Release = 0;
   	   	   	   	u16_release_val_TK1 = u16_TK1_environment_val - Const_SEN_T_Key1; //
   	   	   	}
   	   	}
   	   	else //���»���ֵ
   	   	{
   	   	   	FilterCnt_TK1 = 0;

   	   	   	if(SleepCnt)
   	   	   	{
   	   	   	   	TK1_Filter_Cnt_T ++;
   	   	   	   	
   	   	   	   	if(TK1_Filter_Cnt_T >= 4)
                {
   	   	   	   	   	TK1_Filter_Cnt_T = 0;
   	   	   	   	   	u16_TK1_environment_val_Sum += u16_get_val;
   	   	   	   	   	TK1_Filter_Cnt++;
                }
   	   	   	   	
   	   	   	   	if(TK1_Filter_Cnt > 7)
   	   	   	   	{
   	   	   	   	   	TK1_Filter_Cnt = 0;
   	   	   	   	   	u16_TK1_environment_val = u16_TK1_environment_val_Sum >> 3;
   	   	   	   	   	u16_TK1_environment_val_Sum = 0;

   	   	   	   	   	if(TK1_Release_Flag)
   	   	   	   	   	{
   	   	   	   	   	   	TK1_Release_Flag = 0;
   	   	   	   	   	   	u16_TK1_environment_val = u16_get_val;
   	   	   	   	   	}
   	   	   	   	}
   	   	   	}
   	   	   	else
   	   	   	{
   	   	   	   	u16_TK1_environment_val = u16_get_val;
   	   	   	   	u16_TK1_environment_val_Sum = 0;
   	   	   	   	TK1_Filter_Cnt = 0;
   	   	   	}
   	   	   	
   	   	   	if(TK1_Release_Flag == 1)
   	   	   	{
   	   	   	   	if(u16_get_val > u16_TK1_environment_val)
   	   	   	   	{
   	   	   	   	   	u16_TK1_environment_val = u16_get_val;
   	   	   	   	}
   	   	   	}
   	   	}
   	}
   	else  
   	{
   	   	if(u16_get_val < u16_TK1_get_val_Min)
        {
   	   	   	u16_TK1_get_val_Min = u16_get_val;
        }
   	
   	   	u16_temp_val = u16_release_val_TK1 + Const_SEN_T_Key1 + u16_TK1_get_val_Min;
   	   	u16_temp_val = u16_temp_val >> 1;

   	   	if(u16_get_val > u16_release_val_TK1 || u16_get_val > u16_temp_val)	//�ɿ�
   	   	{
   	   	   	FilterCnt_TK1 ++;
   	   	   	if(FilterCnt_TK1 >= 4) //�����ɿ��˲� 20ms
   	   	   	{
   	   	   	   	TK1_Release_();    	   	   	   	
   	   	   	}
   	   	}
   	   	else
   	   	{
   	   	   	FilterCnt_TK1 = 0;
   	   	}  	
    }  	
}


void TK1_value_Read(void)
{
   	if(T_Key1_Signal && TK1_Key_Release_Flag == 0) //�а�������
   	{ 
   	   	TK1_Key_Cnt ++;
   	   	   	
        PWM_Change_KeyFlg = 1;

   	   	if(TK1_Key_Cnt == 60) //600ms
   	   	{
   	   	   	TK0_Key_Release_Flag = 1;
   	      //   	TK1_Key_Cnt = 60;  	

   	       	if(TK1_Long_press_Flag == 0)
   	       	{
                TK1_Long_press_Flag = 1;   	//������־λ��1

       	   	   	PWM_Change_KeyFlg = 1;

                Y_AS_Flag = !Y_AS_Flag;    	//����������־λ״̬�任
   	       	 }
   	   	}  	   	
   	   	
   	}
   	else if(T_Key1_Signal == 0)
    {
        TK1_Long_press_Flag = 0;   	//������־λ��0

   	   	if(TK1_Key_Cnt > 1 && TK1_Key_Cnt < 60)
   	   	{
            PWM_Change_KeyFlg = 1;

            if (Y_Power_Flag)
            {
                Y_Power_Flag = 0;
            }
            else
            {
                Y_Power_Flag = 1;
            }
   	   	}
   	   	TK1_Key_Release_Flag = 0;
   	   	TK1_Key_Cnt = 0;
    }
}


void TK0_value_Read(void)
{
   	if(T_Key0_Signal && TK0_Key_Release_Flag == 0) //�а�������
   	{
        TK0_Key_Cnt++;

        PWM_Change_KeyFlg = 1;

         if (TK0_Key_Cnt == 60) //600ms
         {
             TK1_Key_Release_Flag = 1;
             //    	TK1_Key_Cnt = 60;  	

             if (TK0_Long_press_Flag == 0)
             {
                 TK0_Long_press_Flag = 1;  	//������־λ��1

                 PWM_Change_KeyFlg = 1;

                 W_AS_Flag = !W_AS_Flag;   	//����������־λ״̬�任
             }
         }     	   	           	   	 
   	}
   	else if(T_Key0_Signal == 0)
   	{  	   	
        TK0_Long_press_Flag = 0;

        if (TK0_Key_Cnt > 1 && TK0_Key_Cnt < 60)
        {
            PWM_Change_KeyFlg = 1;
            
            if (W_Power_Flag)
            {
                W_Power_Flag = 0;
            }
            else
            {
                W_Power_Flag = 1;
            }
        }

   	   	TK0_Key_Release_Flag = 0;
        TK0_Key_Cnt = 0;
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

   	   	if(W_Power_Flag == 0)
   	   	{
   	   	   	PWM_W_OFF();   	   	   	
   	   	}
        else
        {
            T1DATD = PWM_Duty_W; //PWM_Duty_W
            PWM1DOE = 1; //�򿪶˿����������Ʋ���
            PWM1DEN = 1; //�� PWM1D ���� 	
        }

        if (Y_Power_Flag == 0)
        {
            PWM_Y_OFF();
        }
        else
        {
            T1DATC = PWM_Duty_Y;
            PWM1COE = 1; //�򿪶˿����������Ʋ���
            PWM1CEN = 1; //�� PWM1D ����  
        }
   	}


   	if(TK1_Long_press_Flag) //�����޼����⣨255����
   	{
   	   	if(Y_AS_Flag && Y_Power_Flag)      	//�𽥱䰵
   	   	{
   	   	   	if(PWM_Duty_Y < 255) //������� 100%
   	   	   	{
   	   	   	   	PWM_Duty_Y ++;
   	   	   	}  	   	   	
   	   	}
   	   	else if(Y_Power_Flag)  	//�𽥱���
   	   	{  	  
   	   	   	if(PWM_Duty_Y > 12 ) //��С����PWMֵ��255 * 5%��
   	   	   	{
   	   	   	   	PWM_Duty_Y --; 
   	   	   	}
   	   	}
   	}

    if (TK0_Long_press_Flag) //�����޼����⣨255����
    {
        if (W_AS_Flag && W_Power_Flag)     	//�𽥱䰵
        {
            if (PWM_Duty_W < 255) //������� 100%
            {
                PWM_Duty_W++;
            }
        }
        else if(W_Power_Flag)  	//�𽥱���
        {
            if (PWM_Duty_W > 12) //��С����PWMֵ��255 * 8%��
            {
                PWM_Duty_W--;
            }
        }
    }
}


void TK_10S_Reset(void)
{
    if (T_Key0_Signal || T_Key1_Signal)
    {
        u8_TK_Reset_Cnt++;
        if (u8_TK_Reset_Cnt >= 1000) // 10s
        {
            //u8_TK_Reset_Cnt = 0;
            TK0_Release_();
            TK1_Release_();
        }
    }
    else
    {
        u8_TK_Reset_Cnt = 0;
    }

}

// ˯��ģʽ

void Sleep_mode(void)
{
   	if(SleepCnt) 
   	{
   	   	SleepCnt--;
   	}

   	if(W_Power_Flag || Y_Power_Flag)
   	{
   	   	SleepCnt = 0xFF; // 2.55s
   	}


   	if(!SleepCnt)
   	{

   	   	TKEN = 0;       //�ر�TK
   	 //    	CMPCR0 = 0x00;  //�ر�CMP

   	   	SLEEP();   //�������ֱ�д��ʽ(��ʽ��)

   	 //    	Timer16_Init(); //1ms  //�л���ʱ����ʱ��

   	   	TKEN = 1;  	   //��TK
   	 //    	CMPCR0 = 0x81;//����CMP ����VIR ��:VDD��ѹ���� ����CMP�˿���� ����޻���

   	   	T0_5ms_Flag = 1;
   	   	T0_10ms_Flag = 1;

   	}
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

   	   	Delay_us_2(0x5020); // 4M Լ100ms

   	   	TOUCH_Init(); // ���ô����Ĵ��� 

   	   	T1_PWM_Init();
   	   	SleepCnt = 0xff;

   	   	PWM_Duty_W = 0xff; // 
   	   	PWM_Duty_Y = 0xff; // 

        W_AS_Flag = 1;
        Y_AS_Flag = 1;
   	   	Pre_T_Key0_Release = 1;
   	   	u16_TK0_get_val_Min = 0xFFFF;
   	   	u16_TK1_get_val_Min = 0xFFFF;

   	   	while(1) 
   	   	{    
   	   	   	if(T0_5ms_Flag)
            {
   	   	   	   	T0_5ms_Flag = 0;

   	   	   	   	TK0_Scan();                                
   	   	   	   	TK1_Scan();    	   	   	   	
                
                
   	   	   	 //   Uart_Send_Data();
            }

   	   	   	if(T0_10ms_Flag) 
            {
   	   	   	   	T0_10ms_Flag = 0;

                TK0_value_Read();
                TK1_value_Read();
 
   	   	   	   	LED_PWM_Control();     	   	   	 
   	   	   	   	                
                TK_10S_Reset();
   	   	       	Sleep_mode();
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

//========= T0/T1�ж� ==============     	
       	if(T0IF)
       	{      	       	
   	   	   	T0IF   = 0; 
   	   	   	T0CNT = 217; // T0û���Զ���������

   	   	   	T0_5ms_Flag = 1;
   	   	 //    	T0_5ms_Flag_PWM = 1;

   	   	   	T0_5ms_Cnt ++;
   	   	   	if(T0_5ms_Cnt >= 2)
            {
               	T0_5ms_Cnt = 0;
               	T0_10ms_Flag = 1;
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



//;****************************************************************************
//;****************************************************************************

