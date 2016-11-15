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
rawStart( void )
{
	return GPIO_DRV_ReadPinInput(kGpioStart);
}

ruint
rawStop( void )
{
	return GPIO_DRV_ReadPinInput(kGpioStop);
}
	
ruint
rawDoor( void )
{
	return GPIO_DRV_ReadPinInput(kGpioDoor);
}
