#include "routines.h"



char Setpot (char value) {
	char test=0;
	SoftI2CStart();
	test+= SoftI2CWriteByte( 0b01011000);//address bytes
	test+= SoftI2CWriteByte( 0b00000000);//address bytes
	test+= SoftI2CWriteByte( value);
	SoftI2CStop();
	return test;
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
