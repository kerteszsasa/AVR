#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define ron PORTC|=32
#define roff PORTC&=~32
#define bon PORTC|=16
#define boff PORTC&=~16
#define gon PORTC|=8
#define goff PORTC&=~8


volatile int i=1;
volatile uint8_t RED, GREEN, BLUE;
uint8_t szamlal;





int main() //Main fõprogram
{

//EXint0************************
//exint
MCUCR=1<<ISC01; //lefutó él
GICR=1<<INT0;	//int0 engedélyezése


//timer0*********************
 TCCR0= 1;//<<CS02 | 1<<CS00 ; //timer0 enable ,prescaler 1024
   TIMSK=1<<TOIE0;	//timer0 interrupt enable
  

sei ( );

DDRC=255;



GREEN=60;

while(1)	//a proramnak sosem szabad véget érnie
	{
_delay_ms(1000);
RED+=10;

	}
return 0;
}






ISR(TIMER0_OVF_vect)
{

	if(RED>szamlal)ron; else roff;
	if(GREEN>szamlal)gon; else goff;
	if(BLUE>szamlal)bon; else boff;
	szamlal++;



}





ISR (INT0_vect) {




if(i==1){GREEN=100;BLUE=0;i=0;}
else{GREEN=0;BLUE=100;i=1;}



}
