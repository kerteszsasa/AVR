#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


volatile uint8_t alma;
volatile uint8_t valt1;
//volatile uint8_t valt2;




 unsigned char Beolvas8bitADC(unsigned char csatorna)
   
      {
  
      ADMUX = (ADMUX & 0b11110000) | csatorna;   // ADC csatorna kivalasztasa
  
      ADCSRA |= (1<<ADSC);    // ADC konverzio elinditasa
  
      while (ADCSRA & (1<<ADSC));    // varas az atalakitasra
  
      ADCSRA |= (1<<ADSC);         // konverzió elindítás
  
      while (ADCSRA & (1<<ADSC));    // varas az atalakitasra
  
      return (ADCH);     // ADC ertek visszaadasa (csak a felso 8 bit (ADCH), az also 2 zajos bit elhagyasa)
  
      }







void Wait()
{
   uint8_t i=0;
   for(;i<20;i++)
      _delay_loop_2(0);
}

void main()
{
   //Set PORTC0 as output

	//external interrupt
	GICR |= (1<<INT0); // 4-es labat (PD2) hasznaljuk ebben a peldaban //gicr=0 tiltja
	MCUCR = (1<<ISC01) ; // megszakitas az INT0 labon, lefuto el eseten

//int1
	GICR |= (1<<INT1); // 4-es labat (PD2) hasznaljuk ebben a peldaban //gicr=0 tiltja
	MCUCR = (1<<ISC11) ; // megszakitas az INT0 labon, lefuto el eseten








   DDRD=0b11000000;
   DDRB=0b000011111;


  alma=0;
  valt1=0;
  //valt2=0;
  Konfig8bitADC() ;

   TCCR0=5; //timer0 enable prescaler 1024
   TIMSK=1;
   sei ( );

   while(1)
   {
   unsigned char csatorna=1;


  // sevensegment( Beolvas8bitADC(5)/26);

	 //sevensegment(alma);
	
//sei ( );
     /*
	 sevensegment(alma);
	 _delay_ms(500);
	 sevensegment(alma-1);
	 if(alma==10) alma=0;
	 _delay_ms(1000);
	 
*/
//	cli();
     

   }
}

//7segment***********************************
void sevensegment(uint8_t num)
	{
		switch(num)
			{
			// DDRD=0b11000000;
		    //DDRB=0b000011111;
			case 0 :{PORTD=0b11000000;PORTB=0b000011011;break;}//
			case 1 :{PORTD=0b00000000;PORTB=0b000001010;break;}//
			case 2 :{PORTD=0b01000000;PORTB=0b000010111;break;}//
			case 3 :{PORTD=0b00000000;PORTB=0b000011111;break;}//
			case 4 :{PORTD=0b10000000;PORTB=0b000001110;break;}//
			case 5 :{PORTD=0b10000000;PORTB=0b000011101;break;}//
			case 6 :{PORTD=0b11000000;PORTB=0b000011100;break;}//
			case 7 :{PORTD=0b00000000;PORTB=0b000001011;break;}//
			case 8 :{PORTD=0b11000000;PORTB=0b000011111;break;}//
			case 9 :{PORTD=0b10000000;PORTB=0b000011111;break;}//
			}
	}
//**************************************************



//**************************************************
ISR (INT0_vect) {


//alma++;
//	 sevensegment(alma);

valt1=5;

//Wait();



}
//**************************************************

//*****************************************

ISR (TIMER0_OVF_vect) {


alma++;
	
if(alma==4)valt1++;
if(alma==5)alma=0;
 sevensegment(valt1);
 if(valt1==10)valt1=0;

//Wait();


}

//***********************



//*****************************
   
      void Konfig8bitADC()    // ADC konfiguralas (beallitas)
  
      {
   
                 ADMUX |= (1<<REFS0)|(1<<ADLAR);    // Vcc mint referencia, balra rendezett ADC eredmeny
   
                 ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0);  // ADC engedelyezese, ADC eloosztas = 8 (125 KHz)
  
      }
   
//***********************************
   
     





ISR (INT1_vect) {


//alma++;
//	 sevensegment(alma);

valt1=3;

//Wait();



}
