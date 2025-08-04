/*
 * @Author: ZenonXie
 * @Date: 2025-03-03 15:17:15
 * @LastEditors: ZenonXie
 * @LastEditTime: 2025-03-03 15:17:32
 * @FilePath: \undefinedc:\Users\Zenon\Desktop\SLs.c
 * @Description: 
 * 
 * Copyright (c) 2025 by ggbond_xie@qq.com, All Rights Reserved. 
 */
#define NO_SIGN    0
#define WAIT_SIGN  1
#define SHORT_SIGN 2
#define LONG_SIGN  3

/***************** ShortLong Press 1 *************************/
#define Signal_1 xx1    // if touch, xx1 is the touch signal
byte time_10ms_cnt1;
byte press_sign1;
bit  long_trigger1;
bit  done_trigger1;

/* Press Fliter, used in 1ms timed */
#define	Key_Filter_Time 20 //定义滤波时长
byte key_icnt;
bit Signal_1;
if (!KEY1_PIN)
{
	key_icnt--;
	if (key_icnt == 0)
	{
		Signal_1 = 1;
	}
}
else
{
	Signal_1 = 0;
	key_icnt = Key_Filter_Time;
}

/* ShortLong Func, used in 10ms timed */
void SL1(void)
{
	time_10ms_cnt1++;
	/* Short-Long Judge */
	if(Signal_1 && time_10ms_cnt1 > 50) // Long press, over 500ms
	{
		time_10ms_cnt1 = 50; // Fix the time in case not overflow
		press_sign1 = LONG_SIGN;
	}
	else if(Signal_1) 
	{
		press_sign1 = WAIT_SIGN;
	}
	else // No press
	{
		time_10ms_cnt1 = 0;
		if(press_sign1 == WAIT_SIGN)
		{
			press_sign1 = SHORT_SIGN;
		}
		else
		{
			press_sign1 = NO_SIGN;
		}
		long_trigger1 = 1;
	}
    /* Signal process */
	if(press_sign1 == SHORT_SIGN) // Short press func
	{	
		done_trigger1 = 1;
        /* USER CODE BEGIN */
        
        /* USER CODE END */
	}
	else if(press_sign1 == LONG_SIGN && long_trigger1) // Long press func
	{
        if(long_trigger1 == 1)
		{
			long_trigger1 = 0;
			done_trigger1 = 1;
			/* USER CODE BEGIN */
			
			/* USER CODE END */
		}
	}
	else if(press_sign1 == NO_SIGN)
	{
		if(done_trigger1 == 1)
		{
			done_trigger1 = 0;
			/* USER CODE BEGIN */
			
			/* USER CODE END */
		}
	}
}



/***************** ShortLong Press 2 *************************/
#define Signal_2 xx2    // if touch, xx2 is the touch signal
byte time_10ms_cnt2;
byte press_sign2;
bit  long_trigger2;
bit  done_trigger2;

/* Press Fliter, used in 1ms timed */
#define	Key_Filter_Time 20 //定义滤波时长
byte key_icnt;
bit Signal_2;
if (!KEY2_PIN)
{
	key_icnt--;
	if (key_icnt == 0)
	{
		Signal_2 = 1;
	}
}
else
{
	Signal_2 = 0;
	key_icnt = Key_Filter_Time;
}

/* ShortLong Func, used in 10ms timed */
void SL2(void)
{
	time_10ms_cnt2++;
	/* Short-Long Judge */
	if(Signal_2 && time_10ms_cnt2 > 50) // Long press, over 500ms
	{
		time_10ms_cnt2 = 50; // Fix the time in case not overflow
		press_sign2 = LONG_SIGN;
	}
	else if(Signal_2) 
	{
		press_sign2 = WAIT_SIGN;
	}
	else // No press
	{
		time_10ms_cnt2 = 0;
		if(press_sign2 == WAIT_SIGN)
		{
			press_sign2 = SHORT_SIGN;
		}
		else
		{
			press_sign2 = NO_SIGN;
		}
		long_trigger2 = 1;
	}
    /* Signal process */
	if(press_sign2 == SHORT_SIGN) // Short press func
	{	
		done_trigger2 = 1;
        /* USER CODE BEGIN */
        
        /* USER CODE END */
	}
	else if(press_sign2 == LONG_SIGN && long_trigger2) // Long press func
	{
        if(long_trigger2 == 1)
		{
			long_trigger2 = 0;
			done_trigger2 = 1;
			/* USER CODE BEGIN */
			
			/* USER CODE END */
		}
	}
	else if(press_sign2 == NO_SIGN)
	{
		if(done_trigger2 == 1)
		{
			done_trigger2 = 0;
			/* USER CODE BEGIN */
			
			/* USER CODE END */
		}
	}
}



/***************** ShortLong Press 3 *************************/
#define Signal_3 xx3    // if touch, xx3 is the touch signal
byte time_10ms_cnt3;
byte press_sign3;
bit  long_trigger3;
bit  done_trigger3;

/* Press Fliter, used in 1ms timed */
#define	Key_Filter_Time 20 //定义滤波时长
byte key_icnt;
bit Signal_3;
if (!KEY3_PIN)
{
	key_icnt--;
	if (key_icnt == 0)
	{
		Signal_3 = 1;
	}
}
else
{
	Signal_3 = 0;
	key_icnt = Key_Filter_Time;
}

/* ShortLong Func, used in 10ms timed */
void SL3(void)
{
	time_10ms_cnt3++;
	/* Short-Long Judge */
	if(Signal_3 && time_10ms_cnt3 > 50) // Long press, over 500ms
	{
		time_10ms_cnt3 = 50; // Fix the time in case not overflow
		press_sign3 = LONG_SIGN;
	}
	else if(Signal_3) 
	{
		press_sign3 = WAIT_SIGN;
	}
	else // No press
	{
		time_10ms_cnt3 = 0;
		if(press_sign3 == WAIT_SIGN)
		{
			press_sign3 = SHORT_SIGN;
		}
		else
		{
			press_sign3 = NO_SIGN;
		}
		long_trigger3 = 1;
	}
    /* Signal process */
	if(press_sign3 == SHORT_SIGN) // Short press func
	{	
		done_trigger3 = 1;
        /* USER CODE BEGIN */
        
        /* USER CODE END */
	}
	else if(press_sign3 == LONG_SIGN && long_trigger3) // Long press func
	{
        if(long_trigger3 == 1)
		{
			long_trigger3 = 0;
			done_trigger3 = 1;
			/* USER CODE BEGIN */
			
			/* USER CODE END */
		}
	}
	else if(press_sign3 == NO_SIGN)
	{
		if(done_trigger3 == 1)
		{
			done_trigger3 = 0;
			/* USER CODE BEGIN */
			
			/* USER CODE END */
		}
	}
}



/***************** ShortLong Press 4 *************************/
#define Signal_4 xx4    // if touch, xx4 is the touch signal
byte time_10ms_cnt4;
byte press_sign4;
bit  long_trigger4;
bit  done_trigger4;

/* Press Fliter, used in 1ms timed */
#define	Key_Filter_Time 20 //定义滤波时长
byte key_icnt;
bit Signal_4;
if (!KEY4_PIN)
{
	key_icnt--;
	if (key_icnt == 0)
	{
		Signal_4 = 1;
	}
}
else
{
	Signal_4 = 0;
	key_icnt = Key_Filter_Time;
}

/* ShortLong Func, used in 10ms timed */
void SL4(void)
{
	time_10ms_cnt4++;
	/* Short-Long Judge */
	if(Signal_4 && time_10ms_cnt4 > 50) // Long press, over 500ms
	{
		time_10ms_cnt4 = 50; // Fix the time in case not overflow
		press_sign4 = LONG_SIGN;
	}
	else if(Signal_4) 
	{
		press_sign4 = WAIT_SIGN;
	}
	else // No press
	{
		time_10ms_cnt4 = 0;
		if(press_sign4 == WAIT_SIGN)
		{
			press_sign4 = SHORT_SIGN;
		}
		else
		{
			press_sign4 = NO_SIGN;
		}
		long_trigger4 = 1;
	}
    /* Signal process */
	if(press_sign4 == SHORT_SIGN) // Short press func
	{	
		done_trigger4 = 1;
        /* USER CODE BEGIN */
        
        /* USER CODE END */
	}
	else if(press_sign4 == LONG_SIGN && long_trigger4) // Long press func
	{
        if(long_trigger4 == 1)
		{
			long_trigger4 = 0;
			done_trigger4 = 1;
			/* USER CODE BEGIN */
			
			/* USER CODE END */
		}
	}
	else if(press_sign4 == NO_SIGN)
	{
		if(done_trigger4 == 1)
		{
			done_trigger4 = 0;
			/* USER CODE BEGIN */
			
			/* USER CODE END */
		}
	}
}