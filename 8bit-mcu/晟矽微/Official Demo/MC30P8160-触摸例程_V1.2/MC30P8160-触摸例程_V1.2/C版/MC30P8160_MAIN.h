//;****************************************************************************
//;****************************************************************************
//;使用到其它子程序定义的SRAM（全局变量）
extern unsigned char CTOUCH_FLAG;  	   	   	   	   	   	//对应哪个触摸通道被触发（相应的位置1则表示有触摸)
//主程序的SRAM定义
unsigned char CSAVE_ACC;
unsigned char CSAVE_STATUS;
unsigned char CPLAY_FLAG;
unsigned char CTEMP0;  	   	   	   	   	   	   	   	   	   	//TEMP0-TEMP7这8个寄存器在TK子程序中也有借用，注意退出后重新设定
unsigned char CTEMP1;
unsigned char CTEMP2;
unsigned char CTEMP3;
unsigned char CTEMP4;
unsigned char CTEMP5;
unsigned char CTEMP6;
unsigned char CTEMP7;


#define	SAVE_ACC   	   	_CSAVE_ACC
#define	SAVE_STATUS	   	_CSAVE_STATUS
#define	PLAY_FLAG  	   	_CPLAY_FLAG
#define	TEMP0  	   	   	_CTEMP0
#define	TEMP1  	   	   	_CTEMP1	
#define	TEMP2  	   	   	_CTEMP2
#define	TEMP3  	   	   	_CTEMP3
#define	TEMP4  	   	   	_CTEMP4
#define	TEMP5  	   	   	_CTEMP5
#define	TEMP6  	   	   	_CTEMP6
#define	TEMP7  	   	   	_CTEMP7
//-----------------------------------------------
#define	   	PIN_LED1   	   	P14D					//;LED1输出脚

#define	   	OFF	   	   	   	0
#define	   	ON 	   	   	   	1

//;-----------------------------------------------
#define		SET_UART_ENABLE	   	1					//;串口功能是否使能
//;-----------------------------------------------
#define	   	P1_ADCRSET 	   	00001111B  	   	   	   	//;P1口数字功能设定,0是有效
#define	   	P1_INOUT   	   	00000000B  	   	   	   	//;定义P1口输入输出状态,1-输出,0-输入
#define	   	P1_UPSET   	   	00000000B  	   	   	   	//;定义P1口上拉选择,1-有效,0-无效
#define	   	P1_DNSET   	   	00000000B  	   	   	   	//;定义P1口下拉选择,1-有效,0-无效

//;---------- 串口功能定义  ---------------------
//#if SET_UART_ENABLE  	   	   	   	   	//;串口功能是否使能
#define	   	UART_ON_FG 	   	_CPLAY_FLAG,4  	   	   	//;串口启动标志位
#define	   	UART_END_FG	   	_CPLAY_FLAG,5  	   	   	//;串口发送结束标志位
//#else
//#endif

//#define  	   	SET_WAKEUP_TIME1   	   	1  	   	   	//;唤醒后再重新休眠的延迟时间长度（主循环次数）

//;****************************************************************************
//;声明调用的函数
//;TOUCH
void SET_TOUCH_OPTION(void);
void SET_TOUCH_OPTION2(void);
void SCAN_TOUCH(void);
void TK_SLEEP(void);
void TOUCH_OUT(void);

//;UART
void SET_UART_9600BPS(void);
void UART_SUB(void);
void SCAN_UART_OUT(void);
void OPEN_OUT_UART(void);

//;****************************************************************************
//;****************************************************************************
