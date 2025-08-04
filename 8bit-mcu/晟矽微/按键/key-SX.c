#define KEY_FILT_TIME 1500 // ?????????1MHZ?1500
#define NO_SIGN    0
#define WAIT_SIGN  1
#define SHORT_SIGN 2
#define LONG_SIGN  3

uint8_t Key_Icnt1;
uint8_t  Key_Sign1;
uint8_t Time_10ms_Cnt;
uint8_t	 Time_10ms_Flag;
uint8_t Touch_Sign;
uint8_t  Long_trigger;
uint8_t  Done_trigger;

void Scan_Key_Mode(void)
{
    if(Key_Sign1)
    {
        if(!Key1)
        {
            Key_Icnt1--;
            if(Key_Icnt1 == 0)
            {
                Key_Sign1 = 0;
                /* USER CODE BEGIN */
                Signal_X = 1;
                /* USER CODE END */
            }
        }
        else
        {
            Key_Icnt1 = KEY_FILT_TIME;
        }
    }
    else
    {
        if(Key1) // ?????
        {
            Key_Sign1 = 1; // ??????
            Key_Icnt1 = KEY_FILT_TIME;
            /* USER CODE BEGIN */
            Signal_X = 0;
            /* USER CODE END */    
        }
    }
}
void Key_Judge(void)
{
    Time_10ms_Cnt++;
    
    /* Short-Long Judge */
    if(Signal_X && Time_10ms_Cnt > 50) // Long touch, over 500ms
    {
        Time_10ms_Cnt = 50; // Fix the time??in case not overflow
        Touch_Sign = LONG_SIGN;
    }
    else if(Signal_X) 
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


uint8_t  Key_Icnt2;
uint8_t  Key_Sign2;
void Scan_Key_Power(void)
{
    if(Key_Sign2)
    {
        if(!Key1)
        {
            Key_Icnt2--;
            if(Key_Icnt2 == 0)
            {
                Key_Sign2 = 0;
                /* USER CODE BEGIN */
                
                /* USER CODE END */
            }
        }
        else
        {
            Key_Icnt2 = KEY_FILT_TIME;
        }
    }
    else
    {
        if(Key1) // ?????
        {
            Key_Sign2 = 1; // ??????
            Key_Icnt2 = KEY_FILT_TIME;
            /* USER CODE BEGIN */
            
            /* USER CODE END */    
        }
    }
}

