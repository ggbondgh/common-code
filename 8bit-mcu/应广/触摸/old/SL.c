/***************** ShortLong Press *************************/
#define NO_SIGN    0
#define WAIT_SIGN  1
#define SHORT_SIGN 2
#define LONG_SIGN  3
#define Signal_X xxx   // if touch, xxx is the touch signal
byte time_10ms_cnt;
byte press_sign;
bit  long_trigger;
bit  done_trigger;

/* Press Fliter, used in 1ms timed */
#define	Key_Filter_Time 20 //定义滤波时长
byte key_icnt;
bit Signal_X;
if (!KEY_PIN)
{
	key_icnt--;
	if (key_icnt == 0)
	{
		Signal_X = 1;
	}
}
else
{
	Signal_X = 0;
	key_icnt = Key_Filter_Time;
}

void SL(void)
{
	time_10ms_cnt++;
	/* Short-Long Judge */
	if(Signal_X && time_10ms_cnt > 50) // Long touch, over 500ms
	{
		time_10ms_cnt = 50; // Fix the time in case not overflow
		press_sign = LONG_SIGN;
	}
	else if(Signal_X) 
	{
		press_sign = WAIT_SIGN;
	}
	else // No touch
	{
		time_10ms_cnt = 0;
		if(press_sign == WAIT_SIGN)
		{
			press_sign = SHORT_SIGN;
		}
		else
		{
			press_sign = NO_SIGN;
		}
		long_trigger = 1;
	}
    /* Signal process */
	if(press_sign == SHORT_SIGN) // Short touch func
	{	
		done_trigger = 1;
        /* USER CODE BEGIN */
        
        /* USER CODE END */
	}
	else if(press_sign == LONG_SIGN && long_trigger) // Long touch func
	{
        if(long_trigger == 1)
		{
			long_trigger = 0;
			done_trigger = 1;
			/* USER CODE BEGIN */
			
			/* USER CODE END */
		}
	}
	else if(press_sign == NO_SIGN)
	{
		if(done_trigger == 1)
		{
			done_trigger = 0;
			/* USER CODE BEGIN */
			
			/* USER CODE END */
		}
	}
}