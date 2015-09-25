#include "fuggvenyek.h"
#include "mcu_avr_atmega128_api.h" 	// MCU API   
#include "dpy_trm_s01.h"			// DPY API


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

//********  main program  ***************************
int main (void)
{
	dpy_trm_s01__Init();		// DPY kártya init
	Timer1_Init();			// Timer1 init
	dpy_trm_s01__Temp_Init(TMP75_JUMPER_OFF,TMP75_JUMPER_OFF,TMP75_JUMPER_OFF);	//hõmérsékletszenzor init

	//*** system led
	SYS_LED_DIR_OUTPUT();
	SYS_LED_ON();

	sei();					// enable interrupts

	//*** 0. állapot feltételei
	allapot=0;
	DPY_TRM_S01__LED_1_ON();

	//*** kezdeti feltételek
	ido=0;
	but=0;


	//*** fõciklus
	while(1)
	{

		//*** gombnyomás figyelése
		if(!DPY_TRM_S01__BUTTON_1_GET_STATE() & !but)
		{
			allapot++;
			if(allapot==4) allapot=0;
			kepfrissites();
			but=1;
		}

		// pergésmentesítés
		if(DPY_TRM_S01__BUTTON_1_GET_STATE() && but) but++;
		if(but==2000) but=0;


		// másodpercenkénti adat- és képfrissítés
		if(ido==5)
			{
			szamol();
			kepfrissites();
			ido=0;
			}
	}//while
    
}//main
