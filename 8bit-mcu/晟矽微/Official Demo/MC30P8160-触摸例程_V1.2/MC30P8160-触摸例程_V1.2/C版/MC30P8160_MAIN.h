//;****************************************************************************
//;****************************************************************************
//;ʹ�õ������ӳ������SRAM��ȫ�ֱ�����
extern unsigned char CTOUCH_FLAG;  	   	   	   	   	   	//��Ӧ�ĸ�����ͨ������������Ӧ��λ��1���ʾ�д���)
//�������SRAM����
unsigned char CSAVE_ACC;
unsigned char CSAVE_STATUS;
unsigned char CPLAY_FLAG;
unsigned char CTEMP0;  	   	   	   	   	   	   	   	   	   	//TEMP0-TEMP7��8���Ĵ�����TK�ӳ�����Ҳ�н��ã�ע���˳��������趨
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
#define	   	PIN_LED1   	   	P14D					//;LED1�����

#define	   	OFF	   	   	   	0
#define	   	ON 	   	   	   	1

//;-----------------------------------------------
#define		SET_UART_ENABLE	   	1					//;���ڹ����Ƿ�ʹ��
//;-----------------------------------------------
#define	   	P1_ADCRSET 	   	00001111B  	   	   	   	//;P1�����ֹ����趨,0����Ч
#define	   	P1_INOUT   	   	00000000B  	   	   	   	//;����P1���������״̬,1-���,0-����
#define	   	P1_UPSET   	   	00000000B  	   	   	   	//;����P1������ѡ��,1-��Ч,0-��Ч
#define	   	P1_DNSET   	   	00000000B  	   	   	   	//;����P1������ѡ��,1-��Ч,0-��Ч

//;---------- ���ڹ��ܶ���  ---------------------
//#if SET_UART_ENABLE  	   	   	   	   	//;���ڹ����Ƿ�ʹ��
#define	   	UART_ON_FG 	   	_CPLAY_FLAG,4  	   	   	//;����������־λ
#define	   	UART_END_FG	   	_CPLAY_FLAG,5  	   	   	//;���ڷ��ͽ�����־λ
//#else
//#endif

//#define  	   	SET_WAKEUP_TIME1   	   	1  	   	   	//;���Ѻ����������ߵ��ӳ�ʱ�䳤�ȣ���ѭ��������

//;****************************************************************************
//;�������õĺ���
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
