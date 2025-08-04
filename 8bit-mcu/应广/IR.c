$ IR in,pull;
IR_Receive();
De_IR_Data();

/***************** IR *************************/
/* IR Receive */
byte ReverseBits(byte num) 
{
    num = ((num & 0x55) << 1) | ((num & 0xAA) >> 1);
    num = ((num & 0x33) << 2) | ((num & 0xCC) >> 2);
    num = ((num & 0x0F) << 4) | ((num & 0xF0) >> 4);
    return num;
}
bit   Time_100us_Flag;
byte  Time_100us_Cnt;
word  Time_100us_Cnt2;
word  Time_100us_Cnt3;
bit	  IR_M_Grad_Flag;
bit	  IR_N_Grad_Flag;
byte  IR_Flag;
byte  IR_Data;
byte  IR_Mode = 0;
byte  i;
dword Data_Temp;
word  Ready_Data_Temp;
bit   IR_Sign;

void IR_Receive(void)
{
	switch(IR_Mode)
	{
		case 0: // Wait the start code
			if(!IR)
			{
	 			IR_Mode = 1;
				IR_Sign = 1;
				Time_100us_Cnt2 = 0; // Determine if there will be any signal appearing in the future period of time
			}
			else
			{
				IR_Mode = 0;
				if(Time_100us_Cnt2 > 1200) // If >100ms, Cancel long press content
				{
					/* USER CODE BEGIN */
					
					/* USER CODE END */
				}
			}
			Time_100us_Cnt = 0; 
			break;
 		case 1: // Judge the start code
			if(IR_Sign)
			{
				if(IR) // If low->high, to next
				{
					IR_Sign = 0;
				}
				else
				{
					nop;
				}
			}
			else
			{
				if(!IR) // Get the "low-high" pulse time
				{
					if(Time_100us_Cnt > 120 && Time_100us_Cnt < 150) // Judge the start code approx. time: 13.46ms
					{
						IR_Mode = 2; // Is start code£¬to next mode
						IR_Sign = 1;		
						Time_100us_Cnt = 0;
						i = 0;
						IR_Flag = 0;
					}
					else if(Time_100us_Cnt > 100 && Time_100us_Cnt < 120) // Judge the repeat code approx. time: 11.23ms
					{
						Time_100us_Cnt2 = 0; // Determine if there will be any signal appearing in the future period of time
					}
					else
					{
						IR_Mode = 0; // Return to wait the start code
					}
				}
				else
				{
					nop;
				}
			}
			break;
		case 2: // Judge the data code is 0 or 1 and record it
			if(IR_Sign)
			{
				if(IR) // If low->high, to next
				{
					IR_Sign = 0;
				}
			}
			else
			{
				if(!IR) // Get the "low-high" pulse time     data 0£º1.126ms    data 1£º2.25ms
				{
					if(Time_100us_Cnt >= 20) // '1'
					{
						Data_Temp <<= 1;
						Data_Temp |= 0x00000001;
					}
					else // '0'
					{
						Data_Temp <<= 1;
						Data_Temp &= 0xFFFFFFFE;
					}
					Time_100us_Cnt = 0;				
					IR_Sign = 1;
					i++;
					if(i == 32) // Move left 32 times, all data accepted, enter the next mode
					{
						IR_Mode = 3;
					}
				}
				else
				{
					nop;
				}
			}
			break;
		case 3:
			Ready_Data_Temp$1 = Data_Temp$3;
			Ready_Data_Temp$0 = Data_Temp$2;			
			if(Ready_Data_Temp == 0x00FF) // User code: 0x00FF
			{
				IR_Data = Data_Temp$1;	// Get the section of data cade
				IR_Data = ReverseBits(IR_Data);
				IR_Flag = 1;
				//.printf("%x\n",IR_Data); // For debug
			}
			Data_Temp = 0;
			IR_Mode = 0;
			Time_100us_Cnt2 = 0;
			break;
	}
}
/* IR Signal Process */
void De_IR_Data()
{
	if(IR_Flag)
	{
		if(IR_Data == 0x45)
		{
			IR_Flag = 0;

		}
		else if(IR_Data == 0x07)
		{
			IR_Flag = 0;

		}
		else if(IR_Data == 0x09)
		{
			IR_Flag = 0;

		}
		else if(IR_Data == 0x40)
		{

		}
		else if(IR_Data == 0x47)
		{

		}
		else if(IR_Data == 0x5A)
		{

		}
		else if(IR_Data == 0x08)
		{

		}
	}
}
/***************** IR-Interrupt *************************/
Time_100us_Flag = 1;
Time_100us_Cnt++;
Time_100us_Cnt2++;
/* IR anti-interference */
if(IR)
{
    Time_100us_Cnt3++;
    if(Time_100us_Cnt3 >= 100) // 10ms
    {
        IR_Mode = 0;
    }
}
else
{
    Time_100us_Cnt3 = 0;
}