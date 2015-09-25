#include <avr/io.h>
#include <avr/interrupt.h>	
#include <util/delay.h>
//#include "i2csoft.h"
//#include "routines.h"
#include "uart.h"

int timer=0;
int getdatafromio5(void)
{

	int data = 0;
	DDRC|=32;
	PORTC|=32;
	//_delay_ms(1);
	_delay_us(900);
	DDRC&=!32;
	PORTC&=!32;
		PORTB=2;
	while(PINC&32)
	{
	//	_delay_us(1);
		data++;
	}
	PORTB=0;
	return data;
}

int getdatafromio4(void)
{
	int data = 0;
	DDRC=16;
	PORTC=16;
	_delay_ms(20);
	DDRC=0;
	PORTC=0;
	while(PINC&16)
	{
	//	_delay_us(1);
		data++;
	}
	return data;
}






int main(void)
{

DDRB=255;
DDRC=255;


	USART_Init ( MYUBRR );
	putstring("HELLO");
	USART_Transmit(  '\n' );
	USART_Transmit(  '\r' );



	while(1)
	{

	putnum(getdatafromio5());
	putstring("    ");
	//	_delay_ms(200);
//	putnum(getdatafromio4());
	USART_Transmit(  '\n' );
	USART_Transmit(  '\r' );
	_delay_ms(200);
	}



return 0;
}// end of main

