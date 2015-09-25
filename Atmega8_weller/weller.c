#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"

#define pot 1
#define temp 0

#define on() PORTC|=4
#define off() PORTC&=~4

void Konfig10bitADC()    // ADC konfiguralas (beallitas)
{
    ADMUX |= 0;//(1<<REFS0)|(1<<REFS1);    // 2.56V mint referencia
    ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0);  // ADC engedelyezese, ADC eloosztas = 8 (125 KHz)
}
 
unsigned int Beolvas10bitADC(unsigned char csatorna)
{
	ADMUX = (ADMUX & 0b11110000) | csatorna;    //ADC csatorna kivalasztasa
	ADCSRA |= (1<<ADSC);    // ADC konverzio elinditasa
	while (ADCSRA & (1<<ADSC));    // varas az atalakitasra
	ADCSRA |= (1<<ADSC);         // konverzió elindítás
	while (ADCSRA & (1<<ADSC));    // varas az atalakitasra
	return (ADCL | (ADCH<<8));    // ADC ertek kiolvasasa
}

void main()
{


//output led
DDRC=4;


Konfig10bitADC();


	unsigned char i;
	unsigned long settemp=0;
	unsigned long gettemp=0;


	//Initialize LCD module
//	InitLCD(LS_BLINK|LS_ULINE);
		InitLCD(0);

	//Clear the screen
	LCDClear();


int barlength=0;
int barindex;

while(0){
		LCDClear();
		LCDData(255);
	
		_delay_ms(1000);
		}










	//LCDWriteString("SET128C TEMP255C");
	
	while(1){

		settemp=Beolvas10bitADC(pot);


/*
		settemp*=225;
		settemp/=512;
		settemp++;
		settemp/=5;
		settemp*=5;
		*/


		
		settemp/=23;
		settemp++;
	
		settemp*=10;



		
		//settemp=Beolvas10bitADC(pot)/11*5;
	//	_delay_ms(1000);
		//gettemp=( Beolvas10bitADC(temp)-740 )*30/21 + 150;
		//gettemp=( Beolvas10bitADC(temp)-600 )*42/35 + 30;
		//gettemp=Beolvas10bitADC(temp);

		gettemp=Beolvas10bitADC(temp);

	

	//	gettemp/=4;

		gettemp*=125;
		gettemp/=512;

		//most visszaadja a bemenõ fesz értékét

		gettemp*=25;

		// most már ellenállás értéket ad vissza 40mA áramnál

		gettemp/=10;
		gettemp-=209;

			gettemp*=124;
			gettemp/=100;


		LCDClear();

		LCDWriteString("Set");
		LCDWriteIntXY(3,0,settemp,3);
		LCDWriteString("C ");
		
		if(gettemp == 512){
			LCDWriteString("NO IRON");
			}
		else{

			LCDWriteString("Temp");
			LCDWriteIntXY(12,0,gettemp,3);
			LCDWriteString("C");
		}
			

			if(settemp > gettemp+0) on();

			if(settemp <= gettemp) off();



			LCDWriteStringXY(0,1,"");
			//LCDData(255);
			//LCDData(255);

		barlength=settemp/28;

			for(barindex=0;barindex<barlength;barindex++){
			LCDData(255);

			}

			_delay_ms(500);

	}




























	//Simple string printing
	LCDWriteString("Congrats ");
	
	//A string on line 2
	LCDWriteStringXY(0,1,"Loading ");

	//Print some numbers
	for (i=0;i<99;i+=1)
	{
		LCDWriteIntXY(9,1,i,3);
		LCDWriteStringXY(12,1,"%");
		_delay_loop_2(0);	
		_delay_loop_2(0);	
		_delay_loop_2(0);	
		_delay_loop_2(0);	


	}

	//Clear the screen
	LCDClear();

	//Some more text

	LCDWriteString("Hello world");
	LCDWriteStringXY(0,1,"By YourName Here");		// <--- Write ur NAME HERE !!!!!!!!!!!

	//Wait
	for(i=0;i<100;i++) _delay_loop_2(0);

	//Some More ......
	LCDClear();
	LCDWriteString("    eXtreme");
	LCDWriteStringXY(0,1,"  Electronics");

}



