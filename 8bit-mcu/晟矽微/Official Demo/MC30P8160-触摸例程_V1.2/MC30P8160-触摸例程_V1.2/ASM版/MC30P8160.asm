#include		"MC30P8160.inc"
#include		"MC30P8160_TK.h"

#DEFINE				INTFLAG	   	INTF  	   	;8160与其它芯片的寄存器定义差异
#DEFINE				INTECON	   	INTE
#DEFINE				KBIM		P1KBCR
;;;------- 功能模块使能定义  --------------------
#DEFINE	   	   	   	SET_UART_ENABLE	   	1  	;串口功能是否使能
;;;--------- 用户数据定义------------------------
cblock    0x10
SAVE_ACC
SAVE_STATUS

PLAY_FLAG
TEMP0		;TEMP0-TEMP7在各子程序中暂时使用，退出子程序时无效
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
#DEFINE	   	   	   	PIN_UART_TX		P1,5   	   	;串口TX脚
#DEFINE	   	   	   	PIN_LED1		P1,4   	   	;LED1输出脚
;;;**********************************************
;;;**********************************************
;;;**********************************************
;中断向量表
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
#if SET_UART_ENABLE	   	   	   	   	;串口功能是否使能
#include        "MC30P8160_UART.asm"
#else
#endif
;;---------------------------------------------------------
INT_SUB:
	MOVRA	SAVE_ACC
	SWAPAR	STATUS
	MOVRA	SAVE_STATUS
	JBCLR	INTFLAG,0		;定时0中断标志
	GOTO	T0_INT
	JBCLR	T1IF			;定时1中断标志
	GOTO	T1_INT
;	JBCLR	INTFLAG,1		;按键中断标志
;	GOTO	KEY_INT
;	JBCLR	INTFLAG,2		;外部中断标志
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
	BCLR	INTFLAG,0		;清定时0中断标志
;	MOVAI   131				;定时器0没有重载器，改变周期可以改T0CR分频值或在中断里改T0CNT	
;	MOVRA	T0CNT			;清定时器0计数值
	BSET	TIME_FG
	GOTO	INT_END
;;;--------------------------
T1_INT:
	BCLR	T1IF			;清定时1中断标志
;;;----------------
#if SET_UART_ENABLE	   	   	   	   	;串口功能是否使能
   	CALL   	UART_SUB
#else
#endif
;;;----------------
	GOTO	INT_END
;;;--------------------------
;KEY_INT:
;	BCLR	INTFLAG,1		;清按键中断标志
;	GOTO	INT_END
;;;--------------------------
;PORT_INT:
;	BCLR	INTFLAG,2		;清外部中断标志
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
;清零RAM 10H~3FH
;------------------------------------------------------------------------------------------------------------
CLR_RAM:
	MOVAI	0X4F
	MOVRA	FSR
	MOVAI	0X3F
	MOVRA	0X4F			;把寄存器的数量保存到最后一个寄存器上
CLR_RAM_LOOP:
	DECR	FSR
	CLRR	INDF
	DJZR	0X4F
	GOTO	CLR_RAM_LOOP
	RETURN
;------------------------------------------------------------------------------------------------------------
;特殊寄存器初始化
;------------------------------------------------------------------------------------------------------------
SET_OPTION:
   	MOVAI   00001111B 	   	;I/O口数字功能设定,0是有效
   	MOVRA   P1ADCR
	MOVAI   00001111B		;P10,P11,P12输出口，P14,P15输入口；1为输入，0为输出(P13只能做输入)
	MOVRA   DDR1
	MOVAI   00000000B		;P10,P11,P12输出，P14,P15输入口低电平触发
	MOVRA   P1
	
	MOVAI   0xFF			;下拉电阻,1是无效
	MOVRA   PDCON
	MOVAI   0xFF			;P14,P15开上拉电阻,P13无法设上拉、下拉，均为浮空，做输入口时最好外边加上拉电阻
	MOVRA   PUCON			;3081/6060的P13有上拉
	MOVAI   0x00			;开漏推挽,1是开漏,0是推挽
	MOVRA   ODCON

;定时器设定	
;	MOVAI   00000011B		;定时器0配置,BIT0-2:定时器分频,BIT3定时器分配:1-WDT,0-TC0
;	MOVRA   T0CR			;BIT4:0-上升沿计数1-下降沿计数,BIT5:时钟源0-FCPU,1-外部;BIT6:1-上升沿触发0-下降沿触发
;	MOVAI   6	;131
;	CLRR	T0CNT			;清定时器0计数值;T0没有自动重载器，所以计数值以256为基准，或者在中断里改变T0CNT值

	MOVAI   00000000B		;定时器1配置,BIT7=T1EN, BIT6=PWM1AOE,1允许PWM, BIT5=PWM1AEN,1使能PWM1A
	MOVRA   T1CR			;BIT4.3:T1时钟源选择,BIT2-0:T1分频
	CLRR	T1CNT			;清定时器1计数值
	CLRR	T1LOAD
	MOVAI	00000000B
	MOVRA	TMRCR			;BIT6=T0TBS,BIT3=T2IE,BIT2=T2IF,BIT1=T1IE,BIT0=T1IF
	MOVAI	00000000B
	MOVRA	PWM1CR0			;关闭PWM
	MOVAI	00000000B
	MOVRA	PWM1CR1
	MOVAI	00000000B
	MOVRA	PWM1CR2
	CLRR	T1DATA
	CLRR	T1DATB
	CLRR	T1DATC
	CLRR	T1DATD

;	MOVAI   00000010B		;定时器2配置,BIT0-2:定时器分频,BIT3定时器分配:1-WDT,0-TC0
;	MOVRA   T2CR			;BIT4:0-上升沿1-下降沿,BIT5:：
;	MOVAI   0XF0
;	MOVRA	T2CNTL			;清定时器2计数值
;	MOVRA	T2LOADL			;清定时器2计数值
;	MOVAI   0X6D
;	MOVRA	T2LOADH			;清定时器2计数值
	
	MOVAI   00000001B
	MOVRA   INTECON			;BIT7=GIE,总中断,BIT0=T0IE,BIT1=KBIE,BIT2=INT0IE,1-中断使能
	BSET	GIE
;	BSET	T0IE			;打开T0中断，必须单独设定
	MOVAI   0x00
	MOVRA   INTFLAG			;BIT0=T0IF,BIT1=KBIF,BIT2=INT0IF,1-中断发生
	MOVAI   0x00			;P14,P15,P13键盘中断功能开
	MOVRA   KBIM
	RETURN
;------------------------------------------------------------------------------------------------------------
;复位后开始处
;------------------------------------------------------------------------------------------------------------
SET_MAIN_T0:
	MOVAI   00000011B		;定时器0配置,BIT0-2:定时器分频,BIT3定时器分配:1-WDT,0-TC0
	MOVRA   T0CR			;BIT4:0-上升沿计数1-下降沿计数,BIT5:时钟源0-FCPU,1-外部;BIT6:1-上升沿触发0-下降沿触发
	CLRR	T0CNT			;清定时器0计数值;T0没有自动重载器，所以计数值以256为基准，或者在中断里改变T0CNT值
	RETURN
;----------------------------
SCAN_LED:					;处理触摸对应的输出（或其它输出口）
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
START:						;开始程序
	CLRWDT  				;清看门狗定时器
	CALL    CLR_RAM			;清零RAM
	CALL    SET_OPTION		;初始化特殊寄存器
	CALL	SET_TOUCH_OPTION
	CALL	SET_MAIN_T0
#if SET_UART_ENABLE	   	   	   	   	;串口功能是否使能
   	CALL   	SET_UART_9600BPS
#else
#endif
	NOP
	NOP
MAIN_LOOP:					;P17按键中断唤醒
	CLRWDT  				;清看门狗定时器
	CALL	SCAN_TOUCH
	JBSET   TIME_FG			;每2MS处理一次
	GOTO	MAIN_LOOP
MAIN_LOOP_2MS:
  	BCLR	TIME_FG
  	CALL	SCAN_LED

;;---------------------------
#if SET_UART_ENABLE	   	   	   	   	   	;串口功能是否使能
   	CALL   	SCAN_UART_OUT  	   	   	   	;串口输出子程序
   	JBCLR  	UART_ON_FG
   	GOTO   	MAIN_LOOP
   	CALL   	OPEN_OUT_UART  	   	   	   	;开启串口输出
#else
#endif
;;---------------------------

   	MOVAR  	TOUCH_FLAG
   	JBSET	_Z
   	GOTO   	MAIN_LOOP
   	JBCLR  	WAKEUP_FG
   	GOTO   	MAIN_LOOP
;;---------------------------------------------------------
#if TOUCH_SLEEP_FG==0  	   	   	   	;是否需要唤醒功能
   	GOTO   	MAIN_LOOP
#else
MAIN_SLEEP:
	MOVAI  	00000000B
	ANDRA  	TKCR0  	   	   	   	   	;TK触摸配置,BIT7=1开启TK,BIT6=1允许触摸充放电,BIT5/4为TK时钟滤波,BIT3:TK跳频,BIT2-0:TK振荡频率选择
   	MOVAI   00000000B  	   	   	   	;使能中断发生
   	MOVRA   INTECON	   	   	   	   	;BIT7=T2IE,BIT6=LVDIE,BIT5=ADIE,BIT4=KBIE,BIT3=INT1,BIT2=INT0IE,BIT1=T1IE,BIT0=T0IE
   	BSET   	GIE
   	MOVAI   0x00
   	MOVRA   INTFLAG	   	   	   	   	;清中断发生标志
   	NOP
   	NOP
   	STOP
   	NOP
   	NOP
   	MOVAI   00000001B  	   	   	   	;使能中断发生
   	MOVRA   INTECON	   	   	   	   	;BIT7=T2IE,BIT6=LVDIE,BIT5=ADIE,BIT4=KBIE,BIT3=INT1,BIT2=INT0IE,BIT1=T1IE,BIT0=T0IE
   	BSET   	GIE
   	MOVAI   0x00
   	MOVRA   INTFLAG	   	   	   	   	;清中断发生标志
   	JBCLR  	TO
   	GOTO   	START
WDT_WAKEUP:
   	CLRWDT 	   	   	   	   	   	   	;清看门狗
   	CALL   	SET_TOUCH_OPTION2
   	GOTO   	MAIN_LOOP
#endif
;;;**********************************************************************************************************
;;;**********************************************************************************************************
	GOTO   	START
;;;========================================================
	END
;;;========================================================