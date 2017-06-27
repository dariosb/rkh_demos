/**
 	\file FW_Display.c
 	\brief Drivers de dispositivos de dipswitch y leds
 	\details Expansion 1
 	\author Pablo Irrera Condines
 	\date 2013.05.08
*/

#include "UtilesInfo2.h"
#include "KitInfo2_Expansiones.h"
#include "FW_EXP1IO.h"

uint8_t BufferLED;
uint16_t EntradasDIP;

#ifdef KITINFOII_EXPANSION1

void EX1_BarridoLEDs (void)
{
	if( BufferLED & (1 << IOEXP1_LED1) )
		SetPIN(EX1_LED1, ON);
	else
		SetPIN(EX1_LED1, OFF);

	if( BufferLED & (1 << IOEXP1_LED2) )
		SetPIN(EX1_LED2, ON);
	else
		SetPIN(EX1_LED2, OFF);

	if( BufferLED & (1 << IOEXP1_LED3) )
		SetPIN(EX1_LED3, ON);
	else
		SetPIN(EX1_LED3, OFF);

	if( BufferLED & (1 << IOEXP1_LED4) )
		SetPIN(EX1_LED4, ON);
	else
		SetPIN(EX1_LED4, OFF);

	if( BufferLED & (1 << IOEXP1_LED5) )
		SetPIN(EX1_LED5, ON);
	else
		SetPIN(EX1_LED5, OFF);

	if( BufferLED & (1 << IOEXP1_LED6) )
		SetPIN(EX1_LED6, ON);
	else
		SetPIN(EX1_LED6, OFF);

	if( BufferLED & (1 << IOEXP1_LED7) )
		SetPIN(EX1_LED7, ON);
	else
		SetPIN(EX1_LED7, OFF);

	if( BufferLED & (1 << IOEXP1_LED8) )
		SetPIN(EX1_LED8, ON);
	else
		SetPIN(EX1_LED8, OFF);
}

void EX1_EntradasDebounce(void)
{
	uint8_t cambios,j;

	static uint8_t contador_estados[ 8 ];

	cambios = (EntradasDIP&0x01) ^ (GetPIN(EX1_IN1) << 0);
	cambios |= (EntradasDIP&0x02) ^ (GetPIN(EX1_IN2) << 1);
	cambios |= (EntradasDIP&0x04) ^ (GetPIN(EX1_IN3) << 2);
	cambios |= (EntradasDIP&0x08) ^ (GetPIN(EX1_IN4) << 3);
	cambios |= (EntradasDIP&0x10) ^ (GetPIN(EX1_IN5) << 4);
	cambios |= (EntradasDIP&0x20) ^ (GetPIN(EX1_IN6) << 5);
	cambios |= (EntradasDIP&0x40) ^ (GetPIN(EX1_IN7) << 6);
	cambios |= (EntradasDIP&0x80) ^ (GetPIN(EX1_IN8) << 7);

	if(cambios)
	{
		for(j = 0 ; j < 8 ; j++)
		{
			if( cambios & (0x01 << j) )
			{
				contador_estados[j]++;

				if(contador_estados[j] == ACEPTAR_ESTADO)
				{
					contador_estados[j] = 0;
					EntradasDIP = EntradasDIP ^ (0x01 << j);
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
		for(j = 0 ; j < 8 ; j++)
			contador_estados[ j ] = 0;
	}
}

#endif
