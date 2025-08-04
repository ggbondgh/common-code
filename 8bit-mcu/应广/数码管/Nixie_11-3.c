/********************************************************************************
			功能名称:	11脚-3位数码管
---------------------------------------------------------------------------------
使用方法：
	要显示的数字变量是Num
	在主循环中添加：
		if(Nixie_Scan_Flag)
		{
			Scan_Flag = 0;
			LED_Scan_Display_11COM(Num);
		}		
	在中断中添加：
		Nixie_Scan_Flag = 1;
---------------------------------------------------------------------------------
注意：
	1.建议用1ms扫描数码管一次，所以定时中断是1ms
	2.引脚定义要根据实际需要修改
	3.代码为共阴极，共阳只需将LED_Scan_Display_11COM()里面的low和high反过来即可
********************************************************************************/
#include	"extern.h"

//引脚定义
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

//变量定义
byte	Num;

byte	data_hun;//百位
byte	data_ten;//十位
byte	data_bit;//个位
byte 	Digit_COM_Count;//扫描次数
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

void Data_Display_Conversion(byte num_in)//提取每位的数字
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

void LED_Scan_Display_11COM(byte num_in) //1ms中断扫描
{
	LED_IO_in(); //高阻
	
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
