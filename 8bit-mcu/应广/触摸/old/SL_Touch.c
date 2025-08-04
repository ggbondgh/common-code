/***************** Touch_Func *************************/
bit Signal0_Flag;
bit Signal2_Flag;
bit Signal3_Flag;

void Touch_Func(void)
{
	Touch_Get_val();
//	Get_vale();
	TKHandleproess();
	if(TK_signal0 && Signal0_Flag)
	{
		Signal0_Flag = 0;
		/* USER CODE BEGIN */
		
		/* USER CODE END */
	}
	else
	{
		Signal0_Flag = 1;
	}

	if(TK_signal1 && Signal1_Flag)
	{
		Signal1_Flag = 0;
		/* USER CODE BEGIN */
		
		/* USER CODE END */		
	}
	else
	{
		Signal1_Flag = 1;		
	}
	if(TK_signal2 && Signal2_Flag)
	{
		Signal2_Flag = 0;	
		/* USER CODE BEGIN */
		
		/* USER CODE END */	
	}
	else
	{
		Signal2_Flag = 1;		
	}
}



/***************** Touch_ShortLong_1 *************************/
#define Signal_1 xxx
byte time_10ms_cnt1;
byte touch_sign1;
bit  long_trigger1;
bit  done_trigger1;

void TK_SL(void)
{
	time_10ms_cnt1++;
	/* Short-Long Judge */
	if(Signal_X && time_10ms_cnt1 > 50) // Long touch, over 500ms
	{
		time_10ms_cnt1 = 50; // Fix the time£¬in case not overflow
		touch_sign1 = LONG_SIGN;
	}
	else if(Signal_X) 
	{
		touch_sign1 = WAIT_SIGN;
	}
	else // No touch
	{
		time_10ms_cnt1 = 0;
		if(touch_sign1 == WAIT_SIGN)
		{
			touch_sign1 = SHORT_SIGN;
		}
		else
		{
			touch_sign1 = NO_SIGN;
		}
		long_trigger1 = 1;
	}
    /* Signal process */
	if(touch_sign1 == SHORT_SIGN) // Short touch func
	{	
		done_trigger1 = 1;
        /* USER CODE BEGIN */
        
        /* USER CODE END */
	}
	else if(touch_sign1 == LONG_SIGN && long_trigger1) // Long touch func
	{
        if(long_trigger1 == 1)
		{
			long_trigger1 = 0;
			done_trigger1 = 1;
			/* USER CODE BEGIN */
			
			/* USER CODE END */
		}
	}
	else if(touch_sign1 == NO_SIGN)
	{
		if(done_trigger1 == 1)
		{
			done_trigger1 = 0;
			/* USER CODE BEGIN */
			
			/* USER CODE END */
		}
	}
}


