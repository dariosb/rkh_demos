/**
 	\file FW_IO.c
 	\brief Drivers de dispositivos de entrada/salida
 	\details barrido de teclas, entradas y salidas digitales
 	\author Pablo Irrera Condines
 	\date 2013.05.08
*/

#include "FW_IO.h"
#include "PR_IO.h"
#include "UtilesInfo2.h"
#include "KitInfo2.h"

volatile uint8_t BufferLED_Relay;
volatile uint8_t BufferRGB_Buzzer;
volatile uint8_t EntradasDigitales;

// Buffer de teclas
volatile uint32_t Teclas_Key;

void BarridoSalidas (void)
{
	if( BufferLED_Relay & (1 << IO_LED1) )
		SetPIN(LED1, ON);
	else
		SetPIN(LED1, OFF);

	if( BufferLED_Relay & (1 << IO_LED2) )
		SetPIN(LED2, ON);
	else
		SetPIN(LED2, OFF);

	if( BufferLED_Relay & (1 << IO_LED3) )
		SetPIN(LED3, ON);
	else
		SetPIN(LED3, OFF);

	if( BufferLED_Relay & (1 << IO_LED4) )
		SetPIN(LED4, ON);
	else
		SetPIN(LED4, OFF);

	if( BufferRGB_Buzzer & (1 << IO_RGBR) )
		SetPIN(RGBR, ON);
	else
		SetPIN(RGBR, OFF);

	if( BufferRGB_Buzzer & (1 << IO_RGBG) )
		SetPIN(RGBG, ON);
	else
		SetPIN(RGBG, OFF);

	if( BufferRGB_Buzzer & (1 << IO_RGBB) )
		SetPIN(RGBB, ON);
	else
		SetPIN(RGBB, OFF);

	if( BufferRGB_Buzzer & (1 << IO_BUZZER) )
		SetPIN(BUZZ, BUZZ_ON);
	else
		SetPIN(BUZZ, BUZZ_OFF);
}

void DriverTeclas(void)
{
	uint8_t codigoActual;
	codigoActual = DriverTeclasHW();

	DriverTeclasSW(codigoActual);
}

void DriverTeclasSW (uint8_t codigoActual)
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
		Teclas_Key = codigoActual;
		estadosEstables++;
		return;
	}

	if( estadosEstables == REBOTES + 1)
		return;

	estadosEstables ++;

	return;
}

uint8_t DriverTeclasHW(void)
{
	uint8_t codigo = NO_KEY;

	if ( GetPIN(KEY_RC) == OFF )
		return 0;

	if ( GetPIN(KEY3) == OFF )
		return 1;

	if ( GetPIN(KEY2) == OFF )
		return 2;

	if ( GetPIN(KEY1) == OFF )
		return 3;

	if ( GetPIN(KEY0) == OFF )
		return 4;

	return codigo ;
}

void Entradas_Debounce(void)
{
	uint8_t cambios,j;

	static uint8_t contador_estados[ 2 ];

	cambios = (EntradasDigitales&0x01) ^ (GetPIN(IN0) << 0);
	cambios |= (EntradasDigitales&0x02) ^ (GetPIN(IN1) << 1);

	if(cambios)
	{
		for(j = 0 ; j < 2 ; j++)
		{
			if( cambios & (0x01 << j) )
			{
				contador_estados[j]++;

				if(contador_estados[j] == ACEPTAR_ESTADO)
				{
					contador_estados[j] = 0;
					EntradasDigitales = EntradasDigitales ^ (0x01 << j);
				}
			}
			else
			{
				contador_estados[ j ] = 0;
			}
		}
	}
	else
	{
		contador_estados[ 0 ] = 0;
		contador_estados[ 1 ] = 0;
	}
}
