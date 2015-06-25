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
#include "fsl_gpio_driver.h"

ruint rawsw1( void );
ruint rawsw2( void );

#endif
