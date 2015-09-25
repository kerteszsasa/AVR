#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>



#define RESET_btn() 	PORTB&=~(0b00000001);_delay_ms(200);PORTB|=(0b00000001);_delay_ms(200)
#define LEFT_btn()		PORTB&=~(0b00000010);_delay_ms(200);PORTB|=(0b00000010);_delay_ms(200)
#define RIGHT_btn()		PORTD&=~(0b00001000);_delay_ms(200);PORTD|=(0b00001000);_delay_ms(200)
#define SELECT_btn()	PORTD&=~(0b00010000);_delay_ms(200);PORTD|=(0b00010000);_delay_ms(200)
#define OK_btn()		PORTD&=~(0b00100000);_delay_ms(200);PORTD|=(0b00100000);_delay_ms(200) //?????? not tested yet


#define LED_ON()		PORTB|=(0b00000100)
#define LED_OFF()		PORTB&=~(0b00000100)

#define BEEP()			PORTC|=(0b00000001);_delay_ms(1000);PORTC&=~(0b00000001)




void DDS_reset(void);

void DDS_SetFreq(char* numbers);

void EncoderUp(void);

void EncoderDown(void);
