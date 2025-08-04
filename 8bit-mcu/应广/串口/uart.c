
#if (UART_EN == 1)


//------------------串口接收----------------------------
#if (UART_RECEIVE_EN == 1)

#define	ONE_BIT_DELAY 417  //定义的值= SYSCLK*(1/Baud_Rate)（SYSCLK是时钟频率值，1MHz就是1000000；Baud_Rate是波特率）
#define HALF_BIT_DELAY ONE_BIT_DELAY/2 //半个数据位

RX	=>	PA.5  //接收引脚

byte Data = 0;

static void UART_Receive (void)
{

	byte temp_Data = 0;
	byte bit_cnt = 0;

	while(RX)NULL; //等待起始位

	.delay (ONE_BIT_DELAY + HALF_BIT_DELAY)

	while (bit_cnt < 8) //8个数据位，先收低位再收高位
	{
		temp_Data=temp_Data >> 1; //先右移一位

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
	
	while(!Rx)NULL; //停止位，高电平跳出

	Data = temp_Data; //临时变量赋予外部变量
	
}

#endif
//------------------串口发送----------------------------
#if (UART_SEND_EN == 1)

TX	=>	PA.0 //发送引脚

byte uart_send_c = 0;
byte uart_send_val; //要发送的数据
byte SYS_CLKMD;
byte CLKMD_BK;

void Clock_Adjust(void) //时钟调整
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
	CLKMD = CLKMD_BK; //将系统时钟修改为设定的UART时钟
	nop;			  //等待
}

void Uart_Send_One_Byte(void) // 38400
{
	$ TX out, low; //起始位
	.delay ONE_BIT_DELAY_SYSCLK_CNT // 42us

	byte bit_cnt = 0;
	while (bit_cnt < 8) //8个数据位，先发低位再发高位
	{
		SR uart_send_c; //右移一位

		.swapc_o TX; //进位制C赋给IO端口

		bit_cnt++;

		.delay ONE_BIT_DELAY_SYSCLK_CNT
	}

	TX = 1; //停止位
	.delay ONE_BIT_DELAY_SYSCLK_CNT

	$ TX in;
}

void Uart_Send_Data(void)
{
	Clock_Adjust(); // 将系统时钟修改为设定的UART时钟

	uart_send_c = uart_send_val;
	Uart_Send_One_Byte();
	
//	uart_send_c = u16_get_val $ 0;
//	Uart_Send_One_Byte();
//	uart_send_c = u16_get_val $ 1;
//	Uart_Send_One_Byte();

	CLKMD = SYS_CLKMD; // 数据发送结束后，切回原来的系统时钟
	nop;			   // 等待
}

#endif

#endif

//------------------串口发送头文件----------------------------
#define UART_EN 1               //Uart使能，default:1
#define UART_BaudRate 9600      //UART波特率:7200 9600, 19200, 38400, 56000
#define Uart_Work_SYSCLK '4M'
#define Interrupt_Uart 0        //UART中断及传输端口选择
                                //0:PA0中断  1:PA5中断	2:PB0中断	default:0
								//注意:仿真时不支持PA5和PB0中断
 								//实际IC烧录建议使用PA5
T_Watch_Set:
														
		//根据波特率设置,定义半位和一位串口数据位的延时值,单位:系统时钟
		#ifdef	UART_BaudRate
			#if	    (UART_BaudRate == 7200)
				#ifdef	Uart_Work_SYSCLK
					#if	(Uart_Work_SYSCLK == '250K')
						HALF_BIT_DELAY_SYSCLK_CNT	=> 8	//=52(-10) 半位延时计数值,单位:系统时钟										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 25	//=104(-10)
					#endif
				#endif
			#elif	(UART_BaudRate == 9600)
				#ifdef	Uart_Work_SYSCLK
					#if	(Uart_Work_SYSCLK == '250K')
						HALF_BIT_DELAY_SYSCLK_CNT	=> 3	//=52(-10) 半位延时计数值,单位:系统时钟										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 16	//=104(-10)
					#elif	(Uart_Work_SYSCLK == '1M')
						HALF_BIT_DELAY_SYSCLK_CNT	=> 42	//=52(-10) 半位延时计数值,单位:系统时钟										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 94	//=104(-10)
					#elif	(Uart_Work_SYSCLK == '2M')
					    HALF_BIT_DELAY_SYSCLK_CNT	=> 94	//=104(-10) 半位延时计数值,单位:系统时钟										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 198	//=208(-10)
					#elif	(Uart_Work_SYSCLK == '4M')
						HALF_BIT_DELAY_SYSCLK_CNT	=> 198	//=208(-10) 半位延时计数值,单位:系统时钟										
					    ONE_BIT_DELAY_SYSCLK_CNT	=> 407	//=417(-10)
				    #elif	(Uart_Work_SYSCLK == '8M')
						HALF_BIT_DELAY_SYSCLK_CNT	=> 407	//=417(-10) 半位延时计数值,单位:系统时钟										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 823	//=833(-10)
					#else	//默认 Uart_Work_SYSCLK ='2M'				
						HALF_BIT_DELAY_SYSCLK_CNT	=> 94	//=104(-10) 半位延时计数值,单位:系统时钟										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 198	//=208(-10)
					#endif
				#else	//默认 Uart_Work_SYSCLK ='2M'
			
					HALF_BIT_DELAY_SYSCLK_CNT	=> 94	//=104(-10) 半位延时计数值,单位:系统时钟										
					ONE_BIT_DELAY_SYSCLK_CNT	=> 198	//=208(-10)
				#endif
			#elif	(UART_BaudRate == 19200)
				#ifdef	Uart_Work_SYSCLK
					#if	(Uart_Work_SYSCLK == '1M')
							
					#elif	(Uart_Work_SYSCLK == '2M')
						HALF_BIT_DELAY_SYSCLK_CNT	=> 42	//=52(-10) 半位延时计数值,单位:系统时钟										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 94	//=104(-10)
					#elif	(Uart_Work_SYSCLK == '4M')
						HALF_BIT_DELAY_SYSCLK_CNT	=> 94	//=104(-10) 半位延时计数值,单位:系统时钟										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 198	//=208(-10)
					#elif	(Uart_Work_SYSCLK == '8M')
						HALF_BIT_DELAY_SYSCLK_CNT	=> 198	//=208(-10) 半位延时计数值,单位:系统时钟										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 407	//=417(-10)
					#else	
					
						HALF_BIT_DELAY_SYSCLK_CNT	=> 42	//=52(-10) 半位延时计数值,单位:系统时钟										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 94	//=104(-10)
					#endif
				#else		
					HALF_BIT_DELAY_SYSCLK_CNT	=> 42	//=52(-10) 半位延时计数值,单位:系统时钟										
					ONE_BIT_DELAY_SYSCLK_CNT	=> 94	//=104(-10)
				#endif
			#elif	(UART_BaudRate == 38400)
				#ifdef	Uart_Work_SYSCLK
					#if	(Uart_Work_SYSCLK == '1M')
					
					#elif	(Uart_Work_SYSCLK == '2M')		//计算理论值( - 指令延时调整值)
						HALF_BIT_DELAY_SYSCLK_CNT	=> 16	//=26(-10) 半位延时计数值,单位:系统时钟										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 42	//=52(-10)
					#elif	(Uart_Work_SYSCLK == '4M')
						HALF_BIT_DELAY_SYSCLK_CNT	=> 42	//=52(-10) 半位延时计数值,单位:系统时钟										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 96	//=104(-10)
					#elif	(Uart_Work_SYSCLK == '8M')
						HALF_BIT_DELAY_SYSCLK_CNT	=> 94	//=104(-10) 半位延时计数值,单位:系统时钟										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 198	//=208(-10)
					#else
					
						HALF_BIT_DELAY_SYSCLK_CNT	=> 16	//=26(-10) 半位延时计数值,单位:系统时钟										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 42	//=52(-10)
					#endif
				#else	
					HALF_BIT_DELAY_SYSCLK_CNT	=> 16	//=26(-10) 半位延时计数值,单位:系统时钟										
					ONE_BIT_DELAY_SYSCLK_CNT	=> 42	//=52(-10)
				#endif
			#else
				#if	(UART_BaudRate != 56000)
				
				#endif

				#ifdef	Uart_Work_SYSCLK
					#if		(Uart_Work_SYSCLK == '1M')
				
					#elif	(Uart_Work_SYSCLK == '2M')		//计算理论值( - 指令延时调整值)
						HALF_BIT_DELAY_SYSCLK_CNT	=> 8	//=18(-10) 半位延时计数值,单位:系统时钟										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 26	//=36(-10)
					#elif	(Uart_Work_SYSCLK == '4M')
						HALF_BIT_DELAY_SYSCLK_CNT	=> 26	//=36(-10) 半位延时计数值,单位:系统时钟										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 61	//=71(-10)
					#elif	(Uart_Work_SYSCLK == '8M')
						HALF_BIT_DELAY_SYSCLK_CNT	=> 61	//=71(-10) 半位延时计数值,单位:系统时钟										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 132	//=142(-10)
					#else
						HALF_BIT_DELAY_SYSCLK_CNT	=> 8	//=18(-10) 半位延时计数值,单位:系统时钟										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 26	//=36(-10)
					#endif
				#else	
					HALF_BIT_DELAY_SYSCLK_CNT	=> 8	//=18(-10) 半位延时计数值,单位:系统时钟										
					ONE_BIT_DELAY_SYSCLK_CNT	=> 26	//=36(-10)
				#endif			
			#endif
		#else	
			#ifdef	Uart_Work_SYSCLK
				#if	(Uart_Work_SYSCLK == '1M')
				
				#elif	(Uart_Work_SYSCLK == '2M')
					HALF_BIT_DELAY_SYSCLK_CNT	=> 8	//=18(-10) 半位延时计数值,单位:系统时钟										
					ONE_BIT_DELAY_SYSCLK_CNT	=> 26	//=36(-10)
				#elif	(Uart_Work_SYSCLK == '4M')
					HALF_BIT_DELAY_SYSCLK_CNT	=> 26	//=36(-10) 半位延时计数值,单位:系统时钟										
					ONE_BIT_DELAY_SYSCLK_CNT	=> 61	//=71(-10)
				#elif	(Uart_Work_SYSCLK == '8M')
					HALF_BIT_DELAY_SYSCLK_CNT	=> 61	//=71(-10) 半位延时计数值,单位:系统时钟										
					ONE_BIT_DELAY_SYSCLK_CNT	=> 132	//=142(-10)
				#else	
					HALF_BIT_DELAY_SYSCLK_CNT	=> 8	//=18(-10) 半位延时计数值,单位:系统时钟										
					ONE_BIT_DELAY_SYSCLK_CNT	=> 26	//=36(-10)
				#endif
			#else			
				HALF_BIT_DELAY_SYSCLK_CNT	=> 8	//=18(-10) 半位延时计数值,单位:系统时钟										
				ONE_BIT_DELAY_SYSCLK_CNT	=> 26	//=36(-10)
			#endif
		#endif