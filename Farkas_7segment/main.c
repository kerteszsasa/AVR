#include <avr/io.h>
#include <avr/interrupt.h>	
#include <util/delay.h>

#include "routines.h"
#include "uart.h"






//////////////////////////////////////////////////////   
void main(void)
{
DDRB=255;	// output for segments
DDRD=(1<<5)|(1<<6)|(1<<7);	//output for digits
USART_Init ( MYUBRR );
Konfig10bitADC();

while(1)
{
	Current(Beolvas10bitADC(5)/4);

	Voltage(Beolvas10bitADC(4)/4);

	putnum(Beolvas10bitADC(4)/4);
}

//Voltage(0);

//putnum(5);


}//main


