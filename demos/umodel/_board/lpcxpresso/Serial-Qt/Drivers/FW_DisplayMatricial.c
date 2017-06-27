/**
 	\file FW_Display.c
 	\brief Drivers de display matricial
 	\details Expansion 4
 	\author Pablo Irrera Condines
 	\date 2013.05.08
*/

#include "FW_DisplayMatricial.h"
#include "UtilesInfo2.h"
#include "KitInfo2_Expansiones.h"

struct Matriz EX4_BufferMatriz[EX4_DIGITOS];
volatile uint32_t ticks_matricial;
volatile uint32_t recarga_ticks_matricial;
volatile uint8_t matricial_modo_rotacion;

#ifdef KITINFOII_EXPANSION4

void EX4_BarridoMatriz( void )
{
	static uint32_t fila = 0 ;

	SetPIN(EX4_DSPFILA1, OFF);
	SetPIN(EX4_DSPFILA2, OFF);
	SetPIN(EX4_DSPFILA3, OFF);
	SetPIN(EX4_DSPFILA4, OFF);
	SetPIN(EX4_DSPFILA5, OFF);
	SetPIN(EX4_DSPFILA6, OFF);
	SetPIN(EX4_DSPFILA7, OFF);

	EX4_ShiftDato( fila );

	switch( fila )
	{
		case 0: SetPIN(EX4_DSPFILA1, ON); break;
		case 1: SetPIN(EX4_DSPFILA2, ON); break;
		case 2: SetPIN(EX4_DSPFILA3, ON); break;
		case 3: SetPIN(EX4_DSPFILA4, ON); break;
		case 4: SetPIN(EX4_DSPFILA5, ON); break;
		case 5: SetPIN(EX4_DSPFILA6, ON); break;
		case 6: SetPIN(EX4_DSPFILA7, ON); break;
	}

	fila++;
	fila %= 7;
}

void EX4_ShiftDato( uint8_t fila )
{
	uint32_t i , j;

	for( j = 0 ; j < EX4_DIGITOS ; j++ )
	{
		for( i = 0 ; i < 5 ; i++ )
		{
			SetPIN(EX4_SER, ( EX4_BufferMatriz[ j ].Fila[fila] >> i ) & 0x01);

			SetPIN(EX4_LCLK, ON);
			SetPIN(EX4_LCLK, OFF);
		}
	}

	SetPIN(EX4_SRCLK, ON);
	SetPIN(EX4_SRCLK, OFF);
}

#endif
