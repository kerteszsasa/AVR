#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "usart.h"
#include "adc.h"
#include "misep.h"

/////////////////////////////////

/*
volatile int timerdivider=0;
char sweeptype=0;
char measure_running=0;
int sweepcounter=0;
volatile int runningtime=1;

volatile char start=0;
*/

int* datavector[8];
volatile  int* msg[30];

//***********************
void InitTimer(void){
	
	TCCR0= 1<<CS02  | 1<<CS00;  // timer enable 1024 prescaler
	TIMSK = 1<<TOIE0 ; //tim0 int enable
}

//**************************************
ISR(TIMER0_OVF_vect){

}

//*******************
void InitEXTINT(void)
{
	MCUCR=1<<ISC11|1<<ISC01;
	GICR=0<<INT1|1<<INT0; //INT1 disabled //INT0 enabled
}



//**********************
ISR (INT0_vect){
	
}


//************************
//ISR (INT1_vect){
//	_delay_ms(100);
//}





//************************
int Measure_CAP(int ch){
	uint8_t channel =1<<ch;

	
	int clk = 0;
	DDRC=0;
	DDRC |= channel;	//out
	PORTC = channel;	//high
	_delay_ms(5); // cahrge the cap
	DDRC = 0; // input
	PORTC = 0; //tri state
	while((PINC & channel)&&(clk<1023)){
	//	_delay_us(1);//wait a bit
		clk++;
		}
	return clk;
}


//************************
int Measure_CAP_AD(int ch){
	uint8_t channel =1<<ch;

	Beolvas10bitADC(15);	//ad channel to gnd
	DDRC=0;
	DDRC |= channel;	//out
	PORTC = channel;	//high
	DDRC=0; //input pin
	PORTC=0; //nopullup
	return Beolvas10bitADC(ch);
}



//***********main****************************
int main( void )
{

	USART_Init ( MYUBRR );
	Konfig10bitADC();
//	InitEXTINT();
	//InitTimer();
	sei();




//	InitMessage();
	//DDS_reset();


while(1){


DDRD=0b00001000;
//PORTD=0b00001000;
PORTD=0;
	_delay_ms(100);

/*	datavector[0]=( Beolvas10bitADC(0));
	datavector[1]=( Beolvas10bitADC(1));
	datavector[2]=( Beolvas10bitADC(2));
	datavector[3]=( Beolvas10bitADC(3));
	datavector[4]=( Beolvas10bitADC(4));
	datavector[5]=( Beolvas10bitADC(5));
	datavector[6]=( Beolvas10bitADC(6));
	datavector[7]=( Beolvas10bitADC(7));

	*/



//	int cap =( Beolvas10bitADC(4));

int cap = 0;

//cap=( Beolvas10bitADC(15));
//cap = Measure_CAP_AD(0);

	cap = Measure_CAP(0);
	msg[0] = cap &255;
	msg[1] = (cap>>8) & 255;

	cap = Measure_CAP(1);
	msg[2] = cap &255;
	msg[3] = (cap>>8) & 255;

	cap = Measure_CAP(2);
	msg[4] = cap &255;
	msg[5] = (cap>>8) & 255;

	cap = Measure_CAP(3);
	msg[6] = cap &255;
	msg[7] = (cap>>8) & 255;

	cap = Measure_CAP(4);
	msg[8] = cap &255;
	msg[9] = (cap>>8) & 255;
	
	cap = Measure_CAP(5);
	msg[10] = cap &255;
	msg[11] = (cap>>8) & 255;


	Misep_Send( 0,  10,  567,  msg,  12);

	if (Misep_Is_Ready()){
		PORTD=0b00001000;
		_delay_ms(1000);
		Misep_Data_Processed();
	}

	
}



return 0;
}
