#include <avr/io.h>
#include <avr/interrupt.h>	
#include <util/delay.h>


#define FOSC 8000000// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1






//*******uart_init*************************************************************************************
void USART_Init( unsigned int ubrr);

//********uart_transmit********************************************************************************
void USART_Transmit( unsigned char data );

//**********uart_receive*******************************************************************************
char UART_Receive(); // Ez a fuggveny a beerkezo adatokat kiolvassa az UDR regiszter bejovo pufferebol

//***********uart_string************************************************** putstring("hello");
void putstring(const char *ptr);

//***********uart_num****************** putnum(1023)
void putnum(unsigned int i);

//******uart_int**************************************************************************************
//ISR(USART_RXC_vect);
