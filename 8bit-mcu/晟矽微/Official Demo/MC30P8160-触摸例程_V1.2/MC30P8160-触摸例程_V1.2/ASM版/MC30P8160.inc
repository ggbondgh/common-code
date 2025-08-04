		LIST
;mc30p8160.inc    Standard Header File, Version 1.00 by Sinomcu
		NOLIST

;==========================================================================
;
;	Verify Processor
;
;==========================================================================

;	IFNDEF __30P8160
;		MESSG "Processor-header file mismatch.  Verify selected processor."
;	ENDIF

;==========================================================================
;
;	Register Definitions
;
;==========================================================================

;----- Register Files ---------------------------------------------------

INDF      		EQU		H'0000'
T0CNT     		EQU		H'0001'
PCL       		EQU		H'0002'
STATUS    		EQU		H'0003'
FSR       		EQU		H'0004'
P1        		EQU		H'0006'
MCR       		EQU		H'0008'
T0CR      		EQU		H'0009'
PCLATH    		EQU		H'000A'
PDCON     		EQU		H'000B'
ODCON     		EQU		H'000C'
PUCON     		EQU		H'000D'
INTE      		EQU		H'000E'
INTF      		EQU		H'000F'
PWM1CR0   		EQU		H'0050'
PWM1CR1   		EQU		H'0051'
PWM1CR2   		EQU		H'0052'
DDR1      		EQU		H'0056'
TMRCR     		EQU		H'0058'
T1CR      		EQU		H'0059'
T1CNT     		EQU		H'005A'
T1LOAD    		EQU		H'005B'
T1DATA    		EQU		H'005C'
T1DATB    		EQU		H'005D'
T1DATC    		EQU		H'005E'
T1DATD    		EQU		H'005F'
T2CR      		EQU		H'0060'
T2CNTH    		EQU		H'0061'
T2CNTL    		EQU		H'0062'
T2LOADH   		EQU		H'0063'
T2LOADL   		EQU		H'0064'
P1KBCR    		EQU		H'0065'
P1ADCR    		EQU		H'0067'
CMPCR0    		EQU		H'0068'
CMPCR1    		EQU		H'0069'
CMPCR2    		EQU		H'006A'
TKCR0     		EQU		H'006B'
TKCR1     		EQU		H'006C'
TKCR2     		EQU		H'006D'
TKCNTH    		EQU		H'006E'
TKCNTL    		EQU		H'006F'

;----- INDF Bits ---------------------------------------------------

#define 	INDF0     	INDF,0
#define 	INDF1     	INDF,1
#define 	INDF2     	INDF,2
#define 	INDF3     	INDF,3
#define 	INDF4     	INDF,4
#define 	INDF5     	INDF,5
#define 	INDF6     	INDF,6
#define 	INDF7     	INDF,7

;----- T0CNT Bits ---------------------------------------------------

#define 	T0CNT0    	T0CNT,0
#define 	T0CNT1    	T0CNT,1
#define 	T0CNT2    	T0CNT,2
#define 	T0CNT3    	T0CNT,3
#define 	T0CNT4    	T0CNT,4
#define 	T0CNT5    	T0CNT,5
#define 	T0CNT6    	T0CNT,6
#define 	T0CNT7    	T0CNT,7

;----- PCL Bits ---------------------------------------------------

#define 	PC0       	PCL,0
#define 	PC1       	PCL,1
#define 	PC2       	PCL,2
#define 	PC3       	PCL,3
#define 	PC4       	PCL,4
#define 	PC5       	PCL,5
#define 	PC6       	PCL,6
#define 	PC7       	PCL,7

;----- STATUS Bits ---------------------------------------------------

#define 	C         	STATUS,0
#define 	DC        	STATUS,1
#define 	Z         	STATUS,2
#define 	PD        	STATUS,3
#define 	TO        	STATUS,4
#define 	WKUP      	STATUS,7

;----- FSR Bits ---------------------------------------------------

#define 	FSR0      	FSR,0
#define 	FSR1      	FSR,1
#define 	FSR2      	FSR,2
#define 	FSR3      	FSR,3
#define 	FSR4      	FSR,4
#define 	FSR5      	FSR,5
#define 	FSR6      	FSR,6

;----- P1 Bits ---------------------------------------------------

#define 	P10D      	P1,0
#define 	P11D      	P1,1
#define 	P12D      	P1,2
#define 	P13D      	P1,3
#define 	P14D      	P1,4
#define 	P15D      	P1,5

;----- MCR Bits ---------------------------------------------------

#define 	CMPOF     	MCR,5
#define 	EIS       	MCR,6
#define 	WDTEN     	MCR,7

;----- T0CR Bits ---------------------------------------------------

#define 	T0PRS0    	T0CR,0
#define 	T0PRS1    	T0CR,1
#define 	T0PRS2    	T0CR,2
#define 	T0PTA     	T0CR,3
#define 	T0CSE     	T0CR,4
#define 	T0PTS     	T0CR,5
#define 	INTM      	T0CR,6

;----- PCLATH Bits ---------------------------------------------------

#define 	PCH0      	PCLATH,0
#define 	PCH1      	PCLATH,1

;----- PDCON Bits ---------------------------------------------------

#define 	P10PD     	PDCON,0
#define 	P11PD     	PDCON,1
#define 	P12PD     	PDCON,2
#define 	P13PD     	PDCON,3
#define 	P14PD     	PDCON,4
#define 	P15PD     	PDCON,5

;----- ODCON Bits ---------------------------------------------------

#define 	P10OD     	ODCON,0
#define 	P11OD     	ODCON,1
#define 	P12OD     	ODCON,2
#define 	P13OD     	ODCON,3
#define 	P14OD     	ODCON,4
#define 	P15OD     	ODCON,5

;----- PUCON Bits ---------------------------------------------------

#define 	P10PU     	PUCON,0
#define 	P11PU     	PUCON,1
#define 	P12PU     	PUCON,2
#define 	P13PU     	PUCON,3
#define 	P14PU     	PUCON,4
#define 	P15PU     	PUCON,5

;----- INTE Bits ---------------------------------------------------

#define 	T0IE      	INTE,0
#define 	KBIE      	INTE,1
#define 	INTIE     	INTE,2
#define 	GIE       	INTE,7

;----- INTF Bits ---------------------------------------------------

#define 	T0IF      	INTF,0
#define 	KBIF      	INTF,1
#define 	INTIF     	INTF,2

;----- PWM1CR0 Bits ---------------------------------------------------

#define 	PWM1BEN   	PWM1CR0,0
#define 	PWM1BOE   	PWM1CR0,1
#define 	PWM1CEN   	PWM1CR0,2
#define 	PWM1COE   	PWM1CR0,3
#define 	PWM1DEN   	PWM1CR0,4
#define 	PWM1DOE   	PWM1CR0,5

;----- PWM1CR1 Bits ---------------------------------------------------

#define 	PWM1LG    	PWM1CR1,0
#define 	PWM1MD    	PWM1CR1,1
#define 	PWM1ANV   	PWM1CR1,2
#define 	PWM1DOS   	PWM1CR1,3

;----- PWM1CR2 Bits ---------------------------------------------------

#define 	PWM1ADB   	PWM1CR2,0
#define 	PWM1BDB   	PWM1CR2,1
#define 	PWM1CDB   	PWM1CR2,2
#define 	PWM1DDB   	PWM1CR2,3

;----- DDR1 Bits ---------------------------------------------------

#define 	DDR10     	DDR1,0
#define 	DDR11     	DDR1,1
#define 	DDR12     	DDR1,2
#define 	DDR13     	DDR1,3
#define 	DDR14     	DDR1,4
#define 	DDR15     	DDR1,5

;----- TMRCR Bits ---------------------------------------------------

#define 	T1IF      	TMRCR,0
#define 	T1IE      	TMRCR,1
#define 	T2IF      	TMRCR,2
#define 	T2IE      	TMRCR,3
#define 	T0TBS     	TMRCR,6

;----- T1CR Bits ---------------------------------------------------

#define 	T1PRS0    	T1CR,0
#define 	T1PRS1    	T1CR,1
#define 	T1PRS2    	T1CR,2
#define 	T1CKS0    	T1CR,3
#define 	T1CKS1    	T1CR,4
#define 	PWM1AEN   	T1CR,5
#define 	PWM1AOE   	T1CR,6
#define 	T1EN      	T1CR,7

;----- T1CNT Bits ---------------------------------------------------

#define 	T1CNT0    	T1CNT,0
#define 	T1CNT1    	T1CNT,1
#define 	T1CNT2    	T1CNT,2
#define 	T1CNT3    	T1CNT,3
#define 	T1CNT4    	T1CNT,4
#define 	T1CNT5    	T1CNT,5
#define 	T1CNT6    	T1CNT,6
#define 	T1CNT7    	T1CNT,7

;----- T1LOAD Bits ---------------------------------------------------

#define 	T1LOAD0   	T1LOAD,0
#define 	T1LOAD1   	T1LOAD,1
#define 	T1LOAD2   	T1LOAD,2
#define 	T1LOAD3   	T1LOAD,3
#define 	T1LOAD4   	T1LOAD,4
#define 	T1LOAD5   	T1LOAD,5
#define 	T1LOAD6   	T1LOAD,6
#define 	T1LOAD7   	T1LOAD,7

;----- T1DATA Bits ---------------------------------------------------

#define 	T1DATA0   	T1DATA,0
#define 	T1DATA1   	T1DATA,1
#define 	T1DATA2   	T1DATA,2
#define 	T1DATA3   	T1DATA,3
#define 	T1DATA4   	T1DATA,4
#define 	T1DATA5   	T1DATA,5
#define 	T1DATA6   	T1DATA,6
#define 	T1DATA7   	T1DATA,7

;----- T1DATB Bits ---------------------------------------------------

#define 	T1DATB0   	T1DATB,0
#define 	T1DATB1   	T1DATB,1
#define 	T1DATB2   	T1DATB,2
#define 	T1DATB3   	T1DATB,3
#define 	T1DATB4   	T1DATB,4
#define 	T1DATB5   	T1DATB,5
#define 	T1DATB6   	T1DATB,6
#define 	T1DATB7   	T1DATB,7

;----- T1DATC Bits ---------------------------------------------------

#define 	T1DATC0   	T1DATC,0
#define 	T1DATC1   	T1DATC,1
#define 	T1DATC2   	T1DATC,2
#define 	T1DATC3   	T1DATC,3
#define 	T1DATC4   	T1DATC,4
#define 	T1DATC5   	T1DATC,5
#define 	T1DATC6   	T1DATC,6
#define 	T1DATC7   	T1DATC,7

;----- T1DATD Bits ---------------------------------------------------

#define 	T1DATD0   	T1DATD,0
#define 	T1DATD1   	T1DATD,1
#define 	T1DATD2   	T1DATD,2
#define 	T1DATD3   	T1DATD,3
#define 	T1DATD4   	T1DATD,4
#define 	T1DATD5   	T1DATD,5
#define 	T1DATD6   	T1DATD,6
#define 	T1DATD7   	T1DATD,7

;----- T2CR Bits ---------------------------------------------------

#define 	T2PRS0    	T2CR,0
#define 	T2PRS1    	T2CR,1
#define 	T2PRS2    	T2CR,2
#define 	T2CKS0    	T2CR,3
#define 	T2CKS1    	T2CR,4
#define 	T2MOD     	T2CR,6
#define 	T2EN      	T2CR,7

;----- T2CNTH Bits ---------------------------------------------------

#define 	T2CNT8    	T2CNTH,0
#define 	T2CNT9    	T2CNTH,1
#define 	T2CNT10   	T2CNTH,2
#define 	T2CNT11   	T2CNTH,3
#define 	T2CNT12   	T2CNTH,4
#define 	T2CNT13   	T2CNTH,5
#define 	T2CNT14   	T2CNTH,6
#define 	T2CNT15   	T2CNTH,7

;----- T2CNTL Bits ---------------------------------------------------

#define 	T2CNT0    	T2CNTL,0
#define 	T2CNT1    	T2CNTL,1
#define 	T2CNT2    	T2CNTL,2
#define 	T2CNT3    	T2CNTL,3
#define 	T2CNT4    	T2CNTL,4
#define 	T2CNT5    	T2CNTL,5
#define 	T2CNT6    	T2CNTL,6
#define 	T2CNT7    	T2CNTL,7

;----- T2LOADH Bits ---------------------------------------------------

#define 	T1LOAD8   	T2LOADH,0
#define 	T1LOAD9   	T2LOADH,1
#define 	T1LOAD10  	T2LOADH,2
#define 	T1LOAD11  	T2LOADH,3
#define 	T1LOAD12  	T2LOADH,4
#define 	T1LOAD13  	T2LOADH,5
#define 	T1LOAD14  	T2LOADH,6
#define 	T1LOAD15  	T2LOADH,7

;----- T2LOADL Bits ---------------------------------------------------

#define 	T2LOAD0   	T2LOADL,0
#define 	T2LOAD1   	T2LOADL,1
#define 	T2LOAD2   	T2LOADL,2
#define 	T2LOAD3   	T2LOADL,3
#define 	T2LOAD4   	T2LOADL,4
#define 	T2LOAD5   	T2LOADL,5
#define 	T2LOAD6   	T2LOADL,6
#define 	T2LOAD7   	T2LOADL,7

;----- P1KBCR Bits ---------------------------------------------------

#define 	P10KE     	P1KBCR,0
#define 	P11KE     	P1KBCR,1
#define 	P12KE     	P1KBCR,2
#define 	P13KE     	P1KBCR,3
#define 	P14KE     	P1KBCR,4
#define 	P15KE     	P1KBCR,5

;----- P1ADCR Bits ---------------------------------------------------

#define 	P10DC     	P1ADCR,0
#define 	P11DC     	P1ADCR,1
#define 	P12DC     	P1ADCR,2
#define 	P13DC     	P1ADCR,3
#define 	P14DC     	P1ADCR,4
#define 	P15DC     	P1ADCR,5

;----- CMPCR0 Bits ---------------------------------------------------

#define 	CMPOE     	CMPCR0,0
#define 	CMPNV     	CMPCR0,1
#define 	EVDIS0    	CMPCR0,3
#define 	EVDIS1    	CMPCR0,4
#define 	CMPNS     	CMPCR0,5
#define 	CMPPS     	CMPCR0,6
#define 	CMPEN     	CMPCR0,7

;----- CMPCR1 Bits ---------------------------------------------------

#define 	EVDVS0    	CMPCR1,0
#define 	EVDVS1    	CMPCR1,1
#define 	EVDVS2    	CMPCR1,2
#define 	EVDVS3    	CMPCR1,3
#define 	EVDVS4    	CMPCR1,4
#define 	EVDVS5    	CMPCR1,5

;----- CMPCR2 Bits ---------------------------------------------------

#define 	CMPIF     	CMPCR2,0
#define 	CMPIE     	CMPCR2,1
#define 	CMPIM     	CMPCR2,2

;----- TKCR0 Bits ---------------------------------------------------

#define 	TKFS0     	TKCR0,0
#define 	TKFS1     	TKCR0,1
#define 	TKFS2     	TKCR0,2
#define 	TKFJE     	TKCR0,3
#define 	TKCFL     	TKCR0,5
#define 	TKCON     	TKCR0,6
#define 	TKEN      	TKCR0,7

;----- TKCR1 Bits ---------------------------------------------------

#define 	TKCHS0    	TKCR1,0
#define 	TKCHS1    	TKCR1,1
#define 	TKCHS2    	TKCR1,2
#define 	TKCHS3    	TKCR1,3
#define 	TKIF      	TKCR1,6
#define 	TKIE      	TKCR1,7

;----- TKCNTH Bits ---------------------------------------------------

#define 	TKCNT8    	TKCNTH,0
#define 	TKCNT9    	TKCNTH,1
#define 	TKCNT10   	TKCNTH,2
#define 	TKCNT11   	TKCNTH,3
#define 	TKCNT12   	TKCNTH,4
#define 	TKCNT13   	TKCNTH,5
#define 	TKCNT14   	TKCNTH,6
#define 	TKCNT15   	TKCNTH,7

;----- TKCNTL Bits ---------------------------------------------------

#define 	TKCNT0    	TKCNTL,0
#define 	TKCNT1    	TKCNTL,1
#define 	TKCNT2    	TKCNTL,2
#define 	TKCNT3    	TKCNTL,3
#define 	TKCNT4    	TKCNTL,4
#define 	TKCNT5    	TKCNTL,5
#define 	TKCNT6    	TKCNTL,6
#define 	TKCNT7    	TKCNTL,7

;==========================================================================
;
;	RAM Definition
;
;==========================================================================

	__MAXRAM H'FF'
	__BADRAM H'80'-H'81'
	__BADRAM H'85'


;==========================================================================
;
;	Configuration Bits
;
;==========================================================================

_CONFIG1  		EQU		H'8001'
_CONFIG0  		EQU		H'8000'

;OPBIT1

;OPBIT0

		LIST
