;;;****************************************************************************
;;;****************************************************************************
;;;****************************************************************************
;; ��������
;; ��ʼ����������: 				CALL	SET_TOUCH_OPTION
;; �������:					CALL	SCAN_TOUCH
;;--------------------------

;-------------------------------------------------------------------------------------
SET_TOUCH_OPTION:
   	MOVAI   TOUCH_KEY				;00001111B
   	MOVRA   P1ADCR 	   				;�趨��Ӧ��TK��Ϊ�����ֹ��ܣ�1Ϊ�����ֹ���
   	ORRA	DDR1					;ֻ�趨TK��Ϊ����ģʽ���������䡣����/�����1Ϊ���룬0Ϊ���
	MOVRA	TOUCH_FLAG
	SWAPR	TOUCH_FLAG				;����Ӧ��TK ʹ�ܴ�����Ҫˢ�»�׼���ݣ�TOUCH_NEW_FLAG��
	BCLR	T2IE					;����ҪT2�жϣ�TK����ɨ�跽ʽ
   	MOVAI  	11001000B  	   			;��ʱ��0����,BIT7Ϊ��ʱ��2����,BIT6Ϊ��ʱ��2����/���μ���ģʽ,BIT4-3:ʱ��Դѡ��,BIT0-2:��ʱ����Ƶ
   	ORRA   	T2CR   	   			   	;����T2��ʱ��������Ϊ���μ�ʱģʽ
   	MOVAI  	00000000B
   	MOVRA  	TKCR0					;TK��������,BIT7=1����TK,BIT6=1��������ŵ�,BIT5/4ΪTKʱ���˲�,BIT3:TK��Ƶ,BIT2-0:TK��Ƶ��ѡ��
   	MOVAI   11111111B  	   	   	   	;ѡ��ͨ��0
   	MOVRA  	TKCR2  	   	   	   	   	;TK��������,BIT7=1ʹ��TK����,BIT6:TKM�����ж�,BIT2/0:ѡ������ͨ��
SET_TOUCH_OPTION2:					;���߻��Ѻ������趨��������
   	CLRR	TOUCH_SCAN_LIST
   	CLRR	TOUCH_SCAN_TONE
   	CLRR   	TOUCH_DEBOUNCE1
   	CLRR   	TOUCH_DEBOUNCE2
   	CLRR   	TOUCH_DEBOUNCE3
   	CLRR   	TOUCH_DEBOUNCE4
   	BCLR	TK_SCANEND_FG			;����TK��ɨ�����
   	BSET   	WAKEUP_FG  	   	   	   	;���Ź�����
	RETURN
;-------------------------------------------------------------------------------------
SCAN_TOUCH:
	MOVAR  	TOUCH_SCAN_LIST	   	   	;ɨ�败���Ĳ���
	ANDAI  	0X03
	ADDRA  	PCL
	GOTO   	SCAN_TOUCH_STEP1   	   	;�趨ɨ��ͨ����ɨ�����������������
	GOTO   	SCAN_TOUCH_STEP2   	   	;�ȴ�����������ɣ��������Ӳ�
	GOTO   	SCAN_TOUCH_STEP3   	   	;����ÿ��ͨ���Ķ������˲���������,ȷ���Ƿ񴥷���������
	CLRR	TOUCH_SCAN_LIST
;	GOTO   	SCAN_TOUCH_STEP1   	   	;�趨ɨ��ͨ����ɨ�����������������
;;---------------------------------------------------------
SCAN_TOUCH_STEP1:
   	MOVAR  	TOUCH_SCAN_TONE	   	   	;ɨ��ͨ����
   	ANDAI  	0X03
   	ADDRA  	PCL
#if SET_TOUCH0_ENABLE  	   	   	   	;��0���������Ƿ�ʹ��
   	GOTO   	SCAN_TOUCH_STEP1_TONE0
#else
#endif
#if SET_TOUCH1_ENABLE  	   	   	   	;��1���������Ƿ�ʹ��
   	GOTO   	SCAN_TOUCH_STEP1_TONE1
#else
#endif
#if SET_TOUCH2_ENABLE  	   	   	   	;��2���������Ƿ�ʹ��
   	GOTO   	SCAN_TOUCH_STEP1_TONE2
#else
#endif
#if SET_TOUCH3_ENABLE  	   	   	   	;��3���������Ƿ�ʹ��
   	GOTO   	SCAN_TOUCH_STEP1_TONE3
#else
#endif
;;---------------------------
#if SET_TOUCH0_ENABLE  	   	   	   	;��0���������Ƿ�ʹ��
SCAN_TOUCH_STEP1_TONE0:
   	MOVAI   00000001B  		 	  	;1-���,0-����
	ORRA	DDR1   	   	   			;����Ӧ�Ĵ���ͨ��(TK0-P10��Ϊ�����
	ORRA	P1ADCR 	   	   	   	   	;����Ӧ�Ĵ���ͨ��(TK0-P10���ر����ֹ���
   	MOVAI   00000000B  	   	   	   	;ѡ��ͨ��0
   	MOVRA  	TKCR1  	   	   	   	   	;TK��������,BIT7=1ʹ��TK����,BIT6:TKM�����ж�,BIT2/0:ѡ������ͨ��
   	BCLR	START_TK_FG
   	JBCLR	TOUCH_NEW_FLAG_0
   	BSET	START_TK_FG
	MOVAI	SET_SENS_LEVEL0
	GOTO	SCAN_TOUCH_STEP1_NEXT
#else
#endif
#if SET_TOUCH1_ENABLE  	   	   	   	;��1���������Ƿ�ʹ��
SCAN_TOUCH_STEP1_TONE1:
	MOVAI   00000010B  		 	  	;1-���,0-����
	ORRA	DDR1   	   	   			;����Ӧ�Ĵ���ͨ��(TK0-P10��Ϊ�����
	ORRA	P1ADCR 	   	   	   	   	;����Ӧ�Ĵ���ͨ��(TK0-P10���ر����ֹ���
	MOVAI   00000001B  	   	   	   	;ѡ��ͨ��0
	MOVRA  	TKCR1  	   	   	   	   	;TK��������,BIT7=1ʹ��TK����,BIT6:TKM�����ж�,BIT2/0:ѡ������ͨ��
	BCLR	START_TK_FG
	JBCLR	TOUCH_NEW_FLAG_1
	BSET	START_TK_FG
	MOVAI	SET_SENS_LEVEL1
	GOTO	SCAN_TOUCH_STEP1_NEXT
#else
#endif
#if SET_TOUCH2_ENABLE  	   	   	   	;��2���������Ƿ�ʹ��
SCAN_TOUCH_STEP1_TONE2:
	MOVAI   00000100B  		 	  	;1-���,0-����
	ORRA	DDR1   	   	   			;����Ӧ�Ĵ���ͨ��(TK0-P10��Ϊ�����
	ORRA	P1ADCR 	   	   	   	   	;����Ӧ�Ĵ���ͨ��(TK0-P10���ر����ֹ���
	MOVAI   00000010B  	   	   	   	;ѡ��ͨ��0
	MOVRA  	TKCR1  	   	   	   	   	;TK��������,BIT7=1ʹ��TK����,BIT6:TKM�����ж�,BIT2/0:ѡ������ͨ��
	BCLR	START_TK_FG
	JBCLR	TOUCH_NEW_FLAG_2
	BSET	START_TK_FG
	MOVAI	SET_SENS_LEVEL2
	GOTO	SCAN_TOUCH_STEP1_NEXT
#else
#endif
#if SET_TOUCH3_ENABLE  	   	   	   	;��3���������Ƿ�ʹ��
SCAN_TOUCH_STEP1_TONE3:
	MOVAI   00001000B  		 	  	;1-���,0-����
	ORRA	DDR1   	   	   			;����Ӧ�Ĵ���ͨ��(TK0-P10��Ϊ�����
	ORRA	P1ADCR 	   	   	   	   	;����Ӧ�Ĵ���ͨ��(TK0-P10���ر����ֹ���
	MOVAI   00000011B  	   	   	   	;ѡ��ͨ��0
	MOVRA  	TKCR1  	   	   	   	   	;TK��������,BIT7=1ʹ��TK����,BIT6:TKM�����ж�,BIT2/0:ѡ������ͨ��
	BCLR	START_TK_FG
	JBCLR	TOUCH_NEW_FLAG_3
	BSET	START_TK_FG
	MOVAI	SET_SENS_LEVEL3
	GOTO	SCAN_TOUCH_STEP1_NEXT
#else
#endif
;;---------------------------
SCAN_TOUCH_STEP1_NEXT:
	MOVRA  	T2CNTH 	   	   			;�趨��ʱ��0����ֵ(16λ�ߵ�ַ)
	MOVRA  	T2LOADH	   	   			;�趨��ʱ��0��װ����ֵ(16λ�ߵ�ַ)
	MOVAI   250
	MOVRA  	T2CNTL 	   	   			;�趨��ʱ��0����ֵ(16λ�͵�ַ)
	MOVRA  	T2LOADL	   	   			;�趨��ʱ��0��װ����ֵ(16λ�͵�ַ)

	CLRR   	TKCNTH
	CLRR   	TKCNTL 	   	   	   	   	;��TOUCH����,�����ֹ�����
	MOVAI  	11001000B
	ORRA   	TKCR0  	   	   	   	   	;TK��������,BIT7=1����TK,BIT6=1��������ŵ�,BIT5/4ΪTKʱ���˲�,BIT3:TK��Ƶ,BIT2-0:TK��Ƶ��ѡ��
	BSET   	TKCON					;��ʼ���ݳ�ŵ�
	BSET   	TKEN
	BSET   	T2EN
	MOVAI  	0X01
	MOVRA  	TOUCH_SCAN_LIST
	RETURN
;;---------------------------------------------------------
SCAN_TOUCH_STEP2:
	JBSET  	T2IF
	RETURN
	BCLR   	T2IF   	   	   	   	   	;�����������

	MOVAR  	TKCNTH
	MOVRA  	TKCNTH_NEW
	MOVAR  	TKCNTL
	MOVRA  	TKCNTL_NEW
	BCLR   	TKCON
	CLRR   	TKCNTH
	CLRR   	TKCNTL					;��TOUCH����,�����ֹ�����

	MOVAI   TOUCH_KEY  	   			;I/O�����ֹ����趨,0����Ч
	XORAI	00001111B
	ANDRA  	P1ADCR					;�趨��Ӧ��TK��Ϊ���ֹ��ܣ�0Ϊ���ֹ���
	ANDRA	DDR1   	   	   			;����Ӧ�Ĵ���ͨ��(TK0-TK3��Ϊ�����
	MOVAI  	0X02
	MOVRA  	TOUCH_SCAN_LIST
	RETURN
;;---------------------------------------------------------
SCAN_TOUCH_STEP3:
	JBCLR  	START_TK_FG					;������ǰһ��ʱ�䣬���Բ��������ݲ�ֵ
	GOTO   	SCAN_TOUCH_STEP3_SAVE
   	MOVAR  	TKCNTL_NEW

   	MOVAR  	TOUCH_SCAN_TONE	   	   	   	;ɨ��ͨ����
   	ANDAI  	0X07
   	ADDRA  	PCL
#if SET_TOUCH0_ENABLE					;��0���������Ƿ�ʹ��
   	GOTO   	SCAN_TOUCH_STEP3_TONE0
#else
#endif
#if SET_TOUCH1_ENABLE					;��1���������Ƿ�ʹ��
   	GOTO   	SCAN_TOUCH_STEP3_TONE1
#else
#endif
#if SET_TOUCH2_ENABLE					;��2���������Ƿ�ʹ��
   	GOTO   	SCAN_TOUCH_STEP3_TONE2
#else
#endif
#if SET_TOUCH3_ENABLE					;��3���������Ƿ�ʹ��
   	GOTO   	SCAN_TOUCH_STEP3_TONE3
#else
#endif
#if SET_TOUCH0_ENABLE					;��0���������Ƿ�ʹ��
SCAN_TOUCH_STEP3_TONE0:
   	MOVAR  	TKCNT0_SAVEH
   	MOVRA  	TKCNTL_OLD_TEMPH
   	MOVAR  	TKCNT0_SAVEL
   	MOVRA  	TKCNTL_OLD_TEMPL   	   	   	;�ѱ�������ͨ���Ķ���ֵ��ȡ����
   	MOVAI  	SET_TOUCH0_PRE_LEVEL   	   	;�������µķ�ֵ
   	MOVRA  	TOUCH_TEMP1
   	MOVAI  	SET_TOUCH0_RELEA_LEVEL 	   	;�����뿪�ķ�ֵ
   	MOVRA  	TOUCH_TEMP2
   	MOVAI  	00000001B
   	MOVRA  	TOUCH_TEMP3	   	   	   	   	;��Ӧ����ͨ��0
   	MOVAI  	SET_TOUCH0_DEBOUNCEC   	   	;ͨ�������������,���������ٴ���Ӧ����Ϊ��Ч
   	MOVRA  	TOUCH_TEMP4
   	MOVAR  	TKCNT0_BASEL
   	MOVRA  	TOUCH_TEMP5
   	MOVAR  	TKCNT0_BASEH
   	MOVRA  	TOUCH_TEMP6
   	GOTO   	SCAN_TOUCH_STEP3_CHECK
#else
#endif
#if SET_TOUCH1_ENABLE					;��1���������Ƿ�ʹ��
SCAN_TOUCH_STEP3_TONE1:
   	MOVAR  	TKCNT1_SAVEH
   	MOVRA  	TKCNTL_OLD_TEMPH
   	MOVAR  	TKCNT1_SAVEL
   	MOVRA  	TKCNTL_OLD_TEMPL   	   	   	;�ѱ�������ͨ���Ķ���ֵ��ȡ����
   	MOVAI  	SET_TOUCH1_PRE_LEVEL   	   	;�������µķ�ֵ
   	MOVRA  	TOUCH_TEMP1
   	MOVAI  	SET_TOUCH1_RELEA_LEVEL 	   	;�����뿪�ķ�ֵ
   	MOVRA  	TOUCH_TEMP2
   	MOVAI  	00000010B
   	MOVRA  	TOUCH_TEMP3	   	   	   	   	;��Ӧ����ͨ��1
   	MOVAI  	SET_TOUCH1_DEBOUNCEC   	   	;ͨ�������������,���������ٴ���Ӧ����Ϊ��Ч
   	MOVRA  	TOUCH_TEMP4
   	MOVAR  	TKCNT1_BASEL
   	MOVRA  	TOUCH_TEMP5
   	MOVAR  	TKCNT1_BASEH
   	MOVRA  	TOUCH_TEMP6
   	GOTO   	SCAN_TOUCH_STEP3_CHECK
#else
#endif
#if SET_TOUCH2_ENABLE					;��2���������Ƿ�ʹ��
SCAN_TOUCH_STEP3_TONE2:
   	MOVAR  	TKCNT2_SAVEH
   	MOVRA  	TKCNTL_OLD_TEMPH
   	MOVAR  	TKCNT2_SAVEL
   	MOVRA  	TKCNTL_OLD_TEMPL   	   	   	;�ѱ�������ͨ���Ķ���ֵ��ȡ����
   	MOVAI  	SET_TOUCH2_PRE_LEVEL   	   	;�������µķ�ֵ
   	MOVRA  	TOUCH_TEMP1
   	MOVAI  	SET_TOUCH2_RELEA_LEVEL 	   	;�����뿪�ķ�ֵ
   	MOVRA  	TOUCH_TEMP2
   	MOVAI  	00000100B
   	MOVRA  	TOUCH_TEMP3	   	   	   	   	;��Ӧ����ͨ��2
   	MOVAI  	SET_TOUCH2_DEBOUNCEC   	   	;ͨ�������������,���������ٴ���Ӧ����Ϊ��Ч
   	MOVRA  	TOUCH_TEMP4
   	MOVAR  	TKCNT2_BASEL
   	MOVRA  	TOUCH_TEMP5
   	MOVAR  	TKCNT2_BASEH
   	MOVRA  	TOUCH_TEMP6
   	GOTO   	SCAN_TOUCH_STEP3_CHECK
#else
#endif
#if SET_TOUCH3_ENABLE					;��3���������Ƿ�ʹ��
SCAN_TOUCH_STEP3_TONE3:
   	MOVAR  	TKCNT3_SAVEH
   	MOVRA  	TKCNTL_OLD_TEMPH
   	MOVAR  	TKCNT3_SAVEL
   	MOVRA  	TKCNTL_OLD_TEMPL   	   	   	;�ѱ�������ͨ���Ķ���ֵ��ȡ����
   	MOVAI  	SET_TOUCH3_PRE_LEVEL   	   	;�������µķ�ֵ
   	MOVRA  	TOUCH_TEMP1
   	MOVAI  	SET_TOUCH3_RELEA_LEVEL 	   	;�����뿪�ķ�ֵ
   	MOVRA  	TOUCH_TEMP2
   	MOVAI  	00001000B
   	MOVRA  	TOUCH_TEMP3	   	   	   	   	;��Ӧ����ͨ��3
   	MOVAI  	SET_TOUCH3_DEBOUNCEC   	   	;ͨ�������������,���������ٴ���Ӧ����Ϊ��Ч
   	MOVRA  	TOUCH_TEMP4
   	MOVAR  	TKCNT3_BASEL
   	MOVRA  	TOUCH_TEMP5
   	MOVAR  	TKCNT3_BASEH
   	MOVRA  	TOUCH_TEMP6
   	GOTO   	SCAN_TOUCH_STEP3_CHECK
#else
#endif
;;---------------------------
SCAN_TOUCH_STEP3_CHECK:
   	MOVAR  	TKCNTL_NEW
   	MOVRA  	SUB_AL
   	MOVAR  	TKCNTH_NEW
   	MOVRA  	SUB_AH
   	MOVAR  	TKCNTL_OLD_TEMPL
   	MOVRA  	SUB_BL
   	MOVAR  	TKCNTL_OLD_TEMPH
   	MOVRA  	SUB_BH
   	CALL   	SUB_2BYTE  	   	   	   	   	;�ж��¾�ֵ�Ĳ�ֵ
SCAN_TOUCH_STEP3_CHECK_MAX:
   	MOVAI  	0X70
   	ANDAR  	SUB_CH 	   	   	   	   	   	;SUB_CH/LΪ�����ݵĲ�ֵ��SUB_AH/L>SUB_BH/L��SUB_CH.7λΪ0������Ϊ1
   	JBSET  	_Z
   	GOTO   	SCAN_TOUCH_STEP3_BAD   	   	;���ݲ�ֵ����0X1000H,�����ٴ�ɨ�赱ǰ����ͨ��
;---------------------------
SCAN_TOUCH_STEP3_CHECK_NEXT:
   	JBSET  	SUB_CH,7
   	GOTO   	SCAN_TOUCH_STEP3_TORELEASE 	;��ֵС�ڻ������ֵ���뿪����������
SCAN_TOUCH_STEP3_TOPRESS:  	   	   	   	;��ֵ������ֵ�����´���������
   	MOVAI  	0X7F
   	ANDAR  	SUB_CH 	   	   	   	   	   	;SUB_CH/LΪ�����ݵĲ�ֵ��SUB_AH/L>SUB_BH/L��SUB_CH.7λΪ0������Ϊ1
   	JBSET  	_Z
   	GOTO   	SCAN_TOUCH_STEP3_PRE   	   	;���ݲ�ֵ����0X100H,���ڷ�ֵ��ȷ���а��¶���
   	MOVAR  	TOUCH_TEMP1		   	   	   	   	;�¾����ݲ�ֵ
   	RSUBAR 	SUB_CL	   	   	   	   	;(TKCNTL_OLD - TKCNTL_NEW) - TOUCH0_PRE_LEVEL ,�жϲ�ֵ�봥����ֵ��С
   	JBCLR  	_C
	GOTO   	SCAN_TOUCH_STEP3_PRE    	;��ֵ���ڷ�ֵ��ȷ���а��¶���
   	MOVAI  	SET_TOUCH_ENV_LEVEL
   	RSUBAR 	SUB_CL
   	JBCLR  	_C
	GOTO	SCAN_TOUCH_STEP3_SAVEDEBOUNCE	;��ֵ���ڻ�����ֵС�ڴ�����ֵ���������ƣ�����������һֱû�й�������ֵ��������ˢ�±���ֵ���׼ֵ
	GOTO   	SCAN_TOUCH_STEP3_NORMAL	    	;��ֵС�ڻ�����ֵ��ȥ����ֵ(TKCNTx_SAVE)���׼ֵ(TKCNTx_BASE)�Ĳ�ֵ
SCAN_TOUCH_STEP3_PRE:   	   			;��ֵ���ڵ��ڷ�ֵ������ȷ���а���
   	MOVAR  	TKCNTL_NEW
   	MOVRA  	SUB_AL
   	MOVAR  	TKCNTH_NEW
   	MOVRA  	SUB_AH
   	MOVAR  	TOUCH_TEMP5
   	MOVRA  	SUB_BL
   	MOVAR  	TOUCH_TEMP6
   	MOVRA  	SUB_BH
   	CALL   	SUB_2BYTE  	   	   	   	   	;�ж���ֵ�����ֵ�Ĳ�ֵ
   	MOVAI  	0X70
   	ANDAR  	SUB_CH 	   	   	   	   	   	;SUB_CH/LΪ�����ݵĲ�ֵ��SUB_AH/L>SUB_BH/L��SUB_CH.7λΪ0������Ϊ1
   	JBSET  	_Z
   	GOTO   	SCAN_TOUCH_STEP3_BAD	   	;���ݲ�ֵ����0X1000H,�ݶ�Ϊ����/���ж��Ƿ����µĴ���ֵԶ���ڻ���ֵ��
   	MOVAI	SET_TOUCH_ENV2_LEVEL
   	RSUBAR 	SUB_CL						;���¶���ʱ����ǰֵ(TKCNTx_NEW)���׼ֵ(TKCNTx_BASE)��ֵ���ڻ���ֵ���ڶ�����ֵ��
   	JBSET  	_C
   	GOTO   	SCAN_TOUCH_STEP3_BAD		;��ֵС���ڻ�����ֵ�����������쳣�������µ�ǰ���ݵ����ô�����־
SCAN_TOUCH_STEP3_PRE_MAX:
   	JBSET  	SUB_CH,7
	GOTO	SCAN_TOUCH_STEP3_BAD		;�µĴ���ֵԶ���ڻ���ֵ�����������쳣�������µ�ǰ���ݵ����ô�����־
SCAN_TOUCH_STEP3_PRE_NEXT:
   	CLRR   	TOUCH_DEBOUNCE1
   	INCR   	TOUCH_DEBOUNCE2	   	   	   	;ͨ�������������,���������ٴ���Ӧ����Ϊ��Ч
   	MOVAR  	TOUCH_TEMP4
   	RSUBAR 	TOUCH_DEBOUNCE2
   	JBSET  	_C
   	GOTO   	SCAN_TOUCH_STEP3_RECHECK   	;����û�д����꣬�ٴ�ɨ�赱ǰ����ͨ��
   	MOVAR  	TOUCH_TEMP3
   	ORRA   	TOUCH_FLAG 	   	   	   	   	;��Ӧ�Ĵ���ͨ����־��λ
   	GOTO   	SCAN_TOUCH_STEP3_SAVE_DATA	;����״̬��ֻˢ�±���ֵ
;----------------------------------------------------------
SCAN_TOUCH_STEP3_NORMAL:   	   	   	   	;��ֵ�ͱ���ֵ�ò�ֵ�ڻ�����ֵ��Χ�ģ�ȫ���ٱȽϱ���ֵ(TKCNTx_SAVE)���׼ֵ(TKCNTx_BASE)�Ĳ�ֵ
#if TOUCH_SLEEP_FG						;�л��ѹ���ʱ����
   	JBCLR  	WAKEUP_FG
   	GOTO	SCAN_TOUCH_STEP3_NORMAL2	;���߸ջ���ʱ����Ҫ������
#else
#endif
	INCR   	TOUCH_DEBOUNCE3
	MOVAI  	SET_TOUCH_DELAY_LEVEL		;��������Ӧʱ�䣨������������������Ӧʱ�䣬�趨ʱ���ʱ������������������������Ӧ������Ӧ��
	RSUBAR 	TOUCH_DEBOUNCE3
	JBSET  	_C
	GOTO   	SCAN_TOUCH_STEP3_RECHECK   	;����û�д����꣬�ٴ�ɨ�赱ǰ����ͨ��
	CLRR	TOUCH_DEBOUNCE3
SCAN_TOUCH_STEP3_NORMAL2:
   	MOVAR  	TKCNTL_OLD_TEMPL
   	MOVRA  	SUB_AL
   	MOVAR  	TKCNTL_OLD_TEMPH
   	MOVRA  	SUB_AH
   	MOVAR  	TOUCH_TEMP5
   	MOVRA  	SUB_BL
   	MOVAR  	TOUCH_TEMP6
   	MOVRA  	SUB_BH
   	CALL   	SUB_2BYTE  	   	   	   	   	;�ж���ֵ�����ֵ�Ĳ�ֵ
   	MOVAI  	0X70
   	ANDAR  	SUB_CH 	   	   	   	   	   	;SUB_CH/LΪ�����ݵĲ�ֵ��SUB_AH/L>SUB_BH/L��SUB_CH.7λΪ0������Ϊ1
   	JBSET  	_Z
   	GOTO   	SCAN_TOUCH_STEP3_BAD   		;���ݲ�ֵ����0X1000H,�ݶ�Ϊ����
   	MOVAR  	TOUCH_TEMP3
   	ANDAR  	TOUCH_FLAG 	   	   	   	   	;��Ӧ�Ĵ���ͨ����־��λ
   	JBCLR  	_Z
   	GOTO	SCAN_TOUCH_STEP3_NORMAL_KEYUNHOLD
SCAN_TOUCH_STEP3_NORMAL_KEYHOLD:		;������������״̬
   	MOVAI  	0X7F
   	ANDAR  	SUB_CH 	   	   	   	   	   	;SUB_CH/LΪ�����ݵĲ�ֵ��SUB_AH/L>SUB_BH/L��SUB_CH.7λΪ0������Ϊ1
   	JBSET  	_Z
   	GOTO   	SCAN_TOUCH_STEP3_SAVE_DATA 	;���ݲ�ֵ����0X100H����ڷ�ֵ��ȷ�����¶�������
   	MOVAI	SET_TOUCH_ENV2_LEVEL
   	RSUBAR 	SUB_CL						;���¶���ʱ������ֵ(TKCNTx_SAVE)����С�ڻ�׼ֵ(TKCNTx_BASE)���Ҳ�ֵ���ڻ���ֵ���ڶ�����ֵ��
   	JBSET  	_C
   	GOTO   	SCAN_TOUCH_STEP3_BAD		;��ֵС���ڻ�����ֵ������
   	JBSET  	SUB_CH,7
   	GOTO   	SCAN_TOUCH_STEP3_BAD		;����ֵ(TKCNTx_SAVE)���ڻ�׼ֵ(TKCNTx_BASE)������
   	GOTO   	SCAN_TOUCH_STEP3_SAVE_DATA	;����״̬��ֻˢ�±���ֵ
SCAN_TOUCH_STEP3_NORMAL_KEYUNHOLD:		;���������ɿ�״̬
  	GOTO   	SCAN_TOUCH_STEP3_SAVE 	   	;��ֵС���ڻ�����ֵ������������ˢ�±���ֵ(TKCNTx_SAVE)�ͻ�׼ֵ(TKCNTx_BASE)��Ȼ�����ɨ��TK
;----------------------------
SCAN_TOUCH_STEP3_SAVEDEBOUNCE:
	INCR   	TOUCH_DEBOUNCE3
#if TOUCH_SLEEP_FG						;�л��ѹ���ʱ����
	MOVAI	0X10
   	JBSET  	WAKEUP_FG
	MOVAI	0XF0
#else
	MOVAI	0XF0
#endif
	RSUBAR 	TOUCH_DEBOUNCE3
	JBSET  	_C
	GOTO   	SCAN_TOUCH_STEP3_RECHECK   	;����û�д����꣬�ٴ�ɨ�赱ǰ����ͨ��
   	GOTO   	SCAN_TOUCH_STEP3_SAVE_DATA	;����״̬��ֻˢ�±���ֵ
;----------------------------------------------------------
SCAN_TOUCH_STEP3_TORELEASE:	   	   	   	;��ֵС�ڻ������ֵ���뿪����������
   	MOVAI  	0X7F
   	ANDAR  	SUB_CH 	   	   	   	   	   	;SUB_CH/LΪ�����ݵĲ�ֵ��SUB_AH/L>SUB_BH/L��SUB_CH.7λΪ0������Ϊ1
   	JBSET  	_Z
   	GOTO   	SCAN_TOUCH_STEP3_RELEASE 	;���ݲ�ֵ����0X100H����ڷ�ֵ��ȷ���ɿ���������
   	MOVAR  	TOUCH_TEMP2		   	   	   	   	;�¾����ݲ�ֵ
   	RSUBAR 	SUB_CL	   	   		   	   	;(TKCNTL_NEW - TKCNTL_OLD) - TOUCH0_RELA_LEVEL ,�жϲ�ֵ���뿪������ֵ��С
   	JBCLR  	_C
	GOTO   	SCAN_TOUCH_STEP3_RELEASE 	;��ֵ���ڷ�ֵ��ȷ�����ɿ�����
	GOTO   	SCAN_TOUCH_STEP3_NORMAL    	;��ֵС�ڻ�����ֵ��ȥ����ֵ(TKCNTx_SAVE)���׼ֵ(TKCNTx_BASE)�Ĳ�ֵ
SCAN_TOUCH_STEP3_RELEASE:   			;��ֵ���ڵ��ڷ�ֵ������ȷ�����뿪
   	CLRR   	TOUCH_DEBOUNCE2
   	INCR   	TOUCH_DEBOUNCE1	   	   	   	;ͨ�������������,���������ٴ���Ӧ����Ϊ��Ч
   	MOVAR  	TOUCH_TEMP4
   	RSUBAR 	TOUCH_DEBOUNCE1
   	JBSET  	_C
   	GOTO   	SCAN_TOUCH_STEP3_RECHECK   	;����û�д����꣬�ٴ�ɨ�赱ǰ����ͨ��
SCAN_TOUCH_STEP3_RELEASE_SET:  	   	   	;����ȷ�����뿪
   	COMAR  	TOUCH_TEMP3
   	ANDRA  	TOUCH_FLAG 	   	   	   	   	;��Ӧ�Ĵ���ͨ����־����
   	GOTO   	SCAN_TOUCH_STEP3_SAVE_DATA	;����״̬��ֻˢ�±���ֵ
;  	GOTO   	SCAN_TOUCH_STEP3_SAVE
;;---------------------------
SCAN_TOUCH_STEP3_BAD:
   	INCR   	TOUCH_DEBOUNCE4	   	   	   	;ͨ�������������,���������ٴ���Ӧ����Ϊ��Ч
   	MOVAR  	TOUCH_TEMP4
   	RSUBAR 	TOUCH_DEBOUNCE4
   	JBSET  	_C
   	GOTO   	SCAN_TOUCH_STEP3_RECHECK   	;����û�д����꣬�ٴ�ɨ�赱ǰ����ͨ��
   	COMAR	TOUCH_TEMP3
   	ANDRA	TOUCH_FLAG					;����Ӧ��TK��־ȡ��
	SWAPAR	TOUCH_TEMP3
	ORRA	TOUCH_FLAG					;��Ӧ��TK����ɨ��TOUCH_NEW_FLAG
   	GOTO   	SCAN_TOUCH_STEP3_NEXT
;;---------------------------
SCAN_TOUCH_STEP3_RECHECK:
   	CLRR   	TOUCH_SCAN_LIST
   	RETURN
;;---------------------------
SCAN_TOUCH_STEP3_SAVE:
   	MOVAR  	TOUCH_SCAN_TONE	   	   	   	;ɨ��ͨ����
   	ANDAI  	0X03
   	ADDRA  	PCL
#if SET_TOUCH0_ENABLE  	   	   	   	;��0���������Ƿ�ʹ��
   	GOTO   	SCAN_TOUCH_STEP3_BAKTONE0
#else
#endif
#if SET_TOUCH1_ENABLE  	   	   	   	;��1���������Ƿ�ʹ��
   	GOTO   	SCAN_TOUCH_STEP3_BAKTONE1
#else
#endif
#if SET_TOUCH2_ENABLE  	   	   	   	;��2���������Ƿ�ʹ��
   	GOTO   	SCAN_TOUCH_STEP3_BAKTONE2
#else
#endif
#if SET_TOUCH3_ENABLE  	   	   	   	;��3���������Ƿ�ʹ��
   	GOTO   	SCAN_TOUCH_STEP3_BAKTONE3
#else
#endif
;---------------------------
SCAN_TOUCH_STEP3_SAVE_DATA:	   	   	   	;���浱ǰ��������
   	MOVAR  	TOUCH_SCAN_TONE	   	   	   	;ɨ��ͨ����
   	ANDAI  	0X03
   	ADDRA  	PCL
#if SET_TOUCH0_ENABLE  	   	   	   	;��0���������Ƿ�ʹ��
   	GOTO   	SCAN_TOUCH_STEP3_SAVETONE0
#else
#endif
#if SET_TOUCH1_ENABLE  	   	   	   	;��1���������Ƿ�ʹ��
   	GOTO   	SCAN_TOUCH_STEP3_SAVETONE1
#else
#endif
#if SET_TOUCH2_ENABLE  	   	   	   	;��2���������Ƿ�ʹ��
   	GOTO   	SCAN_TOUCH_STEP3_SAVETONE2
#else
#endif
#if SET_TOUCH3_ENABLE  	   	   	   	;��3���������Ƿ�ʹ��
   	GOTO   	SCAN_TOUCH_STEP3_SAVETONE3
#else
#endif
;---------------------------
#if SET_TOUCH0_ENABLE  	   	   	   	   	;��0���������Ƿ�ʹ��
SCAN_TOUCH_STEP3_BAKTONE0:
   	MOVAR  	TKCNTL_NEW
   	MOVRA  	TKCNT0_BASEL
   	MOVAR  	TKCNTH_NEW
   	MOVRA  	TKCNT0_BASEH
   	BCLR	TOUCH_NEW_FLAG_0
SCAN_TOUCH_STEP3_SAVETONE0:
   	MOVAR  	TKCNTL_NEW
   	MOVRA  	TKCNT0_SAVEL
   	MOVAR  	TKCNTH_NEW
   	MOVRA  	TKCNT0_SAVEH
   	GOTO   	SCAN_TOUCH_STEP3_NEXT
#else
#endif
#if SET_TOUCH1_ENABLE  	   	   	   	   	;��1���������Ƿ�ʹ��
SCAN_TOUCH_STEP3_BAKTONE1:
   	MOVAR  	TKCNTL_NEW
   	MOVRA  	TKCNT1_BASEL
   	MOVAR  	TKCNTH_NEW
   	MOVRA  	TKCNT1_BASEH
   	BCLR	TOUCH_NEW_FLAG_1
SCAN_TOUCH_STEP3_SAVETONE1:
   	MOVAR  	TKCNTL_NEW
   	MOVRA  	TKCNT1_SAVEL
   	MOVAR  	TKCNTH_NEW
   	MOVRA  	TKCNT1_SAVEH
   	GOTO   	SCAN_TOUCH_STEP3_NEXT
#else
#endif
#if SET_TOUCH2_ENABLE  	   	   	   	   	;��2���������Ƿ�ʹ��
SCAN_TOUCH_STEP3_BAKTONE2:
   	MOVAR  	TKCNTL_NEW
   	MOVRA  	TKCNT2_BASEL
   	MOVAR  	TKCNTH_NEW
   	MOVRA  	TKCNT2_BASEH
   	BCLR	TOUCH_NEW_FLAG_2
SCAN_TOUCH_STEP3_SAVETONE2:
   	MOVAR  	TKCNTL_NEW
   	MOVRA  	TKCNT2_SAVEL
   	MOVAR  	TKCNTH_NEW
   	MOVRA  	TKCNT2_SAVEH
   	GOTO   	SCAN_TOUCH_STEP3_NEXT
#else
#endif
#if SET_TOUCH3_ENABLE  	   	   	   	   	;��3���������Ƿ�ʹ��
SCAN_TOUCH_STEP3_BAKTONE3:
   	MOVAR  	TKCNTL_NEW
   	MOVRA  	TKCNT3_BASEL
   	MOVAR  	TKCNTH_NEW
   	MOVRA  	TKCNT3_BASEH
   	BCLR	TOUCH_NEW_FLAG_3
SCAN_TOUCH_STEP3_SAVETONE3:
   	MOVAR  	TKCNTL_NEW
   	MOVRA  	TKCNT3_SAVEL
   	MOVAR  	TKCNTH_NEW
   	MOVRA  	TKCNT3_SAVEH
   	GOTO   	SCAN_TOUCH_STEP3_NEXT
#else
#endif
;---------------------------
SCAN_TOUCH_STEP3_NEXT:
   	INCR   	TOUCH_SCAN_TONE				;ɨ����һͨ���������д�������ʱ��Ϊ�������ֹ����
   	MOVAI	TOUCH_KEY_NUM
   	RSUBAR	TOUCH_SCAN_TONE
   	JBSET	C
   	GOTO	SCAN_TOUCH_STEP3_NEXT1
#if TOUCH_SLEEP_FG					;�л��ѹ���ʱ����
   	BSET	TK_SCANEND_FG			;����TK��ɨ�����
#else
   	BSET	TK_SCANEND_FG			;����TK��ɨ�����
   	CLRR	TOUCH_SCAN_TONE
#endif
SCAN_TOUCH_STEP3_NEXT1:
   	CLRR   	TOUCH_DEBOUNCE1
   	CLRR   	TOUCH_DEBOUNCE2
   	CLRR   	TOUCH_DEBOUNCE3
   	CLRR   	TOUCH_DEBOUNCE4
	CLRR	TOUCH_SCAN_LIST

#if TOUCH_SLEEP_FG					;�л��ѹ���ʱ����
   	MOVAI  	TOUCH_KEY_NUM
   	RSUBAR 	TOUCH_SCAN_TONE
   	JBSET  	_C
   	RETURN
   	CLRR	TOUCH_SCAN_TONE
   	JBSET  	WAKEUP_FG
   	RETURN
   	BCLR   	WAKEUP_FG
#else
#endif
   	RETURN
;------------------------------------------------
SUB_2BYTE: 	   	   	   	   	   	   	   	;�����ӳ���SUB_AH/L-SUB_BH/L=SUB_CH/L)(������2������������15BIT)
;SUB_AH/LΪ��������/��8λ��SUB_BH/LΪ������/��8λ����ֵ����SUB_CH/L����SUB_CH-bit7Ϊ��ʱ��ʾ�����������������Ϊ1ʱ��ʾ�����������
;�����������0XFF������0XFFΪ����ֵ
   	BCLR   	_C
   	MOVAR  	SUB_BL
   	RSUBAR 	SUB_AL
   	MOVRA  	SUB_CL
   	MOVAR  	SUB_BH
   	RSBCAR 	SUB_AH
   	MOVRA  	SUB_CH
   	BCLR   	SUB_CH,7   	   	   	   	   	;SUB_CH/LΪ�����ݵĲ�ֵ��SUB_AH/L>SUB_BH/L��SUB_CH.7λΪ0������Ϊ1
   	JBCLR  	_C
   	RETURN
   	MOVAR  	SUB_AL
   	RSUBAR 	SUB_BL
   	MOVRA  	SUB_CL
   	MOVAR  	SUB_AH
   	RSBCAR 	SUB_BH
   	MOVRA  	SUB_CH
   	BSET   	SUB_CH,7   	   	   	   	   	;SUB_CH/LΪ�����ݵĲ�ֵ��SUB_AH/L>SUB_BH/L��SUB_CH.7λΪ0������Ϊ1
   	RETURN
;**********************************************************************************************************

