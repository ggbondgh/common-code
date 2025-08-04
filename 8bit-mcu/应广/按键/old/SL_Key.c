
#define NO_SIGN    0
#define WAIT_SIGN  1
#define SHORT_SIGN 2
#define LONG_SIGN  3

byte Time_10ms_Cnt;
bit	 Time_10ms_Flag;
byte Touch_Sign;
bit  Long_trigger;
bit  Done_trigger;

void Scan_Key(void)
{
	if(Time_10ms_Flag)
	{
		Time_10ms_Cnt++;
		
		/* Short-Long Judge */
		if(!Key && Time_10ms_Cnt > 50) // Long touch, over 500ms
		{
			Time_10ms_Cnt = 50; // Fix the time in case not overflow
			Touch_Sign = LONG_SIGN;
		}
		else if(!Key) 
		{
			Touch_Sign = WAIT_SIGN;
		}
		else // No touch
		{
			Time_10ms_Cnt = 0;
			if(Touch_Sign == WAIT_SIGN)
			{
				Touch_Sign = SHORT_SIGN;
			}
			else
			{
				Touch_Sign = NO_SIGN;
			}
			Long_trigger = 1;
		}
		/* Signal process */
		if(Touch_Sign == SHORT_SIGN) // Short touch func
		{	
			Done_trigger = 1;
			/* USER CODE BEGIN */
			
			/* USER CODE END */
		}
		else if(Touch_Sign == LONG_SIGN && Long_trigger) // Long touch func
		{
			if(Long_trigger == 1)
			{
				Long_trigger = 0;
				Done_trigger = 1;
				/* USER CODE BEGIN */
				
				/* USER CODE END */
			}
		}
		else if(Touch_Sign == NO_SIGN)
		{
			if(Done_trigger == 1)
			{
				Done_trigger = 0;
				/* USER CODE BEGIN */
				
				/* USER CODE END */
			}
		}
	}
}



