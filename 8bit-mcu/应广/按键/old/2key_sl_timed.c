
#define	Press_Filt_Time 100 		//�����˲�ʱ�䣨�ö�ʱ�������˲���
#define	Long_Press_Time 800-100  	//����ʱ�䣺800ms


//���Ŷ���
Key1	=>	PA.7  //Vol+
Key2	=>	PA.5  //Vol-

//Key
dword	Delay_Icnt1;
dword 	Delay_Icnt2;
byte	Delay0;
byte	Delay1;
byte	Delay2;
byte	Delay3;
bit		Key_Keep1;
bit		Key_Keep2;
bit		Key_Long_Sign1;
bit		Key_Long_Sign2;
bit	  	Judging_Flag1;
bit	  	Judging_Flag2;
bit	  	Judged_Flag1;
bit	  	Judged_Flag2;


void Scan_Key1(void) //Vol+
{
	if(!Judging_Flag1 && !Judged_Flag1)
	{
		if (Key_Keep1 == 0)
		{
			Delay1 = Press_Filt_Time;
			if (!Key1)
			{
				Delay0--;
				if (Delay0 == 0) //����ȷʵ������
				{
					Key_Keep1 = 1;			
					Key_Long_Sign1 = 0;
					Delay_Icnt1 = 0;
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
				if (Delay1 == 0) //���ֺ�
				{
					Key_Keep1 = 0;
				}
			}
			else
			{
				Delay1 = Press_Filt_Time;
			}
		}
	}
	else if(Judging_Flag1) //���̰��ж�
	{
		if(!Key1)
		{
			Delay_Icnt1++;
			if (Delay_Icnt1 >= Long_Press_Time) //һ��ʱ���ȷ���ǳ���
			{
				Key_Long_Sign1 = 1;
				Judging_Flag1 = 0;
				Judged_Flag1 = 1;
			}
		}
		else
		{
			Judging_Flag1 = 0;
			Judged_Flag1 = 1;
		}
	}
	else if(Judged_Flag1) //���̰�����
	{
		Judged_Flag1 = 0;
		if (Key_Long_Sign1) //����
		{
			// User Code
		}
		else //�̰�
		{
			// User Code
		}
	}
}

void Scan_Key2(void) //Vol-
{
	if(!Judging_Flag2 && !Judged_Flag2)
	{
		if (Key_Keep2 == 0)
		{
			Delay3 = Press_Filt_Time;
			if (!Key2)
			{
				Delay2--;
				if (Delay2 == 0) //����ȷʵ������
				{
					Key_Keep2 = 1;			
					Key_Long_Sign2 = 0;
					Delay_Icnt2 = 0;
				}
			}
			else
			{
				Delay2 = Press_Filt_Time;
			}
		}
		else
		{
			Delay2 = Press_Filt_Time;
			if (Key2)
			{
				Delay3--;
				if (Delay3 == 0) //���ֺ�
				{
					Key_Keep2 = 0;
				}
			}
			else
			{
				Delay3 = Press_Filt_Time;
			}
		}
	}
	else if(Judging_Flag2) //���̰��ж�
	{
		if(!Key2)
		{
			Delay_Icnt2++;
			if (Delay_Icnt2 >= Long_Press_Time) //һ��ʱ���ȷ���ǳ���
			{
				Key_Long_Sign2 = 1;
				Judging_Flag2 = 0;
				Judged_Flag2 = 1;
			}
		}
		else
		{
			Judging_Flag2 = 0;
			Judged_Flag2 = 1;
		}
	}
	else if(Judged_Flag2) //���̰�����
	{
		Judged_Flag2 = 0;
		if (Key_Long_Sign2) //����
		{
			// User Code
		}
		else //�̰�
		{
			// User Code
		}
	}
}

