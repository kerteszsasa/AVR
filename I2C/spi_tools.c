
#include <avr/io.h>

#define DD_MOSI 2
#define DD_SCK 1
#define DD_SS 0

void SPI_MasterInit(void)
{
/* Set MOSI and SCK output, all others input */
DDRB = (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS);
/* Enable SPI, Master, set clock rate fck/16 */
//SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1)|(1<<SPR0); // fosc/128
SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0); // fosc/16
}

void SPI_MasterTransmit(char cData)
{
/* Start transmission */
SPDR = cData;
/* Wait for transmission complete */
while(!(SPSR & (1<<SPIF)));
}

unsigned char SPI_MasterRW(char cData)
{
SPI_MasterTransmit(cData);
return(SPDR);
}
