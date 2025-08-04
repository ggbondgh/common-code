//;****************************************************************************
//; 触摸标准程序调用的SRAM定义
//;****************************************************************************
//#ifndef MC30P8160_TKSRAM_H
//#define MC30P8160_TKSRAM_H
//;;---------------------------------------------
//;;触摸功能没有使用时取消定义
unsigned char CTOUCH_SCAN_LIST;	   	   	   	   	   	//;扫描TOUCH步骤顺序
unsigned char CTOUCH_SCAN_TONE;	   	   	   	   	   	//;扫描触摸通道顺序
unsigned char CTOUCH_DEBOUNCE1;	   	   	   	   	   	//;触摸按下消抖计数
unsigned char CTOUCH_DEBOUNCE2;	   	   	   	   	   	//;触摸松开消抖计数
unsigned char CTOUCH_DEBOUNCE3;	   	   	   	   	   	//;触摸环境消抖计数
unsigned char CTOUCH_DEBOUNCE4;	   	   	   	   	   	//;触摸环境消抖计数
unsigned char CTKCNTL_NEW;
unsigned char CTKCNTH_NEW; 	   	   	   	   	   	   	//;刚扫描到的触摸计数值
unsigned char CTOUCH_FLAG;  	   	   	   	   	   	   	//;对应哪个触摸通道被触发（相应的位置1则表示有触摸)
unsigned char CTOUCH_TEMP1;	   	   	   	   	   	   	//;暂存
unsigned char CTOUCH_TEMP2;	   	   	   	   	   	   	//;暂存
unsigned char CTOUCH_TEMP3;	   	   	   	   	   	   	//;暂存
unsigned char CTOUCH_TEMP4;	   	   	   	   	   	   	//;暂存
unsigned char CTOUCH_TEMP5;	   	   	   	   	   	   	//;暂存
unsigned char CTOUCH_TEMP6;	   	   	   	   	   	   	//;暂存
//;;---------------------------------------------
unsigned char CTKCNT0_SAVEH;   	   	   	   	   	   	//;触摸按键0是否使能;没有使用时取消定义
unsigned char CTKCNT0_SAVEL;
unsigned char CTKCNT0_BASEH;
unsigned char CTKCNT0_BASEL;
//;;---------------------------------------------
unsigned char CTKCNT1_SAVEH;   	   	   	   	   	   	//;触摸按键1是否使能;没有使用时取消定义
unsigned char CTKCNT1_SAVEL;
unsigned char CTKCNT1_BASEH;
unsigned char CTKCNT1_BASEL;
//;;---------------------------------------------
unsigned char CTKCNT2_SAVEH;   	   	   	   	   	   	//;触摸按键2是否使能;没有使用时取消定义
unsigned char CTKCNT2_SAVEL;
unsigned char CTKCNT2_BASEH;
unsigned char CTKCNT2_BASEL;
//;;---------------------------------------------
unsigned char CTKCNT3_SAVEH;   	   	   	   	   	   	//;触摸按键3是否使能;没有使用时取消定义
unsigned char CTKCNT3_SAVEL;
unsigned char CTKCNT3_BASEH;
unsigned char CTKCNT3_BASEL;

//;****************************************************************************
//;使用到其它子程序定义的SRAM（全局变量）
//主程序的SRAM定义
extern unsigned char CSAVE_ACC;
extern unsigned char CSAVE_STATUS;
extern unsigned char CPLAY_FLAG;
extern unsigned char CTEMP0;
extern unsigned char CTEMP1;  	   	   	   	   	   	   	   	   	   	//TEMP1-TEMP6这6个寄存器在TK子程序中也有借用，注意
extern unsigned char CTEMP2;
extern unsigned char CTEMP3;
extern unsigned char CTEMP4;
extern unsigned char CTEMP5;
extern unsigned char CTEMP6;
extern unsigned char CTEMP7;

#define	SAVE_ACC   	   	_CSAVE_ACC
#define	SAVE_STATUS	   	_CSAVE_STATUS
#define	PLAY_FLAG  	   	_CPLAY_FLAG
#define	TEMP0			_CTEMP0
#define	TEMP1  	   	   	_CTEMP1	
#define	TEMP2  	   	   	_CTEMP2
#define	TEMP3  	   	   	_CTEMP3
#define	TEMP4  	   	   	_CTEMP4
#define	TEMP5  	   	   	_CTEMP5
#define	TEMP6  	   	   	_CTEMP6
#define	TEMP7  	   	   	_CTEMP7

//;****************************************************************************
#define	   	TOUCH_SCAN_LIST	   	    _CTOUCH_SCAN_LIST  	   	   	   	   	   	;扫描TOUCH步骤顺序
#define	   	TOUCH_SCAN_TONE	   	    _CTOUCH_SCAN_TONE  	   	   	   	   	   	;扫描触摸通道顺序
#define	   	TOUCH_DEBOUNCE1	   	    _CTOUCH_DEBOUNCE1  	   	   	   	   	   	;触摸按下消抖计数
#define	   	TOUCH_DEBOUNCE2	   	    _CTOUCH_DEBOUNCE2  	   	   	   	   	   	;触摸松开消抖计数
#define	   	TOUCH_DEBOUNCE3	   	    _CTOUCH_DEBOUNCE3  	   	   	   	   	   	;触摸环境消抖计数
#define	   	TOUCH_DEBOUNCE4	   	    _CTOUCH_DEBOUNCE4  	   	   	   	   	   	;触摸环境消抖计数
#define	   	TKCNTL_NEW              _CTKCNTL_NEW
#define	   	TKCNTH_NEW 	   	   	    _CTKCNTH_NEW   	   	   	   	   	   	   	;刚扫描到的触摸计数值
#define	   	TOUCH_FLAG 	   	   	    _CTOUCH_FLAG   	   	   	   	   	   	   	;对应哪个触摸通道被触发（相应的位置1则表示有触摸)
#define	   	TOUCH_FLAG_0			_CTOUCH_FLAG,0  	   	   	   	   	   	;对应哪个触摸通道被触发（相应的位置1则表示有触摸)
#define	   	TOUCH_FLAG_1			_CTOUCH_FLAG,1  	   	   	   	   	   	;对应哪个触摸通道被触发（相应的位置1则表示有触摸)
#define	   	TOUCH_FLAG_2			_CTOUCH_FLAG,2  	   	   	   	   	   	;对应哪个触摸通道被触发（相应的位置1则表示有触摸)
#define	   	TOUCH_FLAG_3			_CTOUCH_FLAG,3  	   	   	   	   	   	;对应哪个触摸通道被触发（相应的位置1则表示有触摸)
#define	   	TOUCH_NEW_FLAG_0		_CTOUCH_FLAG,4							;对应哪个触摸通道被触发（相应的位置1则表示有触摸)
#define	   	TOUCH_NEW_FLAG_1		_CTOUCH_FLAG,5							;对应哪个触摸通道被触发（相应的位置1则表示有触摸)
#define	   	TOUCH_NEW_FLAG_2		_CTOUCH_FLAG,6							;对应哪个触摸通道被触发（相应的位置1则表示有触摸)
#define	   	TOUCH_NEW_FLAG_3		_CTOUCH_FLAG,7							;对应哪个触摸通道被触发（相应的位置1则表示有触摸)

//;;-----------------------------------------------
#define	   	TOUCH_TEMP1	   	   	    _CTOUCH_TEMP1  	   	   	   	   	   	   	;暂存
#define	   	TOUCH_TEMP2	   	   	    _CTOUCH_TEMP2  	   	   	   	   	   	   	;暂存
#define	   	TOUCH_TEMP3	   	   	    _CTOUCH_TEMP3  	   	   	   	   	   	   	;暂存
#define	   	TOUCH_TEMP4	   	   	    _CTOUCH_TEMP4  	   	   	   	   	   	   	;暂存
#define	   	TOUCH_TEMP5	   	   	    _CTOUCH_TEMP5  	   	   	   	   	   	   	;暂存
#define	   	TOUCH_TEMP6	   	   	    _CTOUCH_TEMP6  	   	   	   	   	   	   	;暂存
//;;-----------------------------------------------
#define	   	TKCNT0_SAVEH   	   	    _CTKCNT0_SAVEH     	   	   	   	   	   	;触摸按键0是否使能;没有使用时取消定义
#define	   	TKCNT0_SAVEL            _CTKCNT0_SAVEL
#define	   	TKCNT0_BASEH            _CTKCNT0_BASEH
#define	   	TKCNT0_BASEL            _CTKCNT0_BASEL
//;;-----------------------------------------------
#define	   	TKCNT1_SAVEH   	   	    _CTKCNT1_SAVEH     	   	   	   	   	   	;触摸按键1是否使能;没有使用时取消定义
#define	   	TKCNT1_SAVEL            _CTKCNT1_SAVEL
#define	   	TKCNT1_BASEH            _CTKCNT1_BASEH
#define	   	TKCNT1_BASEL            _CTKCNT1_BASEL
//;;-----------------------------------------------
#define	   	TKCNT2_SAVEH   	   	    _CTKCNT2_SAVEH     	   	   	   	   	   	;触摸按键2是否使能;没有使用时取消定义
#define	   	TKCNT2_SAVEL            _CTKCNT2_SAVEL
#define	   	TKCNT2_BASEH            _CTKCNT2_BASEH
#define	   	TKCNT2_BASEL            _CTKCNT2_BASEL
//;;-----------------------------------------------
#define	   	TKCNT3_SAVEH   	   	    _CTKCNT3_SAVEH     	   	   	   	   	   	;触摸按键3是否使能;没有使用时取消定义
#define	   	TKCNT3_SAVEL            _CTKCNT3_SAVEL
#define	   	TKCNT3_BASEH            _CTKCNT3_BASEH
#define	   	TKCNT3_BASEL            _CTKCNT3_BASEL
//;;---------------------------------------------
#define	   	START_TK_FG    	PLAY_FLAG,0	   	   	//;上电启动标志位
#define	   	WAKEUP_FG  	   	PLAY_FLAG,1	   	   	//;休眠重新唤醒标志位
#define	   	TK_SCANEND_FG  	PLAY_FLAG,2	   	   	//;TK扫描完一轮标志位

#define	   	TKCNTL_OLD_TEMPH	TEMP0			//;暂存各通道保存值
#define	   	TKCNTL_OLD_TEMPL	TEMP1			//;暂存各通道保存值
#define	   	SUB_AH 	   	   		TEMP2
#define	   	SUB_AL 	   	   		TEMP3
#define	   	SUB_BH 	   	   		TEMP4
#define	   	SUB_BL 	   	   		TEMP5
#define	   	SUB_CH 	   	   		TEMP6
#define	   	SUB_CL 	   	   		TEMP7


//;****************************************************************************
//#endif
//;****************************************************************************
