#include "define.h"
#include "user.h"

volatile bit_flag Flag1;
volatile u8 abuf;
volatile u8 statusbuf;

/****************user variable*******************/





/************************************************/







/************************************************
 * @brief Function for System Init
 *
 * @param[\] void.
 * 
 * @return  void.
*************************************************/
void Sys_Init(void)
{
    GIE = 0;
    CLR_RAM();
    IO_Init();
    //ADC_Power_On_Stability();
    //while (ADC_Zero_ADJ()); // demo��ʾ,У׼ʧ��һֱУ׼���û���������ѡ���Ƿ�У׼
    //ADC_Init();
    //TIMER0_INT_Init();
    GIE = 1;
}


void main() 
{
   	Sys_Init();
    while (1)
    {

   	}
}


/************************************************
 * @brief interrupt
 *
 * @param[\] void.
 * 
 * @return  void.
*************************************************/
void int_isr(void) __interrupt
{
__asm 
    movra _abuf
    swapar _PFLAG
    movra _statusbuf
__endasm;
    //==============T0===============
    if (T0IF & T0IE)
    {
        T0IF = 0;

    }
    //==============T0===============
    if (T1IF & T1IE)
    {
        T1IF = 0;  	   	
   	   	
    }
/*
    //==============T0===============
    if (T2IF & T2IE)
    {
        P12D = !P12D;
        T2IF = 0;
    }
    //==============T0===============
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

///************************************************
// * @brief Function for Sleep
// *
// * @param[\] void.
// * 
// * @return  void.
//*************************************************/
//u8 sleep_time;
//void Sleep_Func(void)
//{
//    if(!ON_flag)
//    {
//        if(++sleep_time >= 100) //����ʱʱ����2ms������2ms*100 =200ms
//        {
//   	   	   	sleep_time = 0;
//            GIE = 0;
//            KBIF = 0;
//            KBIE = 1;
//            //����ǰ�ر����� AD�� ʹ�ܻ������������ж�
//            Nop();
//            Nop();
//            Stop();
//            Nop();
//            Nop();
//            KBIE = 0;
//            KBIF = 0;
//            GIE = 1;
//            //���Ѻ�ʹ������رռ����жϣ�ʵ��Ӧ���û���������  
//        }
//    }
//    else
//        sleep_time = 0;
//}