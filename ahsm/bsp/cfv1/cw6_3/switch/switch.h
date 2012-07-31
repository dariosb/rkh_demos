/*
 * switch.h
 */

#ifndef __SWITCH_H__
#define __SWITCH_H__

#include "rkh.h"
#include "mytypes.h"

typedef struct
{
	uchar state;			/* current state */
	uchar last;				/* previouse state */
	uchar (*rawsw)(void); 	/* read IO */
	uchar debsw;			/* debounced switch state */
	uchar sc;				/* switch scan code */
}SWITCH_ST;

enum
{
	SW_RELEASED,
	SW_PRESSED
};

enum
{
	SW1_SWITCH,
	SW2_SWITCH,
	SW3_SWITCH,
	SW4_SWITCH,
	SWITCHS_NUM
};

#define SWITCH_TICK		10		// Switch debouncing tick

void switch_tick( void );

uchar get_switch_state( uchar who );

void switch_start( void );

#endif
