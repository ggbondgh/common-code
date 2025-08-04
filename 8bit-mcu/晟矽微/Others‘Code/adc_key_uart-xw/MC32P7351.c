

#include "Define.h"
#include "User.h"

volatile u8 abuf;
volatile u8 statusbuf;

u8 sleep_time;
u8 key_per,key_cur,key_down,key_keep;
u8 int_time0;

u8 testflag;
u8 charge_F;
u8 ADCScan_F;

volatile bit_flag Flag1,Flag2;

const u16 Bat_voltage[] = {1413,1536,1843};//2.75V   3V   3.6V

u16 test__;
struct ADC_Val
{
    u16 BAT_Voltage;
    u16 I_Voltage;
    u16 I_Target;
    u8 PWMDuty_Target;
    u8 PWMDuty_Now;
    u8 VIN_first;
}ChargeTrue;

#define UART_LEN 8
#define UARTSEND_PIN P17D
struct UART_x
{
    u8 Uart_bit_cnt ;
    u8 Uart_ov ;
    u8 Uart_send_F ;
    u8 Uart_send_byteLen;
    u8 Uart_sendbuff[4];
}UARTUser;

void Uart_send_Function(void)
{
    UARTUser.Uart_bit_cnt++;
    if(UARTUser.Uart_bit_cnt <= UART_LEN)
    {   
        if(UARTUser.Uart_sendbuff[UARTUser.Uart_send_byteLen-1]&0x01)
            UARTSEND_PIN = 1;
        else
            UARTSEND_PIN = 0;
        UARTUser.Uart_sendbuff[UARTUser.Uart_send_byteLen-1] >>= 1;
    }
    else if(UARTUser.Uart_bit_cnt == UART_LEN+1)
    {
        UARTSEND_PIN = 1;
    }
    else if(UARTUser.Uart_bit_cnt == UART_LEN+2)
    {
        UARTUser.Uart_bit_cnt = 0;
        UARTUser.Uart_send_byteLen--;
        if(UARTUser.Uart_send_byteLen == 0)
        {
            UARTUser.Uart_ov = 1;
            T0IE = 0;
            T0IF = 0;
        }
   	   	else UARTSEND_PIN = 0;
    }
}
void Uart_getsend_func(u8* data,u8 len)
{
    u8 i;
    if(UARTUser.Uart_ov)
    {
        if(UARTUser.Uart_send_F)
        {
            for ( i = 0; i < len; i++)
            {
                UARTUser.Uart_sendbuff[i] = data[i];
            }
            UARTUser.Uart_send_byteLen = len;
            //UARTUser.Uart_sendbuff[0] = data;
            UARTUser.Uart_bit_cnt = 0;
            UARTUser.Uart_ov = 0;
            UARTSEND_PIN = 0;
            T0IF = 0;
            T0IE = 1;
            T0CNT = 104 -1;
        }
    }
}


struct opop
{
    u8 key_cnt;
    u8 key_release;
}keytrue,VINtrue;


///struct opop keytrue;

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
    TIMER0_INT_Init();     	
    TIMER1_INT_Init();
    //TIMER2_INT_Init();
    //TIMER3_INT_Init();
    //TIMER0_PWM_Init();
    //TIMER1_PWM_Init();
    TIMER2_PWM_Init();
    ADC_Init();
    GIE = 1;
}

/**
 * LED 引脚定义
 * 
 */
#define PIN1 P00D
#define PIN2 P16D
#define KEYPIN P00D

#define VIN_5V P13D
u8 buff[6];
void ADC_cul(void)//AD_val : 103 为1A电流
{
    if(ADCScan_F)
   	   	{
   	   	    ADCScan_F = 0;
            ChargeTrue.BAT_Voltage = ADC_Get_Value_Average();
            Set_ADC_Channel(3);
            delay(2);
            buff[0] = ChargeTrue.BAT_Voltage;
            buff[1] = ChargeTrue.BAT_Voltage >> 8;
            ChargeTrue.I_Voltage = ADC_Get_Value_Average();
            Set_ADC_Channel(10);
            buff[2] = ChargeTrue.I_Voltage;
            buff[3] = ChargeTrue.I_Voltage >> 8;
   	   	   	buff[4] = 0;
            buff[5] = charge_F;
            Uart_getsend_func(buff,6);
         //   if(charge_F)
            {
                /*
                if (ChargeTrue.BAT_Voltage<Bat_voltage[0])
                {
                    ChargeTrue.I_Target = 10;
                }
                else if (ChargeTrue.BAT_Voltage>=Bat_voltage[0] && ChargeTrue.BAT_Voltage<Bat_voltage[1])
                {
                    ChargeTrue.I_Target = 103;
                }
                else if(ChargeTrue.BAT_Voltage>=Bat_voltage[1] && ChargeTrue.BAT_Voltage<Bat_voltage[2])
                {
                    ChargeTrue.I_Target = 10;
                }*/
                if(ChargeTrue.I_Voltage < ChargeTrue.I_Target)
                {
                    ChargeTrue.PWMDuty_Target = ChargeTrue.I_Target - ChargeTrue.I_Voltage;
                    if(ChargeTrue.PWMDuty_Target >8)//不需要调整wpm
                    {
                        if(ChargeTrue.PWMDuty_Now<155)
                        ChargeTrue.PWMDuty_Now += 1;
                        T2DATA = ChargeTrue.PWMDuty_Now;
                    }
                }
                else
                {
                    ChargeTrue.PWMDuty_Target = ChargeTrue.I_Voltage - ChargeTrue.I_Target;
                    if(ChargeTrue.PWMDuty_Target >8)//不需要调整wpm
                    {
                        if(ChargeTrue.PWMDuty_Now >2)
                        ChargeTrue.PWMDuty_Now -= 1;
                        T2DATA = ChargeTrue.PWMDuty_Now;
                    }
                }
            }
            
   	   	}
}

void VIN_Scan(void)
{
    if(VIN_5V)
    {
        if(VINtrue.key_cnt <100)VINtrue.key_cnt++;
        if(VINtrue.key_cnt>=25 && VINtrue.key_release)
        {
            VINtrue.key_release = 0;
   	   	   	charge_F = 1;
        }
    }
    else
    {
        VINtrue.key_cnt = 0;
        VINtrue.key_release = 1;
   	   	charge_F = 0;
    }
}

/**
 * LED扫描
*/
void LED_Scan(void)
{
    OEP1 |= DEF_SET_BIT6; // io口方向 1:out  0:in
    OEP0 |= DEF_SET_BIT0; // io口方向 1:out  0:in
    PUP0 = 0x00;
    if(Flag1.bits.bit0)
    {
        PIN1 = 1;
        PIN2 = 0;
        delay(350);
    }
    else 
    {
        if(testflag)
        {
       	 PIN1 = 0;
       	 PIN2 = 1;
   	   	  //   	P14D = 1;
        }
        else
        {
            PIN1 = 0;
            PIN2 = 0;
   	   	   //  	P14D = 0;
        }
        delay(350);
    }
    
    OEP1 &= DEF_CLR_BIT6; // io口方向 1:out  0:in
    OEP0 &= DEF_CLR_BIT0; // io口方向 1:out  0:in
    PUP0 = 0x01;
    delay(4);
    if(!KEYPIN)
    {
        if(keytrue.key_cnt <100)keytrue.key_cnt++;
        if(keytrue.key_cnt>=25 && keytrue.key_release)
        {
            keytrue.key_release = 0;
            Flag1.bits.bit0 = ~Flag1.bits.bit0;
            //Uart_getsend_func(0x43);
        }
    }
    else
    {
        keytrue.key_cnt = 0;
        keytrue.key_release = 1;
    }
    
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
    UARTUser.Uart_ov = 1;
    UARTUser.Uart_send_F = 1;
    Set_ADC_Channel(3); 
   	ChargeTrue.I_Target = 102;
    while (1)
    {
   	   	ClrWdt();
        LED_Scan();
   	   	VIN_Scan();
   	   	//if(charge_F)
        ADC_cul();
        /*
        if(ADCScan_F)
   	   	{
   	   	    ADCScan_F = 0;
            ChargeTrue.BAT_Voltage = ADC_Get_Value_Average();test__ = ChargeTrue.BAT_Voltage;
            buff[0] = ChargeTrue.BAT_Voltage;
            buff[1] = ChargeTrue.BAT_Voltage >> 8;
            
            Uart_getsend_func(buff,2);
   	   	}*/

        /*
        if(T1_flag)   //2ms
        {
            T1_flag = 0;
   	   	   	ClrWdt();
            Scan_ADC();     //采样+求平均的时间 =1ms
            //P17D = !P17D;
            
            //Sleep_Func();   //睡眠

            if(++int_time0 >= 10)   //2ms*10 =20ms
            {
                int_time0 = 0 ;
                Scan_Key();         //按键扫描
            }
        }*/
   	   	
    }
}

/************************************************
;  *    @函数名            : Scan_Key
;  *    @说明              : 按键扫描
;  *    @输入参数          :
;  *    @返回参数          :
;  ***********************************************/
void Scan_Key(void)
{
    key_per = key_cur; 	
   	//key_cur = IOP1&0x08;     	   	//高有效
   	key_cur = (~IOP1)&0x08;    	   	//低有效
   	   	
   	key_down = (~key_per) & key_cur;
   	key_keep = key_per & key_cur;
   	
   	if(key_down & Key)
   	{
   	   	key_keep = 1;
   	}

}

/************************************************
;  *    @函数名            : Sleep_Func
;  *    @说明              : 睡眠
;  *    @输入参数          :
;  *    @返回参数          :
;  ***********************************************/
void Sleep_Func(void)
{
    if(!ON_flag)
    {
        if(++sleep_time >= 100) //2ms*100 =200ms
        {
   	   	   	sleep_time = 0;
            GIE = 0;
            KBIF = 0;
            KBIE = 1;
            //休眠前关闭外设 AD等 使能唤醒条件键盘中断
            Nop();
            Nop();
            Stop();
            Nop();
            Nop();
            KBIE = 0;
            KBIF = 0;
            GIE = 1;
            //唤醒后使能外设关闭键盘中断，实际应用用户按需配置  
        }
    }
    else
        sleep_time = 0;

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
    //=======T0========================
    if (T0IF & T0IE)   	//104us
    {
        //P10D = !P10D;
        T0IF = 0;
        Uart_send_Function();
    }
    //=======T1========================
    if (T1IF & T1IE)   	//2ms
    {
        //P11D = !P11D;
        T1IF = 0;
   	   	T1_flag    	=  	1;
        int_time0++;
        if(int_time0>125)
        {
            testflag= !testflag;
   	   	   	ADCScan_F = 1;
            //P14D = ~P14D;
            int_time0 = 0;
        }
    }
/*
    //=======T2========================
    if (T2IF & T2IE)
    {
        P12D = !P12D;
        T2IF = 0;
    }
    //=======T3========================
    if (T3IF & T3IE)
    {
        P14D = !P14D;
        T3IF = 0;
    }*/
__asm 
    swapar _statusbuf
    movra _PFLAG
    swapr _abuf
    swapar _abuf
__endasm;

}