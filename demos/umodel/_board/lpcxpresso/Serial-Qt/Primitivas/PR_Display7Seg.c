/**
 	\file PR_display7seg.c
 	\brief Primitiva de displays de 7 segmentos
 	\details no convierte a codigo 7 segmentos
 	\author Pablo Irrera Condines
 	\date 2013.05.08
*/

#include "FW_Display7Seg.h"
#include "PR_Display7Seg.h"

void Display (uint16_t valor, uint8_t dsp)
{
	int i;
	uint8_t aux[3];
	for(i=2;i>=0;i--)
	{
		aux[i] = valor % 10 ;
		valor /= 10;
	}

	switch(dsp)
	{
		case DSP0:
			Digitos[0] = aux[0];
			Digitos[1] = aux[1];
			Digitos[2] = aux[2];
			break;
		case DSP1:
			Digitos[3] = aux[0];
			Digitos[4] = aux[1];
			Digitos[5] = aux[2];
			break;
	}
}
