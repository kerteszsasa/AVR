#include "adc.h"

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
