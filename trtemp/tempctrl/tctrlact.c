/*
 *	file: tctrlact.c
 *	Last updated for version: 1.0.00
 *	Date of the last update:  May 20, 2012
 *	Contact information:
 *		e-mail:	dariosb@gmail.com
 */


#include "rkh.h"
#include "tmp.h"
#include "trtemp.h"
#include "tctrlact.h"
#include "tctrl.h"
#include "gmgr.h"
#include "dbgcfg.h"

#include <time.h>

#if TCTRL_DBG_CFG == 1
	#define ACTIVE_DEBUG 	1
#else
	#define ACTIVE_DEBUG 	0
#endif

#include "debug.h"

DBG_MODULE_NAME(tmpctrl)


/*
 *	Defines local variables
 */


/*
 * Defines local functions
 */

static
void
tctrl_send_evt( rkhui8_t st, rkhui8_t temp )
{
	SEND_EVT_REQ_T *e;
	CMPCHG_T *p;
	
	if( ( e = gmgr_evt_req() ) == NULL )
		return;

	e->ts = (ts_t)time( NULL ); 
	e->type = TRT_EVT_COMPRESSOR;

	p = &e->data.cmp;

	p->temp = temp;
	p->state = st;
	
	gmgr_evt_post( e );
}


/*
 *	Defines SMA init function
 */

void
tctrl_init( void )
{
	mdebug( TCTRL_DBG );

	tmp_init();
}


/*
 *	Defines state entry functions
 */


/*
 *	Defines state exit functions
 */


/*
 *	Defines transition action functions
 */

void
compressor_stop( RKHEVT_T *pe )
{
	mdebug( TCTRL_DBG );

	tctrl_send_evt( COMPRESSOR_IDLE, CTS(pe)->temp );
}


void
compressor_start( RKHEVT_T *pe )
{
	mdebug( TCTRL_DBG );

	tctrl_send_evt( COMPRESSOR_RUNNING, CTS(pe)->temp );
}


void
compressor_failure( RKHEVT_T *pe )
{
	(void)pe;

	mdebug( TCTRL_DBG );

	tctrl_send_evt( COMPRESSOR_FAILURE, get_curr_temp() );
}


void
compressor_failrst( RKHEVT_T *pe )
{
	(void)pe;

	mdebug( TCTRL_DBG );

	tctrl_send_evt( COMPRESSOR_FAILRST, get_curr_temp() );
}


/*
 *	Defines branch's guards
 */

HUInt
upper2tmax( RKHEVT_T *pe )
{
	return (CTS(pe)->temp > TCTRL_TMP_HIGH_TH) ? RKH_GTRUE : RKH_GFALSE ;
}


HUInt
lower2tmin( RKHEVT_T *pe )
{
	return (CTS(pe)->temp < TCTRL_TMP_LOW_TH) ? RKH_GTRUE : RKH_GFALSE ;
}


