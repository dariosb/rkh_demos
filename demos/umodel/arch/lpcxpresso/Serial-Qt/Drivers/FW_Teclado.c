/**
 	\file FW_Teclado.c
 	\brief Drivers de teclado
 	\details Expansiones 3 y 4
 	\author Pablo Irrera Condines
 	\date 2013.05.08
*/

#include "KitInfo2_Expansiones.h"
#include "FW_Teclado.h"
#include "PR_Teclado.h"

// Buffer de teclado matricial
volatile uint8_t Teclado_Key = NO_KEY;

void DriverTecladoSW (uint8_t codigoActual)
{
	static uint8_t codigoAnterior = NO_KEY;
	static uint8_t estadosEstables;

	if( codigoActual == NO_KEY )
	{
		codigoAnterior = NO_KEY;
		estadosEstables = 0;
		return;
	}

	if( estadosEstables == 0  )
	{
		codigoAnterior = codigoActual;
		estadosEstables = 1;
		return;
	}

	if( codigoActual != codigoAnterior )
	{
		codigoAnterior = NO_KEY;
		estadosEstables = 0;
		return;
	}

	if( estadosEstables == REBOTES )
	{
		Teclado_Key = codigoActual;
		estadosEstables++;
		return;
	}

	if( estadosEstables == REBOTES + 1)
		return;

	estadosEstables++;

	return;
}

#ifdef	KITINFOII_EXPANSION3

void EX3_DriverTeclado(void)
{
	uint8_t codigoActual;
	codigoActual = EX3_DriverTecladoHW();

	DriverTecladoSW(codigoActual);
}

uint8_t EX3_DriverTecladoHW(void)
{
	uint8_t codigo = NO_KEY;

	SetPIN(EX3_COL0, OFF);
	SetPIN(EX3_COL1, ON);

	if ( GetPIN(EX3_FILA0) == OFF )
		codigo = 0;

	if ( GetPIN(EX3_FILA1) == OFF )
		codigo = 1;

	if ( GetPIN(EX3_FILA2) == OFF )
		codigo = 2;

	if ( GetPIN(EX3_FILA3) == OFF )
		codigo = 3;

	SetPIN(EX3_COL0, ON);
	SetPIN(EX3_COL1, OFF);

	if ( GetPIN(EX3_FILA0) == OFF )
		codigo = 7;

	if ( GetPIN(EX3_FILA1) == OFF )
		codigo = 6;

	if ( GetPIN(EX3_FILA2) == OFF )
		codigo = 5;

	if ( GetPIN(EX3_FILA3) == OFF )
		codigo = 4;

	SetPIN(EX3_COL0, ON);
	SetPIN(EX3_COL1, ON);

	return codigo;
}

#elif defined KITINFOII_EXPANSION4

void EX4_DriverTeclado(void)
{
	uint8_t codigoActual;
	codigoActual = EX4_DriverTecladoHW();

	DriverTecladoSW(codigoActual);
}

uint8_t EX4_DriverTecladoHW(void)
{
	uint8_t codigo = NO_KEY;

	SetPIN(EX4_COL0, OFF);
	SetPIN(EX4_COL1, ON);
	SetPIN(EX4_COL2, ON);

	if ( GetPIN(EX4_FILA0) == OFF )
		codigo = 0;

	if ( GetPIN(EX4_FILA1) == OFF )
		codigo = 1;

	if ( GetPIN(EX4_FILA2) == OFF )
		codigo = 2;

	SetPIN(EX4_COL0, ON);
	SetPIN(EX4_COL1, OFF);
	SetPIN(EX4_COL2, ON);

	if ( GetPIN(EX4_FILA0) == OFF )
		codigo = 3;

	if ( GetPIN(EX4_FILA1) == OFF )
		codigo = 4;

	if ( GetPIN(EX4_FILA2) == OFF )
		codigo = 5;

	SetPIN(EX4_COL0, ON);
	SetPIN(EX4_COL1, ON);
	SetPIN(EX4_COL2, OFF);

	if ( GetPIN(EX4_FILA0) == OFF )
		codigo = 6;

	if ( GetPIN(EX4_FILA1) == OFF )
		codigo = 7;

	if ( GetPIN(EX4_FILA2) == OFF )
		codigo = 8;

	SetPIN(EX4_COL0, ON);
	SetPIN(EX4_COL1, ON);
	SetPIN(EX4_COL2, ON);

	return codigo;
}

#endif


