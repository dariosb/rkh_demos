/*
 * swhdl.c
 *
 * Minimal debouncing switch handler.
 * hardware access.
 *
 */

#include "board.h"
#include "swhdl.h"


ruint
rawsw1( void )
{
	return GPIO_DRV_ReadPinInput(kGpioSW2);
}

ruint
rawsw2( void )
{
	return GPIO_DRV_ReadPinInput(kGpioSW3);
}
