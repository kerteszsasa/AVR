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
int  ADVALUE = 0;
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
			ADVALUE=Beolvas10bitADC(5);

			if(0   <= ADVALUE && ADVALUE <= 102) sweeptype = 1;
			if(102 <= ADVALUE && ADVALUE <= 307) sweeptype = 2;
			if(307 <= ADVALUE && ADVALUE <= 512) sweeptype = 3;
			if(512 <= ADVALUE && ADVALUE <= 716) sweeptype = 4;
			if(716 <= ADVALUE && ADVALUE <= 921) sweeptype = 5;
			if(921 <= ADVALUE && ADVALUE <=1024) sweeptype = 6;



			RIGHT_btn();
			RIGHT_btn();
			RIGHT_btn();
			RIGHT_btn();
			RIGHT_btn();
			RIGHT_btn();
			RIGHT_btn();
			RIGHT_btn();
			LED_ON();




			// Lépésköz beállítása, + kiírás
			if(sweeptype==1){
				putstring("50Hz sweep 1Hz lépéssel ");
				LEFT_btn();
				}

			if(sweeptype==2){
				putstring("100Hz sweep 1Hz lépéssel ");
				LEFT_btn();
				}

			if(sweeptype==3){
				putstring("250Hz sweep 1Hz lépéssel ");
				LEFT_btn();
				}

			if(sweeptype==4){
				putstring("500Hz sweep 10Hz lépéssel ");
				LEFT_btn();
				LEFT_btn();
				}

			if(sweeptype==5){
				putstring("1kHz sweep 10Hz lépéssel ");
				LEFT_btn();
				LEFT_btn();
				}

			if(sweeptype==6){
				putstring("2kHz sweep 10Hz lépéssel ");
				LEFT_btn();
				LEFT_btn();
				}

			
			while(measure_running){

				if(sweeptype==1){
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

				if(sweeptype==4){
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

				if(sweeptype==5){
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

				if(sweeptype==6){
					for(sweepcounter=0;sweepcounter<200;sweepcounter++){
						EncoderUp();
						_delay_ms(10);
						}
					for(sweepcounter=0;sweepcounter<400;sweepcounter++){
						EncoderDown();
						_delay_ms(10);
						}
					for(sweepcounter=0;sweepcounter<200;sweepcounter++){
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
