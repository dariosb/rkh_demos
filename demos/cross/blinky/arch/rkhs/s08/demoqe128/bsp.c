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
 * 	\brief 		BSP for DemoQE128 CW6.3
 */


#include "bsp.h"
#include "blinky.h"
#include "rkh.h"

#include "mcu.h"
#include "gpio.h"
#include "serial.h"


#define SERIAL_TRACE			1


RKH_THIS_MODULE

				
/*
 * 	For serial trace feature.
 */

#if SERIAL_TRACE == 1

	/* Trazer Tool COM Port */
	#define TRC_COM_PORT		COM1	

	#define SERIAL_TRACE_OPEN()		serial_init( TRC_COM_PORT )
	#define SERIAL_TRACE_CLOSE() 	(void)0
	#define SERIAL_TRACE_SEND( d ) 	put_char( TRC_COM_PORT, d )
	#define SERIAL_TRACE_SEND_BLOCK( buf_, len_ ) 							\
					put_nchar( 	TRC_COM_PORT, 								\
								(const unsigned char *)(buf_), 				\
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
bsp_init( int argc, char *argv[]  )
{
	(void)argc;
	(void)argv;
	
	mcu_init( RKH_TICK_RATE_MS );
	gpio_init();

	rkh_fwk_init();

	RKH_FILTER_ON_GROUP( RKH_TRC_ALL_GROUPS );
	RKH_FILTER_ON_EVENT( RKH_TRC_ALL_EVENTS );
	RKH_FILTER_OFF_EVENT( RKH_TE_TMR_TOUT );
	RKH_FILTER_OFF_EVENT( RKH_TE_SM_STATE );
	RKH_FILTER_OFF_SMA( blinky );
	RKH_FILTER_OFF_ALL_SIGNALS();

	RKH_TRC_OPEN();
	
	RKH_ENA_INTERRUPT();
}


void 
bsp_led_on( void )
{
	set_iopin( LED1, PIN_LOW );
}


void 
bsp_led_off( void )
{
	set_iopin( LED1, PIN_HIGH );
}
