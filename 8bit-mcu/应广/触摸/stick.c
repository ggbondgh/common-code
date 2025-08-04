

/***************** ShortLong Press 1 *************************/
#define Signal_99 xx99    // if touch, xx99 is the touch signal
byte time_10ms_cnt99;
byte press_sign99;
bit  long_trigger99;
bit  done_trigger99;

/* Press Fliter, used in 1ms timed */
#define	Key_Filter_Time 20 //定义滤波时长
byte key_icnt;
bit Signal_99;
if (!KEY99_PIN)
{
	key_icnt--;
	if (key_icnt == 0)
	{
		Signal_99 = 1;
	}
}
else
{
	Signal_99 = 0;
	key_icnt = Key_Filter_Time;
}

/* ShortLong Func, used in 10ms timed */
void SL99(void)
{
	time_10ms_cnt99++;
	/* Short-Long Judge */
	if(Signal_99 && time_10ms_cnt99 > 50) // Long press, over 500ms
	{
		time_10ms_cnt99 = 50; // Fix the time in case not overflow
		press_sign99 = LONG_SIGN;
	}
	else if(Signal_99) 
	{
		press_sign99 = WAIT_SIGN;
	}
	else // No press
	{
		time_10ms_cnt99 = 0;
		if(press_sign99 == WAIT_SIGN)
		{
			press_sign99 = SHORT_SIGN;
		}
		else
		{
			press_sign99 = NO_SIGN;
		}
		long_trigger99 = 1;
	}
    /* Signal process */
	if(press_sign99 == SHORT_SIGN) // Short press func
	{	
		done_trigger99 = 1;
        /* USER CODE BEGIN */
        
        /* USER CODE END */
	}
	else if(press_sign99 == LONG_SIGN && long_trigger99) // Long press func
	{
        if(long_trigger99 == 1)
		{
			long_trigger99 = 0;
			done_trigger99 = 1;
			/* USER CODE BEGIN */
			
			/* USER CODE END */
		}
	}
	else if(press_sign99 == NO_SIGN)
	{
		if(done_trigger99 == 1)
		{
			done_trigger99 = 0;
			/* USER CODE BEGIN */
			
			/* USER CODE END */
		}
	}
}