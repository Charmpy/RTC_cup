/*
 * servo_2560.c
 *
 * Created: 15.03.2023 15:36:55
 *  Author: HP
 */ 

#include <avr/io.h>
#include "main.h"
#include "servo.h"
#include "uart.h"


#include "UART_2560.c"
#include "SERVO.c"

#include "SPI_C.c"
#include "MPU9250.c"
#include <avr/interrupt.h>

volatile unsigned char count=0;
volatile unsigned int i,j;
volatile unsigned int SERVO_TIMING [8]={0};
	volatile unsigned char count;
int main(void)
{
/*
 	DDRB=0xFF;
 	PORTB=0x00;
	//DDRE=0xFF;
	
	
	
	init_servo(&S1,100,2);
	
//	PORTE=0;
	//инициализация UART0
	USART_Init(UART_SERVO,57600);
	USART_Init(0,57600);
	UART_INIT_BUF(&UART0);
	UART_INIT_BUF(&UART3);
	
	UART_INIT_BUF(&UART1);
	/ *
	USART_Transmit(0xFF,0);
	USART_Transmit(0xFF,0);
  USART_Transmit(ID,0);
  USART_Transmit(0x4,0);
  USART_Transmit(0x3,0);
  USART_Transmit(0X19,0);
  USART_Transmit(0X01,0);
  int checksum = ~((ID + 4 + 3 + 0x19 + (0x01&0xff)) % 256);
  USART_Transmit(checksum,0);* /
	//join_mode(ID_1,4095);
	//Mx_write(254,3,1,ID_1,2);
//  	Mx_write(254,8,2,4095,2);
//  	Mx_write(254,6,2,0,2);
// 	volatile unsigned int i=0;
// 	while (i<3000){i++;}
// 	Mx_write(ID_1,LED_ADDR,1,0,UART_SERVO);
 	//Mx_write(ID_1,Moving_Speed,2,1000,UART_SERVO);
	// set_position(ID_1,1000);
 	//delay();
	 
// 	DDRE=0;
// 	PORTE=0;
// 	Mx_write(ID_1,32,2,3090,2);
// 	delay();
	
/ *
	//init timer0 for update value of uart
	TCCR0B=(1<<CS02)|(1<<CS00);
	TIMSK0=(1<<TOIE0);
	* /
		
/ *
	//инициализация таймера Timer1 Phase correct, Icr1- max, ocr1a-сравнение
	ICR1=TIME_PERIOD;
	OCR1A=OCRA_MIN;//OCRA_MIN;
	TCCR1A=(1<<WGM11);
	TCCR1B=(1<<WGM13)|(1<<WGM12)|(1<<CS11);
	TIMSK1=(1<<TOIE1)|(1<<OCIE1A);
	TCNT1=0;* /
	S1.angle_free=90;
	S1.midle_pos=2048;*/
    USART_Init(0,57600);
	UART_INIT_BUF(&UART0);
	sei();
	USART_Transmit(0x11,0);
 	spi_init();
	InitMPU9250();
//  	
// 	CS_SET();
//  	USART_Transmit(SPI_Transmit(0x75|0b10000000),0);
// 	//CS_RESET();
// 	//CS_SET();
// // 	//SPI_Transmit(1);
// // 	SPI_Transmit(0x3B);
//  	USART_Transmit(SPI_Transmit(0x75|0b10000000),0);
// 	CS_RESET();
	USART_Transmit(SpiRead(0x3B),0);
	
	//set_position(ID_1,0000);
	/*delay();
	MX_READ(ID_1,Present_Position,2,UART_SERVO);
	delay();
	
	MX_READ(ID_1,Present_Position,2,UART_SERVO);
	delay();*/
	
// 	for (char i=0;i<256;i++)
// 			{
// 				USART_Transmit(SPI_Transmit(i),0);
// 				delay();
// 			}
// 	
    while(1)
		{
			USART_Transmit(SpiRead(0x3B),0);
			delay();


/*
			i=0;
			while (i<0xFFF)
			{
				j=0;
				while(j<0x2)
				{
					j++;
				}
				i++;
			}
			MX_READ(ID_1,Present_Position,2,UART_SERVO);
			delay();
			
			if ((signed int)(S1.midle_pos-S1.angle_free*6)>0)
			{
				if ((S1.present_pos>(S1.midle_pos+S1.angle_free*6))&(S1.present_pos<=4096))
				 {
						 set_position(ID_1,S1.midle_pos+S1.angle_free*6-5);
				 }
				else
				{
					if ((S1.present_pos<(S1.midle_pos-S1.angle_free*6))&(S1.present_pos<=4096))
					{
						set_position(ID_1,S1.midle_pos-S1.angle_free*6+5);
					}
					else
					{
						torque(ID_1,0);
					}
				}	
			}
			else
			{
				if ((S1.present_pos>(S1.midle_pos+S1.angle_free))&(S1.present_pos<(4096+S1.midle_pos-S1.angle_free))&(S1.present_pos<=4096))
				{
					set_position(ID_1,S1.midle_pos+S1.angle_free*6-5);
				}
				else
				{
					if ((S1.present_pos>(4096+S1.midle_pos-S1.angle_free))&(S1.present_pos<=4096))
					{
						set_position(ID_1,4096+S1.midle_pos-S1.angle_free*6+5);
					}
					else
					{
						torque(ID_1,0);
					}
				}
			}
				
 			*/
		}

	}

#include "Interrupts.c"