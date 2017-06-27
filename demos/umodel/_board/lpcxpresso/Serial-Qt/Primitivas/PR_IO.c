/**
 	\file PR_IO.c
 	\brief Primitiva de dispostivos de entrada/salida
 	\details relays, led rgb, entradas digitales y leds y dipswitches de expansion 1
 	\author Pablo Irrera Condines
 	\date 2013.05.08
*/

#include "PR_IO.h"
#include "FW_IO.h"
#include "FW_EXP1IO.h"

void LEDs_Relays (uint8_t n, uint8_t estado)
{
	if ( estado )
		BufferLED_Relay |= (1 << n);
	else
		BufferLED_Relay &= (~(1 << n));
}

void RGB_Buzzer (uint8_t pin, uint8_t estado)
{
	if ( estado )
		BufferRGB_Buzzer |= (1 << pin);
	else
		BufferRGB_Buzzer &= (~(1 << pin));
}

uint8_t GetEntradas (void)
{
	return EntradasDigitales;
}

void LEDs (uint8_t n, uint8_t estado)
{
	if ( estado )
		BufferLED |= (1 << n);
	else
		BufferLED &= (~(1 << n));
}

uint8_t GetEntradasDIP (void)
{
	return EntradasDIP;
}
