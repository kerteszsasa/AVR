   
#include <avr/io.h>
#include <avr/interrupt.h>	
#include <util/delay.h>
 
volatile uint8_t a=2;
   
void main(void)
{
DDRB=255;
DDRD=1<<0|1<<1;
PORTD=0;



PORTB=1;


//k�ls� megszak�t�s
MCUCR=1<<ISC01|1<<ISC11; //int1 megszak�t�st fogom haszn�lni, lefut� �lre reag�ljon
GICR=1<<INT0|1<<INT1;	// k�ls� megszak�t�sok enged�lyez�se 

sei();

while(1)
{


if(PORTB>=64)PORTB=1;
}


}




ISR (INT1_vect)
{

PORTB*=2;			//***	
if(PORTB>=64)PORTB=1;//***ezeknek kell lefutni


_delay_ms(100);
//GIFR=1<<INTF1;

}









ISR (INT0_vect)
{
	PORTB/=2;					//***	
	if(PORTB==64)PORTB=1;	//***ezeknek is
	if(PORTB==0)PORTB=32;

}


