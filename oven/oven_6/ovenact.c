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

#define MAX_SIZEOF_QURC		3

RKH_RQ_T qurc;
static RKH_EVT_T *qurc_sto[ MAX_SIZEOF_QURC ];

static rui8_t restart_cnt;


/*
 *	Defines HSM init function
 */

void
oven_init( void )
{
	bsp_oven_init();
	RKH_TMR_INIT( &oventim, &e_tout, NULL );
	rkh_rq_init( &qurc, (const void **)qurc_sto, MAX_SIZEOF_QURC, NULL );
	restart_cnt = 0;
}


/*
 *	Defines state entry/exit functions
 */

void 
start_cooking( void )
{
	bsp_emitter_on();
	RKH_TMR_ONESHOT( &oventim, oven, EMITTER_ON_TIME );
}

void 
stop_cooking( void )
{
	bsp_emitter_off();
	rkh_tmr_stop( &oventim );
}

/*
 * Defines actions functions
 */

void
inc_start( const RKH_SMA_T *sma, RKH_EVT_T *pe )
{
	(void)sma;
	(void)pe;

	++restart_cnt;
}


void
defer_start( const RKH_SMA_T *sma, RKH_EVT_T *pe )
{
	(void)sma;

	rkh_fwk_defer( &qurc, pe );
}


void
recall_evts( const RKH_SMA_T *sma, RKH_EVT_T *pe )
{
	(void)pe;

	if( rkh_fwk_recall( (RKH_SMA_T *)(sma), &qurc ) == RKH_EVT_CAST(0) )
		restart_cnt = 0;
}


/*
 * Defines actions functions
 */

rbool_t
chk_restart_cnt( void )
{
	return ( restart_cnt < 2 ) ? RKH_TRUE : RKH_FALSE;
}
