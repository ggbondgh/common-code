;;;**********************************************************************************************************
;;;**********************************************************************************************************
;; 串口程序
;; 波特率初始化:	CALL	SET_UART_9600BPS	;设定波特率
;; 中断调用：		CALL	UART_SUB
;; 数据刷新：		CALL	SCAN_UART_OUT
;; 重新/再次启动：	CALL	OPEN_OUT_UART
;;;**********************************************************************************************************
;;;**********************************************************************************************************
#if SET_UART_ENABLE	   	   	   	   	;串口功能是否使能

#DEFINE	   	   	   	UART_ON_FG 	   	PLAY_FLAG,4	   	   	;串口启动标志位
#DEFINE	   	   	   	UART_END_FG	   	PLAY_FLAG,5	   	   	;串口发送结束标志位
;;-----------------------------------------------
CBLOCK 	0X40
;;-----------------------------------------------
;;串口功能没有使用时取消定义
;;UART RAM、
UART_OUT_DATA  	   	   	   	   	   	;UART串口发送数据
UART_OUT_LIST  	   	   	   	   	   	;UART串口发送数据序列
UART_OUT_LIST2 	   	   	   	   	   	;UART串口发送数据序列2
UART_OUT_CHECKSUM  	   	   	   	   	;UART串口数据发送累计和
UART_OUT_COUNT 	   	   	   	   	   	;UART串口发送数据计数
UART_OUT_DATA_TEMP 	   	   	   	   	;UART串口发送数据暂存
;;-----------------------------------------------
ENDC

;;;****************************************************************************
;;;****************************************************************************
;;UART_INT:
UART_SUB:  	   	   	   	   	   	;串口通信控制
   	JBSET  	UART_ON_FG
	RETURN
   	DJZR   	UART_OUT_COUNT
   	GOTO   	UART_SUB_OUT_FG
   	JBCLR  	UART_END_FG
   	GOTO   	UART_SUB_WAIT_NEXT
   	BCLR   	PIN_UART_TX	   	   	;起始位发0
   	MOVAI  	10 	;18	   	   	   	;18为带帧数据间隔
   	MOVRA  	UART_OUT_COUNT 	   	;初始UART计数(每帧数据1起始位，8位数据，1停止位,中间再加8个0做无效数据做帧间隔)
   	MOVAR  	UART_OUT_DATA
   	MOVRA  	UART_OUT_DATA_TEMP 	;更新数据
	RETURN
UART_SUB_OUT_FG:
   	MOVAI  	2  	;10
   	RSUBAR 	UART_OUT_COUNT
   	JBSET  	C
   	GOTO   	UART_SUB_OUT_ENDBIT	;起始发0（加上8个帧间隔码）合计9个0码
UART_SUB_OUT:
   	JBSET  	UART_OUT_DATA_TEMP,0
   	GOTO   	UART_SUB_OUT_LOW
UART_SUB_OUT_HIGH:
   	BSET   	PIN_UART_TX	   	   	;发1码
   	GOTO   	UART_SUB_NEXT
UART_SUB_OUT_LOW:
   	BCLR   	PIN_UART_TX	   	   	;发0码
   	GOTO   	UART_SUB_NEXT
UART_SUB_NEXT:
   	RRR	   	UART_OUT_DATA_TEMP
	RETURN
UART_SUB_OUT_ENDBIT:
   	BSET   	PIN_UART_TX	   	   	;结束位发1
   	BSET   	UART_END_FG	   	   	;只发一次
;	RETURN
   	GOTO	SCAN_UART_OUT		;读取下一个BYTE的数据，保持数据的连续性
UART_SUB_WAIT_NEXT:
   	MOVAI  	1
   	MOVRA  	UART_OUT_COUNT
   	BSET   	PIN_UART_TX	   	   	;结束位发1
	RETURN
;;;****************************************************************************
;;;****************************************************************************
SET_UART_9600BPS:
	MOVAI   10001011B			;定时器0配置,BIT0-2:定时器分频,BIT3定时器分配:1-WDT,0-TC0
	MOVRA   T1CR				;BIT4:0-上升沿1-下降沿,BIT5:：
	MOVAI   208					;定时器1配置,BIT0-2:定时器分频,BIT3定时器分配:1-WDT,0-TC0
	MOVRA	T1CNT				;清定时器1计数值
	MOVRA	T1LOAD				;设定定时器1重装计数值
	BSET	T1IE

;	MOVAI   10001011B  	   	   	   	;定时器2配置,BIT7=T2EN,BIT4-3:时钟源选定,BIT0-2:定时器分频
;	MOVRA   T2CR
;	MOVAI   208	   	   	   	   	   	;选择HOSC时钟源，32M 16分频，单计数时间长度为1000000/(32000000/16)=0.5US,208*0.5=104US（=9600BPS）
;	MOVRA  	T2CNT  	   	   	   	   	;设定定时器1计数值
;	MOVRA   T2LOAD 	   	   	   	   	;设定定时器1重装计数值
;	BSET	T2IE
   	RETURN
;------------------------------------------------
OPEN_OUT_UART: 	   	   	   	   	   	;开启串口输出
   	JBCLR  	UART_ON_FG
   	RETURN
   	BSET   	UART_ON_FG 	   	   	   	;只发一次
   	BSET  	UART_END_FG
   	CLRR   	UART_OUT_LIST
   	CLRR   	UART_OUT_LIST2
   	CLRR   	UART_OUT_CHECKSUM
   	RETURN
;;---------------------------
SCAN_UART_OUT: 	   	   	   	   	   	;串口输出子程序
   	JBSET  	UART_ON_FG
   	RETURN
   	JBSET  	UART_END_FG
   	RETURN
   	BCLR   	UART_END_FG
SCAN_UART_OUT_LIST:	   	   	   	   	;数据格式是：0X88+0XAF+1BYTE（数据长度）+N*2BYTE（每个通道2byte的数据）+校验码（从0X88头至最后的累加和）
   	MOVAR  	UART_OUT_LIST  	   	   	;串口输出模式
   	ANDAI  	0X03
   	ADDRA  	PCL
   	GOTO   	SCAN_UART_OUT_HEAD 	   	;头码部分
   	GOTO   	SCAN_UART_OUT_DATA 	   	;数据部分
   	GOTO   	SCAN_UART_OUT_ENDCODE  	;结束码部分
   	CLRR   	UART_OUT_LIST  	   	   	;帧间隔部分，持续10个高电平时间
SCAN_UART_OUT_HEAD:
   	MOVAR  	UART_OUT_LIST2 	   	   	;串口输出模式
   	ANDAI  	0X03
   	ADDRA  	PCL
   	GOTO   	SCAN_UART_OUT_HEAD1	   	;头码 0X88
   	GOTO   	SCAN_UART_OUT_HEAD2	   	;第二BYTE码 0XA1
   	GOTO   	SCAN_UART_OUT_HEAD3	   	;第三BYTE码 为数据长度
   	CLRR   	UART_OUT_LIST2
   	MOVAI  	0X01
   	MOVRA  	UART_OUT_LIST
SCAN_UART_OUT_DATA:	
   	MOVAR  	UART_OUT_LIST2 	   	   	;串口输出模式
   	ANDAI  	0X1F					;要大于触摸通道数，这样发完通道数据后才会到“SCAN_UART_OUT_DATA_END”
   	ADDRA  	PCL
;;---------------------------
#if SET_TOUCH0_ENABLE  	   	   	   	;第0个触摸点是否使能
	GOTO   	SCAN_UART_OUT_SAVE0H
	GOTO   	SCAN_UART_OUT_SAVE0L
	GOTO   	SCAN_UART_OUT_BASE0H
	GOTO   	SCAN_UART_OUT_BASE0L
#else
#endif
#if SET_TOUCH1_ENABLE  	   	   	   	;第1个触摸点是否使能
	GOTO   	SCAN_UART_OUT_SAVE1H
	GOTO   	SCAN_UART_OUT_SAVE1L
	GOTO   	SCAN_UART_OUT_BASE1H
	GOTO   	SCAN_UART_OUT_BASE1L
#else
#endif
#if SET_TOUCH2_ENABLE  	   	   	   	;第2个触摸点是否使能
	GOTO   	SCAN_UART_OUT_SAVE2H
	GOTO   	SCAN_UART_OUT_SAVE2L
	GOTO   	SCAN_UART_OUT_BASE2H
	GOTO   	SCAN_UART_OUT_BASE2L
#else
#endif
#if SET_TOUCH3_ENABLE  	   	   	   	;第3个触摸点是否使能
	GOTO   	SCAN_UART_OUT_SAVE3H
	GOTO   	SCAN_UART_OUT_SAVE3L
	GOTO   	SCAN_UART_OUT_BASE3H
	GOTO   	SCAN_UART_OUT_BASE3L
#else
#endif
SCAN_UART_OUT_DATA_END:
   	CLRR   	UART_OUT_LIST2
   	MOVAI  	0X02
   	MOVRA  	UART_OUT_LIST
;;---------------------------
SCAN_UART_OUT_ENDCODE: 	   	   	   	;结束码部分
   	MOVAR  	UART_OUT_LIST2 	   	   	;串口输出模式
   	ANDAI  	0X03
   	ADDRA  	PCL
   	GOTO   	SCAN_UART_OUT_CHECK	   	;发校验和
;  	GOTO   	SCAN_UART_OUT_ENDBYTE  	;发送帧间隔，10个高电平周期
   	NOP
   	NOP
  	BSET   	PIN_UART_TX				;起始位发0
   	BCLR   	UART_ON_FG 	   	   	   	;结束整个发码
   	RETURN
;;---------------------------
#if SET_TOUCH0_ENABLE  	   	   	   	   	;第0个触摸点是否使能
SCAN_UART_OUT_SAVE0L:
	MOVAR  	TKCNT0_SAVEL
	GOTO   	SCAN_UART_OUTCHECKSUM
SCAN_UART_OUT_SAVE0H:
	MOVAR  	TKCNT0_SAVEH
	GOTO   	SCAN_UART_OUTCHECKSUM
SCAN_UART_OUT_BASE0L:
	MOVAR  	TKCNT0_BASEL
	GOTO   	SCAN_UART_OUTCHECKSUM
SCAN_UART_OUT_BASE0H:
	MOVAR  	TKCNT0_BASEH
	GOTO   	SCAN_UART_OUTCHECKSUM
#else
#endif
#if SET_TOUCH1_ENABLE  	   	   	   	   	;第1个触摸点是否使能
SCAN_UART_OUT_SAVE1L:
	MOVAR  	TKCNT1_SAVEL
	GOTO   	SCAN_UART_OUTCHECKSUM
SCAN_UART_OUT_SAVE1H:
	MOVAR  	TKCNT1_SAVEH
	GOTO   	SCAN_UART_OUTCHECKSUM
SCAN_UART_OUT_BASE1L:
	MOVAR  	TKCNT1_BASEL
	GOTO   	SCAN_UART_OUTCHECKSUM
SCAN_UART_OUT_BASE1H:
	MOVAR  	TKCNT1_BASEH
	GOTO   	SCAN_UART_OUTCHECKSUM
#else
#endif
#if SET_TOUCH2_ENABLE  	   	   	   	   	;第2个触摸点是否使能
SCAN_UART_OUT_SAVE2L:
	MOVAR  	TKCNT2_SAVEL
	GOTO   	SCAN_UART_OUTCHECKSUM
SCAN_UART_OUT_SAVE2H:
	MOVAR  	TKCNT2_SAVEH
	GOTO   	SCAN_UART_OUTCHECKSUM
SCAN_UART_OUT_BASE2L:
	MOVAR  	TKCNT2_BASEL
	GOTO   	SCAN_UART_OUTCHECKSUM
SCAN_UART_OUT_BASE2H:
	MOVAR  	TKCNT2_BASEH
	GOTO   	SCAN_UART_OUTCHECKSUM
#else
#endif
#if SET_TOUCH3_ENABLE  	   	   	   	   	;第3个触摸点是否使能
SCAN_UART_OUT_SAVE3L:
	MOVAR  	TKCNT3_SAVEL
	GOTO   	SCAN_UART_OUTCHECKSUM
SCAN_UART_OUT_SAVE3H:
	MOVAR  	TKCNT3_SAVEH
	GOTO   	SCAN_UART_OUTCHECKSUM
SCAN_UART_OUT_BASE3L:
	MOVAR  	TKCNT3_BASEL
	GOTO   	SCAN_UART_OUTCHECKSUM
SCAN_UART_OUT_BASE3H:
	MOVAR  	TKCNT3_BASEH
	GOTO   	SCAN_UART_OUTCHECKSUM
#else
#endif
;;---------------------------
SCAN_UART_OUT_HEAD1:   	   	   	   	   	;头码1
   	MOVAI  	0X88
   	GOTO   	SCAN_UART_OUTCHECKSUM
SCAN_UART_OUT_HEAD2:   	   	   	   	   	;头码2
   	MOVAI  	0XA1
   	GOTO   	SCAN_UART_OUTCHECKSUM
SCAN_UART_OUT_HEAD3:   	   	   	   	   	;头码3-数据长度
   	MOVAI  	TOUCH_KEY_NUM  	   	   	   	;数据总长度是触摸通道数*4
   	MOVRA  	UART_OUT_DATA
   	RLR	   	UART_OUT_DATA
   	RLR	   	UART_OUT_DATA
   	MOVAR  	UART_OUT_DATA
   	GOTO   	SCAN_UART_OUTCHECKSUM
SCAN_UART_OUT_CHECK:
   	MOVAR  	UART_OUT_CHECKSUM
   	MOVRA  	UART_OUT_DATA
   	GOTO   	SCAN_UART_OUTING
SCAN_UART_OUTCHECKSUM:
   	MOVRA  	UART_OUT_DATA
;	MOVAR  	UART_OUT_DATA
   	ADDRA  	UART_OUT_CHECKSUM  	   	   	;校验和
SCAN_UART_OUTING:
   	INCR   	UART_OUT_LIST2 	   	   	   	;发送下一BYTE
   	MOVAI  	0X01
   	MOVRA  	UART_OUT_COUNT
   	RETURN
;SCAN_UART_OUT_ENDBYTE:					;需要发送间隔码时调用
;   	INCR   	UART_OUT_LIST2 	   	   	   	;发送下一BYTE
;;  	BSET   	PIN_UART_TX	   	   	   	   	;起始位发1
;   	MOVAI  	10 	   	   	   	   	   	   	;10个帧数据间隔
;   	MOVRA  	UART_OUT_COUNT 	   	   	   	;直接赋UART计数
;   	MOVAI  	0XFF
;   	MOVRA  	UART_OUT_DATA
;   	MOVRA  	UART_OUT_DATA_TEMP 	   	   	;持续发送高电平
;   	RETURN
;;;****************************************************************************
#else  	   	   	   	   	   	   	   	;串口功能是否使能
#endif
;;;**********************************************************************************************************
