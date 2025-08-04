//I2C工作流程
//I2C总有两条线：SCL和SDA

void I2C_Init(void)
{
	SCL = 1;
	SDA = 1;
}

void I2C_Start(void)
{
	SDA = 1;
	SCL = 1;
	SDA = 0;
	SCL = 0;
}

void I2C_Stop(void)
{
	SDA = 0;
	SCL = 1;
	SDA = 1;
}

void I2C_SendByte(uint8_t SendByte)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		SDA = (SendByte & (0x80>>1));
		SendByte <<= 1;
		SCL = 1;
		SCL = 0;
	}
}

uint8_t I2C_ReceiveByte(void)
{
	uint8_t i, ReceiveByte = 0x00;
	SDA = 0; //交出SDA控制权
	for(i=0;i<8;i++)
	{
		SCL = 1;
		ReceiveByte <<= 1;
		if(SDA)
		{
			ReceiveByte |= 0x01;
		}
		SCL = 0;
	}
	return ReceiveByte;
}

void I2C_SendAck(uint8_t AckBit)
{
	SDA = AckBit;//直接写入应答位
	//时钟SCL产生一个脉冲（高电平），让从机读取应答
	SCL = 1;
	SCL = 0;
}

uint8_t I2C_ReceiveAck(void)
{
	uint8_t AckBit;
	SDA = 0;//交出SDA控制权
	SCL = 1;
	AckBit = SDA;
	SCL = 0;
	if(AckBit)
	{
		I2C_Stop();
	}
	return AckBit;
}

void I2C_Write(uint8_t DevAddress_w, uint8_t RegAddress, uint8_t SendData)
{
	//DevAddress_x末尾是读写位，0是写，1是读
	DevAddress_w = DevAddress << 1;

	I2C_Start();

	I2C_SendByte(DevAddress_w);
	I2C_ReceiveAck();
	I2C_SendByte(RegAddress);
	I2C_ReceiveAck();
	I2C_SendByte(SendData);
	I2C_ReceiveAck();		

	I2C_Stop();
}

uint8_t I2C_Read(uint8_t DevAddress, uint8_t RegAddress)
{
	//DevAddress_x末尾是读写位，0是写，1是读
	DevAddress_w = DevAddress << 1;
	DevAddress_r = DevAddress << 1 | 0x01;

	//指定位置
	I2C_Start();
	I2C_SendByte(DevAddress_w);
	I2C_ReceiveAck();
	I2C_SendByte(RegAddress);
	I2C_ReceiveAck();
	//读数据
	I2C_Start();
	I2C_SendByte(DevAddress_r);
	I2C_ReceiveAck();		
	I2C_ReceiveByte();//接收数据
	I2C_ReceiveAck();	
	I2C_Stop();
}

int main(void)
{
	uint8_t ReceiveData;
	I2C_Init();
	
	I2C_Write(DevAddress, RegAddress, SendData); //向指定地址写入数据
	ReceiveData = I2C_Read(DevAddress, RegAddress);//从指定地址读数据

	return 0;
}
