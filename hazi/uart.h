#define FOSC 2000000// Clock Speed
#define BAUD 300
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

void putstring(const char *ptr);
void putnum(unsigned int i);

