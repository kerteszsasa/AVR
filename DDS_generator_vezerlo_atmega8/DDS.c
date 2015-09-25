#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "usart.h"
#include "adc.h"
#include "console.h"
#include "commands.h"

/////////////////////////////////


volatile int timerdivider=0;
char sweeptype=0;
char measure_running=0;
int sweepcounter=0;
volatile int runningtime=1;

volatile char start=0;


//***********************
void InitTimer(void){
	
	TCCR0= 1<<CS02  | 1<<CS00;  // timer enable 1024 prescaler
	TIMSK = 1<<TOIE0 ; //tim0 int enable
}

//**************************************
ISR(TIMER0_OVF_vect){

	if(timerdivider>30*runningtime){

		measure_running=0; // leállítjuk a mérést
		timerdivider=0;
	}
	timerdivider++;


}

//*******************
void InitEXTINT(void)
{
	MCUCR=1<<ISC11|1<<ISC01;
	GICR=0<<INT1|1<<INT0; //INT1 disabled //INT0 enabled
}



//**********************
ISR (INT0_vect){
	start=1;	//Start button
	
}


//************************
//ISR (INT1_vect){
//	_delay_ms(100);
//}







//***********main****************************
int main( void )
{

	USART_Init ( MYUBRR );
	Konfig10bitADC();
	InitEXTINT();
	//InitTimer();
	sei();


	PORTB=0b00000011; 
	DDRB=0b00000111;
	PORTD=0b11111100;
	DDRD=0b11111000;
	DDRC=0b00000001;

	InitMessage();
	//DDS_reset();








	while(1)
	{


		 if(start){

		 	// Futási idõ beállítása
			runningtime=60*( Beolvas10bitADC(4)/100 +1 );
			putnum(runningtime/60);
			putstring(" Perc ");


			TCNT0=0; //timer nullázása
			InitTimer(); //timer indítása
			measure_running=1;


			
			
			// Beállított frekvencia beolvasása
			sweeptype=Beolvas10bitADC(5) /256;



			RIGHT_btn();
			RIGHT_btn();
			RIGHT_btn();
			RIGHT_btn();
			RIGHT_btn();
			RIGHT_btn();
			RIGHT_btn();
			RIGHT_btn();
			LED_ON();





			if(sweeptype==0){
				putstring("50Hz sweep 1Hz lépéssel ");
				LEFT_btn();
				}

			if(sweeptype==1){
				putstring("250Hz sweep 1Hz lépéssel ");
				LEFT_btn();
				}

			if(sweeptype==2){
				putstring("1kHz sweep 10Hz lépéssel ");
				LEFT_btn();
				LEFT_btn();
				}

			if(sweeptype==3){
				putstring("5kHz sweep 10Hz lépéssel ");
				LEFT_btn();
				LEFT_btn();
				}

			
			while(measure_running){

				if(sweeptype==0){
					for(sweepcounter=0;sweepcounter<50;sweepcounter++){
						EncoderUp();
						_delay_ms(10);
						}
					for(sweepcounter=0;sweepcounter<100;sweepcounter++){
						EncoderDown();
						_delay_ms(10);
						}
					for(sweepcounter=0;sweepcounter<50;sweepcounter++){
						EncoderUp();
						_delay_ms(10);
						}
					}

				if(sweeptype==1){
					for(sweepcounter=0;sweepcounter<250;sweepcounter++){
						EncoderUp();
						_delay_ms(10);
						}
					for(sweepcounter=0;sweepcounter<500;sweepcounter++){
						EncoderDown();
						_delay_ms(10);
						}
					for(sweepcounter=0;sweepcounter<250;sweepcounter++){
						EncoderUp();
						_delay_ms(10);
						}
					}

				if(sweeptype==2){
					for(sweepcounter=0;sweepcounter<100;sweepcounter++){
						EncoderUp();
						_delay_ms(10);
						}
					for(sweepcounter=0;sweepcounter<200;sweepcounter++){
						EncoderDown();
						_delay_ms(10);
						}
					for(sweepcounter=0;sweepcounter<100;sweepcounter++){
						EncoderUp();
						_delay_ms(10);
						}
					}

				if(sweeptype==3){
					for(sweepcounter=0;sweepcounter<500;sweepcounter++){
						EncoderUp();
						_delay_ms(10);
						}
					for(sweepcounter=0;sweepcounter<1000;sweepcounter++){
						EncoderDown();
						_delay_ms(10);
						}
					for(sweepcounter=0;sweepcounter<500;sweepcounter++){
						EncoderUp();
						_delay_ms(10);
						}
					}
			
				
			}

			

			LED_OFF();
			start=0;
			BEEP();
		 }





		


	}
return 0;
}
