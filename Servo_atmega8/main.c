
#include <avr/io.h>

#include <util/delay.h>

//Simple Wait Function
void Wait()
{
   uint8_t i;
   for(i=0;i<50;i++)
   {
      _delay_loop_2(0);
      _delay_loop_2(0);
      _delay_loop_2(0);
   }

}

int main()
{
   //servo settings
   TCCR1A = (1<<COM1A1) | (1<<WGM11) ;
   TCCR1B =(1<<WGM13) |(1<<WGM12) |(1<<CS10) | (1<<CS11);
   ICR1=2499; //50 hz 
   OCR1A = 188; // servo 1.5 ms

   DDRB|=(1<<PB1);   //PWM Pin as Out
   DDRB|=(1<<PB0);   //YELLOW LED Pin as Out

   //TODO: analóg bemenet olvasása

	DDRC=0; // c port bemenet

	int i=0;

    while(1)
   {
/*	if ((PINC&(32+16+8)) ==(16+8))	PORTB|=(1<<PB0); //32 pin5 jp1
	else PORTB&=~(1<<PB0);

	if ((PINC&(32+16+8)) ==(32+8))	PORTB|=(1<<PB0); //16 pin4 jp2
	else PORTB&=~(1<<PB0);

	if ((PINC&(32+16+8)) ==(32+16))	PORTB|=(1<<PB0); //8 pin3 jp3
	else PORTB&=~(1<<PB0);
*/


	if((PINC&(32+16+8)) ==(16+8)) { // felsõ jumper

      OCR1A=200;  //default state
	  PORTB&=~(1<<PB0);
      
	  for(i=0 ; i<40 ; i++) _delay_ms(1000);
	  
	  OCR1A=183;   //fényképezõ exponál
	  PORTB|=(1<<PB0);
      _delay_ms(800);
	  }

	  if((PINC&(32+16+8)) ==(32+8)) { // középsõ jumper

      OCR1A=200;  //default state
	  PORTB&=~(1<<PB0);
      
	  for(i=0 ; i<70 ; i++) _delay_ms(1000);
	  
	  OCR1A=183;   //fényképezõ exponál
	  PORTB|=(1<<PB0);
      _delay_ms(800);
	  }

	  if((PINC&(32+16+8)) ==(32+16)) { // alsó jumper

      OCR1A=200;  //default state
	  PORTB&=~(1<<PB0);
      
	  for(i=0 ; i<3 ; i++) _delay_ms(1000);
	  
	  OCR1A=183;   //fényképezõ exponál
	  PORTB|=(1<<PB0);
      _delay_ms(800);
	  }


	  OCR1A=200;  //default state
	  PORTB&=~(1<<PB0);



 
   }
   
   
   
   while(1)
   {

      OCR1A=125;   //+90 degree clockwise
      Wait();

      OCR1A=188;  //0 degree
      Wait();

      OCR1A=250;  //-90 degree

      Wait();

      OCR1A=188;  //0 degree
      Wait();
   }
return 0;
}
