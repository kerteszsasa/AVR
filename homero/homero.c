/* -----------------------------------------------------------------------
 * Title:    Led counting reaction on pressed switch (I/O)
 * Hardware: ATmega8
 * Software: WinAVR 20060421
 -----------------------------------------------------------------------*/
 
#include <avr/io.h>
#include <util/delay.h>
 
int main(void);
char shift(uint8_t n);
void led1(char n);
char shift(uint8_t n);





//main******************************************************************
int main(void) {
 DDRB =0xFF;

DIDR0=1<<ADC1D;
ADMUX=0b00000001;

ADCSRA=0b10000100;
PORTB=1<<PB2;





while(8){

int k=0;
for(k=0;k<200;k++)
{
//led(k);

led(adc());
}
}

}
//endofmain*************************************************************



int adc(void)
{
DIDR0=1<<ADC1D;
ADMUX=0b00100001;
ADCSRA=0b10000100;
ADCSRA|=1<<ADSC;
while(!(ADCSRA&1<<ADIF));
ADCSRA&=~(1<<ADIF);

return (ADCH);
}



void led(int i)
{
//if(i>99){_delay_ms(111);return;}
long int k;
for(k=0;k<255;k++){
led1(i/10);_delay_us(800);
led2(i%10);_delay_us(800);}
}















//********************************
char shift(uint8_t n)
{
uint8_t i;
uint8_t a=n;
for(i=0;i<8;i++)
	{
	PORTB=(a&0b00000001)<<4;  //n legalsó bitjét kiíratom
	clk();
	a=a>>1;	//na értékét jobbra tolom egyel
	}
}//*******************************


//********************************
void clk(void)
{
PORTB=PORTB|(1<<PB3);
PORTB=PORTB&~(1<<PB3);
}//********************************

//***********************************
void led1(char n)
{
	if(n<10)	
   {
      switch (n)
      {
         case 0:
         shift(0b10111110);
         break;

         case 1:
         shift(0b00011000);
         break;

         case 2:
         shift(0b10101011);
         break;

         case 3:
         shift(0b10011011);
         break;

         case 4:
         shift(0b00011101);
         break;

         case 5:
         shift(0b10010111);
         break;

         case 6:
         shift(0b10110111);
         break;

         case 7:
         shift(0b00011010);
         break;

         case 8:
         shift(0b10111111);
         break;

         case 9:
         shift(0b10011111);
         break;
      }
	}
	else shift(0b00000001);
	PORTB=(1<<PB0);
	


}//**********************************

//***********************************
void led2(char n)
{
	if(n<10)	
   {
      switch (n)
      {
         case 0:
         shift(0b10111110);
         break;

         case 1:
         shift(0b00011000);
         break;

         case 2:
         shift(0b10101011);
         break;

         case 3:
         shift(0b10011011);
         break;

         case 4:
         shift(0b00011101);
         break;

         case 5:
         shift(0b10010111);
         break;

         case 6:
         shift(0b10110111);
         break;

         case 7:
         shift(0b00011010);
         break;

         case 8:
         shift(0b10111111);
         break;

         case 9:
         shift(0b10011111);
         break;
      }
	}
	else shift(0b00000001);
	PORTB=(1<<PB1);
	


}//**********************************
