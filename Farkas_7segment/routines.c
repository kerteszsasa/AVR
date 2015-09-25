#include "routines.h"



void SevenSegment(uint8_t n,uint8_t dp)
{
/*
This function writes a digits given by n to the display
the decimal point is displayed if dp=1

Note: n must be less than 9
*/
   if(n<10)
   {
      switch (n)
      {
         case 0:
         SEVEN_SEGMENT_PORT=0b00111111;
         break;

         case 1:
         SEVEN_SEGMENT_PORT=0b00000110;
         break;

         case 2:
         SEVEN_SEGMENT_PORT=0b01011011;
         break;

         case 3:
         SEVEN_SEGMENT_PORT=0b01001111;
         break;

         case 4:
         SEVEN_SEGMENT_PORT=0b01100110;
         break;

         case 5:
         SEVEN_SEGMENT_PORT=0b01101101;
         break;

         case 6:
         SEVEN_SEGMENT_PORT=0b01111101;
         break;

         case 7:
         SEVEN_SEGMENT_PORT=0b00000111;
         break;

         case 8:
         SEVEN_SEGMENT_PORT=0b01111111;
         break;

         case 9:
         SEVEN_SEGMENT_PORT=0b01101111;
         break;

      }
      if(dp)
      {
         //if decimal point should be displayed

         //make 0th bit Low
         SEVEN_SEGMENT_PORT|=0b10000000;
      }
   }
   else
   {
      //This symbol on display tells that n was greater than 9
      //so display can't handle it

      SEVEN_SEGMENT_PORT=0b00000000;
   }

   if(n=='V')SEVEN_SEGMENT_PORT=0b00111110;
   if(n=='A')SEVEN_SEGMENT_PORT=0b01110111;
}



void DispNum(uint8_t num,uint8_t dp,uint8_t time)
{

	uint8_t digit1,digit2,digit3;
	digit3=num%10;
	num=num/10;
	digit2=num%10;
	num=num/10;
	digit1=num%10;

	for(;time;time--)
	{
		PORTD=(0<<5)|(1<<6)|(1<<7);
		SevenSegment(digit1, (dp==3));
		_delay_ms(5);
	
		PORTD=(1<<5)|(0<<6)|(1<<7);
		SevenSegment(digit2, (dp==2));
		_delay_ms(5);
	

		PORTD=(1<<5)|(1<<6)|(0<<7);
		SevenSegment(digit3, (dp==1));
		_delay_ms(5);

	}

	PORTD=(1<<5)|(1<<6)|(1<<7);	//kijelzõ kikapcsolása
	SevenSegment(10, 0);
}

void Current (int current)
{
	DispNum(current,2,DISPTIME);
	PORTD=(1<<5)|(1<<6)|(0<<7);
	SevenSegment('A', 0);
	_delay_ms(DISPTIME*15);
	PORTD=(1<<5)|(1<<6)|(1<<7);
}

void Voltage(int voltage)
{
	DispNum(voltage,2,DISPTIME);
	PORTD=(1<<5)|(1<<6)|(0<<7);
	SevenSegment('V', 0);
	_delay_ms(DISPTIME*15);
	PORTD=(1<<5)|(1<<6)|(1<<7);
}

void Konfig10bitADC()        // ADC konfiguralas (beallitas)
{
           ADMUX |= (1<<REFS0);    // Vcc mint referencia
           ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0);    // ADC engedelyezese, ADC eloosztas = 8 (125 KHz)
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
