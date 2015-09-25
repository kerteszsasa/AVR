#define FOSC 7372800// Clock Speed
#define BAUD 4800
#define MYUBRR FOSC/16/BAUD-1

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "fuggvenyek.h"
#include "lcd.h"

/////////////////////////////////

float temp100;
char szamlal;
long int beolvas(void);
volatile unsigned char sec;
unsigned char min;
unsigned char hour;


//***********************




//*******************
void InitINT(void)
{
	MCUCR=1<<ISC11|1<<ISC01;
	GICR=1<<INT1|1<<INT0;
}



//**********************
ISR (INT0_vect)
{
	hour++;
	_delay_ms(100);
}


//************************
ISR (INT1_vect)
{
	min++;
	_delay_ms(100);
}







//***********main****************************
void main( void )
{

USART_Init ( MYUBRR );
Konfig10bitADC();
sei();
InitLCD(LS_BLINK|LS_ULINE);
LCDClear();
InitTIMER();
InitINT();

min=0;
hour=0;



	while(1)
	{
	
		//_delay_ms(100);
		//	LCDWriteIntXY(0,0,temp100,4);
		LCDWriteIntXY(0,0,hour,2);
		LCDWriteStringXY(2,0,":");
		LCDWriteIntXY(3,0,min,2);
		LCDWriteStringXY(5,0,":");
		LCDWriteIntXY(6,0,sec,2);

		LCDWriteIntXY(10,0,temp100/100,3);
		LCDData(0b11011111);
		LCDWriteStringXY(14,0,"C");

		_delay_ms(100);
	
		if(sec==60){sec=0; min++;}
		if(min==60){min=0; hour++;}
		if(hour==24){hour=0;}


		


	}
}
