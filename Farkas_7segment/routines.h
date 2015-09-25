#include <avr/io.h>
#include <avr/interrupt.h>	
#include <util/delay.h>




#define SEVEN_SEGMENT_PORT PORTB

#define DISPTIME 40	//Set the time of a visible number. Value between : 0-255



void SevenSegment(uint8_t n,uint8_t dp);	//Displays one digit, and set the dot point. 0=< n >=9 NOTE: you must set the digit where you want to put the nuumber

void DispNum(uint8_t num,uint8_t dp,uint8_t time); 	//Displays a whole number ( 000 - 255), arguments: number, locatoin of dot point, display time

void Current (int current);	//Display an integer, than put a "A" sign

void Voltage(int voltage);	//Display an integer, than put a "V" sign


void Konfig10bitADC()  ;      // ADC konfiguralas (beallitas)

unsigned int Beolvas10bitADC(unsigned char csatorna);



