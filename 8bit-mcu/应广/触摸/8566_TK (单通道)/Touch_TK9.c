/**************************************************************************************************
								           ����
----------------------------------------------------------------------------------------------
ʹ�÷�����
    1.����ѭ��ǰ����(��ͨ������)��
    
	TK_Init();

	2.����ѭ��-��ʱ5ms-�е���������������������TK9_Scan������������ͨ�����ã���
	
	if(T16_5ms_Flag_TK)
	{
		T16_5ms_Flag_TK = 0;
		
		TK9_Scan();
		TK_Out_Control();
		Long_Press_Reset();//����Ҫ�ɲ���
	}

	3.�ж�����Ҫ����5ms��ʱ�������ļ������־λ(�ഥ��ֻ����һ������)��bit T16_5ms_Flag_TK;

	4.���������ú��� TK_Init��Long_Press_Reset��TK_Out_Control (��ĩβע��)�������ļ��б��ڸĶ�

	5.��Ҫ�Ѹ��ļ����·��ġ�extern.h�����ݼӵ�extern.h(�ഥ��ֻ��һ������)

	6.���õ�Long_Press_Reset()��Ҫ�����ļ����壺word RestCnt;	//������λ����

----------------------------------------------------------------------------------------------
ע�⣺
	1.�����õ���Key9�������������������Ҫ�ѡ�9��ȫ���ĳ���Ӧ����,����TK9_Scan()��ʹ���õ���TKEͨ��λ
*****************************************************************************************************/

#include	"extern.h"


#define FilterCnt_Value  8 
#define Const_SEN_T_Key9  30 		 //������ֵ
#define Const_SEN_T_Key9_Release  40 //�ɿ���ֵ

word u16_get_val_TK9;		//��ȡֵ
word u16_Press_val_TK9;     //���º�Ķ�ȡֵ
word u16_release_val_TK9;	//�ɿ���Ķ�ȡֵ

eword u16_TK9_environment_val_Sum = 0;  //������ʱ��ȡ�ۼ�ֵ
word u16_TK9_environment_val;			//����ֵ�����ڸ����ȡֵ��
word u16_release_val2_TK9 = 0;  		//���º�� ������ֵ-������ֵ��
bit  TK9_Release_Flag;

word u16_temp_val_TK9 = 0;   //һ���˲��õ�����ʱ����

byte TK9_Filter_Cnt = 0;
byte TK9_Release_Cnt = 0;
byte Pre_T_Key9_Release = 1; //�ɿ�ǰ��־λ��1Ϊ�ɿ�ǰ��ⰴ�£�0Ϊ���º����ɿ�
byte FilterCnt_TK9;
word u16_get_val_Temp_TK9 = 0;

bit  T_Key9_Signal; //״̬��־λ��1Ϊ���µ�״̬��0Ϊ�ɿ���״̬

//=================================================================

void	TK_Release_TK9(void)
{
	//�����ɿ��ļ���ֵ������ر�־λ
	TK9_Release_Cnt = 0;

	T_Key9_Signal = 0;
	Pre_T_Key9_Release = 1;					
	u16_TK9_environment_val = u16_get_val_TK9;
	TK9_Filter_Cnt = 0;
	u16_TK9_environment_val_Sum = 0;

	TK9_Release_Flag = 1;
}

void	TK9_Scan(void) //*********
{	
	TKE1 = 0b_0000_0000;	//TKE1:bit1~7 => TK1~7
	TKE2 = 0b_0000_0010;	//TKE2:bit0~4 => TK8~12  ʹ��TK9
	
	//��ȡ����ֵ
	$ TCC TK_RUN;
	while(A != 0x00) 
	{
		A = TCC & 0x70;
	}
	u16_get_val_TK9 =  (TKCH << 8) | TKCL;

	//һ���˲�
	u16_temp_val_TK9 = u16_get_val_Temp_TK9 << 2;
	u16_temp_val_TK9 -= u16_get_val_Temp_TK9;
	u16_temp_val_TK9 += u16_get_val_TK9;
	u16_get_val_Temp_TK9 = u16_temp_val_TK9 >> 2;

	u16_get_val_TK9 = u16_get_val_Temp_TK9;


	if(Pre_T_Key9_Release) //����Ƿ���
	{
		u16_Press_val_TK9 = u16_get_val_TK9 + Const_SEN_T_Key9;
		
		if(u16_Press_val_TK9 < u16_TK9_environment_val)	 //���£�����ֵ>��ȡֵ+������ֵ
		{
		//	Const_Env_Dw_Fix_Speed = 5;

			FilterCnt_TK9 ++;
			if(FilterCnt_TK9 >= FilterCnt_Value)  //�˲�����⵽������β���Ϊ����
			{
				T_Key9_Signal = 1;
				Pre_T_Key9_Release = 0;
				u16_release_val2_TK9 = u16_TK9_environment_val - Const_SEN_T_Key9; //��ȡ���������ɿ������
			}
		}
		else //���»���ֵ�������ȡֵ
		{
			FilterCnt_TK9 = 0;

			// ����ζ�ȡֵȡƽ��ֵ
			TK9_Filter_Cnt ++;
			u16_TK9_environment_val_Sum += u16_get_val_TK9; //��ȡֵ�ۼ�
			if(TK9_Filter_Cnt > 31) //�ۼ�32��
			{
				TK9_Filter_Cnt = 0;
				u16_TK9_environment_val = u16_TK9_environment_val_Sum >> 5; //����2^5=32
				u16_TK9_environment_val_Sum = 0;

				if(TK9_Release_Flag)
				{
					TK9_Release_Flag = 0;
					u16_TK9_environment_val = u16_get_val_TK9;
				}
			}

			if(TK9_Release_Flag == 1) //�ۼ���ִ�д��б�
			{
				if(u16_get_val_TK9 > u16_TK9_environment_val)
				{
					u16_TK9_environment_val = u16_get_val_TK9;
				}
			}
		}
	}
	else   //����Ƿ��ɿ�
	{
		FilterCnt_TK9 = 0; //�������水�µļ���ֵ

		//����ֵ�����ȡֵ
		TK9_Filter_Cnt++;

		if(TK9_Filter_Cnt >= 3) // 15ms
		{
			TK9_Filter_Cnt = 0;

			if(u16_get_val_TK9 <= u16_TK9_environment_val)
			{
				u16_TK9_environment_val = u16_get_val_TK9;
			}
			else
			{
				u16_TK9_environment_val ++;
			}
		}

		//�ɿ����
		if(u16_get_val_TK9 > u16_TK9_environment_val)
		{
			u16_release_val_TK9 = u16_get_val_TK9 - u16_TK9_environment_val;
		}
		else
		{
			u16_release_val_TK9 = 0;
		}

		if(u16_get_val_TK9 > u16_release_val2_TK9 || u16_release_val_TK9 > Const_SEN_T_Key9_Release)	//�ɿ�
		{
			TK9_Release_Cnt ++;
			if(TK9_Release_Cnt >= 4) //�����ɿ��˲� 20ms
			{
				TK_Release_TK9();
			}
		}
		else
		{
			TK9_Release_Cnt = 0;
		}	
    }	
}




/*--------------------------------����ͨ�����������ú���--------------------------------

void	TK_Init(void)
{
	TS   = 0b_0010_00_10; 	// IHRC/8, 0.5*VCC, 128*CLK
	TKE1 = 0b_0000_000_0;
	TKE2 = 0b_0000_000_0;

	TPS2 = 0x01; // CS ��VDD
}


void	Long_Press_Reset(void)
{
	if(T_Key9_Signal)	//�а�������
	{
		RestCnt ++;
		if(RestCnt > 2000) //Լ 10S
		{
			RestCnt = 0;
			TK_Release_TK9();
		}
	}
	else
	{
		RestCnt = 0;
	}
}


void	TK_Out_Control(void)
{
	if(T_Key9_Signal)
	{
		//User Code
		//$ PB.5 out, high;
	}
	else
	{
		//User Code
		//$ PB.5 out, low;
	}
}

--------------------------------------------------------------------------------------*/

/*---------------------------------extern.h-------------------------------------------

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
