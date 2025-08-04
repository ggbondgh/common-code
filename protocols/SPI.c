   //SPI实现过程
//SPI四根线：SCK MOSI MISO SS
//SCK时钟线，MOSI数据输出线，MISO数据输入线，SS片选线
//以下以CPOL=0 CPHA=0为例
void SPI_Init(void)
{
	//初始化SPI
	SCK = 0;
}

void SPI_Start(void)
{
	//开始SPI传输
	SS = 0;
}

void SPI_Stop(void)
{
	//结束SPI传输
	SS = 1;
}

uint8_t MySPI_SwapByte(uint8_t ByteSend)
{
	uint8_t i, ByteReceive = 0x00;
	SCK = 0;
	for(i=0;i<8;i++)
	{
		//第一个边沿采集(接收)数据，但是数据需要先移入再移出，所以在第一个边沿前需要先移出(发送)
		MOSI = (ByteSend & 0x80>>i);
		//上升沿接收数据
		SCK= 1;
		if(MISO)
		{
			ByteReceive |= (0x80>>i);
		}
		SCK = 0;
	}
	return ByteReceive;	
}

int main()
{
	while(1)
	{
		SPI_Init();
		SPI_Start();
		//SPI发送数据
		SPI_SwapByte(0x55);
		SPI_Stop();
	}
	return 0;
}

