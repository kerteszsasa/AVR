// 1 channel servo receiver, it converts PPM signal to PWM output
#include<avr/io.h>
#include<util/delay.h>
#include <avr/interrupt.h>

#define LED_ON PORTB |= (1<< PB4)
#define LED_OFF PORTB &= ~(1<< PB4)

volatile int servo =0;
volatile int watchdog=0;

ISR (INT0_vect)               // Interrupt on PCINT0 vector
{

		_delay_ms(1);
		servo=0;
		while( PINB & (1<< PB1)) {
		//LED_ON;
		servo++;
		_delay_us(2);


	

		}

		//servo-=125;
	//	servo*=1;

/*
		if(servo < 125) servo = 0;
		if (servo ) servo -= 124; 
		OCR0A= 10*servo;

		*/

		if(servo<255) PWM(servo);
		else PWM(255);

		watchdog=100;


}


void PWM (char i){
	OCR0A= i;
}
 


int main(void)
{
DDRB |= (1<< PB4);	// set PB4 as output for LED
DDRB |= (1 << PB0); //PB0 is output

LED_ON;
_delay_ms(1000);
_delay_ms(1000);
LED_OFF;


//Set the PWM timer
TCCR0A |=((1 << COM0A1  )  | (1 << WGM01) | (1 << WGM00) );
TCCR0B |= (1 << CS00);

//int servo = 0;
char setpwm =0;


//enable INT0 ext interrupt
MCUCR = (1<< ISC01 )| (1<< ISC00 );
GIMSK = (1<< INT0 );
PCMSK = (1<< PCINT1);


sei();
OCR0A= 0;	//PWM default value



while(1){
	_delay_ms(1);
	if(watchdog>0)watchdog--;

	if(watchdog==0){
		LED_ON;
		OCR0A= 0;
		_delay_ms(100);
		}

	else LED_OFF;;
	}


return(0);
}
