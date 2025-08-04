/********************************************************************************
   	   	   	功能名称:  	6脚-3位数码管
---------------------------------------------------------------------------------
使用方法：
   	要显示的数字变量是 Num
   	在主循环中添加：
   	LED_Scan_Display_6COM(Num);
   	
---------------------------------------------------------------------------------
注意：
   	1.建议用1ms扫描数码管一次，所以定时中断是1ms
   	2.引脚定义要根据实际需要修改，要对应6-3数码管图的脚位来
********************************************************************************/
#include "Define.h"
#include "User.h"

volatile bit_flag Flag_1,Flag_2,Flag_3;
//以下每个位表示的是数码管的段
#define   LED1_A_Flag   Flag_1.bits.bit0
#define   LED1_B_Flag   Flag_1.bits.bit1
#define   LED1_C_Flag   Flag_1.bits.bit2
#define   LED1_D_Flag   Flag_1.bits.bit3
#define   LED1_E_Flag   Flag_1.bits.bit4
#define   LED1_F_Flag   Flag_1.bits.bit5
#define   LED1_G_Flag   Flag_1.bits.bit6
#define   LED1_P_Flag   Flag_1.bits.bit7

#define   LED2_A_Flag   Flag_2.bits.bit0
#define   LED2_B_Flag   Flag_2.bits.bit1
#define   LED2_C_Flag   Flag_2.bits.bit2
#define   LED2_D_Flag   Flag_2.bits.bit3
#define   LED2_E_Flag   Flag_2.bits.bit4
#define   LED2_F_Flag   Flag_2.bits.bit5
#define   LED2_G_Flag   Flag_2.bits.bit6
#define   LED2_P_Flag   Flag_2.bits.bit7

#define   LED3_A_Flag   Flag_3.bits.bit0
#define   LED3_B_Flag   Flag_3.bits.bit1
#define   LED3_C_Flag   Flag_3.bits.bit2
#define   LED3_D_Flag   Flag_3.bits.bit3
#define   LED3_E_Flag   Flag_3.bits.bit4
#define   LED3_F_Flag   Flag_3.bits.bit5
#define   LED3_G_Flag   Flag_3.bits.bit6
#define   LED3_P_Flag   Flag_3.bits.bit7


uint8_t Digit_COM_Count;
uint8_t	Data_Hun;  	   	//百位数字
uint8_t	Data_Ten;  	   	//十位数字
uint8_t	Data_Bit;  	   	//个位数字

uint8_t LED1_Flag;
uint8_t LED2_Flag;
uint8_t LED3_Flag;

const uint8_t DIGIT_CODE[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; //bit位高到低排列为seg8~1/H~A


void LED_IO_in(void)
{
   	P04OE = 0;
   	P11OE = 0;
   	P12OE = 0;
   	P13OE = 0;
   	P14OE = 0;
   	P15OE = 0;
}

void Data_Display_Conversion(uint16_t num_in)
{
   	uint16_t U16_Data_Temp = num_in;
   	uint8_t  H_Count = 0;
   	uint8_t  T_Count = 0;

   	while(1)
   	{
   	   	if(U16_Data_Temp >= 100)
   	   	{
   	   	   	U16_Data_Temp = U16_Data_Temp - 100;
   	   	   	H_Count ++;
   	   	}  	   	
   	   	else if(U16_Data_Temp >= 10)
   	   	{
   	   	   	U16_Data_Temp = U16_Data_Temp - 10;
   	   	   	T_Count ++;
   	   	}
   	   	else
   	   	{
   	   	   	Data_Hun = H_Count;
   	   	   	Data_Ten = T_Count;
   	   	   	Data_Bit = U16_Data_Temp;
   	   	   	break;
   	   	}
   	}
   	//低位、高位赋予数字对应段选
   	LED1_Flag = DIGIT_CODE[Data_Hun];
   	LED2_Flag = DIGIT_CODE[Data_Ten];
   	LED3_Flag = DIGIT_CODE[Data_Bit];
   	Set_Bits();
}

void LED_Scan_Display_6COM(uint16_t num_in)
{
   	LED_IO_in();
   	Data_Display_Conversion(num_in);
   	LED2_P_Flag = 1; //第二个小数点一直亮

   	Digit_COM_Count ++;
   	if(Digit_COM_Count > 5)
   	{
   	   	Digit_COM_Count = 1;
   	}
   	
   	switch(Digit_COM_Count) 
   	{  	
   	   	case 1 : P04OE = 1;P04D = 1;
       	   	   	   	if(LED1_A_Flag)
       	   	   	   	{
       	   	   	   	   	P11OE = 1;P11D = 0;
       	   	   	   	}
       	   	   	   	if(LED1_D_Flag)
       	   	   	   	{
       	   	   	   	   	P12OE = 1;P12D = 0;
       	   	   	   	}
       	   	   	   	if(LED1_E_Flag)
       	   	   	   	{
       	   	   	   	   	P13OE = 1;P13D = 0;
       	   	   	   	}
       	   	   	   	if(LED1_F_Flag)
       	   	   	   	{
       	   	   	   	   	P14OE = 1;P14D = 0;
       	   	   	   	}
       	   	   	   	if(LED1_G_Flag)
       	   	   	   	{
       	   	   	   	   	P15OE = 1;P15D = 0;
       	   	   	   	}
       	   	   	   	break; 

   	   	case 2 : P11OE = 1;P11D = 1;
   	   	   	   	   	if(LED1_B_Flag)
   	   	   	   	   	{
   	   	   	   	   	   	P04OE = 1;P04D = 0;
   	   	   	   	   	}
   	   	   	   	   	if(LED1_C_Flag)
   	   	   	   	   	{
   	   	   	   	   	   	P12OE = 1;P12D = 0;
   	   	   	   	   	}
   	   	   	   	   	if(LED1_P_Flag)
   	   	   	   	   	{
   	   	   	   	   	   	P13OE = 1;P13D = 0;
   	   	   	   	   	}
   	   	   	   	   	if(LED2_E_Flag)
   	   	   	   	   	{
   	   	   	   	   	   	P14OE = 1;P14D = 0;
   	   	   	   	   	}
   	   	   	   	   	if(LED2_F_Flag)
   	   	   	   	   	{
   	   	   	   	   	   	P15OE = 1;P15D = 0;
   	   	   	   	   	}
   	   	   	   	   	break; 

   	   	case 3 : P12OE = 1;P12D = 1;
   	   	   	   	   	if(LED2_A_Flag)
   	   	   	   	   	{
   	   	   	   	   	   	P04OE = 1;P04D = 0;
   	   	   	   	   	}
   	   	   	   	   	if(LED2_B_Flag)
   	   	   	   	   	{
   	   	   	   	   	   	P11OE = 1;P11D = 0;
   	   	   	   	   	}
   	   	   	   	   	if(LED2_C_Flag)
   	   	   	   	   	{
   	   	   	   	   	   	P13OE = 1;P13D = 0;
   	   	   	   	   	}
   	   	   	   	   	if(LED2_D_Flag)
   	   	   	   	   	{
   	   	   	   	   	   	P14OE = 1;P14D = 0;
   	   	   	   	   	}
   	   	   	   	   	if(LED2_G_Flag)
   	   	   	   	   	{
   	   	   	   	   	   	P15OE = 1;P15D = 0;
   	   	   	   	   	}
   	   	   	   	   	break;  

   	   	case 4 : P13OE = 1;P13D = 1;
   	   	   	   	   	if(LED2_P_Flag)
   	   	   	   	   	{
   	   	   	   	   	   	P04OE = 1;P04D = 0;
   	   	   	   	   	}
   	   	   	   	   	if(LED3_A_Flag)
   	   	   	   	   	{
   	   	   	   	   	   	P11OE = 1;P11D = 0;
   	   	   	   	   	}
   	   	   	   	   	if(LED3_D_Flag)
   	   	   	   	   	{
   	   	   	   	   	   	P12OE = 1;P12D = 0;
   	   	   	   	   	}
   	   	   	   	   	if(LED3_E_Flag)
   	   	   	   	   	{
   	   	   	   	   	   	P14OE = 1;P14D = 0;
   	   	   	   	   	}
   	   	   	   	   	if(LED3_F_Flag)
   	   	   	   	   	{
   	   	   	   	   	   	P15OE = 1;P15D = 0;
   	   	   	   	   	}
   	   	   	   	   	break; 

   	   	case 5 : P14OE = 1;P14D = 1;
   	   	   	   	   	if(LED3_G_Flag)
   	   	   	   	   	{
   	   	   	   	   	   	P04OE = 1;P04D = 0;
   	   	   	   	   	}
   	   	   	   	   	if(LED3_B_Flag)
   	   	   	   	   	{
   	   	   	   	   	   	P11OE = 1;P11D = 0;
   	   	   	   	   	}
   	   	   	   	   	if(LED3_C_Flag)
   	   	   	   	   	{
   	   	   	   	   	   	P12OE = 1;P12D = 0;
   	   	   	   	   	}
   	   	   	   	   	if(LED3_P_Flag)
   	   	   	   	   	{
   	   	   	   	   	   	P13OE = 1;P13D = 0;
   	   	   	   	   	}
   	   	   	   	   	break; 
   	}  	
}

void Set_Bits(void)
{
   	//LED1
    if(LED1_Flag == 0x3F)
    {
       	LED1_P_Flag = 0;
       	LED1_G_Flag = 0; 
       	LED1_F_Flag = 1; 
       	LED1_E_Flag = 1; 
       	LED1_D_Flag = 1; 
       	LED1_C_Flag = 1; 
       	LED1_B_Flag = 1; 
       	LED1_A_Flag = 1;
    }
    else if(LED1_Flag == 0x06)
    {
       	LED1_P_Flag = 0;
       	LED1_G_Flag = 0; 
       	LED1_F_Flag = 0; 
       	LED1_E_Flag = 0; 
       	LED1_D_Flag = 0; 
       	LED1_C_Flag = 1; 
       	LED1_B_Flag = 1; 
       	LED1_A_Flag = 0;
    }
    else if(LED1_Flag == 0x5B)
    {
       	LED1_P_Flag = 0;
       	LED1_G_Flag = 1; 
       	LED1_F_Flag = 0; 
       	LED1_E_Flag = 1; 
       	LED1_D_Flag = 1; 
       	LED1_C_Flag = 0; 
       	LED1_B_Flag = 1; 
       	LED1_A_Flag = 1;
    }
    else if(LED1_Flag == 0x4F)
    {
       	LED1_P_Flag = 0;
       	LED1_G_Flag = 1; 
       	LED1_F_Flag = 0; 
       	LED1_E_Flag = 0; 
       	LED1_D_Flag = 1; 
       	LED1_C_Flag = 1; 
       	LED1_B_Flag = 1; 
       	LED1_A_Flag = 1;
    }
    else if(LED1_Flag == 0x66)
    {
       	LED1_P_Flag = 0;
       	LED1_G_Flag = 1; 
       	LED1_F_Flag = 1; 
       	LED1_E_Flag = 0; 
       	LED1_D_Flag = 0; 
       	LED1_C_Flag = 1; 
       	LED1_B_Flag = 1; 
       	LED1_A_Flag = 0;
    }
    else if(LED1_Flag == 0x6D)
    {
       	LED1_P_Flag = 0;
       	LED1_G_Flag = 1; 
       	LED1_F_Flag = 1; 
       	LED1_E_Flag = 0; 
       	LED1_D_Flag = 1; 
       	LED1_C_Flag = 1; 
       	LED1_B_Flag = 0; 
       	LED1_A_Flag = 1;
    }
    else if(LED1_Flag == 0x7D)
    {
       	LED1_P_Flag = 0;
       	LED1_G_Flag = 1; 
       	LED1_F_Flag = 1; 
       	LED1_E_Flag = 1; 
       	LED1_D_Flag = 1; 
       	LED1_C_Flag = 1; 
       	LED1_B_Flag = 0; 
       	LED1_A_Flag = 1;
    }
    else if(LED1_Flag == 0x07)
    {
       	LED1_P_Flag = 0;
       	LED1_G_Flag = 0; 
       	LED1_F_Flag = 0; 
       	LED1_E_Flag = 0; 
       	LED1_D_Flag = 0; 
       	LED1_C_Flag = 1; 
       	LED1_B_Flag = 1; 
       	LED1_A_Flag = 1;
    }
    else if(LED1_Flag == 0x7F)
    {
       	LED1_P_Flag = 0;
       	LED1_G_Flag = 1; 
       	LED1_F_Flag = 1; 
       	LED1_E_Flag = 1; 
       	LED1_D_Flag = 1; 
       	LED1_C_Flag = 1; 
       	LED1_B_Flag = 1; 
       	LED1_A_Flag = 1;
    }
    else if(LED1_Flag == 0x6F)
    {
       	LED1_P_Flag = 0;
       	LED1_G_Flag = 1; 
       	LED1_F_Flag = 1; 
       	LED1_E_Flag = 0; 
       	LED1_D_Flag = 1; 
       	LED1_C_Flag = 1; 
       	LED1_B_Flag = 1; 
       	LED1_A_Flag = 1;
    }
   	//LED2
    if(LED2_Flag == 0x3F)
    {
       	LED2_P_Flag = 0;
       	LED2_G_Flag = 0; 
       	LED2_F_Flag = 1; 
       	LED2_E_Flag = 1; 
       	LED2_D_Flag = 1; 
       	LED2_C_Flag = 1; 
       	LED2_B_Flag = 1; 
       	LED2_A_Flag = 1;
    }
    else if(LED2_Flag == 0x06)
    {
       	LED2_P_Flag = 0;
       	LED2_G_Flag = 0; 
       	LED2_F_Flag = 0; 
       	LED2_E_Flag = 0; 
       	LED2_D_Flag = 0; 
       	LED2_C_Flag = 1; 
       	LED2_B_Flag = 1; 
       	LED2_A_Flag = 0;
    }
    else if(LED2_Flag == 0x5B)
    {
       	LED2_P_Flag = 0;
       	LED2_G_Flag = 1; 
       	LED2_F_Flag = 0; 
       	LED2_E_Flag = 1; 
       	LED2_D_Flag = 1; 
       	LED2_C_Flag = 0; 
       	LED2_B_Flag = 1; 
       	LED2_A_Flag = 1;
    }
    else if(LED2_Flag == 0x4F)
    {
       	LED2_P_Flag = 0;
       	LED2_G_Flag = 1; 
       	LED2_F_Flag = 0; 
       	LED2_E_Flag = 0; 
       	LED2_D_Flag = 1; 
       	LED2_C_Flag = 1; 
       	LED2_B_Flag = 1; 
       	LED2_A_Flag = 1;
    }
    else if(LED2_Flag == 0x66)
    {
       	LED2_P_Flag = 0;
       	LED2_G_Flag = 1; 
       	LED2_F_Flag = 1; 
       	LED2_E_Flag = 0; 
       	LED2_D_Flag = 0; 
       	LED2_C_Flag = 1; 
       	LED2_B_Flag = 1; 
       	LED2_A_Flag = 0;
    }
    else if(LED2_Flag == 0x6D)
    {
       	LED2_P_Flag = 0;
       	LED2_G_Flag = 1; 
       	LED2_F_Flag = 1; 
       	LED2_E_Flag = 0; 
       	LED2_D_Flag = 1; 
       	LED2_C_Flag = 1; 
       	LED2_B_Flag = 0; 
       	LED2_A_Flag = 1;
    }
    else if(LED2_Flag == 0x7D)
    {
       	LED2_P_Flag = 0;
       	LED2_G_Flag = 1; 
       	LED2_F_Flag = 1; 
       	LED2_E_Flag = 1; 
       	LED2_D_Flag = 1; 
       	LED2_C_Flag = 1; 
       	LED2_B_Flag = 0; 
       	LED2_A_Flag = 1;
    }
    else if(LED2_Flag == 0x07)
    {
       	LED2_P_Flag = 0;
       	LED2_G_Flag = 0; 
       	LED2_F_Flag = 0; 
       	LED2_E_Flag = 0; 
       	LED2_D_Flag = 0; 
       	LED2_C_Flag = 1; 
       	LED2_B_Flag = 1; 
       	LED2_A_Flag = 1;
    }
    else if(LED2_Flag == 0x7F)
    {
       	LED2_P_Flag = 0;
       	LED2_G_Flag = 1; 
       	LED2_F_Flag = 1; 
       	LED2_E_Flag = 1; 
       	LED2_D_Flag = 1; 
       	LED2_C_Flag = 1; 
       	LED2_B_Flag = 1; 
       	LED2_A_Flag = 1;
    }
    else if(LED2_Flag == 0x6F)
    {
       	LED2_P_Flag = 0;
       	LED2_G_Flag = 1; 
       	LED2_F_Flag = 1; 
       	LED2_E_Flag = 0; 
       	LED2_D_Flag = 1; 
       	LED2_C_Flag = 1; 
       	LED2_B_Flag = 1; 
       	LED2_A_Flag = 1;
    }
   	//LED3
    if(LED3_Flag == 0x3F)
    {
       	LED3_P_Flag = 0;
       	LED3_G_Flag = 0; 
       	LED3_F_Flag = 1; 
       	LED3_E_Flag = 1; 
       	LED3_D_Flag = 1; 
       	LED3_C_Flag = 1; 
       	LED3_B_Flag = 1; 
       	LED3_A_Flag = 1;
    }
    else if(LED3_Flag == 0x06)
    {
       	LED3_P_Flag = 0;
       	LED3_G_Flag = 0; 
       	LED3_F_Flag = 0; 
       	LED3_E_Flag = 0; 
       	LED3_D_Flag = 0; 
       	LED3_C_Flag = 1; 
       	LED3_B_Flag = 1; 
       	LED3_A_Flag = 0;
    }
    else if(LED3_Flag == 0x5B)
    {
       	LED3_P_Flag = 0;
       	LED3_G_Flag = 1; 
       	LED3_F_Flag = 0; 
       	LED3_E_Flag = 1; 
       	LED3_D_Flag = 1; 
       	LED3_C_Flag = 0; 
       	LED3_B_Flag = 1; 
       	LED3_A_Flag = 1;
    }
    else if(LED3_Flag == 0x4F)
    {
       	LED3_P_Flag = 0;
       	LED3_G_Flag = 1; 
       	LED3_F_Flag = 0; 
       	LED3_E_Flag = 0; 
       	LED3_D_Flag = 1; 
       	LED3_C_Flag = 1; 
       	LED3_B_Flag = 1; 
       	LED3_A_Flag = 1;
    }
    else if(LED3_Flag == 0x66)
    {
       	LED3_P_Flag = 0;
       	LED3_G_Flag = 1; 
       	LED3_F_Flag = 1; 
       	LED3_E_Flag = 0; 
       	LED3_D_Flag = 0; 
       	LED3_C_Flag = 1; 
       	LED3_B_Flag = 1; 
       	LED3_A_Flag = 0;
    }
    else if(LED3_Flag == 0x6D)
    {
       	LED3_P_Flag = 0;
       	LED3_G_Flag = 1; 
       	LED3_F_Flag = 1; 
       	LED3_E_Flag = 0; 
       	LED3_D_Flag = 1; 
       	LED3_C_Flag = 1; 
       	LED3_B_Flag = 0; 
       	LED3_A_Flag = 1;
    }
    else if(LED3_Flag == 0x7D)
    {
       	LED3_P_Flag = 0;
       	LED3_G_Flag = 1; 
       	LED3_F_Flag = 1; 
       	LED3_E_Flag = 1; 
       	LED3_D_Flag = 1; 
       	LED3_C_Flag = 1; 
       	LED3_B_Flag = 0; 
       	LED3_A_Flag = 1;
    }
    else if(LED3_Flag == 0x07)
    {
       	LED3_P_Flag = 0;
       	LED3_G_Flag = 0; 
       	LED3_F_Flag = 0; 
       	LED3_E_Flag = 0; 
       	LED3_D_Flag = 0; 
       	LED3_C_Flag = 1; 
       	LED3_B_Flag = 1; 
       	LED3_A_Flag = 1;
    }
    else if(LED3_Flag == 0x7F)
    {
       	LED3_P_Flag = 0;
       	LED3_G_Flag = 1; 
       	LED3_F_Flag = 1; 
       	LED3_E_Flag = 1; 
       	LED3_D_Flag = 1; 
       	LED3_C_Flag = 1; 
       	LED3_B_Flag = 1; 
       	LED3_A_Flag = 1;
    }
    else if(LED3_Flag == 0x6F)
    {
       	LED3_P_Flag = 0;
       	LED3_G_Flag = 1; 
       	LED3_F_Flag = 1; 
       	LED3_E_Flag = 0; 
       	LED3_D_Flag = 1; 
       	LED3_C_Flag = 1; 
       	LED3_B_Flag = 1; 
       	LED3_A_Flag = 1;
    }
}

//// Nixie
//void LED_IO_in(void);
//void Data_Display_Conversion(uint16_t num_in);
//void LED_Scan_Display_6COM(uint16_t num_in);
//void Set_Bits(void);


//测试用
//void LED_All_Flag_0(void)
//{
//         	LED1_A_Flag = 0;
//         	LED1_B_Flag = 0; 
//         	LED1_C_Flag = 0; 
//         	LED1_D_Flag = 0; 
//         	LED1_E_Flag = 0; 
//         	LED1_F_Flag = 0; 
//         	LED1_G_Flag = 0; 
//         	LED1_P_Flag = 0;
//         	LED2_A_Flag = 0;
//         	LED2_B_Flag = 0; 
//         	LED2_C_Flag = 0; 
//         	LED2_D_Flag = 0; 
//         	LED2_E_Flag = 0; 
//         	LED2_F_Flag = 0; 
//         	LED2_G_Flag = 0; 
//         	LED2_P_Flag = 0;
//         	LED3_A_Flag = 0;
//         	LED3_B_Flag = 0; 
//         	LED3_C_Flag = 0; 
//         	LED3_D_Flag = 0; 
//         	LED3_E_Flag = 0; 
//         	LED3_F_Flag = 0; 
//         	LED3_G_Flag = 0; 
//         	LED3_P_Flag = 0;
//}