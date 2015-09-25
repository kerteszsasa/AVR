/**********************************************************

Software I2C Library for AVR Devices.

Copyright 2008-2012
eXtreme Electronics, India
www.eXtremeElectronics.co.in
**********************************************************/
 
#include <avr/io.h>
#include <util/delay.h>

#include "i2csoft.h"

#define Q_DEL _delay_loop_2(3)
#define H_DEL _delay_loop_2(5)

void SoftI2CInit()
{
	SDAPORT&=(1<<SDA);
	SCLPORT&=(1<<SCL);
	
	SOFT_I2C_SDA_HIGH;	
	SOFT_I2C_SCL_HIGH;	
		
}
void SoftI2CStart()
{
	SOFT_I2C_SCL_HIGH;
	H_DEL;
	
	SOFT_I2C_SDA_LOW;	
	H_DEL;  	
}

void SoftI2CStop()
{
	 SOFT_I2C_SDA_LOW;
	 H_DEL;
	 SOFT_I2C_SCL_HIGH;
	 Q_DEL;
	 SOFT_I2C_SDA_HIGH;
	 H_DEL;
}

uint8_t SoftI2CWriteByte(uint8_t data)
{
	 
	 uint8_t i;
	 	
	 for(i=0;i<8;i++)
	 {
		SOFT_I2C_SCL_LOW;
		Q_DEL;
		
		if(data & 0x80)
			SOFT_I2C_SDA_HIGH;
		else
			SOFT_I2C_SDA_LOW;	
		
		H_DEL;
		
		SOFT_I2C_SCL_HIGH;
		H_DEL;
		
		while((SCLPIN & (1<<SCL))==0);
			
		data=data<<1;
	}
	 
	//The 9th clock (ACK Phase)
	SOFT_I2C_SCL_LOW;
	Q_DEL;
		
	SOFT_I2C_SDA_HIGH;		
	H_DEL;
		
	SOFT_I2C_SCL_HIGH;
	H_DEL;	
	
	uint8_t ack=!(SDAPIN & (1<<SDA));
	
	SOFT_I2C_SCL_LOW;
	H_DEL;
	
	return ack;
	 
}
 
 
uint8_t SoftI2CReadByte(uint8_t ack)
{
	uint8_t data=0x00;
	uint8_t i;
			
	for(i=0;i<8;i++)
	{
			
		SOFT_I2C_SCL_LOW;
		H_DEL;
		SOFT_I2C_SCL_HIGH;
		H_DEL;
			
		while((SCLPIN & (1<<SCL))==0);
		
		if(SDAPIN &(1<<SDA))
			data|=(0x80>>i);
			
	}
		
	SOFT_I2C_SCL_LOW;
	Q_DEL;						//Soft_I2C_Put_Ack
	
	if(ack)
	{
		SOFT_I2C_SDA_LOW;	
	}
	else
	{
		SOFT_I2C_SDA_HIGH;
	}	
	H_DEL;
	
	SOFT_I2C_SCL_HIGH;
	H_DEL;
	
	SOFT_I2C_SCL_LOW;
	H_DEL;
			
	return data;
	
}


/////my fv********************************************************

//**// 2 byte address
uint8_t EEWriteByte(uint8_t base, uint16_t address,uint8_t data)
{
   SoftI2CStart();


   //SLA+W
   if(!SoftI2CWriteByte(   base&=~1  ))
   {
      SoftI2CStop();

      //I2C i/o error

      return EE_IO_ERROR;
   }

   //Address HIGH
   if(!SoftI2CWriteByte(address>>8))
   {
      SoftI2CStop();

      //I2C i/o error
      return EE_IO_ERROR;
   }

   //Address LOW

   if(!SoftI2CWriteByte(address))
   {
      SoftI2CStop();

      //I2C i/o error
      return EE_IO_ERROR;
   }

   //Data
   if(!SoftI2CWriteByte(data))
   {
      SoftI2CStop();

      //I2C i/o error
      return EE_IO_ERROR;
   }

   SoftI2CStop();

   _delay_ms(5);

   return EE_SUCCESS;
}
/******************************************************/

uint8_t EEReadByte(uint8_t base, uint16_t address,uint8_t *data)
{

   SoftI2CStart();

   //SLA+W

   if(!SoftI2CWriteByte(    base&=~1    ))
   {
      SoftI2CStop();

      //I2C i/o error
      return EE_IO_ERROR;
   }

   //Address HIGH
   if(!SoftI2CWriteByte(address>>8))
   {
      SoftI2CStop();

      //I2C i/o error

      return EE_IO_ERROR;
   }
   //Address LOW     
   if(!SoftI2CWriteByte(address))
   {
      SoftI2CStop();

      //I2C i/o error
      return EE_IO_ERROR;
   }

   //Repeat Start

   SoftI2CStart();

   //SLA+R
   if(!SoftI2CWriteByte(  base|=1 ))
   {
      SoftI2CStop();

      //I2C i/o error
      return EE_IO_ERROR;
   }

   //Read + NAK   
   *data=SoftI2CReadByte(0);

   SoftI2CStop();

   return EE_SUCCESS;
}





//****************************************/
//**/ 1 byte address

/***************************************************


***************************************************/

char I2CRead(uint8_t base, uint8_t address,uint8_t *data)
{
   uint8_t res;   //result

   //Start

   SoftI2CStart();

   //SLA+W (for dummy write to set register pointer)
   res=SoftI2CWriteByte( base&=~1 ); //DS1307 address + W

   //Error
   if(!res) return EE_IO_ERROR;

   //Now send the address of required register

   res=SoftI2CWriteByte(address);

   //Error
   if(!res) return EE_IO_ERROR;

   //Repeat Start
   SoftI2CStart();

   //SLA + R
   res=SoftI2CWriteByte( base|=1 ); //DS1307 Address + R

   //Error
   if(!res) return EE_IO_ERROR;

   //Now read the value with NACK
   *data=SoftI2CReadByte(0);

   //Error

   if(!res) return EE_IO_ERROR;

   //STOP
   SoftI2CStop();

   return EE_SUCCESS;
}


//***************************************************/

char I2CWrite(uint8_t base, uint8_t address,uint8_t data)
{
   uint8_t res;   //result

   //Start
   SoftI2CStart();

   //SLA+W
   res=SoftI2CWriteByte( base&=~1 ); //DS1307 address + W

   //Error
   if(!res) return EE_IO_ERROR;

   //Now send the address of required register
   res=SoftI2CWriteByte(address);

   //Error
   if(!res) return EE_IO_ERROR;

   //Now write the value

   res=SoftI2CWriteByte(data);

   //Error
   if(!res) return EE_IO_ERROR;

   //STOP
   SoftI2CStop();

   return EE_SUCCESS;
}







