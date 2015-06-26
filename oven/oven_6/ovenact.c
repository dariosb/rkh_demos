/*
 *	ovenact.c
 */


#include "rkh.h"
#include "oven.h"
#include "ovenevt.h"
#include "bsp.h"

#include <stdio.h>


/*
 * 	Declare and allocate the 'e_tout' event.
 * 	The 'e_tout' event with TOUT signal never changes, so it can be 
 * 	statically allocated just once by means of RKH_ROM_STATIC_EVENT() macro.
 */

static RKH_ROM_STATIC_EVENT( e_tout, TOUT );


/*
 * 	Declare and allocate the 'oventim' timer, which is responsible for control
 * 	cooking duration, posting the TIMEOUT signal event to active object	'oven'.
 */

RKH_TMR_T oventim;


/*
 * Declare queue to be used as deferred queue
 */

static rui8_t start_cnt, restart_cnt;


/*
 *	Defines HSM init function
 */

void
oven_init( void )
{
	bsp_oven_init();
	RKH_TMR_INIT( &oventim, &e_tout, NULL );
}


/*
 *	Defines state entry/exit functions
 */

void
door_open( void )
{
	bsp_door_open();
}

void
cook_ready( void )
{
	bsp_emitter_ready();
	start_cnt = restart_cnt = 0;
}

void 
cook_start( void )
{
	bsp_emitter_on();
	RKH_TMR_ONESHOT( &oventim, oven, COOKING_TIME );
}

void 
cook_pause( void )
{
	bsp_emitter_pause();
	rkh_tmr_stop( &oventim );
}

void 
cook_continue( void )
{
	bsp_emitter_continue();
	RKH_TMR_ONESHOT( &oventim, oven, COOKING_TIME );
}


void 
cook_stop( void )
{
	bsp_emitter_off();
	rkh_tmr_stop( &oventim );
}


/*
 * Defines actions functions
 */


void
inc_start( void )
{
	++start_cnt;
}


void
cook_restart( void )
{
	++restart_cnt;
	RKH_TMR_ONESHOT( &oventim, oven, COOKING_TIME );
}


/*
 * Defines guard functions
 */

rbool_t
chk_start( void )
{
	return ( start_cnt < RESTRT_COOK_ALLOW ) ? RKH_TRUE : RKH_FALSE;
}

rbool_t
chk_restart( void )
{
	return ( restart_cnt == start_cnt ) ? RKH_TRUE : RKH_FALSE;
}
