/*
 *	file: tmp.c
 *	Last updated for version: 1.0.00
 *	Date of the last update:  May 20, 2012
 *	Contact information:
 *		e-mail:	dariosb@gmail.com
 */

/**
 * 	\file tmp.c
 *
 *	\brief
 *	Temperature adquisition emulation.
 */


#include "rkh.h"
#include "trtemp.h"
#include "tmp.h"
#include "tctrl.h"
#include "bsp.h"
#include "critical.h"
#include "dbgcfg.h"

#include <stdio.h>


#if TMP_DBG_CFG == 1
	#define ACTIVE_DEBUG 	1
#else
	#define ACTIVE_DEBUG 	0
#endif

#include "debug.h"

DBG_MODULE_NAME(tmp)


static rkhi8_t curr_temp = TEMP_INITIAL;
static rkhi8_t tmptick;
static rkhi8_t cmp_status;

static RKH_DCLR_STATIC_EVENT( e_cmpok, CMP_FAILURE_RST );
static RKH_DCLR_STATIC_EVENT( e_cmpf, CMP_FAILURE );

void
tmp_isr( void )
{
	TSMP_T *e;

	enter_critical();

	if( tmptick && --tmptick == 0 )
	{
		tmptick = RKH_TIM_MS( TEMP_TICK );
		e = RKH_ALLOC_EVENT( TSMP_T, TSMP );
		e->temp = curr_temp;
		rkh_sma_post_fifo( tctrl, CE(e) );
	}

	exit_critical();
}


void
tmp_inc( void )
{
	mdebug( TMP_DBG );


	if( curr_temp < TEMP_MAX_VALUE ) 
	{
		enter_critical();
		curr_temp += TEMP_DELTA;
		exit_critical();

		printf( "%s\tTemperature = %d\r\n", DBG_OFFSET, curr_temp );	
	}

}


void
tmp_dec( void )
{
	mdebug( TMP_DBG );


	if( curr_temp > TEMP_MIN_VALUE )
	{
		enter_critical();
		curr_temp -= TEMP_DELTA;
		exit_critical();

		printf( "%s\tTemperature = %d\r\n", DBG_OFFSET, curr_temp );
	}

}


rkhi8_t
get_curr_temp( void )
{
	return curr_temp;
}


void
cmp_status_chg( void )
{
	enter_critical();

	cmp_status ^= 1;

	exit_critical();

	if( cmp_status )
		rkh_sma_post_fifo( tctrl, &e_cmpok );
	else
		rkh_sma_post_fifo( tctrl, &e_cmpf );
}


void
tmp_init( void )
{
	mdebug( TMP_DBG );

	enter_critical();

	tmptick = RKH_TIM_MS( TEMP_TICK );
	cmp_status = 1;
	
	exit_critical();
}
