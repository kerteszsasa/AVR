#define FOSC 7372800// Clock Speed
#define BAUD 4800
#define MYUBRR FOSC/16/BAUD-1

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "fuggvenyek.h"
#include "lcd.h"
#include "fonts.h"

/////////////////////////////////
volatile char alma=0;
volatile char kirajzol=0;

float temp100;
char szamlal;
long int beolvas(void);
volatile unsigned char sec;
unsigned char min;
unsigned char hour;




#define FONT_DELAY 150

/*
void FONT(char X, char Y)
{						
	int i=0;				
	int j=X-32;				
	for (i=0; i<5; i++) {
		if (Y==1)
			disp1(font[j][i]);
		else
			disp0(font[j][i]);
		_delay_us(FONT_DELAY); 
	}			
	if (Y==1)			
		disp1(0);				
	else
		disp0(0);				
	_delay_us(FONT_DELAY);	
}

#define FONT_I(X)	FONT(X,0)
#define FONT_O(X)	FONT(X,1)

#define FONT_IO(X,Z)	\
		do {						\
			int i=0;				\
			int j=(X)-32;			\
			int k=(Z)-32;			\
			for (i=0; i<5; i++) {	\
				disp0(font[j][i]);	\
				disp1(font[k][i]);	\
				_delay_us(FONT_DELAY); \
			}						\
			disp0(0);				\
			disp1(0);				\			
			_delay_us(FONT_DELAY);	\
		} while(0)
*/
volatile int aaa=5;
//***********************
void putch(unsigned char x)
{
unsigned char i=0;
for(i=0;i<5;i++)
{
	disp1(font[x-32][i]);
	_delay_us(FONT_DELAY);
}
disp1(0);
_delay_us(FONT_DELAY);

}


//*******************
void InitINT(void)
{
	MCUCR=1<<ISC11|1<<ISC01;
	GICR=1<<INT1|1<<INT0;
}



//**********************SNC
ISR (INT0_vect)
{
	/*int j=6;
	char *c = "Kertesz Sandor";
	char *d = "* 2011 07 27 *";
	for(j=0; c[j]!='\0'; j++) {
		FONT_I(c[j]);
		FONT_O(d[j]);
	}	
	*/

putch('K');
putch('E');
putch('R');
putch('T');
putch('E');
putch('S');
putch('Z');
putch(' ');
putch('S');
putch('A');
putch('N');
putch('D');
putch('O');
putch('R');
putch(' ');
putch('!');

//disp1(128);
//_delay_ms(1);
disp1(00);

}

//************************
ISR (INT1_vect)
{
//	min++;
	//_delay_ms(100);
//	alma++;
//	kirajzol=alma;
	
}




//*********************************************
void RTCInit(void)
{
   ASSR=1<<AS2;	//ext cristal
   TCCR2= 1<<CS22|1<<CS20; //prescaler 128
   TIMSK=1<<TOIE2;
}



//*******************
ISR(TIMER2_OVF_vect )
{
	alma++;
}


//***********************
void disp0(unsigned char data)
{
	if(data & 1)	PORTD|=16;
	else			PORTD&=~16;
	if(data & 2)	PORTC|=32;
	else			PORTC&=~32;
	if(data & 4)	PORTC|=16;
	else			PORTC&=~16;
	if(data & 8)	PORTC|=8;
	else			PORTC&=~8;
	if(data & 16)	PORTC|=4;
	else			PORTC&=~4;
	if(data & 32)	PORTC|=2;
	else			PORTC&=~2;
	if(data & 64)	PORTC|=1;
	else			PORTC&=~1;
	if(data & 128)	PORTB|=32;
	else			PORTB&=~32;
}


//***********************
void disp1(unsigned char data)
{
	if(data & 1)	PORTB|=16;
	else			PORTB&=~16;
	if(data & 2)	PORTB|=8;
	else			PORTB&=~8;
	if(data & 4)	PORTB|=4;
	else			PORTB&=~4;
	if(data & 8)	PORTB|=2;
	else			PORTB&=~2;
	if(data & 16)	PORTB|=1;
	else			PORTB&=~1;
	if(data & 32)	PORTD|=128;
	else			PORTD&=~128;
	if(data & 64)	PORTD|=64;
	else			PORTD&=~64;
	if(data & 128)	PORTD|=32;
	else			PORTD&=~32;
}





//***********main****************************
void main( void )
{

	DDRC=0xFF;
	DDRB=0x3F;
	DDRD=0xF0;

	//USART_Init ( MYUBRR );
	//Konfig10bitADC();
	//InitTIMER();
	InitINT();
	RTCInit();






	sei();


	disp1(128);
		_delay_ms(500);
				_delay_ms(500);
						_delay_ms(500);
								_delay_ms(500);
	while(1);


	while(0)
	{
	/*
		//_delay_ms(100);
		//	LCDWriteIntXY(0,0,temp100,4);
		LCDWriteIntXY(0,0,aaa,2);
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
	*/
	}
}
