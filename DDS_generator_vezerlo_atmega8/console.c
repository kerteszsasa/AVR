#include "console.h"
#include "commands.h"
#include "usart.h"

//0=48
//9=57

volatile char resetcounter=0;
volatile char helpcounter=0;
volatile char mincounter=0;
volatile char maxcounter=0;
volatile char freqcounter=0;
volatile char xxxcounter=0;

volatile char temp_egyes=0;
volatile char temp_tizes=0;
volatile char temp_szazas=0;

char *numbers[16];



void InitMessage(){
		putstring("DDS generator driver v_");
		putnum(10);
		USART_Transmit(  '\n' );
		USART_Transmit(  '\r' );
		putstring("Type help for command list");
		USART_Transmit(  '\n' );
		USART_Transmit(  '\r' );
}

void Console_help( char ch){

    switch (helpcounter) {
    case 0: if (ch=='h') helpcounter++; else helpcounter=0; break;
    case 1: if (ch=='e') helpcounter++; else helpcounter=0; break;
    case 2: if (ch=='l') helpcounter++; else helpcounter=0; break;
    case 3: if (ch=='p') helpcounter++; else helpcounter=0; break;
  
    }

	if (helpcounter ==4){
		putstring("help reset minXXX maxXXX freqXXXXXXXX");
		USART_Transmit(  '\n' );
		USART_Transmit(  '\r' );
		helpcounter=0;
	}

}

void Console_reset( char ch){

    switch (resetcounter) {
    case 0: if (ch=='r') resetcounter++; else resetcounter=0; break;
    case 1: if (ch=='e') resetcounter++; else resetcounter=0; break;
    case 2: if (ch=='s') resetcounter++; else resetcounter=0; break;
    case 3: if (ch=='e') resetcounter++; else resetcounter=0; break;
    case 4: if (ch=='t') resetcounter++; else resetcounter=0; break;
    }

	if (resetcounter ==5){
		DDS_reset();
		putstring("reset jott ");
		resetcounter=0;
	}

}

void Console_SetMin( char ch){

    switch (mincounter) {
    case 0: if (ch=='m') mincounter++; else mincounter=0; break;
    case 1: if (ch=='i') mincounter++; else mincounter=0; break;
    case 2: if (ch=='n') mincounter++; else mincounter=0; break;
    case 3: if (ch>47 && ch<58) { mincounter++; temp_szazas= ch-48;; } else mincounter=0; break;
	case 4: if (ch>47 && ch<58) { mincounter++; temp_tizes= ch-48; } else mincounter=0; break;
	case 5: if (ch>47 && ch<58) { mincounter++; temp_egyes= ch-48; } else mincounter=0; break;
    }

	if (mincounter ==6){
		putstring("min jott ");
		putnum(100*temp_szazas + 10*temp_tizes + temp_egyes);
		mincounter=0;
	}

}

void Console_SetMax( char ch){

    switch (maxcounter) {
    case 0: if (ch=='m') maxcounter++; else maxcounter=0; break;
    case 1: if (ch=='a') maxcounter++; else maxcounter=0; break;
    case 2: if (ch=='x') maxcounter++; else maxcounter=0; break;
    case 3: if (ch>47 && ch<58) { maxcounter++; temp_szazas= ch-48; } else maxcounter=0; break;
	case 4: if (ch>47 && ch<58) { maxcounter++; temp_tizes= ch-48; } else maxcounter=0; break;
	case 5: if (ch>47 && ch<58) { maxcounter++; temp_egyes= ch-48; } else maxcounter=0; break;
    }

	if (maxcounter ==6){
		putstring("max jott ");
		putnum(100*temp_szazas + 10*temp_tizes + temp_egyes);
		maxcounter=0;
	}

}

void Console_SetFreq( char ch){

    switch (freqcounter) {
    case 0: if (ch=='f') freqcounter++; else freqcounter=0; break;
    case 1: if (ch=='r') freqcounter++; else freqcounter=0; break;
    case 2: if (ch=='e') freqcounter++; else freqcounter=0; break;
	case 3: if (ch=='q') freqcounter++; else freqcounter=0; break;
    case 4: if (ch>47 && ch<58) { freqcounter++; numbers[0]= ch-48; } else freqcounter=0; break;
	case 5: if (ch>47 && ch<58) { freqcounter++; numbers[1]= ch-48; } else freqcounter=0; break;
	case 6: if (ch>47 && ch<58) { freqcounter++; numbers[2]= ch-48; } else freqcounter=0; break;
	case 7: if (ch>47 && ch<58) { freqcounter++; numbers[3]= ch-48; } else freqcounter=0; break;
	case 8: if (ch>47 && ch<58) { freqcounter++; numbers[4]= ch-48; } else freqcounter=0; break;
	case 9: if (ch>47 && ch<58) { freqcounter++; numbers[5]= ch-48; } else freqcounter=0; break;
	case 10: if (ch>47 && ch<58) { freqcounter++; numbers[6]= ch-48; } else freqcounter=0; break;
	case 11: if (ch>47 && ch<58) { freqcounter++; numbers[7]= ch-48; } else freqcounter=0; break;
    }

	if (freqcounter ==12){
		putstring("freq jott ");
		DDS_SetFreq(numbers);
		freqcounter=0;
	}

}

//just for test
void Console_xxx( char ch){

    switch (xxxcounter) {
    case 0: if (ch=='x') xxxcounter++; else xxxcounter=0; break;
    case 1: if (ch=='x') xxxcounter++; else xxxcounter=0; break;
    case 2: if (ch=='x') xxxcounter++; else xxxcounter=0; break;

    }

	if (xxxcounter ==3){
		putstring("xxx jott ");
		//DDS_reset();

		//EncoderDown();

		//LEFT_btn()	;

		RIGHT_btn();

		
		xxxcounter=0;
	}

}


//****************************************************************************************************
void Incoming_char(char c){

		Console_reset(c);
		Console_help(c);
		Console_SetMin(c);
		Console_SetMax(c);
		Console_SetFreq(c);
		
		Console_xxx(c);

	
}
