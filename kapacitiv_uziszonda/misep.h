#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>

void Incoming_char(char c);
void Misep_Send(char from, char to, int type, int* msg, int length);
char Misep_Is_Ready();
char Misep_Get_From();
int Misep_Get_Type();
int Misep_Get_Length();
int* Misep_Get_Data();
void Misep_Data_Processed();
