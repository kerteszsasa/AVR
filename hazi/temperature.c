#include "temperature.h"

signed int GetTemp()
{
uint8_t res;   //result
char msb, lsb=0;
signed int temp;

   //Start
   SoftI2CStart();

   //SLA+W
   res=SoftI2CWriteByte( 0b10010000 ); //DS1307 address + W

   //Error
   if(!res) return EE_IO_ERROR;

   //Now send the address of required register
   res=SoftI2CWriteByte(0b00000000);

   //Error
   if(!res) return EE_IO_ERROR;


  //Start
   SoftI2CStart();

   //SLA+W
   res=SoftI2CWriteByte( 0b10010001 ); //DS1307 address + W

   //Error
   if(!res) return EE_IO_ERROR;


	  msb= SoftI2CReadByte(0);
	  lsb=SoftI2CReadByte(1);
	SoftI2CStop();

temp=msb;
temp=temp<<8;
temp+=lsb;
temp=temp>>5;
return temp;

}
