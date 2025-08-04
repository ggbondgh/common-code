;;;****************************************************************************
;;;****************************************************************************
;;;****************************************************************************
;; 触摸程序
;; 初始化触摸参数: 				CALL	SET_TOUCH_OPTION
;; 调用入口:					CALL	SCAN_TOUCH
;;--------------------------

;-------------------------------------------------------------------------------------
SET_TOUCH_OPTION:
   	MOVAI   TOUCH_KEY				;00001111B
   	MOVRA   P1ADCR 	   				;设定对应的TK口为非数字功能，1为非数字功能
   	ORRA	DDR1					;只设定TK脚为输入模式，其它不变。输入/输出；1为输入，0为输出
	MOVRA	TOUCH_FLAG
	SWAPR	TOUCH_FLAG				;将对应的TK 使能触摸点要刷新基准数据（TOUCH_NEW_FLAG）
	BCLR	T2IE					;不需要T2中断，TK采用扫描方式
   	MOVAI  	11001000B  	   			;定时器0配置,BIT7为定时器2开启,BIT6为定时器2连续/单次计数模式,BIT4-3:时钟源选定,BIT0-2:定时器分频
   	ORRA   	T2CR   	   			   	;开启T2定时器，并且为单次计时模式
   	MOVAI  	00000000B
   	MOVRA  	TKCR0					;TK触摸配置,BIT7=1开启TK,BIT6=1允许触摸充放电,BIT5/4为TK时钟滤波,BIT3:TK跳频,BIT2-0:TK振荡频率选择
   	MOVAI   11111111B  	   	   	   	;选择通道0
   	MOVRA  	TKCR2  	   	   	   	   	;TK触摸配置,BIT7=1使能TK计数,BIT6:TKM计数中断,BIT2/0:选定触摸通道
SET_TOUCH_OPTION2:					;休眠唤醒后重新设定触摸参数
   	CLRR	TOUCH_SCAN_LIST
   	CLRR	TOUCH_SCAN_TONE
   	CLRR   	TOUCH_DEBOUNCE1
   	CLRR   	TOUCH_DEBOUNCE2
   	CLRR   	TOUCH_DEBOUNCE3
   	CLRR   	TOUCH_DEBOUNCE4
   	BCLR	TK_SCANEND_FG			;所有TK的扫描完成
   	BSET   	WAKEUP_FG  	   	   	   	;看门狗唤醒
	RETURN
;-------------------------------------------------------------------------------------
SCAN_TOUCH:
	MOVAR  	TOUCH_SCAN_LIST	   	   	;扫描触摸的步骤
	ANDAI  	0X03
	ADDRA  	PCL
	GOTO   	SCAN_TOUCH_STEP1   	   	;设定扫描通道和扫描参数，并开启触摸
	GOTO   	SCAN_TOUCH_STEP2   	   	;等待触摸计数完成，并屏蔽杂波
	GOTO   	SCAN_TOUCH_STEP3   	   	;分析每个通道的读数（滤波和消抖）,确认是否触发触摸按键
	CLRR	TOUCH_SCAN_LIST
;	GOTO   	SCAN_TOUCH_STEP1   	   	;设定扫描通道和扫描参数，并开启触摸
;;---------------------------------------------------------
SCAN_TOUCH_STEP1:
   	MOVAR  	TOUCH_SCAN_TONE	   	   	;扫描通道数
   	ANDAI  	0X03
   	ADDRA  	PCL
#if SET_TOUCH0_ENABLE  	   	   	   	;第0个触摸点是否使能
   	GOTO   	SCAN_TOUCH_STEP1_TONE0
#else
#endif
#if SET_TOUCH1_ENABLE  	   	   	   	;第1个触摸点是否使能
   	GOTO   	SCAN_TOUCH_STEP1_TONE1
#else
#endif
#if SET_TOUCH2_ENABLE  	   	   	   	;第2个触摸点是否使能
   	GOTO   	SCAN_TOUCH_STEP1_TONE2
#else
#endif
#if SET_TOUCH3_ENABLE  	   	   	   	;第3个触摸点是否使能
   	GOTO   	SCAN_TOUCH_STEP1_TONE3
#else
#endif
;;---------------------------
#if SET_TOUCH0_ENABLE  	   	   	   	;第0个触摸点是否使能
SCAN_TOUCH_STEP1_TONE0:
   	MOVAI   00000001B  		 	  	;1-输出,0-输入
	ORRA	DDR1   	   	   			;设相应的触摸通道(TK0-P10）为输入口
	ORRA	P1ADCR 	   	   	   	   	;设相应的触摸通道(TK0-P10）关闭数字功能
   	MOVAI   00000000B  	   	   	   	;选择通道0
   	MOVRA  	TKCR1  	   	   	   	   	;TK触摸配置,BIT7=1使能TK计数,BIT6:TKM计数中断,BIT2/0:选定触摸通道
   	BCLR	START_TK_FG
   	JBCLR	TOUCH_NEW_FLAG_0
   	BSET	START_TK_FG
	MOVAI	SET_SENS_LEVEL0
	GOTO	SCAN_TOUCH_STEP1_NEXT
#else
#endif
#if SET_TOUCH1_ENABLE  	   	   	   	;第1个触摸点是否使能
SCAN_TOUCH_STEP1_TONE1:
	MOVAI   00000010B  		 	  	;1-输出,0-输入
	ORRA	DDR1   	   	   			;设相应的触摸通道(TK0-P10）为输入口
	ORRA	P1ADCR 	   	   	   	   	;设相应的触摸通道(TK0-P10）关闭数字功能
	MOVAI   00000001B  	   	   	   	;选择通道0
	MOVRA  	TKCR1  	   	   	   	   	;TK触摸配置,BIT7=1使能TK计数,BIT6:TKM计数中断,BIT2/0:选定触摸通道
	BCLR	START_TK_FG
	JBCLR	TOUCH_NEW_FLAG_1
	BSET	START_TK_FG
	MOVAI	SET_SENS_LEVEL1
	GOTO	SCAN_TOUCH_STEP1_NEXT
#else
#endif
#if SET_TOUCH2_ENABLE  	   	   	   	;第2个触摸点是否使能
SCAN_TOUCH_STEP1_TONE2:
	MOVAI   00000100B  		 	  	;1-输出,0-输入
	ORRA	DDR1   	   	   			;设相应的触摸通道(TK0-P10）为输入口
	ORRA	P1ADCR 	   	   	   	   	;设相应的触摸通道(TK0-P10）关闭数字功能
	MOVAI   00000010B  	   	   	   	;选择通道0
	MOVRA  	TKCR1  	   	   	   	   	;TK触摸配置,BIT7=1使能TK计数,BIT6:TKM计数中断,BIT2/0:选定触摸通道
	BCLR	START_TK_FG
	JBCLR	TOUCH_NEW_FLAG_2
	BSET	START_TK_FG
	MOVAI	SET_SENS_LEVEL2
	GOTO	SCAN_TOUCH_STEP1_NEXT
#else
#endif
#if SET_TOUCH3_ENABLE  	   	   	   	;第3个触摸点是否使能
SCAN_TOUCH_STEP1_TONE3:
	MOVAI   00001000B  		 	  	;1-输出,0-输入
	ORRA	DDR1   	   	   			;设相应的触摸通道(TK0-P10）为输入口
	ORRA	P1ADCR 	   	   	   	   	;设相应的触摸通道(TK0-P10）关闭数字功能
	MOVAI   00000011B  	   	   	   	;选择通道0
	MOVRA  	TKCR1  	   	   	   	   	;TK触摸配置,BIT7=1使能TK计数,BIT6:TKM计数中断,BIT2/0:选定触摸通道
	BCLR	START_TK_FG
	JBCLR	TOUCH_NEW_FLAG_3
	BSET	START_TK_FG
	MOVAI	SET_SENS_LEVEL3
	GOTO	SCAN_TOUCH_STEP1_NEXT
#else
#endif
;;---------------------------
SCAN_TOUCH_STEP1_NEXT:
	MOVRA  	T2CNTH 	   	   			;设定定时器0计数值(16位高地址)
	MOVRA  	T2LOADH	   	   			;设定定时器0重装计数值(16位高地址)
	MOVAI   250
	MOVRA  	T2CNTL 	   	   			;设定定时器0计数值(16位低地址)
	MOVRA  	T2LOADL	   	   			;设定定时器0重装计数值(16位低地址)

	CLRR   	TKCNTH
	CLRR   	TKCNTL 	   	   	   	   	;清TOUCH读数,必须手工清零
	MOVAI  	11001000B
	ORRA   	TKCR0  	   	   	   	   	;TK触摸配置,BIT7=1开启TK,BIT6=1允许触摸充放电,BIT5/4为TK时钟滤波,BIT3:TK跳频,BIT2-0:TK振荡频率选择
	BSET   	TKCON					;开始电容充放电
	BSET   	TKEN
	BSET   	T2EN
	MOVAI  	0X01
	MOVRA  	TOUCH_SCAN_LIST
	RETURN
;;---------------------------------------------------------
SCAN_TOUCH_STEP2:
	JBSET  	T2IF
	RETURN
	BCLR   	T2IF   	   	   	   	   	;触摸计数完成

	MOVAR  	TKCNTH
	MOVRA  	TKCNTH_NEW
	MOVAR  	TKCNTL
	MOVRA  	TKCNTL_NEW
	BCLR   	TKCON
	CLRR   	TKCNTH
	CLRR   	TKCNTL					;清TOUCH读数,必须手工清零

	MOVAI   TOUCH_KEY  	   			;I/O口数字功能设定,0是有效
	XORAI	00001111B
	ANDRA  	P1ADCR					;设定对应的TK口为数字功能，0为数字功能
	ANDRA	DDR1   	   	   			;设相应的触摸通道(TK0-TK3）为输出口
	MOVAI  	0X02
	MOVRA  	TOUCH_SCAN_LIST
	RETURN
;;---------------------------------------------------------
SCAN_TOUCH_STEP3:
	JBCLR  	START_TK_FG					;启动的前一段时间，可以不考虑数据差值
	GOTO   	SCAN_TOUCH_STEP3_SAVE
   	MOVAR  	TKCNTL_NEW

   	MOVAR  	TOUCH_SCAN_TONE	   	   	   	;扫描通道数
   	ANDAI  	0X07
   	ADDRA  	PCL
#if SET_TOUCH0_ENABLE					;第0个触摸点是否使能
   	GOTO   	SCAN_TOUCH_STEP3_TONE0
#else
#endif
#if SET_TOUCH1_ENABLE					;第1个触摸点是否使能
   	GOTO   	SCAN_TOUCH_STEP3_TONE1
#else
#endif
#if SET_TOUCH2_ENABLE					;第2个触摸点是否使能
   	GOTO   	SCAN_TOUCH_STEP3_TONE2
#else
#endif
#if SET_TOUCH3_ENABLE					;第3个触摸点是否使能
   	GOTO   	SCAN_TOUCH_STEP3_TONE3
#else
#endif
#if SET_TOUCH0_ENABLE					;第0个触摸点是否使能
SCAN_TOUCH_STEP3_TONE0:
   	MOVAR  	TKCNT0_SAVEH
   	MOVRA  	TKCNTL_OLD_TEMPH
   	MOVAR  	TKCNT0_SAVEL
   	MOVRA  	TKCNTL_OLD_TEMPL   	   	   	;把保存的这个通道的读数值提取出来
   	MOVAI  	SET_TOUCH0_PRE_LEVEL   	   	;触摸按下的阀值
   	MOVRA  	TOUCH_TEMP1
   	MOVAI  	SET_TOUCH0_RELEA_LEVEL 	   	;触摸离开的阀值
   	MOVRA  	TOUCH_TEMP2
   	MOVAI  	00000001B
   	MOVRA  	TOUCH_TEMP3	   	   	   	   	;对应触摸通道0
   	MOVAI  	SET_TOUCH0_DEBOUNCEC   	   	;通道消抖处理次数,即连续多少次响应按键为有效
   	MOVRA  	TOUCH_TEMP4
   	MOVAR  	TKCNT0_BASEL
   	MOVRA  	TOUCH_TEMP5
   	MOVAR  	TKCNT0_BASEH
   	MOVRA  	TOUCH_TEMP6
   	GOTO   	SCAN_TOUCH_STEP3_CHECK
#else
#endif
#if SET_TOUCH1_ENABLE					;第1个触摸点是否使能
SCAN_TOUCH_STEP3_TONE1:
   	MOVAR  	TKCNT1_SAVEH
   	MOVRA  	TKCNTL_OLD_TEMPH
   	MOVAR  	TKCNT1_SAVEL
   	MOVRA  	TKCNTL_OLD_TEMPL   	   	   	;把保存的这个通道的读数值提取出来
   	MOVAI  	SET_TOUCH1_PRE_LEVEL   	   	;触摸按下的阀值
   	MOVRA  	TOUCH_TEMP1
   	MOVAI  	SET_TOUCH1_RELEA_LEVEL 	   	;触摸离开的阀值
   	MOVRA  	TOUCH_TEMP2
   	MOVAI  	00000010B
   	MOVRA  	TOUCH_TEMP3	   	   	   	   	;对应触摸通道1
   	MOVAI  	SET_TOUCH1_DEBOUNCEC   	   	;通道消抖处理次数,即连续多少次响应按键为有效
   	MOVRA  	TOUCH_TEMP4
   	MOVAR  	TKCNT1_BASEL
   	MOVRA  	TOUCH_TEMP5
   	MOVAR  	TKCNT1_BASEH
   	MOVRA  	TOUCH_TEMP6
   	GOTO   	SCAN_TOUCH_STEP3_CHECK
#else
#endif
#if SET_TOUCH2_ENABLE					;第2个触摸点是否使能
SCAN_TOUCH_STEP3_TONE2:
   	MOVAR  	TKCNT2_SAVEH
   	MOVRA  	TKCNTL_OLD_TEMPH
   	MOVAR  	TKCNT2_SAVEL
   	MOVRA  	TKCNTL_OLD_TEMPL   	   	   	;把保存的这个通道的读数值提取出来
   	MOVAI  	SET_TOUCH2_PRE_LEVEL   	   	;触摸按下的阀值
   	MOVRA  	TOUCH_TEMP1
   	MOVAI  	SET_TOUCH2_RELEA_LEVEL 	   	;触摸离开的阀值
   	MOVRA  	TOUCH_TEMP2
   	MOVAI  	00000100B
   	MOVRA  	TOUCH_TEMP3	   	   	   	   	;对应触摸通道2
   	MOVAI  	SET_TOUCH2_DEBOUNCEC   	   	;通道消抖处理次数,即连续多少次响应按键为有效
   	MOVRA  	TOUCH_TEMP4
   	MOVAR  	TKCNT2_BASEL
   	MOVRA  	TOUCH_TEMP5
   	MOVAR  	TKCNT2_BASEH
   	MOVRA  	TOUCH_TEMP6
   	GOTO   	SCAN_TOUCH_STEP3_CHECK
#else
#endif
#if SET_TOUCH3_ENABLE					;第3个触摸点是否使能
SCAN_TOUCH_STEP3_TONE3:
   	MOVAR  	TKCNT3_SAVEH
   	MOVRA  	TKCNTL_OLD_TEMPH
   	MOVAR  	TKCNT3_SAVEL
   	MOVRA  	TKCNTL_OLD_TEMPL   	   	   	;把保存的这个通道的读数值提取出来
   	MOVAI  	SET_TOUCH3_PRE_LEVEL   	   	;触摸按下的阀值
   	MOVRA  	TOUCH_TEMP1
   	MOVAI  	SET_TOUCH3_RELEA_LEVEL 	   	;触摸离开的阀值
   	MOVRA  	TOUCH_TEMP2
   	MOVAI  	00001000B
   	MOVRA  	TOUCH_TEMP3	   	   	   	   	;对应触摸通道3
   	MOVAI  	SET_TOUCH3_DEBOUNCEC   	   	;通道消抖处理次数,即连续多少次响应按键为有效
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
   	CALL   	SUB_2BYTE  	   	   	   	   	;判断新旧值的差值
SCAN_TOUCH_STEP3_CHECK_MAX:
   	MOVAI  	0X70
   	ANDAR  	SUB_CH 	   	   	   	   	   	;SUB_CH/L为两数据的差值，SUB_AH/L>SUB_BH/L则SUB_CH.7位为0，否则为1
   	JBSET  	_Z
   	GOTO   	SCAN_TOUCH_STEP3_BAD   	   	;数据差值超过0X1000H,错误，再次扫描当前触摸通道
;---------------------------
SCAN_TOUCH_STEP3_CHECK_NEXT:
   	JBSET  	SUB_CH,7
   	GOTO   	SCAN_TOUCH_STEP3_TORELEASE 	;旧值小于或等于新值，离开触摸的趋势
SCAN_TOUCH_STEP3_TOPRESS:  	   	   	   	;旧值大于新值，按下触摸的趋势
   	MOVAI  	0X7F
   	ANDAR  	SUB_CH 	   	   	   	   	   	;SUB_CH/L为两数据的差值，SUB_AH/L>SUB_BH/L则SUB_CH.7位为0，否则为1
   	JBSET  	_Z
   	GOTO   	SCAN_TOUCH_STEP3_PRE   	   	;数据差值超过0X100H,大于阀值，确定有按下动作
   	MOVAR  	TOUCH_TEMP1		   	   	   	   	;新旧数据差值
   	RSUBAR 	SUB_CL	   	   	   	   	;(TKCNTL_OLD - TKCNTL_NEW) - TOUCH0_PRE_LEVEL ,判断差值与触摸阀值大小
   	JBCLR  	_C
	GOTO   	SCAN_TOUCH_STEP3_PRE    	;差值大于阀值，确认有按下动作
   	MOVAI  	SET_TOUCH_ENV_LEVEL
   	RSUBAR 	SUB_CL
   	JBCLR  	_C
	GOTO	SCAN_TOUCH_STEP3_SAVEDEBOUNCE	;差值大于环境阀值小于触摸阀值，按下趋势，消抖处理，如一直没有过触摸阀值，则重新刷新保存值与基准值
	GOTO   	SCAN_TOUCH_STEP3_NORMAL	    	;差值小于环境阀值，去保存值(TKCNTx_SAVE)与基准值(TKCNTx_BASE)的差值
SCAN_TOUCH_STEP3_PRE:   	   			;差值大于等于阀值，触摸确认有按下
   	MOVAR  	TKCNTL_NEW
   	MOVRA  	SUB_AL
   	MOVAR  	TKCNTH_NEW
   	MOVRA  	SUB_AH
   	MOVAR  	TOUCH_TEMP5
   	MOVRA  	SUB_BL
   	MOVAR  	TOUCH_TEMP6
   	MOVRA  	SUB_BH
   	CALL   	SUB_2BYTE  	   	   	   	   	;判断新值与基础值的差值
   	MOVAI  	0X70
   	ANDAR  	SUB_CH 	   	   	   	   	   	;SUB_CH/L为两数据的差值，SUB_AH/L>SUB_BH/L则SUB_CH.7位为0，否则为1
   	JBSET  	_Z
   	GOTO   	SCAN_TOUCH_STEP3_BAD	   	;数据差值超过0X1000H,暂定为错误/（判断是否是新的触摸值远大于基础值）
   	MOVAI	SET_TOUCH_ENV2_LEVEL
   	RSUBAR 	SUB_CL						;按下动作时，当前值(TKCNTx_NEW)与基准值(TKCNTx_BASE)差值大于环境值（第二级阀值）
   	JBSET  	_C
   	GOTO   	SCAN_TOUCH_STEP3_BAD		;差值小于在环境阀值，（可能是异常），更新当前数据但不置触摸标志
SCAN_TOUCH_STEP3_PRE_MAX:
   	JBSET  	SUB_CH,7
	GOTO	SCAN_TOUCH_STEP3_BAD		;新的触摸值远大于基础值，（可能是异常），更新当前数据但不置触摸标志
SCAN_TOUCH_STEP3_PRE_NEXT:
   	CLRR   	TOUCH_DEBOUNCE1
   	INCR   	TOUCH_DEBOUNCE2	   	   	   	;通道消抖处理次数,即连续多少次响应按键为有效
   	MOVAR  	TOUCH_TEMP4
   	RSUBAR 	TOUCH_DEBOUNCE2
   	JBSET  	_C
   	GOTO   	SCAN_TOUCH_STEP3_RECHECK   	;消抖没有处理完，再次扫描当前触摸通道
   	MOVAR  	TOUCH_TEMP3
   	ORRA   	TOUCH_FLAG 	   	   	   	   	;对应的触摸通道标志置位
   	GOTO   	SCAN_TOUCH_STEP3_SAVE_DATA	;按下状态，只刷新保存值
;----------------------------------------------------------
SCAN_TOUCH_STEP3_NORMAL:   	   	   	   	;新值和保存值得差值在环境阀值范围的，全部再比较保存值(TKCNTx_SAVE)与基准值(TKCNTx_BASE)的差值
#if TOUCH_SLEEP_FG						;有唤醒功能时调用
   	JBCLR  	WAKEUP_FG
   	GOTO	SCAN_TOUCH_STEP3_NORMAL2	;休眠刚唤醒时不需要再消抖
#else
#endif
	INCR   	TOUCH_DEBOUNCE3
	MOVAI  	SET_TOUCH_DELAY_LEVEL		;触摸重适应时间（缓慢靠近按键允许响应时间，设定时间短时，缓慢靠近按键当作环境适应，不响应）
	RSUBAR 	TOUCH_DEBOUNCE3
	JBSET  	_C
	GOTO   	SCAN_TOUCH_STEP3_RECHECK   	;消抖没有处理完，再次扫描当前触摸通道
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
   	CALL   	SUB_2BYTE  	   	   	   	   	;判断新值与基础值的差值
   	MOVAI  	0X70
   	ANDAR  	SUB_CH 	   	   	   	   	   	;SUB_CH/L为两数据的差值，SUB_AH/L>SUB_BH/L则SUB_CH.7位为0，否则为1
   	JBSET  	_Z
   	GOTO   	SCAN_TOUCH_STEP3_BAD   		;数据差值超过0X1000H,暂定为错误
   	MOVAR  	TOUCH_TEMP3
   	ANDAR  	TOUCH_FLAG 	   	   	   	   	;对应的触摸通道标志置位
   	JBCLR  	_Z
   	GOTO	SCAN_TOUCH_STEP3_NORMAL_KEYUNHOLD
SCAN_TOUCH_STEP3_NORMAL_KEYHOLD:		;触摸按键按下状态
   	MOVAI  	0X7F
   	ANDAR  	SUB_CH 	   	   	   	   	   	;SUB_CH/L为两数据的差值，SUB_AH/L>SUB_BH/L则SUB_CH.7位为0，否则为1
   	JBSET  	_Z
   	GOTO   	SCAN_TOUCH_STEP3_SAVE_DATA 	;数据差值超过0X100H或大于阀值，确定按下动作正常
   	MOVAI	SET_TOUCH_ENV2_LEVEL
   	RSUBAR 	SUB_CL						;按下动作时，保存值(TKCNTx_SAVE)必须小于基准值(TKCNTx_BASE)，且差值大于环境值（第二级阀值）
   	JBSET  	_C
   	GOTO   	SCAN_TOUCH_STEP3_BAD		;差值小于在环境阀值，错误
   	JBSET  	SUB_CH,7
   	GOTO   	SCAN_TOUCH_STEP3_BAD		;保存值(TKCNTx_SAVE)大于基准值(TKCNTx_BASE)，错误
   	GOTO   	SCAN_TOUCH_STEP3_SAVE_DATA	;按下状态，只刷新保存值
SCAN_TOUCH_STEP3_NORMAL_KEYUNHOLD:		;触摸按键松开状态
  	GOTO   	SCAN_TOUCH_STEP3_SAVE 	   	;差值小于在环境阀值，数据正常，刷新保存值(TKCNTx_SAVE)和基准值(TKCNTx_BASE)，然后继续扫描TK
;----------------------------
SCAN_TOUCH_STEP3_SAVEDEBOUNCE:
	INCR   	TOUCH_DEBOUNCE3
#if TOUCH_SLEEP_FG						;有唤醒功能时调用
	MOVAI	0X10
   	JBSET  	WAKEUP_FG
	MOVAI	0XF0
#else
	MOVAI	0XF0
#endif
	RSUBAR 	TOUCH_DEBOUNCE3
	JBSET  	_C
	GOTO   	SCAN_TOUCH_STEP3_RECHECK   	;消抖没有处理完，再次扫描当前触摸通道
   	GOTO   	SCAN_TOUCH_STEP3_SAVE_DATA	;按下状态，只刷新保存值
;----------------------------------------------------------
SCAN_TOUCH_STEP3_TORELEASE:	   	   	   	;旧值小于或等于新值，离开触摸的趋势
   	MOVAI  	0X7F
   	ANDAR  	SUB_CH 	   	   	   	   	   	;SUB_CH/L为两数据的差值，SUB_AH/L>SUB_BH/L则SUB_CH.7位为0，否则为1
   	JBSET  	_Z
   	GOTO   	SCAN_TOUCH_STEP3_RELEASE 	;数据差值超过0X100H或大于阀值，确定松开动作正常
   	MOVAR  	TOUCH_TEMP2		   	   	   	   	;新旧数据差值
   	RSUBAR 	SUB_CL	   	   		   	   	;(TKCNTL_NEW - TKCNTL_OLD) - TOUCH0_RELA_LEVEL ,判断差值与离开触摸阀值大小
   	JBCLR  	_C
	GOTO   	SCAN_TOUCH_STEP3_RELEASE 	;差值大于阀值，确认有松开动作
	GOTO   	SCAN_TOUCH_STEP3_NORMAL    	;差值小于环境阀值，去保存值(TKCNTx_SAVE)与基准值(TKCNTx_BASE)的差值
SCAN_TOUCH_STEP3_RELEASE:   			;差值大于等于阀值，触摸确认有离开
   	CLRR   	TOUCH_DEBOUNCE2
   	INCR   	TOUCH_DEBOUNCE1	   	   	   	;通道消抖处理次数,即连续多少次响应按键为有效
   	MOVAR  	TOUCH_TEMP4
   	RSUBAR 	TOUCH_DEBOUNCE1
   	JBSET  	_C
   	GOTO   	SCAN_TOUCH_STEP3_RECHECK   	;消抖没有处理完，再次扫描当前触摸通道
SCAN_TOUCH_STEP3_RELEASE_SET:  	   	   	;触摸确认有离开
   	COMAR  	TOUCH_TEMP3
   	ANDRA  	TOUCH_FLAG 	   	   	   	   	;对应的触摸通道标志清零
   	GOTO   	SCAN_TOUCH_STEP3_SAVE_DATA	;按下状态，只刷新保存值
;  	GOTO   	SCAN_TOUCH_STEP3_SAVE
;;---------------------------
SCAN_TOUCH_STEP3_BAD:
   	INCR   	TOUCH_DEBOUNCE4	   	   	   	;通道消抖处理次数,即连续多少次响应按键为有效
   	MOVAR  	TOUCH_TEMP4
   	RSUBAR 	TOUCH_DEBOUNCE4
   	JBSET  	_C
   	GOTO   	SCAN_TOUCH_STEP3_RECHECK   	;消抖没有处理完，再次扫描当前触摸通道
   	COMAR	TOUCH_TEMP3
   	ANDRA	TOUCH_FLAG					;将对应的TK标志取消
	SWAPAR	TOUCH_TEMP3
	ORRA	TOUCH_FLAG					;相应的TK重新扫描TOUCH_NEW_FLAG
   	GOTO   	SCAN_TOUCH_STEP3_NEXT
;;---------------------------
SCAN_TOUCH_STEP3_RECHECK:
   	CLRR   	TOUCH_SCAN_LIST
   	RETURN
;;---------------------------
SCAN_TOUCH_STEP3_SAVE:
   	MOVAR  	TOUCH_SCAN_TONE	   	   	   	;扫描通道数
   	ANDAI  	0X03
   	ADDRA  	PCL
#if SET_TOUCH0_ENABLE  	   	   	   	;第0个触摸点是否使能
   	GOTO   	SCAN_TOUCH_STEP3_BAKTONE0
#else
#endif
#if SET_TOUCH1_ENABLE  	   	   	   	;第1个触摸点是否使能
   	GOTO   	SCAN_TOUCH_STEP3_BAKTONE1
#else
#endif
#if SET_TOUCH2_ENABLE  	   	   	   	;第2个触摸点是否使能
   	GOTO   	SCAN_TOUCH_STEP3_BAKTONE2
#else
#endif
#if SET_TOUCH3_ENABLE  	   	   	   	;第3个触摸点是否使能
   	GOTO   	SCAN_TOUCH_STEP3_BAKTONE3
#else
#endif
;---------------------------
SCAN_TOUCH_STEP3_SAVE_DATA:	   	   	   	;保存当前触摸读数
   	MOVAR  	TOUCH_SCAN_TONE	   	   	   	;扫描通道数
   	ANDAI  	0X03
   	ADDRA  	PCL
#if SET_TOUCH0_ENABLE  	   	   	   	;第0个触摸点是否使能
   	GOTO   	SCAN_TOUCH_STEP3_SAVETONE0
#else
#endif
#if SET_TOUCH1_ENABLE  	   	   	   	;第1个触摸点是否使能
   	GOTO   	SCAN_TOUCH_STEP3_SAVETONE1
#else
#endif
#if SET_TOUCH2_ENABLE  	   	   	   	;第2个触摸点是否使能
   	GOTO   	SCAN_TOUCH_STEP3_SAVETONE2
#else
#endif
#if SET_TOUCH3_ENABLE  	   	   	   	;第3个触摸点是否使能
   	GOTO   	SCAN_TOUCH_STEP3_SAVETONE3
#else
#endif
;---------------------------
#if SET_TOUCH0_ENABLE  	   	   	   	   	;第0个触摸点是否使能
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
#if SET_TOUCH1_ENABLE  	   	   	   	   	;第1个触摸点是否使能
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
#if SET_TOUCH2_ENABLE  	   	   	   	   	;第2个触摸点是否使能
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
#if SET_TOUCH3_ENABLE  	   	   	   	   	;第3个触摸点是否使能
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
   	INCR   	TOUCH_SCAN_TONE				;扫描下一通道，将所有触摸口暂时设为输出，防止误动作
   	MOVAI	TOUCH_KEY_NUM
   	RSUBAR	TOUCH_SCAN_TONE
   	JBSET	C
   	GOTO	SCAN_TOUCH_STEP3_NEXT1
#if TOUCH_SLEEP_FG					;有唤醒功能时调用
   	BSET	TK_SCANEND_FG			;所有TK的扫描完成
#else
   	BSET	TK_SCANEND_FG			;所有TK的扫描完成
   	CLRR	TOUCH_SCAN_TONE
#endif
SCAN_TOUCH_STEP3_NEXT1:
   	CLRR   	TOUCH_DEBOUNCE1
   	CLRR   	TOUCH_DEBOUNCE2
   	CLRR   	TOUCH_DEBOUNCE3
   	CLRR   	TOUCH_DEBOUNCE4
	CLRR	TOUCH_SCAN_LIST

#if TOUCH_SLEEP_FG					;有唤醒功能时调用
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
SUB_2BYTE: 	   	   	   	   	   	   	   	;减法子程序（SUB_AH/L-SUB_BH/L=SUB_CH/L)(适用于2个数据相差不超过15BIT)
;SUB_AH/L为被减数高/低8位，SUB_BH/L为减数高/低8位，差值存在SUB_CH/L，且SUB_CH-bit7为零时表示减法运算结果无溢出，为1时表示运算结果有溢出
;如果两数相差超过0XFF，则以0XFF为最大差值
   	BCLR   	_C
   	MOVAR  	SUB_BL
   	RSUBAR 	SUB_AL
   	MOVRA  	SUB_CL
   	MOVAR  	SUB_BH
   	RSBCAR 	SUB_AH
   	MOVRA  	SUB_CH
   	BCLR   	SUB_CH,7   	   	   	   	   	;SUB_CH/L为两数据的差值，SUB_AH/L>SUB_BH/L则SUB_CH.7位为0，否则为1
   	JBCLR  	_C
   	RETURN
   	MOVAR  	SUB_AL
   	RSUBAR 	SUB_BL
   	MOVRA  	SUB_CL
   	MOVAR  	SUB_AH
   	RSBCAR 	SUB_BH
   	MOVRA  	SUB_CH
   	BSET   	SUB_CH,7   	   	   	   	   	;SUB_CH/L为两数据的差值，SUB_AH/L>SUB_BH/L则SUB_CH.7位为0，否则为1
   	RETURN
;**********************************************************************************************************

