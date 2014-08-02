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
 * 	\brief 		BSP for TWR-K60D100M IAR V6.5
 */

#include "bsp.h"
#include "rkh.h"
#include "ovenevt.h"
#include "oven.h"

#include "cpu.h"
#include "gpio.h"
#include "kuart.h"

#include "switch.h"


#define SERIAL_TRACE			1

#define SIZEOF_EP0STO				32
#define SIZEOF_EP0_BLOCK			sizeof( RKH_EVT_T )
#define SIZEOF_EP1STO				16
#define SIZEOF_EP1_BLOCK			sizeof( REQ_EVT_T )


RKH_THIS_MODULE


static RKH_ROM_STATIC_EVENT( e_start, START );
static RKH_ROM_STATIC_EVENT( e_open, OPEN );
static RKH_ROM_STATIC_EVENT( e_close, CLOSE );

static rbool_t sw2_tgl;

#if defined( RKH_USE_TRC_SENDER )
static rui8_t l_isr_switch;
#endif


/*
 * 	For serial trace feature.
 */

#if SERIAL_TRACE == 1

	static const KUARTPP_ST trz_uart = 
	{
		115200, 0, 1, KUART_HFC_DISABLE, NULL
	};

	/* Trazer Tool COM Port */
	#define SERIAL_TRACE_OPEN()		kuart_init( UART3_BASE_PTR, &trz_uart )
	#define SERIAL_TRACE_CLOSE() 	(void)0
	#define SERIAL_TRACE_SEND( d ) 	kuart_putchar( UART3_BASE_PTR, d )
	#define SERIAL_TRACE_SEND_BLOCK( buf_, len_ ) 		\
					kuart_putnchar( UART3_BASE_PTR, 	\
								(char *)(buf_), 		\
								(rui16_t)(len_))
#else
	#define SERIAL_TRACE_OPEN()						(void)0
	#define SERIAL_TRACE_CLOSE()					(void)0
	#define SERIAL_TRACE_SEND( d )					(void)0
	#define SERIAL_TRACE_SEND_BLOCK( buf_, len_ )	(void)0
#endif


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
	RKH_DIS_INTERRUPT();
	RKH_TR_FWK_ASSERT( (RKHROM char *)file, line );
	rkh_fwk_exit();
	reset_now();
}


#if RKH_CFG_TRC_EN == 1

void 
rkh_trc_open( void )
{
	rkh_trc_init();

	SERIAL_TRACE_OPEN();
	RKH_TRC_SEND_CFG( BSP_TS_RATE_HZ );
}


void 
rkh_trc_close( void )
{
	SERIAL_TRACE_CLOSE();
}


RKH_TS_T 
rkh_trc_getts( void )
{
	return ( RKH_TS_T )get_ts();
}


void 
rkh_trc_flush( void )
{
	rui8_t *blk;
	TRCQTY_T nbytes;
	RKH_SR_ALLOC();

	FOREVER
	{
		nbytes = 128;

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
bsp_switch_evt( rui8_t s, rui8_t st )
{
	if( st == SW_RELEASED )
		return;

	switch(s)
	{
		case SW1_SWITCH:
		  RKH_SMA_POST_FIFO( oven, &e_start, &l_isr_switch );
		  break;

		case SW2_SWITCH:
		  tgl_gpio( LED3 );
		  RKH_SMA_POST_FIFO( oven, 
				  ( sw2_tgl ^= 1 ) ? &e_close : &e_open, &l_isr_switch );
		  break;
	} 
}


void
bsp_oven_init( void )
{
}


void
bsp_emitter_on( void )
{
	clr_gpio( LED1 );
}


void
bsp_emitter_off( void )
{
	set_gpio( LED1 );
}


void 
bsp_init( int argc, char *argv[]  )
{
	(void)argc;
	(void)argv;

	cpu_init();
	systick_init( RKH_CFG_FWK_TICK_RATE_HZ );
	cpu_tstmr_init();
	init_ioports();

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
	RKH_TR_FWK_OBJ( &l_isr_switch );
#endif
    RKH_ENA_INTERRUPT();
}




