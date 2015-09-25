#include "usart.h"
#include "misep.h"


void USART_Init( unsigned int ubrr);
void USART_Transmit( unsigned char data );
char UART_Receive();
void putstring(const char *ptr);
void putnum(unsigned int i);


//*******uart_init******************************************************
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

//********uart_transmit******************************************************
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






//***********uart_string************************** putstring("hello");******
void putstring(const char *ptr)
{
  while(*ptr)
  {
   USART_Transmit( *(ptr++));  
  }
}

//***********uart_num****************** putnum(1023)**************************
void putnum(unsigned int i)
{
unsigned char c[7]; 
itoa(i, c, 10); 
putstring(c);
}




//******uart_int**********************************************
ISR(USART_RXC_vect)
{

// call from misep.c
Incoming_char( UART_Receive() );



}





