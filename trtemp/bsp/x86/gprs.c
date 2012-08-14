/*
 *	file: grps.c
 *	Last updated for version: 1.0.00
 *	Date of the last update:  May 20, 2012
 *	Contact information:
 *		e-mail:	dariosb@gmail.com
 */

/**
 * 	\file grps.c
 *
 *	\brief
 *	GPRS link emulation.
 */


#include "rkh.h"
#include "trtemp.h"
#include "gprs.h"
#include "gmgr.h"
#include "bsp.h"
#include "critical.h"
#include "dbgcfg.h"

#include <stdio.h>
#include <time.h>


#if GPRS_DBG_CFG == 1
	#define ACTIVE_DEBUG 	1
#else
	#define ACTIVE_DEBUG 	0
#endif

#include "debug.h"

DBG_MODULE_NAME(gprs)


/*
 *	Defines local variables
 */

static rkhi8_t gprstick;
static rkhui8_t link_is_ok;
static SEND_EVT_REQ_T gevt;

static const char *cmpst_str[] =
{
	"IDLE",
	"RUNNING",
	"ON FAILURE",
	"IDLE"
};

static RKH_DCLR_STATIC_EVENT( e_scfm, SEND_EVT_CFM );
static RKH_DCLR_STATIC_EVENT( e_srej, SEND_EVT_REJ );


#define SHOW_GPRS_FMT( s, ... )		printf( "%s%06u - "s"\r\n", PR_OFFSET, gevt.ts, ##__VA_ARGS__ )


/*
 * Defines local functions
 */

static
void
show_evt_position( GPSFRM_T *p )
{
	SHOW_GPRS_FMT( "%s: Lat= %05d, Long= %05d, Vel= %03d", " POSITION ", p->lat, p->lng, p->vel );
}


static
void
show_evt_stop( STOP_T *p )
{
	SHOW_GPRS_FMT( "%s: Lat= %05d, Long= %05d", "   STOP   ", p->lat, p->lng );
}


static
void
show_evt_vmax( VMAX_T *p )
{
	SHOW_GPRS_FMT( "%s: Lat= %05d, Long= %05d, Vel= %03d", "   VMAX   ", p->lat, p->lng, p->vel );
}


static
void
show_evt_compressor( CMPCHG_T *p )
{
	SHOW_GPRS_FMT( "%s: %s at Temp= %02d", "COMPRESSOR", cmpst_str[p->state], p->temp );
}


static
void
show_evt( void )
{
	switch( gevt.type )
	{
		case TRT_EVT_POSITION:
			show_evt_position( &gevt.data.pos );
			break;

		case TRT_EVT_STOP:
			show_evt_stop( &gevt.data.stop );
			break;

		case TRT_EVT_VMAX:
			show_evt_vmax( &gevt.data.vmax );
			break;

		case TRT_EVT_COMPRESSOR:
			show_evt_compressor( &gevt.data.cmp );
			break;

		default:
			break;
	}

}

/*
 * Defines public functions
 */

void
gprs_isr( void )
{
	enter_critical();

	if( gprstick && --gprstick == 0 )
	{
		if( link_is_ok )
		{
			show_evt();
			rkh_sma_post_fifo( gmgr, &e_scfm );
		}
		else
			rkh_sma_post_fifo( gmgr, &e_srej );
	}
	
	exit_critical();
}


void
gprs_send( SEND_EVT_REQ_T *p )
{
	mdebug( GPRS_DBG );

	gevt = *p;

	enter_critical();

	gprstick = RKH_TIM_MS( GPRS_RESP_TIME );

	exit_critical();
}


void
gprs_link_chg( void )
{
	mdebug( GPRS_DBG );

	enter_critical();

	link_is_ok ^= 1;

	exit_critical();

	printf( "%s\t GPRS Link: %s\r\n", DBG_OFFSET, link_is_ok ? "OK" : "BROKEN" );	
}


void
gprs_init( void )
{
	mdebug( GPRS_DBG );

	enter_critical();

	link_is_ok = 1;
	
	exit_critical();
}
