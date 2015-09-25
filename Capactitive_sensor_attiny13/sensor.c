#include <avr/io.h>
#include <avr/interrupt.h>	
#include <util/delay.h>
#include <avr/sleep.h>
 
//PB3: btn
//PB4: LED

//*******************************
#define BLINK_TIMES 300  // 1 blink in every second




#define on PORTB=0b00010000
#define off PORTB=0

volatile char timer_int_divider=0;
volatile int blink_counter=0;



//*******************
ISR(TIM0_OVF_vect )
{
	timer_int_divider++;
	if(timer_int_divider==2 ){
		if(blink_counter>0){
			on;
			_delay_ms(1);
			blink_counter--;
		}
		timer_int_divider=0;
				
	}
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
		}
	return clk;
	}
/////////////////////////////////





int main(void)
{
	DDRB=0b00010000;


	TCCR0B =  (1<<CS02) |(1<<CS00); //clock prescaler
	TIMSK0 = 1<<TOIE0; //int enable

	sei(); //int enable

	set_sleep_mode(SLEEP_MODE_IDLE);
	sleep_mode(); 


	while(1){

		off;
		if(GetData() >22){


			if(blink_counter){ //switch off it is running
				blink_counter=0;
				_delay_ms(2000);
			}
			else{					//switch on
				on;
				_delay_ms(1000);
				blink_counter=BLINK_TIMES;
			}

		}
			

		sleep_mode(); 

	}
	return 0;
}
