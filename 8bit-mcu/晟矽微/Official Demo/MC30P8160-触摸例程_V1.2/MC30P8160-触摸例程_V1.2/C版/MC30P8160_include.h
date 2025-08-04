//;****************************************************************************

#ifndef include_H
#define include_H

#include <MC30p8160.h>

//;****************************************************************************
#define	   	INTECON	   	INTE 	   	//8160与其它芯片的寄存器定义差异
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

//----- 特殊语句 ---------------------------------------------------
#define WDT_Clear()		{__asm CLRWDT __endasm;}
#define NOP()			{__asm NOP __endasm;}
#define SLEEP()			{__asm STOP __endasm;}


//******************************************************************************
#endif
//******************************************************************************
