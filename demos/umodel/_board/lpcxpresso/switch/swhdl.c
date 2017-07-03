/*
 * swhdl.c
 *
 * Minimal debouncing switch handler.
 * hardware access.
 *
 */

#include "swhdl.h"
#include "KitInfo2.h"
#include "UtilesInfo2.h"


ruint
rawDoorOpen( void )
{
	return GetPIN(KEY2);
}

ruint
rawDoorClose( void )
{
	return GetPIN(KEY0);
}
	
ruint
rawSensor( void )
{
	return GetPIN(KEY1);
}
