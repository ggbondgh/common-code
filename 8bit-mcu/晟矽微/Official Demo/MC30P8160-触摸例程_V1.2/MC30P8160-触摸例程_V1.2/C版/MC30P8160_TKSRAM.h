//;****************************************************************************
//; ������׼������õ�SRAM����
//;****************************************************************************
//#ifndef MC30P8160_TKSRAM_H
//#define MC30P8160_TKSRAM_H
//;;---------------------------------------------
//;;��������û��ʹ��ʱȡ������
unsigned char CTOUCH_SCAN_LIST;	   	   	   	   	   	//;ɨ��TOUCH����˳��
unsigned char CTOUCH_SCAN_TONE;	   	   	   	   	   	//;ɨ�败��ͨ��˳��
unsigned char CTOUCH_DEBOUNCE1;	   	   	   	   	   	//;����������������
unsigned char CTOUCH_DEBOUNCE2;	   	   	   	   	   	//;�����ɿ���������
unsigned char CTOUCH_DEBOUNCE3;	   	   	   	   	   	//;����������������
unsigned char CTOUCH_DEBOUNCE4;	   	   	   	   	   	//;����������������
unsigned char CTKCNTL_NEW;
unsigned char CTKCNTH_NEW; 	   	   	   	   	   	   	//;��ɨ�赽�Ĵ�������ֵ
unsigned char CTOUCH_FLAG;  	   	   	   	   	   	   	//;��Ӧ�ĸ�����ͨ������������Ӧ��λ��1���ʾ�д���)
unsigned char CTOUCH_TEMP1;	   	   	   	   	   	   	//;�ݴ�
unsigned char CTOUCH_TEMP2;	   	   	   	   	   	   	//;�ݴ�
unsigned char CTOUCH_TEMP3;	   	   	   	   	   	   	//;�ݴ�
unsigned char CTOUCH_TEMP4;	   	   	   	   	   	   	//;�ݴ�
unsigned char CTOUCH_TEMP5;	   	   	   	   	   	   	//;�ݴ�
unsigned char CTOUCH_TEMP6;	   	   	   	   	   	   	//;�ݴ�
//;;---------------------------------------------
unsigned char CTKCNT0_SAVEH;   	   	   	   	   	   	//;��������0�Ƿ�ʹ��;û��ʹ��ʱȡ������
unsigned char CTKCNT0_SAVEL;
unsigned char CTKCNT0_BASEH;
unsigned char CTKCNT0_BASEL;
//;;---------------------------------------------
unsigned char CTKCNT1_SAVEH;   	   	   	   	   	   	//;��������1�Ƿ�ʹ��;û��ʹ��ʱȡ������
unsigned char CTKCNT1_SAVEL;
unsigned char CTKCNT1_BASEH;
unsigned char CTKCNT1_BASEL;
//;;---------------------------------------------
unsigned char CTKCNT2_SAVEH;   	   	   	   	   	   	//;��������2�Ƿ�ʹ��;û��ʹ��ʱȡ������
unsigned char CTKCNT2_SAVEL;
unsigned char CTKCNT2_BASEH;
unsigned char CTKCNT2_BASEL;
//;;---------------------------------------------
unsigned char CTKCNT3_SAVEH;   	   	   	   	   	   	//;��������3�Ƿ�ʹ��;û��ʹ��ʱȡ������
unsigned char CTKCNT3_SAVEL;
unsigned char CTKCNT3_BASEH;
unsigned char CTKCNT3_BASEL;

//;****************************************************************************
//;ʹ�õ������ӳ������SRAM��ȫ�ֱ�����
//�������SRAM����
extern unsigned char CSAVE_ACC;
extern unsigned char CSAVE_STATUS;
extern unsigned char CPLAY_FLAG;
extern unsigned char CTEMP0;
extern unsigned char CTEMP1;  	   	   	   	   	   	   	   	   	   	//TEMP1-TEMP6��6���Ĵ�����TK�ӳ�����Ҳ�н��ã�ע��
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
#define	   	TOUCH_SCAN_LIST	   	    _CTOUCH_SCAN_LIST  	   	   	   	   	   	;ɨ��TOUCH����˳��
#define	   	TOUCH_SCAN_TONE	   	    _CTOUCH_SCAN_TONE  	   	   	   	   	   	;ɨ�败��ͨ��˳��
#define	   	TOUCH_DEBOUNCE1	   	    _CTOUCH_DEBOUNCE1  	   	   	   	   	   	;����������������
#define	   	TOUCH_DEBOUNCE2	   	    _CTOUCH_DEBOUNCE2  	   	   	   	   	   	;�����ɿ���������
#define	   	TOUCH_DEBOUNCE3	   	    _CTOUCH_DEBOUNCE3  	   	   	   	   	   	;����������������
#define	   	TOUCH_DEBOUNCE4	   	    _CTOUCH_DEBOUNCE4  	   	   	   	   	   	;����������������
#define	   	TKCNTL_NEW              _CTKCNTL_NEW
#define	   	TKCNTH_NEW 	   	   	    _CTKCNTH_NEW   	   	   	   	   	   	   	;��ɨ�赽�Ĵ�������ֵ
#define	   	TOUCH_FLAG 	   	   	    _CTOUCH_FLAG   	   	   	   	   	   	   	;��Ӧ�ĸ�����ͨ������������Ӧ��λ��1���ʾ�д���)
#define	   	TOUCH_FLAG_0			_CTOUCH_FLAG,0  	   	   	   	   	   	;��Ӧ�ĸ�����ͨ������������Ӧ��λ��1���ʾ�д���)
#define	   	TOUCH_FLAG_1			_CTOUCH_FLAG,1  	   	   	   	   	   	;��Ӧ�ĸ�����ͨ������������Ӧ��λ��1���ʾ�д���)
#define	   	TOUCH_FLAG_2			_CTOUCH_FLAG,2  	   	   	   	   	   	;��Ӧ�ĸ�����ͨ������������Ӧ��λ��1���ʾ�д���)
#define	   	TOUCH_FLAG_3			_CTOUCH_FLAG,3  	   	   	   	   	   	;��Ӧ�ĸ�����ͨ������������Ӧ��λ��1���ʾ�д���)
#define	   	TOUCH_NEW_FLAG_0		_CTOUCH_FLAG,4							;��Ӧ�ĸ�����ͨ������������Ӧ��λ��1���ʾ�д���)
#define	   	TOUCH_NEW_FLAG_1		_CTOUCH_FLAG,5							;��Ӧ�ĸ�����ͨ������������Ӧ��λ��1���ʾ�д���)
#define	   	TOUCH_NEW_FLAG_2		_CTOUCH_FLAG,6							;��Ӧ�ĸ�����ͨ������������Ӧ��λ��1���ʾ�д���)
#define	   	TOUCH_NEW_FLAG_3		_CTOUCH_FLAG,7							;��Ӧ�ĸ�����ͨ������������Ӧ��λ��1���ʾ�д���)

//;;-----------------------------------------------
#define	   	TOUCH_TEMP1	   	   	    _CTOUCH_TEMP1  	   	   	   	   	   	   	;�ݴ�
#define	   	TOUCH_TEMP2	   	   	    _CTOUCH_TEMP2  	   	   	   	   	   	   	;�ݴ�
#define	   	TOUCH_TEMP3	   	   	    _CTOUCH_TEMP3  	   	   	   	   	   	   	;�ݴ�
#define	   	TOUCH_TEMP4	   	   	    _CTOUCH_TEMP4  	   	   	   	   	   	   	;�ݴ�
#define	   	TOUCH_TEMP5	   	   	    _CTOUCH_TEMP5  	   	   	   	   	   	   	;�ݴ�
#define	   	TOUCH_TEMP6	   	   	    _CTOUCH_TEMP6  	   	   	   	   	   	   	;�ݴ�
//;;-----------------------------------------------
#define	   	TKCNT0_SAVEH   	   	    _CTKCNT0_SAVEH     	   	   	   	   	   	;��������0�Ƿ�ʹ��;û��ʹ��ʱȡ������
#define	   	TKCNT0_SAVEL            _CTKCNT0_SAVEL
#define	   	TKCNT0_BASEH            _CTKCNT0_BASEH
#define	   	TKCNT0_BASEL            _CTKCNT0_BASEL
//;;-----------------------------------------------
#define	   	TKCNT1_SAVEH   	   	    _CTKCNT1_SAVEH     	   	   	   	   	   	;��������1�Ƿ�ʹ��;û��ʹ��ʱȡ������
#define	   	TKCNT1_SAVEL            _CTKCNT1_SAVEL
#define	   	TKCNT1_BASEH            _CTKCNT1_BASEH
#define	   	TKCNT1_BASEL            _CTKCNT1_BASEL
//;;-----------------------------------------------
#define	   	TKCNT2_SAVEH   	   	    _CTKCNT2_SAVEH     	   	   	   	   	   	;��������2�Ƿ�ʹ��;û��ʹ��ʱȡ������
#define	   	TKCNT2_SAVEL            _CTKCNT2_SAVEL
#define	   	TKCNT2_BASEH            _CTKCNT2_BASEH
#define	   	TKCNT2_BASEL            _CTKCNT2_BASEL
//;;-----------------------------------------------
#define	   	TKCNT3_SAVEH   	   	    _CTKCNT3_SAVEH     	   	   	   	   	   	;��������3�Ƿ�ʹ��;û��ʹ��ʱȡ������
#define	   	TKCNT3_SAVEL            _CTKCNT3_SAVEL
#define	   	TKCNT3_BASEH            _CTKCNT3_BASEH
#define	   	TKCNT3_BASEL            _CTKCNT3_BASEL
//;;---------------------------------------------
#define	   	START_TK_FG    	PLAY_FLAG,0	   	   	//;�ϵ�������־λ
#define	   	WAKEUP_FG  	   	PLAY_FLAG,1	   	   	//;�������»��ѱ�־λ
#define	   	TK_SCANEND_FG  	PLAY_FLAG,2	   	   	//;TKɨ����һ�ֱ�־λ

#define	   	TKCNTL_OLD_TEMPH	TEMP0			//;�ݴ��ͨ������ֵ
#define	   	TKCNTL_OLD_TEMPL	TEMP1			//;�ݴ��ͨ������ֵ
#define	   	SUB_AH 	   	   		TEMP2
#define	   	SUB_AL 	   	   		TEMP3
#define	   	SUB_BH 	   	   		TEMP4
#define	   	SUB_BL 	   	   		TEMP5
#define	   	SUB_CH 	   	   		TEMP6
#define	   	SUB_CL 	   	   		TEMP7


//;****************************************************************************
//#endif
//;****************************************************************************
