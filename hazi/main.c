#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "i2csoft.h"
#include "uart.h"
#include "temperature.h"


#define EE_BASE 0xA2
#define SENSOR_BASE A0

volatile char index=0; 	// timer0 interrupt counter
volatile signed int kiir;
volatile char button_flag=0; //ext1 int flag
volatile char* temp;

//******************************************




//**  timer0 int
ISR(TIMER0_OVF_vect)
{
	index++;
	if(index==7)index=0;

}


//** ext int0 
ISR (INT1_vect)
{
	button_flag=1;

}


void save(char data)
{
int index_save=1;
	while(index_save)
	{
	EEReadByte(0xa2, index_save-1, temp);
	if(temp[0]==255)
		{
		//LCDWriteString("DATA");
		EEWriteByte(0xa2, index_save-1, data);
		EEWriteByte(0xa2, index_save, 255);
		break;
		}
		index_save++;
	}
}



void send(void)
{
int index_send=0;
signed int data_s;
EEReadByte(0xa2, index_send, temp);
while(temp[0]!=255)
	{

data_s=temp[0];
data_s=data_s<<3;
data_s*=125;
		putnum(data_s/1000);
		USART_Transmit(  'C' );
		USART_Transmit( '   ' );
	
		LCDGotoXY(0,0);
		LCDData(temp[0]);



	index_send++;
	EEReadByte(0xa2, index_send, temp);
	}


}


///**********************************************************************************/

void main()
{

	// timer0 init
	TCCR0= (1<<CS02) | (1<<CS00);
	TIMSK=(1<<TOIE0);

	USART_Init ( MYUBRR );	//init uart module

	//Initialize LCD module
	InitLCD(LS_BLINK|LS_ULINE);
	//Clear the screen
	LCDClear();

	MCUCR=1<<ISC11;	//int1 falling edge
	GICR= (1<<INT1); // int1 enable

	DDRB=0;	//portB bemenet
	sei();	// global int enable


//***************************************************
//EEWriteByte(0xa2, 6, 255);

//save('d');

/*

for (char i=0; i<10;i++)
{
EEReadByte(0xa2, i, temp);
LCDData(temp[0]);
USART_Transmit( 'A' );

_delay_ms(10);
}



USART_Transmit( 1);
USART_Transmit( 'A' );
USART_Transmit( 'A' );
USART_Transmit( 125 );

while(1){USART_Transmit( 0x41 );
_delay_ms(100);}
*/






char status=0;
//*********************************************
while(1)
{



	if(index==0)
		{
			if(status==0)
			{
			kiir=GetTemp()*125;
			LCDWriteIntXY(0,0,kiir/1000,2);
			LCDWriteString(".");
			LCDWriteIntXY(3,0,kiir%1000,3);
			LCDData(0b11011111);
			LCDWriteStringXY(7,0,"C");
			
			save(GetTemp()>>3);
			}
		}

	if(button_flag==1)
	{
		status=1;
		LCDClear();
		LCDWriteString("MENU");
			//LCDWriteIntXY(0,0,PINB,5);
			_delay_ms(100);



		if(PINB&1)
		{
		LCDGotoXY(0,0);
		LCDWriteString("EEPROM CLEAR");
		EEWriteByte(0xa2, 0, 255);
		_delay_ms(250);
		_delay_ms(250);
		_delay_ms(250);
		_delay_ms(250);
		LCDClear();
		button_flag=0;
		status=0;
		}

		if(PINB&2)
		{
		LCDGotoXY(0,0);
		LCDWriteString("DATA SEND");
		send();
		_delay_ms(250);
		_delay_ms(250);
		_delay_ms(250);
		_delay_ms(250);
		LCDClear();
		button_flag=0;
		status=0;
		}
		


	
	}




}





}//end of main



