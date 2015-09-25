#include <stdlib.h>

// Aritmetical routins

// Binary byte to BCD converter
// input: number (0-255)
/*
unsigned int Bin_to_BCD(unsigned char bin_data)
{
unsigned int BCD;
char l;
char tmp;

BCD = 0x0000;
for (l = 7; l>=0; l--)
	{
	
	BCD = BCD << 1;
	
	if ((bin_data & 0x80) == 0x80)
		{
			BCD = BCD | 0x0001;
		}
	
	bin_data = bin_data << 1;
	
	if (l == 0)
		{
		break;
		}
	
	tmp = BCD & 0x000f;
	if (tmp>4)
		{
			tmp = tmp + 3;
			BCD = (BCD & 0x0ff0) | tmp;
		}

	tmp = (BCD >> 4) & 0x000f;
	if (tmp>4)
		{
			tmp = tmp + 3;
			BCD = (BCD & 0x0f0f) | (tmp << 4);
		}

	tmp = (BCD >> 8) & 0x000f;
	if (tmp>4)
		{
			tmp = tmp + 3;
			BCD = (BCD & 0x00ff) | (tmp << 8);
		}
	}	
	
return (BCD);
}
*/

//convert binary number (0-9999) to packed BCD number
unsigned int Bin_to_BCD(unsigned int val)
{ 
  char BCD_text[6]; // max 5 digits in a 16 bit uint 
  int i,j,k; 
  //char result[5];
  unsigned int result,digit,digitsh;

  utoa(val, BCD_text, 10); //convert integer to string
  i=0; 
  while(BCD_text[i]) // compute the length of the string
  { 				 // the string ended by 0x00 byte
    i++; 
  } 
  
  // convert string to packed BCD number (max:9999)
  result = 0;
  for(j = i-1; j>-1; j--)
  { 
  	k = 4*((i-1)-j);
	digit = BCD_text[j]-'0';
	digitsh = digit << k;
    result = result | digitsh; 
  } 
  return(result); 
} 
