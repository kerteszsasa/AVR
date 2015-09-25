#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>






unsigned char Beolvas8bitADC(unsigned char csatorna)
{

ADMUX = (ADMUX & 0b11110000) | csatorna;   // ADC csatorna kivalasztasa

ADCSRA |= (1<<ADSC);    // ADC konverzio elinditasa

while (ADCSRA & (1<<ADSC));    // varas az atalakitasra

ADCSRA |= (1<<ADSC);         // konverzió elindítás

while (ADCSRA & (1<<ADSC));    // varas az atalakitasra

return (ADCH);     // ADC ertek visszaadasa (csak a felso 8 bit (ADCH), az also 2 zajos bit elhagyasa)

}

   
void Konfig8bitADC()    // ADC konfiguralas (beallitas)
{

 ADMUX |= (1<<REFS0)|(1<<ADLAR);    // Vcc mint referencia, balra rendezett ADC eredmeny

 ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0);  // ADC engedelyezese, ADC eloosztas = 8 (125 KHz)

}
   





void Wait()
{
_delay_ms(200);
   uint8_t i=0;
   uint8_t loops = Beolvas8bitADC(0);

   for(i;i<loops;i++)
      _delay_ms(5);
	   
}

void main()
{
   DDRD=0b00011111;
   Konfig8bitADC() ;
   
   
   

_delay_ms(5000);
   



   while(1)
   {

   //jobbra fut
PORTD = 1;
Wait();
PORTD = 3;
Wait();
PORTD = 7;
Wait();
PORTD = 15;
Wait();
PORTD = 31;
Wait();
PORTD = 0;
Wait();
PORTD = 16;
Wait();
PORTD = 24;
Wait();
PORTD = 28;
Wait();
PORTD = 30;
Wait();
PORTD = 31;
Wait();
PORTD = 0;
Wait();



PORTD = 4;
Wait();
PORTD = 14;
Wait();
PORTD = 31;
Wait();
PORTD = 0;
Wait();
PORTD = 17;
Wait();
PORTD = 27;
Wait();
PORTD = 31;
Wait();
PORTD = 0;
Wait();






   }
}// end of main









   
     




