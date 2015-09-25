#include <avr/io.h>
#include <avr/interrupt.h>	
#include <util/delay.h>
#include "i2csoft.h"
#include "routines.h"
#include "uart.h"



char out_enable=0;			//gomb lenyomva, kimenet engedélyezve
char out_chan=0;			//kimenõ csatorna kiválasztása

volatile char* tomb[10];	//bejövõ buffer
volatile char index=0;		//buffer index
volatile char ready=0;		//megjött a lezáró karakter
char volt_1=0;
char volt_2=0;
char volt_3=0;
char voltage=0;
char channel=0;

 
void led(char c)
{
if(c) PORTD|=(1<<4);
else PORTD&=~(1<<4);
}

void ledch(char a)
{
	if(a==1) PORTD|=(1<<6);
	else PORTD&=~(1<<6);

	if(a==2) PORTD|=(1<<7);
	else PORTD&=~(1<<7);
}


char button() {
	return !(PINB&1);
}

char input_handler() {
	if(button() && out_enable==0) {
			putstring("<ON>");
			out_enable=1;
	}

	if( !button() && out_enable==1) {
		putstring("<OFF>");
		out_enable=0;
	}

	return out_enable;
}





//******uart_int**********************************************
ISR(USART_RXC_vect)
{

	char x;
	x=UART_Receive();

	if(x=='>') ready=1;
	if(x=='<') { index=0; return; }

	tomb[index]=x;
	index++;
}


//////////////////////////////////////////////////////   
void main(void)
{
DDRD|=(1<<4) | (1<<6) | (1<<7);

SoftI2CInit();	
USART_Init ( MYUBRR );
Konfig8bitADC();

sei();




//while(0){ putnum( Beolvas8bitADC(2)); USART_Transmit(  '\n' );
//USART_Transmit(  '\r' );  _delay_ms(1000); }

/////// i2c prog

 putnum(Setpot (20));



//while(1);putstring("Tattoo firmware: 0.1");


// innentõl jó
USART_Transmit(  '\n' );
USART_Transmit(  '\r' );
putstring("Tattoo firmware: 0.1");
USART_Transmit(  '\n' );
USART_Transmit(  '\r' );

while(1){

	if (ready==1) {
		
		if ( (tomb[3]=='C') && (tomb[4]=='H') )	{	
			channel = tomb[5] -48;

			volt_1=tomb[0] -48;
			volt_2=tomb[1] -48;
			volt_3=tomb[2] -48;
			voltage= 100*volt_1 + 10*volt_2 + volt_3;

			//putnum(voltage);putnum(channel); // itt állítom majd be a potit
			putnum(Setpot (voltage));
			putstring("<ACK>");
		}
		ready=0;
	}

	input_handler();

	if (out_enable==1) {
		ledch(channel);
		}
	if (out_enable==0) {
		ledch(0);
		}


	if(out_enable){ USART_Transmit(  '<' ); putnum( Beolvas8bitADC(2)); USART_Transmit(  '>' ); }
	_delay_ms(10);

	


}














//} if(0){








while(0){


/////////////////////////////////////////////////////////////////////////////ez után jó
		if (ready==1){

		
			ready=0;
			putstring("<ACK>");
			USART_Transmit(  tomb[0] );USART_Transmit(  tomb[1] );USART_Transmit(  tomb[2] );USART_Transmit(  tomb[3] );USART_Transmit(  tomb[4] );USART_Transmit(  tomb[5] );USART_Transmit(  tomb[6] );USART_Transmit(  tomb[7] );


			if ( (tomb[3]=='c') && (tomb[4]=='h') )
			{
				if ( tomb[5]=='1' ) out_chan=1;
				if ( tomb[5]=='2' ) out_chan=2;
			}	
			else out_chan=0;
			
		}

	
	input_handler();

		if (out_enable==1) {
			ledch(out_chan);
			}
		if (out_enable==0) {
			ledch(0);
			}
	


	}//while
}//main


