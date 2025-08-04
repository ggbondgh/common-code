//;****************************************************************************

#ifndef include_H
#define include_H

#include <MC30p8160.h>

//;****************************************************************************
#define	   	INTECON	   	INTE   	   	//8160������оƬ�ļĴ����������
#define	   	INTFLAG	   	INTF
#define	   	KBIM   	   	P1KBCR

#define    	_TKCON     	TKCR0,6
#define    	_TKEN      	TKCR0,7
#define    	_T2EN      	T2CR,7
#define    	_T2IE      	TMRCR,3
#define    	_T2IF      	TMRCR,2

#define    	_C         	STATUS,0
#define    	_DC        	STATUS,1
#define    	_Z         	STATUS,2
#define    	_TO        	STATUS,4

//typedef struct {
//    unsigned char bit0 : 1;
//    unsigned char bit1 : 1;
//    unsigned char bit2 : 1;
//    unsigned char bit3 : 1;
//    unsigned char bit4 : 1;
//    unsigned char bit5 : 1;
//    unsigned char bit6 : 1;
//    unsigned char bit7 : 1;
//} BITS_T;

//----- ������� ---------------------------------------------------
#define WDT_Clear()	   	{__asm CLRWDT __endasm;}
#define NOP()  	   	   	{__asm NOP __endasm;}
#define SLEEP()	   	   	{__asm STOP __endasm;}


//******************************************************************************
#endif
//******************************************************************************
