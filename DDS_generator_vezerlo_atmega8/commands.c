#include "commands.h"



#define time _delay_us(100)
volatile char encoder_state=0;

void DDS_reset(void){
	
	RESET_btn();
	_delay_ms(2000);

	LEFT_btn();
	LEFT_btn();
	LEFT_btn();
	LEFT_btn();
	_delay_ms(100);
	EncoderDown();

}

void DDS_SetFreq(char *numbers){
	
	char i=0;
	putnum(666);

/*	
	putnum(numbers[0]);
	putnum(numbers[2]);
	putnum(numbers[4]);
	putnum(numbers[6]);
	putnum(numbers[8]);
	putnum(numbers[10]);
	putnum(numbers[12]);
	putnum(numbers[14]);

*/
	/*
	for(i=0;i<numbers[0];i++) putnum(1);

	for(i=0;i<numbers[2];i++) putnum(2);

	for(i=0;i<numbers[4];i++) putnum(3);

	for(i=0;i<numbers[6];i++) putnum(4);

	for(i=0;i<numbers[8];i++) putnum(5);
*/

}


void EncoderDown(void){

	PORTD|=(0b01000000);
	PORTD|=(0b10000000);
	time;
	PORTD&=~(0b01000000);
	PORTD|=(0b10000000);
	time;
	PORTD&=~(0b01000000);
	PORTD&=~(0b10000000);
	time;
	PORTD|=(0b01000000);
	PORTD&=~(0b10000000);
	time;
	PORTD|=(0b01000000);
	PORTD|=(0b10000000);
	time;

}

void EncoderUp(void){

	PORTD|=(0b01000000);
	PORTD|=(0b10000000);
	time;
	PORTD|=(0b01000000);
	PORTD&=~(0b10000000);
	time;
	PORTD&=~(0b01000000);
	PORTD&=~(0b10000000);
	time;
	PORTD&=~(0b01000000);
	PORTD|=(0b10000000);
	time;
	PORTD|=(0b01000000);
	PORTD|=(0b10000000);
	time;

}
