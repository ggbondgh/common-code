;--------------------------------------------------------
; File Created by SN-SDCC : SinoMCU ANSI-C Compiler
; Version 2.0.0 (Dec 11 2019) (MINGW32)
; This file was generated Thu Oct 31 10:13:09 2024
;--------------------------------------------------------
; MC30 port for the RISC core
;--------------------------------------------------------
;	.file	"MC30P8160.c"
	list	p=1K8160
	radix dec
	include "1K8160.inc"
;--------------------------------------------------------
; external declarations
;--------------------------------------------------------
	extern	_INDFbits
	extern	_T0CNTbits
	extern	_PCLbits
	extern	_STATUSbits
	extern	_FSRbits
	extern	_P1bits
	extern	_MCRbits
	extern	_T0CRbits
	extern	_PCLATHbits
	extern	_PDCONbits
	extern	_ODCONbits
	extern	_PUCONbits
	extern	_INTEbits
	extern	_INTFbits
	extern	_PWM1CR0bits
	extern	_PWM1CR1bits
	extern	_PWM1CR2bits
	extern	_DDR1bits
	extern	_TMRCRbits
	extern	_T1CRbits
	extern	_T1CNTbits
	extern	_T1LOADbits
	extern	_T1DATAbits
	extern	_T1DATBbits
	extern	_T1DATCbits
	extern	_T1DATDbits
	extern	_T2CRbits
	extern	_T2CNTHbits
	extern	_T2CNTLbits
	extern	_T2LOADHbits
	extern	_T2LOADLbits
	extern	_P1KBCRbits
	extern	_P1ADCRbits
	extern	_CMPCR0bits
	extern	_CMPCR1bits
	extern	_CMPCR2bits
	extern	_TKCR0bits
	extern	_TKCR1bits
	extern	_TKCR2bits
	extern	_TKCNTHbits
	extern	_TKCNTLbits
	extern	_INDF
	extern	_T0CNT
	extern	_PCL
	extern	_STATUS
	extern	_FSR
	extern	_P1
	extern	_MCR
	extern	_T0CR
	extern	_PCLATH
	extern	_PDCON
	extern	_ODCON
	extern	_PUCON
	extern	_INTE
	extern	_INTF
	extern	_PWM1CR0
	extern	_PWM1CR1
	extern	_PWM1CR2
	extern	_DDR1
	extern	_TMRCR
	extern	_T1CR
	extern	_T1CNT
	extern	_T1LOAD
	extern	_T1DATA
	extern	_T1DATB
	extern	_T1DATC
	extern	_T1DATD
	extern	_T2CR
	extern	_T2CNTH
	extern	_T2CNTL
	extern	_T2LOADH
	extern	_T2LOADL
	extern	_P1KBCR
	extern	_P1ADCR
	extern	_CMPCR0
	extern	_CMPCR1
	extern	_CMPCR2
	extern	_TKCR0
	extern	_TKCR1
	extern	_TKCR2
	extern	_TKCNTH
	extern	_TKCNTL
;--------------------------------------------------------
; global declarations
;--------------------------------------------------------
	global	_Delay_us_2
	global	_Init_Sys
	global	_Clr_Ram
	global	_T1_PWM_Init
	global	_IO_Init
	global	_TOUCH_Init
	global	_TK_Init
	global	_Get_TK_Value
	global	_TK0_Release_
	global	_TK0_Scan
	global	_TK1_Release_
	global	_TK1_Scan
	global	_TK1_value_Read
	global	_TK0_value_Read
	global	_PWM_W_OFF
	global	_PWM_Y_OFF
	global	_LED_PWM_Control
	global	_TK_10S_Reset
	global	_Sleep_mode
	global	_main
	global	_int_isr
	global	_CSAVE_ACC
	global	_CSAVE_STATUS
	global	_CPLAY_FLAG
	global	_flag1
	global	_flag2
	global	_flag3
	global	_u16_get_val
	global	_u16_release_val
	global	_u16_temp_val
	global	_u16_release_val_TK0
	global	_u16_release_val_TK1
	global	_u16_TK1_get_val_Min
	global	_u16_TK0_get_val_Min
	global	_u16_TK0_environment_val
	global	_u16_TK0_environment_val_Sum
	global	_u16_TK1_environment_val
	global	_u16_TK1_environment_val_Sum
	global	_TK0_Filter_Cnt
	global	_TK0_Filter_Cnt_T
	global	_TK1_Filter_Cnt
	global	_TK1_Filter_Cnt_T
	global	_FilterCnt_TK0
	global	_FilterCnt_TK1
	global	_SleepCnt
	global	_PWM_Duty_W
	global	_PWM_Duty_Y
	global	_T_key_Value
	global	_TK1_Key_Cnt
	global	_TK0_Key_Cnt
	global	_T0_5ms_Cnt
	global	_u8_TK_Reset_Cnt
	global	_u16_TK0_get_val_Temp
	global	_u16_TK1_get_val_Temp

	global STK06
	global STK05
	global STK04
	global STK03
	global STK02
	global STK01
	global STK00

sharebank udata_ovr 0x0010
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
UD_MC30P8160_0	udata
_CSAVE_ACC	res	1

UD_MC30P8160_1	udata
_CSAVE_STATUS	res	1

UD_MC30P8160_2	udata
_CPLAY_FLAG	res	1

UD_MC30P8160_3	udata
_flag1	res	1

UD_MC30P8160_4	udata
_flag2	res	1

UD_MC30P8160_5	udata
_flag3	res	1

UD_MC30P8160_6	udata
_u16_get_val	res	2

UD_MC30P8160_7	udata
_u16_release_val	res	2

UD_MC30P8160_8	udata
_u16_temp_val	res	2

UD_MC30P8160_9	udata
_u16_release_val_TK0	res	2

UD_MC30P8160_10	udata
_u16_release_val_TK1	res	2

UD_MC30P8160_11	udata
_u16_TK1_get_val_Min	res	2

UD_MC30P8160_12	udata
_u16_TK0_get_val_Min	res	2

UD_MC30P8160_13	udata
_u16_TK0_environment_val	res	2

UD_MC30P8160_14	udata
_u16_TK0_environment_val_Sum	res	2

UD_MC30P8160_15	udata
_u16_TK1_environment_val	res	2

UD_MC30P8160_16	udata
_u16_TK1_environment_val_Sum	res	2

UD_MC30P8160_17	udata
_TK0_Filter_Cnt	res	1

UD_MC30P8160_18	udata
_TK0_Filter_Cnt_T	res	1

UD_MC30P8160_19	udata
_TK1_Filter_Cnt	res	1

UD_MC30P8160_20	udata
_TK1_Filter_Cnt_T	res	1

UD_MC30P8160_21	udata
_FilterCnt_TK0	res	1

UD_MC30P8160_22	udata
_FilterCnt_TK1	res	1

UD_MC30P8160_23	udata
_SleepCnt	res	1

UD_MC30P8160_24	udata
_PWM_Duty_W	res	1

UD_MC30P8160_25	udata
_PWM_Duty_Y	res	1

UD_MC30P8160_26	udata
_T_key_Value	res	1

UD_MC30P8160_27	udata
_TK1_Key_Cnt	res	1

UD_MC30P8160_28	udata
_TK0_Key_Cnt	res	1

UD_MC30P8160_29	udata
_T0_5ms_Cnt	res	1

UD_MC30P8160_30	udata
_u8_TK_Reset_Cnt	res	2

UD_MC30P8160_31	udata
_u16_TK0_get_val_Temp	res	2

UD_MC30P8160_32	udata
_u16_TK1_get_val_Temp	res	2

;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
;--------------------------------------------------------
; compiler-defined variables
;--------------------------------------------------------
UDL_MC30P8160_0	udata
r0x1029	res	1
r0x102A	res	1
r0x102B	res	1
r0x102D	res	1
r0x102E	res	1
;--------------------------------------------------------
; initialized data
;--------------------------------------------------------

;@Allocation info for local variables in function 'Delay_us_2'
;@Delay_us_2 Delay_us_2                Allocated to registers ;size:2
;@Delay_us_2 INDFbits                  Allocated to registers ;size:1
;@Delay_us_2 T0CNTbits                 Allocated to registers ;size:1
;@Delay_us_2 PCLbits                   Allocated to registers ;size:1
;@Delay_us_2 STATUSbits                Allocated to registers ;size:1
;@Delay_us_2 FSRbits                   Allocated to registers ;size:1
;@Delay_us_2 P1bits                    Allocated to registers ;size:1
;@Delay_us_2 MCRbits                   Allocated to registers ;size:1
;@Delay_us_2 T0CRbits                  Allocated to registers ;size:1
;@Delay_us_2 PCLATHbits                Allocated to registers ;size:1
;@Delay_us_2 PDCONbits                 Allocated to registers ;size:1
;@Delay_us_2 ODCONbits                 Allocated to registers ;size:1
;@Delay_us_2 PUCONbits                 Allocated to registers ;size:1
;@Delay_us_2 INTEbits                  Allocated to registers ;size:1
;@Delay_us_2 INTFbits                  Allocated to registers ;size:1
;@Delay_us_2 PWM1CR0bits               Allocated to registers ;size:1
;@Delay_us_2 PWM1CR1bits               Allocated to registers ;size:1
;@Delay_us_2 PWM1CR2bits               Allocated to registers ;size:1
;@Delay_us_2 DDR1bits                  Allocated to registers ;size:1
;@Delay_us_2 TMRCRbits                 Allocated to registers ;size:1
;@Delay_us_2 T1CRbits                  Allocated to registers ;size:1
;@Delay_us_2 T1CNTbits                 Allocated to registers ;size:1
;@Delay_us_2 T1LOADbits                Allocated to registers ;size:1
;@Delay_us_2 T1DATAbits                Allocated to registers ;size:1
;@Delay_us_2 T1DATBbits                Allocated to registers ;size:1
;@Delay_us_2 T1DATCbits                Allocated to registers ;size:1
;@Delay_us_2 T1DATDbits                Allocated to registers ;size:1
;@Delay_us_2 T2CRbits                  Allocated to registers ;size:1
;@Delay_us_2 T2CNTHbits                Allocated to registers ;size:1
;@Delay_us_2 T2CNTLbits                Allocated to registers ;size:1
;@Delay_us_2 T2LOADHbits               Allocated to registers ;size:1
;@Delay_us_2 T2LOADLbits               Allocated to registers ;size:1
;@Delay_us_2 P1KBCRbits                Allocated to registers ;size:1
;@Delay_us_2 P1ADCRbits                Allocated to registers ;size:1
;@Delay_us_2 CMPCR0bits                Allocated to registers ;size:1
;@Delay_us_2 CMPCR1bits                Allocated to registers ;size:1
;@Delay_us_2 CMPCR2bits                Allocated to registers ;size:1
;@Delay_us_2 TKCR0bits                 Allocated to registers ;size:1
;@Delay_us_2 TKCR1bits                 Allocated to registers ;size:1
;@Delay_us_2 TKCR2bits                 Allocated to registers ;size:1
;@Delay_us_2 TKCNTHbits                Allocated to registers ;size:1
;@Delay_us_2 TKCNTLbits                Allocated to registers ;size:1
;@Delay_us_2 CSAVE_ACC                 Allocated to registers ;size:1
;@Delay_us_2 CSAVE_STATUS              Allocated to registers ;size:1
;@Delay_us_2 CPLAY_FLAG                Allocated to registers ;size:1
;@Delay_us_2 flag1                     Allocated to registers ;size:1
;@Delay_us_2 flag2                     Allocated to registers ;size:1
;@Delay_us_2 flag3                     Allocated to registers ;size:1
;@Delay_us_2 u16_get_val               Allocated to registers ;size:2
;@Delay_us_2 u16_release_val           Allocated to registers ;size:2
;@Delay_us_2 u16_temp_val              Allocated to registers ;size:2
;@Delay_us_2 u16_release_val_TK0       Allocated to registers ;size:2
;@Delay_us_2 u16_release_val_TK1       Allocated to registers ;size:2
;@Delay_us_2 u16_TK1_get_val_Min       Allocated to registers ;size:2
;@Delay_us_2 u16_TK0_get_val_Min       Allocated to registers ;size:2
;@Delay_us_2 u16_TK0_environment_val   Allocated to registers ;size:2
;@Delay_us_2 u16_TK0_environment_val_Sum Allocated to registers ;size:2
;@Delay_us_2 u16_TK1_environment_val   Allocated to registers ;size:2
;@Delay_us_2 u16_TK1_environment_val_Sum Allocated to registers ;size:2
;@Delay_us_2 TK0_Filter_Cnt            Allocated to registers ;size:1
;@Delay_us_2 TK0_Filter_Cnt_T          Allocated to registers ;size:1
;@Delay_us_2 TK1_Filter_Cnt            Allocated to registers ;size:1
;@Delay_us_2 TK1_Filter_Cnt_T          Allocated to registers ;size:1
;@Delay_us_2 FilterCnt_TK0             Allocated to registers ;size:1
;@Delay_us_2 FilterCnt_TK1             Allocated to registers ;size:1
;@Delay_us_2 SleepCnt                  Allocated to registers ;size:1
;@Delay_us_2 PWM_Duty_W                Allocated to registers ;size:1
;@Delay_us_2 PWM_Duty_Y                Allocated to registers ;size:1
;@Delay_us_2 T_key_Value               Allocated to registers ;size:1
;@Delay_us_2 TK1_Key_Cnt               Allocated to registers ;size:1
;@Delay_us_2 TK0_Key_Cnt               Allocated to registers ;size:1
;@Delay_us_2 T0_5ms_Cnt                Allocated to registers ;size:1
;@Delay_us_2 u8_TK_Reset_Cnt           Allocated to registers ;size:2
;@Delay_us_2 u16_TK0_get_val_Temp      Allocated to registers ;size:2
;@Delay_us_2 u16_TK1_get_val_Temp      Allocated to registers ;size:2
;@Delay_us_2 i                         Allocated to registers ;size:1
;@Delay_us_2 INDF                      Allocated to registers ;size:1
;@Delay_us_2 T0CNT                     Allocated to registers ;size:1
;@Delay_us_2 PCL                       Allocated to registers ;size:1
;@Delay_us_2 STATUS                    Allocated to registers ;size:1
;@Delay_us_2 FSR                       Allocated to registers ;size:1
;@Delay_us_2 P1                        Allocated to registers ;size:1
;@Delay_us_2 MCR                       Allocated to registers ;size:1
;@Delay_us_2 T0CR                      Allocated to registers ;size:1
;@Delay_us_2 PCLATH                    Allocated to registers ;size:1
;@Delay_us_2 PDCON                     Allocated to registers ;size:1
;@Delay_us_2 ODCON                     Allocated to registers ;size:1
;@Delay_us_2 PUCON                     Allocated to registers ;size:1
;@Delay_us_2 INTE                      Allocated to registers ;size:1
;@Delay_us_2 INTF                      Allocated to registers ;size:1
;@Delay_us_2 PWM1CR0                   Allocated to registers ;size:1
;@Delay_us_2 PWM1CR1                   Allocated to registers ;size:1
;@Delay_us_2 PWM1CR2                   Allocated to registers ;size:1
;@Delay_us_2 DDR1                      Allocated to registers ;size:1
;@Delay_us_2 TMRCR                     Allocated to registers ;size:1
;@Delay_us_2 T1CR                      Allocated to registers ;size:1
;@Delay_us_2 T1CNT                     Allocated to registers ;size:1
;@Delay_us_2 T1LOAD                    Allocated to registers ;size:1
;@Delay_us_2 T1DATA                    Allocated to registers ;size:1
;@Delay_us_2 T1DATB                    Allocated to registers ;size:1
;@Delay_us_2 T1DATC                    Allocated to registers ;size:1
;@Delay_us_2 T1DATD                    Allocated to registers ;size:1
;@Delay_us_2 T2CR                      Allocated to registers ;size:1
;@Delay_us_2 T2CNTH                    Allocated to registers ;size:1
;@Delay_us_2 T2CNTL                    Allocated to registers ;size:1
;@Delay_us_2 T2LOADH                   Allocated to registers ;size:1
;@Delay_us_2 T2LOADL                   Allocated to registers ;size:1
;@Delay_us_2 P1KBCR                    Allocated to registers ;size:1
;@Delay_us_2 P1ADCR                    Allocated to registers ;size:1
;@Delay_us_2 CMPCR0                    Allocated to registers ;size:1
;@Delay_us_2 CMPCR1                    Allocated to registers ;size:1
;@Delay_us_2 CMPCR2                    Allocated to registers ;size:1
;@Delay_us_2 TKCR0                     Allocated to registers ;size:1
;@Delay_us_2 TKCR1                     Allocated to registers ;size:1
;@Delay_us_2 TKCR2                     Allocated to registers ;size:1
;@Delay_us_2 TKCNTH                    Allocated to registers ;size:1
;@Delay_us_2 TKCNTL                    Allocated to registers ;size:1
;@end Allocation info for local variables in function 'Delay_us_2';
;@Allocation info for local variables in function 'Init_Sys'
;@end Allocation info for local variables in function 'Init_Sys';
;@Allocation info for local variables in function 'Clr_Ram'
;@end Allocation info for local variables in function 'Clr_Ram';
;@Allocation info for local variables in function 'T1_PWM_Init'
;@end Allocation info for local variables in function 'T1_PWM_Init';
;@Allocation info for local variables in function 'IO_Init'
;@end Allocation info for local variables in function 'IO_Init';
;@Allocation info for local variables in function 'TOUCH_Init'
;@end Allocation info for local variables in function 'TOUCH_Init';
;@Allocation info for local variables in function 'TK_Init'
;@end Allocation info for local variables in function 'TK_Init';
;@Allocation info for local variables in function 'Get_TK_Value'
;@end Allocation info for local variables in function 'Get_TK_Value';
;@Allocation info for local variables in function 'TK0_Release_'
;@end Allocation info for local variables in function 'TK0_Release_';
;@Allocation info for local variables in function 'TK0_Scan'
;@end Allocation info for local variables in function 'TK0_Scan';
;@Allocation info for local variables in function 'TK1_Release_'
;@end Allocation info for local variables in function 'TK1_Release_';
;@Allocation info for local variables in function 'TK1_Scan'
;@end Allocation info for local variables in function 'TK1_Scan';
;@Allocation info for local variables in function 'TK1_value_Read'
;@end Allocation info for local variables in function 'TK1_value_Read';
;@Allocation info for local variables in function 'TK0_value_Read'
;@end Allocation info for local variables in function 'TK0_value_Read';
;@Allocation info for local variables in function 'PWM_W_OFF'
;@end Allocation info for local variables in function 'PWM_W_OFF';
;@Allocation info for local variables in function 'PWM_Y_OFF'
;@end Allocation info for local variables in function 'PWM_Y_OFF';
;@Allocation info for local variables in function 'LED_PWM_Control'
;@end Allocation info for local variables in function 'LED_PWM_Control';
;@Allocation info for local variables in function 'TK_10S_Reset'
;@end Allocation info for local variables in function 'TK_10S_Reset';
;@Allocation info for local variables in function 'Sleep_mode'
;@end Allocation info for local variables in function 'Sleep_mode';
;@Allocation info for local variables in function 'main'
;@end Allocation info for local variables in function 'main';
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
;; Starting pCode block
_int_isr	;Function start
; 0 exit points
;	.line	898; "MC30P8160.c"	__endasm;
	MOVRA	_CSAVE_ACC
	SWAPAR	STATUS
	MOVRA	_CSAVE_STATUS
	
;	.line	901; "MC30P8160.c"	if(T0IF)
	JBSET	_INTFbits,0
	GOTO	_00468_DS_
;	.line	903; "MC30P8160.c"	T0IF   = 0; 
	BCLR	_INTFbits,0
;	.line	904; "MC30P8160.c"	T0CNT = 217; // T0没有自动重载器，
	MOVAI	0xd9
	MOVRA	_T0CNT
;	.line	906; "MC30P8160.c"	T0_5ms_Flag = 1;
	BSET	_flag1,4
;	.line	909; "MC30P8160.c"	T0_5ms_Cnt ++;
	INCR	_T0_5ms_Cnt
;;unsigned compare: left < lit(0x2=2), size=1
;	.line	910; "MC30P8160.c"	if(T0_5ms_Cnt >= 2)
	MOVAI	0x02
	RSUBAR	_T0_5ms_Cnt
	JBSET	STATUS,0
	GOTO	_00468_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	912; "MC30P8160.c"	T0_5ms_Cnt = 0;
	CLRR	_T0_5ms_Cnt
;	.line	913; "MC30P8160.c"	T0_10ms_Flag = 1;
	BSET	_flag1,5
_00468_DS_
;	.line	918; "MC30P8160.c"	if(T1IF)
	JBSET	_TMRCRbits,0
	GOTO	_00470_DS_
;	.line	920; "MC30P8160.c"	T1IF   = 0; 
	BCLR	_TMRCRbits,0
_00470_DS_
;	.line	931; "MC30P8160.c"	__endasm;
	SWAPAR	_CSAVE_STATUS
	MOVRA	STATUS
	SWAPR	_CSAVE_ACC
	SWAPAR	_CSAVE_ACC
	
END_OF_INTERRUPT
;	.line	932; "MC30P8160.c"	}
	RETIE	

;--------------------------------------------------------
; code
;--------------------------------------------------------
code_MC30P8160	code
;***
;  pBlock Stats: dbName = M
;***
;entry:  _main	;Function start
; 2 exit points
;has an exit
;functions called:
;   _Clr_Ram
;   _Init_Sys
;   _IO_Init
;   _Delay_us_2
;   _TOUCH_Init
;   _T1_PWM_Init
;   _TK0_Scan
;   _TK1_Scan
;   _TK0_value_Read
;   _TK1_value_Read
;   _LED_PWM_Control
;   _TK_10S_Reset
;   _Sleep_mode
;   _Clr_Ram
;   _Init_Sys
;   _IO_Init
;   _Delay_us_2
;   _TOUCH_Init
;   _T1_PWM_Init
;   _TK0_Scan
;   _TK1_Scan
;   _TK0_value_Read
;   _TK1_value_Read
;   _LED_PWM_Control
;   _TK_10S_Reset
;   _Sleep_mode
;; Starting pCode block
_main	;Function start
; 2 exit points
;	.line	835; "MC30P8160.c"	Clr_Ram();
	CALL	_Clr_Ram
;	.line	836; "MC30P8160.c"	Init_Sys();
	CALL	_Init_Sys
;	.line	838; "MC30P8160.c"	IO_Init();
	CALL	_IO_Init
;	.line	840; "MC30P8160.c"	Delay_us_2(0x5020); // 4M 约100ms
	MOVAI	0x20
	CALL	_Delay_us_2
;	.line	842; "MC30P8160.c"	TOUCH_Init(); // 设置触摸寄存器 
	CALL	_TOUCH_Init
;	.line	844; "MC30P8160.c"	T1_PWM_Init();
	CALL	_T1_PWM_Init
;	.line	845; "MC30P8160.c"	SleepCnt = 0xff;
	MOVAI	0xff
	MOVRA	_SleepCnt
;	.line	847; "MC30P8160.c"	PWM_Duty_W = 0xff; // 
	MOVAI	0xff
	MOVRA	_PWM_Duty_W
;	.line	848; "MC30P8160.c"	PWM_Duty_Y = 0xff; // 
	MOVAI	0xff
	MOVRA	_PWM_Duty_Y
;	.line	850; "MC30P8160.c"	W_AS_Flag = 1;
	BSET	_flag1,7
;	.line	851; "MC30P8160.c"	Y_AS_Flag = 1;
	BSET	_flag3,0
;	.line	852; "MC30P8160.c"	Pre_T_Key0_Release = 1;
	BSET	_flag1,1
;	.line	853; "MC30P8160.c"	u16_TK0_get_val_Min = 0xFFFF;
	MOVAI	0xff
	MOVRA	_u16_TK0_get_val_Min
	MOVRA	(_u16_TK0_get_val_Min + 1)
;	.line	854; "MC30P8160.c"	u16_TK1_get_val_Min = 0xFFFF;
	MOVAI	0xff
	MOVRA	_u16_TK1_get_val_Min
	MOVRA	(_u16_TK1_get_val_Min + 1)
_00460_DS_
;	.line	858; "MC30P8160.c"	if(T0_5ms_Flag)
	JBSET	_flag1,4
	GOTO	_00456_DS_
;	.line	860; "MC30P8160.c"	T0_5ms_Flag = 0;
	BCLR	_flag1,4
;	.line	862; "MC30P8160.c"	TK0_Scan();                                
	CALL	_TK0_Scan
;	.line	863; "MC30P8160.c"	TK1_Scan();    	   	   	   	
	CALL	_TK1_Scan
_00456_DS_
;	.line	869; "MC30P8160.c"	if(T0_10ms_Flag) 
	JBSET	_flag1,5
	GOTO	_00458_DS_
;	.line	871; "MC30P8160.c"	T0_10ms_Flag = 0;
	BCLR	_flag1,5
;	.line	873; "MC30P8160.c"	TK0_value_Read();
	CALL	_TK0_value_Read
;	.line	874; "MC30P8160.c"	TK1_value_Read();
	CALL	_TK1_value_Read
;	.line	876; "MC30P8160.c"	LED_PWM_Control();     	   	   	 
	CALL	_LED_PWM_Control
;	.line	878; "MC30P8160.c"	TK_10S_Reset();
	CALL	_TK_10S_Reset
;	.line	879; "MC30P8160.c"	Sleep_mode();
	CALL	_Sleep_mode
_00458_DS_
;	.line	882; "MC30P8160.c"	WDT_Clear();
	CLRWDT	
	GOTO	_00460_DS_
;	.line	885; "MC30P8160.c"	}
	RETURN	
; exit point of _main

;***
;  pBlock Stats: dbName = C
;***
;entry:  _Sleep_mode	;Function start
; 2 exit points
;has an exit
;; Starting pCode block
_Sleep_mode	;Function start
; 2 exit points
;	.line	798; "MC30P8160.c"	if(SleepCnt) 
	MOVAI	0x00
	ORAR	_SleepCnt
	JBCLR	STATUS,2
	GOTO	_00444_DS_
;	.line	800; "MC30P8160.c"	SleepCnt--;
	DECR	_SleepCnt
_00444_DS_
;	.line	803; "MC30P8160.c"	if(W_Power_Flag || Y_Power_Flag)
	JBCLR	_flag2,0
	GOTO	_00445_DS_
	JBSET	_flag2,5
	GOTO	_00446_DS_
_00445_DS_
;	.line	805; "MC30P8160.c"	SleepCnt = 0xFF; // 2.55s
	MOVAI	0xff
	MOVRA	_SleepCnt
_00446_DS_
;	.line	809; "MC30P8160.c"	if(!SleepCnt)
	MOVAI	0x00
	ORAR	_SleepCnt
	JBSET	STATUS,2
	GOTO	_00450_DS_
;	.line	812; "MC30P8160.c"	TKEN = 0;       //关闭TK
	BCLR	_TKCR0bits,7
;	.line	815; "MC30P8160.c"	SLEEP();   //休眠两种编写方式(方式二)
	STOP	
;	.line	819; "MC30P8160.c"	TKEN = 1;  	   //打开TK
	BSET	_TKCR0bits,7
;	.line	822; "MC30P8160.c"	T0_5ms_Flag = 1;
	BSET	_flag1,4
;	.line	823; "MC30P8160.c"	T0_10ms_Flag = 1;
	BSET	_flag1,5
_00450_DS_
;	.line	826; "MC30P8160.c"	}
	RETURN	
; exit point of _Sleep_mode

;***
;  pBlock Stats: dbName = C
;***
;entry:  _TK_10S_Reset	;Function start
; 2 exit points
;has an exit
;functions called:
;   _TK0_Release_
;   _TK1_Release_
;   _TK0_Release_
;   _TK1_Release_
;; Starting pCode block
_TK_10S_Reset	;Function start
; 2 exit points
;	.line	777; "MC30P8160.c"	if (T_Key0_Signal || T_Key1_Signal)
	JBCLR	_flag1,0
	GOTO	_00424_DS_
	JBSET	_flag2,3
	GOTO	_00425_DS_
_00424_DS_
;	.line	779; "MC30P8160.c"	u8_TK_Reset_Cnt++;
	INCR	_u8_TK_Reset_Cnt
	JBCLR	STATUS,2
	INCR	(_u8_TK_Reset_Cnt + 1)
;;unsigned compare: left < lit(0x3E8=1000), size=2
;	.line	780; "MC30P8160.c"	if (u8_TK_Reset_Cnt >= 1000) // 10s
	MOVAI	0x03
	RSUBAR	(_u8_TK_Reset_Cnt + 1)
	JBSET	STATUS,2
	GOTO	_00438_DS_
	MOVAI	0xe8
	RSUBAR	_u8_TK_Reset_Cnt
_00438_DS_
	JBSET	STATUS,0
	GOTO	_00428_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	783; "MC30P8160.c"	TK0_Release_();
	CALL	_TK0_Release_
;	.line	784; "MC30P8160.c"	TK1_Release_();
	CALL	_TK1_Release_
	GOTO	_00428_DS_
_00425_DS_
;	.line	789; "MC30P8160.c"	u8_TK_Reset_Cnt = 0;
	CLRR	_u8_TK_Reset_Cnt
	CLRR	(_u8_TK_Reset_Cnt + 1)
_00428_DS_
;	.line	792; "MC30P8160.c"	}
	RETURN	
; exit point of _TK_10S_Reset

;***
;  pBlock Stats: dbName = C
;***
;entry:  _LED_PWM_Control	;Function start
; 2 exit points
;has an exit
;functions called:
;   _PWM_W_OFF
;   _PWM_Y_OFF
;   _PWM_W_OFF
;   _PWM_Y_OFF
;1 compiler assigned register :
;   r0x1029
;; Starting pCode block
_LED_PWM_Control	;Function start
; 2 exit points
;	.line	709; "MC30P8160.c"	if(PWM_Change_KeyFlg == 1)     	//按键值改变更新状态
	CLRR	r0x1029
	JBCLR	_flag2,1
	INCR	r0x1029
	MOVAR	r0x1029
	XORAI	0x01
	JBSET	STATUS,2
	GOTO	_00392_DS_
;	.line	711; "MC30P8160.c"	PWM_Change_KeyFlg = 0;
	BCLR	_flag2,1
;	.line	713; "MC30P8160.c"	if(W_Power_Flag == 0)
	JBCLR	_flag2,0
	GOTO	_00386_DS_
;	.line	715; "MC30P8160.c"	PWM_W_OFF();   	   	   	
	CALL	_PWM_W_OFF
	GOTO	_00387_DS_
_00386_DS_
;	.line	719; "MC30P8160.c"	T1DATD = PWM_Duty_W; //PWM_Duty_W
	MOVAR	_PWM_Duty_W
	MOVRA	_T1DATD
;	.line	720; "MC30P8160.c"	PWM1DOE = 1; //打开端口输出脉宽调制波形
	BSET	_PWM1CR0bits,5
;	.line	721; "MC30P8160.c"	PWM1DEN = 1; //打开 PWM1D 功能 	
	BSET	_PWM1CR0bits,4
_00387_DS_
;	.line	724; "MC30P8160.c"	if (Y_Power_Flag == 0)
	JBCLR	_flag2,5
	GOTO	_00389_DS_
;	.line	726; "MC30P8160.c"	PWM_Y_OFF();
	CALL	_PWM_Y_OFF
	GOTO	_00392_DS_
_00389_DS_
;	.line	730; "MC30P8160.c"	T1DATC = PWM_Duty_Y;
	MOVAR	_PWM_Duty_Y
	MOVRA	_T1DATC
;	.line	731; "MC30P8160.c"	PWM1COE = 1; //打开端口输出脉宽调制波形
	BSET	_PWM1CR0bits,3
;	.line	732; "MC30P8160.c"	PWM1CEN = 1; //打开 PWM1D 功能  
	BSET	_PWM1CR0bits,2
_00392_DS_
;	.line	737; "MC30P8160.c"	if(TK1_Long_press_Flag) //长按无极调光（255极）
	JBSET	_flag1,3
	GOTO	_00404_DS_
;	.line	739; "MC30P8160.c"	if(Y_AS_Flag && Y_Power_Flag)      	//逐渐变暗
	JBSET	_flag3,0
	GOTO	_00400_DS_
	JBSET	_flag2,5
	GOTO	_00400_DS_
;;unsigned compare: left < lit(0xFF=255), size=1
;	.line	741; "MC30P8160.c"	if(PWM_Duty_Y < 255) //最大亮度 100%
	MOVAI	0xff
	RSUBAR	_PWM_Duty_Y
	JBCLR	STATUS,0
	GOTO	_00404_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	743; "MC30P8160.c"	PWM_Duty_Y ++;
	INCR	_PWM_Duty_Y
	GOTO	_00404_DS_
_00400_DS_
;	.line	746; "MC30P8160.c"	else if(Y_Power_Flag)  	//逐渐变亮
	JBSET	_flag2,5
	GOTO	_00404_DS_
;;swapping arguments (AOP_TYPEs 1/3)
;;unsigned compare: left >= lit(0xD=13), size=1
;	.line	748; "MC30P8160.c"	if(PWM_Duty_Y > 12 ) //最小亮度PWM值：255 * 5%，
	MOVAI	0x0d
	RSUBAR	_PWM_Duty_Y
	JBSET	STATUS,0
	GOTO	_00404_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	750; "MC30P8160.c"	PWM_Duty_Y --; 
	DECR	_PWM_Duty_Y
_00404_DS_
;	.line	755; "MC30P8160.c"	if (TK0_Long_press_Flag) //长按无极调光（255极）
	JBSET	_flag1,6
	GOTO	_00417_DS_
;	.line	757; "MC30P8160.c"	if (W_AS_Flag && W_Power_Flag)     	//逐渐变暗
	JBSET	_flag1,7
	GOTO	_00412_DS_
	JBSET	_flag2,0
	GOTO	_00412_DS_
;;unsigned compare: left < lit(0xFF=255), size=1
;	.line	759; "MC30P8160.c"	if (PWM_Duty_W < 255) //最大亮度 100%
	MOVAI	0xff
	RSUBAR	_PWM_Duty_W
	JBCLR	STATUS,0
	GOTO	_00417_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	761; "MC30P8160.c"	PWM_Duty_W++;
	INCR	_PWM_Duty_W
	GOTO	_00417_DS_
_00412_DS_
;	.line	764; "MC30P8160.c"	else if(W_Power_Flag)  	//逐渐变亮
	JBSET	_flag2,0
	GOTO	_00417_DS_
;;swapping arguments (AOP_TYPEs 1/3)
;;unsigned compare: left >= lit(0xD=13), size=1
;	.line	766; "MC30P8160.c"	if (PWM_Duty_W > 12) //最小亮度PWM值：255 * 8%，
	MOVAI	0x0d
	RSUBAR	_PWM_Duty_W
	JBSET	STATUS,0
	GOTO	_00417_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	768; "MC30P8160.c"	PWM_Duty_W--;
	DECR	_PWM_Duty_W
_00417_DS_
;	.line	772; "MC30P8160.c"	}
	RETURN	
; exit point of _LED_PWM_Control

;***
;  pBlock Stats: dbName = C
;***
;entry:  _PWM_Y_OFF	;Function start
; 2 exit points
;has an exit
;; Starting pCode block
_PWM_Y_OFF	;Function start
; 2 exit points
;	.line	701; "MC30P8160.c"	T1DATC = 0;
	CLRR	_T1DATC
;	.line	702; "MC30P8160.c"	PWM1COE = 0; //禁止端口输出脉宽调制波形；
	BCLR	_PWM1CR0bits,3
;	.line	703; "MC30P8160.c"	PWM1CEN = 0; //关闭 PWM1C 功能；
	BCLR	_PWM1CR0bits,2
;	.line	704; "MC30P8160.c"	}
	RETURN	
; exit point of _PWM_Y_OFF

;***
;  pBlock Stats: dbName = C
;***
;entry:  _PWM_W_OFF	;Function start
; 2 exit points
;has an exit
;; Starting pCode block
_PWM_W_OFF	;Function start
; 2 exit points
;	.line	694; "MC30P8160.c"	T1DATD = 0;
	CLRR	_T1DATD
;	.line	695; "MC30P8160.c"	PWM1DOE = 0; //禁止端口输出脉宽调制波形；
	BCLR	_PWM1CR0bits,5
;	.line	696; "MC30P8160.c"	PWM1DEN = 0; //关闭 PWM1D 功能；
	BCLR	_PWM1CR0bits,4
;	.line	697; "MC30P8160.c"	}
	RETURN	
; exit point of _PWM_W_OFF

;***
;  pBlock Stats: dbName = C
;***
;entry:  _TK0_value_Read	;Function start
; 2 exit points
;has an exit
;2 compiler assigned registers:
;   r0x1029
;   r0x102A
;; Starting pCode block
_TK0_value_Read	;Function start
; 2 exit points
;	.line	648; "MC30P8160.c"	if(T_Key0_Signal && TK0_Key_Release_Flag == 0) //有按键按下
	JBSET	_flag1,0
	GOTO	_00369_DS_
	JBCLR	_flag2,2
	GOTO	_00369_DS_
;	.line	650; "MC30P8160.c"	TK0_Key_Cnt++;
	INCR	_TK0_Key_Cnt
;	.line	652; "MC30P8160.c"	PWM_Change_KeyFlg = 1;
	BSET	_flag2,1
;	.line	654; "MC30P8160.c"	if (TK0_Key_Cnt == 60) //600ms
	MOVAR	_TK0_Key_Cnt
	XORAI	0x3c
	JBSET	STATUS,2
	GOTO	_00372_DS_
;	.line	656; "MC30P8160.c"	TK1_Key_Release_Flag = 1;
	BSET	_flag2,7
;	.line	659; "MC30P8160.c"	if (TK0_Long_press_Flag == 0)
	JBCLR	_flag1,6
	GOTO	_00372_DS_
;	.line	661; "MC30P8160.c"	TK0_Long_press_Flag = 1;  	//长按标志位置1
	BSET	_flag1,6
;	.line	663; "MC30P8160.c"	PWM_Change_KeyFlg = 1;
	BSET	_flag2,1
;	.line	665; "MC30P8160.c"	W_AS_Flag = !W_AS_Flag;   	//调亮调暗标志位状态变换
	CLRR	r0x1029
	JBCLR	_flag1,7
	INCR	r0x1029
	MOVAR	r0x1029
	MOVAI	0x00
	JBCLR	STATUS,2
	MOVAI	0x01
	MOVRA	r0x1029
;;1	MOVRA	r0x102A
;;102	MOVAR	r0x102A
	RRAR	r0x1029
	JBSET	STATUS,0
	BCLR	_flag1,7
	JBCLR	STATUS,0
	BSET	_flag1,7
	GOTO	_00372_DS_
_00369_DS_
;	.line	669; "MC30P8160.c"	else if(T_Key0_Signal == 0)
	JBCLR	_flag1,0
	GOTO	_00372_DS_
;	.line	671; "MC30P8160.c"	TK0_Long_press_Flag = 0;
	BCLR	_flag1,6
;;swapping arguments (AOP_TYPEs 1/3)
;;unsigned compare: left >= lit(0x2=2), size=1
;	.line	673; "MC30P8160.c"	if (TK0_Key_Cnt > 1 && TK0_Key_Cnt < 60)
	MOVAI	0x02
	RSUBAR	_TK0_Key_Cnt
	JBSET	STATUS,0
	GOTO	_00364_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;;unsigned compare: left < lit(0x3C=60), size=1
	MOVAI	0x3c
	RSUBAR	_TK0_Key_Cnt
	JBCLR	STATUS,0
	GOTO	_00364_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	675; "MC30P8160.c"	PWM_Change_KeyFlg = 1;
	BSET	_flag2,1
;	.line	677; "MC30P8160.c"	if (W_Power_Flag)
	JBSET	_flag2,0
	GOTO	_00361_DS_
;	.line	679; "MC30P8160.c"	W_Power_Flag = 0;
	BCLR	_flag2,0
	GOTO	_00364_DS_
_00361_DS_
;	.line	683; "MC30P8160.c"	W_Power_Flag = 1;
	BSET	_flag2,0
_00364_DS_
;	.line	687; "MC30P8160.c"	TK0_Key_Release_Flag = 0;
	BCLR	_flag2,2
;	.line	688; "MC30P8160.c"	TK0_Key_Cnt = 0;
	CLRR	_TK0_Key_Cnt
_00372_DS_
;	.line	690; "MC30P8160.c"	}
	RETURN	
; exit point of _TK0_value_Read

;***
;  pBlock Stats: dbName = C
;***
;entry:  _TK1_value_Read	;Function start
; 2 exit points
;has an exit
;2 compiler assigned registers:
;   r0x1029
;   r0x102A
;; Starting pCode block
_TK1_value_Read	;Function start
; 2 exit points
;	.line	601; "MC30P8160.c"	if(T_Key1_Signal && TK1_Key_Release_Flag == 0) //有按键按下
	JBSET	_flag2,3
	GOTO	_00348_DS_
	JBCLR	_flag2,7
	GOTO	_00348_DS_
;	.line	603; "MC30P8160.c"	TK1_Key_Cnt ++;
	INCR	_TK1_Key_Cnt
;	.line	605; "MC30P8160.c"	PWM_Change_KeyFlg = 1;
	BSET	_flag2,1
;	.line	607; "MC30P8160.c"	if(TK1_Key_Cnt == 60) //600ms
	MOVAR	_TK1_Key_Cnt
	XORAI	0x3c
	JBSET	STATUS,2
	GOTO	_00351_DS_
;	.line	609; "MC30P8160.c"	TK0_Key_Release_Flag = 1;
	BSET	_flag2,2
;	.line	612; "MC30P8160.c"	if(TK1_Long_press_Flag == 0)
	JBCLR	_flag1,3
	GOTO	_00351_DS_
;	.line	614; "MC30P8160.c"	TK1_Long_press_Flag = 1;   	//长按标志位置1
	BSET	_flag1,3
;	.line	616; "MC30P8160.c"	PWM_Change_KeyFlg = 1;
	BSET	_flag2,1
;	.line	618; "MC30P8160.c"	Y_AS_Flag = !Y_AS_Flag;    	//调亮调暗标志位状态变换
	CLRR	r0x1029
	JBCLR	_flag3,0
	INCR	r0x1029
	MOVAR	r0x1029
	MOVAI	0x00
	JBCLR	STATUS,2
	MOVAI	0x01
	MOVRA	r0x1029
;;1	MOVRA	r0x102A
;;101	MOVAR	r0x102A
	RRAR	r0x1029
	JBSET	STATUS,0
	BCLR	_flag3,0
	JBCLR	STATUS,0
	BSET	_flag3,0
	GOTO	_00351_DS_
_00348_DS_
;	.line	623; "MC30P8160.c"	else if(T_Key1_Signal == 0)
	JBCLR	_flag2,3
	GOTO	_00351_DS_
;	.line	625; "MC30P8160.c"	TK1_Long_press_Flag = 0;   	//长按标志位清0
	BCLR	_flag1,3
;;swapping arguments (AOP_TYPEs 1/3)
;;unsigned compare: left >= lit(0x2=2), size=1
;	.line	627; "MC30P8160.c"	if(TK1_Key_Cnt > 1 && TK1_Key_Cnt < 60)
	MOVAI	0x02
	RSUBAR	_TK1_Key_Cnt
	JBSET	STATUS,0
	GOTO	_00343_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;;unsigned compare: left < lit(0x3C=60), size=1
	MOVAI	0x3c
	RSUBAR	_TK1_Key_Cnt
	JBCLR	STATUS,0
	GOTO	_00343_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	629; "MC30P8160.c"	PWM_Change_KeyFlg = 1;
	BSET	_flag2,1
;	.line	631; "MC30P8160.c"	if (Y_Power_Flag)
	JBSET	_flag2,5
	GOTO	_00340_DS_
;	.line	633; "MC30P8160.c"	Y_Power_Flag = 0;
	BCLR	_flag2,5
	GOTO	_00343_DS_
_00340_DS_
;	.line	637; "MC30P8160.c"	Y_Power_Flag = 1;
	BSET	_flag2,5
_00343_DS_
;	.line	640; "MC30P8160.c"	TK1_Key_Release_Flag = 0;
	BCLR	_flag2,7
;	.line	641; "MC30P8160.c"	TK1_Key_Cnt = 0;
	CLRR	_TK1_Key_Cnt
_00351_DS_
;	.line	643; "MC30P8160.c"	}
	RETURN	
; exit point of _TK1_value_Read

;***
;  pBlock Stats: dbName = C
;***
;entry:  _TK1_Scan	;Function start
; 2 exit points
;has an exit
;functions called:
;   _TK_Init
;   _Get_TK_Value
;   _TK1_Release_
;   _TK_Init
;   _Get_TK_Value
;   _TK1_Release_
;2 compiler assigned registers:
;   r0x102D
;   r0x102E
;; Starting pCode block
_TK1_Scan	;Function start
; 2 exit points
;	.line	489; "MC30P8160.c"	DDR1 |= 0x02;     // 1： 端口作为输入口          0： 端口作为输出口
	BSET	_DDR1,1
;	.line	490; "MC30P8160.c"	P1ADCR |= 0x02;   // 0 使能端口的数字 I/O 功能； 1 关闭端口的数字 I/O 功能；
	BSET	_P1ADCR,1
;	.line	492; "MC30P8160.c"	TKCR1 = 0x01; // 写0000_0000 bit0-1: 01 TK1 选择相应按键输入通道
	MOVAI	0x01
	MOVRA	_TKCR1
;	.line	493; "MC30P8160.c"	TK_Init();
	CALL	_TK_Init
;	.line	495; "MC30P8160.c"	Get_TK_Value();
	CALL	_Get_TK_Value
;	.line	498; "MC30P8160.c"	DDR1 &= 0xFD;     // 1： 端口作为输入口         0： 端口作为输出口
	BCLR	_DDR1,1
;	.line	499; "MC30P8160.c"	P1ADCR &= 0xFD;   // 1 关闭端口的数字 I/O 功能； 0 使能端口的数字 I/O 功能； 
	BCLR	_P1ADCR,1
;	.line	500; "MC30P8160.c"	P10D = 0;
	BCLR	_P1bits,0
;	.line	507; "MC30P8160.c"	u16_TK1_get_val_Temp = u16_get_val;
	MOVAR	_u16_get_val
	MOVRA	_u16_TK1_get_val_Temp
	MOVAR	(_u16_get_val + 1)
	MOVRA	(_u16_TK1_get_val_Temp + 1)
;	.line	514; "MC30P8160.c"	if(Pre_T_Key1_Release) 
	JBSET	_flag2,4
	GOTO	_00271_DS_
;	.line	516; "MC30P8160.c"	u16_temp_val = u16_get_val + Const_SEN_T_Key1;
	MOVAI	0x2d
	ADDAR	_u16_get_val
	MOVRA	_u16_temp_val
	CLRR	(_u16_temp_val + 1)
	RLR	(_u16_temp_val + 1)
	MOVAR	(_u16_get_val + 1)
	ADDRA	(_u16_temp_val + 1)
;	.line	518; "MC30P8160.c"	if(u16_temp_val < u16_TK1_environment_val) 	 //按下
	MOVAR	(_u16_TK1_environment_val + 1)
	RSUBAR	(_u16_temp_val + 1)
	JBSET	STATUS,2
	GOTO	_00323_DS_
	MOVAR	_u16_TK1_environment_val
	RSUBAR	_u16_temp_val
_00323_DS_
	JBCLR	STATUS,0
	GOTO	_00260_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	520; "MC30P8160.c"	SleepCnt = 0xFF;
	MOVAI	0xff
	MOVRA	_SleepCnt
;	.line	521; "MC30P8160.c"	FilterCnt_TK1 ++;
	INCR	_FilterCnt_TK1
;;swapping arguments (AOP_TYPEs 1/3)
;;unsigned compare: left >= lit(0xC=12), size=1
;	.line	522; "MC30P8160.c"	if(FilterCnt_TK1 > FilterCnt_Value)
	MOVAI	0x0c
	RSUBAR	_FilterCnt_TK1
	JBSET	STATUS,0
	GOTO	_00273_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	524; "MC30P8160.c"	T_Key1_Signal = 1;
	BSET	_flag2,3
;	.line	525; "MC30P8160.c"	Pre_T_Key1_Release = 0;
	BCLR	_flag2,4
;	.line	526; "MC30P8160.c"	u16_release_val_TK1 = u16_TK1_environment_val - Const_SEN_T_Key1; //
	MOVAI	0xd3
	ADDAR	_u16_TK1_environment_val
	MOVRA	_u16_release_val_TK1
	MOVAI	0xff
	MOVRA	(_u16_release_val_TK1 + 1)
	MOVAR	(_u16_TK1_environment_val + 1)
	JBCLR	STATUS,0
	JZAR	(_u16_TK1_environment_val + 1)
	ADDRA	(_u16_release_val_TK1 + 1)
	GOTO	_00273_DS_
_00260_DS_
;	.line	531; "MC30P8160.c"	FilterCnt_TK1 = 0;
	CLRR	_FilterCnt_TK1
;	.line	533; "MC30P8160.c"	if(SleepCnt)
	MOVAI	0x00
	ORAR	_SleepCnt
	JBCLR	STATUS,2
	GOTO	_00253_DS_
;	.line	535; "MC30P8160.c"	TK1_Filter_Cnt_T ++;
	INCR	_TK1_Filter_Cnt_T
;;unsigned compare: left < lit(0x4=4), size=1
;	.line	537; "MC30P8160.c"	if(TK1_Filter_Cnt_T >= 4)
	MOVAI	0x04
	RSUBAR	_TK1_Filter_Cnt_T
	JBSET	STATUS,0
	GOTO	_00247_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	539; "MC30P8160.c"	TK1_Filter_Cnt_T = 0;
	CLRR	_TK1_Filter_Cnt_T
;	.line	540; "MC30P8160.c"	u16_TK1_environment_val_Sum += u16_get_val;
	MOVAR	_u16_get_val
	ADDRA	_u16_TK1_environment_val_Sum
	MOVAR	(_u16_get_val + 1)
	JBCLR	STATUS,0
	JZAR	(_u16_get_val + 1)
	ADDRA	(_u16_TK1_environment_val_Sum + 1)
;	.line	541; "MC30P8160.c"	TK1_Filter_Cnt++;
	INCR	_TK1_Filter_Cnt
;;swapping arguments (AOP_TYPEs 1/3)
;;unsigned compare: left >= lit(0x8=8), size=1
_00247_DS_
;	.line	544; "MC30P8160.c"	if(TK1_Filter_Cnt > 7)
	MOVAI	0x08
	RSUBAR	_TK1_Filter_Cnt
	JBSET	STATUS,0
	GOTO	_00254_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	546; "MC30P8160.c"	TK1_Filter_Cnt = 0;
	CLRR	_TK1_Filter_Cnt
;;shiftRight_Left2ResultLit:5339: shCount=1, size=2, sign=0, same=0, offr=0
;	.line	547; "MC30P8160.c"	u16_TK1_environment_val = u16_TK1_environment_val_Sum >> 3;
	BCLR	STATUS,0
	RRAR	(_u16_TK1_environment_val_Sum + 1)
	MOVRA	(_u16_TK1_environment_val + 1)
	RRAR	_u16_TK1_environment_val_Sum
	MOVRA	_u16_TK1_environment_val
;;shiftRight_Left2ResultLit:5339: shCount=1, size=2, sign=0, same=1, offr=0
	BCLR	STATUS,0
	RRR	(_u16_TK1_environment_val + 1)
	RRR	_u16_TK1_environment_val
;;shiftRight_Left2ResultLit:5339: shCount=1, size=2, sign=0, same=1, offr=0
	BCLR	STATUS,0
	RRR	(_u16_TK1_environment_val + 1)
	RRR	_u16_TK1_environment_val
;	.line	548; "MC30P8160.c"	u16_TK1_environment_val_Sum = 0;
	CLRR	_u16_TK1_environment_val_Sum
	CLRR	(_u16_TK1_environment_val_Sum + 1)
;	.line	550; "MC30P8160.c"	if(TK1_Release_Flag)
	JBSET	_flag2,6
	GOTO	_00254_DS_
;	.line	552; "MC30P8160.c"	TK1_Release_Flag = 0;
	BCLR	_flag2,6
;	.line	553; "MC30P8160.c"	u16_TK1_environment_val = u16_get_val;
	MOVAR	_u16_get_val
	MOVRA	_u16_TK1_environment_val
	MOVAR	(_u16_get_val + 1)
	MOVRA	(_u16_TK1_environment_val + 1)
	GOTO	_00254_DS_
_00253_DS_
;	.line	559; "MC30P8160.c"	u16_TK1_environment_val = u16_get_val;
	MOVAR	_u16_get_val
	MOVRA	_u16_TK1_environment_val
	MOVAR	(_u16_get_val + 1)
	MOVRA	(_u16_TK1_environment_val + 1)
;	.line	560; "MC30P8160.c"	u16_TK1_environment_val_Sum = 0;
	CLRR	_u16_TK1_environment_val_Sum
	CLRR	(_u16_TK1_environment_val_Sum + 1)
;	.line	561; "MC30P8160.c"	TK1_Filter_Cnt = 0;
	CLRR	_TK1_Filter_Cnt
_00254_DS_
;	.line	564; "MC30P8160.c"	if(TK1_Release_Flag == 1)
	CLRR	r0x102D
	JBCLR	_flag2,6
	INCR	r0x102D
	MOVAR	r0x102D
	XORAI	0x01
	JBSET	STATUS,2
	GOTO	_00273_DS_
;	.line	566; "MC30P8160.c"	if(u16_get_val > u16_TK1_environment_val)
	MOVAR	(_u16_get_val + 1)
	RSUBAR	(_u16_TK1_environment_val + 1)
	JBSET	STATUS,2
	GOTO	_00327_DS_
	MOVAR	_u16_get_val
	RSUBAR	_u16_TK1_environment_val
_00327_DS_
	JBCLR	STATUS,0
	GOTO	_00273_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	568; "MC30P8160.c"	u16_TK1_environment_val = u16_get_val;
	MOVAR	_u16_get_val
	MOVRA	_u16_TK1_environment_val
	MOVAR	(_u16_get_val + 1)
	MOVRA	(_u16_TK1_environment_val + 1)
	GOTO	_00273_DS_
_00271_DS_
;	.line	575; "MC30P8160.c"	if(u16_get_val < u16_TK1_get_val_Min)
	MOVAR	(_u16_TK1_get_val_Min + 1)
	RSUBAR	(_u16_get_val + 1)
	JBSET	STATUS,2
	GOTO	_00328_DS_
	MOVAR	_u16_TK1_get_val_Min
	RSUBAR	_u16_get_val
_00328_DS_
	JBCLR	STATUS,0
	GOTO	_00263_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	577; "MC30P8160.c"	u16_TK1_get_val_Min = u16_get_val;
	MOVAR	_u16_get_val
	MOVRA	_u16_TK1_get_val_Min
	MOVAR	(_u16_get_val + 1)
	MOVRA	(_u16_TK1_get_val_Min + 1)
_00263_DS_
;	.line	580; "MC30P8160.c"	u16_temp_val = u16_release_val_TK1 + Const_SEN_T_Key1 + u16_TK1_get_val_Min;
	MOVAI	0x2d
	ADDAR	_u16_release_val_TK1
	MOVRA	r0x102D
	CLRR	r0x102E
	RLR	r0x102E
	MOVAR	(_u16_release_val_TK1 + 1)
	ADDRA	r0x102E
	MOVAR	_u16_TK1_get_val_Min
	ADDAR	r0x102D
	MOVRA	_u16_temp_val
	MOVAR	r0x102E
	MOVRA	(_u16_temp_val + 1)
	MOVAR	(_u16_TK1_get_val_Min + 1)
	JBCLR	STATUS,0
	JZAR	(_u16_TK1_get_val_Min + 1)
	ADDRA	(_u16_temp_val + 1)
;;shiftRight_Left2ResultLit:5339: shCount=1, size=2, sign=0, same=1, offr=0
;	.line	581; "MC30P8160.c"	u16_temp_val = u16_temp_val >> 1;
	BCLR	STATUS,0
	RRR	(_u16_temp_val + 1)
	RRR	_u16_temp_val
;	.line	583; "MC30P8160.c"	if(u16_get_val > u16_release_val_TK1 || u16_get_val > u16_temp_val)	//松开
	MOVAR	(_u16_get_val + 1)
	RSUBAR	(_u16_release_val_TK1 + 1)
	JBSET	STATUS,2
	GOTO	_00329_DS_
	MOVAR	_u16_get_val
	RSUBAR	_u16_release_val_TK1
_00329_DS_
	JBSET	STATUS,0
	GOTO	_00266_DS_
;;genSkipc:3291: created from rifx:013B5EFC
	MOVAR	(_u16_get_val + 1)
	RSUBAR	(_u16_temp_val + 1)
	JBSET	STATUS,2
	GOTO	_00330_DS_
	MOVAR	_u16_get_val
	RSUBAR	_u16_temp_val
_00330_DS_
	JBCLR	STATUS,0
	GOTO	_00267_DS_
;;genSkipc:3291: created from rifx:013B5EFC
_00266_DS_
;	.line	585; "MC30P8160.c"	FilterCnt_TK1 ++;
	INCR	_FilterCnt_TK1
;;unsigned compare: left < lit(0x4=4), size=1
;	.line	586; "MC30P8160.c"	if(FilterCnt_TK1 >= 4) //触摸松开滤波 20ms
	MOVAI	0x04
	RSUBAR	_FilterCnt_TK1
	JBSET	STATUS,0
	GOTO	_00273_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	588; "MC30P8160.c"	TK1_Release_();    	   	   	   	
	CALL	_TK1_Release_
	GOTO	_00273_DS_
_00267_DS_
;	.line	593; "MC30P8160.c"	FilterCnt_TK1 = 0;
	CLRR	_FilterCnt_TK1
_00273_DS_
;	.line	596; "MC30P8160.c"	}
	RETURN	
; exit point of _TK1_Scan

;***
;  pBlock Stats: dbName = C
;***
;entry:  _TK1_Release_	;Function start
; 2 exit points
;has an exit
;; Starting pCode block
_TK1_Release_	;Function start
; 2 exit points
;	.line	472; "MC30P8160.c"	FilterCnt_TK1 = 0;
	CLRR	_FilterCnt_TK1
;	.line	474; "MC30P8160.c"	T_Key1_Signal = 0;
	BCLR	_flag2,3
;	.line	476; "MC30P8160.c"	Pre_T_Key1_Release = 1;	   	   	   	   	
	BSET	_flag2,4
;	.line	477; "MC30P8160.c"	u16_TK1_environment_val = u16_TK1_get_val_Temp;
	MOVAR	_u16_TK1_get_val_Temp
	MOVRA	_u16_TK1_environment_val
	MOVAR	(_u16_TK1_get_val_Temp + 1)
	MOVRA	(_u16_TK1_environment_val + 1)
;	.line	478; "MC30P8160.c"	TK1_Filter_Cnt = 0;
	CLRR	_TK1_Filter_Cnt
;	.line	479; "MC30P8160.c"	u16_TK1_environment_val_Sum = 0;
	CLRR	_u16_TK1_environment_val_Sum
	CLRR	(_u16_TK1_environment_val_Sum + 1)
;	.line	481; "MC30P8160.c"	TK1_Release_Flag = 1;
	BSET	_flag2,6
;	.line	483; "MC30P8160.c"	u16_TK1_get_val_Min = 0xFFFF;
	MOVAI	0xff
	MOVRA	_u16_TK1_get_val_Min
	MOVRA	(_u16_TK1_get_val_Min + 1)
;	.line	484; "MC30P8160.c"	}
	RETURN	
; exit point of _TK1_Release_

;***
;  pBlock Stats: dbName = C
;***
;entry:  _TK0_Scan	;Function start
; 2 exit points
;has an exit
;functions called:
;   _TK_Init
;   _Get_TK_Value
;   _TK0_Release_
;   _TK_Init
;   _Get_TK_Value
;   _TK0_Release_
;2 compiler assigned registers:
;   r0x102D
;   r0x102E
;; Starting pCode block
_TK0_Scan	;Function start
; 2 exit points
;	.line	358; "MC30P8160.c"	DDR1 |= 0x01;     // 1： 端口作为输入口          0： 端口作为输出口
	BSET	_DDR1,0
;	.line	359; "MC30P8160.c"	P1ADCR |= 0x01;   // 0 使能端口的数字 I/O 功能； 1 关闭端口的数字 I/O 功能；
	BSET	_P1ADCR,0
;	.line	361; "MC30P8160.c"	TKCR1 = 0x00; // 写0000_0000 bit0-1: 00 TK0 选择相应按键输入通道
	CLRR	_TKCR1
;	.line	362; "MC30P8160.c"	TK_Init();
	CALL	_TK_Init
;	.line	364; "MC30P8160.c"	Get_TK_Value();
	CALL	_Get_TK_Value
;	.line	367; "MC30P8160.c"	DDR1 &= 0xFE;     // 1： 端口作为输入口         0： 端口作为输出口
	BCLR	_DDR1,0
;	.line	368; "MC30P8160.c"	P1ADCR &= 0xFE;   // 1 关闭端口的数字 I/O 功能； 0 使能端口的数字 I/O 功能； 
	BCLR	_P1ADCR,0
;	.line	369; "MC30P8160.c"	P10D = 0;
	BCLR	_P1bits,0
;	.line	376; "MC30P8160.c"	u16_TK0_get_val_Temp = u16_get_val;
	MOVAR	_u16_get_val
	MOVRA	_u16_TK0_get_val_Temp
	MOVAR	(_u16_get_val + 1)
	MOVRA	(_u16_TK0_get_val_Temp + 1)
;	.line	383; "MC30P8160.c"	if(Pre_T_Key0_Release) 
	JBSET	_flag1,1
	GOTO	_00176_DS_
;	.line	385; "MC30P8160.c"	u16_temp_val = u16_get_val + Const_SEN_T_Key0;
	MOVAI	0x2d
	ADDAR	_u16_get_val
	MOVRA	_u16_temp_val
	CLRR	(_u16_temp_val + 1)
	RLR	(_u16_temp_val + 1)
	MOVAR	(_u16_get_val + 1)
	ADDRA	(_u16_temp_val + 1)
;	.line	387; "MC30P8160.c"	if(u16_temp_val < u16_TK0_environment_val) 	 //按下
	MOVAR	(_u16_TK0_environment_val + 1)
	RSUBAR	(_u16_temp_val + 1)
	JBSET	STATUS,2
	GOTO	_00228_DS_
	MOVAR	_u16_TK0_environment_val
	RSUBAR	_u16_temp_val
_00228_DS_
	JBCLR	STATUS,0
	GOTO	_00165_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	389; "MC30P8160.c"	SleepCnt = 0xFF;
	MOVAI	0xff
	MOVRA	_SleepCnt
;	.line	390; "MC30P8160.c"	FilterCnt_TK0 ++;
	INCR	_FilterCnt_TK0
;;swapping arguments (AOP_TYPEs 1/3)
;;unsigned compare: left >= lit(0xC=12), size=1
;	.line	391; "MC30P8160.c"	if(FilterCnt_TK0 > FilterCnt_Value)
	MOVAI	0x0c
	RSUBAR	_FilterCnt_TK0
	JBSET	STATUS,0
	GOTO	_00178_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	393; "MC30P8160.c"	T_Key0_Signal = 1;
	BSET	_flag1,0
;	.line	394; "MC30P8160.c"	Pre_T_Key0_Release = 0;
	BCLR	_flag1,1
;	.line	395; "MC30P8160.c"	u16_release_val_TK0 = u16_TK0_environment_val - Const_SEN_T_Key0; //
	MOVAI	0xd3
	ADDAR	_u16_TK0_environment_val
	MOVRA	_u16_release_val_TK0
	MOVAI	0xff
	MOVRA	(_u16_release_val_TK0 + 1)
	MOVAR	(_u16_TK0_environment_val + 1)
	JBCLR	STATUS,0
	JZAR	(_u16_TK0_environment_val + 1)
	ADDRA	(_u16_release_val_TK0 + 1)
	GOTO	_00178_DS_
_00165_DS_
;	.line	400; "MC30P8160.c"	FilterCnt_TK0 = 0;
	CLRR	_FilterCnt_TK0
;	.line	402; "MC30P8160.c"	if(SleepCnt)
	MOVAI	0x00
	ORAR	_SleepCnt
	JBCLR	STATUS,2
	GOTO	_00158_DS_
;	.line	405; "MC30P8160.c"	TK0_Filter_Cnt_T ++;
	INCR	_TK0_Filter_Cnt_T
;;unsigned compare: left < lit(0x4=4), size=1
;	.line	407; "MC30P8160.c"	if(TK0_Filter_Cnt_T >= 4)
	MOVAI	0x04
	RSUBAR	_TK0_Filter_Cnt_T
	JBSET	STATUS,0
	GOTO	_00159_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	409; "MC30P8160.c"	TK0_Filter_Cnt_T = 0;
	CLRR	_TK0_Filter_Cnt_T
;	.line	410; "MC30P8160.c"	u16_TK0_environment_val_Sum += u16_get_val;
	MOVAR	_u16_get_val
	ADDRA	_u16_TK0_environment_val_Sum
	MOVAR	(_u16_get_val + 1)
	JBCLR	STATUS,0
	JZAR	(_u16_get_val + 1)
	ADDRA	(_u16_TK0_environment_val_Sum + 1)
;	.line	412; "MC30P8160.c"	TK0_Filter_Cnt ++;                 	   	   	   	
	INCR	_TK0_Filter_Cnt
;;swapping arguments (AOP_TYPEs 1/3)
;;unsigned compare: left >= lit(0x8=8), size=1
;	.line	413; "MC30P8160.c"	if(TK0_Filter_Cnt > 7)
	MOVAI	0x08
	RSUBAR	_TK0_Filter_Cnt
	JBSET	STATUS,0
	GOTO	_00159_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	415; "MC30P8160.c"	TK0_Filter_Cnt = 0;
	CLRR	_TK0_Filter_Cnt
;;shiftRight_Left2ResultLit:5339: shCount=1, size=2, sign=0, same=0, offr=0
;	.line	416; "MC30P8160.c"	u16_TK0_environment_val = u16_TK0_environment_val_Sum >> 3;
	BCLR	STATUS,0
	RRAR	(_u16_TK0_environment_val_Sum + 1)
	MOVRA	(_u16_TK0_environment_val + 1)
	RRAR	_u16_TK0_environment_val_Sum
	MOVRA	_u16_TK0_environment_val
;;shiftRight_Left2ResultLit:5339: shCount=1, size=2, sign=0, same=1, offr=0
	BCLR	STATUS,0
	RRR	(_u16_TK0_environment_val + 1)
	RRR	_u16_TK0_environment_val
;;shiftRight_Left2ResultLit:5339: shCount=1, size=2, sign=0, same=1, offr=0
	BCLR	STATUS,0
	RRR	(_u16_TK0_environment_val + 1)
	RRR	_u16_TK0_environment_val
;	.line	417; "MC30P8160.c"	u16_TK0_environment_val_Sum = 0;
	CLRR	_u16_TK0_environment_val_Sum
	CLRR	(_u16_TK0_environment_val_Sum + 1)
;	.line	419; "MC30P8160.c"	if(TK0_Release_Flag)
	JBSET	_flag1,2
	GOTO	_00159_DS_
;	.line	421; "MC30P8160.c"	TK0_Release_Flag = 0;
	BCLR	_flag1,2
;	.line	422; "MC30P8160.c"	u16_TK0_environment_val = u16_get_val;
	MOVAR	_u16_get_val
	MOVRA	_u16_TK0_environment_val
	MOVAR	(_u16_get_val + 1)
	MOVRA	(_u16_TK0_environment_val + 1)
	GOTO	_00159_DS_
_00158_DS_
;	.line	429; "MC30P8160.c"	u16_TK0_environment_val = u16_get_val;
	MOVAR	_u16_get_val
	MOVRA	_u16_TK0_environment_val
	MOVAR	(_u16_get_val + 1)
	MOVRA	(_u16_TK0_environment_val + 1)
;	.line	430; "MC30P8160.c"	u16_TK0_environment_val_Sum = 0;
	CLRR	_u16_TK0_environment_val_Sum
	CLRR	(_u16_TK0_environment_val_Sum + 1)
;	.line	431; "MC30P8160.c"	TK0_Filter_Cnt = 0;
	CLRR	_TK0_Filter_Cnt
_00159_DS_
;	.line	434; "MC30P8160.c"	if(TK0_Release_Flag == 1)
	CLRR	r0x102D
	JBCLR	_flag1,2
	INCR	r0x102D
	MOVAR	r0x102D
	XORAI	0x01
	JBSET	STATUS,2
	GOTO	_00178_DS_
;	.line	436; "MC30P8160.c"	if(u16_get_val > u16_TK0_environment_val)
	MOVAR	(_u16_get_val + 1)
	RSUBAR	(_u16_TK0_environment_val + 1)
	JBSET	STATUS,2
	GOTO	_00232_DS_
	MOVAR	_u16_get_val
	RSUBAR	_u16_TK0_environment_val
_00232_DS_
	JBCLR	STATUS,0
	GOTO	_00178_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	438; "MC30P8160.c"	u16_TK0_environment_val = u16_get_val;
	MOVAR	_u16_get_val
	MOVRA	_u16_TK0_environment_val
	MOVAR	(_u16_get_val + 1)
	MOVRA	(_u16_TK0_environment_val + 1)
	GOTO	_00178_DS_
_00176_DS_
;	.line	447; "MC30P8160.c"	if(u16_get_val < u16_TK0_get_val_Min)
	MOVAR	(_u16_TK0_get_val_Min + 1)
	RSUBAR	(_u16_get_val + 1)
	JBSET	STATUS,2
	GOTO	_00233_DS_
	MOVAR	_u16_TK0_get_val_Min
	RSUBAR	_u16_get_val
_00233_DS_
	JBCLR	STATUS,0
	GOTO	_00168_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	449; "MC30P8160.c"	u16_TK0_get_val_Min = u16_get_val;
	MOVAR	_u16_get_val
	MOVRA	_u16_TK0_get_val_Min
	MOVAR	(_u16_get_val + 1)
	MOVRA	(_u16_TK0_get_val_Min + 1)
_00168_DS_
;	.line	452; "MC30P8160.c"	u16_temp_val = u16_release_val_TK0 + Const_SEN_T_Key0 + u16_TK0_get_val_Min;
	MOVAI	0x2d
	ADDAR	_u16_release_val_TK0
	MOVRA	r0x102D
	CLRR	r0x102E
	RLR	r0x102E
	MOVAR	(_u16_release_val_TK0 + 1)
	ADDRA	r0x102E
	MOVAR	_u16_TK0_get_val_Min
	ADDAR	r0x102D
	MOVRA	_u16_temp_val
	MOVAR	r0x102E
	MOVRA	(_u16_temp_val + 1)
	MOVAR	(_u16_TK0_get_val_Min + 1)
	JBCLR	STATUS,0
	JZAR	(_u16_TK0_get_val_Min + 1)
	ADDRA	(_u16_temp_val + 1)
;;shiftRight_Left2ResultLit:5339: shCount=1, size=2, sign=0, same=1, offr=0
;	.line	453; "MC30P8160.c"	u16_temp_val = u16_temp_val >> 1;
	BCLR	STATUS,0
	RRR	(_u16_temp_val + 1)
	RRR	_u16_temp_val
;	.line	455; "MC30P8160.c"	if(u16_get_val > u16_release_val_TK0 || u16_get_val > u16_temp_val)	//松开
	MOVAR	(_u16_get_val + 1)
	RSUBAR	(_u16_release_val_TK0 + 1)
	JBSET	STATUS,2
	GOTO	_00234_DS_
	MOVAR	_u16_get_val
	RSUBAR	_u16_release_val_TK0
_00234_DS_
	JBSET	STATUS,0
	GOTO	_00171_DS_
;;genSkipc:3291: created from rifx:013B5EFC
	MOVAR	(_u16_get_val + 1)
	RSUBAR	(_u16_temp_val + 1)
	JBSET	STATUS,2
	GOTO	_00235_DS_
	MOVAR	_u16_get_val
	RSUBAR	_u16_temp_val
_00235_DS_
	JBCLR	STATUS,0
	GOTO	_00172_DS_
;;genSkipc:3291: created from rifx:013B5EFC
_00171_DS_
;	.line	457; "MC30P8160.c"	FilterCnt_TK0 ++;
	INCR	_FilterCnt_TK0
;;unsigned compare: left < lit(0x4=4), size=1
;	.line	458; "MC30P8160.c"	if(FilterCnt_TK0 >= 4) //触摸松开滤波 20ms
	MOVAI	0x04
	RSUBAR	_FilterCnt_TK0
	JBSET	STATUS,0
	GOTO	_00178_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	460; "MC30P8160.c"	TK0_Release_(); 	
	CALL	_TK0_Release_
	GOTO	_00178_DS_
_00172_DS_
;	.line	465; "MC30P8160.c"	FilterCnt_TK0 = 0;
	CLRR	_FilterCnt_TK0
_00178_DS_
;	.line	468; "MC30P8160.c"	}
	RETURN	
; exit point of _TK0_Scan

;***
;  pBlock Stats: dbName = C
;***
;entry:  _TK0_Release_	;Function start
; 2 exit points
;has an exit
;; Starting pCode block
_TK0_Release_	;Function start
; 2 exit points
;	.line	344; "MC30P8160.c"	FilterCnt_TK0 = 0;
	CLRR	_FilterCnt_TK0
;	.line	345; "MC30P8160.c"	T_Key0_Signal = 0;
	BCLR	_flag1,0
;	.line	346; "MC30P8160.c"	Pre_T_Key0_Release = 1;	   	   	   	   	
	BSET	_flag1,1
;	.line	347; "MC30P8160.c"	u16_TK0_environment_val = u16_TK0_get_val_Temp;;
	MOVAR	_u16_TK0_get_val_Temp
	MOVRA	_u16_TK0_environment_val
	MOVAR	(_u16_TK0_get_val_Temp + 1)
	MOVRA	(_u16_TK0_environment_val + 1)
;	.line	348; "MC30P8160.c"	TK0_Filter_Cnt = 0;
	CLRR	_TK0_Filter_Cnt
;	.line	349; "MC30P8160.c"	u16_TK0_environment_val_Sum = 0;
	CLRR	_u16_TK0_environment_val_Sum
	CLRR	(_u16_TK0_environment_val_Sum + 1)
;	.line	351; "MC30P8160.c"	TK0_Release_Flag = 1;
	BSET	_flag1,2
;	.line	352; "MC30P8160.c"	u16_TK0_get_val_Min = 0xFFFF;
	MOVAI	0xff
	MOVRA	_u16_TK0_get_val_Min
	MOVRA	(_u16_TK0_get_val_Min + 1)
;	.line	353; "MC30P8160.c"	}
	RETURN	
; exit point of _TK0_Release_

;***
;  pBlock Stats: dbName = C
;***
;entry:  _Get_TK_Value	;Function start
; 2 exit points
;has an exit
;4 compiler assigned registers:
;   r0x1029
;   r0x102A
;   r0x102B
;   r0x102C
;; Starting pCode block
_Get_TK_Value	;Function start
; 2 exit points
_00138_DS_
;	.line	330; "MC30P8160.c"	while(TKCF == 1)
	CLRR	r0x1029
	JBCLR	_TKCR1bits,5
	INCR	r0x1029
	MOVAR	r0x1029
	XORAI	0x01
	JBSET	STATUS,2
	GOTO	_00140_DS_
;	.line	332; "MC30P8160.c"	WDT_Clear();
	CLRWDT	
	GOTO	_00138_DS_
_00140_DS_
;	.line	335; "MC30P8160.c"	u16_get_val =  (TKCNTH << 8) | TKCNTL;
	MOVAR	_TKCNTH
	MOVRA	r0x102B
	MOVRA	r0x1029
	CLRR	r0x102A
;;104	MOVAR	r0x1029
;;99	CLRR	r0x102C
	MOVAR	_TKCNTL
	MOVRA	_u16_get_val
	MOVRA	r0x1029
	CLRR	r0x102A
;;103	MOVAR	r0x1029
;;100	ORAR	r0x102C
	MOVAI	0x00
	ORAR	r0x102B
	MOVRA	(_u16_get_val + 1)
;	.line	337; "MC30P8160.c"	TKCON = 0;  // 关闭 TKM 电容充放计数；
	BCLR	_TKCR0bits,6
;	.line	338; "MC30P8160.c"	TKCNTH = 0; // 清TOUCH读数,必须手工清零
	CLRR	_TKCNTH
;	.line	339; "MC30P8160.c"	TKCNTL = 0;
	CLRR	_TKCNTL
;	.line	340; "MC30P8160.c"	}
	RETURN	
; exit point of _Get_TK_Value

;***
;  pBlock Stats: dbName = C
;***
;entry:  _TK_Init	;Function start
; 2 exit points
;has an exit
;; Starting pCode block
_TK_Init	;Function start
; 2 exit points
;	.line	302; "MC30P8160.c"	TKCR1 &= 0x03; // 关闭触摸, 不改变通道选择位 bit 0-1
	MOVAI	0x03
	ANDRA	_TKCR1
;	.line	303; "MC30P8160.c"	TKCNTH = 0;
	CLRR	_TKCNTH
;	.line	304; "MC30P8160.c"	TKCNTL = 0;
	CLRR	_TKCNTL
;	.line	306; "MC30P8160.c"	T2MOD = 1;   // 单次计时模式（触摸模式）
	BSET	_T2CRbits,6
;	.line	308; "MC30P8160.c"	T2CR = 0x4A;   // 01_0_01_010 FOSC 16M 4分频 4M
	MOVAI	0x4a
	MOVRA	_T2CR
;	.line	310; "MC30P8160.c"	T2LOADH = TK_SENS_LEVEL_H1;
	MOVAI	0x0e
	MOVRA	_T2LOADH
;	.line	311; "MC30P8160.c"	T2LOADL = TK_SENS_LEVEL_L;
	MOVAI	0xff
	MOVRA	_T2LOADL
;	.line	316; "MC30P8160.c"	TKCR0 = 0xF4;  // 写1111_0000 bit0-3: 000 TK0 选择 4.8MHz
	MOVAI	0xf4
	MOVRA	_TKCR0
;	.line	319; "MC30P8160.c"	TKCFL = 1; 	 // TKM 计数时钟滤波时间（典型值）为 50ns；
	BSET	_TKCR0bits,5
;	.line	322; "MC30P8160.c"	TKFJE = 0; 	// 关闭 TKM 自动跳频功能
	BCLR	_TKCR0bits,3
;	.line	323; "MC30P8160.c"	T2EN = 1;  	// 开启定时器 T2
	BSET	_T2CRbits,7
;	.line	324; "MC30P8160.c"	TKCON = 1; 	// 允许 TKM 电容充放计数
	BSET	_TKCR0bits,6
;	.line	325; "MC30P8160.c"	TKEN = 1;  	// 开启 TKM      	       	
	BSET	_TKCR0bits,7
;	.line	326; "MC30P8160.c"	}
	RETURN	
; exit point of _TK_Init

;***
;  pBlock Stats: dbName = C
;***
;entry:  _TOUCH_Init	;Function start
; 2 exit points
;has an exit
;; Starting pCode block
_TOUCH_Init	;Function start
; 2 exit points
;	.line	296; "MC30P8160.c"	__endasm;
	BCLR	TMRCR,3
	MOVAI	00000000B
	MOVRA	TKCR0
	MOVAI	11111111B
	MOVRA	TKCR2
	RETURN
;	.line	297; "MC30P8160.c"	}
	RETURN	
; exit point of _TOUCH_Init

;***
;  pBlock Stats: dbName = C
;***
;entry:  _IO_Init	;Function start
; 2 exit points
;has an exit
;; Starting pCode block
_IO_Init	;Function start
; 2 exit points
;	.line	256; "MC30P8160.c"	P1 = 0x00; //  	P1nD – P1n 端口数据位（n=5-0）
	CLRR	_P1
;	.line	259; "MC30P8160.c"	DDR1 = 0x33;   	   // DR1n – P1n 端口方向控制位（n=5-0）  0： 端口作为输出口
	MOVAI	0x33
	MOVRA	_DDR1
;	.line	263; "MC30P8160.c"	P1ADCR = 0x33;   // 0 使能端口的数字 I/O 功能； 1 关闭端口的数字 I/O 功能；
	MOVAI	0x33
	MOVRA	_P1ADCR
;	.line	266; "MC30P8160.c"	PUCON = 0xFF; //  1：端口内部上拉电阻无效；  0：端口内部上拉电阻有效
	MOVAI	0xff
	MOVRA	_PUCON
;	.line	267; "MC30P8160.c"	PDCON = 0xFF; //  1：端口内部下拉电阻无效；  0：端口内部下拉电阻有效
	MOVAI	0xff
	MOVRA	_PDCON
;	.line	269; "MC30P8160.c"	ODCON = 0x00; // 0： 端口输出时为推挽输出   1 开漏输出
	CLRR	_ODCON
;	.line	272; "MC30P8160.c"	}
	RETURN	
; exit point of _IO_Init

;***
;  pBlock Stats: dbName = C
;***
;entry:  _T1_PWM_Init	;Function start
; 2 exit points
;has an exit
;; Starting pCode block
_T1_PWM_Init	;Function start
; 2 exit points
;	.line	248; "MC30P8160.c"	T1CR = 0x89;    // 100_01_001 使能T1、时钟为FOSC、2分频
	MOVAI	0x89
	MOVRA	_T1CR
;	.line	249; "MC30P8160.c"	T1CNT = 255-1;
	MOVAI	0xfe
	MOVRA	_T1CNT
;	.line	250; "MC30P8160.c"	T1LOAD = 255-1;    	   	//31k
	MOVAI	0xfe
	MOVRA	_T1LOAD
;	.line	251; "MC30P8160.c"	}
	RETURN	
; exit point of _T1_PWM_Init

;***
;  pBlock Stats: dbName = C
;***
;entry:  _Clr_Ram	;Function start
; 2 exit points
;has an exit
;; Starting pCode block
_Clr_Ram	;Function start
; 2 exit points
;	.line	242; "MC30P8160.c"	__endasm;
CLR_RAM:
	MOVAI	0X4F
	MOVRA	FSR
	MOVAI	0X3F
	MOVRA	0X4F ;
CLR_RAM_LOOP:
	DECR	FSR
	CLRR	INDF
	DJZR	0X4F
	GOTO	CLR_RAM_LOOP
	RETURN
	
;	.line	243; "MC30P8160.c"	}   
	RETURN	
; exit point of _Clr_Ram

;***
;  pBlock Stats: dbName = C
;***
;entry:  _Init_Sys	;Function start
; 2 exit points
;has an exit
;; Starting pCode block
_Init_Sys	;Function start
; 2 exit points
;	.line	222; "MC30P8160.c"	__endasm;
SET_OPTION:
	MOVAI	00000111B
	MOVRA	T0CR
	MOVAI	217
	CLRR	T0CNT
	MOVAI	00000001B
	MOVRA	INTE
	BSET	INTE,7
	MOVAI	0x00
	MOVRA	INTF
	MOVAI	0x00
	MOVRA	P1KBCR
	RETURN
	
;	.line	223; "MC30P8160.c"	} 
	RETURN	
; exit point of _Init_Sys

;***
;  pBlock Stats: dbName = C
;***
;entry:  _Delay_us_2	;Function start
; 2 exit points
;has an exit
;1 compiler assigned register :
;   r0x1029
;; Starting pCode block
_Delay_us_2	;Function start
; 2 exit points
;	.line	119; "MC30P8160.c"	void Delay_us_2(uint8_t i)
	MOVRA	r0x1029
_00107_DS_
;	.line	121; "MC30P8160.c"	for(; i>0; i--)
	MOVAI	0x00
	ORAR	r0x1029
	JBCLR	STATUS,2
	GOTO	_00109_DS_
;	.line	123; "MC30P8160.c"	WDT_Clear();
	CLRWDT	
;	.line	124; "MC30P8160.c"	Nop();
	nop	
;	.line	125; "MC30P8160.c"	Nop();
	nop	
;	.line	126; "MC30P8160.c"	Nop();
	nop	
;	.line	127; "MC30P8160.c"	Nop();
	nop	
;	.line	121; "MC30P8160.c"	for(; i>0; i--)
	DECR	r0x1029
	GOTO	_00107_DS_
_00109_DS_
;	.line	129; "MC30P8160.c"	}
	RETURN	
; exit point of _Delay_us_2


;	code size estimation:
;	  716+    0 =   716 instructions ( 1432 byte)

	end
