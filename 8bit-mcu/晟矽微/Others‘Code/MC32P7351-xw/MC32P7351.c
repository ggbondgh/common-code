

#include "Define.h"
#include "User.h"

volatile u8 abuf;
volatile u8 statusbuf;

u8 sleep_time;
u8 key_per,key_cur,key_down,key_keep;
u8 int_time0;

volatile bit_flag Flag1,Flag2;

/************************************************
;  *    @������            : Sys_Init
;  *    @˵��              : ϵͳ��ʼ��
;  *    @�������          :
;  *    @���ز���          :
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
    //TIMER2_PWM_Init();
    ADC_Init();
    GIE = 1;
}
/************************************************
;  *    @������            : main
;  *    @˵��              : ������
;  *    @�������          :
;  *    @���ز���          :
;  ***********************************************/
void main(void)
{
    Sys_Init();
    while (1)
    {
   	   	if(T1_flag)   //2ms
        {
            T1_flag = 0;
   	   	   	ClrWdt();
            Scan_ADC();     //����+��ƽ����ʱ�� =1ms
            //P17D = !P17D;
            //Sleep_Func();   //˯��

            if(++int_time0 >= 10)   //2ms*10 =20ms
            {
                int_time0 = 0 ;
                Scan_Key();         //����ɨ��
            }
        }
   	   	
    }
}

/************************************************
;  *    @������            : Scan_Key
;  *    @˵��              : ����ɨ��
;  *    @�������          :
;  *    @���ز���          :
;  ***********************************************/
void Scan_Key(void)
{
    key_per = key_cur; 	
   	//key_cur = IOP1&0x08;     	   	//����Ч
   	key_cur = (~IOP1)&0x08;    	   	//����Ч
   	   	
   	key_down = (~key_per) & key_cur;
   	key_keep = key_per & key_cur;
   	
   	if(key_down & Key)
   	{
   	   	key_keep = 1;
   	}

}

/************************************************
;  *    @������            : Sleep_Func
;  *    @˵��              : ˯��
;  *    @�������          :
;  *    @���ز���          :
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
            //����ǰ�ر����� AD�� ʹ�ܻ������������ж�
            Nop();
            Nop();
            Stop();
            Nop();
            Nop();
            KBIE = 0;
            KBIF = 0;
            GIE = 1;
            //���Ѻ�ʹ������رռ����жϣ�ʵ��Ӧ���û���������  
        }
    }
    else
        sleep_time = 0;

}



/************************************************
;  *    @������            : interrupt
;  *    @˵��              : �жϺ���
;  *    @�������          :
;  *    @���ز���          :
;  ***********************************************/
void int_isr(void) __interrupt
{
__asm 
    movra _abuf
    swapar _PFLAG
    movra _statusbuf
__endasm;
    //=======T0========================
    if (T0IF & T0IE)   	//100us
    {
        //P10D = !P10D;
        T0IF = 0;
    }
    //=======T1========================
    if (T1IF & T1IE)   	//2ms
    {
        P11D = !P11D;
        T1IF = 0;
   	   	T1_flag    	=  	1;
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