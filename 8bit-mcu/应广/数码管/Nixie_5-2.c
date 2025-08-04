/********************************************************************************
			��������:	5��-2λ�����
---------------------------------------------------------------------------------
ʹ�÷�����
	Ҫ��ʾ�����ֱ�����Num
	����ѭ������ӣ�
		if(Nixie_Scan_Flag)
		{
			Scan_Flag = 0;
			LED_Scan_Display_5COM(Num);
		}		
	���ж�����ӣ�
		Nixie_Scan_Flag = 1;
---------------------------------------------------------------------------------
ע�⣺
	1.������1msɨ�������һ�Σ����Զ�ʱ�ж���1ms
	2.���Ŷ���Ҫ����ʵ����Ҫ�޸ģ�Ҫ��Ӧ5-2�����ͼ�Ľ�λ��
********************************************************************************/

#include	"extern.h"

WORD T16_1ms_Cnt;

//IO pin definitions
LED_IO_1	BIT   PB.0
LED_IO_2	BIT   PB.1
LED_IO_3	BIT   PB.2
LED_IO_4	BIT   PB.3
LED_IO_5	BIT   PB.4


byte	Num = 0; 	//��ʾ������

byte 	Digit_COM_Count;
byte	Data_H;	//��λ����
byte	Data_L;	//��λ����
bit		Nixie_Scan_Flag;


//LED1������ܵ�λ���ڶ�λ����LED2������ܸ�λ����һλ��
//����ÿ��λ��ʾ��������ܵĶ�
byte LED1_Flag = 0x00;
bit  LED1_1_Flag :   LED1_Flag.0;
bit  LED1_2_Flag :   LED1_Flag.1;
bit  LED1_3_Flag :   LED1_Flag.2;
bit  LED1_4_Flag :   LED1_Flag.3;
bit  LED1_5_Flag :   LED1_Flag.4;
bit  LED1_6_Flag :   LED1_Flag.5;
bit  LED1_7_Flag :   LED1_Flag.6;
bit  LED1_8_Flag :   LED1_Flag.7;

byte LED2_Flag = 0x00;
bit  LED2_1_Flag :   LED2_Flag.0; 
bit  LED2_2_Flag :   LED2_Flag.1; 
bit  LED2_3_Flag :   LED2_Flag.2;
bit  LED2_4_Flag :   LED2_Flag.3;
bit  LED2_5_Flag :   LED2_Flag.4;
bit  LED2_6_Flag :   LED2_Flag.5;
bit  LED2_7_Flag :   LED2_Flag.6;
bit  LED2_8_Flag :   LED2_Flag.7;

byte DIGIT_CODE[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; //bitλ�ߵ�������Ϊseg8~1/H~A


void	LED_5IO_in(void)
{
	$ LED_IO_1 in;
	$ LED_IO_2 in;
	$ LED_IO_3 in;
	$ LED_IO_4 in;
	$ LED_IO_5 in;
}

void	Data_Display_Conversion(byte num_in)
{
	byte H_Count = 0;
	byte U8_Data_Temp = num_in;
	
	while(1)
	{
		if(U8_Data_Temp >= 10)
		{
			U8_Data_Temp = U8_Data_Temp - 10;
			H_Count ++;
		}
		else
		{
			Data_H = H_Count;
			Data_L = U8_Data_Temp;
			break;
		}
	}
	//��λ����λ�������ֶ�Ӧ��ѡ
	LED1_Flag = DIGIT_CODE[Data_L];	
	LED2_Flag = DIGIT_CODE[Data_H];
}

void	LED_Scan_Display_5COM(byte num_in)
{
	LED_5IO_in();
	
	Data_Display_Conversion(num_in);

	Digit_COM_Count ++;
	if(Digit_COM_Count > 5)
	{
		Digit_COM_Count = 1;
	}

	switch(Digit_COM_Count) 
	{	
		case 1 : $ LED_IO_1 out,low;  //��һ·

					if(LED2_5_Flag)
					{
						$ LED_IO_2 out,high;
					}
					if(LED1_1_Flag)
					{
						$ LED_IO_3 out,high;
					}
					if(LED1_5_Flag)
					{
						$ LED_IO_4 out,high;
					}
					break; 

		case 2 : $ LED_IO_2 out,low;  //�ڶ�·

					if(LED2_1_Flag)
					{
						$ LED_IO_1 out,high;
					}
					if(LED1_2_Flag)
					{
						$ LED_IO_3 out,high;
					}
					if(LED1_6_Flag)
					{
						$ LED_IO_4 out,high;
					}
					break; 

		case 3 : $ LED_IO_3 out,low;  //����·

					if(LED2_2_Flag)
					{
						$ LED_IO_1 out,high;
					}
					if(LED2_6_Flag)
					{
						$ LED_IO_2 out,high;
					}
					if(LED1_7_Flag)
					{
						$ LED_IO_4 out,high;
					}
					break; 

		case 4 : $ LED_IO_4 out,low;  //����·

					if(LED2_3_Flag)
					{
						$ LED_IO_1 out,high;
					}
					if(LED2_7_Flag)
					{
						$ LED_IO_2 out,high;
					}
					if(LED1_3_Flag)
					{
						$ LED_IO_3 out,high;
					}
					break; 

		case 5 : $ LED_IO_5 out, low;  //����·

					if(LED2_4_Flag)
					{
						$ LED_IO_1 out,high;
					}
//						if(LED2_8_Flag)//DP��
//						{
//							$ LED_IO_2 out, high;
//						}
					if(LED1_4_Flag)
					{
						$ LED_IO_3 out,high;
					}
//						if(LED1_8_Flag)//DP��
//						{
//							$ LED_IO_4 out,high;
//						}
					break;

	}
	
}


