#define CS PB5
#define MOSI PB2
#define MISO PB3
#define SCK PB1

#define SPI_PORT PORTB
#define SPI_DDR DDRB

// #define CS_SET SPI_PORT&=(1<<CS)
// #define CS_RESET SPI_PORT|=(1<<CS)

void spi_init()
{
	SPI_PORT=(1<<CS);
	SPI_DDR=(1<<PB0)|(1<<CS)|(1<<MOSI)|(1<<SCK);//|(0<<MISO);
	SPI_PORT|=(1<<CS)|(1<<MOSI)|(1<<SCK);//|(1<<MISO);
	SPCR=(1<<SPE)|(1<<MSTR)|(1<<SPR0);//|(0<<CPOL)|(1<<CPHA);
}

void CS_SET()
{
	SPI_PORT&=~(1<<CS);
}
void CS_RESET()
{
	SPI_PORT|=(1<<CS);
}

char SPI_Transmit(char cData)
{
	//SPI_PORT&=~(1<<CS);
/* Start transmission */
SPDR = cData;
//USART_Transmit(cData,0);
/* Wait for transmission complete */
while(!(SPSR&(1<<SPIF)))
{
	//USART_Transmit(0x99,0);
}
return SPDR;
}

char SPI_Receive(void)
{
/* Wait for reception complete */
while(!(SPSR & (1<<SPIF)));
/* Return Data Register */
return SPDR;
}

void SpiWrite(char Adr, char Data)
{
	CS_SET();
 	SPI_Transmit(Adr);
	SPI_Transmit(Data);
	CS_RESET();
}

char SpiRead(char Adr)
{
	CS_SET();
 	SPI_Transmit(Adr|0b10000000);
	char data;
	data=SPI_Transmit(Adr+1);
	CS_RESET();
	return(data);
}