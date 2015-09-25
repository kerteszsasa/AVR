#define FOSC 7372800// Clock Speed
#define BAUD 4800
#define MYUBRR FOSC/16/BAUD-1

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>


extern float temp100;








void USART_Init( unsigned int ubrr);
void USART_Transmit( unsigned char data );
void USART_Transmit( unsigned char data );
char UART_Receive();
void Konfig10bitADC();
unsigned int Beolvas10bitADC(unsigned char csatorna);
void putstring(const char *ptr);
void putnum(unsigned int i);
long int beolvas(void);
