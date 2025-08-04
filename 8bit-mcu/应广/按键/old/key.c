// SL:Short and Long press 

#define KEY_MODE1_SINGLE 			1
#define KEY_MODE2_RELEASE_DO 		0
#define KEY_MODE3_SL_SINGLE_DELAY 	0
#define KEY_MODE4_SL_SINGLE_TIMED 	0
#define KEY_MODE5_2PIN_3KEYS 		0
#define KEY_MODE6_SL_MULTI_DELAY 	0
#define KEY_NUM 					4  // ������
#if KEY_NUM == 0 || KEY_NUM > 4
.error KEY_NUM  donot set 0 or set more then 4
#endif


#if KEY_MODE1_SINGLE

/***************** ������������ִ�У� *************************/

#define		Key_Filter_Time 2000 //�����˲�ʱ��

byte	Key_Icnt;
bit		Key_Sign;

void Scan_Key(void)
{
	if (Key_Sign)
	{
		if (!Key)
		{
			Key_Icnt--;
			if (Key_Icnt == 0)
			{
				Key_Sign = 0;
				/* USER CODE BEGIN */
				
				/* USER CODE END */
			}
		}
		else
		{
			Key_Icnt = Key_Filter_Time;
		}
	}
	else
	{
		if (Key) // �����ͷź�
		{
			Key_Sign = 1; // ����ɨ�谴��
			Key_Icnt = Key_Filter_Time;
		}
	}
}
#endif /* KEY_MODE1 */

#if KEY_MODE2_RELEASE_DO

/***************** �����������ֺ�ִ�У� *************************/

void Scan_Key(void)
{
	word Icnt = 1000;
	while (1)
	{
		if (!Key)
		{
			Icnt--;
			if (Icnt == 0)
			{
				// User add code
				while (Key == 0) // �ȴ������ͷ�
					nop;
				break;
			}
		}
		else
		{
			break;
		}
	}
}
#endif /* KEY_MODE2 */

#if KEY_MODE3_SL_SINGLE_DELAY

/***************** �����������̰������������� *************************/

#define	Press_Filt_Time 100 		//�����˲�ʱ��,�ö�ʱ�������˲�
#define	Long_Press_Time 150000  	//�����˲�ʱ��,ȡ����ʱ��Ƶ��

bit Key_Keep;
bit Key_Long_Sign;
byte Delay1;
byte Delay0;

void	Scan_Key(void)
{
	if (Key_Keep == 0)
	{
		Delay1 = Press_Filt_Time;
		if (Key == 0)
		{
			Delay0--;
			if (Delay0 == 0) //����ȷʵ������
				Key_Keep = 1; //������������ּ��
				Key_Long_Sign = 0;
				word Delay_Icnt = 0;
				
				//���볤��ǰ������
				
				while (!Key) //�ȴ����жϰ����Ƿ񳤰�
				{
					Delay_Icnt++;
					if (Delay_Icnt >= Long_Press_Time) //һ��ʱ���ȷ���ǳ���
					{
						Key_Long_Sign = 1;
						break;
					}
				}
				if (Key_Long_Sign) //����
				{
					// User add code
				}
				else //�̰�
				{
					// User add code
				}
			}
		}
		else
		{
			Delay0 = Press_Filt_Time;//�ް������������˲�ֵ
		}
	}
	else
	{
		Delay0 = Press_Filt_Time;
		if (Key) //�������
		{
			Delay1--;
			if (Delay1 == 0)
			{
				Key_Keep = 0; //�����֣����½��밴�����
			}
		}
		else
		{
			Delay1 = Press_Filt_Time; //�����������˲�ֵ
		}
	}
}

#endif /* KEY_MODE3 */

#if KEY_MODE4_SL_SINGLE_TIMED

/***************** �����������̰��������������� *************************/

#define	Press_Filt_Time 100 		//�����˲�ʱ�䣨�ö�ʱ�������˲���
#define	Long_Press_Time 800-100  	//����ʱ�䣺800ms

dword Delay_Icnt;
byte  Delay1;
byte  Delay0;
bit	  Key_Keep;
bit   Key_Long_Sign;
bit	  Judging_Flag;
bit	  Judged_Flag;

void Scan_Key(void)
{
	if(!Judging_Flag && !Judged_Flag)
	{
		if (Key_Keep == 0)
		{
			Delay1 = Press_Filt_Time;
			if (!Key)
			{
				Delay0--;
				if (Delay0 == 0) // ����ȷʵ������
				{
					Key_Keep = 1;			
					Key_Long_Sign = 0;
					Delay_Icnt = 0;
					Judging_Flag = 1; // ���볤�̰��ж�	
				}
			}
			else
			{
				Delay0 = Press_Filt_Time;
			}
		}
		else
		{
			Delay0 = Press_Filt_Time;
			if (Key1)
			{
				Delay1--;
				if (Delay1 == 0) // ���ֺ�
				{
					Key_Keep = 0;
				}
			}
			else
			{
				Delay1 = Press_Filt_Time;
			}
		}
	}
	else if(Judging_Flag) // ���̰��ж�
	{
		if(!Key)
		{
			Delay_Icnt++;
			if (Delay_Icnt >= Long_Press_Time) // һ��ʱ���ȷ���ǳ���
			{
				Key_Long_Sign = 1;
				Judging_Flag = 0;
				Judged_Flag = 1;
			}
		}
		else
		{
			Judging_Flag = 0;
			Judged_Flag = 1;
		}
	}
	else if(Judged_Flag) //���̰�����
	{
		Judged_Flag = 0;
		if (Key_Long_Sign) //����
		{
			/* USER CODE BEGIN */
			
			/* USER CODE END */
		}
		else //�̰�
		{
			/* USER CODE BEGIN */
			
			/* USER CODE END */
		}
	}
}
#endif /* KEY_MODE4 */

#if KEY_MODE5_2PIN_3KEYS

/***************** 2���Ÿ���3���� *************************/

//K2���½ӵ�Ϊ�͵�ƽ��ִ�в���1��
//K3���½ӵ�Ϊ�͵�ƽ��ִ�в���2��
//K2��K3ͬʱ���£�ִ�в���3,�г��̰�

#define	Press_Filt_Time 100 		//�����˲�ʱ��
#define	Long_Press_Time 150000  //�����˲�ʱ��,180000

//Key
byte	Delay1;
byte	Delay0;
bit 	Key_Keep;
bit 	Key_Long_Sign;

void Scan_Key(void)
{
	if (Key_Keep == 0)
	{
		Delay1 = Press_Filt_Time;
		if (!K2 && K3)
		{
			Delay0--;
			if (Delay0 == 0)
			{
				Key_Keep = 1;
				//ִ��1��
				
			}

		}
		else if (!K3 && K2)
		{	
			Delay0--;
			if (Delay0 == 0)
			{
				Key_Keep = 1;
				//ִ��2��
				
			}

		}
		else if (K2 && K3)
		{
			$ K2 out,low; //������һ������
			.delay 2*100
			if(!K3) //�ж���һ���Ƿ���ͬ
			{
				Delay0--;
				if (Delay0 == 0)
				{
					Key_Keep = 1;
					Key_Long_Sign = 0;
					dword Delay_Icnt = 0;

					//���볤��ǰ������
					
					while (!K2 && !K3) //�ȴ����жϰ����Ƿ񳤰�
					{
						Delay_Icnt++;
						if (Delay_Icnt >= Long_Press_Time) //һ��ʱ���ȷ���ǳ���
						{
							Key_Long_Sign = 1;
							break; //�˳�����ɨ��
						}
					}

					if (Key_Long_Sign) //����
					{
						/* USER CODE BEGIN */

						/* USER CODE END */
					}
					else //�̰�
					{
						/* USER CODE BEGIN */
						
						/* USER CODE END */
					}
				}
			}
			else
			{
				Delay0 = Press_Filt_Time;
			}
		}
		else
		{
			Delay0 = Press_Filt_Time;
		}

	}
	else
	{
		Delay0 = Press_Filt_Time;
		if (K2 && K3)
		{
			$ K2 out,low;
			.delay 4*100
			if(K3)
			{
				Delay1--;
				if (Delay1 == 0)//����
				{
					Key_Keep = 0;				
				}
			}
			else
			{			
				Delay1 = Press_Filt_Time;
			}
		}
		else
		{
			Delay1 = Short_Press_Time;
		}

	}

	$ K2 in,pull; //K2����
}

#endif /* KEY_MODE5 */

#if KEY_MODE6_SL_MULTI_DELAY

/***************** �İ��������̰������������� *************************/

#define KEY_FILT_TIME 1500 // �����˲�ʱ��

#if (KEY_NUM >= 1)
word Key_Icnt1;
bit  Key_Sign1;
#endif
#if (KEY_NUM >= 2)
word Key_Icnt2;
bit  Key_Sign2;
#endif
#if (KEY_NUM >= 3)
word Key_Icnt3;
bit  Key_Sign3;
#endif
#if (KEY_NUM >= 4)
word Key_Icnt4;
bit  Key_Sign4;
#endif

#if (KEY_NUM >= 1)
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
#endif /* KEY1 */

#if (KEY_NUM >= 2)
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
            Add_Sign_R = 0;
            /* USER CODE END */
        }
    }
}
#endif /* KEY2 */

#if (KEY_NUM >= 3)
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
        if(KEY3_PIN) // �����ͷź�
        {
            Key_Sign3 = 1; // ����ɨ�谴��
            Key_Icnt3 = KEY_FILT_TIME;
            /* USER CODE BEGIN */
			
            /* USER CODE END */    
        }
    }
}
#endif /* KEY3 */

#if (KEY_NUM >= 4)
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
        if(KEY4_PIN) // �����ͷź�
        {
            Key_Sign4 = 1; // ����ɨ�谴��
            Key_Icnt4 = KEY_FILT_TIME;
            /* USER CODE BEGIN */

            /* USER CODE END */
        }
    }
}
#endif /* KEY4 */

#endif /* KEY_MODE6 */