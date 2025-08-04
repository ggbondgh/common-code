//;****************************************************************************
//;****************************************************************************
//;ʹ�õ������ӳ������SRAM��ȫ�ֱ�����
//extern unsigned char CTOUCH_FLAG;    	   	   	   	   	   	//��Ӧ�ĸ�����ͨ������������Ӧ��λ��1���ʾ�д���)
//�������SRAM����
unsigned char CSAVE_ACC;
unsigned char CSAVE_STATUS;
unsigned char CPLAY_FLAG;

#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long int
#define uint8_t  unsigned char
#define uint16_t unsigned int
#define uint32_t unsigned long int


#define	SAVE_ACC   	   	_CSAVE_ACC
#define	SAVE_STATUS	   	_CSAVE_STATUS
#define	PLAY_FLAG  	   	_CPLAY_FLAG



//===============Define  Flag===============
typedef union {
   	unsigned char byte;
   	struct
   	{
   	   	u8 bit0 : 1;
   	   	u8 bit1 : 1;
   	   	u8 bit2 : 1;
   	   	u8 bit3 : 1;
   	   	u8 bit4 : 1;
   	   	u8 bit5 : 1;
   	   	u8 bit6 : 1;
   	   	u8 bit7 : 1;
   	}bits;
}bit_flag;

volatile bit_flag flag1;
volatile bit_flag flag2;
volatile bit_flag flag3;



//-----------------------------------------------
#define	   	PIN_LED1   	   	P14D   	   	   	   	   	//;LED1�����

#define	   	OFF	   	   	   	0
#define	   	ON 	   	   	   	1

//;-----------------------------------------------
#define	   	SET_UART_ENABLE	   	0  	   	   	   	   	//;���ڹ����Ƿ�ʹ��
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
//void TOUCH_Init(void);
//void SET_TOUCH_OPTION(void);
//void SET_TOUCH_OPTION2(void);
//void SCAN_TOUCH(void);
//void TK_SLEEP(void);
//void TOUCH_TK0_OUT(void);



//;****************************************************************************
//;****************************************************************************
