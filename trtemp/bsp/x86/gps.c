/*
 *	file: gps.c
 *	Last updated for version: 1.0.00
 *	Date of the last update:  May 20, 2012
 *	Contact information:
 *		e-mail:	dariosb@gmail.com
 */

/**
 * 	\file gps.c
 *
 *	\brief
 *	GPS adquisition emulation.
 */


#include "rkh.h"
#include "trtemp.h"
#include "gps.h"
#include "trk.h"
#include "bsp.h"
#include "critical.h"
#include "dbgcfg.h"

#include <stdio.h>
#include <time.h>


#if GPS_DBG_CFG == 1
	#define ACTIVE_DEBUG 	1
#else
	#define ACTIVE_DEBUG 	0
#endif

#include "debug.h"

DBG_MODULE_NAME(gps)


static rkhi8_t gpstick;
static GPSFRM_T gpsfrm;


void
gps_isr( void )
{
	EGPSFRM_T *e;

	enter_critical();

	if( gpstick && --gpstick == 0 )
	{
		gpstick = RKH_TIM_MS( GPS_TICK );
		e = RKH_ALLOC_EVENT( EGPSFRM_T, GPSFRM );

		gpsfrm.lat = rand();
		gpsfrm.lng = rand();
		memcpy( &e->frm, &gpsfrm, sizeof(GPSFRM_T) );
		rkh_sma_post_fifo( trk, CE(e) );
	}

	exit_critical();
}


void
vel_inc( void )
{
	mdebug( GPS_DBG );


	if( gpsfrm.vel < VEL_MAX_VALUE ) 
	{
		enter_critical();
		gpsfrm.vel += VEL_DELTA;
		exit_critical();

		printf( "%s\t Velocity = %u\r\n", DBG_OFFSET, gpsfrm.vel );	
	}
}


void
vel_dec( void )
{
	mdebug( GPS_DBG );


	if( gpsfrm.vel > VEL_MIN_VALUE )
	{
		enter_critical();
		gpsfrm.vel -= VEL_DELTA;
		exit_critical();

		printf( "%s\t Velocity = %u\r\n", DBG_OFFSET, gpsfrm.vel );	
	}
}


void
gps_sats_chg( void )
{
	enter_critical();

	gpsfrm.state ^= 1;
	
	exit_critical();

	printf( "%s\t GPS Coverage: %s\r\n", DBG_OFFSET,
			gpsfrm.state == GPS_IS_ONLINE ? "ONLINE" : "OFFLINE" );	
}


void
gps_init( void )
{
	mdebug( GPS_DBG );

	enter_critical();

	gpsfrm.state = GPS_IS_ONLINE;
	gpsfrm.lat = 0;
	gpsfrm.lng = 0;
	gpsfrm.vel = 0;

	gpstick = RKH_TIM_MS( GPS_TICK );

	exit_critical();
}
