/*
* 注：在10ms扫描下使用
* 如果需要只执行一次则需要打开相应注释
* 短按只能执行一次
* 
*/

#define NO_SIGN    0
#define WAIT_SIGN  1
#define SHORT_SIGN 2
#define LONG_SIGN  3
byte Time_10ms_Cnt;
byte Touch_Sign;
bit  LongSign; // For single trigger-LONG
bit  DoneSign; // For single trigger-DONE


void Scan_TK(void)
{
	Time_10ms_Cnt++;
	/* Short-Long Judge */
	if(Signal_X && Time_10ms_Cnt > 50) // Long touch, over 500ms
	{
		Time_10ms_Cnt = 50; // Fix the time，in case not overflow
		Touch_Sign = LONG_SIGN;
		/* For single trigger-LONG:
		if(LongSign)
		{
			LongSign = 0;
            /* USER CODE BEGIN */           
            /* USER CODE END */
		}
		*/
	}
	else if(Signal_X) 
	{
		Touch_Sign = WAIT_SIGN;
		// LongSign = 1; // For single trigger-LONG
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
	}
    /* Signal process */
	if(Touch_Sign == SHORT_SIGN) // Short touch func
	{	
        /* USER CODE BEGIN */
        
        /* USER CODE END */
	}
	else if(Touch_Sign == LONG_SIGN) // Long touch func
	{
        /* USER CODE BEGIN */
        
        /* USER CODE END */
	}
	else if(Touch_Sign == NO_SIGN)
	{
        /* USER CODE BEGIN */
		/* For single trigger-DONE:
		if(DoneSign == 1)
		{
			DoneSign = 0;
		}
		*/          
        /* USER CODE END */
	}
}



