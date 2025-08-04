

#include "Define.h"
#include "User.h"

volatile u8 abuf;
volatile u8 statusbuf;

u8 sleep_time;
u8 key_per,key_cur,key_down,key_keep;
u8 int_time0;

volatile bit_flag Flag1,Flag2;

#define PIN1 P15D
#define PIN2 P16D
#define PIN3 P13D
#define PIN4 P00D
#define PIN5 P17D
#define A1 0
#define B1 1
#define C1 2
#define D1 3
#define E1  4
#define F1  5
#define G1 6
#define A2  7
#define B2 8
#define C2 9
#define D2 10
#define E2 11
#define F2 12
#define G2 13
#define T 14
#define RED 15
#define GRE 16
#define BLU 17

u8 state;
u8 LED_buff[18];
u8 LED_DisplayNum;
u8 ADC_Scan_cnt;
u16 ADC_error_val;

const u8 LED_table[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x79};
const u16 tp[]={958, 
996 ,
1035 ,
1074 ,
1114 ,
1155 ,
1197 ,
1239 ,
1281 ,
1325 ,
1368 ,
1412 ,
1457 ,
1501 ,
1546 ,
1592 ,
1637 ,
1683 ,
1729 ,
1775 ,
1820 ,
1866 ,
1912 ,
1957 ,
2003 ,
2048 ,
2093 ,
2137 ,
2182 ,
2226 ,
2269 ,
2312 ,
2355 ,
2397 ,
2438 ,
2479 ,
2519 ,
2559 ,
2598 ,
2637 ,
2675 ,
2712 ,
2748 ,
2784 ,
2819 ,
2853 ,
2887 ,
2920 ,
2952 ,
2984 ,
3014 ,
3044 ,
3074 ,
3102 ,
3130 ,
3158 ,
3184 ,
3210 ,
3235 ,
3260 ,
3284 ,
3307 ,
3330 ,
3352 ,
3373 ,
3394 ,
3414 ,
3434 ,
3453 ,
3472 ,
3490 ,
3507 ,
3524 ,
3541 ,
3557 ,
3572 ,
3587 ,
3602 ,
3616 ,
3630 ,
3643 ,
3656 ,
3669 ,
3681 ,
3693 ,
3704 ,
3715 ,
3726 ,
3736 ,
3747 ,
3756 ,
3766 ,
3775 ,
3784 ,
3793 ,
3801 ,
3809 ,
3817 ,
3825 ,
//3832 ,
};

u16 adc_data_Old;
u8 num;

u16 adc_tmp;
u16 cnt_test;
u8 cnt_iop;
u16 ADC_Val_tmp;

u16 ADC_Val[4];
u16 ADC_filte(u16 data_tmp)
{
    u8 i;
   	u16 temp;
    if(adc_data_Old>data_tmp)
    {
        temp = adc_data_Old - data_tmp;
    }
    else
    {
        temp = data_tmp - adc_data_Old;
    }
    if(temp>10)
    {
        temp = data_tmp;
    }else
    {
        temp = adc_data_Old;
    }
    ADC_Val[num] = temp;
    num++;
    if(num>=4)
        num = 0;
    temp = 0;
    for ( i = 0; i < 4; i++)
    {
        temp += ADC_Val[i];
    }
    temp >>= 2;
    adc_data_Old = data_tmp;
    return temp;
}


u8 tp_looktable(u16 val)
{
    u8 po; 	
    for ( po = 0; po < 99; po++)
    {
        if(val <=tp[po])
            break;
    }
   	//po = 77-po;
   	if(po>1)po-=2;
    return po;
}

void PIN_setinmode()
{
PIN1 = 0;PIN2 = 0;PIN3 = 0;PIN4 = 0;PIN5 = 0;
    OEP1 &= DEF_CLR_BIT6 ; // io????? 1:out  0:in
    OEP1 &= DEF_CLR_BIT7;
    OEP1 &= DEF_CLR_BIT3;
    OEP1 &= DEF_CLR_BIT5;
    OEP0 &= DEF_CLR_BIT0; // io????? 1:out  0:in
}

void LookTableFunc(u8 num,u8 bit)
{
    u8 table_temp ;
    if(bit == 1)
    {
        num = (num/10) % 10;
    }
    else if(bit == 0)
    {
        num = num % 10;
    }

    table_temp = LED_table[num];
    for (u8 i = 0; i < 7; i++)
    {
        if (table_temp&0x01)
        {
            if (bit)
            {
                LED_buff[i] = 1;
            }
            else
            {
                LED_buff[i+7] = 1;
            }
        }
        else
        {
            if (bit)
            {
                LED_buff[i] = 0;
            }
            else
            {
                LED_buff[i+7] = 0;
            }
        }
        table_temp >>= 1;
    }
    
}

#define PIN5_0 {OEP1 |= DEF_SET_BIT7;\
            PIN5 = 0;}
#define PIN4_0 {OEP0 |= DEF_SET_BIT0;\
       	   	PIN4 = 0;}
void LED_DispalayFunction()
{
    PIN_setinmode();
    switch (state)
    {
    case 0:
        OEP1 |= DEF_SET_BIT5;
        PIN1 = 1;
        if(LED_buff[A1])
        {
            OEP1 |= DEF_SET_BIT6;
            PIN2 = 0;
        }
        if(LED_buff[B1])
        {
            OEP1 |= DEF_SET_BIT3;
            PIN3 = 0;
        }
        if(LED_buff[C1])
        {
         //   OEP1 |= DEF_SET_BIT5;
         //    	PIN1 = 1;
   	   	   	//OEP0 |= DEF_SET_BIT0;
       	   	//PIN4 = 0;
         PIN5_0;
        }
        state++;
        break;
    case 1:
        OEP1 |= DEF_SET_BIT6;
        PIN2 = 1;
        if(LED_buff[E1])
        {
            OEP1 |= DEF_SET_BIT5;
            PIN1 = 0;
        }
        if(LED_buff[F1])
        {
            OEP1 |= DEF_SET_BIT3;
            PIN3 = 0;
        }
     /*   if(LED_buff[GRE])
        {
           // OEP0 |= DEF_SET_BIT0;
            //PIN4 = 0;
           PIN5_0;
        }*/
        if(LED_buff[D1])
        {
           // OEP1 |= DEF_SET_BIT7;
           // PIN5 = 0;
            PIN4_0;
        }
        state++;
        break;
    case 2:
        OEP1 |= DEF_SET_BIT3;
        PIN3 = 1;
        if(LED_buff[B2])
        {
            OEP1 |= DEF_SET_BIT5;
            PIN1 = 0;
        }
      /*  if(LED_buff[BLU])
        {
            OEP1 |= DEF_SET_BIT6;
            PIN2 = 0;
        }*/
        if(LED_buff[G1])
        {
            //OEP0 |= DEF_SET_BIT0;
           //PIN4 = 0;
            PIN5_0;
        }
        if(LED_buff[A2])
        {
            //OEP1 |= DEF_SET_BIT7;
           // PIN5 = 0;
            PIN4_0;
        }
        state++;
        break;
    case 3:
        OEP1 |= DEF_SET_BIT7;
        PIN5 = 1;
        if(LED_buff[C2])
        {
            OEP1 |= DEF_SET_BIT6;
            PIN2 = 0;
        }
        if(LED_buff[D2])
        {
            OEP1 |= DEF_SET_BIT3;
            PIN3 = 0;
        }
        if(LED_buff[E2])
        {
            //OEP1 |= DEF_SET_BIT7;
            //PIN5 = 0;
            PIN4_0;
        }
        state++;
        break;
    case 4:
        OEP0 |= DEF_SET_BIT0;
        PIN4 = 1;
        if(LED_buff[F2])
        {
            OEP1 |= DEF_SET_BIT5;
            PIN1 = 0;
        }
        if(LED_buff[G2])
        {
            OEP1 |= DEF_SET_BIT6;
            PIN2 = 0;
        }
      /*  if(LED_buff[RED])
        {
          //  OEP0 |= DEF_SET_BIT0;
         //   PIN4 = 0;
          PIN5_0;
        }*/
        if(LED_buff[T])
        {
            OEP1 |= DEF_SET_BIT3;
            PIN3 = 0;
        }
        //state=0;
   	   	state++;
        break;
    case 5:
        OEP1 |= DEF_SET_BIT6;
        PIN2 = 1;
   	   	if(LED_buff[GRE])
        {
           // OEP0 |= DEF_SET_BIT0;
            //PIN4 = 0;
           PIN5_0;
        }
   	   	state++;
        break;
    case 6:
   	   	OEP1 |= DEF_SET_BIT3;
        PIN3 = 1;
   	   	if(LED_buff[BLU])
        {
            OEP1 |= DEF_SET_BIT6;
            PIN2 = 0;
        }
        state++;
   	  //   	state = 0;
        break;
    case 7:
   	   	OEP0 |= DEF_SET_BIT0;
        PIN4 = 1;
   	   	if(LED_buff[RED])
        {
          //  OEP0 |= DEF_SET_BIT0;
         //   PIN4 = 0;
          PIN5_0;
        }
        state++;
        break;
    case 8:
        state = 0;
        break;
    default:
        break;
    }
}



void Decode()
{
if(ADC_error_val<30 || ADC_error_val>=3830)
   	   	   	{
   	   	   	   	LookTableFunc(1,0);
                LookTableFunc(10,2);
                LED_buff[T] = 0;
                LED_buff[RED] = 0;
                LED_buff[BLU] = 0;
                LED_buff[GRE] = 0;
            }
   	   	   	else
            {
            LED_DisplayNum = tp_looktable(ADC_error_val);
   	   	   	LED_buff[T] = 1;
            /*if(LED_DisplayNum<20)
            {
                LED_buff[RED] = 0;
                LED_buff[BLU] = 0;
                LED_buff[GRE] = 0;
            }else LED_DisplayNum >=20 &&*/
            if( LED_DisplayNum <35)
            {
                LED_buff[RED] = 0;
                LED_buff[BLU] = 1;
                LED_buff[GRE] = 0;
            }
            else if(LED_DisplayNum >= 35 && LED_DisplayNum<41)
            {
                LED_buff[RED] = 0;
                LED_buff[BLU] = 0;
                LED_buff[GRE] = 1;
            }
            else if(LED_DisplayNum>=41)
            {
                LED_buff[RED] = 1;
                LED_buff[BLU] = 0;
                LED_buff[GRE] = 0;
            }
            LookTableFunc(LED_DisplayNum,0);
            LookTableFunc(LED_DisplayNum,1);
            }
}




/************************************************
;  *    @??????            : Sys_Init
;  *    @???              : ???????
;  *    @???????          :
;  *    @???????          :
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
;  *    @??????            : main
;  *    @???              : ??????
;  *    @???????          :
;  *    @???????          :
;  ***********************************************/
u8 i;
void main(void)
{
    Sys_Init();
  ADIOS0 = 0x08;                     //io???????  1:???????  0:???io
//bit7~0  P12 P11 P10 P05 P04 P03 P02 P00

   	ADIOS1 = 0x00;  
  PMOD = 0x07; 
   	LED_buff[A1] = 0;
LED_buff[1] = 1;
LED_buff[2] = 1;
for ( i = 0; i < 18; i++)
{
    LED_buff[i] = 0;
}

//LookTableFunc(10,0);
//LookTableFunc(5,1);
LED_buff[RED] = 0;
LED_buff[BLU] = 0;
LED_buff[GRE] = 0;
//LED_buff[GRE] = LED_buff[GRE]/LED_buff[BLU];

for ( i = 0; i < 4; i++)
{
   	adc_data = ADC_Get_Value_Average();
   	ADC_error_val = ADC_filte(adc_data);
}
//GIE = 1;

T1_flag = 1;
    while (1)
    {
ClrWdt();
   	   	if(T1_flag)   //2ms
        {
            T1_flag = 0;
   	   	   	ClrWdt();
            adc_data = ADC_Get_Value_Average();
   	   	   	adc_tmp += adc_data;
   	   	   	cnt_test++;
   	   	   	if(cnt_test>=16)
            {
            cnt_test= 0;
            adc_tmp>>=4;
   	   	   	ADC_Val_tmp += adc_tmp;
   	   	   	adc_tmp = 0;
   	   	   	cnt_iop++;
   	   	   	if(cnt_iop>=16)
            {
            cnt_iop = 0;
            ADC_Val_tmp>>=4;
   	   	   	ADC_error_val = ADC_filte(ADC_Val_tmp);
   	   	   	ADC_Val_tmp = 0;
   	   	   	Decode();
   	   	   	}

            }
        }
       	   	
    }
}

/************************************************
;  *    @??????            : Scan_Key
;  *    @???              : ???????
;  *    @???????          :
;  *    @???????          :
;  ***********************************************/


/************************************************
;  *    @??????            : Sleep_Func
;  *    @???              : ???
;  *    @???????          :
;  *    @???????          :
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
            //???????????? AD?? ??????????????????
            Nop();
            Nop();
            Stop();
            Nop();
            Nop();
            KBIE = 0;
            KBIF = 0;
            GIE = 1;
            //???????????????????????????????????????  
        }
    }
    else
        sleep_time = 0;

}


