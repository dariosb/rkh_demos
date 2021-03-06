/*
 * switch.c
 *
 * Minimal debouncing switch handler.
 * hardware access.
 *
 */

#include "switch.h"
#include "swhdl.h"
#include "bsp.h"

static SWITCH_ST switchs[SWITCHS_NUM] = 
{
	{ 0, rawDoorOpen,	SW_RELEASE, SW_PRESS },
	{ 0, rawDoorClose,	SW_RELEASE, SW_PRESS },
	{ 0, rawSensor,	    SW_RELEASE, SW_PRESS|SW_RELEASE },
};


void
switch_tick( void )
{
	SWITCH_ST *p;
	ruint s;

	for( s = 0, p = switchs; p < &switchs[SWITCHS_NUM]; ++p, ++s ) 
	{
		p->state = (p->state<<1) | !(p->rawsw()); 
		if( (p->state == 0xFF) && (p->debsw != SW_PRESS) )
		{
			p->debsw = SW_PRESS;
			if( p->filter & SW_PRESS )
				bsp_pub_sw_evt( s, SW_PRESS );
		}
		else if( ( p->state == 0x00 ) && (p->debsw != SW_RELEASE) )
		{
			p->debsw = SW_RELEASE;
			if( p->filter & SW_RELEASE )
				bsp_pub_sw_evt( s, SW_RELEASE );
		}
	}

}


ruint
get_switch_state( ruint who )
{
	return switchs[who].debsw;
}
