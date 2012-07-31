/*
 * switch.c
 */

#include "mcu.h"
#include "swhdl.h"
#include "switch.h"

#include "rkhdata.h"
#include "my.h"

#define INF_ON_RELEASE	0

static SWITCH_ST switchs[SWITCHS_NUM] = 
{
	{ 0, 0, rawsw1,	SW_RELEASED, ONE },
	{ 0, 0, rawsw2,	SW_RELEASED, TWO },
	{ 0, 0, rawsw3,	SW_RELEASED, THREE },
	{ 0, 0, rawsw4,	SW_RELEASED, FOUR },
};

static HUInt swtick;


void
inform_switch( SWITCH_ST *p )
{
	MYEVT_T *mye;

	mye = RKH_ALLOC_EVENT( MYEVT_T, p->sc );
	mye->ts = ( rkhui16_t )get_ts();

	rkh_sma_post_fifo( my, ( RKHEVT_T* )mye );
}

void
switch_tick( void )
{
	SWITCH_ST *p;

	if(!( swtick && --swtick == 0 ))
		return;

	swtick = SWITCH_TICK_MS( SWITCH_TICK );
		
	for( p = switchs; p < &switchs[SWITCHS_NUM]; ++p ) 
	{
		p->state = (uchar)((p->state<<1) | !(p->rawsw())); 
		if( p->last == p->state )
			continue;
		
		p->last = p->state;

		if(	p->state == 0xFF )
		{
			p->debsw = SW_PRESSED;
			inform_switch( p );
		}
		else if( p->state == 0x00 )
		{
			p->debsw = SW_RELEASED;
#if INF_ON_RELEASE == 1
			inform_switch( p );
#endif
		}
	}

}

uchar
get_switch_state( uchar who )
{
	return switchs[who].debsw;
}

void
switch_start( void )
{
	swtick = SWITCH_TICK_MS( SWITCH_TICK );
}
