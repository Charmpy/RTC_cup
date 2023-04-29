volatile unsigned int DEGREE_TO_TAIM(unsigned char deg)
{
	return(1050+200*deg/9);
}

void delay()
{
	volatile unsigned int i=0;
	while (i<6000){i++;}
}

#define ID_1 200
#define ID_2 100

void set_position(volatile unsigned char ID, volatile unsigned int position)//range 0-4095
{
//	join_mode(ID,4095);
//	delay();
	Mx_write(ID,30,2,position,UART_SERVO);
//	delay();
}
void speed_run(volatile unsigned char ID, volatile unsigned int speed)
{
	wheel_mode(ID);
	delay();
	Mx_write(ID,32,2,speed,UART_SERVO);
	delay();
}

void led(volatile unsigned char ID, volatile unsigned char on)
{
	Mx_write(ID,0x19,1,on,UART_SERVO);
}

void torque(volatile unsigned char ID, volatile unsigned char on)
{
	Mx_write(ID,24,1,on,UART_SERVO);
}
void Mx_write(volatile unsigned char ID, volatile unsigned char reg, volatile unsigned char size, volatile unsigned int data, volatile unsigned char n_uart)
{
	UCSR3B&=~(1<<RXEN3);
	UCSR3B|=(1<<TXEN3);
	USART_Transmit(0xFF,n_uart);
	USART_Transmit(0xFF,n_uart);
	USART_Transmit(ID,n_uart);
	USART_Transmit(size+3,n_uart);
	USART_Transmit(0x3,n_uart);
	USART_Transmit(reg,n_uart);
	USART_Transmit(data&0xFF,n_uart);
	int checksum;
	if (size>1)
	{
		USART_Transmit((data&0xFF00)>>8,n_uart);
		checksum = ~((ID + 5 + 3 + reg + (data&0xFF) + ((data&0xFF00)>>8)) % 256);
	}
	else
	{
		checksum = ~((ID + 4 + 0x3 + reg + (data&0xff)) % 256);
	}	
	USART_Transmit(checksum,n_uart);
	
	//UCSR3B|=(1<<RXCIE3);
}

void MX_READ(volatile unsigned char ID, volatile unsigned char reg_st, volatile unsigned char size, volatile unsigned char n_uart)
{
	//USART_Transmit(0x54,0);
	UCSR1B&=~(1<<RXEN1);
	UCSR1B|=(1<<TXEN1);
	S1.NUMBER_BUF_SERVO=6+size;	
	USART_Transmit(0xFF,n_uart);
	USART_Transmit(0xFF,n_uart);
	USART_Transmit(ID,n_uart);
	USART_Transmit(4,n_uart);
	USART_Transmit(2,n_uart);
	USART_Transmit(reg_st,n_uart);
	USART_Transmit(size,n_uart);
	int checksum;
	checksum = ~(ID + 4 + 2 + reg_st + size);
	USART_Transmit(checksum,n_uart);
	//USART_Transmit(checksum,n_uart);
	//USART_Transmit(0xFF,n_uart);
	
// 	USART_Transmit(0xFF,n_uart);
// 	USART_Transmit(0xFF,n_uart);
// 	USART_Transmit(ID,n_uart);
// 	USART_Transmit(3,n_uart);
/* while ((UCSR3B&(1<<TXC3))!=0){}*/
	
	while ((!( UCSR1A &(1<<TXC1)))|(UCSR1B&(1<<UDRIE1))){};
	UCSR1B&=~(1<<TXEN1);
	//PORTJ|=(1<<PJ1)|(1<<PG0);
 	UCSR1B|=(1<<RXEN1);
	/*USART_Receive(UART_SERVO);
	USART_Receive(UART_SERVO);
	for (char a=0;a<((S1.NUMBER_BUF_SERVO));a++)
	{
		UART3.buf_in[a]=USART_Receive(UART_SERVO);
	}		
	UCSR3B&=~(1<<RXEN3);
	UCSR3B|=(1<<TXEN3);
	UART3.flag=1;*/
}

void wheel_mode(volatile unsigned char ID)
{
	Mx_write(ID,8,2,0,UART_SERVO);
	delay();
	Mx_write(ID,6,2,0,UART_SERVO);
}

void join_mode(volatile unsigned char ID, volatile unsigned int range)
{
	Mx_write(ID,8,2,4095,UART_SERVO);
	//delay();
	Mx_write(ID,6,2,0,UART_SERVO);
}

void init_servo(servo_type *servo, char ID_S, char uart_number_s)
{
	servo->uart_number=uart_number_s;
	servo->ID_TYPE=ID_S;
	servo->led_en=1;
	servo->CW=0;
	servo->CWW=0;
	servo->speed=1023;
	update_servo(&servo);
}

void update_servo(servo_type *servo)
{
	//Mx_write(servo->ID,LED_ADDR,2,servo->led_en,servo->uart_number);
}
