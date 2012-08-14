/*
 *	file: trkact.c
 *	Last updated for version: 1.0.00
 *	Date of the last update:  May 20, 2012
 *	Contact information:
 *		e-mail:	dariosb@gmail.com
 */


#include "rkh.h"
#include "rkhtim.h"
#include "gps.h"
#include "trtemp.h"
#include "trkact.h"
#include "trk.h"
#include "gmgr.h"
#include "bsp.h"
#include "dbgcfg.h"

#include <time.h>

#if TRK_DBG_CFG == 1
	#define ACTIVE_DEBUG 	1
#else
	#define ACTIVE_DEBUG 	0
#endif

#include "debug.h"

DBG_MODULE_NAME(trk)


/*
 *	Defines local variables
 */

static RKHT_T tpos, tstop; 
static GPSFRM_T curr_pos;
static EGPSFRM_T *ppos;


/*
 * Defines local functions
 */


/*
 *	Defines SMA init function
 */

void
trk_init( void )
{
	mdebug( TRK_DBG );

	rkh_tim_init( &tpos, EPOS_TOUT, NULL );
	rkh_tim_init( &tstop, ESTOP_TOUT, NULL );

	gps_init();
}


/*
 *	Defines state entry functions
 */

void
start_epos_tmr( void )
{
	mdebug( TRK_DBG );

	rkh_tim_periodic( &tpos, trk, 
			RKH_TIM_MS( TRK_POS_PRD ),
			RKH_TIM_MS( TRK_POS_PRD ) );
}


void
start_estop_tmr( void )
{
	mdebug( TRK_DBG );

	rkh_tim_periodic( &tstop, trk, 
			RKH_TIM_MS( TRK_STOP_TIME ),
		   	RKH_TIM_MS( TRK_STOP_TIME ) );
}


/*
 *	Defines state exit functions
 */

void
stop_epos_tmr( void )
{
	mdebug( TRK_DBG );

	rkh_tim_stop( &tpos );
}


void
stop_estop_tmr( void )
{
	mdebug( TRK_DBG );

	rkh_tim_stop( &tstop );
}


void
send_vmax_limit( void )
{
	SEND_EVT_REQ_T *e;
	VMAX_T *p;

	mdebug( TRK_DBG );

	if( ( e = gmgr_evt_req() ) == NULL )
		return;

	e->ts = (ts_t)time( NULL ); 
	e->type = TRT_EVT_VMAX; 
	
	p = &e->data.vmax;

	p->lat = ppos->frm.lat;
	p->lng = ppos->frm.lng;
	p->vel = ppos->frm.vel;

	gmgr_evt_post( e );
}


/*
 *	Defines transition action functions
 */

void
set_curr_pos( RKHEVT_T *pe )
{
	mdebug( TRK_DBG );

	RKH_RSV( pe );
	ppos = CEGF( pe );
}


void
upd_curr_pos( RKHEVT_T *pe )
{
	mdebug( TRK_DBG );

	RKH_GC( CE( ppos ) );

	RKH_RSV( pe );
	ppos = CEGF( pe );
}


void
rel_curr_pos( RKHEVT_T *pe )
{
	(void)pe;

	mdebug( TRK_DBG );

	RKH_GC( CE( ppos ) );
}


void
send_curr_pos( RKHEVT_T *pe )
{
	SEND_EVT_REQ_T *e;

	(void)pe;

	mdebug( TRK_DBG );

	if( ( e = gmgr_evt_req() ) == NULL )
		return;

	e->ts = (ts_t)time( NULL ); 
	e->type = TRT_EVT_POSITION;

	e->data.pos = ppos->frm;

	gmgr_evt_post( e );
}


void
send_in_stop( RKHEVT_T *pe )
{
	SEND_EVT_REQ_T *e;
	STOP_T *p;

	(void)pe;

	mdebug( TRK_DBG );

	if( ( e = gmgr_evt_req() ) == NULL )
		return;

	e->ts = (ts_t)time( NULL ); 
	e->type = TRT_EVT_STOP; 

	p = &e->data.stop;
	p->lat = ppos->frm.lat;
	p->lng = ppos->frm.lng;

	gmgr_evt_post( e );	
}


/*
 *	Defines branch's guards
 */

HUInt
is_online( RKHEVT_T *pe )
{
	return ( CEGF(pe)->frm.state == GPS_IS_ONLINE ) ? RKH_GTRUE : RKH_GFALSE;
}


HUInt
in_stop( RKHEVT_T *pe )
{
	return ( CEGF(pe)->frm.vel <= TRK_MIN_VELOCITY ) ? RKH_GTRUE : RKH_GFALSE;
}


HUInt
is_vmax( RKHEVT_T *pe )
{
	return ( CEGF(pe)->frm.vel >= TRK_MAX_VELOCITY ) ? RKH_GTRUE : RKH_GFALSE;
}


