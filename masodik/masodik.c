#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define Bon PORTC|=1<<4
#define Boff PORTC&=~1<<4

#define Gon PORTC|=1<<3
#define Goff PORTC&=~1<<3

#define Ron PORTC|=1<<5
#define Roff PORTC&=~1<<5


volatile uint8_t RED, GREEN, BLUE, szam=0, i=0;

int main() //Main fõprogram
{
//DDRD=0;	//DDR: data direction register itt állítom h ki=1 / be=0 menet legyenen  a láb
DDRC=1<<3|1<<4|1<<5;

MCUCR=1<<ISC01; //int0 enable
GICR=1<<INT0;	// minterrupt enable

///////////////////
TCCR0=1;
TIMSK=1;


RED=0;
GREEN=0;
BLUE=0;

sei();

while(1)	//a proramnak sosem szabad véet érnie
	{
//	PORTC=16;
	RED+=10;
	_delay_ms(1000);
	}
return 0;
}

ISR (INT0_vect) {


if(i==0){GREEN=150;BLUE=0;i=1;}

else if(i==1){GREEN=0;BLUE=105;i=2;}

else{GREEN=50;BLUE=50;i=0;}






}



ISR(TIMER0_OVF_vect){

	if(RED>szam){Ron;}else{Roff;}
	if(GREEN>szam){Gon;}else{Goff;}
	if(BLUE>szam){Bon;}else{Boff;}
	szam++;

}














