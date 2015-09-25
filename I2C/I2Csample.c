#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <I2C_tools.h>
#include <arit_tools.h>
#include <Display.h>
#include <general.h>
#include <LM75_Tempsensor.h>

int main()
{
unsigned int temp;
	DisplayInit();
	TWI_Init();

	do{
		temp = Temperature();
		DisplayInteger(temp,2);
		SWDelay(20000);
	}while(1);
}
