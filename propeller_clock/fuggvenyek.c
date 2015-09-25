#define FOSC 7372800// Clock Speed
#define BAUD 4800
#define MYUBRR FOSC/16/BAUD-1

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>


extern float temp100;
extern volatile unsigned char sec;
extern char szamlal;
extern unsigned char min;
extern unsigned char hour;




volatile int timer=0;






void USART_Init( unsigned int ubrr);
void USART_Transmit( unsigned char data );
void USART_Transmit( unsigned char data );
char UART_Receive();
void Konfig10bitADC();
unsigned int Beolvas10bitADC(unsigned char csatorna);
void putstring(const char *ptr);
void putnum(unsigned int i);
long int beolvas(void);
void convert(void);
ISR(TIMER0_OVF_vect);
void InitTIMER(void);




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




//*********konfig_uart************************************************
void Konfig10bitADC()        // ADC konfiguralas (beallitas)
{
	ADMUX |= (1<<REFS0);    // Vcc mint referencia
	ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0);    // ADC engedelyezese, ADC eloosztas = 8 (125 KHz)
}


//*********uart_10bit**************************************************
unsigned int Beolvas10bitADC(unsigned char csatorna)
{
   ADMUX = (ADMUX & 0b11110000) | csatorna;   //ADC csatorna kivalasztasa
   ADCSRA |= (1<<ADSC);    // elso ADC konverzio elinditasa
   while (ADCSRA & (1<<ADSC));        // varas az atalakitasra
   ADCSRA |= (1<<ADSC);          // masodik ADC konverzió elindítás
   while (ADCSRA & (1<<ADSC));        // varas az atalakitasra
   return (ADCL | (ADCH<<8));        // ADC ertek kiolvasasa
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
UART_Receive();


convert();

putnum(temp100);
USART_Transmit(  '\n' );
USART_Transmit(  '\r' );

}


//***********convert******************
void convert(void)
{
	//	long int a;

		temp100=beolvas();
		temp100=temp100*500/1023-273;


		temp100*=100;

		/***** tizedesponttal
		a=(temp100/100);
		a*=100;
		putnum(a/100);
		USART_Transmit(  '.' );
		putnum(temp100-a);	
		*/
	

}

//****beolvas********************************************
long int beolvas(void)
{
long int a=0;
	for(int i=0;i<100;i++)
	{
		a+=Beolvas10bitADC(5);
	}
	a/=100;
	return a;
}

//***************************************************************
void InitTIMER(void)
{
TCCR0=1<<CS01|1<<CS00;	//órajel 64-es elõosztás
TIMSK=1<<TOIE0;	//timer enable
}



//**************************************
ISR(TIMER0_OVF_vect)
{
timer++;
if(timer==450){timer=0; sec++;convert();}

//7372800/64/256/450=1s !!!
}
