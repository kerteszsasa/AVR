#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 8000000UL



#define r_on() PORTB|=0b000000100;
#define y_on() PORTB|=0b000000010;
#define g_on() PORTB|=0b000000001;

#define r_off() PORTB&=~0b000000100;
#define y_off() PORTB&=~0b000000010;
#define g_off() PORTB&=~0b000000001; 


int state=0;


//*******************************************
void delay(int time){
	for(int i=0;i<time;i++){
		_delay_us(250);
	}
}

//*******************************************
void AD_init(){
	    DIDR0 = (1<<ADC1D);
    ADMUX = (0<<REFS1)
          | (0<<REFS0)    //Vcc mint referencia
          | (0<<ADLAR);
    ADCSRA = (1<<ADEN)    //adc enable
           | (0<<ADPS2)
           | (0<<ADPS1)
           | (0<<ADPS0); //elõosztó 128as
    ADCSRB = 0x00;
}

//********************************************
uint16_t ReadADC(uint8_t channel) {
 
 
    ADMUX = (ADMUX & 0b11110000) | channel;    //csat. kiválaszt
    ADCSRA |= (1<<ADSC);    //start
    while(ADCSRA & (1<<ADSC));//várok amíg átalakít
    return (ADCL | (ADCH<<8));//adc kiolvasás
}

//********************************************
int main()
{
	//set pin directions
	DDRB=0b00000111;
	AD_init();

    while(1){
		//normál mûködés
		if(PINB & 0b00010000){
			switch (state) {

			    case 0:{	//P
					r_on();
					y_off();
					g_off();
					delay(30*ReadADC(3));
					state++;
					break;
				}
			    case 1:{	//PS
					r_on();
					y_on();
					g_off();
					delay(4*ReadADC(3));
					state++;
					break;
				}
				case 2:{	//Z
					r_off();
					y_off();
					g_on();
					delay(30*ReadADC(3));
					state++;
					break;
				}
				case 3:{	//s
					r_off();
					y_on();
					g_off();
					delay(4*ReadADC(3));
					state = 0;
					break;
				}
			}
		}
		//sarga villog
		else{
			state =0;
			r_off();
			g_off();
			y_off();
			delay(1*ReadADC(3));

			y_on();
			delay(1*ReadADC(3));
		}


	
	}

}
