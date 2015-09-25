// Display handler

extern void DisplayInit(void);

//input:BCDnum:BCD2,BCD1,BCD0 in packed format
// DPN: place of dot
//output: DPdata[0-2] 7segment codes of numbers
extern void BCDto7segment(int BCDnum, char DPN);

//dislays the 7segment codes from DPdata[0-2]
extern void Display(void);

// display integer value, valid range:(0-999)
extern void DisplayInteger(unsigned int num, char DPN);

extern void DisplayHex(unsigned int num, char DPN);

// set LED 3-0
extern void LED_SET(char leds);

//set the selected LED
extern void LED_BIT_SET(char bit,char value);


