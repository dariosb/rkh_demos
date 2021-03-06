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
	ruint filter;
}SWITCH_ST;

enum
{
	SW_RELEASE = 0x01,
	SW_PRESS = 0x02
};

#define SW_FLT_MSK	(SW_RELEASE|SW_PRESS)

enum
{
	DOOROPEN_SW,
	DOORCLOSE_SW,
	SENSOR_SW,
	SWITCHS_NUM
};

void switch_tick( void );
ruint get_switch_state( ruint who );

#endif
