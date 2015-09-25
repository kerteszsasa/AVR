#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>

void Konfig10bitADC();
unsigned int Beolvas10bitADC(unsigned char csatorna);
