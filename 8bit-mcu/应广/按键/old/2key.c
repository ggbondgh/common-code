#define KEY_FILT_TIME 2000 // �����˲�ʱ��

word Key_Icnt1;
bit  Key_Sign1;
word Key_Icnt2;
bit  Key_Sign2;


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
        if(KEY1_PIN) // �����ͷź�
        {
            Key_Sign1 = 1; // ����ɨ�谴��
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
        if(KEY2_PIN) // �����ͷź�
        {
            Key_Sign2 = 1; // ����ɨ�谴��
            Key_Icnt2 = KEY_FILT_TIME;
            /* USER CODE BEGIN */

            /* USER CODE END */
        }
    }
}

