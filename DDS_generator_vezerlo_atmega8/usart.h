#define FOSC 8000000// Clock Speed
#define BAUD 19200
#define MYUBRR FOSC/16/BAUD-1

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>



void USART_Init( unsigned int ubrr);
void USART_Transmit( unsigned char data );

char UART_Receive();

void putstring(const char *ptr);
void putnum(unsigned int i);

