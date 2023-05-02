
void InitMPU9250()
{
	CS_SET();//установка соединеия по SPI
 	SPI_Transmit(106);
	SPI_Transmit(0b00010000);
	CS_RESET();
	
// 	CS_SET();
// 	SPI_Transmit(29);
// 	SPI_Transmit(6);
// 	CS_RESET();
// 	CS_SET();
// 	SPI_Transmit(26);
// 	SPI_Transmit(6);
// 	CS_RESET();
	CS_SET();//установка разрешения гироскопа 250
	SPI_Transmit(27);
	SPI_Transmit(0b00000000);
	CS_RESET();
	
	CS_SET();//установка разрешения акс 2g
	SPI_Transmit(28);
	SPI_Transmit(0b00000000);
	CS_RESET();
	
// 	CS_SET();//настройка прерываний
// 	SPI_Transmit(0x37);
// 	SPI_Transmit(0x02);
// 	CS_RESET();
// 	CS_SET();//что-то от компаса
// 	SPI_Transmit(0x0A);
// 	SPI_Transmit(0x16);
// 	CS_RESET();
}

/*Reset and Enable FIFO & DMP:
1. Write {0x40} to USER_CTRL (0x6A)
2. Write {0x04} to USER_CTRL (0x6A)
3. Write {0x80} to USER_CTRL (0x6A)
4. Write {0x08} to USER_CTRL (0x6A)*/
	
void ResetDMP_FIFO()
{
	SpiWrite(0x6A,0x40);
	SpiWrite(0x6A,0x04);
	SpiWrite(0x6A,0x80);
	SpiWrite(0x6A,0x08);
}

//чтение данных напрямую с ацп 
void DataUp(IMU *MPU)
{
	CS_SET();
	SPI_Transmit(59|0b10000000);
	MPU->A_Xout=(SPI_Transmit(60|0b10000000))<<8;
	MPU->A_Xout=SPI_Transmit(61|0b10000000)+MPU->A_Xout;
	MPU->A_Yout=(SPI_Transmit(62|0b10000000))<<8;
	MPU->A_Yout=(SPI_Transmit(63|0b10000000))+MPU->A_Yout;
	MPU->A_Zout=(SPI_Transmit(64|0b10000000))<<8;
	MPU->A_Zout=(SPI_Transmit(65|0b10000000))+MPU->A_Zout;
	CS_RESET();
	
	MPU->G_Xout=SpiRead(67)<<8;
	MPU->G_Xout=SpiRead(68)+MPU->G_Xout;
	MPU->G_Yout=SpiRead(69)<<8;
	MPU->G_Yout=SpiRead(70)+MPU->G_Yout;
	MPU->G_Zout=SpiRead(71)<<8;
	MPU->G_Zout=SpiRead(72)+MPU->G_Zout;
	/*MPU->A_Xout=SpiReadInt(59);
	MPU->A_Yout=SpiReadInt(61);
	MPU->A_Zout=SpiReadInt(63);
	
	MPU->G_Xout=SpiReadInt(67);
	MPU->G_Yout=SpiReadInt(69);
	MPU->G_Zout=SpiReadInt(71);*/
	
// 	CS_SET();
// 	SPI_Transmit(59|0b10000000);
// 	MPU->A_Xout=SPI_Transmit(59|0b10000000);
}

//отправка значений с гироскопа по UART в ASCII
void GyroOut(IMU *MPU)
{
	USART_Transmit('$',0);
	
	USART_Transmit((MPU->G_Xout/10000)|0x30,0);
	USART_Transmit((MPU->G_Xout%10000/1000)|0x30,0);
	USART_Transmit((MPU->G_Xout%1000/100)|0x30,0);
	USART_Transmit((MPU->G_Xout%100/10)|0x30,0);
	USART_Transmit((MPU->G_Xout%10)|0x30,0);
	
	USART_Transmit(' ',0);
	
	USART_Transmit((MPU->G_Yout/10000)|0x30,0);
	USART_Transmit((MPU->G_Yout%10000/1000)|0x30,0);
	USART_Transmit((MPU->G_Yout%1000/100)|0x30,0);
	USART_Transmit((MPU->G_Yout%100/10)|0x30,0);
	USART_Transmit((MPU->G_Yout%10)|0x30,0);
	
	USART_Transmit(' ',0);
	
	USART_Transmit((MPU->G_Zout/10000)|0x30,0);
	USART_Transmit((MPU->G_Zout%10000/1000)|0x30,0);
	USART_Transmit((MPU->G_Zout%1000/100)|0x30,0);
	USART_Transmit((MPU->G_Zout%100/10)|0x30,0);
	USART_Transmit((MPU->G_Zout%10)|0x30,0);
	
	USART_Transmit(';',0);
	
	USART_Transmit(13,0);
}

//отправка значений с акселерометра по UART  в ASCII
void AccelOut(IMU *MPU)
{
	USART_Transmit('$',0);
	USART_Transmit((MPU->A_Xout/10000)|0x30,0);
	USART_Transmit((MPU->A_Xout%10000/1000)|0x30,0);
	USART_Transmit((MPU->A_Xout%1000/100)|0x30,0);
	USART_Transmit((MPU->A_Xout%100/10)|0x30,0);
	USART_Transmit((MPU->A_Xout%10)|0x30,0);
	
	USART_Transmit(' ',0);
	
	USART_Transmit((MPU->A_Yout%100000/10000)|0x30,0);
	USART_Transmit((MPU->A_Yout%10000/1000)|0x30,0);
	USART_Transmit((MPU->A_Yout%1000/100)|0x30,0);
	USART_Transmit((MPU->A_Yout%100/10)|0x30,0);
	USART_Transmit((MPU->A_Yout%10)|0x30,0);
	
	USART_Transmit(' ',0);	
	
	USART_Transmit((MPU->A_Zout/10000)|0x30,0);
	USART_Transmit((MPU->A_Zout%10000/1000)|0x30,0);
	USART_Transmit((MPU->A_Zout%1000/100)|0x30,0);
	USART_Transmit((MPU->A_Zout%100/10)|0x30,0);
	USART_Transmit((MPU->A_Zout%10)|0x30,0);
	USART_Transmit(';',0);
	
	USART_Transmit(13,0);
}