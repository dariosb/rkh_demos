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
cook_start( void )
{
	bsp_emitter_on();
	RKH_TMR_ONESHOT( &oventim, oven, COOKING_TIME );
}

void 
cook_stop( void )
{
	bsp_emitter_off();
	rkh_tmr_stop( &oventim );
}

