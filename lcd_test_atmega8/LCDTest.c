#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"

void main()
{
	unsigned char i;

	//Initialize LCD module
	InitLCD(LS_BLINK|LS_ULINE);

	//Clear the screen
	LCDClear();

	_delay_ms(1);


	LCDWriteStringXY(0,0,"");
_delay_ms(1);

	LCDWriteString("12345678");
	_delay_ms(500);
	LCDWriteStringXY(0,1,"Loading123456789");

	while(1);

	//Simple string printing
	LCDWriteString("Congrats");
	_delay_ms(1000);
	
	
	//A string on line 2
	LCDWriteStringXY(0,1,"Loading123456789");
	while(1);

	_delay_ms(1000);

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



