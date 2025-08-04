

/***************** touch_func *************************/
Only execute once

bit Signal0_Flag;

if(TK_signal0 && Signal0_Flag)
{
    Signal0_Flag = 0;
    /* USER CODE BEGIN */
    
    /* USER CODE END */
}
else if(TK_signal0 == 0)
{
    Signal0_Flag = 1;
}




/***************** Flash *************************/
#define Const_Flash_Cnt 600
byte Flash_Count;

void Flash(void)
{
    _1ms_Cnt++;
    if(_1ms_Cnt <= Const_Flash_Cnt)
    {
        $ LED out,high;  // Open
    }
    else if(_1ms_Cnt2 <= Const_Flash_Cnt*2)
    {
        $ LED out,low; // Close
    }
    else
    {
        _1ms_Cnt = 0;
        Flash_Count++;	
    }
    if(Flash_Count >= 3)
    {
        Flash_Count = 0;
    }
}

/***************** PWM Gradual *************************/
#define UP 1
#define DOWN 0
bit  Grad_W_Flag;
bit  Grad_Y_Flag;
bit  Grad_WY_Flag;
bit  PWM_Sign_W;
bit  PWM_Sign_Y;
bit  PWM_Sign_WY;
byte PWM_Num_W;
byte PWM_Num_Y;
byte PWM_Num_WY;

void PWM_Grad(void)
{
	/* 白灯调光 */
	if(Grad_W_Flag)
	{
		if(PWM_Sign_W == UP) // PWM++
		{			
			if(PWM_Num_W >= 255) // Brightness => 100%
			{
				PWM_Num_W = 255;
			}
			else
			{
				PWM_Num_W++;
			}		
		}
		if(PWM_Sign_W == DOWN) // PWM--
		{		
			if(PWM_Num_W == 0) // Brightness => 0%
			{
				PWM_Num_W = 0;
				$ TM2C STOP;		
			}
			else
			{
				PWM_Num_W--;
			}
		}
		TM2B = PWM_Num_W;
	}
	/* 黄灯调光 */
	if(Grad_Y_Flag)
	{
		if(PWM_Sign_Y == UP) // PWM++
		{	
			if(PWM_Num_Y >= 255) // Brightness => 100%
			{
				PWM_Num_Y = 255;
			}
			else
			{
				PWM_Num_Y++;
			}	
		}
		if(PWM_Sign_Y == DOWN) // PWM--
		{
			if(PWM_Num_Y == 0) // Brightness => 0%
			{
				PWM_Num_Y = 0;
				$ TM3C STOP;
			}
			else
			{
				PWM_Num_Y--;
			}
		}
		TM3B = PWM_Num_Y;
	}
	/* 黄白灯调光 */
	if(Grad_WY_Flag)
	{
		if(PWM_Sign_WY == UP) // PWM++
		{				
			if(PWM_Num_WY >= 255) // Brightness => 100%
			{
				PWM_Num_WY = 255;
			}
			else
			{
				PWM_Num_WY++;
			}
		}
		if(PWM_Sign_WY == DOWN) // PWM--
		{		
			if(PWM_Num_WY == 0) // Brightness => 0%
			{
				PWM_Num_WY = 0;
				$ TM2C STOP;
				$ TM3C STOP;
			}
			else
			{
				PWM_Num_WY--;
			}
		}
		TM2B = PWM_Num_WY;
		TM3B = PWM_Num_WY;	
	}
}