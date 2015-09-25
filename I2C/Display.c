#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <SPI_tools.h>
#include <arit_tools.h>

//LED szegmensek

//   0
// 4   1
//	 5
// 6   2
//   7   3

//                7654 3210 
#define L0 0x28 //0010 1000
#define L1 0xF9 //1111 1001
#define L2 0x1C //0001 1100
#define L3 0x58 //0101 1000
#define L4 0xC9 //1100 1001
#define L5 0x4A //0100 1010
#define L6 0x0A //0000 1010
#define L7 0xF8 //1111 1000
#define L8 0x08 //0000 1000
#define L9 0x48 //0100 1000

#define LA 0x88 //1000 1000
#define LB 0x0B //0000 1011
#define LC 0x2E //0010 1110
#define LD 0x19 //0001 1001
#define LE 0x0E //0000 1110
#define LF 0x8E //1000 1110

#define DP 0xf7 //1111 0111
#define DP_OFF 0xff

#define NCS 0

static const char seg7_table[] PROGMEM = {L0,L1,L2,L3,L4,L5,L6,L7,L8,L9,LA,LB,LC,LD,LE,LF};
static volatile char DPdata[3]; //0,DPdata1,DPdata2;

void DisplayInit(void)
{
	//port irany beallitasok (kimenetek)
	DDRA = DDRA | 0xf1;	//PB1-3 input, CS, LED1-4 out
	SPI_MasterInit();
}

void Display(void)
{
unsigned char dpind;
PORTA = PORTA & ~(1<<NCS);
for (dpind = 0; dpind<3; dpind++)
	{
	SPI_MasterTransmit(DPdata[2-dpind]);
	}
}

//input:BCDnum:BCD2,BCD1,BCD0 in packed format
// DPN: place of dot
//output: DPdata[0-2] 7segment codes of numbers
void BCDto7segment(unsigned int BCDnum, char DPN)
{
char BCDdigit1;
char BCDdigit2;
char BCDdigit3;
char seg7digit;

BCDdigit3 = (BCDnum >> 8) & 0x000f;
if((BCDdigit3 == 0) && (DPN < 3))
{
	seg7digit = DP_OFF;
}
else
{
	seg7digit = pgm_read_byte_near(seg7_table + BCDdigit3);
}
if (DPN == 0x03) {seg7digit = seg7digit & DP;}
DPdata[2] = seg7digit;


BCDdigit2 = (BCDnum >> 4) & 0x000f;
if(((BCDdigit3 | BCDdigit2)==0) && (DPN < 2))
{
	seg7digit = DP_OFF;
}
else
{
	seg7digit = pgm_read_byte_near(seg7_table + BCDdigit2);
}
if (DPN == 0x02) {seg7digit = seg7digit & DP;}
DPdata[1] = seg7digit;

BCDdigit1 = BCDnum & 0x000f;
seg7digit = pgm_read_byte_near(seg7_table + BCDdigit1);
if (DPN == 0x01) {seg7digit = seg7digit & DP;}
DPdata[0] = seg7digit;
}

// display integer value, valid range:(0-999)
void DisplayInteger(unsigned int num, char DPN)
{
unsigned int BCDnum;

	BCDnum = Bin_to_BCD(num);
	BCDto7segment(BCDnum, DPN);
	Display();
}

void DisplayHex(unsigned int num, char DPN)
{
unsigned int BCDnum;

	BCDnum = num;
	BCDto7segment(BCDnum, DPN);
	Display();
}


#define LED_mask 0xf0
void LED_SET(char leds)
{
char PORTAcopy;

PORTAcopy = PORTA & ~LED_mask;
PORTAcopy = PORTAcopy | (leds << 4);
PORTA = PORTAcopy;
}

void LED_BIT_SET(char bit,char value)
{
char LEDcopy;

LEDcopy = PORTA & LED_mask;
if (value == 1)
	{
	LEDcopy = LEDcopy | (1 << (bit + 4));
	}
else
	{
	LEDcopy = LEDcopy & ~(1 << (bit + 4));
	}
PORTA = LEDcopy;
}
