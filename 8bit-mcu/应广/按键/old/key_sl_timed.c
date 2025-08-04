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