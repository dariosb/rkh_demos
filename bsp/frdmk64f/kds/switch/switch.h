/*
 * switch.h
 *
 * Minimal debouncing switch handler
 *
 */

#ifndef __SWITCH_H__
#define __SWITCH_H__

#include "rkh.h"

typedef struct
{
	unsigned char state;
	ruint (*rawsw)(void);
	ruint debsw;
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
	SWITCHS_NUM
};

void switch_tick( void );
ruint get_switch_state( ruint who );

#endif
