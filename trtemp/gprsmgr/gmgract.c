/*
 *	file: gmgract.c
 *	Last updated for version: 1.0.00
 *	Date of the last update:  May 20, 2012
 *	Contact information:
 *		e-mail:	dariosb@gmail.com
 */


#include "rkh.h"
#include "trtemp.h"
#include "gmgract.h"
#include "gmgr.h"
#include "gprs.h"
#include "dbgcfg.h"


#if EMGR_DBG_CFG == 1
	#define ACTIVE_DEBUG 	1
#else
	#define ACTIVE_DEBUG 	0
#endif

#include "debug.h"

DBG_MODULE_NAME(gmgr)


/*
 *	Defines local variables
 */

static RKHEVT_T *emdfq_sto[ EMGR_MAX_DEFER_EVENT ];
static RKHRQ_T gmgr_dfq;
static SEND_EVT_REQ_T *pevt;


/*
 * Defines local functions
 */


/*
 *	Defines SMA init function
 */

void
gmgr_init( void )
{
	mdebug( EMGR_DBG );

	gprs_init();
	rkh_rq_init( &gmgr_dfq, (const void **)emdfq_sto, EMGR_MAX_DEFER_EVENT, NULL );
}


/*
 *	Defines state entry functions
 */


/*
 *	Defines state exit functions
 */

void
recall_events( void )
{
	mdebug( EMGR_DBG );

	rkh_recall( gmgr, &gmgr_dfq );
}


/*
 *	Defines transition action functions
 */

void
gmgr_send_req( RKHEVT_T *pe )
{
	mdebug( EMGR_DBG );

	RKH_RSV( pe );
	pevt = CSREQ( pe );

	gprs_send( pevt );
}


void
gmgr_defer_evt( RKHEVT_T *pe )
{
	mdebug( EMGR_DBG );

	rkh_defer( &gmgr_dfq, pe );
}


void
gmgr_send_last( RKHEVT_T *pe )
{
	(void)pe;

	mdebug( EMGR_DBG );

	gprs_send( pevt );
}


void
gmgr_send_cfm( RKHEVT_T *pe )
{
	(void)pe;

	mdebug( EMGR_DBG );

	RKH_GC( CE( pevt ) );
}


void
gmgr_term( RKHEVT_T *pe )
{
	(void)pe;

	mdebug( EMGR_DBG );

	rkh_exit();
}

/*
 *	Defines branch's guards
 */

HUInt
room_in_dfq( RKHEVT_T *pe )
{
	(void)pe;

	return ( !rkh_rq_is_full( &gmgr_dfq ) ) ? RKH_GTRUE : RKH_GFALSE;
}


/*
 * Define sma public functions
 */
	
SEND_EVT_REQ_T *
gmgr_evt_req( void )
{
	if( !rkh_rq_is_full( &gmgr_dfq ) )
		return RKH_ALLOC_EVENT( SEND_EVT_REQ_T, SEND_EVT_REQ );
	else
		return NULL;
}


void
gmgr_evt_post( SEND_EVT_REQ_T *e )
{
	rkh_sma_post_fifo( gmgr, CE(e) );
}
