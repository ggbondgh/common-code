//======================================
#ifndef	extern_h
#define	extern_h

#if	defined(ADCC)
	#if defined(ADCR)
		ADCRH	EQU		ADCR
		ADCRL	EQU		0
	#else
		ADCR	EQU		ADCRH
	#endif
#endif

//
T_Watch_Set:
	Const_EN_Uart		=>1	//Uart使能
									
								//default:1
	UART_BaudRate		=>	38400	//UART波特率:7200 9600, 19200, 38400, 56000								
	Uart_Work_SYSCLK	=>	'2M'	
	Interrupt_Uart		=> 1		//UART中断及传输端口选择
									//0:PA0中断  1:PA5中断	2:PB0中断	default:0
									//注意:仿真时不支持PA5和PB0中断
									//实际IC烧录建议使用PA5

		//根据波特率设置,定义半位和一位串口数据位的延时值,单位:系统时钟
		#ifdef	UART_BaudRate
			#if		(UART_BaudRate == 7200)
					#ifdef	Uart_Work_SYSCLK
					#if	(Uart_Work_SYSCLK == '250K')
						HALF_BIT_DELAY_SYSCLK_CNT	=> 8	//=52(-10) 半位延时计数值,单位:系统时钟										
						ONE_BIT_DELAY_SYSCLK_CNT	=> 25	//=104(-10)
					#endif
					#endif

			#elif		(UART_BaudRate == 9600)
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


void	Uart_Send_One_Byte(void);


#endif

//End Of File