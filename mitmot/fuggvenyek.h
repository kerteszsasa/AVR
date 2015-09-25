#ifndef __FOO
#define __FOO

#include "mcu_avr_atmega128_api.h" 	// MCU API
 
extern volatile float			temp_sensor, avg, min, max;
extern volatile double szoras;				// az�rt double, mert az sqrt f�ggv�ny double v�ltoz�t v�r
extern volatile float adat[100];			//puffer adatok
extern volatile uint8_t szamlalo;		//puffer sz�ml�l�ja
extern volatile unsigned int but;			//perg�smentes�t�shez
extern volatile unsigned char ido;			// az 1s kisz�mol�s�hoz kell 
extern volatile unsigned char allapot; //0 - min
								//1 - max
								//2 - avg
								//3 - sz�r�s

/*
  volatile float			temp_sensor, avg, min, max;
  volatile double szoras;				// az�rt double, mert az sqrt f�ggv�ny double v�ltoz�t v�r
  volatile float adat[100];			//puffer adatok
  volatile uint8_t szamlalo=0;		//puffer sz�ml�l�ja
  volatile unsigned int but;			//perg�smentes�t�shez
  volatile unsigned char ido;			// az 1s kisz�mol�s�hoz kell 
  volatile unsigned char allapot; //0 - min
								//1 - max
								//2 - avg
								//3 - sz�r�s
*/

//******** k�pfriss�t�s *****************************
void kepfrissites(void);

/********  Timer1 inicializ�l�sa  ***************************/
void Timer1_Init(void);

//******* 100 elem� cirkul�ris puffer*************************
void kiolvas(void);

//****** output compare interrupt (m�sodpercenk�nt 5x) ****************
//ISR(SIG_OUTPUT_COMPARE1A );

//**************Szamol***********************
void szamol(void);

#endif // __FOO

