#include "fuggvenyek.h"
#include "mcu_avr_atmega128_api.h" 	// MCU API   
#include "dpy_trm_s01.h"			// DPY API


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

//********  main program  ***************************
int main (void)
{
	dpy_trm_s01__Init();		// DPY k�rtya init
	Timer1_Init();			// Timer1 init
	dpy_trm_s01__Temp_Init(TMP75_JUMPER_OFF,TMP75_JUMPER_OFF,TMP75_JUMPER_OFF);	//h�m�rs�kletszenzor init

	//*** system led
	SYS_LED_DIR_OUTPUT();
	SYS_LED_ON();

	sei();					// enable interrupts

	//*** 0. �llapot felt�telei
	allapot=0;
	DPY_TRM_S01__LED_1_ON();

	//*** kezdeti felt�telek
	ido=0;
	but=0;


	//*** f�ciklus
	while(1)
	{

		//*** gombnyom�s figyel�se
		if(!DPY_TRM_S01__BUTTON_1_GET_STATE() & !but)
		{
			allapot++;
			if(allapot==4) allapot=0;
			kepfrissites();
			but=1;
		}

		// perg�smentes�t�s
		if(DPY_TRM_S01__BUTTON_1_GET_STATE() && but) but++;
		if(but==2000) but=0;


		// m�sodpercenk�nti adat- �s k�pfriss�t�s
		if(ido==5)
			{
			szamol();
			kepfrissites();
			ido=0;
			}
	}//while
    
}//main
