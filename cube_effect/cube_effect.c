#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include <avr/interrupt.h>
#define FOSC 8000000
#define BAUD 4800
#define MYUBRR FOSC/16/BAUD-1



volatile char tomb[4];
volatile char i=0;



//*******uart_init******************************
void USART_Init( unsigned int ubrr)
	{
	/* Set baud rate */
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN)| (1 << RXCIE) ;
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1<<URSEL)|(3<<UCSZ0);
	}

//********uart_transmit************************
void USART_Transmit( unsigned char data )
{
/* Wait for empty transmit buffer */
while ( !( UCSRA & (1<<UDRE)) );
/* Put data into buffer, sends the data */
UDR = data;
}

//**********uart_receive**********************************************
char UART_Receive() // Ez a fuggveny a beerkezo adatokat kiolvassa az UDR regiszter bejovo pufferebol
{
  while(!(UCSRA & (1<<RXC)))  // Varakozas amig nincs uj bejovo adat
  {
     //  Varakozas
  }
  //Most mar van beerkezett adat, amit kiolvasunk a pufferbol
  return UDR;
}

//***********uart_string************************** putstring("hello");
void putstring(const char *ptr){
  while(*ptr)
  {
   USART_Transmit( *(ptr++));  
  }
}

//***********uart_num****************** putnum(1023)
void putnum(unsigned int i)
{
unsigned char c[7]; 
itoa(i, c, 10); 
putstring(c);
}


//******uart_int**********************************************
ISR(USART_RXC_vect)
{
tomb[i]=UART_Receive();
USART_Transmit(tomb[i]);
i++;
if(i==4)i=0;
}



void Konfig8bitADC()        // ADC konfiguralas (beallitas)

{

//    ADMUX = 0b01100000;    // Vcc mint referencia, balra rendezett ADC eredmeny

           ADMUX |= (1<<REFS0)|(1<<ADLAR);    // Vcc mint referencia, balra rendezett ADC eredmeny

//    ADCSRA = 0b10000011;    // ADC engedelyezese, ADC eloosztas = 8 (125 KHz)

           ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0);    // ADC engedelyezese, ADC eloosztas = 8 (125 KHz)

}

 

unsigned char Beolvas8bitADC(unsigned char csatorna)

{

           ADMUX = (ADMUX & 0b11110000) | csatorna;

           ADCSRA |= (1<<ADSC);    // ADC konverzio elinditasa

           while (ADCSRA & (1<<ADSC));        // varas az atalakitasra

           ADCSRA |= (1<<ADSC);          // konverzió elindítás

           while (ADCSRA & (1<<ADSC));        // varas az atalakitasra

           return (ADCH);        // ADC ertek visszaadasa (csak a felso 8 bit (ADCH), az also 2 zajos bit elhagyasa)

}









void main()
{
	unsigned char i;

	//Initialize LCD module
	InitLCD(LS_BLINK|LS_ULINE);
	USART_Init( MYUBRR);
	Konfig8bitADC(); 
	//Clear the screen
	LCDClear();

sei();

	while(1)
	{
	LCDWriteIntXY(0,0,tomb[0],3);
	LCDWriteIntXY(4,0,tomb[1],3);
	LCDWriteIntXY(8,0,tomb[2],3);
	LCDWriteIntXY(12,0,tomb[3],3);
	_delay_ms(50);

	
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	while(0)
	{
	//	tomb=Beolvas8bitADC(5)/32;
		LCDWriteIntXY(0,0,tomb,3);
		_delay_ms(5);

		if (tomb==0){USART_Transmit(96);USART_Transmit(6);USART_Transmit(0);USART_Transmit(0);USART_Transmit(0);USART_Transmit(0);USART_Transmit(0);USART_Transmit(0);}
		
		if (tomb==1){USART_Transmit(255);USART_Transmit(255);USART_Transmit(0);USART_Transmit(0);USART_Transmit(0);USART_Transmit(0);USART_Transmit(0);USART_Transmit(0);}

		if (tomb==2){USART_Transmit(255);USART_Transmit(255);USART_Transmit(96);USART_Transmit(6);USART_Transmit(0);USART_Transmit(0);USART_Transmit(0);USART_Transmit(0);}

		if (tomb==3){USART_Transmit(255);USART_Transmit(255);USART_Transmit(255);USART_Transmit(255);USART_Transmit(0);USART_Transmit(0);USART_Transmit(0);USART_Transmit(0);}

		if (tomb==4){USART_Transmit(255);USART_Transmit(255);USART_Transmit(255);USART_Transmit(255);USART_Transmit(96);USART_Transmit(6);USART_Transmit(0);USART_Transmit(0);}

		if (tomb==5){USART_Transmit(255);USART_Transmit(255);USART_Transmit(255);USART_Transmit(255);USART_Transmit(255);USART_Transmit(255);USART_Transmit(0);USART_Transmit(0);}

		if (tomb==6){USART_Transmit(255);USART_Transmit(255);USART_Transmit(255);USART_Transmit(255);USART_Transmit(255);USART_Transmit(255);USART_Transmit(96);USART_Transmit(6);}

		if (tomb==7){USART_Transmit(255);USART_Transmit(255);USART_Transmit(255);USART_Transmit(255);USART_Transmit(255);USART_Transmit(255);USART_Transmit(255);USART_Transmit(255);}







	}

}































