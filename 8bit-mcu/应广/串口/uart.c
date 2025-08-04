
#if (UART_EN == 1)


//------------------���ڽ���----------------------------
#if (UART_RECEIVE_EN == 1)

#define	ONE_BIT_DELAY 417  //�����ֵ= SYSCLK*(1/Baud_Rate)��SYSCLK��ʱ��Ƶ��ֵ��1MHz����1000000��Baud_Rate�ǲ����ʣ�
#define HALF_BIT_DELAY ONE_BIT_DELAY/2 //�������λ

RX	=>	PA.5  //��������

byte Data = 0;

static void UART_Receive (void)
{

	byte temp_Data = 0;
	byte bit_cnt = 0;

	while(RX)NULL; //�ȴ���ʼλ

	.delay (ONE_BIT_DELAY + HALF_BIT_DELAY)

	while (bit_cnt < 8) //8������λ�����յ�λ���ո�λ
	{
		temp_Data=temp_Data >> 1; //������һλ

		if(RX)
		{
			temp_Data |= 0x80;
		}
		else
		{
			temp_Data &= 0x7f;
		}

		bit_cnt++;

		.delay ONE_BIT_DELAY
	}
	
	while(!Rx)NULL; //ֹͣλ���ߵ�ƽ����

	Data = temp_Data; //��ʱ���������ⲿ����
	
}

#endif
//------------------���ڷ���----------------------------
#if (UART_SEND_EN == 1)

TX	=>	PA.0 //��������

byte uart_send_c = 0;
byte uart_send_val; //Ҫ���͵�����
byte SYS_CLKMD;
byte CLKMD_BK;

void Clock_Adjust(void) //ʱ�ӵ���
{
#if Uart_Work_SYSCLK == '8M'
	{
		CLKMD_BK = 0x34; // 8M
	}
#elseif Uart_Work_SYSCLK == '4M'
	{
		CLKMD_BK = 0x14; // 4M
	}
#elseif Uart_Work_SYSCLK == '2M'
	{
		CLKMD_BK = 0x3c; // 2M
	}
#else
	{
		Uart_Work_SYSCLK = > '1M' CLKMD_BK = 0x1c; // 1M
	}
#endif
	CLKMD = CLKMD_BK; //��ϵͳʱ���޸�Ϊ�趨��UARTʱ��
	nop;			  //�ȴ�
}

void Uart_Send_One_Byte(void) // 38400
{
	$ TX out, low; //��ʼλ
	.delay ONE_BIT_DELAY_SYSCLK_CNT // 42us

	byte bit_cnt = 0;
	while (bit_cnt < 8) //8������λ���ȷ���λ�ٷ���λ
	{
		SR uart_send_c; //����һλ

		.swapc_o TX; //��λ��C����IO�˿�

		bit_cnt++;

		.delay ONE_BIT_DELAY_SYSCLK_CNT
	}

	TX = 1; //ֹͣλ
	.delay ONE_BIT_DELAY_SYSCLK_CNT

	$ TX in;
}

void Uart_Send_Data(void)
{
	Clock_Adjust(); // ��ϵͳʱ���޸�Ϊ�趨��UARTʱ��

	uart_send_c = uart_send_val;
	Uart_Send_One_Byte();
	
//	uart_send_c = u16_get_val $ 0;
//	Uart_Send_One_Byte();
//	uart_send_c = u16_get_val $ 1;
//	Uart_Send_One_Byte();

	CLKMD = SYS_CLKMD; // ���ݷ��ͽ������л�ԭ����ϵͳʱ��
	nop;			   // �ȴ�
}

#endif

#endif

//------------------���ڷ���ͷ�ļ�----------------------------
#define UART_EN 1               //Uartʹ�ܣ�default:1
#define UART_BaudRate 9600      //UART������:7200 9600, 19200, 38400, 56000
#define Uart_Work_SYSCLK '4M'
#define Interrupt_Uart 0        //UART�жϼ�����˿�ѡ��
                                //0:PA0�ж�  1:PA5�ж�	2:PB0�ж�	default:0
								//ע��:����ʱ��֧��PA5��PB0�ж�
 								//ʵ��IC��¼����ʹ��PA5
T_Watch_Set:
														
		//���ݲ���������,�����λ��һλ��������λ����ʱֵ,��λ:ϵͳʱ��
		#ifdef	UART_BaudRate
			#if	    (UART_BaudRate == 7200)
				#ifdef	Uart_Work_SYSCLK
					#if	(Uart_Work_SYSCLK == '250K')
						HALF_BIT_DELAY_SYSCLK_CNT	=> 8	//=52(-10) ��λ��ʱ����ֵ,��λ:ϵͳʱ��										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 25	//=104(-10)
					#endif
				#endif
			#elif	(UART_BaudRate == 9600)
				#ifdef	Uart_Work_SYSCLK
					#if	(Uart_Work_SYSCLK == '250K')
						HALF_BIT_DELAY_SYSCLK_CNT	=> 3	//=52(-10) ��λ��ʱ����ֵ,��λ:ϵͳʱ��										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 16	//=104(-10)
					#elif	(Uart_Work_SYSCLK == '1M')
						HALF_BIT_DELAY_SYSCLK_CNT	=> 42	//=52(-10) ��λ��ʱ����ֵ,��λ:ϵͳʱ��										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 94	//=104(-10)
					#elif	(Uart_Work_SYSCLK == '2M')
					    HALF_BIT_DELAY_SYSCLK_CNT	=> 94	//=104(-10) ��λ��ʱ����ֵ,��λ:ϵͳʱ��										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 198	//=208(-10)
					#elif	(Uart_Work_SYSCLK == '4M')
						HALF_BIT_DELAY_SYSCLK_CNT	=> 198	//=208(-10) ��λ��ʱ����ֵ,��λ:ϵͳʱ��										
					    ONE_BIT_DELAY_SYSCLK_CNT	=> 407	//=417(-10)
				    #elif	(Uart_Work_SYSCLK == '8M')
						HALF_BIT_DELAY_SYSCLK_CNT	=> 407	//=417(-10) ��λ��ʱ����ֵ,��λ:ϵͳʱ��										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 823	//=833(-10)
					#else	//Ĭ�� Uart_Work_SYSCLK ='2M'				
						HALF_BIT_DELAY_SYSCLK_CNT	=> 94	//=104(-10) ��λ��ʱ����ֵ,��λ:ϵͳʱ��										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 198	//=208(-10)
					#endif
				#else	//Ĭ�� Uart_Work_SYSCLK ='2M'
			
					HALF_BIT_DELAY_SYSCLK_CNT	=> 94	//=104(-10) ��λ��ʱ����ֵ,��λ:ϵͳʱ��										
					ONE_BIT_DELAY_SYSCLK_CNT	=> 198	//=208(-10)
				#endif
			#elif	(UART_BaudRate == 19200)
				#ifdef	Uart_Work_SYSCLK
					#if	(Uart_Work_SYSCLK == '1M')
							
					#elif	(Uart_Work_SYSCLK == '2M')
						HALF_BIT_DELAY_SYSCLK_CNT	=> 42	//=52(-10) ��λ��ʱ����ֵ,��λ:ϵͳʱ��										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 94	//=104(-10)
					#elif	(Uart_Work_SYSCLK == '4M')
						HALF_BIT_DELAY_SYSCLK_CNT	=> 94	//=104(-10) ��λ��ʱ����ֵ,��λ:ϵͳʱ��										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 198	//=208(-10)
					#elif	(Uart_Work_SYSCLK == '8M')
						HALF_BIT_DELAY_SYSCLK_CNT	=> 198	//=208(-10) ��λ��ʱ����ֵ,��λ:ϵͳʱ��										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 407	//=417(-10)
					#else	
					
						HALF_BIT_DELAY_SYSCLK_CNT	=> 42	//=52(-10) ��λ��ʱ����ֵ,��λ:ϵͳʱ��										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 94	//=104(-10)
					#endif
				#else		
					HALF_BIT_DELAY_SYSCLK_CNT	=> 42	//=52(-10) ��λ��ʱ����ֵ,��λ:ϵͳʱ��										
					ONE_BIT_DELAY_SYSCLK_CNT	=> 94	//=104(-10)
				#endif
			#elif	(UART_BaudRate == 38400)
				#ifdef	Uart_Work_SYSCLK
					#if	(Uart_Work_SYSCLK == '1M')
					
					#elif	(Uart_Work_SYSCLK == '2M')		//��������ֵ( - ָ����ʱ����ֵ)
						HALF_BIT_DELAY_SYSCLK_CNT	=> 16	//=26(-10) ��λ��ʱ����ֵ,��λ:ϵͳʱ��										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 42	//=52(-10)
					#elif	(Uart_Work_SYSCLK == '4M')
						HALF_BIT_DELAY_SYSCLK_CNT	=> 42	//=52(-10) ��λ��ʱ����ֵ,��λ:ϵͳʱ��										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 96	//=104(-10)
					#elif	(Uart_Work_SYSCLK == '8M')
						HALF_BIT_DELAY_SYSCLK_CNT	=> 94	//=104(-10) ��λ��ʱ����ֵ,��λ:ϵͳʱ��										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 198	//=208(-10)
					#else
					
						HALF_BIT_DELAY_SYSCLK_CNT	=> 16	//=26(-10) ��λ��ʱ����ֵ,��λ:ϵͳʱ��										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 42	//=52(-10)
					#endif
				#else	
					HALF_BIT_DELAY_SYSCLK_CNT	=> 16	//=26(-10) ��λ��ʱ����ֵ,��λ:ϵͳʱ��										
					ONE_BIT_DELAY_SYSCLK_CNT	=> 42	//=52(-10)
				#endif
			#else
				#if	(UART_BaudRate != 56000)
				
				#endif

				#ifdef	Uart_Work_SYSCLK
					#if		(Uart_Work_SYSCLK == '1M')
				
					#elif	(Uart_Work_SYSCLK == '2M')		//��������ֵ( - ָ����ʱ����ֵ)
						HALF_BIT_DELAY_SYSCLK_CNT	=> 8	//=18(-10) ��λ��ʱ����ֵ,��λ:ϵͳʱ��										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 26	//=36(-10)
					#elif	(Uart_Work_SYSCLK == '4M')
						HALF_BIT_DELAY_SYSCLK_CNT	=> 26	//=36(-10) ��λ��ʱ����ֵ,��λ:ϵͳʱ��										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 61	//=71(-10)
					#elif	(Uart_Work_SYSCLK == '8M')
						HALF_BIT_DELAY_SYSCLK_CNT	=> 61	//=71(-10) ��λ��ʱ����ֵ,��λ:ϵͳʱ��										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 132	//=142(-10)
					#else
						HALF_BIT_DELAY_SYSCLK_CNT	=> 8	//=18(-10) ��λ��ʱ����ֵ,��λ:ϵͳʱ��										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 26	//=36(-10)
					#endif
				#else	
					HALF_BIT_DELAY_SYSCLK_CNT	=> 8	//=18(-10) ��λ��ʱ����ֵ,��λ:ϵͳʱ��										
					ONE_BIT_DELAY_SYSCLK_CNT	=> 26	//=36(-10)
				#endif			
			#endif
		#else	
			#ifdef	Uart_Work_SYSCLK
				#if	(Uart_Work_SYSCLK == '1M')
				
				#elif	(Uart_Work_SYSCLK == '2M')
					HALF_BIT_DELAY_SYSCLK_CNT	=> 8	//=18(-10) ��λ��ʱ����ֵ,��λ:ϵͳʱ��										
					ONE_BIT_DELAY_SYSCLK_CNT	=> 26	//=36(-10)
				#elif	(Uart_Work_SYSCLK == '4M')
					HALF_BIT_DELAY_SYSCLK_CNT	=> 26	//=36(-10) ��λ��ʱ����ֵ,��λ:ϵͳʱ��										
					ONE_BIT_DELAY_SYSCLK_CNT	=> 61	//=71(-10)
				#elif	(Uart_Work_SYSCLK == '8M')
					HALF_BIT_DELAY_SYSCLK_CNT	=> 61	//=71(-10) ��λ��ʱ����ֵ,��λ:ϵͳʱ��										
					ONE_BIT_DELAY_SYSCLK_CNT	=> 132	//=142(-10)
				#else	
					HALF_BIT_DELAY_SYSCLK_CNT	=> 8	//=18(-10) ��λ��ʱ����ֵ,��λ:ϵͳʱ��										
					ONE_BIT_DELAY_SYSCLK_CNT	=> 26	//=36(-10)
				#endif
			#else			
				HALF_BIT_DELAY_SYSCLK_CNT	=> 8	//=18(-10) ��λ��ʱ����ֵ,��λ:ϵͳʱ��										
				ONE_BIT_DELAY_SYSCLK_CNT	=> 26	//=36(-10)
			#endif
		#endif