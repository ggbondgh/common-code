//;****************************************************************************
//;; 触摸标准程序调用的SRAM定义
//;****************************************************************************
#ifndef MC30P8160_TK_H
#define MC30P8160_TK_H

//;---------- 触摸按键定义  ----------------------
#define	   	TOUCH_KEY  	   	00001111B  	   	   	//;定义触摸按键使能的通道,
//;;特别注意！每个BIT对应顺序:其中BIT0为TK0,BIT1为TK1,类推至BIT3为TK3

#define	   	TOUCH_KEY_NUM  	   	4  	//;定义有效的触摸按键数量（1-4）
#define	   	SET_TOUCH3_ENABLE  	1  	//;触摸按键TK3是否使能P13
#define	   	SET_TOUCH2_ENABLE  	1  	//;触摸按键TK2是否使能P12
#define	   	SET_TOUCH1_ENABLE  	1  	//;触摸按键TK1是否使能P11
#define	   	SET_TOUCH0_ENABLE  	1  	//;触摸按键TK0是否使能P10

//;;#define	   	SET_SENS_LEVELx		0x5B   	   	//;触摸灵敏度级别
//;;特别注意！设定各个按键灵敏度，设定的SET_SENS_LEVEL值越大越灵敏，定义值以低四位为基准，高4位为此基准的倍数关系。
//;;例如定义0X89，其灵敏度会比0X88，0X79高。如要设定高于0X89的灵敏度，则应设为0X8A或0X99以上
//;;低4位取值范围建议在3-E，高4位取值范围是3-E

#define		TOUCH_SLEEP_FG 	   	   	0			//;是否需要触摸休眠唤醒,0=不休眠，非零=休眠

#define	   	SET_TOUCH_ENV_LEVEL	   	0X08   	   	//;通道环境重适应阀值（第一级）
#define		SET_TOUCH_ENV2_LEVEL  	0X10   	   	//;通道环境重适应阀值（第二级）
#define		SET_TOUCH_DELAY_LEVEL  	0X10   	   	//;触摸重适应时间（缓慢靠近按键允许响应时间，设定时间短时，缓慢靠近按键当作环境适应,不响应。设定时间长,允许缓慢靠近按键，但相应的按键响应速度会变慢）
       	   	
#define	   	SET_SENS_LEVEL0			0x55   	   	//;TK0触摸灵敏度级别
#define	   	SET_TOUCH0_PRE_LEVEL   	0X20   	   	//;通道0按下触摸通道的阀值(单独定义值)
#define	   	SET_TOUCH0_RELEA_LEVEL 	0X18   	   	//;通道0放开触摸通道的阀值
#define	   	SET_TOUCH0_DEBOUNCEC   	0X10   	   	//;通道消抖处理次数,即连续多少次响应按键为有效
       	   	
#define	   	SET_SENS_LEVEL1			0x55   	   	//;TK1触摸灵敏度级别
#define	   	SET_TOUCH1_PRE_LEVEL   	0X20   	   	//;通道1按下触摸通道的阀值(单独定义值)
#define	   	SET_TOUCH1_RELEA_LEVEL 	0X18   	   	//;通道1放开触摸通道的阀值
#define	   	SET_TOUCH1_DEBOUNCEC   	0X10   	   	//;通道消抖处理次数,即连续多少次响应按键为有效
       	   	
#define	   	SET_SENS_LEVEL2			0x55   	   	//;TK2触摸灵敏度级别
#define	   	SET_TOUCH2_PRE_LEVEL   	0X20   	   	//;通道2按下触摸通道的阀值(单独定义值)
#define	   	SET_TOUCH2_RELEA_LEVEL 	0X18   	   	//;通道2放开触摸通道的阀值
#define	   	SET_TOUCH2_DEBOUNCEC   	0X10   	   	//;通道消抖处理次数,即连续多少次响应按键为有效
       	   	
#define	   	SET_SENS_LEVEL3			0x55   	   	//;TK3触摸灵敏度级别
#define	   	SET_TOUCH3_PRE_LEVEL   	0X20   	   	//;通道3按下触摸通道的阀值(单独定义值)
#define	   	SET_TOUCH3_RELEA_LEVEL 	0X18   	   	//;通道3放开触摸通道的阀值
#define	   	SET_TOUCH3_DEBOUNCEC   	0X10   	   	//;通道消抖处理次数,即连续多少次响应按键为有效

//;****************************************************************************
#endif
//;****************************************************************************
