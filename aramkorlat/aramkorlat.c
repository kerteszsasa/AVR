#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "lcd.h"

volatile int timer=0;
long int a;
unsigned char i;
volatile unsigned char sec=0;
unsigned char min=49;
unsigned char hour=14;

//***************************************************
unsigned char Beolvas8bitADC(unsigned char csatorna)
   
      {
  
      ADMUX = (ADMUX & 0b11110000) | csatorna;   // ADC csatorna kivalasztasa
      ADCSRA |= (1<<ADSC);    // ADC konverzio elinditasa
      while (ADCSRA & (1<<ADSC));    // varas az atalakitasra
      ADCSRA |= (1<<ADSC);         // konverzi� elind�t�s
      while (ADCSRA & (1<<ADSC));    // varas az atalakitasra
      return (ADCH);     // ADC ertek visszaadasa (csak a felso 8 bit (ADCH), az also 2 zajos bit elhagyasa)
  
      }

//*********************************************
void InitADC(void)
{
ADMUX |= (1<<REFS0)|(1<<ADLAR);  
ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0);
}


void InitTIMER(void)
{
TCCR0=1<<CS01|1<<CS00;	//�rajel 64-es el�oszt�s
TIMSK=1<<TOIE0;	//timer enable
}



//**************************************
ISR(TIMER0_OVF_vect){
timer++;
if(timer==450){timer=0; sec++;}

//7372800/64/256/450=1s !!!
}





void main()
{

InitTIMER();

InitADC();


InitLCD(LS_BLINK|LS_ULINE);	//Initialize LCD module


LCDClear();	//Clear the screen

sei();
//************


/*	while(0)
	{


		a=Beolvas8bitADC(5);
		a*=2;
		a-=273;
		i=a; //mert a fv csak int �rt�ket v�r �s az a egfy long



		LCDWriteIntXY(0,0,hour,2);
		LCDWriteStringXY(2,0,":");
		LCDWriteIntXY(3,0,min,2);
		LCDWriteStringXY(5,0,":");
		LCDWriteIntXY(6,0,sec,2);

		LCDWriteIntXY(10,0,i,3);
		LCDData(0b11011111);
		LCDWriteStringXY(14,0,"C");

		_delay_ms(100);
	
		if(sec==60){sec=0; min++;}
		if(min==60){min=0; hour++;}
		if(hour==24){hour=0;}

		

	}
	*/



unsigned char alma;
	

while(1)
{
alma=Beolvas8bitADC(5);
LCDWriteIntXY(0,0,alma,3);
LCDWriteStringXY(15,0,"C");
_delay_ms(1000);

}







}



