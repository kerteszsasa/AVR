#define F_CPU 1000000UL  /* 1 MHz CPU clock */

#include <util/delay.h>
#include <avr/io.h>

int
main (void)
{
        DDRD = 255;               /* PC0 is digital output */
         
        while (1)                       /* loop forever */
        {

		if(comp())PORTD=255; 
		else PORTD=0;


		/*
               // set PC0 on PORTC (digital high) and delay for 500mS 
                PORTD=255;                
                _delay_ms(5);
                
                //  PC0 on PORTC (digital 0) and delay for 500mS 
                PORTD=0;
                _delay_ms(50);

				*/
        }

        return (0);
}


int comp(void)
{
	DIDR=3; //digital io disable for ANI1 and ANI0
	ACSR=0; //start comparator
	if(ACSR&0b00010000)return(ACSR&0b00100000); //if finished comp, return with result whitch is 1 or 0
// nem törli a flaget, ha kész akkor kell törölni és visszalépni addig egy while ciklusban várni

}
