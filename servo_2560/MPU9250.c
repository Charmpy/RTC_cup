void InitMPU9250()
{
	CS_SET();
 	SPI_Transmit(106);
	SPI_Transmit(0b00010000);
	CS_RESET();
	CS_SET();
	SPI_Transmit(29);
	SPI_Transmit(6);
	CS_RESET();
	CS_SET();
	SPI_Transmit(26);
	SPI_Transmit(6);
	CS_RESET();
	CS_SET();
	SPI_Transmit(27);
	SPI_Transmit(0x18);
	CS_RESET();
	CS_SET();
	SPI_Transmit(28);
	SPI_Transmit(0x08);
	CS_RESET();
	CS_SET();
	SPI_Transmit(0x37);
	SPI_Transmit(0x02);
	CS_RESET();
	CS_SET();
	SPI_Transmit(0x0A);
	SPI_Transmit(0x16);
	CS_RESET();
}