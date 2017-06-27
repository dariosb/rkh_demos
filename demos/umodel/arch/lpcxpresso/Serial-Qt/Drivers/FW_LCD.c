/**
 	\file FW_LCD.c
 	\brief Drivers del LCD
 	\details Validos para LCD manjados por 4 bits
 	\author Pablo Irrera Condines
 	\date 2013.08.05
*/

#include "KitInfo2.h"
#include "UtilesInfo2.h"
#include "FW_LCD.h"
#include "PR_LCD.h"

volatile uint8_t Buffer_LCD[LCDBUFFER_SIZE];
volatile uint32_t inxInLCD;
volatile uint32_t inxOutLCD;
volatile uint32_t cantidadColaLCD;
volatile uint32_t Demora_LCD;

void InitLCD(void)
{
	SetPINSEL(P0,5,PINSEL_GPIO);	//LCD_D4
	SetPINSEL(P0,10,PINSEL_GPIO);	//LCD_D5
	SetPINSEL(P2,4,PINSEL_GPIO);	//LCD_D6
	SetPINSEL(P2,5,PINSEL_GPIO);	//LCD_D7
	SetPINSEL(P2,6,PINSEL_GPIO);	//LCD_RS
	SetPINSEL(P0,4,PINSEL_GPIO);	//LCD_E

	SetDIR(LCD_D4, SALIDA);
	SetDIR(LCD_D5, SALIDA);
	SetDIR(LCD_D6, SALIDA);
	SetDIR(LCD_D7, SALIDA);
	SetDIR(LCD_RS, SALIDA);
	SetDIR(LCD_E, SALIDA);

	SetPIN(LCD_D4,OFF);
	SetPIN(LCD_D5,OFF);
	SetPIN(LCD_D6,OFF);
	SetPIN(LCD_D7,OFF);
	SetPIN(LCD_E,OFF);
	SetPIN(LCD_RS,OFF);

	ConfigLCD();
}

void ConfigLCD(void)
{
	uint8_t i;

	SetPIN(LCD_E,OFF);
	Demora_LCD = 10;			// Demora inicial
	while (Demora_LCD);

	for( i = 0 ; i < 3 ; i++ )
	{
		SetPIN(LCD_D4,ON);			// Configuracion en 8 bits
		SetPIN(LCD_D5,ON);
		SetPIN(LCD_D6,OFF);
		SetPIN(LCD_D7,OFF);

		SetPIN(LCD_RS,OFF);
		SetPIN(LCD_E,ON);
		SetPIN(LCD_E,OFF);
		Demora_LCD = 2;
		while (Demora_LCD);
	}

	// Configuracion en 4 bits
	SetPIN(LCD_D4,OFF);
	SetPIN(LCD_D5,ON);
	SetPIN(LCD_D6,OFF);
	SetPIN(LCD_D7,OFF);

	SetPIN(LCD_RS,OFF);
	SetPIN(LCD_E,ON);
	SetPIN(LCD_E,OFF);

	Demora_LCD = 1;	// Demora inicial
	while (Demora_LCD);

	// A partir de aca el LCD pasa a 4 bits !!!
	PushLCD( 0x28 , LCD_CONTROL );	// DL = 0: 4 bits de datos
									// N = 1 : 2 lineas
									// F = 0 : 5x7 puntos

	PushLCD( 0x08 , LCD_CONTROL);	// D = 0 : display OFF
									// C = 0 : Cursor OFF
									// B = 0 : Blink OFF

	PushLCD( 0x01 , LCD_CONTROL);	// clear display

	PushLCD( 0x06 , LCD_CONTROL);	// I/D = 1 : Incrementa puntero
									// S = 0 : NO Shift Display

	// Activo el LCD y listo para usar !
	PushLCD( 0x0C , LCD_CONTROL);	// D = 1 : display ON
									// C = 0 : Cursor OFF
									// B = 0 : Blink OFF
}

unsigned char PushLCD ( uint8_t dato , uint8_t control )
{
	if (cantidadColaLCD >= LCDBUFFER_SIZE )
		return -1;

	Buffer_LCD [ inxInLCD ] = ( dato >> 4 ) & 0x0f;
	if ( control == LCD_CONTROL )
		Buffer_LCD [ inxInLCD ] |= 0x80;

	inxInLCD ++;

	Buffer_LCD [ inxInLCD ] = dato & 0x0f;
	if ( control == LCD_CONTROL )
		Buffer_LCD [ inxInLCD ] |= 0x80;

	cantidadColaLCD += 2;

	inxInLCD ++;
	inxInLCD %= LCDBUFFER_SIZE;

	return 0;
}

int PopLCD (void)
{
	char dato;

	if ( cantidadColaLCD == 0 )
		return -1;

	dato = Buffer_LCD [ inxOutLCD ] ;

	cantidadColaLCD --;

	inxOutLCD ++;
	inxOutLCD %= LCDBUFFER_SIZE;

	return dato;
}

void Dato_LCD(void)
{
	int data;

	if ( (data = PopLCD ()) == -1 )
		return;

	SetPIN(LCD_D7,((uint8_t)data) >> 3 & 0x01);
	SetPIN(LCD_D6,((uint8_t)data) >> 2 & 0x01);
	SetPIN(LCD_D5,((uint8_t)data) >> 1 & 0x01);
	SetPIN(LCD_D4,((uint8_t)data) >> 0 & 0x01);

	if( ((uint8_t) data ) & 0x80 )
		SetPIN(LCD_RS,OFF);
	else
		SetPIN(LCD_RS,ON);

	SetPIN(LCD_E,ON);
	SetPIN(LCD_E,OFF);
}
