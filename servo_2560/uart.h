typedef struct uart_type
{
	volatile unsigned char buf_out[255];
	volatile unsigned char buf_in[255];
	volatile unsigned int max_count_out;
	volatile unsigned int count_in;
	volatile unsigned int count_out;	
	volatile unsigned char flag;
}uart_type;



uart_type UART3;
uart_type UART0;
uart_type UART1;