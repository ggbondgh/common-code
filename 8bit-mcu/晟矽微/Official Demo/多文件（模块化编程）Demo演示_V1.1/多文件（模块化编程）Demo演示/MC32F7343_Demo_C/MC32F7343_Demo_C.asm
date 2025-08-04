;--------------------------------------------------------
; File Created by SN-SDCC : SinoMCU ANSI-C Compiler
; Version 2.0.0 (Dec 11 2019) (MINGW32)
; This file was generated Thu Nov 07 09:08:18 2024
;--------------------------------------------------------
; MC32 port for the RISC core
;--------------------------------------------------------
;	.file	"MC32F7343_Demo_C.c"
	list	p=7333
	radix dec
	include "7333.inc"
;--------------------------------------------------------
; external declarations
;--------------------------------------------------------
	extern	_Init_I2C
	extern	_I2C_Start
	extern	_I2C_Stop
	extern	_I2C_Byte_Write
	extern	_I2C_Byte_Read
	extern	_Write_Process
	extern	_Read_Process
	extern	_UART_Config
	extern	_SendData
	extern	_SendString
	extern	_Uart_Send_Data
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
	extern	_INTE0bits
	extern	_INTF0bits
	extern	_OSCMRbits
	extern	_INTE1bits
	extern	_INTF1bits
	extern	_P1KBCRbits
	extern	_IOP0bits
	extern	_OEP0bits
	extern	_PUP0bits
	extern	_PDP0bits
	extern	_IOP1bits
	extern	_OEP1bits
	extern	_PUP1bits
	extern	_PDP1bits
	extern	_IOP2bits
	extern	_OEP2bits
	extern	_PUP2bits
	extern	_PDP2bits
	extern	_T0CRbits
	extern	_T0CNTbits
	extern	_T0LOADbits
	extern	_T0DATAbits
	extern	_T1CRbits
	extern	_T1CNTHbits
	extern	_T1CNTLbits
	extern	_T1LOADHbits
	extern	_T1LOADLbits
	extern	_T1DATAHbits
	extern	_T1DATALbits
	extern	_IICCRbits
	extern	_IICSRbits
	extern	_IICDRbits
	extern	_EECRbits
	extern	_EEPRbits
	extern	_EEARbits
	extern	_EEDRbits
	extern	_ADCR0bits
	extern	_ADCR1bits
	extern	_ADRHbits
	extern	_ADRLbits
	extern	_ADIOS0bits
	extern	_ADIOS1bits
	extern	_OSADJCRbits
	extern	_T2CRbits
	extern	_T2CNTHbits
	extern	_T2CNTLbits
	extern	_T2LOADHbits
	extern	_T2LOADLbits
	extern	_T3CRbits
	extern	_T3CNTbits
	extern	_T3LOADbits
	extern	_SCONbits
	extern	_SBUFbits
	extern	_SADDRbits
	extern	_SADENbits
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
	extern	_INTE0
	extern	_INTF0
	extern	_OSCMR
	extern	_INTE1
	extern	_INTF1
	extern	_P1KBCR
	extern	_IOP0
	extern	_OEP0
	extern	_PUP0
	extern	_PDP0
	extern	_IOP1
	extern	_OEP1
	extern	_PUP1
	extern	_PDP1
	extern	_IOP2
	extern	_OEP2
	extern	_PUP2
	extern	_PDP2
	extern	_T0CR
	extern	_T0CNT
	extern	_T0LOAD
	extern	_T0DATA
	extern	_T1CR
	extern	_T1CNTH
	extern	_T1CNTL
	extern	_T1LOADH
	extern	_T1LOADL
	extern	_T1DATAH
	extern	_T1DATAL
	extern	_IICCR
	extern	_IICSR
	extern	_IICDR
	extern	_EECR
	extern	_EEPR
	extern	_EEAR
	extern	_EEDR
	extern	_ADCR0
	extern	_ADCR1
	extern	_ADRH
	extern	_ADRL
	extern	_ADIOS0
	extern	_ADIOS1
	extern	_OSADJCR
	extern	_T2CR
	extern	_T2CNTH
	extern	_T2CNTL
	extern	_T2LOADH
	extern	_T2LOADL
	extern	_T3CR
	extern	_T3CNT
	extern	_T3LOAD
	extern	_SCON
	extern	_SBUF
	extern	_SADDR
	extern	_SADEN
;--------------------------------------------------------
; global declarations
;--------------------------------------------------------
	global	_InitSys
	global	_Timer_Config
	global	_EEPROM_Read_Byte
	global	_EEPROM_Write_Byte
	global	_ADC_Get_Value_Average
	global	_Get_ADC_Value
	global	_ADC_Config
	global	_IO_ADC_Config
	global	_IO_Config
	global	_ADC_Repeat_ADJ
	global	_ADC_Init_ADJ
	global	_C_RAM
	global	_main
	global	_int_isr
	global	_ABuf
	global	_StatusBuf
	global	_Flag1
	global	_Flag2
	global	_UART_Buff
	global	_UART_Test
	global	_ADH_temp
	global	_ADL_temp
	global	_Data_OSADJCR
	global	_ADC_CH0_Value
	global	_ADC_Value
	global	_EEPROM_Num
	global	_Timer0_Num

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
UD_MC32F7343_Demo_C_0	udata
_ABuf	res	1

UD_MC32F7343_Demo_C_1	udata
_StatusBuf	res	1

UD_MC32F7343_Demo_C_2	udata
_Flag1	res	1

UD_MC32F7343_Demo_C_3	udata
_Flag2	res	1

UD_MC32F7343_Demo_C_4	udata
_UART_Buff	res	1

UD_MC32F7343_Demo_C_5	udata
_UART_Test	res	1

UD_MC32F7343_Demo_C_6	udata
_ADC_CH0_Value	res	2

UD_MC32F7343_Demo_C_7	udata
_ADC_Value	res	2

UD_MC32F7343_Demo_C_8	udata
_EEPROM_Num	res	1

UD_MC32F7343_Demo_C_9	udata
_Timer0_Num	res	2

;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
;--------------------------------------------------------
; compiler-defined variables
;--------------------------------------------------------
UDL_MC32F7343_Demo_C_0	udata
r0x102B	res	1
r0x102A	res	1
r0x102C	res	1
r0x100E	res	1
r0x100F	res	1
r0x1010	res	1
r0x1011	res	1
r0x1012	res	1
r0x1013	res	1
r0x1026	res	1
r0x1027	res	1
r0x1029	res	1
r0x1028	res	1
r0x1017	res	1
r0x1018	res	1
r0x1019	res	1
r0x101A	res	1
r0x101B	res	1
r0x101C	res	1
r0x101D	res	1
r0x101E	res	1
r0x101F	res	1
r0x1020	res	1
r0x1021	res	1
r0x1023	res	1
r0x1022	res	1
r0x1024	res	1
r0x1015	res	1
r0x1016	res	1
r0x1014	res	1
r0x102D	res	1
;--------------------------------------------------------
; initialized data
;--------------------------------------------------------

ID_MC32F7343_Demo_C_0	idata
_ADH_temp
	db	0x00, 0x00


ID_MC32F7343_Demo_C_1	idata
_ADL_temp
	db	0x00, 0x00


ID_MC32F7343_Demo_C_2	idata
_Data_OSADJCR
	db	0x00, 0x00


ID_MC32F7343_Demo_C_3	code
___str_0
	dw 0x53 ; 'S'
	dw 0x69 ; 'i'
	dw 0x6e ; 'n'
	dw 0x6f ; 'o'
	dw 0x6d ; 'm'
	dw 0x63 ; 'c'
	dw 0x75 ; 'u'
	dw 0x5f ; '_'
	dw 0x54 ; 'T'
	dw 0x65 ; 'e'
	dw 0x73 ; 's'
	dw 0x74 ; 't'
	dw 0x5f ; '_'
	dw 0x63 ; 'c'
	dw 0x6f ; 'o'
	dw 0x64 ; 'd'
	dw 0x65 ; 'e'
	dw 0x0d ; '.'
	dw 0x0a ; '.'
	dw 0x00 ; '.'

;@Allocation info for local variables in function 'main'
;@main C_RAM                     Allocated to registers ;size:2
;@main ADC_Init_ADJ              Allocated to registers ;size:2
;@main ADC_Repeat_ADJ            Allocated to registers ;size:2
;@main IO_Config                 Allocated to registers ;size:2
;@main IO_ADC_Config             Allocated to registers ;size:2
;@main ADC_Config                Allocated to registers ;size:2
;@main Get_ADC_Value             Allocated to registers ;size:2
;@main ADC_Get_Value_Average     Allocated to registers ;size:2
;@main EEPROM_Write_Byte         Allocated to registers ;size:2
;@main EEPROM_Read_Byte          Allocated to registers ;size:2
;@main Timer_Config              Allocated to registers ;size:2
;@main InitSys                   Allocated to registers ;size:2
;@main Init_I2C                  Allocated to registers ;size:2
;@main I2C_Start                 Allocated to registers ;size:2
;@main I2C_Stop                  Allocated to registers ;size:2
;@main I2C_Byte_Write            Allocated to registers ;size:2
;@main I2C_Byte_Read             Allocated to registers ;size:2
;@main Write_Process             Allocated to registers ;size:2
;@main Read_Process              Allocated to registers ;size:2
;@main UART_Config               Allocated to registers ;size:2
;@main SendData                  Allocated to registers ;size:2
;@main SendString                Allocated to registers ;size:2
;@main Uart_Send_Data            Allocated to registers ;size:2
;@main main                      Allocated to registers ;size:2
;@main INDF0bits                 Allocated to registers ;size:1
;@main INDF1bits                 Allocated to registers ;size:1
;@main INDF2bits                 Allocated to registers ;size:1
;@main HIBYTEbits                Allocated to registers ;size:1
;@main FSR0bits                  Allocated to registers ;size:1
;@main FSR1bits                  Allocated to registers ;size:1
;@main PCLbits                   Allocated to registers ;size:1
;@main PFLAGbits                 Allocated to registers ;size:1
;@main MCRbits                   Allocated to registers ;size:1
;@main INDF3bits                 Allocated to registers ;size:1
;@main INTE0bits                 Allocated to registers ;size:1
;@main INTF0bits                 Allocated to registers ;size:1
;@main OSCMRbits                 Allocated to registers ;size:1
;@main INTE1bits                 Allocated to registers ;size:1
;@main INTF1bits                 Allocated to registers ;size:1
;@main P1KBCRbits                Allocated to registers ;size:1
;@main IOP0bits                  Allocated to registers ;size:1
;@main OEP0bits                  Allocated to registers ;size:1
;@main PUP0bits                  Allocated to registers ;size:1
;@main PDP0bits                  Allocated to registers ;size:1
;@main IOP1bits                  Allocated to registers ;size:1
;@main OEP1bits                  Allocated to registers ;size:1
;@main PUP1bits                  Allocated to registers ;size:1
;@main PDP1bits                  Allocated to registers ;size:1
;@main IOP2bits                  Allocated to registers ;size:1
;@main OEP2bits                  Allocated to registers ;size:1
;@main PUP2bits                  Allocated to registers ;size:1
;@main PDP2bits                  Allocated to registers ;size:1
;@main T0CRbits                  Allocated to registers ;size:1
;@main T0CNTbits                 Allocated to registers ;size:1
;@main T0LOADbits                Allocated to registers ;size:1
;@main T0DATAbits                Allocated to registers ;size:1
;@main T1CRbits                  Allocated to registers ;size:1
;@main T1CNTHbits                Allocated to registers ;size:1
;@main T1CNTLbits                Allocated to registers ;size:1
;@main T1LOADHbits               Allocated to registers ;size:1
;@main T1LOADLbits               Allocated to registers ;size:1
;@main T1DATAHbits               Allocated to registers ;size:1
;@main T1DATALbits               Allocated to registers ;size:1
;@main IICCRbits                 Allocated to registers ;size:1
;@main IICSRbits                 Allocated to registers ;size:1
;@main IICDRbits                 Allocated to registers ;size:1
;@main EECRbits                  Allocated to registers ;size:1
;@main EEPRbits                  Allocated to registers ;size:1
;@main EEARbits                  Allocated to registers ;size:1
;@main EEDRbits                  Allocated to registers ;size:1
;@main ADCR0bits                 Allocated to registers ;size:1
;@main ADCR1bits                 Allocated to registers ;size:1
;@main ADRHbits                  Allocated to registers ;size:1
;@main ADRLbits                  Allocated to registers ;size:1
;@main ADIOS0bits                Allocated to registers ;size:1
;@main ADIOS1bits                Allocated to registers ;size:1
;@main OSADJCRbits               Allocated to registers ;size:1
;@main T2CRbits                  Allocated to registers ;size:1
;@main T2CNTHbits                Allocated to registers ;size:1
;@main T2CNTLbits                Allocated to registers ;size:1
;@main T2LOADHbits               Allocated to registers ;size:1
;@main T2LOADLbits               Allocated to registers ;size:1
;@main T3CRbits                  Allocated to registers ;size:1
;@main T3CNTbits                 Allocated to registers ;size:1
;@main T3LOADbits                Allocated to registers ;size:1
;@main SCONbits                  Allocated to registers ;size:1
;@main SBUFbits                  Allocated to registers ;size:1
;@main SADDRbits                 Allocated to registers ;size:1
;@main SADENbits                 Allocated to registers ;size:1
;@main ABuf                      Allocated to registers ;size:1
;@main StatusBuf                 Allocated to registers ;size:1
;@main Flag1                     Allocated to registers ;size:1
;@main Flag2                     Allocated to registers ;size:1
;@main UART_Buff                 Allocated to registers ;size:1
;@main UART_Test                 Allocated to registers ;size:1
;@main ADH_temp                  Allocated to registers ;size:2
;@main ADL_temp                  Allocated to registers ;size:2
;@main Data_OSADJCR              Allocated to registers ;size:2
;@main ADC_CH0_Value             Allocated to registers ;size:2
;@main ADC_Value                 Allocated to registers ;size:2
;@main EEPROM_Num                Allocated to registers ;size:1
;@main Timer0_Num                Allocated to registers ;size:2
;@main INDF0                     Allocated to registers ;size:1
;@main INDF1                     Allocated to registers ;size:1
;@main INDF2                     Allocated to registers ;size:1
;@main HIBYTE                    Allocated to registers ;size:1
;@main FSR0                      Allocated to registers ;size:1
;@main FSR1                      Allocated to registers ;size:1
;@main PCL                       Allocated to registers ;size:1
;@main PFLAG                     Allocated to registers ;size:1
;@main MCR                       Allocated to registers ;size:1
;@main INDF3                     Allocated to registers ;size:1
;@main INTE0                     Allocated to registers ;size:1
;@main INTF0                     Allocated to registers ;size:1
;@main OSCMR                     Allocated to registers ;size:1
;@main INTE1                     Allocated to registers ;size:1
;@main INTF1                     Allocated to registers ;size:1
;@main P1KBCR                    Allocated to registers ;size:1
;@main IOP0                      Allocated to registers ;size:1
;@main OEP0                      Allocated to registers ;size:1
;@main PUP0                      Allocated to registers ;size:1
;@main PDP0                      Allocated to registers ;size:1
;@main IOP1                      Allocated to registers ;size:1
;@main OEP1                      Allocated to registers ;size:1
;@main PUP1                      Allocated to registers ;size:1
;@main PDP1                      Allocated to registers ;size:1
;@main IOP2                      Allocated to registers ;size:1
;@main OEP2                      Allocated to registers ;size:1
;@main PUP2                      Allocated to registers ;size:1
;@main PDP2                      Allocated to registers ;size:1
;@main T0CR                      Allocated to registers ;size:1
;@main T0CNT                     Allocated to registers ;size:1
;@main T0LOAD                    Allocated to registers ;size:1
;@main T0DATA                    Allocated to registers ;size:1
;@main T1CR                      Allocated to registers ;size:1
;@main T1CNTH                    Allocated to registers ;size:1
;@main T1CNTL                    Allocated to registers ;size:1
;@main T1LOADH                   Allocated to registers ;size:1
;@main T1LOADL                   Allocated to registers ;size:1
;@main T1DATAH                   Allocated to registers ;size:1
;@main T1DATAL                   Allocated to registers ;size:1
;@main IICCR                     Allocated to registers ;size:1
;@main IICSR                     Allocated to registers ;size:1
;@main IICDR                     Allocated to registers ;size:1
;@main EECR                      Allocated to registers ;size:1
;@main EEPR                      Allocated to registers ;size:1
;@main EEAR                      Allocated to registers ;size:1
;@main EEDR                      Allocated to registers ;size:1
;@main ADCR0                     Allocated to registers ;size:1
;@main ADCR1                     Allocated to registers ;size:1
;@main ADRH                      Allocated to registers ;size:1
;@main ADRL                      Allocated to registers ;size:1
;@main ADIOS0                    Allocated to registers ;size:1
;@main ADIOS1                    Allocated to registers ;size:1
;@main OSADJCR                   Allocated to registers ;size:1
;@main T2CR                      Allocated to registers ;size:1
;@main T2CNTH                    Allocated to registers ;size:1
;@main T2CNTL                    Allocated to registers ;size:1
;@main T2LOADH                   Allocated to registers ;size:1
;@main T2LOADL                   Allocated to registers ;size:1
;@main T3CR                      Allocated to registers ;size:1
;@main T3CNT                     Allocated to registers ;size:1
;@main T3LOAD                    Allocated to registers ;size:1
;@main SCON                      Allocated to registers ;size:1
;@main SBUF                      Allocated to registers ;size:1
;@main SADDR                     Allocated to registers ;size:1
;@main SADEN                     Allocated to registers ;size:1
;@end Allocation info for local variables in function 'main';
;@Allocation info for local variables in function 'C_RAM'
;@end Allocation info for local variables in function 'C_RAM';
;@Allocation info for local variables in function 'ADC_Init_ADJ'
;@end Allocation info for local variables in function 'ADC_Init_ADJ';
;@Allocation info for local variables in function 'ADC_Repeat_ADJ'
;@ADC_Repeat_ADJ i                         Allocated to registers r0x1013 ;size:1
;@ADC_Repeat_ADJ j                         Allocated to registers r0x1010 ;size:1
;@ADC_Repeat_ADJ R_Zero                    Allocated to registers r0x100F ;size:1
;@ADC_Repeat_ADJ R_Zero_max                Allocated to registers r0x100E ;size:1
;@end Allocation info for local variables in function 'ADC_Repeat_ADJ';
;@Allocation info for local variables in function 'IO_Config'
;@end Allocation info for local variables in function 'IO_Config';
;@Allocation info for local variables in function 'IO_ADC_Config'
;@IO_ADC_Config CHX                       Allocated to registers r0x100E ;size:1
;@IO_ADC_Config CHX_Temp                  Allocated to registers r0x100E ;size:1
;@end Allocation info for local variables in function 'IO_ADC_Config';
;@Allocation info for local variables in function 'ADC_Config'
;@ADC_Config ADC_VRS                   Allocated to registers r0x1010 ;size:1
;@ADC_Config ADC_Ampling_Time          Allocated to registers r0x100F ;size:1
;@ADC_Config ADC_CLK                   Allocated to registers r0x100E ;size:1
;@end Allocation info for local variables in function 'ADC_Config';
;@Allocation info for local variables in function 'Get_ADC_Value'
;@Get_ADC_Value CHX                       Allocated to registers r0x1026 r0x1025 ;size:2
;@end Allocation info for local variables in function 'Get_ADC_Value';
;@Allocation info for local variables in function 'ADC_Get_Value_Average'
;@ADC_Get_Value_Average CHX                       Allocated to registers r0x1017 ;size:1
;@ADC_Get_Value_Average channel                   Allocated to registers r0x1017 ;size:1
;@ADC_Get_Value_Average tmpBuff                   Allocated to registers r0x101C r0x101D r0x1022 r0x1024 ;size:4
;@ADC_Get_Value_Average AdcMAX                    Allocated to registers r0x101C r0x101D ;size:2
;@ADC_Get_Value_Average AdcMIN                    Allocated to registers r0x101E r0x101F ;size:2
;@end Allocation info for local variables in function 'ADC_Get_Value_Average';
;@Allocation info for local variables in function 'EEPROM_Write_Byte'
;@EEPROM_Write_Byte Data                      Allocated to registers r0x1016 ;size:1
;@EEPROM_Write_Byte Addr                      Allocated to registers r0x1015 ;size:1
;@end Allocation info for local variables in function 'EEPROM_Write_Byte';
;@Allocation info for local variables in function 'EEPROM_Read_Byte'
;@EEPROM_Read_Byte Addr                      Allocated to registers r0x1014 ;size:1
;@EEPROM_Read_Byte Temp                      Allocated to registers r0x1014 ;size:1
;@end Allocation info for local variables in function 'EEPROM_Read_Byte';
;@Allocation info for local variables in function 'Timer_Config'
;@end Allocation info for local variables in function 'Timer_Config';
;@Allocation info for local variables in function 'InitSys'
;@end Allocation info for local variables in function 'InitSys';
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
;   r0x102D
;   r0x102E
;; Starting pCode block
_int_isr	;Function start
; 0 exit points
;	.line	384; "MC32F7343_Demo_C.c"	__endasm;
	movra	_ABuf
	swapar	_PFLAG
	movra	_StatusBuf
;	.line	385; "MC32F7343_Demo_C.c"	if((T0IF)&&(T0IE))
	JBSET	_INTF0bits,0
	GOTO	_00288_DS_
	JBSET	_INTE0bits,0
	GOTO	_00288_DS_
;	.line	387; "MC32F7343_Demo_C.c"	T0IF=0;
	BCLR	_INTF0bits,0
;	.line	388; "MC32F7343_Demo_C.c"	P16D=!P16D;
	CLRR	r0x102D
	JBCLR	_IOP1bits,6
	INCR	r0x102D
	MOVAR	r0x102D
	MOVAI	0x00
	JBCLR	PFLAG,2
	MOVAI	0x01
	MOVRA	r0x102D
;;1	MOVRA	r0x102E
;;99	MOVAR	r0x102E
	RRAR	r0x102D
	JBSET	PFLAG,0
	BCLR	_IOP1bits,6
	JBCLR	PFLAG,0
	BSET	_IOP1bits,6
;	.line	389; "MC32F7343_Demo_C.c"	Timer0_Num++;
	INCR	_Timer0_Num
	JBCLR	PFLAG,2
	INCR	(_Timer0_Num + 1)
;;unsigned compare: left < lit(0x64=100), size=2
;	.line	390; "MC32F7343_Demo_C.c"	if(Timer0_Num>=100)
	MOVAI	0x00
	RSUBAR	(_Timer0_Num + 1)
	JBSET	PFLAG,2
	GOTO	_00333_DS_
	MOVAI	0x64
	RSUBAR	_Timer0_Num
_00333_DS_
	JBSET	PFLAG,0
	GOTO	_00288_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	392; "MC32F7343_Demo_C.c"	Timer0_Num=0;
	CLRR	_Timer0_Num
	CLRR	(_Timer0_Num + 1)
;	.line	393; "MC32F7343_Demo_C.c"	Fre_Mode_Flag=1;
	BSET	_Flag2,0
_00288_DS_
;	.line	396; "MC32F7343_Demo_C.c"	if((T1IF)&&(T1IE))
	JBSET	_INTF0bits,1
	GOTO	_00291_DS_
	JBSET	_INTE0bits,1
	GOTO	_00291_DS_
;	.line	398; "MC32F7343_Demo_C.c"	T1IF  = 0; 	
	BCLR	_INTF0bits,1
_00291_DS_
;	.line	400; "MC32F7343_Demo_C.c"	if (RI)
	JBSET	_SCONbits,0
	GOTO	_00294_DS_
;	.line	402; "MC32F7343_Demo_C.c"	RI=0;
	BCLR	_SCONbits,0
;	.line	403; "MC32F7343_Demo_C.c"	UART_Buff=SBUF;
	MOVAR	_SBUF
	MOVRA	_UART_Buff
;	.line	404; "MC32F7343_Demo_C.c"	UART_Flag=1;
	BSET	_Flag1,1
_00294_DS_
;	.line	411; "MC32F7343_Demo_C.c"	if(UARTIF)
	JBSET	_INTF0bits,7
	GOTO	_00296_DS_
;	.line	413; "MC32F7343_Demo_C.c"	UARTIF  = 0;
	BCLR	_INTF0bits,7
;	.line	414; "MC32F7343_Demo_C.c"	TI=0;//发送中断标志位清零
	BCLR	_SCONbits,1
;	.line	415; "MC32F7343_Demo_C.c"	UART_Busy=0;
	BCLR	_Flag1,0
_00296_DS_
;	.line	417; "MC32F7343_Demo_C.c"	if(IICIF)
	JBSET	_INTF0bits,5
	GOTO	_00298_DS_
;	.line	419; "MC32F7343_Demo_C.c"	IICIF  = 0;
	BCLR	_INTF0bits,5
;	.line	420; "MC32F7343_Demo_C.c"	TI=0;//发送中断标志位清零
	BCLR	_SCONbits,1
;	.line	421; "MC32F7343_Demo_C.c"	F_I2C_done=1;
	BSET	_Flag1,2
_00298_DS_
;	.line	429; "MC32F7343_Demo_C.c"	__endasm;
	swapar	_StatusBuf
	movra	_PFLAG
	swapr	_ABuf
	swapar	_ABuf
END_OF_INTERRUPT
;	.line	430; "MC32F7343_Demo_C.c"	}
	RETIE	

;--------------------------------------------------------
; code
;--------------------------------------------------------
code_MC32F7343_Demo_C	code
;***
;  pBlock Stats: dbName = M
;***
;entry:  _main	;Function start
; 2 exit points
;has an exit
;functions called:
;   _InitSys
;   _EEPROM_Write_Byte
;   _EEPROM_Read_Byte
;   _SendString
;   _InitSys
;   _EEPROM_Write_Byte
;   _EEPROM_Read_Byte
;   _SendString
;5 compiler assigned registers:
;   STK00
;   r0x102A
;   r0x102B
;   r0x102C
;   STK01
;; Starting pCode block
_main	;Function start
; 2 exit points
;	.line	40; "MC32F7343_Demo_C.c"	InitSys();
	CALL	_InitSys
;	.line	41; "MC32F7343_Demo_C.c"	EEPROM_Num=0x55;
	MOVAI	0x55
	MOVRA	_EEPROM_Num
;	.line	42; "MC32F7343_Demo_C.c"	EEPROM_Write_Byte(0x01,EEPROM_Num);
	MOVAI	0x55
	MOVRA	STK00
	MOVAI	0x01
	CALL	_EEPROM_Write_Byte
;	.line	43; "MC32F7343_Demo_C.c"	EEPROM_Num=0;
	CLRR	_EEPROM_Num
;	.line	44; "MC32F7343_Demo_C.c"	EEPROM_Num=EEPROM_Read_Byte(0x01);
	MOVAI	0x01
	CALL	_EEPROM_Read_Byte
	MOVRA	_EEPROM_Num
_00108_DS_
;	.line	47; "MC32F7343_Demo_C.c"	if(Fre_Mode_Flag)
	JBSET	_Flag2,0
	GOTO	_00108_DS_
;	.line	49; "MC32F7343_Demo_C.c"	Fre_Mode_Flag=0;
	BCLR	_Flag2,0
;	.line	50; "MC32F7343_Demo_C.c"	SendString("Sinomcu_Test_code\r\n");
	MOVAI	high (___str_0 + 0)
	MOVRA	r0x102A
	MOVAI	(___str_0 + 0)
	MOVRA	r0x102B
	MOVAI	0x80
	MOVRA	r0x102C
	MOVAR	r0x102B
	MOVRA	STK01
	MOVAR	r0x102A
	MOVRA	STK00
	MOVAR	r0x102C
	CALL	_SendString
	GOTO	_00108_DS_
;	.line	54; "MC32F7343_Demo_C.c"	}
	RETURN	
; exit point of _main

;***
;  pBlock Stats: dbName = C
;***
;entry:  _InitSys	;Function start
; 2 exit points
;has an exit
;functions called:
;   _C_RAM
;   _IO_Config
;   _UART_Config
;   _ADC_Init_ADJ
;   _ADC_Repeat_ADJ
;   _Timer_Config
;   _IO_ADC_Config
;   _ADC_Config
;   _Init_I2C
;   _C_RAM
;   _IO_Config
;   _UART_Config
;   _ADC_Init_ADJ
;   _ADC_Repeat_ADJ
;   _Timer_Config
;   _IO_ADC_Config
;   _ADC_Config
;   _Init_I2C
;2 compiler assigned registers:
;   STK01
;   STK00
;; Starting pCode block
_InitSys	;Function start
; 2 exit points
;	.line	365; "MC32F7343_Demo_C.c"	GIE = 0;
	BCLR	_MCRbits,7
;	.line	366; "MC32F7343_Demo_C.c"	C_RAM();
	CALL	_C_RAM
;	.line	367; "MC32F7343_Demo_C.c"	IO_Config();
	CALL	_IO_Config
;	.line	368; "MC32F7343_Demo_C.c"	UART_Config();
	CALL	_UART_Config
;	.line	369; "MC32F7343_Demo_C.c"	ADC_Init_ADJ();
	CALL	_ADC_Init_ADJ
;	.line	370; "MC32F7343_Demo_C.c"	ADC_Repeat_ADJ();
	CALL	_ADC_Repeat_ADJ
;	.line	371; "MC32F7343_Demo_C.c"	Timer_Config();
	CALL	_Timer_Config
;	.line	372; "MC32F7343_Demo_C.c"	IO_ADC_Config(0);  	   	   	   	//ADC_CH0 P21配置模拟
	MOVAI	0x00
	CALL	_IO_ADC_Config
;	.line	373; "MC32F7343_Demo_C.c"	ADC_Config(0,3,0);     	   	   	//F/8 15ADCLK  in 2V
	MOVAI	0x00
	MOVRA	STK01
	MOVAI	0x03
	MOVRA	STK00
	MOVAI	0x00
	CALL	_ADC_Config
;	.line	374; "MC32F7343_Demo_C.c"	Init_I2C();
	CALL	_Init_I2C
;	.line	375; "MC32F7343_Demo_C.c"	GIE  = 1;        
	BSET	_MCRbits,7
;	.line	376; "MC32F7343_Demo_C.c"	}
	RETURN	
; exit point of _InitSys

;***
;  pBlock Stats: dbName = C
;***
;entry:  _Timer_Config	;Function start
; 2 exit points
;has an exit
;; Starting pCode block
_Timer_Config	;Function start
; 2 exit points
;	.line	342; "MC32F7343_Demo_C.c"	T0CR&=0x60;
	MOVAI	0x60
	ANDRA	_T0CR
;	.line	343; "MC32F7343_Demo_C.c"	T0CR|=0x85;	   	//Fcpu  32分频
	MOVAI	0x85
	ORRA	_T0CR
;	.line	344; "MC32F7343_Demo_C.c"	T0CNT=124;
	MOVAI	0x7c
	MOVRA	_T0CNT
;	.line	345; "MC32F7343_Demo_C.c"	T0LOAD=124;
	MOVAI	0x7c
	MOVRA	_T0LOAD
;	.line	346; "MC32F7343_Demo_C.c"	T0IE=1; 
	BSET	_INTE0bits,0
;	.line	356; "MC32F7343_Demo_C.c"	}
	RETURN	
; exit point of _Timer_Config

;***
;  pBlock Stats: dbName = C
;***
;entry:  _EEPROM_Read_Byte	;Function start
; 2 exit points
;has an exit
;1 compiler assigned register :
;   r0x1014
;; Starting pCode block
_EEPROM_Read_Byte	;Function start
; 2 exit points
;	.line	319; "MC32F7343_Demo_C.c"	u8 EEPROM_Read_Byte(u8 Addr)
	MOVRA	r0x1014
;	.line	322; "MC32F7343_Demo_C.c"	EECR=0;	   	//清除EETRIG
	CLRR	_EECR
;	.line	323; "MC32F7343_Demo_C.c"	EEAR=Addr;
	MOVAR	r0x1014
	MOVRA	_EEAR
;	.line	324; "MC32F7343_Demo_C.c"	GIE=0;
	BCLR	_MCRbits,7
;	.line	325; "MC32F7343_Demo_C.c"	EEDR=0x5A;
	MOVAI	0x5a
	MOVRA	_EEDR
;	.line	326; "MC32F7343_Demo_C.c"	EEDR=0xA5;   	   	//解除保护
	MOVAI	0xa5
	MOVRA	_EEDR
;	.line	327; "MC32F7343_Demo_C.c"	EECR=0x80; 	   	   	//启动EEPROM读写  读数据操作
	MOVAI	0x80
	MOVRA	_EECR
;	.line	328; "MC32F7343_Demo_C.c"	Nop();
	nop	
;	.line	329; "MC32F7343_Demo_C.c"	GIE=1;
	BSET	_MCRbits,7
;	.line	330; "MC32F7343_Demo_C.c"	Temp=EEDR;
	MOVAR	_EEDR
	MOVRA	r0x1014
;	.line	331; "MC32F7343_Demo_C.c"	return Temp;
	MOVAR	r0x1014
;	.line	332; "MC32F7343_Demo_C.c"	}
	RETURN	
; exit point of _EEPROM_Read_Byte

;***
;  pBlock Stats: dbName = C
;***
;entry:  _EEPROM_Write_Byte	;Function start
; 2 exit points
;has an exit
;3 compiler assigned registers:
;   r0x1015
;   STK00
;   r0x1016
;; Starting pCode block
_EEPROM_Write_Byte	;Function start
; 2 exit points
;	.line	300; "MC32F7343_Demo_C.c"	void EEPROM_Write_Byte(u8 Addr,u8 Data)
	MOVRA	r0x1015
	MOVAR	STK00
	MOVRA	r0x1016
;	.line	302; "MC32F7343_Demo_C.c"	EECR=0;	   	//清除EETRIG
	CLRR	_EECR
;	.line	303; "MC32F7343_Demo_C.c"	EEAR=Addr;
	MOVAR	r0x1015
	MOVRA	_EEAR
;	.line	304; "MC32F7343_Demo_C.c"	EEDR=Data;
	MOVAR	r0x1016
	MOVRA	_EEDR
;	.line	305; "MC32F7343_Demo_C.c"	GIE=0;
	BCLR	_MCRbits,7
;	.line	306; "MC32F7343_Demo_C.c"	ClrWdt();  	   	//清看门狗
	clrwdt	
;	.line	307; "MC32F7343_Demo_C.c"	EEDR=0x5A;
	MOVAI	0x5a
	MOVRA	_EEDR
;	.line	308; "MC32F7343_Demo_C.c"	EEDR=0xA5;   	   	//解除保护
	MOVAI	0xa5
	MOVRA	_EEDR
;	.line	309; "MC32F7343_Demo_C.c"	EECR=0xC0; 	   	   	//启动EEPROM读写  写数据操作
	MOVAI	0xc0
	MOVRA	_EECR
;	.line	310; "MC32F7343_Demo_C.c"	Nop();
	nop	
;	.line	311; "MC32F7343_Demo_C.c"	GIE=1;
	BSET	_MCRbits,7
;	.line	312; "MC32F7343_Demo_C.c"	}
	RETURN	
; exit point of _EEPROM_Write_Byte

;***
;  pBlock Stats: dbName = C
;***
;entry:  _ADC_Get_Value_Average	;Function start
; 2 exit points
;has an exit
;15 compiler assigned registers:
;   r0x1017
;   r0x1018
;   r0x1019
;   r0x101A
;   r0x101B
;   r0x101C
;   r0x101D
;   r0x101E
;   r0x101F
;   r0x1020
;   r0x1021
;   r0x1022
;   r0x1023
;   r0x1024
;   STK00
;; Starting pCode block
_ADC_Get_Value_Average	;Function start
; 2 exit points
	MOVRA	r0x1020
;	.line	267; "MC32F7343_Demo_C.c"	uint ADC_Get_Value_Average(uchar CHX)
	MOVRA	r0x1017
;	.line	270; "MC32F7343_Demo_C.c"	unsigned long int tmpBuff = 0;
	CLRR	r0x1018
	CLRR	r0x1019
	CLRR	r0x101A
	CLRR	r0x101B
;	.line	271; "MC32F7343_Demo_C.c"	u16 AdcMAX = 0;
	CLRR	r0x101C
	CLRR	r0x101D
;	.line	272; "MC32F7343_Demo_C.c"	u16 AdcMIN = 0xffff;
	MOVAI	0xff
	MOVRA	r0x101E
	MOVRA	r0x101F
;	.line	274; "MC32F7343_Demo_C.c"	ADCR0&=0x0F;
	MOVAI	0x0f
	ANDRA	_ADCR0
;;120	MOVAR	r0x1017
;	.line	275; "MC32F7343_Demo_C.c"	ADCR0|=CHX<<4;
	SWAPAR	r0x1020
	ANDAI	0xf0
	MOVRA	r0x1017
;;119	MOVAR	r0x1017
;;118	MOVAR	r0x1020
	MOVAR	r0x1017
	MOVRA	r0x1020
	ORRA	_ADCR0
;	.line	276; "MC32F7343_Demo_C.c"	for (channel = 0; channel < 20; channel++)
	CLRR	r0x1017
_00223_DS_
;	.line	278; "MC32F7343_Demo_C.c"	ADEOC=0;   	   	//使能转换
	BCLR	_ADCR0bits,1
_00212_DS_
;	.line	279; "MC32F7343_Demo_C.c"	while(!ADEOC); 	   	   	//等待转换完成
	JBSET	_ADCR0bits,1
	GOTO	_00212_DS_
;	.line	280; "MC32F7343_Demo_C.c"	ADC_Value=(ADRH<<8)+ADRL;
	MOVAR	_ADRH
	MOVRA	r0x1022
	MOVRA	r0x1020
	CLRR	r0x1021
;;113	MOVAR	r0x1020
	CLRR	r0x1023
	MOVAR	_ADRL
	MOVRA	r0x1020
	CLRR	r0x1021
	MOVAR	r0x1020
	ADDAR	r0x1023
	MOVRA	_ADC_Value
	MOVAR	r0x1022
	MOVRA	(_ADC_Value + 1)
	MOVAI	0x00
	JBCLR	PFLAG,0
	JZAR	r0x1021
	ADDRA	(_ADC_Value + 1)
;;unsigned compare: left < lit(0x2=2), size=1
;	.line	281; "MC32F7343_Demo_C.c"	if (channel < 2)
	MOVAI	0x02
	RSUBAR	r0x1017
	JBSET	PFLAG,0
	GOTO	_00221_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	283; "MC32F7343_Demo_C.c"	if (ADC_Value > AdcMAX)
	MOVAR	(_ADC_Value + 1)
	RSUBAR	r0x101D
	JBSET	PFLAG,2
	GOTO	_00263_DS_
	MOVAR	_ADC_Value
	RSUBAR	r0x101C
_00263_DS_
	JBCLR	PFLAG,0
	GOTO	_00218_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	284; "MC32F7343_Demo_C.c"	AdcMAX = ADC_Value; //最大
	MOVAR	_ADC_Value
	MOVRA	r0x101C
	MOVAR	(_ADC_Value + 1)
	MOVRA	r0x101D
_00218_DS_
;	.line	285; "MC32F7343_Demo_C.c"	if (ADC_Value < AdcMIN)
	MOVAR	r0x101F
	RSUBAR	(_ADC_Value + 1)
	JBSET	PFLAG,2
	GOTO	_00264_DS_
	MOVAR	r0x101E
	RSUBAR	_ADC_Value
_00264_DS_
	JBCLR	PFLAG,0
	GOTO	_00220_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	286; "MC32F7343_Demo_C.c"	AdcMIN = ADC_Value; //最小
	MOVAR	_ADC_Value
	MOVRA	r0x101E
	MOVAR	(_ADC_Value + 1)
	MOVRA	r0x101F
_00220_DS_
;	.line	287; "MC32F7343_Demo_C.c"	tmpBuff += ADC_Value;
	MOVAR	_ADC_Value
	MOVRA	r0x1020
	MOVAR	(_ADC_Value + 1)
	MOVRA	r0x1021
	CLRR	r0x1023
	CLRR	r0x1022
	MOVAR	r0x1020
	ADDRA	r0x1018
	MOVAR	r0x1021
	JBCLR	PFLAG,0
	JZAR	r0x1021
	ADDRA	r0x1019
	MOVAR	r0x1023
	JBCLR	PFLAG,0
	JZAR	r0x1023
	ADDRA	r0x101A
	MOVAR	r0x1022
	JBCLR	PFLAG,0
	JZAR	r0x1022
	ADDRA	r0x101B
_00221_DS_
;	.line	276; "MC32F7343_Demo_C.c"	for (channel = 0; channel < 20; channel++)
	INCR	r0x1017
;;unsigned compare: left < lit(0x14=20), size=1
	MOVAI	0x14
	RSUBAR	r0x1017
	JBSET	PFLAG,0
	GOTO	_00223_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;;117	MOVAR	r0x101C
;	.line	289; "MC32F7343_Demo_C.c"	tmpBuff -= AdcMAX; 	   	   	//去掉一个最大
	MOVAR	r0x101D
	MOVRA	r0x1020
	CLRR	r0x1021
	CLRR	r0x1023
;;116	MOVAR	r0x1017
	MOVAR	r0x101C
	MOVRA	r0x1017
	RSUBAR	r0x1018
	MOVRA	r0x101C
	MOVAR	r0x1019
	MOVRA	r0x101D
	MOVAR	r0x1020
	JBSET	PFLAG,0
	JZAR	r0x1020
	RSUBRA	r0x101D
	MOVAR	r0x101A
	MOVRA	r0x1022
	MOVAR	r0x1021
	JBSET	PFLAG,0
	JZAR	r0x1021
	RSUBRA	r0x1022
	MOVAR	r0x1023
	JBSET	PFLAG,0
	INCAR	r0x1023
	RSUBAR	r0x101B
	MOVRA	r0x1024
;;110	MOVAR	r0x101E
;;112	MOVAR	r0x101F
;	.line	290; "MC32F7343_Demo_C.c"	tmpBuff -= AdcMIN; 	   	   	//去掉一个最小
	CLRR	r0x1019
	CLRR	r0x101A
;;109	MOVAR	r0x1017
	MOVAR	r0x101E
	MOVRA	r0x1017
	RSUBRA	r0x101C
;;111	MOVAR	r0x1018
	MOVAR	r0x101F
	MOVRA	r0x1018
	JBSET	PFLAG,0
	JZAR	r0x1018
	RSUBRA	r0x101D
	MOVAR	r0x1019
	JBSET	PFLAG,0
	JZAR	r0x1019
	RSUBRA	r0x1022
	MOVAR	r0x101A
	JBSET	PFLAG,0
	JZAR	r0x101A
	RSUBRA	r0x1024
;	.line	291; "MC32F7343_Demo_C.c"	ADC_Value = (tmpBuff >> 4); //除以16，取平均值
	SWAPAR	r0x101C
	ANDAI	0x0f
	MOVRA	r0x1017
	SWAPAR	r0x101D
	MOVRA	r0x1018
	ANDAI	0xf0
	ORRA	r0x1017
	XORRA	r0x1018
	SWAPAR	r0x1022
	MOVRA	r0x1019
	ANDAI	0xf0
	ORRA	r0x1018
	XORRA	r0x1019
	SWAPAR	r0x1024
	MOVRA	r0x101A
	ANDAI	0xf0
	ORRA	r0x1019
	XORRA	r0x101A
	MOVAR	r0x1017
	MOVRA	_ADC_Value
	MOVAR	r0x1018
	MOVRA	(_ADC_Value + 1)
;	.line	292; "MC32F7343_Demo_C.c"	return ADC_Value;
	MOVAR	_ADC_Value
	MOVRA	STK00
	MOVAR	(_ADC_Value + 1)
;	.line	293; "MC32F7343_Demo_C.c"	}
	RETURN	
; exit point of _ADC_Get_Value_Average

;***
;  pBlock Stats: dbName = C
;***
;entry:  _Get_ADC_Value	;Function start
; 2 exit points
;has an exit
;6 compiler assigned registers:
;   r0x1025
;   STK00
;   r0x1026
;   r0x1027
;   r0x1028
;   r0x1029
;; Starting pCode block
_Get_ADC_Value	;Function start
; 2 exit points
;;1	MOVRA	r0x1025
;	.line	252; "MC32F7343_Demo_C.c"	u16 Get_ADC_Value(u16 CHX)
	MOVAR	STK00
	MOVRA	r0x1027
	MOVRA	r0x1026
;	.line	254; "MC32F7343_Demo_C.c"	ADCR0&=0x0F;
	MOVAI	0x0f
	ANDRA	_ADCR0
;;115	MOVAR	r0x1026
;	.line	255; "MC32F7343_Demo_C.c"	ADCR0|=CHX<<4;
	MOVAR	r0x1027
	MOVRA	r0x1026
	SWAPAR	r0x1026
	ANDAI	0xf0
	MOVRA	r0x1026
	MOVRA	r0x1027
;;108	MOVAR	r0x1027
	MOVAR	r0x1026
	ORRA	_ADCR0
;	.line	256; "MC32F7343_Demo_C.c"	ADEOC=0;   	   	//使能转换
	BCLR	_ADCR0bits,1
_00207_DS_
;	.line	257; "MC32F7343_Demo_C.c"	while(!ADEOC); 	   	   	//等待转换完成
	JBSET	_ADCR0bits,1
	GOTO	_00207_DS_
;	.line	258; "MC32F7343_Demo_C.c"	ADC_Value=(ADRH<<8)+ADRL;
	MOVAR	_ADRH
	MOVRA	r0x1028
	MOVRA	r0x1026
	CLRR	r0x1027
;;107	MOVAR	r0x1026
	CLRR	r0x1029
	MOVAR	_ADRL
	MOVRA	r0x1026
	CLRR	r0x1027
	MOVAR	r0x1026
	ADDAR	r0x1029
	MOVRA	_ADC_Value
	MOVAR	r0x1028
	MOVRA	(_ADC_Value + 1)
	MOVAI	0x00
	JBCLR	PFLAG,0
	JZAR	r0x1027
	ADDRA	(_ADC_Value + 1)
;	.line	259; "MC32F7343_Demo_C.c"	return ADC_Value;
	MOVAR	_ADC_Value
	MOVRA	STK00
	MOVAR	(_ADC_Value + 1)
;	.line	260; "MC32F7343_Demo_C.c"	}
	RETURN	
; exit point of _Get_ADC_Value

;***
;  pBlock Stats: dbName = C
;***
;entry:  _ADC_Config	;Function start
; 2 exit points
;has an exit
;6 compiler assigned registers:
;   r0x100E
;   STK00
;   r0x100F
;   STK01
;   r0x1010
;   r0x1011
;; Starting pCode block
_ADC_Config	;Function start
; 2 exit points
	MOVRA	r0x1011
;	.line	234; "MC32F7343_Demo_C.c"	void ADC_Config(u8 ADC_CLK,u8 ADC_Ampling_Time,u8 ADC_VRS)
	MOVRA	r0x100E
	MOVAR	STK00
	MOVRA	r0x100F
	MOVAR	STK01
	MOVRA	r0x1010
;	.line	236; "MC32F7343_Demo_C.c"	ADCR1&=0xCC;
	MOVAI	0xcc
	ANDRA	_ADCR1
;;114	MOVAR	r0x100E
;	.line	237; "MC32F7343_Demo_C.c"	ADCR1|=ADC_CLK<<4;
	SWAPAR	r0x1011
	ANDAI	0xf0
	MOVRA	r0x100E
;;106	MOVAR	r0x100E
;;105	MOVAR	r0x1011
	MOVAR	r0x100E
	MOVRA	r0x1011
	ORRA	_ADCR1
;	.line	238; "MC32F7343_Demo_C.c"	ADCR1|=ADC_Ampling_Time;
	MOVAR	r0x100F
	ORRA	_ADCR1
;	.line	239; "MC32F7343_Demo_C.c"	ADCR0&=0xF3;
	MOVAI	0xf3
	ANDRA	_ADCR0
;	.line	240; "MC32F7343_Demo_C.c"	ADCR0|=ADC_VRS<<2;
	MOVAR	r0x1010
	MOVRA	r0x100E
	BCLR	PFLAG,0
	RLAR	r0x100E
	MOVRA	r0x1010
	BCLR	PFLAG,0
	RLR	r0x1010
;;104	MOVAR	r0x1010
;;103	MOVAR	r0x100E
	MOVAR	r0x1010
	MOVRA	r0x100E
	ORRA	_ADCR0
;	.line	241; "MC32F7343_Demo_C.c"	ADRSEL=1;  	   	   	//高4位存入ADRH[3:0]、低8位存入ADRL[7:0]
	BSET	_ADCR1bits,7
;	.line	242; "MC32F7343_Demo_C.c"	OSADJCR=0x00;//关闭修调
	CLRR	_OSADJCR
;	.line	243; "MC32F7343_Demo_C.c"	ADEN=1;   //使能ADC  
	BSET	_ADCR0bits,0
;	.line	245; "MC32F7343_Demo_C.c"	}
	RETURN	
; exit point of _ADC_Config

;***
;  pBlock Stats: dbName = C
;***
;entry:  _IO_ADC_Config	;Function start
; 2 exit points
;has an exit
;2 compiler assigned registers:
;   r0x100E
;   r0x100F
;; Starting pCode block
_IO_ADC_Config	;Function start
; 2 exit points
;	.line	211; "MC32F7343_Demo_C.c"	void IO_ADC_Config(u8 CHX)
	MOVRA	r0x100E
;;unsigned compare: left < lit(0x8=8), size=1
;	.line	215; "MC32F7343_Demo_C.c"	if(CHX<8)
	MOVAI	0x08
	RSUBAR	r0x100E
	JBCLR	PFLAG,0
	GOTO	_00182_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;;102	MOVAR	r0x100E
;	.line	217; "MC32F7343_Demo_C.c"	ADIOS0=1<<CHX_Temp;	   	
	MOVAI	0x01
	MOVRA	_ADIOS0
;;101	MOVAR	r0x100F
	MOVAR	r0x100E
	MOVRA	r0x100F
	JBCLR	r0x100F,7
	GOTO	_00193_DS_
	ISUBAI	0x00
	JBCLR	PFLAG,2
	GOTO	_00192_DS_
_00191_DS_
	RLR	_ADIOS0
	ADDAI	0x01
	JBSET	PFLAG,0
	GOTO	_00191_DS_
	GOTO	_00192_DS_
_00193_DS_
	BCLR	PFLAG,0
_00194_DS_
	RRR	_ADIOS0
	ADDAI	0x01
	JBSET	PFLAG,0
	GOTO	_00194_DS_
_00192_DS_
	GOTO	_00184_DS_
_00182_DS_
;	.line	220; "MC32F7343_Demo_C.c"	CHX_Temp=CHX_Temp-8;
	MOVAR	r0x100E
	MOVRA	r0x100F
	MOVAI	0xf8
	ADDAR	r0x100F
	MOVRA	r0x100F
	MOVRA	r0x100E
;;100	MOVAR	r0x100E
;	.line	221; "MC32F7343_Demo_C.c"	ADIOS1=1<<CHX_Temp;	
	MOVAI	0x01
	MOVRA	_ADIOS1
	MOVAR	r0x100F
	JBCLR	r0x100F,7
	GOTO	_00197_DS_
	ISUBAI	0x00
	JBCLR	PFLAG,2
	GOTO	_00184_DS_
_00195_DS_
	RLR	_ADIOS1
	ADDAI	0x01
	JBSET	PFLAG,0
	GOTO	_00195_DS_
	GOTO	_00184_DS_
_00197_DS_
	BCLR	PFLAG,0
_00198_DS_
	RRR	_ADIOS1
	ADDAI	0x01
	JBSET	PFLAG,0
	GOTO	_00198_DS_
_00184_DS_
;	.line	223; "MC32F7343_Demo_C.c"	}
	RETURN	
; exit point of _IO_ADC_Config

;***
;  pBlock Stats: dbName = C
;***
;entry:  _IO_Config	;Function start
; 2 exit points
;has an exit
;; Starting pCode block
_IO_Config	;Function start
; 2 exit points
;	.line	186; "MC32F7343_Demo_C.c"	IOP0=0;
	CLRR	_IOP0
;	.line	187; "MC32F7343_Demo_C.c"	IOP1=0;
	CLRR	_IOP1
;	.line	188; "MC32F7343_Demo_C.c"	IOP2=0;
	CLRR	_IOP2
;	.line	190; "MC32F7343_Demo_C.c"	OEP0=0xff; 	   	//P0  out
	MOVAI	0xff
	MOVRA	_OEP0
;	.line	191; "MC32F7343_Demo_C.c"	OEP1=0xff; 	   	//P1 out
	MOVAI	0xff
	MOVRA	_OEP1
;	.line	192; "MC32F7343_Demo_C.c"	OEP2=0xfC; 	   	//P21 P20 in
	MOVAI	0xfc
	MOVRA	_OEP2
;	.line	194; "MC32F7343_Demo_C.c"	ADIOS0=0;
	CLRR	_ADIOS0
;	.line	195; "MC32F7343_Demo_C.c"	ADIOS1=0;
	CLRR	_ADIOS1
;	.line	197; "MC32F7343_Demo_C.c"	PUP0=0;
	CLRR	_PUP0
;	.line	198; "MC32F7343_Demo_C.c"	PUP1=0; 
	CLRR	_PUP1
;	.line	199; "MC32F7343_Demo_C.c"	PUP2=0x01; 	   	   	//P20  up
	MOVAI	0x01
	MOVRA	_PUP2
;	.line	201; "MC32F7343_Demo_C.c"	PDP0=0;
	CLRR	_PDP0
;	.line	202; "MC32F7343_Demo_C.c"	PDP1=0;
	CLRR	_PDP1
;	.line	203; "MC32F7343_Demo_C.c"	PDP2=0;
	CLRR	_PDP2
;	.line	204; "MC32F7343_Demo_C.c"	}
	RETURN	
; exit point of _IO_Config

;***
;  pBlock Stats: dbName = C
;***
;entry:  _ADC_Repeat_ADJ	;Function start
; 2 exit points
;has an exit
;6 compiler assigned registers:
;   r0x100E
;   r0x100F
;   r0x1010
;   r0x1011
;   r0x1012
;   r0x1013
;; Starting pCode block
_ADC_Repeat_ADJ	;Function start
; 2 exit points
;	.line	147; "MC32F7343_Demo_C.c"	R_Zero_max=0;
	CLRR	r0x100E
;	.line	148; "MC32F7343_Demo_C.c"	R_Zero=0;
	CLRR	r0x100F
;	.line	149; "MC32F7343_Demo_C.c"	Data_OSADJCR=OSADJCR&0x3f;
	MOVAR	_OSADJCR
	MOVRA	r0x1010
	CLRR	r0x1011
	MOVAI	0x3f
	ANDAR	r0x1010
	MOVRA	_Data_OSADJCR
	CLRR	(_Data_OSADJCR + 1)
;	.line	150; "MC32F7343_Demo_C.c"	OSADJCR--;
	DECR	_OSADJCR
;	.line	152; "MC32F7343_Demo_C.c"	for(j=0;j<3;j++)
	CLRR	r0x1010
_00172_DS_
;	.line	154; "MC32F7343_Demo_C.c"	for(i=0;i<6;i++)
	CLRR	r0x1011
	MOVAR	r0x100F
	MOVRA	r0x1012
_00170_DS_
;	.line	156; "MC32F7343_Demo_C.c"	ADEOC=0;     
	BCLR	_ADCR0bits,1
_00160_DS_
;	.line	157; "MC32F7343_Demo_C.c"	while(!ADEOC);
	JBSET	_ADCR0bits,1
	GOTO	_00160_DS_
;	.line	158; "MC32F7343_Demo_C.c"	ADH_temp=ADRH;
	MOVAR	_ADRH
	MOVRA	_ADH_temp
	CLRR	(_ADH_temp + 1)
;	.line	159; "MC32F7343_Demo_C.c"	ADL_temp=ADRL;
	MOVAR	_ADRL
	MOVRA	_ADL_temp
	CLRR	(_ADL_temp + 1)
;	.line	160; "MC32F7343_Demo_C.c"	i++;
	INCAR	r0x1011
	MOVRA	r0x1013
;	.line	161; "MC32F7343_Demo_C.c"	if((ADH_temp==0)&&(ADL_temp==0))
	MOVAR	_ADH_temp
	ORAR	(_ADH_temp + 1)
	JBSET	PFLAG,2
	GOTO	_00171_DS_
	MOVAR	_ADL_temp
	ORAR	(_ADL_temp + 1)
	JBSET	PFLAG,2
	GOTO	_00171_DS_
;	.line	163; "MC32F7343_Demo_C.c"	R_Zero++;
	INCR	r0x1012
_00171_DS_
;	.line	154; "MC32F7343_Demo_C.c"	for(i=0;i<6;i++)
	INCAR	r0x1013
	MOVRA	r0x1011
;;unsigned compare: left < lit(0x6=6), size=1
	MOVAI	0x06
	RSUBAR	r0x1011
	JBSET	PFLAG,0
	GOTO	_00170_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	167; "MC32F7343_Demo_C.c"	if(R_Zero>R_Zero_max)
	MOVAR	r0x1012
	RSUBAR	r0x100E
	JBCLR	PFLAG,0
	GOTO	_00168_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	169; "MC32F7343_Demo_C.c"	R_Zero_max=R_Zero;
	MOVAR	r0x1012
	MOVRA	r0x100E
;	.line	170; "MC32F7343_Demo_C.c"	Data_OSADJCR=OSADJCR&0x3f;
	MOVAR	_OSADJCR
	MOVRA	r0x1011
	CLRR	r0x1012
	MOVAI	0x3f
	ANDAR	r0x1011
	MOVRA	_Data_OSADJCR
	CLRR	(_Data_OSADJCR + 1)
_00168_DS_
;	.line	172; "MC32F7343_Demo_C.c"	OSADJCR++;
	INCR	_OSADJCR
;	.line	173; "MC32F7343_Demo_C.c"	R_Zero=0;
	CLRR	r0x100F
;	.line	152; "MC32F7343_Demo_C.c"	for(j=0;j<3;j++)
	INCR	r0x1010
;;unsigned compare: left < lit(0x3=3), size=1
	MOVAI	0x03
	RSUBAR	r0x1010
	JBSET	PFLAG,0
	GOTO	_00172_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	175; "MC32F7343_Demo_C.c"	OSADJCR=Data_OSADJCR&0x3f;
	MOVAR	_Data_OSADJCR
	MOVRA	r0x100E
	MOVAI	0x3f
	ANDAR	r0x100E
	MOVRA	_OSADJCR
;	.line	177; "MC32F7343_Demo_C.c"	}
	RETURN	
; exit point of _ADC_Repeat_ADJ

;***
;  pBlock Stats: dbName = C
;***
;entry:  _ADC_Init_ADJ	;Function start
; 2 exit points
;has an exit
;2 compiler assigned registers:
;   r0x100E
;   r0x100F
;; Starting pCode block
_ADC_Init_ADJ	;Function start
; 2 exit points
;	.line	84; "MC32F7343_Demo_C.c"	ADCR0=0xe0;//2V参考电压 通道GND
	MOVAI	0xe0
	MOVRA	_ADCR0
;	.line	85; "MC32F7343_Demo_C.c"	OSADJEN=1;//使能 ADC 零点偏移修调模式
	BSET	_OSADJCRbits,7
;	.line	86; "MC32F7343_Demo_C.c"	ADCR1=0x33;//FHIRC/64,15个ADCLK
	MOVAI	0x33
	MOVRA	_ADCR1
;	.line	87; "MC32F7343_Demo_C.c"	OSADJCR&=0xc0;//修调值从零开始
	MOVAI	0xc0
	ANDRA	_OSADJCR
;	.line	89; "MC32F7343_Demo_C.c"	ADEN=1;
	BSET	_ADCR0bits,0
;	.line	90; "MC32F7343_Demo_C.c"	ADEOC=0;
	BCLR	_ADCR0bits,1
_00124_DS_
;	.line	91; "MC32F7343_Demo_C.c"	while(!ADEOC);
	JBSET	_ADCR0bits,1
	GOTO	_00124_DS_
;	.line	93; "MC32F7343_Demo_C.c"	ADH_temp=ADRH;
	MOVAR	_ADRH
	MOVRA	_ADH_temp
	CLRR	(_ADH_temp + 1)
;	.line	94; "MC32F7343_Demo_C.c"	ADL_temp=ADRL;
	MOVAR	_ADRL
	MOVRA	_ADL_temp
	CLRR	(_ADL_temp + 1)
;	.line	96; "MC32F7343_Demo_C.c"	if((ADH_temp==0)&&(ADL_temp==0))
	MOVAR	_ADH_temp
	ORAR	(_ADH_temp + 1)
	JBSET	PFLAG,2
	GOTO	_00152_DS_
	MOVAR	_ADL_temp
	ORAR	(_ADL_temp + 1)
	JBSET	PFLAG,2
	GOTO	_00152_DS_
;	.line	98; "MC32F7343_Demo_C.c"	OSADJCR|=0x3f;
	MOVAI	0x3f
	ORRA	_OSADJCR
;	.line	99; "MC32F7343_Demo_C.c"	Data_OSADJCR=OSADJCR&0x1f;
	MOVAR	_OSADJCR
	MOVRA	r0x100E
	CLRR	r0x100F
	MOVAI	0x1f
	ANDAR	r0x100E
	MOVRA	_Data_OSADJCR
	CLRR	(_Data_OSADJCR + 1)
_00137_DS_
;	.line	102; "MC32F7343_Demo_C.c"	if(Data_OSADJCR==0x00) return;
	MOVAR	_Data_OSADJCR
	ORAR	(_Data_OSADJCR + 1)
	JBSET	PFLAG,2
	GOTO	_00134_DS_
	GOTO	_00155_DS_
_00134_DS_
;	.line	105; "MC32F7343_Demo_C.c"	ADEOC=0;
	BCLR	_ADCR0bits,1
_00127_DS_
;	.line	106; "MC32F7343_Demo_C.c"	while(!ADEOC);
	JBSET	_ADCR0bits,1
	GOTO	_00127_DS_
;	.line	107; "MC32F7343_Demo_C.c"	ADH_temp=ADRH;
	MOVAR	_ADRH
	MOVRA	_ADH_temp
	CLRR	(_ADH_temp + 1)
;	.line	108; "MC32F7343_Demo_C.c"	ADL_temp=ADRL;
	MOVAR	_ADRL
	MOVRA	_ADL_temp
	CLRR	(_ADL_temp + 1)
;	.line	109; "MC32F7343_Demo_C.c"	if((ADH_temp==0)&&(ADL_temp==0)) return;
	MOVAR	_ADH_temp
	ORAR	(_ADH_temp + 1)
	JBSET	PFLAG,2
	GOTO	_00135_DS_
	MOVAR	_ADL_temp
	ORAR	(_ADL_temp + 1)
	JBSET	PFLAG,2
	GOTO	_00135_DS_
	GOTO	_00155_DS_
_00135_DS_
;	.line	112; "MC32F7343_Demo_C.c"	OSADJCR--;
	DECR	_OSADJCR
;	.line	113; "MC32F7343_Demo_C.c"	Data_OSADJCR=OSADJCR&0x1f;
	MOVAR	_OSADJCR
	MOVRA	r0x100E
	CLRR	r0x100F
	MOVAI	0x1f
	ANDAR	r0x100E
	MOVRA	_Data_OSADJCR
	CLRR	(_Data_OSADJCR + 1)
	GOTO	_00137_DS_
_00152_DS_
;	.line	118; "MC32F7343_Demo_C.c"	Data_OSADJCR=OSADJCR&0x1f;
	MOVAR	_OSADJCR
	MOVRA	r0x100E
	CLRR	r0x100F
	MOVAI	0x1f
	ANDAR	r0x100E
	MOVRA	_Data_OSADJCR
	CLRR	(_Data_OSADJCR + 1)
_00149_DS_
;	.line	121; "MC32F7343_Demo_C.c"	if(Data_OSADJCR==0x1f) return;
	MOVAR	_Data_OSADJCR
	XORAI	0x1f
	JBSET	PFLAG,2
	GOTO	_00146_DS_
	MOVAR	(_Data_OSADJCR + 1)
	XORAI	0x00
	JBSET	PFLAG,2
	GOTO	_00146_DS_
	GOTO	_00155_DS_
_00146_DS_
;	.line	124; "MC32F7343_Demo_C.c"	ADEOC=0;
	BCLR	_ADCR0bits,1
_00139_DS_
;	.line	125; "MC32F7343_Demo_C.c"	while(!ADEOC);
	JBSET	_ADCR0bits,1
	GOTO	_00139_DS_
;	.line	127; "MC32F7343_Demo_C.c"	ADH_temp=ADRH;
	MOVAR	_ADRH
	MOVRA	_ADH_temp
	CLRR	(_ADH_temp + 1)
;	.line	128; "MC32F7343_Demo_C.c"	ADL_temp=ADRL;
	MOVAR	_ADRL
	MOVRA	_ADL_temp
	CLRR	(_ADL_temp + 1)
;	.line	129; "MC32F7343_Demo_C.c"	if((ADH_temp==0)&&(ADL_temp==0)) return;
	MOVAR	_ADH_temp
	ORAR	(_ADH_temp + 1)
	JBSET	PFLAG,2
	GOTO	_00147_DS_
	MOVAR	_ADL_temp
	ORAR	(_ADL_temp + 1)
	JBSET	PFLAG,2
	GOTO	_00147_DS_
	GOTO	_00155_DS_
_00147_DS_
;	.line	133; "MC32F7343_Demo_C.c"	OSADJCR++;
	INCR	_OSADJCR
;	.line	134; "MC32F7343_Demo_C.c"	Data_OSADJCR=OSADJCR&0x1f;
	MOVAR	_OSADJCR
	MOVRA	r0x100E
	CLRR	r0x100F
	MOVAI	0x1f
	ANDAR	r0x100E
	MOVRA	_Data_OSADJCR
	CLRR	(_Data_OSADJCR + 1)
	GOTO	_00149_DS_
_00155_DS_
;	.line	137; "MC32F7343_Demo_C.c"	}
	RETURN	
; exit point of _ADC_Init_ADJ

;***
;  pBlock Stats: dbName = C
;***
;entry:  _C_RAM	;Function start
; 2 exit points
;has an exit
;; Starting pCode block
_C_RAM	;Function start
; 2 exit points
;	.line	63; "MC32F7343_Demo_C.c"	for(FSR0=0;FSR0<0xff;FSR0++) 
	CLRR	_FSR0
;;unsigned compare: left < lit(0xFF=255), size=1
_00116_DS_
	MOVAI	0xff
	RSUBAR	_FSR0
	JBCLR	PFLAG,0
	GOTO	_00113_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	65; "MC32F7343_Demo_C.c"	INDF0=0;
	CLRR	_INDF0
;	.line	63; "MC32F7343_Demo_C.c"	for(FSR0=0;FSR0<0xff;FSR0++) 
	INCR	_FSR0
	GOTO	_00116_DS_
_00113_DS_
;	.line	67; "MC32F7343_Demo_C.c"	FSR0=0xFF;
	MOVAI	0xff
	MOVRA	_FSR0
;	.line	68; "MC32F7343_Demo_C.c"	INDF0=0;
	CLRR	_INDF0
;	.line	69; "MC32F7343_Demo_C.c"	for(FSR1=0;FSR1<0x7f;FSR1++) 
	CLRR	_FSR1
;;unsigned compare: left < lit(0x7F=127), size=1
_00119_DS_
	MOVAI	0x7f
	RSUBAR	_FSR1
	JBCLR	PFLAG,0
	GOTO	_00114_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	71; "MC32F7343_Demo_C.c"	INDF1=0;
	CLRR	_INDF1
;	.line	69; "MC32F7343_Demo_C.c"	for(FSR1=0;FSR1<0x7f;FSR1++) 
	INCR	_FSR1
	GOTO	_00119_DS_
_00114_DS_
;	.line	73; "MC32F7343_Demo_C.c"	FSR1=0x7f;
	MOVAI	0x7f
	MOVRA	_FSR1
;	.line	74; "MC32F7343_Demo_C.c"	INDF1=0; 
	CLRR	_INDF1
;	.line	75; "MC32F7343_Demo_C.c"	}
	RETURN	
; exit point of _C_RAM


;	code size estimation:
;	  642+    0 =   642 instructions ( 1284 byte)

	end
