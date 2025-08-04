.forc CC #Count
	byte time_10ms_cnt#CC;
	byte touch_sign#CC;
	bit  long_trigger#CC;
	bit  done_trigger#CC;	
.endm

void TK_SL(void)
{
.forc CC #Count
	time_10ms_cnt#CC++;
	/* Short-Long Judge */
	if(TK_signal#CC && time_10ms_cnt#CC > 50) // Long touch, over 500ms
	{
		time_10ms_cnt#CC = 50; // Fix the time in case not overflow
		touch_sign#CC = LONG_SIGN;
	}
	else if(TK_signal#CC) 
	{
		touch_sign#CC = WAIT_SIGN;
	}
	else // No touch
	{
		time_10ms_cnt#CC = 0;
		if(touch_sign#CC == WAIT_SIGN)
		{
			touch_sign#CC = SHORT_SIGN;
		}
		else
		{
			touch_sign#CC = NO_SIGN;
		}
		long_trigger#CC = 1;
	}
    /* Signal process */
	if(touch_sign#CC == SHORT_SIGN) // Short touch func
	{	
		done_trigger#CC = 1;
        /* USER CODE BEGIN */
		LED_X_Switch();
        /* USER CODE END */
	}
	else if(touch_sign#CC == LONG_SIGN && long_trigger#CC) // Long touch func
	{
        if(long_trigger#CC == 1)
		{
			long_trigger#CC = 0;
			done_trigger#CC = 1;
			/* USER CODE BEGIN */
			if(LED_X_on_flag == 1)
			{
				grad_X_flag = 1; // Open LED_X_Grad
				if(PWM_sign_X == UP)
				{
					PWM_sign_X = DOWN;
				}
				else if(PWM_sign_X == DOWN)
				{
					PWM_sign_X = UP;
				}
			}
			/* USER CODE END */
		}
	}
	else if(touch_sign#CC == NO_SIGN)
	{
		if(done_trigger#CC == 1)
		{
			done_trigger#CC = 0;
			/* USER CODE BEGIN */
			grad_X_flag = 0;			
			/* USER CODE END */
		}
	}
.endm
}
