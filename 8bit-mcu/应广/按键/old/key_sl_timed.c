/*---------------------------------------���������̰���������������---------------------------------------------------*/

#define	Press_Filt_Time 100 		// �����˲�ʱ�䣨�ö�ʱ�������˲���
#define	Long_Press_Time 800-100  	// ����ʱ�䣺800ms

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
	else if(Judged_Flag) // ���̰�����
	{
		Judged_Flag = 0;
		if (Key_Long_Sign) // ����
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