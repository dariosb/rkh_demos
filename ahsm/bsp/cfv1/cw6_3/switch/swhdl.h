/*
 * swhdl.h
 */

#ifndef __SWHDL_H__
#define __SWHDL_H__

#include "mytypes.h"
#include "rkh.h"
#include "mcu.h"

uchar	rawsw1( void ),
		rawsw2( void ),
		rawsw3( void ),
		rawsw4( void );

#define SWITCH_TICK_MS(x)	RTI_MS(x)

#endif
