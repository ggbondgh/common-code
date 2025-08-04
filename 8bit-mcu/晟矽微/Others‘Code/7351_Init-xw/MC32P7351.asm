;--------------------------------------------------------
; File Created by SN-SDCC : SinoMCU ANSI-C Compiler
; Version 2.0.0 (Dec 11 2019) (MINGW32)
; This file was generated Wed Nov 13 10:01:29 2024
;--------------------------------------------------------
; MC32 port for the RISC core
;--------------------------------------------------------
;	.file	"MC32P7351.c"
	list	p=7351
	radix dec
	include "7351.inc"
;--------------------------------------------------------
; external declarations
;--------------------------------------------------------
	extern	_CLR_RAM
	extern	_IO_Init
	extern	_TIMER0_INT_Init
	extern	_TIMER1_INT_Init
	extern	_TIMER2_INT_Init
	extern	_TIMER3_INT_Init
	extern	_TIMER0_PWM_Init
	extern	_TIMER1_PWM_Init
	extern	_TIMER2_PWM_Init
	extern	_ADC_Init
	extern	_Scan_ADC
	extern	_Set_ADC_Channel
	extern	_ADC_Get_Value_Average
	extern	_delay
	extern	_INDF0bits
	extern	_INDF1bits
	extern	_INDF2bits
	extern	_HIBYTEbits
	extern	_FSR0bits
	extern	_FSR1bits
	extern	_PCLbits
	extern	_PFLAGbits
	extern	_MCRbits
	extern	_INDF3bits
	extern	_INTEbits
	extern	_INTFbits
	extern	_DRVCRbits
	extern	_PFRCCRbits
	extern	_P1KBCRbits
	extern	_PFRCCALbits
	extern	_IOP0bits
	extern	_OEP0bits
	extern	_PUP0bits
	extern	_PDP0bits
	extern	_IOP1bits
	extern	_OEP1bits
	extern	_PUP1bits
	extern	_PDP1bits
	extern	_T0CRbits
	extern	_T0CNTbits
	extern	_T0LOADbits
	extern	_T0DATAbits
	extern	_T1CRbits
	extern	_T1CNTbits
	extern	_T1LOADbits
	extern	_T1DATAbits
	extern	_T2CRbits
	extern	_T2CNTbits
	extern	_T2LOADbits
	extern	_T2DATAbits
	extern	_T3CRbits
	extern	_T3CNTbits
	extern	_T3LOADbits
	extern	_PWM0DRbits
	extern	_PWM1DRbits
	extern	_PWM2DRbits
	extern	_PWMCR0bits
	extern	_PWMCR1bits
	extern	_OSCMRbits
	extern	_LVDCRbits
	extern	_ADCR0bits
	extern	_ADCR1bits
	extern	_ADCR2bits
	extern	_OSADJCRbits
	extern	_ADRHbits
	extern	_ADRLbits
	extern	_ADIOS0bits
	extern	_ADIOS1bits
	extern	_PMODbits
	extern	_PWMCR3bits
	extern	_PWMCR2bits
	extern	_PFRCAUXbits
	extern	_HIRCCALbits
	extern	_flag2
	extern	_adc_data
	extern	_INDF0
	extern	_INDF1
	extern	_INDF2
	extern	_HIBYTE
	extern	_FSR0
	extern	_FSR1
	extern	_PCL
	extern	_PFLAG
	extern	_MCR
	extern	_INDF3
	extern	_INTE
	extern	_INTF
	extern	_DRVCR
	extern	_PFRCCR
	extern	_P1KBCR
	extern	_PFRCCAL
	extern	_IOP0
	extern	_OEP0
	extern	_PUP0
	extern	_PDP0
	extern	_IOP1
	extern	_OEP1
	extern	_PUP1
	extern	_PDP1
	extern	_T0CR
	extern	_T0CNT
	extern	_T0LOAD
	extern	_T0DATA
	extern	_T1CR
	extern	_T1CNT
	extern	_T1LOAD
	extern	_T1DATA
	extern	_T2CR
	extern	_T2CNT
	extern	_T2LOAD
	extern	_T2DATA
	extern	_T3CR
	extern	_T3CNT
	extern	_T3LOAD
	extern	_PWM0DR
	extern	_PWM1DR
	extern	_PWM2DR
	extern	_PWMCR0
	extern	_PWMCR1
	extern	_OSCMR
	extern	_LVDCR
	extern	_ADCR0
	extern	_ADCR1
	extern	_ADCR2
	extern	_OSADJCR
	extern	_ADRH
	extern	_ADRL
	extern	_ADIOS0
	extern	_ADIOS1
	extern	_PMOD
	extern	_PWMCR3
	extern	_PWMCR2
	extern	_PFRCAUX
	extern	_HIRCCAL
;--------------------------------------------------------
; global declarations
;--------------------------------------------------------
	global	_Sleep_Func
	global	_Scan_Key
	global	_Sys_Init
	global	_main
	global	_int_isr
	global	_abuf
	global	_statusbuf
	global	_sleep_time
	global	_key_per
	global	_key_cur
	global	_key_down
	global	_key_keep
	global	_int_time0
	global	_Flag1
	global	_Flag2

	global STK06
	global STK05
	global STK04
	global STK03
	global STK02
	global STK01
	global STK00

sharebank udata_ovr 0x0000
STK06	res 1
STK05	res 1
STK04	res 1
STK03	res 1
STK02	res 1
STK01	res 1
STK00	res 1

;--------------------------------------------------------
; global definitions
;--------------------------------------------------------
UD_MC32P7351_0	udata
_abuf	res	1

UD_MC32P7351_1	udata
_statusbuf	res	1

UD_MC32P7351_2	udata
_sleep_time	res	1

UD_MC32P7351_3	udata
_key_per	res	1

UD_MC32P7351_4	udata
_key_cur	res	1

UD_MC32P7351_5	udata
_key_down	res	1

UD_MC32P7351_6	udata
_key_keep	res	1

UD_MC32P7351_7	udata
_int_time0	res	1

UD_MC32P7351_8	udata
_Flag1	res	1

UD_MC32P7351_9	udata
_Flag2	res	1

;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
;--------------------------------------------------------
; compiler-defined variables
;--------------------------------------------------------
UDL_MC32P7351_0	udata
r0x1008	res	1
r0x1009	res	1
r0x100A	res	1
;--------------------------------------------------------
; initialized data
;--------------------------------------------------------

;@Allocation info for local variables in function 'Sys_Init'
;@Sys_Init CLR_RAM                   Allocated to registers ;size:2
;@Sys_Init IO_Init                   Allocated to registers ;size:2
;@Sys_Init TIMER0_INT_Init           Allocated to registers ;size:2
;@Sys_Init TIMER1_INT_Init           Allocated to registers ;size:2
;@Sys_Init TIMER2_INT_Init           Allocated to registers ;size:2
;@Sys_Init TIMER3_INT_Init           Allocated to registers ;size:2
;@Sys_Init TIMER0_PWM_Init           Allocated to registers ;size:2
;@Sys_Init TIMER1_PWM_Init           Allocated to registers ;size:2
;@Sys_Init TIMER2_PWM_Init           Allocated to registers ;size:2
;@Sys_Init ADC_Init                  Allocated to registers ;size:2
;@Sys_Init Scan_ADC                  Allocated to registers ;size:2
;@Sys_Init Set_ADC_Channel           Allocated to registers ;size:2
;@Sys_Init ADC_Get_Value_Average     Allocated to registers ;size:2
;@Sys_Init Scan_Key                  Allocated to registers ;size:2
;@Sys_Init Sleep_Func                Allocated to registers ;size:2
;@Sys_Init delay                     Allocated to registers ;size:2
;@Sys_Init INDF0bits                 Allocated to registers ;size:1
;@Sys_Init INDF1bits                 Allocated to registers ;size:1
;@Sys_Init INDF2bits                 Allocated to registers ;size:1
;@Sys_Init HIBYTEbits                Allocated to registers ;size:1
;@Sys_Init FSR0bits                  Allocated to registers ;size:1
;@Sys_Init FSR1bits                  Allocated to registers ;size:1
;@Sys_Init PCLbits                   Allocated to registers ;size:1
;@Sys_Init PFLAGbits                 Allocated to registers ;size:1
;@Sys_Init MCRbits                   Allocated to registers ;size:1
;@Sys_Init INDF3bits                 Allocated to registers ;size:1
;@Sys_Init INTEbits                  Allocated to registers ;size:1
;@Sys_Init INTFbits                  Allocated to registers ;size:1
;@Sys_Init DRVCRbits                 Allocated to registers ;size:1
;@Sys_Init PFRCCRbits                Allocated to registers ;size:1
;@Sys_Init P1KBCRbits                Allocated to registers ;size:1
;@Sys_Init PFRCCALbits               Allocated to registers ;size:1
;@Sys_Init IOP0bits                  Allocated to registers ;size:1
;@Sys_Init OEP0bits                  Allocated to registers ;size:1
;@Sys_Init PUP0bits                  Allocated to registers ;size:1
;@Sys_Init PDP0bits                  Allocated to registers ;size:1
;@Sys_Init IOP1bits                  Allocated to registers ;size:1
;@Sys_Init OEP1bits                  Allocated to registers ;size:1
;@Sys_Init PUP1bits                  Allocated to registers ;size:1
;@Sys_Init PDP1bits                  Allocated to registers ;size:1
;@Sys_Init T0CRbits                  Allocated to registers ;size:1
;@Sys_Init T0CNTbits                 Allocated to registers ;size:1
;@Sys_Init T0LOADbits                Allocated to registers ;size:1
;@Sys_Init T0DATAbits                Allocated to registers ;size:1
;@Sys_Init T1CRbits                  Allocated to registers ;size:1
;@Sys_Init T1CNTbits                 Allocated to registers ;size:1
;@Sys_Init T1LOADbits                Allocated to registers ;size:1
;@Sys_Init T1DATAbits                Allocated to registers ;size:1
;@Sys_Init T2CRbits                  Allocated to registers ;size:1
;@Sys_Init T2CNTbits                 Allocated to registers ;size:1
;@Sys_Init T2LOADbits                Allocated to registers ;size:1
;@Sys_Init T2DATAbits                Allocated to registers ;size:1
;@Sys_Init T3CRbits                  Allocated to registers ;size:1
;@Sys_Init T3CNTbits                 Allocated to registers ;size:1
;@Sys_Init T3LOADbits                Allocated to registers ;size:1
;@Sys_Init PWM0DRbits                Allocated to registers ;size:1
;@Sys_Init PWM1DRbits                Allocated to registers ;size:1
;@Sys_Init PWM2DRbits                Allocated to registers ;size:1
;@Sys_Init PWMCR0bits                Allocated to registers ;size:1
;@Sys_Init PWMCR1bits                Allocated to registers ;size:1
;@Sys_Init OSCMRbits                 Allocated to registers ;size:1
;@Sys_Init LVDCRbits                 Allocated to registers ;size:1
;@Sys_Init ADCR0bits                 Allocated to registers ;size:1
;@Sys_Init ADCR1bits                 Allocated to registers ;size:1
;@Sys_Init ADCR2bits                 Allocated to registers ;size:1
;@Sys_Init OSADJCRbits               Allocated to registers ;size:1
;@Sys_Init ADRHbits                  Allocated to registers ;size:1
;@Sys_Init ADRLbits                  Allocated to registers ;size:1
;@Sys_Init ADIOS0bits                Allocated to registers ;size:1
;@Sys_Init ADIOS1bits                Allocated to registers ;size:1
;@Sys_Init PMODbits                  Allocated to registers ;size:1
;@Sys_Init PWMCR3bits                Allocated to registers ;size:1
;@Sys_Init PWMCR2bits                Allocated to registers ;size:1
;@Sys_Init PFRCAUXbits               Allocated to registers ;size:1
;@Sys_Init HIRCCALbits               Allocated to registers ;size:1
;@Sys_Init flag2                     Allocated to registers ;size:1
;@Sys_Init adc_data                  Allocated to registers ;size:2
;@Sys_Init abuf                      Allocated to registers ;size:1
;@Sys_Init statusbuf                 Allocated to registers ;size:1
;@Sys_Init sleep_time                Allocated to registers ;size:1
;@Sys_Init key_per                   Allocated to registers ;size:1
;@Sys_Init key_cur                   Allocated to registers ;size:1
;@Sys_Init key_down                  Allocated to registers ;size:1
;@Sys_Init key_keep                  Allocated to registers ;size:1
;@Sys_Init int_time0                 Allocated to registers ;size:1
;@Sys_Init Flag1                     Allocated to registers ;size:1
;@Sys_Init Flag2                     Allocated to registers ;size:1
;@Sys_Init INDF0                     Allocated to registers ;size:1
;@Sys_Init INDF1                     Allocated to registers ;size:1
;@Sys_Init INDF2                     Allocated to registers ;size:1
;@Sys_Init HIBYTE                    Allocated to registers ;size:1
;@Sys_Init FSR0                      Allocated to registers ;size:1
;@Sys_Init FSR1                      Allocated to registers ;size:1
;@Sys_Init PCL                       Allocated to registers ;size:1
;@Sys_Init PFLAG                     Allocated to registers ;size:1
;@Sys_Init MCR                       Allocated to registers ;size:1
;@Sys_Init INDF3                     Allocated to registers ;size:1
;@Sys_Init INTE                      Allocated to registers ;size:1
;@Sys_Init INTF                      Allocated to registers ;size:1
;@Sys_Init DRVCR                     Allocated to registers ;size:1
;@Sys_Init PFRCCR                    Allocated to registers ;size:1
;@Sys_Init P1KBCR                    Allocated to registers ;size:1
;@Sys_Init PFRCCAL                   Allocated to registers ;size:1
;@Sys_Init IOP0                      Allocated to registers ;size:1
;@Sys_Init OEP0                      Allocated to registers ;size:1
;@Sys_Init PUP0                      Allocated to registers ;size:1
;@Sys_Init PDP0                      Allocated to registers ;size:1
;@Sys_Init IOP1                      Allocated to registers ;size:1
;@Sys_Init OEP1                      Allocated to registers ;size:1
;@Sys_Init PUP1                      Allocated to registers ;size:1
;@Sys_Init PDP1                      Allocated to registers ;size:1
;@Sys_Init T0CR                      Allocated to registers ;size:1
;@Sys_Init T0CNT                     Allocated to registers ;size:1
;@Sys_Init T0LOAD                    Allocated to registers ;size:1
;@Sys_Init T0DATA                    Allocated to registers ;size:1
;@Sys_Init T1CR                      Allocated to registers ;size:1
;@Sys_Init T1CNT                     Allocated to registers ;size:1
;@Sys_Init T1LOAD                    Allocated to registers ;size:1
;@Sys_Init T1DATA                    Allocated to registers ;size:1
;@Sys_Init T2CR                      Allocated to registers ;size:1
;@Sys_Init T2CNT                     Allocated to registers ;size:1
;@Sys_Init T2LOAD                    Allocated to registers ;size:1
;@Sys_Init T2DATA                    Allocated to registers ;size:1
;@Sys_Init T3CR                      Allocated to registers ;size:1
;@Sys_Init T3CNT                     Allocated to registers ;size:1
;@Sys_Init T3LOAD                    Allocated to registers ;size:1
;@Sys_Init PWM0DR                    Allocated to registers ;size:1
;@Sys_Init PWM1DR                    Allocated to registers ;size:1
;@Sys_Init PWM2DR                    Allocated to registers ;size:1
;@Sys_Init PWMCR0                    Allocated to registers ;size:1
;@Sys_Init PWMCR1                    Allocated to registers ;size:1
;@Sys_Init OSCMR                     Allocated to registers ;size:1
;@Sys_Init LVDCR                     Allocated to registers ;size:1
;@Sys_Init ADCR0                     Allocated to registers ;size:1
;@Sys_Init ADCR1                     Allocated to registers ;size:1
;@Sys_Init ADCR2                     Allocated to registers ;size:1
;@Sys_Init OSADJCR                   Allocated to registers ;size:1
;@Sys_Init ADRH                      Allocated to registers ;size:1
;@Sys_Init ADRL                      Allocated to registers ;size:1
;@Sys_Init ADIOS0                    Allocated to registers ;size:1
;@Sys_Init ADIOS1                    Allocated to registers ;size:1
;@Sys_Init PMOD                      Allocated to registers ;size:1
;@Sys_Init PWMCR3                    Allocated to registers ;size:1
;@Sys_Init PWMCR2                    Allocated to registers ;size:1
;@Sys_Init PFRCAUX                   Allocated to registers ;size:1
;@Sys_Init HIRCCAL                   Allocated to registers ;size:1
;@end Allocation info for local variables in function 'Sys_Init';
;@Allocation info for local variables in function 'main'
;@end Allocation info for local variables in function 'main';
;@Allocation info for local variables in function 'Scan_Key'
;@end Allocation info for local variables in function 'Scan_Key';
;@Allocation info for local variables in function 'Sleep_Func'
;@end Allocation info for local variables in function 'Sleep_Func';
;@Allocation info for local variables in function 'int_isr'
;@end Allocation info for local variables in function 'int_isr';

;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
;	udata_ovr
;--------------------------------------------------------
; reset vector 
;--------------------------------------------------------
STARTUP	code 0x0000
	goto	_main
;--------------------------------------------------------
; interrupt and initialization code
;--------------------------------------------------------
c_interrupt	code	0x8
__sdcc_interrupt
;***
;  pBlock Stats: dbName = I
;***
;entry:  _int_isr	;Function start
; 0 exit points
;2 compiler assigned registers:
;   r0x1009
;   r0x100A
;; Starting pCode block
_int_isr	;Function start
; 0 exit points
;	.line	134; "MC32P7351.c"	__endasm;
	movra	_abuf
	swapar	_PFLAG
	movra	_statusbuf
;	.line	136; "MC32P7351.c"	if (T0IF & T0IE)   	//100us
	CLRR	r0x1009
	JBCLR	_INTFbits,0
	INCR	r0x1009
	CLRR	r0x100A
	JBCLR	_INTEbits,0
	INCR	r0x100A
	MOVAR	r0x100A
	ANDRA	r0x1009
	MOVAI	0x00
	ORAR	r0x1009
	JBCLR	PFLAG,2
	GOTO	_00137_DS_
;	.line	139; "MC32P7351.c"	T0IF = 0;
	BCLR	_INTFbits,0
_00137_DS_
;	.line	142; "MC32P7351.c"	if (T1IF & T1IE)   	//2ms
	CLRR	r0x1009
	JBCLR	_INTFbits,1
	INCR	r0x1009
	CLRR	r0x100A
	JBCLR	_INTEbits,1
	INCR	r0x100A
	MOVAR	r0x100A
	ANDRA	r0x1009
	MOVAI	0x00
	ORAR	r0x1009
	JBCLR	PFLAG,2
	GOTO	_00139_DS_
;	.line	144; "MC32P7351.c"	P11D = !P11D;
	CLRR	r0x1009
	JBCLR	_IOP1bits,1
	INCR	r0x1009
	MOVAR	r0x1009
	MOVAI	0x00
	JBCLR	PFLAG,2
	MOVAI	0x01
	MOVRA	r0x1009
	MOVRA	r0x100A
;;99	MOVAR	r0x100A
	RRAR	r0x1009
	JBSET	PFLAG,0
	BCLR	_IOP1bits,1
	JBCLR	PFLAG,0
	BSET	_IOP1bits,1
;	.line	145; "MC32P7351.c"	T1IF = 0;
	BCLR	_INTFbits,1
;	.line	146; "MC32P7351.c"	T1_flag    	=  	1;
	BSET	_Flag1,1
_00139_DS_
;	.line	166; "MC32P7351.c"	__endasm;
	swapar	_statusbuf
	movra	_PFLAG
	swapr	_abuf
	swapar	_abuf
END_OF_INTERRUPT
;	.line	167; "MC32P7351.c"	}
	RETIE	

;--------------------------------------------------------
; code
;--------------------------------------------------------
code_MC32P7351	code
;***
;  pBlock Stats: dbName = M
;***
;entry:  _main	;Function start
; 2 exit points
;has an exit
;functions called:
;   _Sys_Init
;   _Scan_ADC
;   _Scan_Key
;   _Sys_Init
;   _Scan_ADC
;   _Scan_Key
;; Starting pCode block
_main	;Function start
; 2 exit points
;	.line	44; "MC32P7351.c"	Sys_Init();
	CALL	_Sys_Init
_00114_DS_
;	.line	47; "MC32P7351.c"	if(T1_flag)   //2ms
	JBSET	_Flag1,1
	GOTO	_00114_DS_
;	.line	49; "MC32P7351.c"	T1_flag = 0;
	BCLR	_Flag1,1
;	.line	50; "MC32P7351.c"	ClrWdt();
	clrwdt	
;	.line	51; "MC32P7351.c"	Scan_ADC();     //采样+求平均的时间 =1ms
	CALL	_Scan_ADC
;	.line	55; "MC32P7351.c"	if(++int_time0 >= 10)   //2ms*10 =20ms
	INCR	_int_time0
;;unsigned compare: left < lit(0xA=10), size=1
	MOVAI	0x0a
	RSUBAR	_int_time0
	JBSET	PFLAG,0
	GOTO	_00114_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	57; "MC32P7351.c"	int_time0 = 0 ;
	CLRR	_int_time0
;	.line	58; "MC32P7351.c"	Scan_Key();         //按键扫描
	CALL	_Scan_Key
	GOTO	_00114_DS_
;	.line	63; "MC32P7351.c"	}
	RETURN	
; exit point of _main

;***
;  pBlock Stats: dbName = C
;***
;entry:  _Sleep_Func	;Function start
; 2 exit points
;has an exit
;; Starting pCode block
_Sleep_Func	;Function start
; 2 exit points
;	.line	95; "MC32P7351.c"	if(!ON_flag)
	JBCLR	_Flag2,0
	GOTO	_00129_DS_
;	.line	97; "MC32P7351.c"	if(++sleep_time >= 100) //2ms*100 =200ms
	INCR	_sleep_time
;;unsigned compare: left < lit(0x64=100), size=1
	MOVAI	0x64
	RSUBAR	_sleep_time
	JBSET	PFLAG,0
	GOTO	_00131_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	99; "MC32P7351.c"	sleep_time = 0;
	CLRR	_sleep_time
;	.line	100; "MC32P7351.c"	GIE = 0;
	BCLR	_MCRbits,7
;	.line	101; "MC32P7351.c"	KBIF = 0;
	BCLR	_INTFbits,4
;	.line	102; "MC32P7351.c"	KBIE = 1;
	BSET	_INTEbits,4
;	.line	104; "MC32P7351.c"	Nop();
	nop	
;	.line	105; "MC32P7351.c"	Nop();
	nop	
;	.line	106; "MC32P7351.c"	Stop();
	stop	
;	.line	107; "MC32P7351.c"	Nop();
	nop	
;	.line	108; "MC32P7351.c"	Nop();
	nop	
;	.line	109; "MC32P7351.c"	KBIE = 0;
	BCLR	_INTEbits,4
;	.line	110; "MC32P7351.c"	KBIF = 0;
	BCLR	_INTFbits,4
;	.line	111; "MC32P7351.c"	GIE = 1;
	BSET	_MCRbits,7
	GOTO	_00131_DS_
_00129_DS_
;	.line	116; "MC32P7351.c"	sleep_time = 0;
	CLRR	_sleep_time
_00131_DS_
;	.line	118; "MC32P7351.c"	}
	RETURN	
; exit point of _Sleep_Func

;***
;  pBlock Stats: dbName = C
;***
;entry:  _Scan_Key	;Function start
; 2 exit points
;has an exit
;1 compiler assigned register :
;   r0x1008
;; Starting pCode block
_Scan_Key	;Function start
; 2 exit points
;	.line	73; "MC32P7351.c"	key_per = key_cur; 	
	MOVAR	_key_cur
	MOVRA	_key_per
;	.line	75; "MC32P7351.c"	key_cur = (~IOP1)&0x08;    	   	//低有效
	COMAR	_IOP1
	MOVRA	r0x1008
	MOVAI	0x08
	ANDAR	r0x1008
	MOVRA	_key_cur
;	.line	77; "MC32P7351.c"	key_down = (~key_per) & key_cur;
	COMAR	_key_per
	MOVRA	r0x1008
	MOVAR	_key_cur
	ANDAR	r0x1008
	MOVRA	_key_down
;	.line	78; "MC32P7351.c"	key_keep = key_per & key_cur;
	MOVAR	_key_cur
	ANDAR	_key_per
	MOVRA	_key_keep
;	.line	80; "MC32P7351.c"	if(key_down & Key)
	MOVAR	_key_down
	MOVRA	r0x1008
	JBSET	r0x1008,3
	GOTO	_00121_DS_
;	.line	82; "MC32P7351.c"	key_keep = 1;
	MOVAI	0x01
	MOVRA	_key_keep
_00121_DS_
;	.line	85; "MC32P7351.c"	}
	RETURN	
; exit point of _Scan_Key

;***
;  pBlock Stats: dbName = C
;***
;entry:  _Sys_Init	;Function start
; 2 exit points
;has an exit
;functions called:
;   _CLR_RAM
;   _IO_Init
;   _TIMER0_INT_Init
;   _TIMER1_INT_Init
;   _ADC_Init
;   _CLR_RAM
;   _IO_Init
;   _TIMER0_INT_Init
;   _TIMER1_INT_Init
;   _ADC_Init
;; Starting pCode block
_Sys_Init	;Function start
; 2 exit points
;	.line	23; "MC32P7351.c"	GIE = 0;
	BCLR	_MCRbits,7
;	.line	24; "MC32P7351.c"	CLR_RAM();
	CALL	_CLR_RAM
;	.line	25; "MC32P7351.c"	IO_Init();
	CALL	_IO_Init
;	.line	26; "MC32P7351.c"	TIMER0_INT_Init();     	
	CALL	_TIMER0_INT_Init
;	.line	27; "MC32P7351.c"	TIMER1_INT_Init();
	CALL	_TIMER1_INT_Init
;	.line	33; "MC32P7351.c"	ADC_Init();
	CALL	_ADC_Init
;	.line	34; "MC32P7351.c"	GIE = 1;
	BSET	_MCRbits,7
;	.line	35; "MC32P7351.c"	}
	RETURN	
; exit point of _Sys_Init


;	code size estimation:
;	  103+    0 =   103 instructions (  206 byte)

	end
