;--------------------------------------------------------
; File Created by SN-SDCC : SinoMCU ANSI-C Compiler
; Version 2.0.0 (Dec 11 2019) (MINGW32)
; This file was generated Mon Nov 11 10:51:22 2024
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
	extern	_Scan_Key
	extern	_delay
	extern	__divsint
	extern	__modsint
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
	extern	__gptrget2
	extern	__gptrget1
;--------------------------------------------------------
; global declarations
;--------------------------------------------------------
	global	_Sleep_Func
	global	_Sys_Init
	global	_ADC_filte
	global	_tp_looktable
	global	_PIN_setinmode
	global	_LookTableFunc
	global	_LED_DispalayFunction
	global	_Decode
	global	_main
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
	global	_state
	global	_LED_buff
	global	_LED_DisplayNum
	global	_ADC_Scan_cnt
	global	_ADC_error_val
	global	_adc_data_Old
	global	_num
	global	_adc_tmp
	global	_cnt_test
	global	_cnt_iop
	global	_ADC_Val_tmp
	global	_ADC_Val
	global	_i
	global	_LED_table
	global	_tp

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

UD_MC32P7351_10	udata
_state	res	1

UD_MC32P7351_11	udata
_LED_buff	res	18

UD_MC32P7351_12	udata
_LED_DisplayNum	res	1

UD_MC32P7351_13	udata
_ADC_Scan_cnt	res	1

UD_MC32P7351_14	udata
_ADC_error_val	res	2

UD_MC32P7351_15	udata
_adc_data_Old	res	2

UD_MC32P7351_16	udata
_num	res	1

UD_MC32P7351_17	udata
_adc_tmp	res	2

UD_MC32P7351_18	udata
_cnt_test	res	2

UD_MC32P7351_19	udata
_cnt_iop	res	1

UD_MC32P7351_20	udata
_ADC_Val_tmp	res	2

UD_MC32P7351_21	udata
_ADC_Val	res	8

UD_MC32P7351_22	udata
_i	res	1

;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
;--------------------------------------------------------
; compiler-defined variables
;--------------------------------------------------------
UDL_MC32P7351_0	udata
r0x102F	res	1
r0x102E	res	1
r0x1030	res	1
r0x1031	res	1
r0x1032	res	1
r0x1033	res	1
r0x1034	res	1
r0x1035	res	1
r0x1036	res	1
r0x1039	res	1
r0x1037	res	1
r0x1038	res	1
;--------------------------------------------------------
; initialized data
;--------------------------------------------------------

ID_MC32P7351_0	code
_LED_table
	dw 0x3f
	dw 0x06
	dw 0x5b
	dw 0x4f
	dw 0x66
	dw 0x6d
	dw 0x7d
	dw 0x07
	dw 0x7f
	dw 0x6f
	dw 0x79


ID_MC32P7351_1	code
_tp
	dw 0xbe
	dw 0x03
	dw 0xe4
	dw 0x03
	dw 0x0b
	dw 0x04
	dw 0x32
	dw 0x04
	dw 0x5a
	dw 0x04
	dw 0x83
	dw 0x04
	dw 0xad
	dw 0x04
	dw 0xd7
	dw 0x04
	dw 0x01
	dw 0x05
	dw 0x2d
	dw 0x05
	dw 0x58
	dw 0x05
	dw 0x84
	dw 0x05
	dw 0xb1
	dw 0x05
	dw 0xdd
	dw 0x05
	dw 0x0a
	dw 0x06
	dw 0x38
	dw 0x06
	dw 0x65
	dw 0x06
	dw 0x93
	dw 0x06
	dw 0xc1
	dw 0x06
	dw 0xef
	dw 0x06
	dw 0x1c
	dw 0x07
	dw 0x4a
	dw 0x07
	dw 0x78
	dw 0x07
	dw 0xa5
	dw 0x07
	dw 0xd3
	dw 0x07
	dw 0x00
	dw 0x08
	dw 0x2d
	dw 0x08
	dw 0x59
	dw 0x08
	dw 0x86
	dw 0x08
	dw 0xb2
	dw 0x08
	dw 0xdd
	dw 0x08
	dw 0x08
	dw 0x09
	dw 0x33
	dw 0x09
	dw 0x5d
	dw 0x09
	dw 0x86
	dw 0x09
	dw 0xaf
	dw 0x09
	dw 0xd7
	dw 0x09
	dw 0xff
	dw 0x09
	dw 0x26
	dw 0x0a
	dw 0x4d
	dw 0x0a
	dw 0x73
	dw 0x0a
	dw 0x98
	dw 0x0a
	dw 0xbc
	dw 0x0a
	dw 0xe0
	dw 0x0a
	dw 0x03
	dw 0x0b
	dw 0x25
	dw 0x0b
	dw 0x47
	dw 0x0b
	dw 0x68
	dw 0x0b
	dw 0x88
	dw 0x0b
	dw 0xa8
	dw 0x0b
	dw 0xc6
	dw 0x0b
	dw 0xe4
	dw 0x0b
	dw 0x02
	dw 0x0c
	dw 0x1e
	dw 0x0c
	dw 0x3a
	dw 0x0c
	dw 0x56
	dw 0x0c
	dw 0x70
	dw 0x0c
	dw 0x8a
	dw 0x0c
	dw 0xa3
	dw 0x0c
	dw 0xbc
	dw 0x0c
	dw 0xd4
	dw 0x0c
	dw 0xeb
	dw 0x0c
	dw 0x02
	dw 0x0d
	dw 0x18
	dw 0x0d
	dw 0x2d
	dw 0x0d
	dw 0x42
	dw 0x0d
	dw 0x56
	dw 0x0d
	dw 0x6a
	dw 0x0d
	dw 0x7d
	dw 0x0d
	dw 0x90
	dw 0x0d
	dw 0xa2
	dw 0x0d
	dw 0xb3
	dw 0x0d
	dw 0xc4
	dw 0x0d
	dw 0xd5
	dw 0x0d
	dw 0xe5
	dw 0x0d
	dw 0xf4
	dw 0x0d
	dw 0x03
	dw 0x0e
	dw 0x12
	dw 0x0e
	dw 0x20
	dw 0x0e
	dw 0x2e
	dw 0x0e
	dw 0x3b
	dw 0x0e
	dw 0x48
	dw 0x0e
	dw 0x55
	dw 0x0e
	dw 0x61
	dw 0x0e
	dw 0x6d
	dw 0x0e
	dw 0x78
	dw 0x0e
	dw 0x83
	dw 0x0e
	dw 0x8e
	dw 0x0e
	dw 0x98
	dw 0x0e
	dw 0xa3
	dw 0x0e
	dw 0xac
	dw 0x0e
	dw 0xb6
	dw 0x0e
	dw 0xbf
	dw 0x0e
	dw 0xc8
	dw 0x0e
	dw 0xd1
	dw 0x0e
	dw 0xd9
	dw 0x0e
	dw 0xe1
	dw 0x0e
	dw 0xe9
	dw 0x0e
	dw 0xf1
	dw 0x0e


;@Allocation info for local variables in function 'ADC_filte'
;@ADC_filte Sys_Init                  Allocated to registers ;size:2
;@ADC_filte CLR_RAM                   Allocated to registers ;size:2
;@ADC_filte IO_Init                   Allocated to registers ;size:2
;@ADC_filte TIMER0_INT_Init           Allocated to registers ;size:2
;@ADC_filte TIMER1_INT_Init           Allocated to registers ;size:2
;@ADC_filte TIMER2_INT_Init           Allocated to registers ;size:2
;@ADC_filte TIMER3_INT_Init           Allocated to registers ;size:2
;@ADC_filte TIMER0_PWM_Init           Allocated to registers ;size:2
;@ADC_filte TIMER1_PWM_Init           Allocated to registers ;size:2
;@ADC_filte TIMER2_PWM_Init           Allocated to registers ;size:2
;@ADC_filte ADC_Init                  Allocated to registers ;size:2
;@ADC_filte Scan_ADC                  Allocated to registers ;size:2
;@ADC_filte Set_ADC_Channel           Allocated to registers ;size:2
;@ADC_filte ADC_Get_Value_Average     Allocated to registers ;size:2
;@ADC_filte Scan_Key                  Allocated to registers ;size:2
;@ADC_filte Sleep_Func                Allocated to registers ;size:2
;@ADC_filte delay                     Allocated to registers ;size:2
;@ADC_filte ADC_filte                 Allocated to registers ;size:2
;@ADC_filte INDF0bits                 Allocated to registers ;size:1
;@ADC_filte INDF1bits                 Allocated to registers ;size:1
;@ADC_filte INDF2bits                 Allocated to registers ;size:1
;@ADC_filte HIBYTEbits                Allocated to registers ;size:1
;@ADC_filte FSR0bits                  Allocated to registers ;size:1
;@ADC_filte FSR1bits                  Allocated to registers ;size:1
;@ADC_filte PCLbits                   Allocated to registers ;size:1
;@ADC_filte PFLAGbits                 Allocated to registers ;size:1
;@ADC_filte MCRbits                   Allocated to registers ;size:1
;@ADC_filte INDF3bits                 Allocated to registers ;size:1
;@ADC_filte INTEbits                  Allocated to registers ;size:1
;@ADC_filte INTFbits                  Allocated to registers ;size:1
;@ADC_filte DRVCRbits                 Allocated to registers ;size:1
;@ADC_filte PFRCCRbits                Allocated to registers ;size:1
;@ADC_filte P1KBCRbits                Allocated to registers ;size:1
;@ADC_filte PFRCCALbits               Allocated to registers ;size:1
;@ADC_filte IOP0bits                  Allocated to registers ;size:1
;@ADC_filte OEP0bits                  Allocated to registers ;size:1
;@ADC_filte PUP0bits                  Allocated to registers ;size:1
;@ADC_filte PDP0bits                  Allocated to registers ;size:1
;@ADC_filte IOP1bits                  Allocated to registers ;size:1
;@ADC_filte OEP1bits                  Allocated to registers ;size:1
;@ADC_filte PUP1bits                  Allocated to registers ;size:1
;@ADC_filte PDP1bits                  Allocated to registers ;size:1
;@ADC_filte T0CRbits                  Allocated to registers ;size:1
;@ADC_filte T0CNTbits                 Allocated to registers ;size:1
;@ADC_filte T0LOADbits                Allocated to registers ;size:1
;@ADC_filte T0DATAbits                Allocated to registers ;size:1
;@ADC_filte T1CRbits                  Allocated to registers ;size:1
;@ADC_filte T1CNTbits                 Allocated to registers ;size:1
;@ADC_filte T1LOADbits                Allocated to registers ;size:1
;@ADC_filte T1DATAbits                Allocated to registers ;size:1
;@ADC_filte T2CRbits                  Allocated to registers ;size:1
;@ADC_filte T2CNTbits                 Allocated to registers ;size:1
;@ADC_filte T2LOADbits                Allocated to registers ;size:1
;@ADC_filte T2DATAbits                Allocated to registers ;size:1
;@ADC_filte T3CRbits                  Allocated to registers ;size:1
;@ADC_filte T3CNTbits                 Allocated to registers ;size:1
;@ADC_filte T3LOADbits                Allocated to registers ;size:1
;@ADC_filte PWM0DRbits                Allocated to registers ;size:1
;@ADC_filte PWM1DRbits                Allocated to registers ;size:1
;@ADC_filte PWM2DRbits                Allocated to registers ;size:1
;@ADC_filte PWMCR0bits                Allocated to registers ;size:1
;@ADC_filte PWMCR1bits                Allocated to registers ;size:1
;@ADC_filte OSCMRbits                 Allocated to registers ;size:1
;@ADC_filte LVDCRbits                 Allocated to registers ;size:1
;@ADC_filte ADCR0bits                 Allocated to registers ;size:1
;@ADC_filte ADCR1bits                 Allocated to registers ;size:1
;@ADC_filte ADCR2bits                 Allocated to registers ;size:1
;@ADC_filte OSADJCRbits               Allocated to registers ;size:1
;@ADC_filte ADRHbits                  Allocated to registers ;size:1
;@ADC_filte ADRLbits                  Allocated to registers ;size:1
;@ADC_filte ADIOS0bits                Allocated to registers ;size:1
;@ADC_filte ADIOS1bits                Allocated to registers ;size:1
;@ADC_filte PMODbits                  Allocated to registers ;size:1
;@ADC_filte PWMCR3bits                Allocated to registers ;size:1
;@ADC_filte PWMCR2bits                Allocated to registers ;size:1
;@ADC_filte PFRCAUXbits               Allocated to registers ;size:1
;@ADC_filte HIRCCALbits               Allocated to registers ;size:1
;@ADC_filte flag2                     Allocated to registers ;size:1
;@ADC_filte adc_data                  Allocated to registers ;size:2
;@ADC_filte abuf                      Allocated to registers ;size:1
;@ADC_filte statusbuf                 Allocated to registers ;size:1
;@ADC_filte sleep_time                Allocated to registers ;size:1
;@ADC_filte key_per                   Allocated to registers ;size:1
;@ADC_filte key_cur                   Allocated to registers ;size:1
;@ADC_filte key_down                  Allocated to registers ;size:1
;@ADC_filte key_keep                  Allocated to registers ;size:1
;@ADC_filte int_time0                 Allocated to registers ;size:1
;@ADC_filte Flag1                     Allocated to registers ;size:1
;@ADC_filte Flag2                     Allocated to registers ;size:1
;@ADC_filte state                     Allocated to registers ;size:1
;@ADC_filte LED_buff                  Allocated to registers ;size:18
;@ADC_filte LED_DisplayNum            Allocated to registers ;size:1
;@ADC_filte ADC_Scan_cnt              Allocated to registers ;size:1
;@ADC_filte ADC_error_val             Allocated to registers ;size:2
;@ADC_filte adc_data_Old              Allocated to registers ;size:2
;@ADC_filte num                       Allocated to registers ;size:1
;@ADC_filte adc_tmp                   Allocated to registers ;size:2
;@ADC_filte cnt_test                  Allocated to registers ;size:2
;@ADC_filte cnt_iop                   Allocated to registers ;size:1
;@ADC_filte ADC_Val_tmp               Allocated to registers ;size:2
;@ADC_filte ADC_Val                   Allocated to registers ;size:8
;@ADC_filte data_tmp                  Allocated to registers r0x102F r0x102E ;size:2
;@ADC_filte i                         Allocated to registers r0x1032 ;size:1
;@ADC_filte temp                      Allocated to registers r0x1030 r0x1031 ;size:2
;@ADC_filte INDF0                     Allocated to registers ;size:1
;@ADC_filte INDF1                     Allocated to registers ;size:1
;@ADC_filte INDF2                     Allocated to registers ;size:1
;@ADC_filte HIBYTE                    Allocated to registers ;size:1
;@ADC_filte FSR0                      Allocated to registers ;size:1
;@ADC_filte FSR1                      Allocated to registers ;size:1
;@ADC_filte PCL                       Allocated to registers ;size:1
;@ADC_filte PFLAG                     Allocated to registers ;size:1
;@ADC_filte MCR                       Allocated to registers ;size:1
;@ADC_filte INDF3                     Allocated to registers ;size:1
;@ADC_filte INTE                      Allocated to registers ;size:1
;@ADC_filte INTF                      Allocated to registers ;size:1
;@ADC_filte DRVCR                     Allocated to registers ;size:1
;@ADC_filte PFRCCR                    Allocated to registers ;size:1
;@ADC_filte P1KBCR                    Allocated to registers ;size:1
;@ADC_filte PFRCCAL                   Allocated to registers ;size:1
;@ADC_filte IOP0                      Allocated to registers ;size:1
;@ADC_filte OEP0                      Allocated to registers ;size:1
;@ADC_filte PUP0                      Allocated to registers ;size:1
;@ADC_filte PDP0                      Allocated to registers ;size:1
;@ADC_filte IOP1                      Allocated to registers ;size:1
;@ADC_filte OEP1                      Allocated to registers ;size:1
;@ADC_filte PUP1                      Allocated to registers ;size:1
;@ADC_filte PDP1                      Allocated to registers ;size:1
;@ADC_filte T0CR                      Allocated to registers ;size:1
;@ADC_filte T0CNT                     Allocated to registers ;size:1
;@ADC_filte T0LOAD                    Allocated to registers ;size:1
;@ADC_filte T0DATA                    Allocated to registers ;size:1
;@ADC_filte T1CR                      Allocated to registers ;size:1
;@ADC_filte T1CNT                     Allocated to registers ;size:1
;@ADC_filte T1LOAD                    Allocated to registers ;size:1
;@ADC_filte T1DATA                    Allocated to registers ;size:1
;@ADC_filte T2CR                      Allocated to registers ;size:1
;@ADC_filte T2CNT                     Allocated to registers ;size:1
;@ADC_filte T2LOAD                    Allocated to registers ;size:1
;@ADC_filte T2DATA                    Allocated to registers ;size:1
;@ADC_filte T3CR                      Allocated to registers ;size:1
;@ADC_filte T3CNT                     Allocated to registers ;size:1
;@ADC_filte T3LOAD                    Allocated to registers ;size:1
;@ADC_filte PWM0DR                    Allocated to registers ;size:1
;@ADC_filte PWM1DR                    Allocated to registers ;size:1
;@ADC_filte PWM2DR                    Allocated to registers ;size:1
;@ADC_filte PWMCR0                    Allocated to registers ;size:1
;@ADC_filte PWMCR1                    Allocated to registers ;size:1
;@ADC_filte OSCMR                     Allocated to registers ;size:1
;@ADC_filte LVDCR                     Allocated to registers ;size:1
;@ADC_filte ADCR0                     Allocated to registers ;size:1
;@ADC_filte ADCR1                     Allocated to registers ;size:1
;@ADC_filte ADCR2                     Allocated to registers ;size:1
;@ADC_filte OSADJCR                   Allocated to registers ;size:1
;@ADC_filte ADRH                      Allocated to registers ;size:1
;@ADC_filte ADRL                      Allocated to registers ;size:1
;@ADC_filte ADIOS0                    Allocated to registers ;size:1
;@ADC_filte ADIOS1                    Allocated to registers ;size:1
;@ADC_filte PMOD                      Allocated to registers ;size:1
;@ADC_filte PWMCR3                    Allocated to registers ;size:1
;@ADC_filte PWMCR2                    Allocated to registers ;size:1
;@ADC_filte PFRCAUX                   Allocated to registers ;size:1
;@ADC_filte HIRCCAL                   Allocated to registers ;size:1
;@end Allocation info for local variables in function 'ADC_filte';
;@Allocation info for local variables in function 'tp_looktable'
;@tp_looktable val                       Allocated to registers r0x102F r0x102E ;size:2
;@tp_looktable po                        Allocated to registers r0x102F ;size:1
;@end Allocation info for local variables in function 'tp_looktable';
;@Allocation info for local variables in function 'PIN_setinmode'
;@end Allocation info for local variables in function 'PIN_setinmode';
;@Allocation info for local variables in function 'LookTableFunc'
;@LookTableFunc bit                       Allocated to registers r0x102F ;size:1
;@LookTableFunc num                       Allocated to registers r0x102E ;size:1
;@LookTableFunc table_temp                Allocated to registers r0x1031 ;size:1
;@LookTableFunc i                         Allocated to registers r0x102E ;size:1
;@end Allocation info for local variables in function 'LookTableFunc';
;@Allocation info for local variables in function 'LED_DispalayFunction'
;@end Allocation info for local variables in function 'LED_DispalayFunction';
;@Allocation info for local variables in function 'Decode'
;@end Allocation info for local variables in function 'Decode';
;@Allocation info for local variables in function 'Sys_Init'
;@end Allocation info for local variables in function 'Sys_Init';
;@Allocation info for local variables in function 'main'
;@end Allocation info for local variables in function 'main';
;@Allocation info for local variables in function 'Sleep_Func'
;@end Allocation info for local variables in function 'Sleep_Func';

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
;   _ADC_Get_Value_Average
;   _ADC_filte
;   _ADC_Get_Value_Average
;   _ADC_filte
;   _Decode
;   _Sys_Init
;   _ADC_Get_Value_Average
;   _ADC_filte
;   _ADC_Get_Value_Average
;   _ADC_filte
;   _Decode
;3 compiler assigned registers:
;   r0x1037
;   r0x1038
;   STK00
;; Starting pCode block
_main	;Function start
; 2 exit points
;	.line	510; "MC32P7351.c"	Sys_Init();
	CALL	_Sys_Init
;	.line	511; "MC32P7351.c"	ADIOS0 = 0x08;                     //io???????  1:???????  0:???io
	MOVAI	0x08
	MOVRA	_ADIOS0
;	.line	514; "MC32P7351.c"	ADIOS1 = 0x00;  
	CLRR	_ADIOS1
;	.line	515; "MC32P7351.c"	PMOD = 0x07; 
	MOVAI	0x07
	MOVRA	_PMOD
;;gen.c:6570: size=0, offset=0, AOP_TYPE(res)=8
;	.line	516; "MC32P7351.c"	LED_buff[A1] = 0;
	CLRR	(_LED_buff + 0)
;;gen.c:6570: size=0, offset=0, AOP_TYPE(res)=8
;	.line	517; "MC32P7351.c"	LED_buff[1] = 1;
	MOVAI	0x01
	MOVRA	(_LED_buff + 1)
;;gen.c:6570: size=0, offset=0, AOP_TYPE(res)=8
;	.line	518; "MC32P7351.c"	LED_buff[2] = 1;
	MOVAI	0x01
	MOVRA	(_LED_buff + 2)
;	.line	519; "MC32P7351.c"	for ( i = 0; i < 18; i++)
	CLRR	_i
_00312_DS_
;	.line	521; "MC32P7351.c"	LED_buff[i] = 0;
	MOVAR	_i
	ADDAI	(_LED_buff + 0)
	MOVRA	r0x1037
	MOVAI	high (_LED_buff + 0)
	JBCLR	PFLAG,0
	ADDAI	0x01
	MOVRA	r0x1038
	MOVAR	r0x1037
	MOVRA	FSR0
	MOVAR	r0x1038
	MOVRA	FSR1
	MOVAI	0x00
	MOVRA	INDF2
;	.line	519; "MC32P7351.c"	for ( i = 0; i < 18; i++)
	INCR	_i
;;unsigned compare: left < lit(0x12=18), size=1
	MOVAI	0x12
	RSUBAR	_i
	JBSET	PFLAG,0
	GOTO	_00312_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;;gen.c:6570: size=0, offset=0, AOP_TYPE(res)=8
;	.line	526; "MC32P7351.c"	LED_buff[RED] = 0;
	CLRR	(_LED_buff + 15)
;;gen.c:6570: size=0, offset=0, AOP_TYPE(res)=8
;	.line	527; "MC32P7351.c"	LED_buff[BLU] = 0;
	CLRR	(_LED_buff + 17)
;;gen.c:6570: size=0, offset=0, AOP_TYPE(res)=8
;	.line	528; "MC32P7351.c"	LED_buff[GRE] = 0;
	CLRR	(_LED_buff + 16)
;	.line	531; "MC32P7351.c"	for ( i = 0; i < 4; i++)
	CLRR	_i
_00314_DS_
;	.line	533; "MC32P7351.c"	adc_data = ADC_Get_Value_Average();
	CALL	_ADC_Get_Value_Average
	MOVRA	(_adc_data + 1)
	MOVAR	STK00
	MOVRA	_adc_data
;	.line	534; "MC32P7351.c"	ADC_error_val = ADC_filte(adc_data);
	MOVAR	_adc_data
	MOVRA	STK00
	MOVAR	(_adc_data + 1)
	CALL	_ADC_filte
	MOVRA	(_ADC_error_val + 1)
	MOVAR	STK00
	MOVRA	_ADC_error_val
;	.line	531; "MC32P7351.c"	for ( i = 0; i < 4; i++)
	INCR	_i
;;unsigned compare: left < lit(0x4=4), size=1
	MOVAI	0x04
	RSUBAR	_i
	JBSET	PFLAG,0
	GOTO	_00314_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	538; "MC32P7351.c"	T1_flag = 1;
	BSET	_Flag1,1
_00310_DS_
;	.line	541; "MC32P7351.c"	ClrWdt();
	clrwdt	
;	.line	542; "MC32P7351.c"	if(T1_flag)   //2ms
	JBSET	_Flag1,1
	GOTO	_00310_DS_
;	.line	544; "MC32P7351.c"	T1_flag = 0;
	BCLR	_Flag1,1
;	.line	545; "MC32P7351.c"	ClrWdt();
	clrwdt	
;	.line	546; "MC32P7351.c"	adc_data = ADC_Get_Value_Average();
	CALL	_ADC_Get_Value_Average
	MOVRA	(_adc_data + 1)
	MOVAR	STK00
	MOVRA	_adc_data
;	.line	547; "MC32P7351.c"	adc_tmp += adc_data;
	MOVAR	_adc_data
	ADDRA	_adc_tmp
	MOVAR	(_adc_data + 1)
	JBCLR	PFLAG,0
	JZAR	(_adc_data + 1)
	ADDRA	(_adc_tmp + 1)
;	.line	548; "MC32P7351.c"	cnt_test++;
	INCR	_cnt_test
	JBCLR	PFLAG,2
	INCR	(_cnt_test + 1)
;;unsigned compare: left < lit(0x10=16), size=2
;	.line	549; "MC32P7351.c"	if(cnt_test>=16)
	MOVAI	0x00
	RSUBAR	(_cnt_test + 1)
	JBSET	PFLAG,2
	GOTO	_00352_DS_
	MOVAI	0x10
	RSUBAR	_cnt_test
_00352_DS_
	JBSET	PFLAG,0
	GOTO	_00310_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	551; "MC32P7351.c"	cnt_test= 0;
	CLRR	_cnt_test
	CLRR	(_cnt_test + 1)
;	.line	552; "MC32P7351.c"	adc_tmp>>=4;
	SWAPAR	_adc_tmp
	ANDAI	0x0f
	MOVRA	_adc_tmp
	SWAPAR	(_adc_tmp + 1)
	MOVRA	(_adc_tmp + 1)
	ANDAI	0xf0
	ORRA	_adc_tmp
	XORRA	(_adc_tmp + 1)
;	.line	553; "MC32P7351.c"	ADC_Val_tmp += adc_tmp;
	MOVAR	_adc_tmp
	ADDRA	_ADC_Val_tmp
	MOVAR	(_adc_tmp + 1)
	JBCLR	PFLAG,0
	JZAR	(_adc_tmp + 1)
	ADDRA	(_ADC_Val_tmp + 1)
;	.line	554; "MC32P7351.c"	adc_tmp = 0;
	CLRR	_adc_tmp
	CLRR	(_adc_tmp + 1)
;	.line	555; "MC32P7351.c"	cnt_iop++;
	INCR	_cnt_iop
;;unsigned compare: left < lit(0x10=16), size=1
;	.line	556; "MC32P7351.c"	if(cnt_iop>=16)
	MOVAI	0x10
	RSUBAR	_cnt_iop
	JBSET	PFLAG,0
	GOTO	_00310_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	558; "MC32P7351.c"	cnt_iop = 0;
	CLRR	_cnt_iop
;	.line	559; "MC32P7351.c"	ADC_Val_tmp>>=4;
	SWAPAR	_ADC_Val_tmp
	ANDAI	0x0f
	MOVRA	_ADC_Val_tmp
	SWAPAR	(_ADC_Val_tmp + 1)
	MOVRA	(_ADC_Val_tmp + 1)
	ANDAI	0xf0
	ORRA	_ADC_Val_tmp
	XORRA	(_ADC_Val_tmp + 1)
;	.line	560; "MC32P7351.c"	ADC_error_val = ADC_filte(ADC_Val_tmp);
	MOVAR	_ADC_Val_tmp
	MOVRA	STK00
	MOVAR	(_ADC_Val_tmp + 1)
	CALL	_ADC_filte
	MOVRA	(_ADC_error_val + 1)
	MOVAR	STK00
	MOVRA	_ADC_error_val
;	.line	561; "MC32P7351.c"	ADC_Val_tmp = 0;
	CLRR	_ADC_Val_tmp
	CLRR	(_ADC_Val_tmp + 1)
;	.line	562; "MC32P7351.c"	Decode();
	CALL	_Decode
	GOTO	_00310_DS_
;	.line	569; "MC32P7351.c"	}
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
;	.line	587; "MC32P7351.c"	if(!ON_flag)
	JBCLR	_Flag2,0
	GOTO	_00360_DS_
;	.line	589; "MC32P7351.c"	if(++sleep_time >= 100) //2ms*100 =200ms
	INCR	_sleep_time
;;unsigned compare: left < lit(0x64=100), size=1
	MOVAI	0x64
	RSUBAR	_sleep_time
	JBSET	PFLAG,0
	GOTO	_00362_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	591; "MC32P7351.c"	sleep_time = 0;
	CLRR	_sleep_time
;	.line	592; "MC32P7351.c"	GIE = 0;
	BCLR	_MCRbits,7
;	.line	593; "MC32P7351.c"	KBIF = 0;
	BCLR	_INTFbits,4
;	.line	594; "MC32P7351.c"	KBIE = 1;
	BSET	_INTEbits,4
;	.line	596; "MC32P7351.c"	Nop();
	nop	
;	.line	597; "MC32P7351.c"	Nop();
	nop	
;	.line	598; "MC32P7351.c"	Stop();
	stop	
;	.line	599; "MC32P7351.c"	Nop();
	nop	
;	.line	600; "MC32P7351.c"	Nop();
	nop	
;	.line	601; "MC32P7351.c"	KBIE = 0;
	BCLR	_INTEbits,4
;	.line	602; "MC32P7351.c"	KBIF = 0;
	BCLR	_INTFbits,4
;	.line	603; "MC32P7351.c"	GIE = 1;
	BSET	_MCRbits,7
	GOTO	_00362_DS_
_00360_DS_
;	.line	608; "MC32P7351.c"	sleep_time = 0;
	CLRR	_sleep_time
_00362_DS_
;	.line	610; "MC32P7351.c"	}
	RETURN	
; exit point of _Sleep_Func

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
;	.line	488; "MC32P7351.c"	GIE = 0;
	BCLR	_MCRbits,7
;	.line	489; "MC32P7351.c"	CLR_RAM();
	CALL	_CLR_RAM
;	.line	490; "MC32P7351.c"	IO_Init();
	CALL	_IO_Init
;	.line	491; "MC32P7351.c"	TIMER0_INT_Init();     	
	CALL	_TIMER0_INT_Init
;	.line	492; "MC32P7351.c"	TIMER1_INT_Init();
	CALL	_TIMER1_INT_Init
;	.line	498; "MC32P7351.c"	ADC_Init();
	CALL	_ADC_Init
;	.line	499; "MC32P7351.c"	GIE = 1;
	BSET	_MCRbits,7
;	.line	500; "MC32P7351.c"	}
	RETURN	
; exit point of _Sys_Init

;***
;  pBlock Stats: dbName = C
;***
;entry:  _Decode	;Function start
; 2 exit points
;has an exit
;functions called:
;   _LookTableFunc
;   _LookTableFunc
;   _tp_looktable
;   _LookTableFunc
;   _LookTableFunc
;   _LookTableFunc
;   _LookTableFunc
;   _tp_looktable
;   _LookTableFunc
;   _LookTableFunc
;1 compiler assigned register :
;   STK00
;; Starting pCode block
_Decode	;Function start
; 2 exit points
;;unsigned compare: left < lit(0x1E=30), size=2
;	.line	435; "MC32P7351.c"	if(ADC_error_val<30 || ADC_error_val>=3830)
	MOVAI	0x00
	RSUBAR	(_ADC_error_val + 1)
	JBSET	PFLAG,2
	GOTO	_00291_DS_
	MOVAI	0x1e
	RSUBAR	_ADC_error_val
_00291_DS_
	JBSET	PFLAG,0
	GOTO	_00265_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;;unsigned compare: left < lit(0xEF6=3830), size=2
	MOVAI	0x0e
	RSUBAR	(_ADC_error_val + 1)
	JBSET	PFLAG,2
	GOTO	_00292_DS_
	MOVAI	0xf6
	RSUBAR	_ADC_error_val
_00292_DS_
	JBSET	PFLAG,0
	GOTO	_00266_DS_
;;genSkipc:3291: created from rifx:013B5EFC
_00265_DS_
;	.line	437; "MC32P7351.c"	LookTableFunc(1,0);
	MOVAI	0x00
	MOVRA	STK00
	MOVAI	0x01
	CALL	_LookTableFunc
;	.line	438; "MC32P7351.c"	LookTableFunc(10,2);
	MOVAI	0x02
	MOVRA	STK00
	MOVAI	0x0a
	CALL	_LookTableFunc
;;gen.c:6570: size=0, offset=0, AOP_TYPE(res)=8
;	.line	439; "MC32P7351.c"	LED_buff[T] = 0;
	CLRR	(_LED_buff + 14)
;;gen.c:6570: size=0, offset=0, AOP_TYPE(res)=8
;	.line	440; "MC32P7351.c"	LED_buff[RED] = 0;
	CLRR	(_LED_buff + 15)
;;gen.c:6570: size=0, offset=0, AOP_TYPE(res)=8
;	.line	441; "MC32P7351.c"	LED_buff[BLU] = 0;
	CLRR	(_LED_buff + 17)
;;gen.c:6570: size=0, offset=0, AOP_TYPE(res)=8
;	.line	442; "MC32P7351.c"	LED_buff[GRE] = 0;
	CLRR	(_LED_buff + 16)
	GOTO	_00269_DS_
_00266_DS_
;	.line	446; "MC32P7351.c"	LED_DisplayNum = tp_looktable(ADC_error_val);
	MOVAR	_ADC_error_val
	MOVRA	STK00
	MOVAR	(_ADC_error_val + 1)
	CALL	_tp_looktable
	MOVRA	_LED_DisplayNum
;;gen.c:6570: size=0, offset=0, AOP_TYPE(res)=8
;	.line	447; "MC32P7351.c"	LED_buff[T] = 1;
	MOVAI	0x01
	MOVRA	(_LED_buff + 14)
;;unsigned compare: left < lit(0x23=35), size=1
;	.line	454; "MC32P7351.c"	if( LED_DisplayNum <35)
	MOVAI	0x23
	RSUBAR	_LED_DisplayNum
	JBCLR	PFLAG,0
	GOTO	_00263_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;;gen.c:6570: size=0, offset=0, AOP_TYPE(res)=8
;	.line	456; "MC32P7351.c"	LED_buff[RED] = 0;
	CLRR	(_LED_buff + 15)
;;gen.c:6570: size=0, offset=0, AOP_TYPE(res)=8
;	.line	457; "MC32P7351.c"	LED_buff[BLU] = 1;
	MOVAI	0x01
	MOVRA	(_LED_buff + 17)
;;gen.c:6570: size=0, offset=0, AOP_TYPE(res)=8
;	.line	458; "MC32P7351.c"	LED_buff[GRE] = 0;
	CLRR	(_LED_buff + 16)
	GOTO	_00264_DS_
;;unsigned compare: left < lit(0x23=35), size=1
_00263_DS_
;	.line	460; "MC32P7351.c"	else if(LED_DisplayNum >= 35 && LED_DisplayNum<41)
	MOVAI	0x23
	RSUBAR	_LED_DisplayNum
	JBSET	PFLAG,0
	GOTO	_00259_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;;unsigned compare: left < lit(0x29=41), size=1
	MOVAI	0x29
	RSUBAR	_LED_DisplayNum
	JBCLR	PFLAG,0
	GOTO	_00259_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;;gen.c:6570: size=0, offset=0, AOP_TYPE(res)=8
;	.line	462; "MC32P7351.c"	LED_buff[RED] = 0;
	CLRR	(_LED_buff + 15)
;;gen.c:6570: size=0, offset=0, AOP_TYPE(res)=8
;	.line	463; "MC32P7351.c"	LED_buff[BLU] = 0;
	CLRR	(_LED_buff + 17)
;;gen.c:6570: size=0, offset=0, AOP_TYPE(res)=8
;	.line	464; "MC32P7351.c"	LED_buff[GRE] = 1;
	MOVAI	0x01
	MOVRA	(_LED_buff + 16)
	GOTO	_00264_DS_
;;unsigned compare: left < lit(0x29=41), size=1
_00259_DS_
;	.line	466; "MC32P7351.c"	else if(LED_DisplayNum>=41)
	MOVAI	0x29
	RSUBAR	_LED_DisplayNum
	JBSET	PFLAG,0
	GOTO	_00264_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;;gen.c:6570: size=0, offset=0, AOP_TYPE(res)=8
;	.line	468; "MC32P7351.c"	LED_buff[RED] = 1;
	MOVAI	0x01
	MOVRA	(_LED_buff + 15)
;;gen.c:6570: size=0, offset=0, AOP_TYPE(res)=8
;	.line	469; "MC32P7351.c"	LED_buff[BLU] = 0;
	CLRR	(_LED_buff + 17)
;;gen.c:6570: size=0, offset=0, AOP_TYPE(res)=8
;	.line	470; "MC32P7351.c"	LED_buff[GRE] = 0;
	CLRR	(_LED_buff + 16)
_00264_DS_
;	.line	472; "MC32P7351.c"	LookTableFunc(LED_DisplayNum,0);
	MOVAI	0x00
	MOVRA	STK00
	MOVAR	_LED_DisplayNum
	CALL	_LookTableFunc
;	.line	473; "MC32P7351.c"	LookTableFunc(LED_DisplayNum,1);
	MOVAI	0x01
	MOVRA	STK00
	MOVAR	_LED_DisplayNum
	CALL	_LookTableFunc
_00269_DS_
;	.line	475; "MC32P7351.c"	}
	RETURN	
; exit point of _Decode

;***
;  pBlock Stats: dbName = C
;***
;entry:  _LED_DispalayFunction	;Function start
; 2 exit points
;has an exit
;functions called:
;   _PIN_setinmode
;   _PIN_setinmode
;1 compiler assigned register :
;   r0x1039
;; Starting pCode block
_LED_DispalayFunction	;Function start
; 2 exit points
;	.line	262; "MC32P7351.c"	PIN_setinmode();
	CALL	_PIN_setinmode
;;swapping arguments (AOP_TYPEs 1/3)
;;unsigned compare: left >= lit(0x9=9), size=1
;	.line	263; "MC32P7351.c"	switch (state)
	MOVAI	0x09
	RSUBAR	_state
	JBCLR	PFLAG,0
	GOTO	_00251_DS_
;;genSkipc:3291: created from rifx:013B5EFC
	MOVAR	_state
	ADDRA	PCL
	GOTO	_00204_DS_
	GOTO	_00211_DS_
	GOTO	_00218_DS_
	GOTO	_00225_DS_
	GOTO	_00232_DS_
	GOTO	_00239_DS_
	GOTO	_00242_DS_
	GOTO	_00245_DS_
	GOTO	_00248_DS_
_00204_DS_
;	.line	266; "MC32P7351.c"	OEP1 |= DEF_SET_BIT5;
	BSET	_OEP1,5
;	.line	267; "MC32P7351.c"	PIN1 = 1;
	BSET	_IOP1bits,5
;	.line	268; "MC32P7351.c"	if(LED_buff[A1])
	MOVAR	(_LED_buff + 0)
	MOVRA	r0x1039
	MOVAI	0x00
	ORAR	r0x1039
	JBCLR	PFLAG,2
	GOTO	_00206_DS_
;	.line	270; "MC32P7351.c"	OEP1 |= DEF_SET_BIT6;
	BSET	_OEP1,6
;	.line	271; "MC32P7351.c"	PIN2 = 0;
	BCLR	_IOP1bits,6
_00206_DS_
;	.line	273; "MC32P7351.c"	if(LED_buff[B1])
	MOVAR	(_LED_buff + 1)
	MOVRA	r0x1039
	MOVAI	0x00
	ORAR	r0x1039
	JBCLR	PFLAG,2
	GOTO	_00208_DS_
;	.line	275; "MC32P7351.c"	OEP1 |= DEF_SET_BIT3;
	BSET	_OEP1,3
;	.line	276; "MC32P7351.c"	PIN3 = 0;
	BCLR	_IOP1bits,3
_00208_DS_
;	.line	278; "MC32P7351.c"	if(LED_buff[C1])
	MOVAR	(_LED_buff + 2)
	MOVRA	r0x1039
	MOVAI	0x00
	ORAR	r0x1039
	JBCLR	PFLAG,2
	GOTO	_00210_DS_
;	.line	284; "MC32P7351.c"	PIN5_0;
	BSET	_OEP1,7
	BCLR	_IOP1bits,7
_00210_DS_
;	.line	286; "MC32P7351.c"	state++;
	INCR	_state
;	.line	287; "MC32P7351.c"	break;
	GOTO	_00251_DS_
_00211_DS_
;	.line	289; "MC32P7351.c"	OEP1 |= DEF_SET_BIT6;
	BSET	_OEP1,6
;	.line	290; "MC32P7351.c"	PIN2 = 1;
	BSET	_IOP1bits,6
;	.line	291; "MC32P7351.c"	if(LED_buff[E1])
	MOVAR	(_LED_buff + 4)
	MOVRA	r0x1039
	MOVAI	0x00
	ORAR	r0x1039
	JBCLR	PFLAG,2
	GOTO	_00213_DS_
;	.line	293; "MC32P7351.c"	OEP1 |= DEF_SET_BIT5;
	BSET	_OEP1,5
;	.line	294; "MC32P7351.c"	PIN1 = 0;
	BCLR	_IOP1bits,5
_00213_DS_
;	.line	296; "MC32P7351.c"	if(LED_buff[F1])
	MOVAR	(_LED_buff + 5)
	MOVRA	r0x1039
	MOVAI	0x00
	ORAR	r0x1039
	JBCLR	PFLAG,2
	GOTO	_00215_DS_
;	.line	298; "MC32P7351.c"	OEP1 |= DEF_SET_BIT3;
	BSET	_OEP1,3
;	.line	299; "MC32P7351.c"	PIN3 = 0;
	BCLR	_IOP1bits,3
_00215_DS_
;	.line	307; "MC32P7351.c"	if(LED_buff[D1])
	MOVAR	(_LED_buff + 3)
	MOVRA	r0x1039
	MOVAI	0x00
	ORAR	r0x1039
	JBCLR	PFLAG,2
	GOTO	_00217_DS_
;	.line	311; "MC32P7351.c"	PIN4_0;
	BSET	_OEP0,0
	BCLR	_IOP0bits,0
_00217_DS_
;	.line	313; "MC32P7351.c"	state++;
	INCR	_state
;	.line	314; "MC32P7351.c"	break;
	GOTO	_00251_DS_
_00218_DS_
;	.line	316; "MC32P7351.c"	OEP1 |= DEF_SET_BIT3;
	BSET	_OEP1,3
;	.line	317; "MC32P7351.c"	PIN3 = 1;
	BSET	_IOP1bits,3
;	.line	318; "MC32P7351.c"	if(LED_buff[B2])
	MOVAR	(_LED_buff + 8)
	MOVRA	r0x1039
	MOVAI	0x00
	ORAR	r0x1039
	JBCLR	PFLAG,2
	GOTO	_00220_DS_
;	.line	320; "MC32P7351.c"	OEP1 |= DEF_SET_BIT5;
	BSET	_OEP1,5
;	.line	321; "MC32P7351.c"	PIN1 = 0;
	BCLR	_IOP1bits,5
_00220_DS_
;	.line	328; "MC32P7351.c"	if(LED_buff[G1])
	MOVAR	(_LED_buff + 6)
	MOVRA	r0x1039
	MOVAI	0x00
	ORAR	r0x1039
	JBCLR	PFLAG,2
	GOTO	_00222_DS_
;	.line	332; "MC32P7351.c"	PIN5_0;
	BSET	_OEP1,7
	BCLR	_IOP1bits,7
_00222_DS_
;	.line	334; "MC32P7351.c"	if(LED_buff[A2])
	MOVAR	(_LED_buff + 7)
	MOVRA	r0x1039
	MOVAI	0x00
	ORAR	r0x1039
	JBCLR	PFLAG,2
	GOTO	_00224_DS_
;	.line	338; "MC32P7351.c"	PIN4_0;
	BSET	_OEP0,0
	BCLR	_IOP0bits,0
_00224_DS_
;	.line	340; "MC32P7351.c"	state++;
	INCR	_state
;	.line	341; "MC32P7351.c"	break;
	GOTO	_00251_DS_
_00225_DS_
;	.line	343; "MC32P7351.c"	OEP1 |= DEF_SET_BIT7;
	BSET	_OEP1,7
;	.line	344; "MC32P7351.c"	PIN5 = 1;
	BSET	_IOP1bits,7
;	.line	345; "MC32P7351.c"	if(LED_buff[C2])
	MOVAR	(_LED_buff + 9)
	MOVRA	r0x1039
	MOVAI	0x00
	ORAR	r0x1039
	JBCLR	PFLAG,2
	GOTO	_00227_DS_
;	.line	347; "MC32P7351.c"	OEP1 |= DEF_SET_BIT6;
	BSET	_OEP1,6
;	.line	348; "MC32P7351.c"	PIN2 = 0;
	BCLR	_IOP1bits,6
_00227_DS_
;	.line	350; "MC32P7351.c"	if(LED_buff[D2])
	MOVAR	(_LED_buff + 10)
	MOVRA	r0x1039
	MOVAI	0x00
	ORAR	r0x1039
	JBCLR	PFLAG,2
	GOTO	_00229_DS_
;	.line	352; "MC32P7351.c"	OEP1 |= DEF_SET_BIT3;
	BSET	_OEP1,3
;	.line	353; "MC32P7351.c"	PIN3 = 0;
	BCLR	_IOP1bits,3
_00229_DS_
;	.line	355; "MC32P7351.c"	if(LED_buff[E2])
	MOVAR	(_LED_buff + 11)
	MOVRA	r0x1039
	MOVAI	0x00
	ORAR	r0x1039
	JBCLR	PFLAG,2
	GOTO	_00231_DS_
;	.line	359; "MC32P7351.c"	PIN4_0;
	BSET	_OEP0,0
	BCLR	_IOP0bits,0
_00231_DS_
;	.line	361; "MC32P7351.c"	state++;
	INCR	_state
;	.line	362; "MC32P7351.c"	break;
	GOTO	_00251_DS_
_00232_DS_
;	.line	364; "MC32P7351.c"	OEP0 |= DEF_SET_BIT0;
	BSET	_OEP0,0
;	.line	365; "MC32P7351.c"	PIN4 = 1;
	BSET	_IOP0bits,0
;	.line	366; "MC32P7351.c"	if(LED_buff[F2])
	MOVAR	(_LED_buff + 12)
	MOVRA	r0x1039
	MOVAI	0x00
	ORAR	r0x1039
	JBCLR	PFLAG,2
	GOTO	_00234_DS_
;	.line	368; "MC32P7351.c"	OEP1 |= DEF_SET_BIT5;
	BSET	_OEP1,5
;	.line	369; "MC32P7351.c"	PIN1 = 0;
	BCLR	_IOP1bits,5
_00234_DS_
;	.line	371; "MC32P7351.c"	if(LED_buff[G2])
	MOVAR	(_LED_buff + 13)
	MOVRA	r0x1039
	MOVAI	0x00
	ORAR	r0x1039
	JBCLR	PFLAG,2
	GOTO	_00236_DS_
;	.line	373; "MC32P7351.c"	OEP1 |= DEF_SET_BIT6;
	BSET	_OEP1,6
;	.line	374; "MC32P7351.c"	PIN2 = 0;
	BCLR	_IOP1bits,6
_00236_DS_
;	.line	382; "MC32P7351.c"	if(LED_buff[T])
	MOVAR	(_LED_buff + 14)
	MOVRA	r0x1039
	MOVAI	0x00
	ORAR	r0x1039
	JBCLR	PFLAG,2
	GOTO	_00238_DS_
;	.line	384; "MC32P7351.c"	OEP1 |= DEF_SET_BIT3;
	BSET	_OEP1,3
;	.line	385; "MC32P7351.c"	PIN3 = 0;
	BCLR	_IOP1bits,3
_00238_DS_
;	.line	388; "MC32P7351.c"	state++;
	INCR	_state
;	.line	389; "MC32P7351.c"	break;
	GOTO	_00251_DS_
_00239_DS_
;	.line	391; "MC32P7351.c"	OEP1 |= DEF_SET_BIT6;
	BSET	_OEP1,6
;	.line	392; "MC32P7351.c"	PIN2 = 1;
	BSET	_IOP1bits,6
;	.line	393; "MC32P7351.c"	if(LED_buff[GRE])
	MOVAR	(_LED_buff + 16)
	MOVRA	r0x1039
	MOVAI	0x00
	ORAR	r0x1039
	JBCLR	PFLAG,2
	GOTO	_00241_DS_
;	.line	397; "MC32P7351.c"	PIN5_0;
	BSET	_OEP1,7
	BCLR	_IOP1bits,7
_00241_DS_
;	.line	399; "MC32P7351.c"	state++;
	INCR	_state
;	.line	400; "MC32P7351.c"	break;
	GOTO	_00251_DS_
_00242_DS_
;	.line	402; "MC32P7351.c"	OEP1 |= DEF_SET_BIT3;
	BSET	_OEP1,3
;	.line	403; "MC32P7351.c"	PIN3 = 1;
	BSET	_IOP1bits,3
;	.line	404; "MC32P7351.c"	if(LED_buff[BLU])
	MOVAR	(_LED_buff + 17)
	MOVRA	r0x1039
	MOVAI	0x00
	ORAR	r0x1039
	JBCLR	PFLAG,2
	GOTO	_00244_DS_
;	.line	406; "MC32P7351.c"	OEP1 |= DEF_SET_BIT6;
	BSET	_OEP1,6
;	.line	407; "MC32P7351.c"	PIN2 = 0;
	BCLR	_IOP1bits,6
_00244_DS_
;	.line	409; "MC32P7351.c"	state++;
	INCR	_state
;	.line	411; "MC32P7351.c"	break;
	GOTO	_00251_DS_
_00245_DS_
;	.line	413; "MC32P7351.c"	OEP0 |= DEF_SET_BIT0;
	BSET	_OEP0,0
;	.line	414; "MC32P7351.c"	PIN4 = 1;
	BSET	_IOP0bits,0
;	.line	415; "MC32P7351.c"	if(LED_buff[RED])
	MOVAR	(_LED_buff + 15)
	MOVRA	r0x1039
	MOVAI	0x00
	ORAR	r0x1039
	JBCLR	PFLAG,2
	GOTO	_00247_DS_
;	.line	419; "MC32P7351.c"	PIN5_0;
	BSET	_OEP1,7
	BCLR	_IOP1bits,7
_00247_DS_
;	.line	421; "MC32P7351.c"	state++;
	INCR	_state
;	.line	422; "MC32P7351.c"	break;
	GOTO	_00251_DS_
_00248_DS_
;	.line	424; "MC32P7351.c"	state = 0;
	CLRR	_state
_00251_DS_
;	.line	429; "MC32P7351.c"	}
	RETURN	
; exit point of _LED_DispalayFunction

;***
;  pBlock Stats: dbName = C
;***
;entry:  _LookTableFunc	;Function start
; 2 exit points
;has an exit
;functions called:
;   __divsint
;   __modsint
;   __modsint
;   __gptrget1
;   __divsint
;   __modsint
;   __modsint
;   __gptrget1
;8 compiler assigned registers:
;   r0x102E
;   STK00
;   r0x102F
;   r0x1030
;   r0x1031
;   STK02
;   STK01
;   r0x1032
;; Starting pCode block
_LookTableFunc	;Function start
; 2 exit points
;	.line	214; "MC32P7351.c"	void LookTableFunc(u8 num,u8 bit)
	MOVRA	r0x102E
	MOVAR	STK00
	MOVRA	r0x102F
;	.line	217; "MC32P7351.c"	if(bit == 1)
	MOVAR	r0x102F
	XORAI	0x01
	JBSET	PFLAG,2
	GOTO	_00184_DS_
;;104	MOVAR	r0x102E
;	.line	219; "MC32P7351.c"	num = (num/10) % 10;
	CLRR	r0x1031
	MOVAI	0x0a
	MOVRA	STK02
	MOVAI	0x00
	MOVRA	STK01
;;103	MOVAR	r0x1030
	MOVAR	r0x102E
	MOVRA	r0x1030
	MOVRA	STK00
	MOVAI	0x00
	CALL	__divsint
	MOVRA	r0x1031
	MOVAR	STK00
	MOVRA	r0x1030
	MOVAI	0x0a
	MOVRA	STK02
	MOVAI	0x00
	MOVRA	STK01
	MOVAR	r0x1030
	MOVRA	STK00
	MOVAR	r0x1031
	CALL	__modsint
	MOVRA	r0x1031
	MOVAR	STK00
	MOVRA	r0x102E
	MOVRA	r0x1030
;;102	MOVAR	r0x1030
	GOTO	_00185_DS_
_00184_DS_
;	.line	221; "MC32P7351.c"	else if(bit == 0)
	MOVAI	0x00
	ORAR	r0x102F
	JBSET	PFLAG,2
	GOTO	_00185_DS_
;;101	MOVAR	r0x102E
;	.line	223; "MC32P7351.c"	num = num % 10;
	CLRR	r0x1031
	MOVAI	0x0a
	MOVRA	STK02
	MOVAI	0x00
	MOVRA	STK01
;;100	MOVAR	r0x1030
	MOVAR	r0x102E
	MOVRA	r0x1030
	MOVRA	STK00
	MOVAI	0x00
	CALL	__modsint
	MOVRA	r0x1031
	MOVAR	STK00
	MOVRA	r0x102E
	MOVRA	r0x1030
;;99	MOVAR	r0x1030
_00185_DS_
;	.line	226; "MC32P7351.c"	table_temp = LED_table[num];
	MOVAR	r0x102E
	ADDAI	(_LED_table + 0)
	MOVRA	r0x102E
	MOVAI	high (_LED_table + 0)
	JBCLR	PFLAG,0
	ADDAI	0x01
	MOVRA	r0x1030
	MOVAR	r0x102E
	MOVRA	STK01
	MOVAR	r0x1030
	MOVRA	STK00
	MOVAI	0x80
	CALL	__gptrget1
	MOVRA	r0x1031
;	.line	227; "MC32P7351.c"	for (u8 i = 0; i < 7; i++)
	CLRR	r0x102E
;;unsigned compare: left < lit(0x7=7), size=1
_00197_DS_
	MOVAI	0x07
	RSUBAR	r0x102E
	JBCLR	PFLAG,0
	GOTO	_00199_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	229; "MC32P7351.c"	if (table_temp&0x01)
	JBSET	r0x1031,0
	GOTO	_00193_DS_
;	.line	231; "MC32P7351.c"	if (bit)
	MOVAI	0x00
	ORAR	r0x102F
	JBCLR	PFLAG,2
	GOTO	_00187_DS_
;	.line	233; "MC32P7351.c"	LED_buff[i] = 1;
	MOVAR	r0x102E
	ADDAI	(_LED_buff + 0)
	MOVRA	r0x1030
	MOVAI	high (_LED_buff + 0)
	JBCLR	PFLAG,0
	ADDAI	0x01
	MOVRA	r0x1032
	MOVAR	r0x1030
	MOVRA	FSR0
	MOVAR	r0x1032
	MOVRA	FSR1
	MOVAI	0x01
	MOVRA	INDF2
	GOTO	_00194_DS_
_00187_DS_
;	.line	237; "MC32P7351.c"	LED_buff[i+7] = 1;
	MOVAR	r0x102E
	MOVRA	r0x1030
	MOVAI	0x07
	ADDAR	r0x1030
	MOVRA	r0x1030
	CLRR	r0x1032
	MOVAR	r0x1030
	ADDAI	(_LED_buff + 0)
	MOVRA	r0x1030
	MOVAI	0x00
	JBCLR	PFLAG,0
	JZAR	r0x1032
	ADDAI	high (_LED_buff + 0)
	MOVRA	r0x1032
	MOVAR	r0x1030
	MOVRA	FSR0
	MOVAR	r0x1032
	MOVRA	FSR1
	MOVAI	0x01
	MOVRA	INDF2
	GOTO	_00194_DS_
_00193_DS_
;	.line	242; "MC32P7351.c"	if (bit)
	MOVAI	0x00
	ORAR	r0x102F
	JBCLR	PFLAG,2
	GOTO	_00190_DS_
;	.line	244; "MC32P7351.c"	LED_buff[i] = 0;
	MOVAR	r0x102E
	ADDAI	(_LED_buff + 0)
	MOVRA	r0x1030
	MOVAI	high (_LED_buff + 0)
	JBCLR	PFLAG,0
	ADDAI	0x01
	MOVRA	r0x1032
	MOVAR	r0x1030
	MOVRA	FSR0
	MOVAR	r0x1032
	MOVRA	FSR1
	MOVAI	0x00
	MOVRA	INDF2
	GOTO	_00194_DS_
_00190_DS_
;	.line	248; "MC32P7351.c"	LED_buff[i+7] = 0;
	MOVAR	r0x102E
	MOVRA	r0x1030
	MOVAI	0x07
	ADDAR	r0x1030
	MOVRA	r0x1030
	CLRR	r0x1032
	MOVAR	r0x1030
	ADDAI	(_LED_buff + 0)
	MOVRA	r0x1030
	MOVAI	0x00
	JBCLR	PFLAG,0
	JZAR	r0x1032
	ADDAI	high (_LED_buff + 0)
	MOVRA	r0x1032
	MOVAR	r0x1030
	MOVRA	FSR0
	MOVAR	r0x1032
	MOVRA	FSR1
	MOVAI	0x00
	MOVRA	INDF2
;;shiftRight_Left2ResultLit:5339: shCount=1, size=1, sign=0, same=1, offr=0
_00194_DS_
;	.line	251; "MC32P7351.c"	table_temp >>= 1;
	BCLR	PFLAG,0
	RRR	r0x1031
;	.line	227; "MC32P7351.c"	for (u8 i = 0; i < 7; i++)
	INCR	r0x102E
	GOTO	_00197_DS_
_00199_DS_
;	.line	254; "MC32P7351.c"	}
	RETURN	
; exit point of _LookTableFunc

;***
;  pBlock Stats: dbName = C
;***
;entry:  _PIN_setinmode	;Function start
; 2 exit points
;has an exit
;; Starting pCode block
_PIN_setinmode	;Function start
; 2 exit points
;	.line	206; "MC32P7351.c"	PIN1 = 0;PIN2 = 0;PIN3 = 0;PIN4 = 0;PIN5 = 0;
	BCLR	_IOP1bits,5
	BCLR	_IOP1bits,6
	BCLR	_IOP1bits,3
	BCLR	_IOP0bits,0
	BCLR	_IOP1bits,7
;	.line	207; "MC32P7351.c"	OEP1 &= DEF_CLR_BIT6 ; // io????? 1:out  0:in
	BCLR	_OEP1,6
;	.line	208; "MC32P7351.c"	OEP1 &= DEF_CLR_BIT7;
	BCLR	_OEP1,7
;	.line	209; "MC32P7351.c"	OEP1 &= DEF_CLR_BIT3;
	BCLR	_OEP1,3
;	.line	210; "MC32P7351.c"	OEP1 &= DEF_CLR_BIT5;
	BCLR	_OEP1,5
;	.line	211; "MC32P7351.c"	OEP0 &= DEF_CLR_BIT0; // io????? 1:out  0:in
	BCLR	_OEP0,0
;	.line	212; "MC32P7351.c"	}
	RETURN	
; exit point of _PIN_setinmode

;***
;  pBlock Stats: dbName = C
;***
;entry:  _tp_looktable	;Function start
; 2 exit points
;has an exit
;functions called:
;   __gptrget2
;   __gptrget2
;9 compiler assigned registers:
;   r0x102E
;   STK00
;   r0x102F
;   r0x1030
;   r0x1031
;   r0x1032
;   STK01
;   r0x1033
;   r0x1034
;; Starting pCode block
_tp_looktable	;Function start
; 2 exit points
;	.line	191; "MC32P7351.c"	u8 tp_looktable(u16 val)
	MOVRA	r0x102E
	MOVAR	STK00
	MOVRA	r0x102F
;	.line	194; "MC32P7351.c"	for ( po = 0; po < 99; po++)
	CLRR	r0x1030
_00155_DS_
;	.line	196; "MC32P7351.c"	if(val <=tp[po])
	BCLR	PFLAG,0
	RLAR	r0x1030
	MOVRA	r0x1031
	MOVAR	r0x1031
	ADDAI	(_tp + 0)
	MOVRA	r0x1031
	MOVAI	high (_tp + 0)
	JBCLR	PFLAG,0
	ADDAI	0x01
	MOVRA	r0x1032
	MOVAR	r0x1031
	MOVRA	STK01
	MOVAR	r0x1032
	MOVRA	STK00
	MOVAI	0x80
	CALL	__gptrget2
	MOVRA	r0x1033
	MOVAR	STK00
	MOVRA	r0x1034
	MOVAR	r0x102E
	RSUBAR	r0x1033
	JBSET	PFLAG,2
	GOTO	_00172_DS_
	MOVAR	r0x102F
	RSUBAR	r0x1034
_00172_DS_
	JBCLR	PFLAG,0
	GOTO	_00162_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	194; "MC32P7351.c"	for ( po = 0; po < 99; po++)
	INCR	r0x1030
;;unsigned compare: left < lit(0x63=99), size=1
	MOVAI	0x63
	RSUBAR	r0x1030
	JBSET	PFLAG,0
	GOTO	_00155_DS_
;;genSkipc:3291: created from rifx:013B5EFC
_00162_DS_
	MOVAR	r0x1030
	MOVRA	r0x102F
;;swapping arguments (AOP_TYPEs 1/2)
;;unsigned compare: left >= lit(0x2=2), size=1
;	.line	200; "MC32P7351.c"	if(po>1)po-=2;
	MOVAI	0x02
	RSUBAR	r0x1030
	JBSET	PFLAG,0
	GOTO	_00154_DS_
;;genSkipc:3291: created from rifx:013B5EFC
	MOVAR	r0x1030
	MOVRA	r0x102E
	MOVAI	0xfe
	ADDAR	r0x102E
	MOVRA	r0x102F
_00154_DS_
;	.line	201; "MC32P7351.c"	return po;
	MOVAR	r0x102F
;	.line	202; "MC32P7351.c"	}
	RETURN	
; exit point of _tp_looktable

;***
;  pBlock Stats: dbName = C
;***
;entry:  _ADC_filte	;Function start
; 2 exit points
;has an exit
;10 compiler assigned registers:
;   r0x102E
;   STK00
;   r0x102F
;   r0x1030
;   r0x1031
;   r0x1032
;   r0x1033
;   r0x1034
;   r0x1035
;   r0x1036
;; Starting pCode block
_ADC_filte	;Function start
; 2 exit points
;	.line	157; "MC32P7351.c"	u16 ADC_filte(u16 data_tmp)
	MOVRA	r0x102E
	MOVAR	STK00
	MOVRA	r0x102F
;	.line	161; "MC32P7351.c"	if(adc_data_Old>data_tmp)
	MOVAR	(_adc_data_Old + 1)
	RSUBAR	r0x102E
	JBSET	PFLAG,2
	GOTO	_00144_DS_
	MOVAR	_adc_data_Old
	RSUBAR	r0x102F
_00144_DS_
	JBCLR	PFLAG,0
	GOTO	_00106_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	163; "MC32P7351.c"	temp = adc_data_Old - data_tmp;
	MOVAR	r0x102F
	RSUBAR	_adc_data_Old
	MOVRA	r0x1030
	MOVAR	r0x102E
	JBSET	PFLAG,0
	INCAR	r0x102E
	RSUBAR	(_adc_data_Old + 1)
	MOVRA	r0x1031
	GOTO	_00107_DS_
_00106_DS_
;	.line	167; "MC32P7351.c"	temp = data_tmp - adc_data_Old;
	MOVAR	_adc_data_Old
	RSUBAR	r0x102F
	MOVRA	r0x1030
	MOVAR	(_adc_data_Old + 1)
	JBSET	PFLAG,0
	INCAR	(_adc_data_Old + 1)
	RSUBAR	r0x102E
	MOVRA	r0x1031
;;swapping arguments (AOP_TYPEs 1/2)
;;unsigned compare: left >= lit(0xB=11), size=2
_00107_DS_
;	.line	169; "MC32P7351.c"	if(temp>10)
	MOVAI	0x00
	RSUBAR	r0x1031
	JBSET	PFLAG,2
	GOTO	_00145_DS_
	MOVAI	0x0b
	RSUBAR	r0x1030
_00145_DS_
	JBSET	PFLAG,0
	GOTO	_00109_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	171; "MC32P7351.c"	temp = data_tmp;
	MOVAR	r0x102F
	MOVRA	r0x1030
	MOVAR	r0x102E
	MOVRA	r0x1031
	GOTO	_00110_DS_
_00109_DS_
;	.line	174; "MC32P7351.c"	temp = adc_data_Old;
	MOVAR	_adc_data_Old
	MOVRA	r0x1030
	MOVAR	(_adc_data_Old + 1)
	MOVRA	r0x1031
_00110_DS_
;	.line	176; "MC32P7351.c"	ADC_Val[num] = temp;
	BCLR	PFLAG,0
	RLAR	_num
	MOVRA	r0x1032
	MOVAR	r0x1032
	ADDAI	(_ADC_Val + 0)
	MOVRA	r0x1032
	MOVAI	high (_ADC_Val + 0)
	JBCLR	PFLAG,0
	ADDAI	0x01
	MOVRA	r0x1033
	MOVAR	r0x1032
	MOVRA	FSR0
	MOVAR	r0x1033
	MOVRA	FSR1
	MOVAR	r0x1030
	MOVRA	INDF2
	INCR	FSR0
	JBCLR	PFLAG,2
	INCR	FSR1
	MOVAR	r0x1031
	MOVRA	INDF2
;	.line	177; "MC32P7351.c"	num++;
	INCR	_num
;;unsigned compare: left < lit(0x4=4), size=1
;	.line	178; "MC32P7351.c"	if(num>=4)
	MOVAI	0x04
	RSUBAR	_num
	JBSET	PFLAG,0
	GOTO	_00112_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;	.line	179; "MC32P7351.c"	num = 0;
	CLRR	_num
_00112_DS_
;	.line	180; "MC32P7351.c"	temp = 0;
	CLRR	r0x1030
	CLRR	r0x1031
;	.line	181; "MC32P7351.c"	for ( i = 0; i < 4; i++)
	CLRR	r0x1032
_00114_DS_
;	.line	183; "MC32P7351.c"	temp += ADC_Val[i];
	BCLR	PFLAG,0
	RLAR	r0x1032
	MOVRA	r0x1033
	MOVAR	r0x1033
	ADDAI	(_ADC_Val + 0)
	MOVRA	r0x1033
	MOVAI	high (_ADC_Val + 0)
	JBCLR	PFLAG,0
	ADDAI	0x01
	MOVRA	r0x1034
	MOVAR	r0x1033
	MOVRA	FSR0
	MOVAR	r0x1034
	MOVRA	FSR1
	MOVAR	INDF2
	MOVRA	r0x1035
	INCR	FSR0
	JBCLR	PFLAG,2
	INCR	FSR1
	MOVAR	INDF2
	MOVRA	r0x1036
	MOVAR	r0x1035
	ADDRA	r0x1030
	MOVAR	r0x1036
	JBCLR	PFLAG,0
	JZAR	r0x1036
	ADDRA	r0x1031
;	.line	181; "MC32P7351.c"	for ( i = 0; i < 4; i++)
	INCR	r0x1032
;;unsigned compare: left < lit(0x4=4), size=1
	MOVAI	0x04
	RSUBAR	r0x1032
	JBSET	PFLAG,0
	GOTO	_00114_DS_
;;genSkipc:3291: created from rifx:013B5EFC
;;shiftRight_Left2ResultLit:5339: shCount=1, size=2, sign=0, same=0, offr=0
;	.line	185; "MC32P7351.c"	temp >>= 2;
	BCLR	PFLAG,0
	RRAR	r0x1031
	MOVRA	r0x1033
	RRAR	r0x1030
	MOVRA	r0x1032
;;shiftRight_Left2ResultLit:5339: shCount=1, size=2, sign=0, same=1, offr=0
	BCLR	PFLAG,0
	RRR	r0x1033
	RRR	r0x1032
;	.line	186; "MC32P7351.c"	adc_data_Old = data_tmp;
	MOVAR	r0x102F
	MOVRA	_adc_data_Old
	MOVAR	r0x102E
	MOVRA	(_adc_data_Old + 1)
;	.line	187; "MC32P7351.c"	return temp;
	MOVAR	r0x1032
	MOVRA	STK00
	MOVAR	r0x1033
;	.line	188; "MC32P7351.c"	}
	RETURN	
; exit point of _ADC_filte


;	code size estimation:
;	  750+    0 =   750 instructions ( 1500 byte)

	end
