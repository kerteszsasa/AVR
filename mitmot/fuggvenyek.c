#include "mcu_avr_atmega128_api.h" 	// MCU API   
#include "dpy_trm_s01.h"			// DPY API
#include "math.h"					//az sqrt függvény használatához
#include "fuggvenyek.h"

//******** képfrissítés *****************************
void kepfrissites(void)
{									//az állapotnak megfelelõ adat kiírása
	switch(allapot) {				//és led bekapcsolása
		case 0: dpy_trm_s01__7seq_write_number(min,1);
				DPY_TRM_S01__LED_4_OFF();
				DPY_TRM_S01__LED_1_ON();
				break;
		case 1: dpy_trm_s01__7seq_write_number(max,1);
				DPY_TRM_S01__LED_1_OFF();
				DPY_TRM_S01__LED_2_ON();
				break;
		case 2: dpy_trm_s01__7seq_write_number(avg,1);
				DPY_TRM_S01__LED_2_OFF();
				DPY_TRM_S01__LED_3_ON();
				break;
		case 3: dpy_trm_s01__7seq_write_number(szoras,1);
				DPY_TRM_S01__LED_3_OFF();
				DPY_TRM_S01__LED_4_ON();
				break;
	}
}


/********  Timer1 inicializálása  ***************************/
void Timer1_Init(void)
{
   //8000000/256/6250=5 Hz
   TCCR1A=0;									//CTC mode
   TCCR1B=1<<WGM12|1<<CS12;			// Set TIMER0 prescaler to CLK//256      
   TCNT1=0;			                   			//kezdõ érték
   TIMSK=1<<OCIE1A;								// ovf int enable
   OCR1A=6250;	                				//ebben a módban a számláló TOP értéke az OCR1A regiszter tartalma
   												//ha ezt eléri, akkor overflow jelzést kapunk, és nullázza a számlálót
}

//******* 100 elemû cirkuláris puffer*************************
void kiolvas(void)
{
	dpy_trm_s01__Temp_ReadTEMP(&temp_sensor,TMP75_JUMPER_OFF,TMP75_JUMPER_OFF,TMP75_JUMPER_OFF);
	adat[szamlalo]=temp_sensor;
	szamlalo++;
	if(szamlalo==100) szamlalo=0;	//puffer feltöltése
}


//****** output compare interrupt (másodpercenként 5x) ****************
ISR(SIG_OUTPUT_COMPARE1A )
{
	ido++;		//minden 5. kiolvasás után íratom csak ki
	kiolvas(); //másodpercenként 5x kiolvassuk a hõmérséklet értékét
	
}




//**************Szamol***********************
void szamol(void)
{
	min=max=adat[0];
	avg=0;
	szoras=0;

	for(uint8_t i=0;i<100;i++) //elsõ ciklusban az átlag, minimum és maximum meghatározása
		{
			if(min>adat[i]) min=adat[i];
			if(max<adat[i]) max=adat[i];
			avg+=adat[i];
		}

	avg=avg/100;	//átlag

	for(uint8_t i=0;i<100;i++)	//szórás meghatározása (ehhez szükség van az átlagra)
		{
			szoras+=(adat[i]-avg)*(adat[i]-avg);
		}

		szoras=sqrt(szoras/100); //szórás
}


