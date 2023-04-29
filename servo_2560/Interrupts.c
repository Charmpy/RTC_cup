/*
		ISR(TIMER1_OVF_vect)
	{
		USART_Transmit(0x45,1);
		PORTC=(1<<count);
	}
		ISR(TIMER1_COMPA_vect)
	{
		USART_Transmit(0x90,1);
		PORTC=0x00;
		OCR1A=SERVO_TIMING[count];

		count++;
		if (count>=6)
		{
			count=0;
		}
	}*/

ISR(TIMER0_OVF_vect)
{
	if (((UART0.flag)&1!=0))
	{
		if (UART0.buf_in[0]=='A')
		{
			set_position(ID_1,(UART0.buf_in[1]&0b11001111)*1000+(UART0.buf_in[2]&0b11001111)*100+(UART0.buf_in[2]&0b11001111)*10+(UART0.buf_in[4]&0b11001111));
		}
		else
		{
			set_position(ID_2,(UART0.buf_in[1]&0b11001111)*1000+(UART0.buf_in[2]&0b11001111)*100+(UART0.buf_in[2]&0b11001111)*10+(UART0.buf_in[4]&0b11001111));
		}
		//S1.midle_pos=(UART0.buf_in[0]&0b11001111)*1000+(UART0.buf_in[1]&0b11001111)*100+(UART0.buf_in[2]&0b11001111)*10+(UART0.buf_in[3]&0b11001111);
		/*USART_Transmit(0x45,0);
		USART_Transmit(0x02,0);
		USART_Transmit(0x74,0);*/
		UART0.flag=0;
	}
	
	
	
	if (((UART1.flag)!=0))
	{
// 		char data;
// 		for (char a=7;a<9;a++)//((S1.NUMBER_BUF_SERVO)+2)
// 		{
// 			data=UART1.buf_in[a];
// 			USART_Transmit(((data%1000)/100)+0x30,0);
// 		USART_Transmit(((data%100)/10)+0x30,0);
// 		USART_Transmit((data%10)+0x30,0);
// 		USART_Transmit(13,0);
// 		}
// 		USART_Transmit(13,0);
		volatile unsigned int data;
		data=(UART1.buf_in[8]<<8);
		data=data+UART1.buf_in[7];
		S1.present_pos=data;	
		USART_Transmit(((data%10000)/1000)+0x30,0);
		USART_Transmit(((data%1000)/100)+0x30,0);
		USART_Transmit(((data%100)/10)+0x30,0);
		USART_Transmit((data%10)+0x30,0);
		USART_Transmit(13,0);
		UART1.flag=0;
	}
}
ISR(USART0_RX_vect)	
{
	UART0.buf_in[UART0.count_in]=UDR0;
	UART0.count_in++;
	if (UART0.count_in>=NUMBER_BUF)
	{
		UART0.count_in=0;
		UART0.flag=1;
		
	}
	/*
	UCSR0B&=~(1<<RXCIE0);
	//set_position(ID_1,adr*11);
	volatile unsigned int data;
	volatile unsigned char adr;
	adr=UDR0;
	data=(adr&0b11001111)*1000+(USART_Receive(0)&0b11001111)*100+(USART_Receive(0)&0b11001111)*10+(USART_Receive(0)&0b11001111);
	set_position(ID_1,data);
	/*switch (adr)
	{
		case 'A':
			set_position(ID_1, data);
			led(ID_1,1);
			break;
		case 'B':
			set_position(ID_2, data);
			led(ID_2,1);
			break;
		case 'S':
			speed_run(ID_1,data);
			led(ID_1,0);
			break;
		case 'G':
			speed_run(ID_2,data);
			led(ID_2,0);
			break;
		case 'H':
			torque(ID_1,1);
			break;
		case 'F':
			torque(ID_1,0);
			break;
	}
	MX_READ(ID_1,Present_Voltage,1,UART_SERVO);
	UCSR0B|=(1<<RXCIE0);*/
}

ISR (USART0_UDRE_vect)
{

	UDR0=UART0.buf_out[UART0.count_out];
	UART0.count_out++;//=UART3.count_out-1;
	if ((UART0.count_out)>=(UART0.max_count_out))
	{
		UCSR0B&=~(1<<UDRIE0);
		UART0.max_count_out=0;
		UART0.count_out=0;
		
	}
}

ISR (USART1_UDRE_vect)
{

	UDR1=UART1.buf_out[UART1.count_out];
	UART1.count_out++;//=UART3.count_out-1;
	if ((UART1.count_out)>=(UART1.max_count_out))
	{
		UCSR1B&=~(1<<UDRIE1);
		UART1.max_count_out=0;
		UART1.count_out=0;
		
	}
}


ISR (USART3_UDRE_vect)
{
	UDR3=UART3.buf_out[UART3.count_out];
	UART3.count_out++;//=UART3.count_out-1;
	if ((UART3.count_out)>=(UART3.max_count_out))
	{
		UCSR3B&=~(1<<UDRIE3);
		UART3.max_count_out=0;
		UART3.count_out=0;
	}
}



ISR (USART3_RX_vect)
{
	//UCSR3A&=~(1<<RXC3);
	UART3.buf_in[UART3.count_in]=UDR3;
	UART3.count_in++;
	if (UART3.count_in>S1.NUMBER_BUF_SERVO+2)
	{
		UART3.count_in=0;
		UART3.flag=1;
		UCSR3B&=~(1<<RXEN3);
		UCSR3B|=(1<<TXEN3);
	}
/*USART_Transmit(UDR3,0);*/
	
}

ISR (USART1_RX_vect)
{
	UART1.buf_in[UART1.count_in]=UDR1;
	UART1.count_in++;
	if (UART1.count_in>S1.NUMBER_BUF_SERVO+2)
	{
		UART1.count_in=0;
		UART1.flag=1;
		UCSR1B&=~(1<<RXEN1);
		UCSR1B|=(1<<TXEN1);
	}
/*USART_Transmit(UDR1,0);*/
	
}