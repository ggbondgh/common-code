;;;**********************************************************************************************************
;;;**********************************************************************************************************
;; ���ڳ���
;; �����ʳ�ʼ��:	CALL	SET_UART_9600BPS	;�趨������
;; �жϵ��ã�		CALL	UART_SUB
;; ����ˢ�£�		CALL	SCAN_UART_OUT
;; ����/�ٴ�������	CALL	OPEN_OUT_UART
;;;**********************************************************************************************************
;;;**********************************************************************************************************
#if SET_UART_ENABLE	   	   	   	   	;���ڹ����Ƿ�ʹ��

#DEFINE	   	   	   	UART_ON_FG 	   	PLAY_FLAG,4	   	   	;����������־λ
#DEFINE	   	   	   	UART_END_FG	   	PLAY_FLAG,5	   	   	;���ڷ��ͽ�����־λ
;;-----------------------------------------------
CBLOCK 	0X40
;;-----------------------------------------------
;;���ڹ���û��ʹ��ʱȡ������
;;UART RAM��
UART_OUT_DATA  	   	   	   	   	   	;UART���ڷ�������
UART_OUT_LIST  	   	   	   	   	   	;UART���ڷ�����������
UART_OUT_LIST2 	   	   	   	   	   	;UART���ڷ�����������2
UART_OUT_CHECKSUM  	   	   	   	   	;UART�������ݷ����ۼƺ�
UART_OUT_COUNT 	   	   	   	   	   	;UART���ڷ������ݼ���
UART_OUT_DATA_TEMP 	   	   	   	   	;UART���ڷ��������ݴ�
;;-----------------------------------------------
ENDC

;;;****************************************************************************
;;;****************************************************************************
;;UART_INT:
UART_SUB:  	   	   	   	   	   	;����ͨ�ſ���
   	JBSET  	UART_ON_FG
	RETURN
   	DJZR   	UART_OUT_COUNT
   	GOTO   	UART_SUB_OUT_FG
   	JBCLR  	UART_END_FG
   	GOTO   	UART_SUB_WAIT_NEXT
   	BCLR   	PIN_UART_TX	   	   	;��ʼλ��0
   	MOVAI  	10 	;18	   	   	   	;18Ϊ��֡���ݼ��
   	MOVRA  	UART_OUT_COUNT 	   	;��ʼUART����(ÿ֡����1��ʼλ��8λ���ݣ�1ֹͣλ,�м��ټ�8��0����Ч������֡���)
   	MOVAR  	UART_OUT_DATA
   	MOVRA  	UART_OUT_DATA_TEMP 	;��������
	RETURN
UART_SUB_OUT_FG:
   	MOVAI  	2  	;10
   	RSUBAR 	UART_OUT_COUNT
   	JBSET  	C
   	GOTO   	UART_SUB_OUT_ENDBIT	;��ʼ��0������8��֡����룩�ϼ�9��0��
UART_SUB_OUT:
   	JBSET  	UART_OUT_DATA_TEMP,0
   	GOTO   	UART_SUB_OUT_LOW
UART_SUB_OUT_HIGH:
   	BSET   	PIN_UART_TX	   	   	;��1��
   	GOTO   	UART_SUB_NEXT
UART_SUB_OUT_LOW:
   	BCLR   	PIN_UART_TX	   	   	;��0��
   	GOTO   	UART_SUB_NEXT
UART_SUB_NEXT:
   	RRR	   	UART_OUT_DATA_TEMP
	RETURN
UART_SUB_OUT_ENDBIT:
   	BSET   	PIN_UART_TX	   	   	;����λ��1
   	BSET   	UART_END_FG	   	   	;ֻ��һ��
;	RETURN
   	GOTO	SCAN_UART_OUT		;��ȡ��һ��BYTE�����ݣ��������ݵ�������
UART_SUB_WAIT_NEXT:
   	MOVAI  	1
   	MOVRA  	UART_OUT_COUNT
   	BSET   	PIN_UART_TX	   	   	;����λ��1
	RETURN
;;;****************************************************************************
;;;****************************************************************************
SET_UART_9600BPS:
	MOVAI   10001011B			;��ʱ��0����,BIT0-2:��ʱ����Ƶ,BIT3��ʱ������:1-WDT,0-TC0
	MOVRA   T1CR				;BIT4:0-������1-�½���,BIT5:��
	MOVAI   208					;��ʱ��1����,BIT0-2:��ʱ����Ƶ,BIT3��ʱ������:1-WDT,0-TC0
	MOVRA	T1CNT				;�嶨ʱ��1����ֵ
	MOVRA	T1LOAD				;�趨��ʱ��1��װ����ֵ
	BSET	T1IE

;	MOVAI   10001011B  	   	   	   	;��ʱ��2����,BIT7=T2EN,BIT4-3:ʱ��Դѡ��,BIT0-2:��ʱ����Ƶ
;	MOVRA   T2CR
;	MOVAI   208	   	   	   	   	   	;ѡ��HOSCʱ��Դ��32M 16��Ƶ��������ʱ�䳤��Ϊ1000000/(32000000/16)=0.5US,208*0.5=104US��=9600BPS��
;	MOVRA  	T2CNT  	   	   	   	   	;�趨��ʱ��1����ֵ
;	MOVRA   T2LOAD 	   	   	   	   	;�趨��ʱ��1��װ����ֵ
;	BSET	T2IE
   	RETURN
;------------------------------------------------
OPEN_OUT_UART: 	   	   	   	   	   	;�����������
   	JBCLR  	UART_ON_FG
   	RETURN
   	BSET   	UART_ON_FG 	   	   	   	;ֻ��һ��
   	BSET  	UART_END_FG
   	CLRR   	UART_OUT_LIST
   	CLRR   	UART_OUT_LIST2
   	CLRR   	UART_OUT_CHECKSUM
   	RETURN
;;---------------------------
SCAN_UART_OUT: 	   	   	   	   	   	;��������ӳ���
   	JBSET  	UART_ON_FG
   	RETURN
   	JBSET  	UART_END_FG
   	RETURN
   	BCLR   	UART_END_FG
SCAN_UART_OUT_LIST:	   	   	   	   	;���ݸ�ʽ�ǣ�0X88+0XAF+1BYTE�����ݳ��ȣ�+N*2BYTE��ÿ��ͨ��2byte�����ݣ�+У���루��0X88ͷ�������ۼӺͣ�
   	MOVAR  	UART_OUT_LIST  	   	   	;�������ģʽ
   	ANDAI  	0X03
   	ADDRA  	PCL
   	GOTO   	SCAN_UART_OUT_HEAD 	   	;ͷ�벿��
   	GOTO   	SCAN_UART_OUT_DATA 	   	;���ݲ���
   	GOTO   	SCAN_UART_OUT_ENDCODE  	;�����벿��
   	CLRR   	UART_OUT_LIST  	   	   	;֡������֣�����10���ߵ�ƽʱ��
SCAN_UART_OUT_HEAD:
   	MOVAR  	UART_OUT_LIST2 	   	   	;�������ģʽ
   	ANDAI  	0X03
   	ADDRA  	PCL
   	GOTO   	SCAN_UART_OUT_HEAD1	   	;ͷ�� 0X88
   	GOTO   	SCAN_UART_OUT_HEAD2	   	;�ڶ�BYTE�� 0XA1
   	GOTO   	SCAN_UART_OUT_HEAD3	   	;����BYTE�� Ϊ���ݳ���
   	CLRR   	UART_OUT_LIST2
   	MOVAI  	0X01
   	MOVRA  	UART_OUT_LIST
SCAN_UART_OUT_DATA:	
   	MOVAR  	UART_OUT_LIST2 	   	   	;�������ģʽ
   	ANDAI  	0X1F					;Ҫ���ڴ���ͨ��������������ͨ�����ݺ�Żᵽ��SCAN_UART_OUT_DATA_END��
   	ADDRA  	PCL
;;---------------------------
#if SET_TOUCH0_ENABLE  	   	   	   	;��0���������Ƿ�ʹ��
	GOTO   	SCAN_UART_OUT_SAVE0H
	GOTO   	SCAN_UART_OUT_SAVE0L
	GOTO   	SCAN_UART_OUT_BASE0H
	GOTO   	SCAN_UART_OUT_BASE0L
#else
#endif
#if SET_TOUCH1_ENABLE  	   	   	   	;��1���������Ƿ�ʹ��
	GOTO   	SCAN_UART_OUT_SAVE1H
	GOTO   	SCAN_UART_OUT_SAVE1L
	GOTO   	SCAN_UART_OUT_BASE1H
	GOTO   	SCAN_UART_OUT_BASE1L
#else
#endif
#if SET_TOUCH2_ENABLE  	   	   	   	;��2���������Ƿ�ʹ��
	GOTO   	SCAN_UART_OUT_SAVE2H
	GOTO   	SCAN_UART_OUT_SAVE2L
	GOTO   	SCAN_UART_OUT_BASE2H
	GOTO   	SCAN_UART_OUT_BASE2L
#else
#endif
#if SET_TOUCH3_ENABLE  	   	   	   	;��3���������Ƿ�ʹ��
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
SCAN_UART_OUT_ENDCODE: 	   	   	   	;�����벿��
   	MOVAR  	UART_OUT_LIST2 	   	   	;�������ģʽ
   	ANDAI  	0X03
   	ADDRA  	PCL
   	GOTO   	SCAN_UART_OUT_CHECK	   	;��У���
;  	GOTO   	SCAN_UART_OUT_ENDBYTE  	;����֡�����10���ߵ�ƽ����
   	NOP
   	NOP
  	BSET   	PIN_UART_TX				;��ʼλ��0
   	BCLR   	UART_ON_FG 	   	   	   	;������������
   	RETURN
;;---------------------------
#if SET_TOUCH0_ENABLE  	   	   	   	   	;��0���������Ƿ�ʹ��
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
#if SET_TOUCH1_ENABLE  	   	   	   	   	;��1���������Ƿ�ʹ��
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
#if SET_TOUCH2_ENABLE  	   	   	   	   	;��2���������Ƿ�ʹ��
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
#if SET_TOUCH3_ENABLE  	   	   	   	   	;��3���������Ƿ�ʹ��
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
SCAN_UART_OUT_HEAD1:   	   	   	   	   	;ͷ��1
   	MOVAI  	0X88
   	GOTO   	SCAN_UART_OUTCHECKSUM
SCAN_UART_OUT_HEAD2:   	   	   	   	   	;ͷ��2
   	MOVAI  	0XA1
   	GOTO   	SCAN_UART_OUTCHECKSUM
SCAN_UART_OUT_HEAD3:   	   	   	   	   	;ͷ��3-���ݳ���
   	MOVAI  	TOUCH_KEY_NUM  	   	   	   	;�����ܳ����Ǵ���ͨ����*4
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
   	ADDRA  	UART_OUT_CHECKSUM  	   	   	;У���
SCAN_UART_OUTING:
   	INCR   	UART_OUT_LIST2 	   	   	   	;������һBYTE
   	MOVAI  	0X01
   	MOVRA  	UART_OUT_COUNT
   	RETURN
;SCAN_UART_OUT_ENDBYTE:					;��Ҫ���ͼ����ʱ����
;   	INCR   	UART_OUT_LIST2 	   	   	   	;������һBYTE
;;  	BSET   	PIN_UART_TX	   	   	   	   	;��ʼλ��1
;   	MOVAI  	10 	   	   	   	   	   	   	;10��֡���ݼ��
;   	MOVRA  	UART_OUT_COUNT 	   	   	   	;ֱ�Ӹ�UART����
;   	MOVAI  	0XFF
;   	MOVRA  	UART_OUT_DATA
;   	MOVRA  	UART_OUT_DATA_TEMP 	   	   	;�������͸ߵ�ƽ
;   	RETURN
;;;****************************************************************************
#else  	   	   	   	   	   	   	   	;���ڹ����Ƿ�ʹ��
#endif
;;;**********************************************************************************************************
