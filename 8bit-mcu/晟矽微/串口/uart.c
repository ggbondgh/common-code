/*
 * File name: uart.c
 * 
 * Description: 
 * 
 * Processing flow: 
 * 
 * 1, before mian.c while(1) should : T2IE = 0;  
 * 2, Uart_Send_Proc() should be use in Timer.
 * 
 * Function declaration:
 * 
 * void Uart_Send_One_Byte(uint8_t uart_send_byte);
 * void Uart_Send_One_Word(uint16_t uart_send_word);
 * void Uart_Send_Proc(void);
 *
 * Version: V0.1
 * 
 * Modifications:
 * 
 * Note: 1 tab == 4 spaces!
 * 
 */

#include "define.h"
#include "user.h"

#define	TX_PIN P17D
/****************************** method 1 *********************************/ 
//volatile bit_flag Flag1; //if main.c no define
#define	sending_flag Flag1.bits.bit4  

uint8_t uart_data;
uint8_t uart_bit_cnt;

void Uart_Send_One_Byte(uint8_t uart_send_byte) // 19200  52us
{
   	P17OE = 1;P17D = 1; // depend by User
   	uart_data = uart_send_byte;
   	uart_bit_cnt = 0;
   	T2CNT = 52-1; // depend by User
   	T2IE = 1;  	
}

void Uart_Send_One_Word(uint16_t uart_send_word)
{
   	uint8_t uart_send_c;
   	uart_send_c = uart_send_word & 0x00FF;
   	Uart_Send_One_Byte(uart_send_c);
   	while(sending_flag) // waiting last byte send
   	uart_send_c = (uart_send_word & 0xFF00) >> 8; 
   	Uart_Send_One_Byte(uart_send_c);
}

void Uart_Send_Proc(void)
{
   	uart_bit_cnt ++;
   	switch(uart_bit_cnt) 
   	{  	
        case 1 :    TX_PIN = 0; sending_flag = 1;
           	   	   	break;
        case 2 :    TX_PIN = (uart_data & 0x01);
   	   	   	   	   	break;
        case 3 :    TX_PIN = ((uart_data & 0x02)>>1);
   	   	   	   	   	break;
        case 4 :    TX_PIN = ((uart_data & 0x04)>>2);
   	   	   	   	   	break;
        case 5 :    TX_PIN = ((uart_data & 0x08)>>3);
   	   	   	   	   	break;
        case 6 :   	TX_PIN = ((uart_data & 0x10)>>4);
   	   	   	   	   	break;
        case 7 :   	TX_PIN = ((uart_data & 0x20)>>5);
   	   	   	   	   	break;
        case 8 :   	TX_PIN = ((uart_data & 0x40)>>6);
   	   	   	   	   	break;
        case 9 :   	TX_PIN = ((uart_data & 0x80)>>7);
   	   	   	   	   	break;
        case 10 :   TX_PIN = 1;
   	   	   	   	   	break;
        case 11 :   P17OE = 0; // depend by User
   	   	   	   	   	T2IE = 0; sending_flag = 0;
   	   	   	   	   	break;
   	}
}

/****************************** method 2 *********************************/
/*
u8 buff[4]
Volt = 0x1234;
buff[0] = Volt;
buff[1] = Volt >> 8;
Uart_getsend_func(buff,2); 
*/
#define UART_LEN 8
struct UART_x
{
    u8 Uart_bit_cnt ;
    u8 Uart_ov ; // Uart over flag
    u8 Uart_send_F ; // Uart send flag
    u8 Uart_send_n_byte; // How many bytes to send
    u8 Uart_sendbuff[4];
}UARTUser;

void Uart_send_Function(void)
{
    UARTUser.Uart_bit_cnt++;
    if(UARTUser.Uart_bit_cnt <= UART_LEN)
    {   
        if(UARTUser.Uart_sendbuff[UARTUser.Uart_send_n_byte - 1] & 0x01)
            TX_PIN = 1;
        else
            TX_PIN = 0;
        UARTUser.Uart_sendbuff[UARTUser.Uart_send_n_byte-1] >>= 1;
    }
    else if(UARTUser.Uart_bit_cnt == UART_LEN + 1)
    {
        TX_PIN = 1;
    }
    else if(UARTUser.Uart_bit_cnt == UART_LEN + 2)
    {
        UARTUser.Uart_bit_cnt = 0;
        UARTUser.Uart_send_n_byte--;
        if(UARTUser.Uart_send_n_byte == 0)
        {
            UARTUser.Uart_ov = 1;
            T3IE = 0;
            T3IF = 0;
        }
   	   	else TX_PIN = 0;
    }
}
/**
 * @brief Function for getiing data and opening the uart.
 * 
 * @param[in] data : The data need to send
 * @param[in] len : How many bytes to send
 * 
 * @return  void.
 * 
 **/
void Uart_getsend_func(u8* data, u8 len)
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
            UARTUser.Uart_send_n_byte = len;
            //UARTUser.Uart_sendbuff[0] = data;
            UARTUser.Uart_bit_cnt = 0;
            UARTUser.Uart_ov = 0;
            TX_PIN = 0;
            T3IF = 0;
            T3IE = 1;
            T3CNT = 104 - 1; // depend by User
        }
    }
}

