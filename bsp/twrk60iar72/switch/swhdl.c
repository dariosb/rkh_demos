/*
 * swhdl.c
 */

#include "gpio.h"
#include "swhdl.h"

MUInt
rawsw1( void )
{
	return get_gpio(SW1);
}

static MUInt val;

MUInt
rawsw2( void )
{
  	val = get_gpio(SW2);
	return val;
}
