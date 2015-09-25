// Program written for ATmega8
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>




volatile char counter1 =0;
volatile char counter2 =0;



#define OUT_1_DIR				DDRC
#define OUT_1_PORT				PORTC
#define OUT_1_PIN				0
#define OUT_1_delay_sec 		60

#define OUT_2_DIR				DDRD
#define OUT_2_PORT				PORTD
#define OUT_2_PIN				4
#define OUT_2_delay_sec 		1


void initTimr2(){
	ASSR =0x08; // ASSR enables clocking From 32kCrystal

	TCNT2 =0x00; //zero the timer register

	TCCR2 = (1<<CS22 ) | (0<<CS21) | (1<<CS20 ); //1028 prescaler

	TIMSK = 1<<TOIE2; //timer overflow interrupt enable
}


/********************************/
void portinit(){
	OUT_1_DIR |=(1<<OUT_1_PIN);
	OUT_2_DIR |=(1<<OUT_2_PIN);
}


//**********************
ISR (TIMER2_OVF_vect ){
	counter1++;
	counter2++;

	if (counter1 == OUT_1_delay_sec){
		OUT_1_PORT^=(1<<OUT_1_PIN);
		//_delay_ms(100);
		counter1 =0;
	}

	if (counter2 == OUT_2_delay_sec){
		OUT_2_PORT^=(1<<OUT_2_PIN);
		//_delay_ms(100);
		counter2 =0;
	}
}





int main(){
 portinit();
 //DDRB=0b00000010; // The DDRXn bit must be ‘1’
 //PORTB=0b00000010;
 
 
 //initTimr2();
 //sei();
 while(1){
DDRB=2;
PORTB=0;
_delay_us(27);
PORTB=2;
_delay_us(27);

 }

 return 0;
}
