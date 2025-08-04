 uint16_t	 g_adc_value;	 //接收ADC检测值
 uint16_t	 f_adc_value;	 //滤波后的AD值
 uint16_t	 Num = 0;		 //显示的数字

//AD滤波
 u8 i;
 u16 adc_data;
 u16 adc_data_Old;
 u8  num;
 u16 ADC_Val[4];
 u16 adc_tmp;
 u16 ADC_Val_tmp;
 u16 cnt_test;
 u8  cnt_iop;

 //AD滤波
 u16 ADC_Filt(u16 data_tmp)
 {
	 u8 i;
	 u16 temp;
	 if(adc_data_Old>data_tmp)
	 {
		 temp = adc_data_Old - data_tmp;
	 }
	 else
	 {
		 temp = data_tmp - adc_data_Old;
	 }
	 if(temp>10)
	 {
		 temp = data_tmp;
	 }else
	 {
		 temp = adc_data_Old;
	 }
	 ADC_Val[num] = temp;
	 num++;
	 if(num>=4)
		 num = 0;
	 temp = 0;
	 for ( i = 0; i < 4; i++)
	 {
		 temp += ADC_Val[i];
	 }
	 temp >>= 2;
	 adc_data_Old = data_tmp;
	 return temp;
 }

 //AD解码
 uint16_t Decode(uint16_t de_val)
 {
	 uint16_t U16_Volt_Temp;
	 
	 U16_Volt_Temp = mullong_ii(de_val,240)>>12;//(de_val/4096)*3*10*8
 
	 return U16_Volt_Temp;
 }


//主循环前先获取一次
 for ( i = 0; i < 4; i++)
 {
	 adc_data = ADC_Get_Value_Average(2);
	 f_adc_value = ADC_Filt(adc_data);
 }

//中断里面
adc_data = ADC_Get_Value_Average(2);
adc_tmp += adc_data;
cnt_test++;
if(cnt_test>=16)
{
	cnt_test= 0;
	adc_tmp>>=4;
	ADC_Val_tmp += adc_tmp;
	adc_tmp = 0;
	cnt_iop++;
	if(cnt_iop>=16)
	{
		cnt_iop = 0;
		ADC_Val_tmp>>=4;
		f_adc_value = ADC_Filt(ADC_Val_tmp);
		ADC_Val_tmp = 0;
		if(PowerOn_Disp_Flag == 0)
		{
			Num = Decode(f_adc_value); //解码
		}
	}
}


