#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define FOSC 1000000
#define BAUD 4800
#define MYUBRR FOSC/16/BAUD-1

volatile char tomb[8];
char index=0;
volatile allapot=0;




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
tomb[index]=UART_Receive();
USART_Transmit(  tomb[index] );
index++;
if(index==8)index=0;
}


//************INT0*************************
ISR (INT0_vect)
{

allapot=!allapot;
}



















int main() //Main fõprogram
{
DDRA=0b00001111;
DDRB=0b11110000;
DDRC=255;
DDRD=0b11110000;




//külsõ megszakítás
MCUCR=1<<ISC01; //int0 megszakítást fogom használni, lefutó élre reagáljon
GICR=1<<INT0;	// külsõ megszakítások engedélyezése 



sei();
USART_Init ( MYUBRR );
USART_Transmit(  'B' );

while(1)
	{
		while(allapot==0)//tomb kijelzése
		{
			PORTB=16;
			PORTA=tomb[0]&0b00001111;
			PORTD=tomb[0]&0b11110000;
			PORTC=tomb[1];
			_delay_ms(1);

			PORTB=32;
			PORTA=tomb[2]&0b00001111;
			PORTD=tomb[2]&0b11110000;
			PORTC=tomb[3];
			_delay_ms(1);

			PORTB=64;
			PORTA=tomb[4]&0b00001111;
			PORTD=tomb[4]&0b11110000;
			PORTC=tomb[5];
			_delay_ms(1);

			PORTB=128;
			PORTA=tomb[6]&0b00001111;
			PORTD=tomb[6]&0b11110000;
			PORTC=tomb[7];
			_delay_ms(1);
		}





		while(allapot)//forgó effect
		{
			PORTB=0b11110000;	

			PORTA=1;
			PORTD=32;
			PORTC=4+128;
			_delay_ms(100);

			PORTA=2;
			PORTD=32;
			PORTC=4+64;
			_delay_ms(100);

			PORTA=4;
			PORTD=64;
			PORTC=2+32;
			_delay_ms(100);

			PORTA=8;
			PORTD=64;
			PORTC=2+16;
			_delay_ms(100);

			PORTA=0;
			PORTD=128+64;
			PORTC=2+1;
			_delay_ms(100);

			PORTA=0;
			PORTD=32+16;
			PORTC=4+8;
			_delay_ms(100);

		}

	}
return 0;
}



