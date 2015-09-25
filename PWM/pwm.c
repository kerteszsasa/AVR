#include <avr/io.h>
#include <avr/interrupt.h>	
#include <util/delay.h>
//#include "i2csoft.h"
//#include "routines.h"
#include "uart.h"


void Konfig8bitADC()        // ADC konfiguralas (beallitas)
{
//    ADMUX = 0b01100000;    // Vcc mint referencia, balra rendezett ADC eredmeny
           ADMUX |= (1<<REFS0)|(1<<ADLAR);    // Vcc mint referencia, balra rendezett ADC eredmeny
//    ADCSRA = 0b10000011;    // ADC engedelyezese, ADC eloosztas = 8 (125 KHz)
           ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0);    // ADC engedelyezese, ADC eloosztas = 8 (125 KHz)
}
 

void Konfig10bitADC()        // ADC konfiguralas (beallitas)
{
           ADMUX |= (1<<REFS0);    // Vcc mint referencia
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

unsigned int Beolvas10bitADC(unsigned char csatorna)
{
           ADMUX = (ADMUX & 0b11110000) | csatorna;
           ADCSRA |= (1<<ADSC);        // elso ADC konverzio elinditasa
           while (ADCSRA & (1<<ADSC));    // varas az atalakitasra
           ADCSRA |= (1<<ADSC);         // masodik ADC konverzió elindítás
           while (ADCSRA & (1<<ADSC));    // varas az atalakitasra
           return (ADCL | (ADCH<<8));    // ADC ertek kiolvasasa
}


 
void led(char c)
{
if(c) PORTD|=(1<<4);
else PORTD&=~(1<<4);
}




void main()
{
DDRD=(1<<4);
DDRB=(1<<3);

//Konfig8bitADC(); 
 Konfig10bitADC();
 USART_Init( MYUBRR);

 putstring("HELLO");

	while(0)
	{
		led(1);
		_delay_ms(500);
		led(0);
		_delay_ms(500);
	}

TCCR2=0b01101001;
OCR2=254;


while(1) 
{

led(1);


 putnum( Beolvas10bitADC(5) ); putstring("     ");
 _delay_ms(500);


}























char TMP=0;

TMP=OCR2 = Beolvas8bitADC(5);	_delay_ms(50);

while(1)
{
	if( TMP < Beolvas8bitADC(4) ) OCR2--;
	if( TMP > Beolvas8bitADC(4) ) OCR2++;
	if( OCR2==255 ) OCR2--;
	if( OCR2==0 ) OCR2++;
	_delay_ms(10);
	TMP = Beolvas8bitADC(5);
}

while(1)
{
	OCR2=1;
	_delay_ms(5000);
		OCR2=50;
	_delay_ms(5000);
		OCR2=100;
	_delay_ms(5000);
		OCR2=150;
	_delay_ms(5000);
		OCR2=200;
	_delay_ms(5000);
}

}//endofmain
