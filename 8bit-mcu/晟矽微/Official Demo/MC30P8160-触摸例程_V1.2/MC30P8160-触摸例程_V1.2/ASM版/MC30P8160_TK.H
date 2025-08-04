;;;****************************************************************************
;; 触摸标准程序调用的SRAM定义
;;;****************************************************************************
#DEFINE		_TKCON				TKCON
#DEFINE		_TKEN				TKEN
#DEFINE		_T0EN				T0EN
#DEFINE		_T0IF				T0IF
#DEFINE		_C					C
#DEFINE		_Z					Z

cblock    0x20
;;-----------------------------------------------
TKCNT0_SAVEH   	   	   	   	   	   	;触摸按键0是否使能;没有使用时取消定义
TKCNT0_SAVEL
TKCNT0_BASEH
TKCNT0_BASEL

TKCNT1_SAVEH   	   	   	   	   	   	;触摸按键1是否使能;没有使用时取消定义
TKCNT1_SAVEL
TKCNT1_BASEH
TKCNT1_BASEL

TKCNT2_SAVEH   	   	   	   	   	   	;触摸按键2是否使能;没有使用时取消定义
TKCNT2_SAVEL
TKCNT2_BASEH
TKCNT2_BASEL

TKCNT3_SAVEH   	   	   	   	   	   	;触摸按键3是否使能;没有使用时取消定义
TKCNT3_SAVEL
TKCNT3_BASEH
TKCNT3_BASEL
;;-----------------------------------------------
;cblock    0x30
TOUCH_SCAN_TONE
TOUCH_SCAN_LIST
TKCNTH_NEW
TKCNTL_NEW
TOUCH_FLAG 	   	   	   	   	   	   	;对应哪个触摸通道被触发（相应的位置1则表示有触摸)
TOUCH_DEBOUNCE1	   	   	   	   	   	;触摸按下消抖计数
TOUCH_DEBOUNCE2	   	   	   	   	   	;触摸松开消抖计数
TOUCH_DEBOUNCE3	   	   	   	   	   	;触摸环境消抖计数
TOUCH_DEBOUNCE4	   	   	   	   	   	;触摸环境错误消抖计数
TOUCH_TEMP1	   	   	   	   	   	   	;暂存
TOUCH_TEMP2	   	   	   	   	   	   	;暂存
TOUCH_TEMP3	   	   	   	   	   	   	;暂存
TOUCH_TEMP4	   	   	   	   	   	   	;暂存
TOUCH_TEMP5	   	   	   	   	   	   	;暂存
TOUCH_TEMP6	   	   	   	   	   	   	;暂存

ENDC
;;-----------------------------------------------
#DEFINE	   	   	   	TKCNTL_OLD_TEMPH   	TEMP0			;暂存各通道保存值
#DEFINE	   	   	   	TKCNTL_OLD_TEMPL   	TEMP1			;暂存各通道保存值
#DEFINE	   	   	   	SUB_AH 	   	   		TEMP2
#DEFINE	   	   	   	SUB_AL 	   	   		TEMP3
#DEFINE	   	   	   	SUB_BH 	   	   		TEMP4
#DEFINE	   	   	   	SUB_BL 	   	   		TEMP5
#DEFINE	   	   	   	SUB_CH 	   	   		TEMP6
#DEFINE	   	   	   	SUB_CL 	   	   		TEMP7

#DEFINE				TOUCH_FLAG_0		TOUCH_FLAG,0
#DEFINE				TOUCH_FLAG_1		TOUCH_FLAG,1
#DEFINE				TOUCH_FLAG_2		TOUCH_FLAG,2
#DEFINE				TOUCH_FLAG_3		TOUCH_FLAG,3
#DEFINE				TOUCH_NEW_FLAG_0	TOUCH_FLAG,4
#DEFINE				TOUCH_NEW_FLAG_1	TOUCH_FLAG,5
#DEFINE				TOUCH_NEW_FLAG_2	TOUCH_FLAG,6
#DEFINE				TOUCH_NEW_FLAG_3	TOUCH_FLAG,7
;;-----------------------------------------------
#DEFINE	   	   	   	START_TK_FG		PLAY_FLAG,0	   	   	;初次启动TK扫描标志位
#DEFINE	   	   	   	WAKEUP_FG		PLAY_FLAG,1	   	   	;休眠重新唤醒标志位
#DEFINE	   	   	   	TK_SCANEND_FG	PLAY_FLAG,2	   	   	;TK扫描完一轮标志位

TOUCH_KEY  	   	   	EQU	00001111B  	   	   				;定义触摸按键使能的通道,
TOUCH_KEY_NUM  	   	EQU	4  	   	   	   	   				;定义有效的触摸按键数量（0-3）
#DEFINE	   	   	   	SET_TOUCH3_ENABLE  		1 		 	;触摸按键TK3是否使能P13
#DEFINE	   	   	   	SET_TOUCH2_ENABLE  		1 		 	;触摸按键TK2是否使能P12
#DEFINE	   	   	   	SET_TOUCH1_ENABLE  		1  			;触摸按键TK1是否使能P11
#DEFINE	   	   	   	SET_TOUCH0_ENABLE  		1  			;触摸按键TK0是否使能P10

#DEFINE	   	   	   	TOUCH_SLEEP_FG 	   	   	1  	   	   	;是否需要触摸休眠唤醒,0=不休眠，非零=休眠
;;-----------------------------------------------
#DEFINE	   	   	   	SET_TOUCH_ENV_LEVEL	   	0X10   	   	;通道环境重适应阀值（第一级）
#DEFINE	   	   	   	SET_TOUCH_ENV2_LEVEL  	0X20   	   	;通道环境重适应阀值（第二级）
#DEFINE	   	   	   	SET_TOUCH_DELAY_LEVEL  	0X20   	   	;触摸重适应时间（缓慢靠近按键允许响应时间，设定时间短时，缓慢靠近按键当作环境适应,不响应。设定时间长,允许缓慢靠近按键，但相应的按键响应速度会变慢）

#DEFINE	   	   	   	SET_SENS_LEVEL0			0xEE   	   	;TK0触摸灵敏度级别
#DEFINE	   	   	   	SET_TOUCH0_PRE_LEVEL   	0X80   	   	;通道0按下触摸通道的阀值(单独定义值)
#DEFINE	   	   	   	SET_TOUCH0_RELEA_LEVEL 	0X80   	   	;通道0放开触摸通道的阀值
#DEFINE	   	   	   	SET_TOUCH0_DEBOUNCEC   	0X10   	   	;通道消抖处理次数,即连续多少次响应按键为有效

#DEFINE	   	   	   	SET_SENS_LEVEL1			0xEE   	   	;TK1触摸灵敏度级别
#DEFINE	   	   	   	SET_TOUCH1_PRE_LEVEL   	0X80   	   	;通道1按下触摸通道的阀值(单独定义值)
#DEFINE	   	   	   	SET_TOUCH1_RELEA_LEVEL 	0X80   	   	;通道1放开触摸通道的阀值
#DEFINE	   	   	   	SET_TOUCH1_DEBOUNCEC   	0X10   	   	;通道消抖处理次数,即连续多少次响应按键为有效

#DEFINE	   	   	   	SET_SENS_LEVEL2			0xEE   	   	;TK2触摸灵敏度级别
#DEFINE	   	   	   	SET_TOUCH2_PRE_LEVEL   	0X80   	   	;通道2按下触摸通道的阀值(单独定义值)
#DEFINE	   	   	   	SET_TOUCH2_RELEA_LEVEL 	0X80   	   	;通道2放开触摸通道的阀值
#DEFINE	   	   	   	SET_TOUCH2_DEBOUNCEC   	0X10   	   	;通道消抖处理次数,即连续多少次响应按键为有效

#DEFINE	   	   	   	SET_SENS_LEVEL3			0xEE  	   	;TK3触摸灵敏度级别
#DEFINE	   	   	   	SET_TOUCH3_PRE_LEVEL   	0X80   	   	;通道3按下触摸通道的阀值(单独定义值)
#DEFINE	   	   	   	SET_TOUCH3_RELEA_LEVEL 	0X80   	   	;通道3放开触摸通道的阀值
#DEFINE	   	   	   	SET_TOUCH3_DEBOUNCEC   	0X10   	   	;通道消抖处理次数,即连续多少次响应按键为有效
