/******************************************************************************
;  *       @型号                 : MC32P7351
;  *       @创建日期             : 2022.12.16
;  *       @公司/作者            : sinomcu.com-FAE
;  *       @晟矽微技术支持       : 2048615934
;  *       @晟矽微官网           : http://www.sinomcu.com/
;  *       @版权                 : 2022 sinomcu.com公司版权所有.
;  *----------------------摘要描述---------------------------------
;  *                  ADC 
;  *                  上电等待AD稳定、零点校准
;  *                  ADC时钟为HIRC32分频1M，12位数据H8L4、内部2V、15ADCLK
;  *                  定时器2MS，P10 采集电压值 
;  *                  采集电压值<  1.5V:P11为低电平;>  1.5V:P11为高电平                                
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
;  *    @函数名          : CLR_RAM
;  *    @说明            : 清RAM
;  *    @输入参数        :
;  *    @返回参数        :
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
;  *    @函数名            : delay
;  *    @说明              : 不精确延时函数
;  *    @输入参数          :
;  *    @返回参数          :
;  ***********************************************/
void delay(uint16_t num)
{
    for (i = 0; i < num; i ++)
    {
        Nop();
    }
}

/************************************************
函数名:   	延时函数
************************************************/

void delay_52us(uint   	us)
{
   	while(us)
   	{
   	   	us--;
   	}
}

/************************************************
;  *    @函数名            : uart
;  *    @说明              : 串口输出
;  *    @输入参数          :
;  *    @返回参数          :
;  ***********************************************/
#define  UART     P05D

uint   	bit_out;   	   	   	   	//串口待发送8位完整码
uint   	data_bit;  	   	   	   	//发送的位码
uint   	send_data; 	   	   	   	//待赋值的8位串口码

void   	UART_send(void)	   	   	   	   	//发送整段有效码
{
   	uint   	send_cnt = 8;  	   	   	   	//定义发送8位
   	bit_out = send_data;   	   	       	//赋值

   	UART = 0;  	   	   	   	   	   	   	//开始发送
   	delay_52us(17);        	   	       	   	//延时52us

   	while(send_cnt)    	   	   	   	   	//从左到右一位一位地发，循环8次
   	{
   	   	send_cnt--;
   	   	data_bit = bit_out & 0x01;
   	   	if(data_bit)
   	   	{
   	   	   	UART = 1;  	   	   	   	   	 //取移位值结果赋给P01,即移位为1时，P01 = 1,否则P01 = 0
   	   	}
   	   	else   	UART = 0;
   	   	bit_out = bit_out >> 1;    	   	 //发完一位，右移一位赋值给下一个待发值
   	   	delay_52us(17);        	   	   	   	 //延时52us
   	}
   	UART = 1;  	   	   	   	   	   	   	 //停止发送
   	delay_52us(17);        	   	   	   	   	 //延时52us
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
;  *    @函数名            : IO_Init
;  *    @说明              : IO初始化
;  *    @输入参数          :
;  *    @返回参数          :
;  ***********************************************/
void IO_Init(void)
{
    IOP0 = 0x00;                       //io口数据位
    OEP0 = 0xFE;                       //io口方向 1:out  0:in  P00输入
    PUP0 = 0x01;                       //io口上拉电阻   1:enable  0:disable  P00上拉有效
    PDP0 = 0x00;                       //io口下拉电阻   1:enable  0:disable
    ADIOS0 = 0x00;                     //io类型选择  1:模拟输入  0:通用io P00数字输入

    IOP1 = 0x00;                       //io口数据位
    OEP1 = 0xFF;                       //io口方向 1:out  0:in
    PUP1 = 0x00;                       //io口上拉电阻   1:enable  0:disable
    PDP1 = 0x00;                       //io口下拉电阻   1:enable  0:disable
    ADIOS1 = 0x00;                     //io类型选择  1:模拟输入  0:通用io

    PMOD = 0x07;                       //bit7-bit5 P17、P13、P01 io类型选择 1:模拟输入  0:通用io 
                                       //bit2-bit0 P13、P01、P00 io端口输出模式  1:推挽输出 0:开漏输出
    DRVCR = 0x80;                      //普通驱动
}


/************************************************
;  *    @函数名            : ADC_Init
;  *    @说明              : ADC初始化
;  *    @输入参数          :
;  *    @返回参数          :
;  ***********************************************/
void ADC_Init(void)
{
    OEP0 &= 0xEF;                                //P04为输入口
    ADIOS0 |= 0x08;                              //使能P04模拟功能
    ADCR0 = 0x3f;                                //使能ADC、12位数据H8L4  P04 AN3
    ADCR1 = 0x83;                                //32分频、VDD参考
    ADCR2 = 0xff;                                //固定为15ADCLK 
}

/************************************************
;  *    @函数名            : ADC_mea
;  *    @说明              : 连续转换
;  *    @输入参数          : 通道
;  *    @返回参数          : 
;  *    函数占用内存较大        
;  ***********************************************/
void   	ADC_mea(void)//测量数据，并用平均值方式滤波
{
    g_temp_value = 0;
    g_tmpbuff = 0;

    uint8_t	Icnt = 16;//测量16笔数据

    while (Icnt--)
    {
        ADEOC = 0; 	   	//开始ADC转换
        while (!ADEOC) 	   	//等待ADC转换结果
            //    NULL;
            //当AD_DONE高电位时读取ADC结果
            //注意：8位分辨率读取ADCR值，9~12为分辨率读取ADCRH和ADCRL
        // 	data = ADCR;   	   	//将ADC的值赋给data
            g_temp_value = ADRH;
        g_temp_value = g_temp_value << 4 | (ADRL & 0x0f);
        g_tmpbuff += g_temp_value;
    }
    g_adc_value0_temp = g_tmpbuff >> 4;//取平均值（2^4 = 16）
}


uint16_t ADC_Get_Value_Average(void)
{
    g_adcsum = 0;
    g_adcmax = 0;
    g_adcmin = 0xffff;
    
    for (g_channel = 0; g_channel < 20; g_channel ++)
    {
        ADEOC = 0;
        while (!ADEOC);                         //等待转换完成
        g_temp_value = ADRH;
        g_temp_value = g_temp_value << 4 | (ADRL & 0x0f);
   	   	if (g_channel < 2)
            continue;                            //丢弃前两次采样的

        if (g_temp_value > g_adcmax)
            g_adcmax = g_temp_value;             //最大
        if (g_temp_value < g_adcmin)
            g_adcmin = g_temp_value;             //最小
        g_adcsum += g_temp_value;  	   	
    }
    g_adcsum -= g_adcmax;                       //去掉一个最大
    g_adcsum -= g_adcmin;                       //去掉一个最小
    g_temp_value = (g_adcsum >> 4);             //除以16，取平均值
    return g_temp_value;
}
/************************************************
;  *    @函数名            : TIMER0_INT_Init
;  *    @说明              : 定时器0初始化
;  *    @输入参数          :
;  *    @返回参数          :
;  ***********************************************/
void TIMER0_INT_Init(void)
{
    T0CR = 0x00;                        //CPU = 32M/16 = 2M,1分频 = 2M
    T0CNT = 50-1;
    T0LOAD = 50-1;                               //25us
    T0EN = 1;                                    //开启定时器
    T0IE = 1;                                    //总中断标志

    GIE = 1;                                     //中断总使能标志
}
/************************************************
;  *    @函数名            : Sys_Init
;  *    @说明              : 系统初始化
;  *    @输入参数          :
;  *    @返回参数          :
;  ***********************************************/
void Sys_Init(void)
{
    GIE = 0;
    CLR_RAM();
    IO_Init();
    //ADC_Power_On_Stability();
    //while (ADC_Zero_ADJ());                      //demo演示,校准失败一直校准，用户按照需求选择是否校准
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
;  *    @函数名            : main
;  *    @说明              : 主程序
;  *    @输入参数          :
;  *    @返回参数          :
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
;  *    @函数名            : interrupt
;  *    @说明              : 中断函数
;  *    @输入参数          :
;  *    @返回参数          :
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
            num++; 	   	   	//不断地增加阶数
            if (num >= 200)    	//当阶数达到设定的值清零
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
            //控制灭灯和亮灯的阶数比例，从而做到LED的亮度的强弱
            if (duty <= num)   	//占空比小于阶数时灭灯
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
            else   	   	   	//占空比大于阶数时亮灯
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
