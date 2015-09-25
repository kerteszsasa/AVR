#include <avr/io.h>
#include <avr/interrupt.h>	
#include <util/delay.h>
#include "i2csoft.h"

char Setpot (char value);

void Konfig8bitADC();

unsigned char Beolvas8bitADC(unsigned char csatorna);
