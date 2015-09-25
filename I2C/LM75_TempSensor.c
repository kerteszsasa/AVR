// LM75 teperature sensor handling routines

#include <I2C_tools.h>
#include <arit_tools.h>

// get temperature from sensor
signed int Temperature(void)
{
unsigned char temph;
unsigned char templ;
unsigned int tempi;
int temp;
float tempf;

StartCond();
TWI_DATA_WRITE(SLA_R);
temph = TWI_DATA_READ(1);
templ = TWI_DATA_READ(0);
StopCond();
tempi = (temph << 8) + templ;

temp = (signed int)(((unsigned int)temph<<8) | ((unsigned int)templ));
tempf = (float)temp*10/256;
temp = (int)tempf;
return(temp);
}





