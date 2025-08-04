//;**********************************************************************************************************
#ifndef MC30P8160_UART_H
#define MC30P8160_UART_H
//;**********************************************************************************************************

#include "MC30P8160_include.h"

//;**********************************************************************************************************
//;ʹ�õ������ӳ������SRAM��ȫ�ֱ�����
extern unsigned char CTKCNT0_SAVEL;
extern unsigned char CTKCNT0_SAVEH;
extern unsigned char CTKCNT0_BASEL;
extern unsigned char CTKCNT0_BASEH;

extern unsigned char CTKCNT1_SAVEL;
extern unsigned char CTKCNT1_SAVEH;
extern unsigned char CTKCNT1_BASEL;
extern unsigned char CTKCNT1_BASEH;

extern unsigned char CTKCNT2_SAVEL;
extern unsigned char CTKCNT2_SAVEH;
extern unsigned char CTKCNT2_BASEL;
extern unsigned char CTKCNT2_BASEH;

extern unsigned char CTKCNT3_SAVEL;
extern unsigned char CTKCNT3_SAVEH;
extern unsigned char CTKCNT3_BASEL;
extern unsigned char CTKCNT3_BASEH;
//;;-----------------------------------------------
#define		TKCNT0_SAVEH		_CTKCNT0_SAVEH				//;��������0�Ƿ�ʹ��;û��ʹ��ʱȡ������
#define		TKCNT0_SAVEL		_CTKCNT0_SAVEL
#define		TKCNT0_BASEH		_CTKCNT0_BASEH
#define		TKCNT0_BASEL		_CTKCNT0_BASEL
//;;-----------------------------------------------
#define		TKCNT1_SAVEH		_CTKCNT1_SAVEH				//;��������1�Ƿ�ʹ��;û��ʹ��ʱȡ������
#define		TKCNT1_SAVEL		_CTKCNT1_SAVEL
#define		TKCNT1_BASEH		_CTKCNT1_BASEH
#define		TKCNT1_BASEL		_CTKCNT1_BASEL
//;;-----------------------------------------------
#define		TKCNT2_SAVEH		_CTKCNT2_SAVEH				//;��������2�Ƿ�ʹ��;û��ʹ��ʱȡ������
#define		TKCNT2_SAVEL		_CTKCNT2_SAVEL
#define		TKCNT2_BASEH		_CTKCNT2_BASEH
#define		TKCNT2_BASEL		_CTKCNT2_BASEL
//;;-----------------------------------------------
#define		TKCNT3_SAVEH		_CTKCNT3_SAVEH				//;��������3�Ƿ�ʹ��;û��ʹ��ʱȡ������
#define		TKCNT3_SAVEL		_CTKCNT3_SAVEL
#define		TKCNT3_BASEH		_CTKCNT3_BASEH
#define		TKCNT3_BASEL		_CTKCNT3_BASEL
//;;-----------------------------------------------
extern unsigned char CPLAY_FLAG;
#define		PLAY_FLAG			_CPLAY_FLAG

#define		UART_ON_FG			PLAY_FLAG,4	   	   	//;����������־λ
#define		UART_END_FG			PLAY_FLAG,5	   	   	//;���ڷ��ͽ�����־λ
//;;-----------------------------------------------
#define		PIN_UART_TX			P1,5				//;����TX��
//;**********************************************************************************************************

//;���ڹ���û��ʹ��ʱȡ������
unsigned char CUART_OUT_DATA;						//;UART���ڷ�������
unsigned char CUART_OUT_LIST;  	   	   	   	   	   	//;UART���ڷ�����������
unsigned char CUART_OUT_LIST2; 	   	   	   	   	   	//;UART���ڷ�����������2
unsigned char CUART_OUT_CHECKSUM;  	   	   	   	   	//;UART�������ݷ����ۼƺ�
unsigned char CUART_OUT_COUNT; 	   	   	   	   	   	//;UART���ڷ������ݼ���
unsigned char CUART_OUT_DATA_TEMP; 	   	   	   	   	//;UART���ڷ��������ݴ�

#define	UART_OUT_DATA			_CUART_OUT_DATA
#define	UART_OUT_LIST			_CUART_OUT_LIST
#define	UART_OUT_LIST2			_CUART_OUT_LIST2
#define	UART_OUT_CHECKSUM 		_CUART_OUT_CHECKSUM 
#define	UART_OUT_COUNT			_CUART_OUT_COUNT
#define	UART_OUT_DATA_TEMP		_CUART_OUT_DATA_TEMP

//;****************************************************************************
#endif
//;****************************************************************************
