#include <avr/io.h>
   
#include <avr/interrupt.h>

#include <util/delay.h>


#include <avr/interrupt.h>

#include <avr/sleep.h>



//----------------------------

#define blueon	(PORTB &= ~(1<<PINB0))
#define redon	(PORTB &= ~(1<<PINB1))
#define greenon	(PORTB &= ~(1<<PINB2))

#define blueoff	(PORTB |=  (1<<PINB0))
#define redoff	(PORTB |=  (1<<PINB1))
#define greenoff	(PORTB |=  (1<<PINB2))

#define button (PINB & 0b00001000)


//---------------------------------------------
void Init(void) {
	DDRB     |= (1<<PINB0)		//kimenet
             |  (1<<PINB1)		//kimenet
             |  (1<<PINB2)		//kimenet
			 |  (0<<PINB3);		//bemenet

			 _delay_ms(10);

			 PORTB|=0b00000111;

}
//................................................


//-----------------------------------------------
void RGB(unsigned char  red,unsigned char  green,unsigned char  blue) {
	while(red ||green||blue) {
		if(red){
			redon;
			red--;
		}
		else redoff;

		if(green){
			greenon;
			green--;
		}
		else greenoff;

		if(blue){
			blueon;
			blue--;
		}
		else blueoff;

	
	}
}
//.....................................................................


//------------------------------------------------------
void Led(unsigned char  red,unsigned char  green,unsigned char  blue){
	int count=0;				//fade sebesség
	for(count=2;count>0;count--){
		RGB(red,green,blue);
	}
}
//........................................................................


//-----------------------------------------------------------------------------
void Kever(){
	 unsigned char val = 1;       //belessen az 1. case-be.
  
 unsigned char R_duty = 128;     //kezdoertekek
  
 unsigned char G_duty = 30;    
  
 unsigned char B_duty = 200;
  
       
  
                 for(;!button;) {     // vegtelen ciklus , amíg gombot nem nyomok
  
                     
  
                    if(!(R_duty||G_duty||(!B_duty))) {blueon; _delay_ms(200);}		//ez csak azért kell h a tiszta színek is sokáig látszódjanak, itt egy pillanatra megáll a fade
					if(!(R_duty||B_duty||(!G_duty))) {greenon; _delay_ms(200);}
					 if(!(B_duty||G_duty||(!R_duty))) {redon; _delay_ms(200);}
				
					 switch(val) {                    // színek fadelése
  
                         case 1:    if(R_duty<0xFF) {R_duty++; Led(R_duty,G_duty,B_duty);}
  
                                 else val = 2;
  
                                 break;
  
                        case 2:    if(B_duty) {B_duty--;Led(R_duty,G_duty,B_duty);}
  
                                 else val = 3;
  
                                 break;
  
                         case 3:    if(G_duty<0xFF){ G_duty++;Led(R_duty,G_duty,B_duty);}
  
                                 else val = 4;
  
                                 break;           // break!! Különben továbbmegy..
  
                         case 4:    if(R_duty) {R_duty--;Led(R_duty,G_duty,B_duty);}
  
                                 else val = 5;
  
                                 break;
  
                         case 5:    if(B_duty<0xFF) {B_duty++;Led(R_duty,G_duty,B_duty);}
  
                                 else val = 6;
  
                                 break;
  
                         case 6:    if(G_duty) {G_duty--;Led(R_duty,G_duty,B_duty);}
  
                                 else val = 1;
  
                                 break;
  
                     }
  
                   
  
                 }

}

//...........................................................................



//---------------------------------------------------------------------------
int main(void) {
	Init();
	_delay_ms(1);
	while(1){
		for(;!button;){RGB(0,255,0);}
		_delay_ms(200);

		for(;!button;){RGB(255,255,0);}
		_delay_ms(200);
 	
		Kever();
 		_delay_ms(200);

       
 	}




	return(0);
}



