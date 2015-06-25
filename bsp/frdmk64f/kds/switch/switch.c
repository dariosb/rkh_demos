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
	{ 0, rawsw1,	SW_RELEASED },
	{ 0, rawsw2,	SW_RELEASED },
};


void
switch_tick( void )
{
	SWITCH_ST *p;
	ruint s;

	for( s = 0, p = switchs; p < &switchs[SWITCHS_NUM]; ++p, ++s ) 
	{
		p->state = (p->state<<1) | !(p->rawsw()); 
		if( (p->state == 0xFF) && (p->debsw != SW_PRESSED) )
		{
			p->debsw = SW_PRESSED;
			bsp_pub_sw_evt( s, p->debsw );
		}
		else if( ( p->state == 0x00 ) && (p->debsw != SW_RELEASED) )
		{
			p->debsw = SW_RELEASED;
			bsp_pub_sw_evt( s, p->debsw );
		}
	}

}


ruint
get_switch_state( ruint who )
{
	return switchs[who].debsw;
}
