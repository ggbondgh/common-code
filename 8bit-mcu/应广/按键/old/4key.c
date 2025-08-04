#define KEY_FILT_TIME 2000 // 定义滤波时长

word Key_Icnt1;
bit  Key_Sign1;
word Key_Icnt2;
bit  Key_Sign2;
word Key_Icnt3;
bit  Key_Sign3;
word Key_Icnt4;
bit  Key_Sign4;


void Scan_Key1(void)
{
    if(Key_Sign1)
    {
        if(!KEY1_PIN)
        {
            Key_Icnt1--;
            if(Key_Icnt1 == 0)
            {
                Key_Sign1 = 0;
                /* USER CODE BEGIN */

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
        if(KEY1_PIN) // 按键释放后
        {
            Key_Sign1 = 1; // 重新扫描按键
            Key_Icnt1 = KEY_FILT_TIME;
            /* USER CODE BEGIN */
            
            /* USER CODE END */
        }
    }
}

void Scan_Key2(void)
{
    if(Key_Sign2)
    {
        if(!KEY2_PIN)
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
        if(KEY2_PIN) // 按键释放后
        {
            Key_Sign2 = 1; // 重新扫描按键
            Key_Icnt2 = KEY_FILT_TIME;
            /* USER CODE BEGIN */

            /* USER CODE END */
        }
    }
}

void Scan_Key3(void)
{
    if(Key_Sign3)
    {
        if(!KEY3_PIN)
        {
            Key_Icnt3--;
            if(Key_Icnt3 == 0)
            {
                Key_Sign3 = 0;
                /* USER CODE BEGIN */

                /* USER CODE END */
            }
        }
        else
        {
            Key_Icnt3 = KEY_FILT_TIME;
        }
    }
    else
    {
        if(KEY3_PIN) // 按键释放后
        {
            Key_Sign3 = 1; // 重新扫描按键
            Key_Icnt3 = KEY_FILT_TIME;
            /* USER CODE BEGIN */
			
            /* USER CODE END */    
        }
    }
}

void Scan_Key4(void)
{
    if(Key_Sign4)
    {
        if(!KEY4_PIN)
        {
            Key_Icnt4--;
            if(Key_Icnt4 == 0)
            {
                Key_Sign4 = 0;
                /* USER CODE BEGIN */

                /* USER CODE END */
            }
        }
        else
        {
            Key_Icnt4 = KEY_FILT_TIME;
        }
    }
    else
    {
        if(KEY4_PIN) // 按键释放后
        {
            Key_Sign4 = 1; // 重新扫描按键
            Key_Icnt4 = KEY_FILT_TIME;
            /* USER CODE BEGIN */

            /* USER CODE END */
        }
    }
}