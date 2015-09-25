//I2C functions:
#include <avr/io.h>

void TWI_Init(void)
{
// set bit rate to 100kHz
TWBR = 64; 
TWSR = 0;
TWDR = 0xff;
TWCR = 1<<TWEN;
}


void StartCond(void)
{
unsigned char tmp;
TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA) ; // start condition
do
	{
	tmp = TWCR & (1<<TWINT);
	}
while(tmp==0);
}

void StopCond(void)
{
TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO); 
}

void TWI_DATA_WRITE(unsigned char data)
{
unsigned char tmp;
TWDR = data;
TWCR = (1<<TWINT)|(1<<TWEN);
do
	{
	tmp = TWCR & (1<<TWINT);
	}
while(tmp==0);
}

unsigned char TWI_DATA_READ(char ack)
{
unsigned char d,tmp;
if (ack)
	{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	}
else
	{
	TWCR = (1<<TWINT) | (1<<TWEN);
	}
do
	{
	tmp = TWCR & (1<<TWINT);
	}
while(tmp==0);	

d = TWDR;
return(d);
}
