/********************************************************************************
			��������:	��BG����VDD������VDD����IO�ŵĵ�ѹ + һ���ͺ��˲�
---------------------------------------------------------------------------------
ʹ�÷�����
    1.������ѭ��ǰ���ã�
	Get_AD_Value();
	temp_data = Get_ADval;//�Ȳ���һ��������Ϊ�ϴ��˲�ֵ

	2.ֱ������ѭ���е��ã�ad_ddddd();
	���ɵõ�����˲���ӿڵõ���ADֵ��temp_data����õ�ֵ��ʵ��ֵ��ѹֵ��100����
---------------------------------------------------------------------------------
ע�⣺
	1.�����ѹ��ҪС�ڲο���ѹ
	2.���øĽӿں����������ʵ��������ģ�ADC_IO_init()����Ķ˿ڣ�ע�ⲻҪ�����ļ���IO���ó�ͻ��
	3.Ҫ���ݷֱ���Ϊ8/12�޸ģ��޸�λ���У���ͷ�ı��������ADC_mea()
	4.ADC���˿���ر��������루PxDIR��Ӧλ��Ϊ0��
********************************************************************************/


#include	"extern.h"

//byte	data;		//�ֱ���Ϊ8��õ�ADCֵ
word	data;    	//�ֱ���Ϊ12��õ�ADCֵ��ADC_mea()��õ���ֵ
word	BG_data;
word	Px_data;
word	Get_ADval;	//Get_AD_Value()��õ���ֵ


void	ADC_IO_init(void)
{
	//ע��ѡ���ͨ��������Ϊ���룬���������������衢����������ʹ�ܣ�
	PAC.0 = 0;
	PAPH.0 = 0;
	PAPL.0 = 0;
//	PADIER = 0b0000_0000;	//ע���ر��������룬������Ĭ��Ϊ1����Ҫ�رյ����ֶ��޸�

	$ ADCC	Enable,PA0;	//����ADC���ܣ�ͨ��ѡ��ADת���������źţ�						
	$ ADCM	/2;			//ʱ��Դѡ��:ϵͳʱ��/2															
	.delay 400;			//ע��ʱ��Դѡ������ʱ���ӳ�ʱ����ο�datasheet
}

void	ADC_BG_init(void)//��ʼ��
{
	$ ADCC	Enable, BANDGAP;	//����ADC���ܣ�ͨ��ѡ��ADת���������źţ�
						//���ã�Enable��ͣ�ã�Disable
						//ͨ��ѡ��PB0, PA0, PB2, PB3, PB4, PB5, PB6, PB7,PA3, PA4, PA0
						//ע��ÿ��оƬ�Ĵ����λ��ͬ������ο�datasheet
	$ ADCM	/2;			//ʱ��Դѡ��ϵͳʱ��/X��
						//X��/1, /2, /4, /8, /16, /32, /64, /128
						//ע��ʱ��Դѡ����ѡ��500K��/2��
						//�ο��ߵ�ѹΪVDD
	.delay 400;			//��ʱ400us
						//ע��ʱ��Դѡ������ʱ���ӳ�ʱ����ο�datasheet
}

void	ADC_mea(void)//�������ݣ�����ƽ��ֵ��ʽ�˲�
{
	byte	Icnt = 16;//����16������
	Eword	_Temp = 0;//16������֮��
	while(Icnt--)
	{
		//��ʼADCת��
		AD_START = 1;		//��ʼADCת��
		while(!AD_DONE)		//�ȴ�ADCת�����
			NULL;
		//��AD_DONE�ߵ�λʱ��ȡADC���
		//ע�⣺8λ�ֱ��ʶ�ȡADCRֵ��9~12Ϊ�ֱ��ʶ�ȡADCRH��ADCRL
	//	data = ADCR;		//��ADC��ֵ����data
		data$1 = ADCRH;
		data$0 = ADCRL;
		_Temp += data;
	}
	data = _Temp >> 4;//ȡƽ��ֵ��2^4 = 16��
}

DWORD	mul_t4;
WORD	mul_x2;
WORD	mul_y2;
void	Word_Mul_Word (void)
{	//	mul_t4[D]	=	mul_x2[W] * mul_y2[W]
	mul_t4$3	=	0;
	mul_t4$2	=	0;
 
	BYTE	cnt;
	cnt	=	16;
 
	do
	{
		mul_x2	>>=	1;
		if (CF)
		{
			mul_t4	+=	(mul_y2 << 16);
		}
		mul_t4	>>>=	1;
	} while (--cnt);
}
 
DWORD	div_src4;
WORD	div_val2, div_res2;
void	DWord_Div_Word (void)
{	//	div_src4[D] / div_val2[W]	=	div_src4[D] * div_val2[W] + div_res2[W]
	BYTE	div_cnt, div_tmp;
	div_cnt		=	0;
	div_res2	=	0;
 
	do
	{
		div_src4	<<=		1;
		div_res2	<<<=	1;
		div_tmp		<<<=	1;
		div_cnt++;
		A	=	(div_res2 - div_val2) >> 8;
		if (div_tmp.0 || ! CF)
		{
			div_res2$1	=	A;
			div_res2$0	-=	div_val2$0;
			div_src4.0	=	1;
		}
	} while (! div_cnt.5);
}

void	ADC_calcu(void)//���ݼ���
{
	mul_x2 = Px_data;//�ֱ���12Ϊ0xFFF0
	mul_y2 = 120;//BG��ѹ��100��
	Word_Mul_Word();
	div_src4 = mul_t4;
	div_val2 = BG_data;
	DWord_Div_Word();
	Get_ADval = div_src4 & 0xffff;//��õ�ֵ��ʵ��ֵ100��
	nop;
}

void	Get_AD_Value(void)//����ѹֵ
{
	ADC_BG_init();
	ADC_mea();
	BG_data = data;
	ADC_IO_init();
	ADC_mea();
	Px_data = data;
	ADC_calcu();
}


/****************������һ���ͺ��˲�*******************/

eword	AD_sum;		//�ϴ��˲���7���뱾���˲�֮��
word	AD_ave;		//ƽ��֮��ı����˲�ֵ
word	temp_data;	//�ϴ��˲�ֵ

void	ad_ddddd(void)
{
	Get_AD_Value();
	AD_sum = temp_data << 3;//�ϴ��˲���8��
	AD_sum = AD_sum - temp_data + Get_ADval;//�ϴ��˲���7���뱾���˲�֮��
	AD_ave = AD_sum >> 3;//ȡƽ������Ϊ�����˲�ֵ
	temp_data = AD_ave;//�������˲�ֵ�����ϴ��˲�ֵ���ȴ��´β���
}
