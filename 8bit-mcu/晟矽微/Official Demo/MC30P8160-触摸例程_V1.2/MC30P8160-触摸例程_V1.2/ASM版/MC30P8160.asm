#include		"MC30P8160.inc"
#include		"MC30P8160_TK.h"

#DEFINE				INTFLAG	   	INTF  	   	;8160������оƬ�ļĴ����������
#DEFINE				INTECON	   	INTE
#DEFINE				KBIM		P1KBCR
;;;------- ����ģ��ʹ�ܶ���  --------------------
#DEFINE	   	   	   	SET_UART_ENABLE	   	1  	;���ڹ����Ƿ�ʹ��
;;;--------- �û����ݶ���------------------------
cblock    0x10
SAVE_ACC
SAVE_STATUS

PLAY_FLAG
TEMP0		;TEMP0-TEMP7�ڸ��ӳ�������ʱʹ�ã��˳��ӳ���ʱ��Ч
TEMP1
TEMP2
TEMP3
TEMP4
TEMP5
TEMP6
TEMP7  	   	;CBLOCK 0X00-0X10

USE_FLAG

ENDC

;;-----------------------------------------------
#DEFINE				TIME_FG		USE_FLAG,0
#DEFINE				TEST_FG		USE_FLAG,1
;;-----------------------------------------------
#DEFINE	   	   	   	PIN_UART_TX		P1,5   	   	;����TX��
#DEFINE	   	   	   	PIN_LED1		P1,4   	   	;LED1�����
;;;**********************************************
;;;**********************************************
;;;**********************************************
;�ж�������
;.code
	ORG		0x03FF
	GOTO	START			;0000H
	ORG		0x0000
	GOTO	START			;0000H
	NOP					;0001H
	NOP					;0002H
	NOP					;0003H  
	NOP					;0004H
	NOP					;0005H
	NOP					;0006H
	NOP					;0007H
	GOTO	INT_SUB			;0008H
;;---------------------------------------------------------
#include        "MC30P8160_TK.asm"
;;---------------------------------------------------------
#if SET_UART_ENABLE	   	   	   	   	;���ڹ����Ƿ�ʹ��
#include        "MC30P8160_UART.asm"
#else
#endif
;;---------------------------------------------------------
INT_SUB:
	MOVRA	SAVE_ACC
	SWAPAR	STATUS
	MOVRA	SAVE_STATUS
	JBCLR	INTFLAG,0		;��ʱ0�жϱ�־
	GOTO	T0_INT
	JBCLR	T1IF			;��ʱ1�жϱ�־
	GOTO	T1_INT
;	JBCLR	INTFLAG,1		;�����жϱ�־
;	GOTO	KEY_INT
;	JBCLR	INTFLAG,2		;�ⲿ�жϱ�־
;	GOTO	PORT_INT
INT_END:
	CLRR	INTFLAG
	SWAPAR	SAVE_STATUS
	MOVRA	STATUS
	SWAPR	SAVE_ACC
	SWAPAR	SAVE_ACC
	RETIE   
;;;--------------------------
T0_INT:
	BCLR	INTFLAG,0		;�嶨ʱ0�жϱ�־
;	MOVAI   131				;��ʱ��0û�����������ı����ڿ��Ը�T0CR��Ƶֵ�����ж����T0CNT	
;	MOVRA	T0CNT			;�嶨ʱ��0����ֵ
	BSET	TIME_FG
	GOTO	INT_END
;;;--------------------------
T1_INT:
	BCLR	T1IF			;�嶨ʱ1�жϱ�־
;;;----------------
#if SET_UART_ENABLE	   	   	   	   	;���ڹ����Ƿ�ʹ��
   	CALL   	UART_SUB
#else
#endif
;;;----------------
	GOTO	INT_END
;;;--------------------------
;KEY_INT:
;	BCLR	INTFLAG,1		;�尴���жϱ�־
;	GOTO	INT_END
;;;--------------------------
;PORT_INT:
;	BCLR	INTFLAG,2		;���ⲿ�жϱ�־
;	GOTO	INT_END

;	MOVAR	LED_STEP2
;	ANDAI	0X07
;	ADDRA	PCL
;	GOTO	SCAN_LED_STEP1U
;	GOTO	SCAN_LED_STEP1D2U
;	GOTO	SCAN_LED_STEP2D3U
;	GOTO	SCAN_LED_STEP3D4U
;	GOTO	SCAN_LED_STEP4D1U
;;------------------------------------------------------------------------------------------------------------
;����RAM 10H~3FH
;------------------------------------------------------------------------------------------------------------
CLR_RAM:
	MOVAI	0X4F
	MOVRA	FSR
	MOVAI	0X3F
	MOVRA	0X4F			;�ѼĴ������������浽���һ���Ĵ�����
CLR_RAM_LOOP:
	DECR	FSR
	CLRR	INDF
	DJZR	0X4F
	GOTO	CLR_RAM_LOOP
	RETURN
;------------------------------------------------------------------------------------------------------------
;����Ĵ�����ʼ��
;------------------------------------------------------------------------------------------------------------
SET_OPTION:
   	MOVAI   00001111B 	   	;I/O�����ֹ����趨,0����Ч
   	MOVRA   P1ADCR
	MOVAI   00001111B		;P10,P11,P12����ڣ�P14,P15����ڣ�1Ϊ���룬0Ϊ���(P13ֻ��������)
	MOVRA   DDR1
	MOVAI   00000000B		;P10,P11,P12�����P14,P15����ڵ͵�ƽ����
	MOVRA   P1
	
	MOVAI   0xFF			;��������,1����Ч
	MOVRA   PDCON
	MOVAI   0xFF			;P14,P15����������,P13�޷�����������������Ϊ���գ��������ʱ�����߼���������
	MOVRA   PUCON			;3081/6060��P13������
	MOVAI   0x00			;��©����,1�ǿ�©,0������
	MOVRA   ODCON

;��ʱ���趨	
;	MOVAI   00000011B		;��ʱ��0����,BIT0-2:��ʱ����Ƶ,BIT3��ʱ������:1-WDT,0-TC0
;	MOVRA   T0CR			;BIT4:0-�����ؼ���1-�½��ؼ���,BIT5:ʱ��Դ0-FCPU,1-�ⲿ;BIT6:1-�����ش���0-�½��ش���
;	MOVAI   6	;131
;	CLRR	T0CNT			;�嶨ʱ��0����ֵ;T0û���Զ������������Լ���ֵ��256Ϊ��׼���������ж���ı�T0CNTֵ

	MOVAI   00000000B		;��ʱ��1����,BIT7=T1EN, BIT6=PWM1AOE,1����PWM, BIT5=PWM1AEN,1ʹ��PWM1A
	MOVRA   T1CR			;BIT4.3:T1ʱ��Դѡ��,BIT2-0:T1��Ƶ
	CLRR	T1CNT			;�嶨ʱ��1����ֵ
	CLRR	T1LOAD
	MOVAI	00000000B
	MOVRA	TMRCR			;BIT6=T0TBS,BIT3=T2IE,BIT2=T2IF,BIT1=T1IE,BIT0=T1IF
	MOVAI	00000000B
	MOVRA	PWM1CR0			;�ر�PWM
	MOVAI	00000000B
	MOVRA	PWM1CR1
	MOVAI	00000000B
	MOVRA	PWM1CR2
	CLRR	T1DATA
	CLRR	T1DATB
	CLRR	T1DATC
	CLRR	T1DATD

;	MOVAI   00000010B		;��ʱ��2����,BIT0-2:��ʱ����Ƶ,BIT3��ʱ������:1-WDT,0-TC0
;	MOVRA   T2CR			;BIT4:0-������1-�½���,BIT5:��
;	MOVAI   0XF0
;	MOVRA	T2CNTL			;�嶨ʱ��2����ֵ
;	MOVRA	T2LOADL			;�嶨ʱ��2����ֵ
;	MOVAI   0X6D
;	MOVRA	T2LOADH			;�嶨ʱ��2����ֵ
	
	MOVAI   00000001B
	MOVRA   INTECON			;BIT7=GIE,���ж�,BIT0=T0IE,BIT1=KBIE,BIT2=INT0IE,1-�ж�ʹ��
	BSET	GIE
;	BSET	T0IE			;��T0�жϣ����뵥���趨
	MOVAI   0x00
	MOVRA   INTFLAG			;BIT0=T0IF,BIT1=KBIF,BIT2=INT0IF,1-�жϷ���
	MOVAI   0x00			;P14,P15,P13�����жϹ��ܿ�
	MOVRA   KBIM
	RETURN
;------------------------------------------------------------------------------------------------------------
;��λ��ʼ��
;------------------------------------------------------------------------------------------------------------
SET_MAIN_T0:
	MOVAI   00000011B		;��ʱ��0����,BIT0-2:��ʱ����Ƶ,BIT3��ʱ������:1-WDT,0-TC0
	MOVRA   T0CR			;BIT4:0-�����ؼ���1-�½��ؼ���,BIT5:ʱ��Դ0-FCPU,1-�ⲿ;BIT6:1-�����ش���0-�½��ش���
	CLRR	T0CNT			;�嶨ʱ��0����ֵ;T0û���Զ������������Լ���ֵ��256Ϊ��׼���������ж���ı�T0CNTֵ
	RETURN
;----------------------------
SCAN_LED:					;��������Ӧ�����������������ڣ�
   	MOVAI	0X0F
   	ANDAR  	TOUCH_FLAG
   	JBCLR	Z
   	GOTO   	SCAN_LED1_OFF
SCAN_LED1_ON:
   	BSET   	PIN_LED1
   	GOTO   	SCAN_LED2
SCAN_LED1_OFF:
   	BCLR   	PIN_LED1
   	GOTO   	SCAN_LED2

SCAN_LED2:
	RETURN
;------------------------------------------------------------------------------------------------------------
START:						;��ʼ����
	CLRWDT  				;�忴�Ź���ʱ��
	CALL    CLR_RAM			;����RAM
	CALL    SET_OPTION		;��ʼ������Ĵ���
	CALL	SET_TOUCH_OPTION
	CALL	SET_MAIN_T0
#if SET_UART_ENABLE	   	   	   	   	;���ڹ����Ƿ�ʹ��
   	CALL   	SET_UART_9600BPS
#else
#endif
	NOP
	NOP
MAIN_LOOP:					;P17�����жϻ���
	CLRWDT  				;�忴�Ź���ʱ��
	CALL	SCAN_TOUCH
	JBSET   TIME_FG			;ÿ2MS����һ��
	GOTO	MAIN_LOOP
MAIN_LOOP_2MS:
  	BCLR	TIME_FG
  	CALL	SCAN_LED

;;---------------------------
#if SET_UART_ENABLE	   	   	   	   	   	;���ڹ����Ƿ�ʹ��
   	CALL   	SCAN_UART_OUT  	   	   	   	;��������ӳ���
   	JBCLR  	UART_ON_FG
   	GOTO   	MAIN_LOOP
   	CALL   	OPEN_OUT_UART  	   	   	   	;�����������
#else
#endif
;;---------------------------

   	MOVAR  	TOUCH_FLAG
   	JBSET	_Z
   	GOTO   	MAIN_LOOP
   	JBCLR  	WAKEUP_FG
   	GOTO   	MAIN_LOOP
;;---------------------------------------------------------
#if TOUCH_SLEEP_FG==0  	   	   	   	;�Ƿ���Ҫ���ѹ���
   	GOTO   	MAIN_LOOP
#else
MAIN_SLEEP:
	MOVAI  	00000000B
	ANDRA  	TKCR0  	   	   	   	   	;TK��������,BIT7=1����TK,BIT6=1��������ŵ�,BIT5/4ΪTKʱ���˲�,BIT3:TK��Ƶ,BIT2-0:TK��Ƶ��ѡ��
   	MOVAI   00000000B  	   	   	   	;ʹ���жϷ���
   	MOVRA   INTECON	   	   	   	   	;BIT7=T2IE,BIT6=LVDIE,BIT5=ADIE,BIT4=KBIE,BIT3=INT1,BIT2=INT0IE,BIT1=T1IE,BIT0=T0IE
   	BSET   	GIE
   	MOVAI   0x00
   	MOVRA   INTFLAG	   	   	   	   	;���жϷ�����־
   	NOP
   	NOP
   	STOP
   	NOP
   	NOP
   	MOVAI   00000001B  	   	   	   	;ʹ���жϷ���
   	MOVRA   INTECON	   	   	   	   	;BIT7=T2IE,BIT6=LVDIE,BIT5=ADIE,BIT4=KBIE,BIT3=INT1,BIT2=INT0IE,BIT1=T1IE,BIT0=T0IE
   	BSET   	GIE
   	MOVAI   0x00
   	MOVRA   INTFLAG	   	   	   	   	;���жϷ�����־
   	JBCLR  	TO
   	GOTO   	START
WDT_WAKEUP:
   	CLRWDT 	   	   	   	   	   	   	;�忴�Ź�
   	CALL   	SET_TOUCH_OPTION2
   	GOTO   	MAIN_LOOP
#endif
;;;**********************************************************************************************************
;;;**********************************************************************************************************
	GOTO   	START
;;;========================================================
	END
;;;========================================================