
//set your clock speed
#define F_CPU 4800000UL
//these are the include files. They are outside the project folder
#include <avr/io.h>
#include <util/delay.h>
//this include is in your 


void set_servo(char position){

if( position > 10) position = 10;

PORTB |=(1<<4);		//on
_delay_ms(1);
int i=0;
for(i=0;i<position;i++)
_delay_us(100);

PORTB &= ~(1 << 4);		//off
_delay_ms(18);
//_delay_us(900);

}






int main (void)
{
	//Set PORTC to all outputs
	DDRB = 0xFF;
	//create an infinite loop
	while(1) {
		int j=0;

		for(j=0;j<15*50;j++){
			set_servo(9);
		}

		for(j=0;j<50;j++){
			set_servo(10);
		}
	}
	return 1;
}
