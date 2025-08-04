/********************************************************************************
			��������:	11��-3λ�����
---------------------------------------------------------------------------------
ʹ�÷�����
	Ҫ��ʾ�����ֱ�����Num
	����ѭ������ӣ�
		if(Nixie_Scan_Flag)
		{
			Scan_Flag = 0;
			LED_Scan_Display_11COM(Num);
		}		
	���ж�����ӣ�
		Nixie_Scan_Flag = 1;
---------------------------------------------------------------------------------
ע�⣺
	1.������1msɨ�������һ�Σ����Զ�ʱ�ж���1ms
	2.���Ŷ���Ҫ����ʵ����Ҫ�޸�
	3.����Ϊ������������ֻ�轫LED_Scan_Display_11COM()�����low��high����������
********************************************************************************/
#include	"extern.h"

//���Ŷ���
SEG1	=>	PA.6  
SEG2	=>	PB.3
SEG3	=>	PB.5
SEG4	=>	PB.7
SEG5	=>	PA.7
SEG6	=>	PA.5
SEG7	=>	PB.4
SEG8	=>	PB.6

DIG1	=>	PA.3
DIG2	=>	PA.4
DIG3	=>	PA.0

//��������
byte	Num;

byte	data_hun;//��λ
byte	data_ten;//ʮλ
byte	data_bit;//��λ
byte 	Digit_COM_Count;//ɨ�����
bit		Nixie_Scan_Flag;



void LED_IO_in(void)
{
	$ SEG1 in;
	$ SEG2 in;
	$ SEG3 in;
	$ SEG4 in;
	$ SEG5 in;
	$ SEG6 in;
	$ SEG7 in;
	$ SEG8 in;
	$ DIG1 in;
	$ DIG2 in;
	$ DIG3 in;
}

void Data_Display_Conversion(byte num_in)//��ȡÿλ������
{
		byte H_Count = 0;
		byte M_Count = 0;
		byte U8_Data_Temp = num_in;
		
		while(1)
		{	
			if(U8_Data_Temp >= 100)
			{
				U8_Data_Temp = U8_Data_Temp - 100;
				H_Count ++;
			}			
			if(U8_Data_Temp >= 10)
			{
				U8_Data_Temp = U8_Data_Temp - 10;
				M_Count ++;
			}
			else
			{
				data_hun = H_Count;
				data_ten = M_Count;
				data_bit = U8_Data_Temp;
				break;
			}
		}
}

void LED_Scan_Display_11COM(byte num_in) //1ms�ж�ɨ��
{
	LED_IO_in(); //����
	
	Data_Display_Conversion(num_in);

	Digit_COM_Count ++;
	if(Digit_COM_Count > 3)
	{
		Digit_COM_Count = 1;
	}

	switch(Digit_COM_Count) 
	{	
		case 1 : $ DIG1 out, low;
					if(data_hun == 0)
					{
						$ SEG1 out, high;
						$ SEG2 out, high;
						$ SEG3 out, high;
						$ SEG4 out, high;
						$ SEG5 out, high;
						$ SEG6 out, high;
					}
					else if(data_hun == 1)
					{
						$ SEG2 out, high;
						$ SEG3 out, high;
					}
					else if(data_hun == 2)
					{
						$ SEG1 out, high;
						$ SEG2 out, high;
						$ SEG4 out, high;
						$ SEG5 out, high;
						$ SEG7 out, high;
					}
					else if(data_hun == 3)
					{
						$ SEG1 out, high;
						$ SEG2 out, high;
						$ SEG3 out, high;
						$ SEG4 out, high;
						$ SEG7 out, high;
					}
					else if(data_hun == 4)
					{
						$ SEG2 out, high;
						$ SEG3 out, high;
						$ SEG6 out, high;
						$ SEG7 out, high;
					}
					else if(data_hun == 5)
					{
						$ SEG1 out, high;
						$ SEG3 out, high;
						$ SEG4 out, high;
						$ SEG6 out, high;
						$ SEG7 out, high;
					}
					else if(data_hun == 6)
					{
						$ SEG1 out, high;
						$ SEG3 out, high;
						$ SEG4 out, high;
						$ SEG5 out, high;
						$ SEG6 out, high;
						$ SEG7 out, high;
					}
					else if(data_hun == 7)
					{
						$ SEG1 out, high;
						$ SEG2 out, high;
						$ SEG3 out, high;
					}
					else if(data_hun == 8)
					{
						$ SEG1 out, high;
						$ SEG2 out, high;
						$ SEG3 out, high;
						$ SEG4 out, high;
						$ SEG5 out, high;
						$ SEG6 out, high;
						$ SEG7 out, high;
					}
					else if(data_hun == 9)
					{
						$ SEG1 out, high;
						$ SEG2 out, high;
						$ SEG3 out, high;
						$ SEG4 out, high;
						$ SEG6 out, high;
						$ SEG7 out, high;
					}
					break; 

		case 2 : $ DIG2 out, low;
					if(data_ten == 0)
					{
						$ SEG1 out, high;
						$ SEG2 out, high;
						$ SEG3 out, high;
						$ SEG4 out, high;
						$ SEG5 out, high;
						$ SEG6 out, high;
					}
					else if(data_ten == 1)
					{
						$ SEG2 out, high;
						$ SEG3 out, high;
					}
					else if(data_ten == 2)
					{
						$ SEG1 out, high;
						$ SEG2 out, high;
						$ SEG4 out, high;
						$ SEG5 out, high;
						$ SEG7 out, high;
					}
					else if(data_ten == 3)
					{
						$ SEG1 out, high;
						$ SEG2 out, high;
						$ SEG3 out, high;
						$ SEG4 out, high;
						$ SEG7 out, high;
					}
					else if(data_ten == 4)
					{
						$ SEG2 out, high;
						$ SEG3 out, high;
						$ SEG6 out, high;
						$ SEG7 out, high;
					}
					else if(data_ten == 5)
					{
						$ SEG1 out, high;
						$ SEG3 out, high;
						$ SEG4 out, high;
						$ SEG6 out, high;
						$ SEG7 out, high;
					}
					else if(data_ten == 6)
					{
						$ SEG1 out, high;
						$ SEG3 out, high;
						$ SEG4 out, high;
						$ SEG5 out, high;
						$ SEG6 out, high;
						$ SEG7 out, high;
					}
					else if(data_ten == 7)
					{
						$ SEG1 out, high;
						$ SEG2 out, high;
						$ SEG3 out, high;
					}
					else if(data_ten == 8)
					{
						$ SEG1 out, high;
						$ SEG2 out, high;
						$ SEG3 out, high;
						$ SEG4 out, high;
						$ SEG5 out, high;
						$ SEG6 out, high;
						$ SEG7 out, high;
					}
					else if(data_ten == 9)
					{
						$ SEG1 out, high;
						$ SEG2 out, high;
						$ SEG3 out, high;
						$ SEG4 out, high;
						$ SEG6 out, high;
						$ SEG7 out, high;
					}
					break;
					
		case 3 : $ DIG3 out, low;
					if(data_bit == 0)
					{
						$ SEG1 out, high;
						$ SEG2 out, high;
						$ SEG3 out, high;
						$ SEG4 out, high;
						$ SEG5 out, high;
						$ SEG6 out, high;
					}
					else if(data_bit == 1)
					{
						$ SEG2 out, high;
						$ SEG3 out, high;
					}
					else if(data_bit == 2)
					{
						$ SEG1 out, high;
						$ SEG2 out, high;
						$ SEG4 out, high;
						$ SEG5 out, high;
						$ SEG7 out, high;
					}
					else if(data_bit == 3)
					{
						$ SEG1 out, high;
						$ SEG2 out, high;
						$ SEG3 out, high;
						$ SEG4 out, high;
						$ SEG7 out, high;
					}
					else if(data_bit == 4)
					{
						$ SEG2 out, high;
						$ SEG3 out, high;
						$ SEG6 out, high;
						$ SEG7 out, high;
					}
					else if(data_bit == 5)
					{
						$ SEG1 out, high;
						$ SEG3 out, high;
						$ SEG4 out, high;
						$ SEG6 out, high;
						$ SEG7 out, high;
					}
					else if(data_bit == 6)
					{
						$ SEG1 out, high;
						$ SEG3 out, high;
						$ SEG4 out, high;
						$ SEG5 out, high;
						$ SEG6 out, high;
						$ SEG7 out, high;
					}
					else if(data_bit == 7)
					{
						$ SEG1 out, high;
						$ SEG2 out, high;
						$ SEG3 out, high;
					}
					else if(data_bit == 8)
					{
						$ SEG1 out, high;
						$ SEG2 out, high;
						$ SEG3 out, high;
						$ SEG4 out, high;
						$ SEG5 out, high;
						$ SEG6 out, high;
						$ SEG7 out, high;
					}
					else if(data_bit == 9)
					{
						$ SEG1 out, high;
						$ SEG2 out, high;
						$ SEG3 out, high;
						$ SEG4 out, high;
						$ SEG6 out, high;
						$ SEG7 out, high;
					}
					break; 
	}
}
