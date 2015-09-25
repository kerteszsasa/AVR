#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>

char vector[18];



#define on PORTA=255
#define off PORTA=0


void PWM(void){
	char i=0;
	for(i=0;i<255;i++){
		
		if(vector[0] > i) PORTA |=(1<<0);
		else PORTA &=~(1<<0);

		if(vector[1] > i) PORTA |=(1<<1);
		else PORTA &=~(1<<1);

		if(vector[2] > i) PORTA |=(1<<2);
		else PORTA &=~(1<<2);

		if(vector[3] > i) PORTA |=(1<<3);
		else PORTA &=~(1<<3);

		if(vector[4] > i) PORTA |=(1<<4);
		else PORTA &=~(1<<4);

		if(vector[5] > i) PORTA |=(1<<5);
		else PORTA &=~(1<<5);

		if(vector[6] > i) PORTA |=(1<<6);
		else PORTA &=~(1<<6);

		if(vector[7] > i) PORTA |=(1<<7);
		else PORTA &=~(1<<7);

		if(vector[8] > i) PORTA |=(1<<0);
		else PORTA &=~(1<<0);

		if(vector[9] > i) PORTA |=(1<<0);
		else PORTA &=~(1<<0);

		if(vector[10] > i) PORTA |=(1<<0);
		else PORTA &=~(1<<0);

		if(vector[11] > i) PORTA |=(1<<0);
		else PORTA &=~(1<<0);

		if(vector[12] > i) PORTA |=(1<<0);
		else PORTA &=~(1<<0);

		if(vector[13] > i) PORTA |=(1<<0);
		else PORTA &=~(1<<0);

		if(vector[14] > i) PORTA |=(1<<0);
		else PORTA &=~(1<<0);

		if(vector[15] > i) PORTA |=(1<<0);
		else PORTA &=~(1<<0);

		if(vector[16] > i) PORTA |=(1<<0);
		else PORTA &=~(1<<0);

		if(vector[17] > i) PORTA |=(1<<0);
		else PORTA &=~(1<<0);



		}

}







int main(void){

	DDRA=255;

//	PORTA=255;

vector[0]=254  ;
vector[1]= 0 ;
vector[2]= 250 ;
vector[3]=  255;
vector[4]=  54;
vector[5]=  255;
vector[6]=  45;
vector[7]=  250;

while(1){
	PWM();
	vector[3];
	
	}


return 0;
}
