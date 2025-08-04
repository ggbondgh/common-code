/********************************************************************************
								���㴥��
---------------------------------------------------------------------------------
ʹ�÷�����
    1.����ѭ��ǰ���ã�
    
	TK_Init();

	2.����ѭ��-��ʱ5ms-�е��ã�
	
	if(T16_5ms_Flag_TK)
	{
		T16_5ms_Flag_TK = 0;
		TK11_Scan();
		TK11_OUT_Control();
		Long_Press_Reset();
	}

	3.�ж�����Ҫ����5ms��ʱ����־λ�ǣ�T16_5ms_Flag_TK(�Ѷ���)

	4.TK11_OUT_Control������Ǵ�����Ҫִ�е�User Code��Ҳ���Խ���������ļ��б��ڸĶ�

	5.��Ҫ�Ѹ��ļ����·��ġ�extern.h�����ݼӵ�extern.h
---------------------------------------------------------------------------------
ע�⣺
	1.�����õ���Key11�������������������Ҫ�ѡ�11��ȫ���ĳ���Ӧ����
********************************************************************************/

#include	"extern.h"


#define FilterCnt_Value  8 
#define Const_SEN_T_Key11  30 //������ֵ
#define Const_SEN_T_Key11_Release  40 //�ɿ���ֵ

word u16_get_val;		//��ȡֵ
word u16_Press_val;     //���º�Ķ�ȡֵ
word u16_release_val;	//�ɿ���Ķ�ȡֵ

eword u16_TK11_environment_val_Sum = 0; //������ʱ��ȡ�ۼ�ֵ
word u16_TK11_environment_val;			//����ֵ�����ڸ����ȡֵ��
word u16_release_val_TK11 = 0;  		//���º�� ������ֵ-������ֵ��
bit  TK11_Release_Flag;

word u16_temp_val = 0;  //һ���˲��õ�����ʱ����

byte TK11_Filter_Cnt = 0;
byte TK11_Release_Cnt = 0;
byte Pre_T_Key11_Release = 1; //�ɿ�ǰ��־λ��1Ϊ�ɿ�ǰ��ⰴ�£�0Ϊ���º����ɿ�
byte FilterCnt_TK11;
word u16_get_val_Temp_TK11 = 0;

bit  T_Key11_Signal; //״̬��־λ��1Ϊ���µ�״̬��0Ϊ�ɿ���״̬

word RestCnt;	//������λ����

bit T16_5ms_Flag_TK;


void	TK_Init(void)
{
	TS   = 0b_0011_00_11; 	// IHRC/8, 0.5*VCC, 128*CLK
	TKE1 = 0b_0000_000_0;
	TKE2 = 0b_0000_000_0;

	TPS2 = 0x01; // CS ��VDD
}

void	TK_Release_(void)
{
	//�����ɿ��ļ���ֵ������ر�־λ
	TK11_Release_Cnt = 0;

	T_Key11_Signal = 0;
	Pre_T_Key11_Release = 1;					
	u16_TK11_environment_val = u16_get_val;
	TK11_Filter_Cnt = 0;
	u16_TK11_environment_val_Sum = 0;

	TK11_Release_Flag = 1;
}

void	TK11_Scan(void) //*********
{	
	TKE2 = 0b_0000_1000;	//ʹ��TK11��PB.0
	
	//��ȡ����ֵ
	$ TCC TK_RUN;
	while(A != 0x00) 
	{
		A = TCC & 0x70;
	}
	u16_get_val =  (TKCH << 8) | TKCL;

	//һ���˲�
	u16_temp_val = u16_get_val_Temp_TK11 << 2;
	u16_temp_val -= u16_get_val_Temp_TK11;
	u16_temp_val += u16_get_val;
	u16_get_val_Temp_TK11 = u16_temp_val >> 2;

	u16_get_val = u16_get_val_Temp_TK11;


	if(Pre_T_Key11_Release) //����Ƿ���
	{
		u16_Press_val = u16_get_val + Const_SEN_T_Key11;
		
		if(u16_Press_val < u16_TK11_environment_val)	 //���£�����ֵ>��ȡֵ+������ֵ
		{
		//	Const_Env_Dw_Fix_Speed = 5;

			FilterCnt_TK11 ++;
			if(FilterCnt_TK11 >= FilterCnt_Value)  //�˲�����⵽������β���Ϊ����
			{
				T_Key11_Signal = 1;
				Pre_T_Key11_Release = 0;
				u16_release_val_TK11 = u16_TK11_environment_val - Const_SEN_T_Key11; //��ȡ���������ɿ������
			}
		}
		else //���»���ֵ�������ȡֵ
		{
			FilterCnt_TK11 = 0;

			// ����ζ�ȡֵȡƽ��ֵ
			TK11_Filter_Cnt ++;
			u16_TK11_environment_val_Sum += u16_get_val; //��ȡֵ�ۼ�
			if(TK11_Filter_Cnt > 31) //�ۼ�32��
			{
				TK11_Filter_Cnt = 0;
				u16_TK11_environment_val = u16_TK11_environment_val_Sum >> 5; //����2^5=32
				u16_TK11_environment_val_Sum = 0;

				if(TK11_Release_Flag)
				{
					TK11_Release_Flag = 0;
					u16_TK11_environment_val = u16_get_val;
				}
			}

			if(TK11_Release_Flag == 1) //�ۼ���ִ�д��б�
			{
				if(u16_get_val > u16_TK11_environment_val)
				{
					u16_TK11_environment_val = u16_get_val;
				}
			}
		}
	}
	else   //����Ƿ��ɿ�
	{
		FilterCnt_TK11 = 0; //�������水�µļ���ֵ

		//����ֵ�����ȡֵ
		TK11_Filter_Cnt++;

		if(TK11_Filter_Cnt >= 3) // 15ms
		{
			TK11_Filter_Cnt = 0;

			if(u16_get_val <= u16_TK11_environment_val)
			{
				u16_TK11_environment_val = u16_get_val;
			}
			else
			{
				u16_TK11_environment_val ++;
			}
		}

		//�ɿ����
		if(u16_get_val > u16_TK11_environment_val)
		{
			u16_release_val = u16_get_val - u16_TK11_environment_val;
		}
		else
		{
			u16_release_val = 0;
		}

		if(u16_get_val > u16_release_val_TK11 || u16_release_val > Const_SEN_T_Key11_Release)	//�ɿ�
		{
			TK11_Release_Cnt ++;
			if(TK11_Release_Cnt >= 4) //�����ɿ��˲� 20ms
			{
				TK_Release_();
			}
		}
		else
		{
			TK11_Release_Cnt = 0;
		}	
    }	
}

void	Long_Press_Reset(void)
{
	if(T_Key11_Signal)	//�а�������
	{
		RestCnt ++;
		if(RestCnt > 1000) //Լ 10S
		{
			RestCnt = 0;
			TK_Release_();
		}
	}
	else
	{
		RestCnt = 0;
	}
}

void	TK11_OUT_Control(void)
{
	if(T_Key11_Signal)
	{
		//User Code
		//$ PA.3 out, high;
	}
	else
	{
		//User Code
		//$ PA.3 out, low;
	}
}

/*---------------------------------extern.h-----------------------------------

#ifndef	extern_h
#define	extern_h


SysClock_DIV => 8

Const_Sleep_WakeUp       	=>  3580  //3680 80MS

System_Clock	EQU	8000000	//	Used at UART, PS2, ...
PMS164	=>	0x164
Chip_Name	=>	PMS164
#if	defined(ADCC)
	#if defined(ADCR)
		ADCRH	EQU		ADCR
		ADCRL	EQU		0
	#else
		ADCR	EQU		ADCRH
	#endif
#endif





	Const_Touch_Source_CLK	=>	3;	//Touch Pad clock selection,ȡֵ0-8
									//0:reserved, 1:reserved, 2:IHRC/4, 3:IHRC/8,
									//4:IHRC/16, 5:IHRC/32, 6:IHRC/64, 7:IHRC/128, 8:ILRC
									//default:2
	Const_Touch_VRef		=>  0;	//0:0.5*VCC, 1:0.4*VCC, 2:0.3*VCC, 3:0.2*VCC
									//CS���ݲο���ѹ�趨 0.2VCC-0.5VCC
									//��CS���ݴ�С�ʹ�����������Ӱ��
									//�˴���߿ɽ����ⲿ��׼����
									//default:0
	Const_Touch_Discharge	=>	3;	
									//0:reserved, 1:CLK_32, 2:CLK_64, 3:CLK_128	
									//default:1
#endif

---------------------------------------------------------------------------*/
