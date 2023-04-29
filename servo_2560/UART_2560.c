#define FOSC 16000000// Clock Speed
#define BAUD 57600
#define MYUBRR FOSC/16/BAUD-1

void USART_Init( volatile unsigned char number, volatile unsigned long int boad)
{
/* Set baud rate */
 unsigned int ubrr=FOSC/16/boad-1;
switch (number)
{
	case 0:
	
	UCSR0A = 0;
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (0<<USBS0)|(1<<UCSZ00)|(1<<UCSZ01);
	break;
	case 1:
	UBRR1H = (unsigned char)(ubrr>>8);
	UBRR1L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR1B = (0<<RXEN1)|(1<<TXEN1)|(1<<RXCIE1);
	/* Set frame format: 8data, 2stop bit */
	UCSR1C = (0<<USBS1)|(3<<UCSZ10);
	break;
	case 2:
	UBRR2H = (unsigned char)(ubrr>>8);
	UBRR2L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR2B = (1<<TXEN2);//(1<<RXEN2)|
	/* Set frame format: 8data, 2stop bit */
	UCSR2C = (1<<USBS2)|(3<<UCSZ20);
	break;
	case 3:
UCSR3A = 0;
	UBRR3H = (unsigned char)(ubrr>>8);
	UBRR3L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR3B = (0<<RXEN3)|(1<<TXEN3)|(1<<RXCIE3);
	/* Set frame format: 8data, 2stop bit */
	UCSR3C = (0<<USBS3)|(1<<UCSZ30)|(1<<UCSZ31);
	break;
	default: break;
}


}

void USART_Transmit(unsigned char data, volatile unsigned char number)
{
	switch (number)
{
	case 0:/*
	/ * Wait for empty transmit buffer * /
	while ( !( UCSR0A & (1<<UDRE0)) );
	/ * Put data into buffer, sends the data * /
	UDR0= data;*/
	
	// 	/* Wait for empty transmit buffer */
// 	while ( !( UCSR3A & (1<<UDRE3)) );
// 	/* Put data into buffer, sends the data */
// 	UDR3= data;
	UART0.buf_out[UART0.max_count_out]=data;
	UART0.max_count_out++;
	UCSR0B|=(1<<UDRIE0);
	break;
	
	break;
	case 1:
	/* Wait for empty transmit buffer 	while ( !( UCSR1A & (1<<UDRE1)) );
	 Put data into buffer, sends the data 	UDR1= data;
	break;*/
	UART1.buf_out[UART1.max_count_out]=data;
	UART1.max_count_out++;
	UCSR1B|=(1<<UDRIE1);
	break;
	case 2:
	/* Wait for empty transmit buffer */
	while ( !( UCSR2A & (1<<UDRE2)) );
	/* Put data into buffer, sends the data */
	UDR2= data;
	break;
	case 3:
// 	/* Wait for empty transmit buffer */
// 	while ( !( UCSR3A & (1<<UDRE3)) );
// 	/* Put data into buffer, sends the data */
// 	UDR3= data;
	UART3.buf_out[UART3.max_count_out]=data;
	UART3.max_count_out++;
	UCSR3B|=(1<<UDRIE3);
	break;
	default: break;
}
}

unsigned char USART_Receive(unsigned char number)
{
	
	switch (number)
{
	case 0:
	/* Wait for data to be received */
	while ( !( UCSR0A& (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
	break;
	case 1:
	/* Wait for data to be received */
	while ( !( UCSR1A& (1<<RXC1)) );
	/* Get and return received data from buffer */
	return UDR1;
	break;
	case 2:
	/* Wait for data to be received */
	while ( !( UCSR2A& (1<<RXC2)) );
	/* Get and return received data from buffer */
	return UDR2;
	break;
	case 3:
	/* Wait for data to be received */
	while ( !( UCSR3A& (1<<RXC3)) );
	/* Get and return received data from buffer */
	return UDR3;
	break;
	default: break;
}
	
	

}


void UART_INIT_BUF(uart_type *uart)
{
	uart->count_in=0;
	uart->count_out=0;
	uart->max_count_out=0;
}