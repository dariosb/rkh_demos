/*
 * swhdl.h
 *
 * Minimal debouncing switch handler.
 * hardware access.
 *
 */

#ifndef __SWHDL_H__
#define __SWHDL_H__

#include "switch.h"

ruint rawDoorOpen( void );
ruint rawDoorClose( void );
ruint rawSensor( void );

#endif
