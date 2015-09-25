   
#include <avr/io.h>
#include <avr/interrupt.h>	
#include <util/delay.h>
#include <avr/sleep.h>
 
//PB3: btn
//PB4: LED

#define on PORTB=0b00010000
#define off PORTB=0


//*******************
ISR(TIM0_OVF_vect )
{
	//on;
	_delay_ms(10);
}

//////////////////////////////////
uint16_t GetData(){
	uint16_t clk =0;
	DDRB |= 8; //set output
	PORTB |= 8; //set high
	_delay_ms(20);
		DDRB &= ~8; //set input
	PORTB &= ~8; //set tri state
	while((PINB&8) ){
		clk++;
	//	_delay_us(1);
		}
	return clk;
	}
/////////////////////////////////




//&& (clk<65000)







int main(void)
{
char i=0;

TCCR0B =  (1<<CS02) |(1<<CS00); //clock prescaler
TIMSK0 = 1<<TOIE0; //int enable

//sei();

//set_sleep_mode(SLEEP_MODE_IDLE);
//sleep_mode(); 





DDRB=0b00010000;
while(1){
	
	if(GetData() >100)on;
	else off;
	//_delay_ms(1);
//	off;
//	_delay_ms(1);

	}	


while(0){

	DDRB=0b00010000;
	if(PINB & 0b00001000)
	PORTB=0b00010000;
	else PORTB=0;

	}



DDRB=0b00010000;


while(1)
	{
	DDRB=0b00011000;
	PORTB=0b00001000;
	for(i=0;i<255;i++);
	DDRB=0b00010000;
	PORTB=0b00000000;

	i=0;
	while(PINB & 0b00001000)
	{
	i++;
	
	}
	on;



	if(0)
	on;
	else off;
	for(i=0;i<255;i++);
	for(i=0;i<255;i++);
	for(i=0;i<255;i++);
	for(i=0;i<255;i++);

	}

return 0;
}
