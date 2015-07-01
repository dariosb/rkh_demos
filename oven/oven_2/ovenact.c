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
 * 	The 'e_tout' event with TMREVT signal never changes, so it can be 
 * 	statically allocated just once by means of RKH_ROM_STATIC_EVENT() macro.
 */

static RKH_ROM_STATIC_EVENT( e_tout, TMREVT );


/*
 * 	Declare and allocate the 'oventim' timer, which is responsible for control
 * 	cooking duration, posting the TIMEOUT signal event to active object	'oven'.
 */

RKH_TMR_T oventim;


/*
 * Declare queue to be used as deferred queue
 */


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
}

void 
cook_start( void )
{
	bsp_emitter_on();
	RKH_TMR_ONESHOT( &oventim, oven, COOK_TIME );
}

void 
cook_stop( void )
{
	bsp_emitter_off();
	rkh_tmr_stop( &oventim );
}

