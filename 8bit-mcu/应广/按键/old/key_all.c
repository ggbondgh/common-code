



/*---------------------------------------按键（按下执行）---------------------------------------------------*/

#define	Key_Filter_Time 2000 //定义滤波时长

byte Key_Icnt;
bit	 Key_Sign;

void Scan_key(void)
{
	if (Key_Sign)
	{
		if (!Key)
		{
			Key_Icnt--;
			if (Key_Icnt == 0)
			{
				Key_Sign = 0;
				/* USER CODE BEGIN */
				
				/* USER CODE END */
			}
		}
		else
		{
			Key_Icnt = Key_Filter_Time;
		}
	}
	else
	{
		if (Key)
		{
			Key_Sign = 1;
			Key_Icnt = Key_Filter_Time;
			/* USER CODE BEGIN */
			
			/* USER CODE END */
		}
	}
}




/*---------------------------------------按键（松手后执行）---------------------------------------------------*/

void Scan_Key(void)
{
	word Icnt = 1000;
	while (1)
	{
		if (!Key)
		{
			Icnt--;
			if (Icnt == 0)
			{
				/* USER CODE BEGIN */
				
				/* USER CODE END */
				while (Key == 0) // 等待按键释放
					nop;
				break;
			}
		}
		else
		{
			break;
		}
	}
}




/*---------------------------------------按键（长短按，长按阻塞）---------------------------------------------------*/

#define	Press_Filt_Time 100 		//按键滤波时间,用定时器计数滤波
#define	Long_Press_Time 150000  	//长按滤波时间,取决于时钟频率

bit  Key_Keep;
bit  Key_Long_Sign;
byte Delay1;
byte Delay0;

void Scan_Key(void)
{
	if (Key_Keep == 0)
	{
		Delay1 = Press_Filt_Time;
		if (Key == 0)
		{
			Delay0--;
			if (Delay0 == 0) // 按键确实被按下
				Key_Keep = 1; // 结束后进入松手检测
				Key_Long_Sign = 0;
				word Delay_Icnt = 0;
				
				//进入长按前操作：
				/* USER CODE BEGIN */
				
				/* USER CODE END */
				
				while (!Key) // 等待，判断按键是否长按
				{
					Delay_Icnt++;
					if (Delay_Icnt >= Long_Press_Time) // 一定时间后确定是长按
					{
						Key_Long_Sign = 1;
						break;
					}
				}
				if (Key_Long_Sign) // 长按
				{
					/* USER CODE BEGIN */
					
					/* USER CODE END */
				}
				else //短按
				{
					/* USER CODE BEGIN */
					
					/* USER CODE END */
				}
			}
		}
		else
		{
			Delay0 = Press_Filt_Time; // 无按键按下重置滤波值
		}
	}
	else
	{
		Delay0 = Press_Filt_Time;
		if (Key) // 检测松手
		{
			Delay1--;
			if (Delay1 == 0)
			{
				Key_Keep = 0; // 已松手，重新进入按键检测
			}
		}
		else
		{
			Delay1 = Press_Filt_Time; // 不松手重置滤波值
		}
	}
}



/*---------------------------------------按键（长短按，长按非阻塞）---------------------------------------------------*/

#define	Press_Filt_Time 100 		// 按键滤波时间（用定时器计数滤波）
#define	Long_Press_Time 800-100  	// 长按时间：800ms

dword Delay_Icnt;
byte  Delay1;
byte  Delay0;
bit	  Key_Keep;
bit   Key_Long_Sign;
bit	  Judging_Flag;
bit	  Judged_Flag;


void Scan_Key(void)
{
	if(!Judging_Flag && !Judged_Flag)
	{
		if (Key_Keep == 0)
		{
			Delay1 = Press_Filt_Time;
			if (!Key)
			{
				Delay0--;
				if (Delay0 == 0) // 按键确实被按下
				{
					Key_Keep = 1;			
					Key_Long_Sign = 0;
					Delay_Icnt = 0;
					Judging_Flag = 1; // 进入长短按判定	
				}
			}
			else
			{
				Delay0 = Press_Filt_Time;
			}
		}
		else
		{
			Delay0 = Press_Filt_Time;
			if (Key1)
			{
				Delay1--;
				if (Delay1 == 0) // 松手后
				{
					Key_Keep = 0;
				}
			}
			else
			{
				Delay1 = Press_Filt_Time;
			}
		}
	}
	else if(Judging_Flag) // 长短按判定
	{
		if(!Key)
		{
			Delay_Icnt++;
			if (Delay_Icnt >= Long_Press_Time) // 一定时间后确定是长按
			{
				Key_Long_Sign = 1;
				Judging_Flag = 0;
				Judged_Flag = 1;
			}
		}
		else
		{
			Judging_Flag = 0;
			Judged_Flag = 1;
		}
	}
	else if(Judged_Flag) // 长短按功能
	{
		Judged_Flag = 0;
		if (Key_Long_Sign) // 长按
		{
			/* USER CODE BEGIN */
			
			/* USER CODE END */
		}
		else //短按
		{
			/* USER CODE BEGIN */
			
			/* USER CODE END */
		}
	}

}





/*---------------------------------------2引脚复用3按键---------------------------------------------------*/

//K2按下接地为低电平，执行操作1；
//K3按下接地为低电平，执行操作2；
//K2和K3同时按下，执行操作3,有长短按


#define	Press_Filt_Time 100 		//按键滤波时间
#define	Long_Press_Time 150000  //按键滤波时间,180000

byte Delay1;
byte Delay0;
bit  Key_Keep;
bit  Key_Long_Sign;


void Scan_Key(void)
{
	if (Key_Keep == 0)
	{
		Delay1 = Press_Filt_Time;
		if (!K2 && K3)
		{
			Delay0--;
			if (Delay0 == 0)
			{
				Key_Keep = 1;
				//执行1：
				/* USER CODE BEGIN */
				
				/* USER CODE END */
			}

		}
		else if (!K3 && K2)
		{	
			Delay0--;
			if (Delay0 == 0)
			{
				Key_Keep = 1;
				//执行2：
				/* USER CODE BEGIN */
				
				/* USER CODE END */	
			}

		}
		else if (K2 && K3)
		{
			$ K2 out,low; // 将其中一边拉低
			.delay 2*100
			if(!K3) // 判断另一边是否相同
			{
				Delay0--;
				if (Delay0 == 0)
				{
					Key_Keep = 1;
					Key_Long_Sign = 0;
					dword Delay_Icnt = 0;

					//进入长按前操作：
					/* USER CODE BEGIN */
					
					/* USER CODE END */
					
					while (!K2 && !K3) // 等待，判断按键是否长按
					{
						Delay_Icnt++;
						if (Delay_Icnt >= Long_Press_Time) // 一定时间后确定是长按
						{
							Key_Long_Sign = 1;
							break; // 退出按键扫描
						}
					}

					if (Key_Long_Sign) // 长按
					{
						/* USER CODE BEGIN */
						
						/* USER CODE END */
					}
					else //短按
					{
						/* USER CODE BEGIN */
						
						/* USER CODE END */
					}
				}
			}
			else
			{
				Delay0 = Press_Filt_Time;
			}
		}
		else
		{
			Delay0 = Press_Filt_Time;
		}

	}
	else
	{
		Delay0 = Press_Filt_Time;
		if (K2 && K3)
		{
			$ K2 out,low;
			.delay 4*100
			if(K3)
			{
				Delay1--;
				if (Delay1 == 0) // 松手
				{
					Key_Keep = 0;
					/* USER CODE BEGIN */
					
					/* USER CODE END */			
				}
			}
			else
			{			
				Delay1 = Press_Filt_Time;
			}
		}
		else
		{
			Delay1 = Short_Press_Time;
		}

	}

	$ K2 in,pull; // K2重置
}




/*--------------------------------------- ---------------------------------------------------*/




