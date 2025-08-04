/********************************************************************************
			功能名称:	用BG反推VDD，并用VDD测量IO脚的电压 + 一阶滞后滤波
---------------------------------------------------------------------------------
使用方法：
    1.先在主循环前调用：
	Get_AD_Value();
	temp_data = Get_ADval;//先测量一组数据作为上次滤波值

	2.直接在主循环中调用：ad_ddddd();
	即可得到最后滤波后接口得到的AD值：temp_data（测得的值是实际值电压值的100倍）
---------------------------------------------------------------------------------
注意：
	1.待测电压需要小于参考电压
	2.调用改接口函数，虚根据实际需求更改：ADC_IO_init()里面的端口（注意不要和主文件的IO配置冲突）
	3.要根据分辨率为8/12修改，修改位置有：开头的变量定义和ADC_mea()
	4.ADC检测端口需关闭数字输入（PxDIR对应位设为0）
********************************************************************************/


#include	"extern.h"

//byte	data;		//分辨率为8测得的ADC值
word	data;    	//分辨率为12测得的ADC值，ADC_mea()后得到的值
word	BG_data;
word	Px_data;
word	Get_ADval;	//Get_AD_Value()后得到的值


void	ADC_IO_init(void)
{
	//注：选择的通道需设置为输入，无上拉、下拉电阻、无数字输入使能；
	PAC.0 = 0;
	PAPH.0 = 0;
	PAPL.0 = 0;
//	PADIER = 0b0000_0000;	//注：关闭数字输入，其他脚默认为1，需要关闭的请手动修改

	$ ADCC	Enable,PA0;	//启用ADC功能，通道选择（AD转换的输入信号）						
	$ ADCM	/2;			//时钟源选择:系统时钟/2															
	.delay 400;			//注：时钟源选择其他时，延迟时间请参考datasheet
}

void	ADC_BG_init(void)//初始化
{
	$ ADCC	Enable, BANDGAP;	//启用ADC功能，通道选择（AD转换的输入信号）
						//启用：Enable；停用：Disable
						//通道选择：PB0, PA0, PB2, PB3, PB4, PB5, PB6, PB7,PA3, PA4, PA0
						//注：每个芯片的待测脚位不同，详情参考datasheet
	$ ADCM	/2;			//时钟源选择（系统时钟/X）
						//X有/1, /2, /4, /8, /16, /32, /64, /128
						//注：时钟源选择建议选用500K（/2）
						//参考高电压为VDD
	.delay 400;			//延时400us
						//注：时钟源选择其他时，延迟时间请参考datasheet
}

void	ADC_mea(void)//测量数据，并用平均值方式滤波
{
	byte	Icnt = 16;//测量16笔数据
	Eword	_Temp = 0;//16笔数据之和
	while(Icnt--)
	{
		//开始ADC转换
		AD_START = 1;		//开始ADC转换
		while(!AD_DONE)		//等待ADC转换结果
			NULL;
		//当AD_DONE高电位时读取ADC结果
		//注意：8位分辨率读取ADCR值，9~12为分辨率读取ADCRH和ADCRL
	//	data = ADCR;		//将ADC的值赋给data
		data$1 = ADCRH;
		data$0 = ADCRL;
		_Temp += data;
	}
	data = _Temp >> 4;//取平均值（2^4 = 16）
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

void	ADC_calcu(void)//数据计算
{
	mul_x2 = Px_data;//分辨率12为0xFFF0
	mul_y2 = 120;//BG电压的100倍
	Word_Mul_Word();
	div_src4 = mul_t4;
	div_val2 = BG_data;
	DWord_Div_Word();
	Get_ADval = div_src4 & 0xffff;//测得的值是实际值100倍
	nop;
}

void	Get_AD_Value(void)//读电压值
{
	ADC_BG_init();
	ADC_mea();
	BG_data = data;
	ADC_IO_init();
	ADC_mea();
	Px_data = data;
	ADC_calcu();
}


/****************以下是一阶滞后滤波*******************/

eword	AD_sum;		//上次滤波的7倍与本次滤波之和
word	AD_ave;		//平均之后的本次滤波值
word	temp_data;	//上次滤波值

void	ad_ddddd(void)
{
	Get_AD_Value();
	AD_sum = temp_data << 3;//上次滤波的8倍
	AD_sum = AD_sum - temp_data + Get_ADval;//上次滤波的7倍与本次滤波之和
	AD_ave = AD_sum >> 3;//取平均，作为本次滤波值
	temp_data = AD_ave;//将本次滤波值赋给上次滤波值，等待下次测试
}
