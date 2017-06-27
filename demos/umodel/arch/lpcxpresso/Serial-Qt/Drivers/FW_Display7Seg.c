/**
 	\file FW_Display.c
 	\brief Drivers de displays de 7 segmentos
 	\details Expansiones 2 y 3
 	\author Pablo Irrera Condines
 	\date 2013.05.08
*/

#include "KitInfo2_expansiones.h"
#include "UtilesInfo2.h"
#include "FW_Display7Seg.h"

// Buffer de display
volatile uint8_t Digitos[DIGITOS];

#ifdef KITINFOII_EXPANSION2

// 	Tabla de conversion bcd a 7 segmentos
//	Codigo bcd		a	b	c	d	e	f	g   dp
//	0				1	1	1	1	1	1	0   0
//	1				0	1	1	0	0	0	0
// 	2				1	1	0	1	1	0	1
// 	3				1	1	1	1	0	0	1
// 	4				0	1	1	0	0	1	1
//	5				1	0	1	1	0	1	1
//	6				1	0	1	1	1	1	1
//	7				1	1	1	0	0	0	0
// 	8				1	1	1	1	1	1	1
//	9				1	1	1	0	0	1	1
const uint8_t tabla_BCD_7seg[10] = { 0x3f, 0x06, 0x5B, 0x4f, 0x66, 0x6D, 0x7D, 0x07, 0x7f, 0x67};

void EX2_BarridoDisplay( void )
{
	uint8_t aux;
	static uint8_t	digito = 0;

	SetPIN(EX2_DIGITO0,OFF);
	SetPIN(EX2_DIGITO1,OFF);
	SetPIN(EX2_DIGITO2,OFF);
	SetPIN(EX2_DIGITO3,OFF);
	SetPIN(EX2_DIGITO4,OFF);
	SetPIN(EX2_DIGITO5,OFF);

	aux = tabla_BCD_7seg[ Digitos[digito] ];

	SetPIN(EX2_A,(aux & (uint8_t)0x01));
	SetPIN(EX2_B,((aux >> 1) & (uint8_t)0x01));
	SetPIN(EX2_C,((aux >> 2) & (uint8_t)0x01));
	SetPIN(EX2_D,((aux >> 3) & (uint8_t)0x01));
	SetPIN(EX2_E,((aux >> 4) & (uint8_t)0x01));
	SetPIN(EX2_F,((aux >> 5) & (uint8_t)0x01));
	SetPIN(EX2_G,((aux >> 6) & (uint8_t)0x01));
	SetPIN(EX2_DP,((aux >> 7) & (uint8_t)0x01));

	switch( digito )
	{
		case 0:
			SetPIN(EX2_DIGITO0,ON); break;
		case 1:
			SetPIN(EX2_DIGITO1,ON); break;
		case 2:
			SetPIN(EX2_DIGITO2,ON); break;
		case 3:
			SetPIN(EX2_DIGITO3,ON); break;
		case 4:
			SetPIN(EX2_DIGITO4,ON); break;
		case 5:
			SetPIN(EX2_DIGITO5,ON); break;
	}

	// Incremento el indice del display
	digito++;
	digito %= DIGITOS;
}

#elif defined KITINFOII_EXPANSION3

void EX3_BarridoDisplay( void )
{
	uint8_t aux ;
	static uint8_t	digito = 0 ;

	SetPIN(EX3_BCDA, ON);
	SetPIN(EX3_BCDB, ON);
	SetPIN(EX3_BCDC, ON);
	SetPIN(EX3_BCDD, ON);
	SetPIN(EX3_DP, OFF);

	if( !digito )
	{
		SetPIN(EX3_RST,ON);
		SetPIN(EX3_RST,OFF);
	}
	else
	{
		SetPIN(EX3_CLK,OFF);
		SetPIN(EX3_CLK,ON);
	}
 	aux = Digitos[digito] ;

 	SetPIN(EX3_BCDA, (aux >> 0) & 0x01);
 	SetPIN(EX3_BCDB, (aux >> 1) & 0x01);
 	SetPIN(EX3_BCDC, (aux >> 2) & 0x01);
 	SetPIN(EX3_BCDD, (aux >> 3) & 0x01);

	// Incremento el indice del display
	digito++;
	digito %= DIGITOS;
}

#endif
