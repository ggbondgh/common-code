



/*---------------------------------------����������ִ�У�---------------------------------------------------*/

#define	Key_Filter_Time 2000 //�����˲�ʱ��

byte Key_Icnt;
bit	 Key_Sign;

void Scan_key(void)
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
		if (Key)
		{
			Key_Sign = 1;
			Key_Icnt = Key_Filter_Time;
			/* USER CODE BEGIN */
			
			/* USER CODE END */
		}
	}
}




/*---------------------------------------���������ֺ�ִ�У�---------------------------------------------------*/

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
				/* USER CODE BEGIN */
				
				/* USER CODE END */
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




/*---------------------------------------���������̰�������������---------------------------------------------------*/

#define	Press_Filt_Time 100 		//�����˲�ʱ��,�ö�ʱ�������˲�
#define	Long_Press_Time 150000  	//�����˲�ʱ��,ȡ����ʱ��Ƶ��

bit  Key_Keep;
bit  Key_Long_Sign;
byte Delay1;
byte Delay0;

void Scan_Key(void)
{
	if (Key_Keep == 0)
	{
		Delay1 = Press_Filt_Time;
		if (Key == 0)
		{
			Delay0--;
			if (Delay0 == 0) // ����ȷʵ������
				Key_Keep = 1; // ������������ּ��
				Key_Long_Sign = 0;
				word Delay_Icnt = 0;
				
				//���볤��ǰ������
				/* USER CODE BEGIN */
				
				/* USER CODE END */
				
				while (!Key) // �ȴ����жϰ����Ƿ񳤰�
				{
					Delay_Icnt++;
					if (Delay_Icnt >= Long_Press_Time) // һ��ʱ���ȷ���ǳ���
					{
						Key_Long_Sign = 1;
						break;
					}
				}
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
		else
		{
			Delay0 = Press_Filt_Time; // �ް������������˲�ֵ
		}
	}
	else
	{
		Delay0 = Press_Filt_Time;
		if (Key) // �������
		{
			Delay1--;
			if (Delay1 == 0)
			{
				Key_Keep = 0; // �����֣����½��밴�����
			}
		}
		else
		{
			Delay1 = Press_Filt_Time; // �����������˲�ֵ
		}
	}
}



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





/*---------------------------------------2���Ÿ���3����---------------------------------------------------*/

//K2���½ӵ�Ϊ�͵�ƽ��ִ�в���1��
//K3���½ӵ�Ϊ�͵�ƽ��ִ�в���2��
//K2��K3ͬʱ���£�ִ�в���3,�г��̰�


#define	Press_Filt_Time 100 		//�����˲�ʱ��
#define	Long_Press_Time 150000  //�����˲�ʱ��,180000

byte Delay1;
byte Delay0;
bit  Key_Keep;
bit  Key_Long_Sign;


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
				/* USER CODE BEGIN */
				
				/* USER CODE END */
			}

		}
		else if (!K3 && K2)
		{	
			Delay0--;
			if (Delay0 == 0)
			{
				Key_Keep = 1;
				//ִ��2��
				/* USER CODE BEGIN */
				
				/* USER CODE END */	
			}

		}
		else if (K2 && K3)
		{
			$ K2 out,low; // ������һ������
			.delay 2*100
			if(!K3) // �ж���һ���Ƿ���ͬ
			{
				Delay0--;
				if (Delay0 == 0)
				{
					Key_Keep = 1;
					Key_Long_Sign = 0;
					dword Delay_Icnt = 0;

					//���볤��ǰ������
					/* USER CODE BEGIN */
					
					/* USER CODE END */
					
					while (!K2 && !K3) // �ȴ����жϰ����Ƿ񳤰�
					{
						Delay_Icnt++;
						if (Delay_Icnt >= Long_Press_Time) // һ��ʱ���ȷ���ǳ���
						{
							Key_Long_Sign = 1;
							break; // �˳�����ɨ��
						}
					}

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
				if (Delay1 == 0) // ����
				{
					Key_Keep = 0;
					/* USER CODE BEGIN */
					
					/* USER CODE END */			
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

	$ K2 in,pull; // K2����
}




/*--------------------------------------- ---------------------------------------------------*/




