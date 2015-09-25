#ifndef __FOO
#define __FOO

#include "mcu_avr_atmega128_api.h" 	// MCU API
 
extern volatile float			temp_sensor, avg, min, max;
extern volatile double szoras;				// azért double, mert az sqrt függvény double változót vár
extern volatile float adat[100];			//puffer adatok
extern volatile uint8_t szamlalo;		//puffer számlálója
extern volatile unsigned int but;			//pergésmentesítéshez
extern volatile unsigned char ido;			// az 1s kiszámolásához kell 
extern volatile unsigned char allapot; //0 - min
								//1 - max
								//2 - avg
								//3 - szórás

/*
  volatile float			temp_sensor, avg, min, max;
  volatile double szoras;				// azért double, mert az sqrt függvény double változót vár
  volatile float adat[100];			//puffer adatok
  volatile uint8_t szamlalo=0;		//puffer számlálója
  volatile unsigned int but;			//pergésmentesítéshez
  volatile unsigned char ido;			// az 1s kiszámolásához kell 
  volatile unsigned char allapot; //0 - min
								//1 - max
								//2 - avg
								//3 - szórás
*/

//******** képfrissítés *****************************
void kepfrissites(void);

/********  Timer1 inicializálása  ***************************/
void Timer1_Init(void);

//******* 100 elemû cirkuláris puffer*************************
void kiolvas(void);

//****** output compare interrupt (másodpercenként 5x) ****************
//ISR(SIG_OUTPUT_COMPARE1A );

//**************Szamol***********************
void szamol(void);

#endif // __FOO

