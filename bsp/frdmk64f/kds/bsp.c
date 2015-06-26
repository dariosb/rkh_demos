/**
 * \cond
 *  --------------------------------------------------------------------------
 *
 *                                Framework RKH
 *                                -------------
 *
 * 	          State-machine framework for reactive embedded systems            
 * 	        
 * 	                    Copyright (C) 2010 Leandro Francucci.
 * 	        All rights reserved. Protected by international copyright laws.
 *
 *
 * 	RKH is free software: you can redistribute it and/or modify it under the 
 * 	terms of the GNU General Public License as published by the Free Software 
 * 	Foundation, either version 3 of the License, or (at your option) any 
 * 	later version.
 *
 *  RKH is distributed in the hope that it will be useful, but WITHOUT ANY 
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for 
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along 
 *  with RKH, see copying.txt file.
 *
 * 	Contact information:
 * 	RKH web site:	http://sourceforge.net/projects/rkh-reactivesys/
 * 	e-mail:			francuccilea@gmail.com
 *
 *  --------------------------------------------------------------------------
 *  File                     : bsp.c
 *	Last updated for version : v2.4.04
 *	By                       : DB
 *  --------------------------------------------------------------------------
 *  \endcond
 *
 * 	\file
 * 	\ingroup 	prt
 *
 * 	\brief 		BSP for FRDK64F120 using Freescale KSDK Bare Metal
 */


#include "bsp.h"
#include "oven.h"
#include "ovenevt.h"
#include "rkh.h"
#include "fsl_debug_console.h"
#include "fsl_hwtimer_systick.h"
#include "switch.h"


#define SERIAL_TRACE			1

/* This macro is needed only if the module requires to check 	.. */
/* .. expressions that ought to be true as long as the program  .. */
/* .. is running. 												   */

RKH_THIS_MODULE


static hwtimer_t hwtimer;			/* Systick hardware timer */

static RKH_ROM_STATIC_EVENT( e_start, START );
static RKH_ROM_STATIC_EVENT( e_open, OPEN );
static RKH_ROM_STATIC_EVENT( e_close, CLOSE );
static RKH_ROM_STATIC_EVENT( e_term, TERM );
#if ( __STOP_BUTTON__ == RKH_ENABLED )
static RKH_ROM_STATIC_EVENT( e_stop, STOP );
#endif

#if defined( RKH_USE_TRC_SENDER )
static rui8_t door;
static rui8_t panel;
#endif


/*
 * 	For serial trace feature.
 */

#if SERIAL_TRACE == 1
	#define SERIAL_TRACE_OPEN()		rkhtrc_uart_init()
	#define SERIAL_TRACE_CLOSE() 	rkhtrc_uart_deinit()
	#define SERIAL_TRACE_SEND_BLOCK( buf_, len_ )	\
									rkhtrc_send_block( buf_, len_ )
#else
	#define SERIAL_TRACE_OPEN()						(void)0
	#define SERIAL_TRACE_CLOSE()					(void)0
	#define SERIAL_TRACE_SEND( d )					(void)0
	#define SERIAL_TRACE_SEND_BLOCK( buf_, len_ )	(void)0
#endif


void
bsp_pub_sw_evt( ruint s, ruint debsw )
{
 	switch( s )
	{
		case START_SW:
			RKH_SMA_POST_FIFO( oven, &e_start, &panel );
			break;

#if ( __STOP_BUTTON__ == RKH_ENABLED )			
		case STOP_SW:
			RKH_SMA_POST_FIFO( oven, &e_stop, &panel );
			break;
#endif

		case DOOR_SW:
			if( debsw == SW_PRESS )
				RKH_SMA_POST_FIFO( oven, &e_close, &door );
			else
				RKH_SMA_POST_FIFO( oven, &e_open, &door );
			break;			
	}
}


void
rkh_tick( void* data )
{
	RKH_TIM_TICK((const void *)(rkh_tick));
}


void 
rkh_hook_timetick( void ) 
{
	switch_tick();
}


void 
rkh_hook_start( void ) 
{
}


void 
rkh_hook_exit( void ) 
{
	RKH_TRC_FLUSH();
}


void 
rkh_hook_idle( void )				/* called within critical section */
{
	RKH_ENA_INTERRUPT();
	RKH_TRC_FLUSH();
}


void 
rkh_assert( RKHROM char * const file, int line )
{
	(void)line;

	RKH_DIS_INTERRUPT();
	RKH_TR_FWK_ASSERT( (RKHROM char *)file, __LINE__ );
	rkh_fwk_exit();
	reset_now();
}


#if RKH_CFG_TRC_EN == RKH_ENABLED

void 
rkh_trc_open( void )
{
	rkh_trc_init();

	SERIAL_TRACE_OPEN();
	RKH_TRC_SEND_CFG( BSP_TS_RATE_HZ );
	RKH_TR_FWK_OBJ( &rkh_tick );
}


void 
rkh_trc_close( void )
{
	SERIAL_TRACE_CLOSE();
}


RKH_TS_T 
rkh_trc_getts( void )
{
	return ( RKH_TS_T )rkhtrc_lptmr_read();
}


void 
rkh_trc_flush( void )
{
	rui8_t *blk;
	TRCQTY_T nbytes;
	RKH_SR_ALLOC();

	FOREVER
	{
		nbytes = (TRCQTY_T)1024;

		RKH_ENTER_CRITICAL_();
		blk = rkh_trc_get_block( &nbytes );
		RKH_EXIT_CRITICAL_();

		if((blk != (rui8_t *)0))
		{
			SERIAL_TRACE_SEND_BLOCK( blk, nbytes );
		}
		else
			break;
	}	
}
#endif


void
bsp_door_open( void )
{
	set_rgb_led( RGB_BLACK );	
}


void
bsp_oven_init( void )
{

}


void
bsp_emitter_ready( void )
{
	set_rgb_led( RGB_LIME );
}


void
bsp_emitter_on( void )
{
	set_rgb_led( RGB_RED );
}


void
bsp_emitter_pause( void )
{
	set_rgb_led( RGB_YELLOW );
}


void
bsp_emitter_continue( void )
{
}


void
bsp_emitter_off( void )
{
	set_rgb_led( RGB_BLACK );
}


void 
bsp_init( int argc, char *argv[]  )
{
	rint cn;

	(void)argc;
	(void)argv;

    board_init();
    rkhtrc_lptmr_init();

	/* Systick initialization */
    HWTIMER_SYS_Init(&hwtimer, &kSystickDevif, 0, NULL);
    HWTIMER_SYS_SetPeriod(&hwtimer, (1000*1000)/RKH_CFG_FWK_TICK_RATE_HZ);
    HWTIMER_SYS_RegisterCallback(&hwtimer, rkh_tick, NULL);
    HWTIMER_SYS_Start(&hwtimer);

	rkh_fwk_init();

	RKH_FILTER_OFF_SMA( oven );
	RKH_FILTER_OFF_EVENT( RKH_TE_SMA_LIFO );
	RKH_FILTER_OFF_EVENT( RKH_TE_SMA_FIFO );
	RKH_FILTER_OFF_EVENT( RKH_TE_SMA_DCH );
	RKH_FILTER_OFF_EVENT( RKH_TE_SM_STATE );
//	RKH_FILTER_OFF_EVENT( RKH_TE_SM_TS_STATE );
	RKH_FILTER_OFF_EVENT( RKH_TE_FWK_DEFER );
	RKH_FILTER_OFF_EVENT( RKH_TE_FWK_RCALL );
//	RKH_FILTER_OFF_GROUP_ALL_EVENTS( RKH_TG_SM );

	RKH_FILTER_OFF_ALL_SIGNALS();

	RKH_TRC_OPEN();

#if defined( RKH_USE_TRC_SENDER )
	RKH_TR_FWK_OBJ( &panel );
	RKH_TR_FWK_OBJ( &door );
	RKH_TR_FWK_OBJ( &rkh_tick );
#endif	
}

