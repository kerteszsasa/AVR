#include "misep.h"
#include "usart.h"

//TODO
void Misep_Send(char from, char to, int type, int* msg, int length){
	
	uint8_t crc = 0;

	USART_Transmit(255);	//START
	USART_Transmit(255);	//START
	USART_Transmit(from);	//FROM
	USART_Transmit(to);		//TO
	USART_Transmit(type & 255);			//TYPE
	USART_Transmit((type>>8) & 255);	//TYPE
	USART_Transmit(length & 255);		//LENGTH
	USART_Transmit((length>>8) & 255);	//LENGTH

	crc =255 + 255 + from + to + (type & 255) + ((type>>8) & 255) + (length & 255) + ((length>>8) & 255);
	USART_Transmit(crc);	//HEADER CRC

	//DATA
	crc = 0;
	for(int i=0; i< length; i++){
		USART_Transmit(msg[i]);
		crc += msg[i];
		}
	
	USART_Transmit(crc);	//DATA CRC

}




int* data[255];
char state = 0;
uint8_t crc = 0;
uint8_t data_ready=0;
int data_counter =0;

int FROM, TO, TYPE, LENGTH;


//****************************************************************************************************
void Incoming_char(char c){

//	if (data_ready ==1){
//		PORTD=0b00001000;
//		_delay_ms(10);
//	}


if(data_ready ==0){

	switch (state){
		case 0: {
			crc = 0;
			crc += c;
			if (c ==255){
				state++;
				break;
			}
			else state = 0;
			break;
		}
		case 1: {
			crc += c;
					if (c ==255){
				state++;
				break;
			}
			else state = 0;
			break;
		}
		case 2: {
			crc += c;
			FROM=c;
			state++;
			break;
		}
		case 3: {
			crc += c;
			TO=c;
			state++;
			break;
		}
		case 4: {
			crc += c;
			TYPE=c;
			state++;
			break;
		}
		case 5: {
			crc += c;
			TYPE<<8;
			TYPE+=c;
			state++;
			break;
		}
		case 6: {
			crc += c;
			LENGTH=c;
			state++;
			break;
		}
		case 7: {
			crc += c;
			LENGTH<<8;
			LENGTH+=c;
			state++;
			break;
		}
		case 8: {
			if(crc == c){
				state++;
				crc=0;
				data_counter=0;
				break;
				}
			else state = 0;
			break;
		}
		//TODO: process data: eddig jó


		case 9: {

			if(LENGTH > data_counter){
				crc += c;
				data[data_counter]=c;
				data_counter++;
				break;
			}
			else{
				state++;
				data_counter=0;
			}
			//break;
		}

		case 10: {
			if(crc == c){
				state=0;
				crc=0;
				data_ready=1;
				
				}
			else{
				state = 0;
				data_ready=0;
				}
			break;
		}
		//TODO: process data: eddig jó



		//itt varok, hogy valaki feldolgozza az adatot






		/*	case 11: {
			
				if(data_ready == 0)
					state=0;
				break;
			}*/
		
	}//end of switch
  }//end of if


}// end of function 

//****************************************************************************************************
char Misep_Is_Ready(){
	return data_ready;
}

//****************************************************************************************************
char Misep_Get_From(){
	return FROM;
	}

//****************************************************************************************************
int Misep_Get_Type(){
	return TYPE;
	}

//****************************************************************************************************
int Misep_Get_Length(){
	return LENGTH;
	}

//****************************************************************************************************
int* Misep_Get_Data(){
	return data;
	}

//****************************************************************************************************
void Misep_Data_Processed(){
	data_ready = 0;
	}

