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
 *	By                       : LF
 *  --------------------------------------------------------------------------
 *  \endcond
 *
 * 	\file
 * 	\ingroup 	prt
 *
 * 	\brief 		BSP for 80x86 OS win32
 */


#include "bsp.h"
#include "rkh.h"
#include "oven.h"
#include "ovenevt.h"

#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define BIN_TRACE					0
#define SOCKET_TRACE				1
#define ESC							0x1B


RKH_THIS_MODULE

static DWORD tick_msec;			/* clock tick in msec */
static RKH_TS_T ts_cntr;		/* time stamp counter */

rui8_t running;

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
static rui8_t rkh_tick;
#endif


/* 
 * 	For binary trace feature.
 */

#if BIN_TRACE == 1
static FILE *ftbin;
#endif


/*
 * 	For socket trace feature.
 */

#if SOCKET_TRACE == 1

	#include "tcptrc.h"

	/* Trazer Tool IP Address */
	#define TRC_IP_ADDR					"127.0.0.1"

	/* Trazer Tool TCP Port Address */
	#define TRC_TCP_PORT				6602

	/* Trace Socket */
	static SOCKET tsock;

	#define TCP_TRACE_OPEN() 									\
				if( tcp_trace_open( TRC_TCP_PORT,				\
							TRC_IP_ADDR, &tsock ) < 0 ) 		\
				{ 												\
					printf( "Can't open socket %s:%u\n", 		\
								TRC_IP_ADDR, TRC_TCP_PORT );	\
					exit( EXIT_FAILURE ); 						\
				}
	#define TCP_TRACE_CLOSE() 		tcp_trace_close( tsock )
	#define TCP_TRACE_SEND( d ) 	tcp_trace_send( tsock, d, (int)1 )
	#define TCP_TRACE_SEND_BLOCK( buf_, len_ ) 					\
				tcp_trace_send( tsock, (const char *)(buf_), (int)(len_) )
#else
	#define TCP_TRACE_OPEN()					(void)0
	#define TCP_TRACE_CLOSE()					(void)0
	#define TCP_TRACE_SEND( d )					(void)0
	#define TCP_TRACE_SEND_BLOCK( buf_, len_ )	(void)0
#endif


#if BIN_TRACE == 1
	#define FTBIN_FLUSH( buf_, len_ ) 						\
				{											\
					fwrite ( (buf_), 1, (len_), ftbin );	\
					fflush( ftbin )							\
				}
	#define FTBIN_CLOSE() 	fclose( ftbin )
	#define FTBIN_OPEN() 												\
				if( ( ftbin = fopen( "../ftbin", "w+b" ) ) == NULL )	\
				{														\
					perror( "Can't open file\n" );						\
					exit( EXIT_FAILURE );								\
				}
#else
	#define FTBIN_FLUSH( buf_, len_ )		(void)0
	#define FTBIN_CLOSE()					(void)0
	#define FTBIN_OPEN()					(void)0
#endif


static 
DWORD WINAPI 
isr_tmr_thread( LPVOID par )	/* Win32 thread to emulate timer ISR */
{
    ( void )par;
    while( running ) 
	{
		RKH_TIM_TICK( &rkh_tick );
        Sleep( tick_msec );
    }
    return 0;
}


static 
DWORD WINAPI 
isr_kbd_thread( LPVOID par )	/* Win32 thread to emulate keyboard ISR */
{
	int c;

    ( void )par;
    while( running ) 
	{
		c = _getch();
		
		switch( tolower(c) )
		{
			case ESC:
				running = 0;
				RKH_SMA_POST_FIFO( oven, &e_term, &panel );
				break;

			case 's':
				RKH_SMA_POST_FIFO( oven, &e_start, &panel );
				break;

#if ( __STOP_BUTTON__ == RKH_ENABLED )
			case 'p':
				RKH_SMA_POST_FIFO( oven, &e_stop, &panel );
				break;
#endif

			case 'o':
				printf( "- Open  ->\n" );
				RKH_SMA_POST_FIFO( oven, &e_open, &door );
				break;

			case 'c':
				printf( "- Close ->\n" );
				RKH_SMA_POST_FIFO( oven, &e_close, &door );
				break;

			default:
				break;
		}
    }
    return 0;
}


void
rkh_hook_timetick( void )
{
	++ts_cntr;
}


void 
rkh_hook_start( void ) 
{
    DWORD thtmr_id, thkbd_id;
    HANDLE hth_tmr, hth_kbd;

	/* set the desired tick rate */
    tick_msec = 1000UL/BSP_TICKS_PER_SEC;
	ts_cntr = 0;
    running = (rui8_t)1;
	
	/* create the ISR timer thread */
    hth_tmr = CreateThread( NULL, 1024, &isr_tmr_thread, 0, 0, &thtmr_id );
    RKH_ASSERT( hth_tmr != (HANDLE)0 );
    SetThreadPriority( hth_tmr, THREAD_PRIORITY_TIME_CRITICAL );

	/* create the ISR keyboard thread */
    hth_kbd = CreateThread( NULL, 1024, &isr_kbd_thread, 0, 0, &thkbd_id );
    RKH_ASSERT( hth_kbd != (HANDLE)0 );
    SetThreadPriority( hth_kbd, THREAD_PRIORITY_NORMAL );
}


void 
rkh_hook_exit( void ) 
{
	RKH_TRC_FLUSH();
}


void 
rkh_hook_idle( void )				/* called within critical section */
{
    RKH_EXIT_CRITICAL( dummy );
	RKH_TRC_FLUSH();
    RKH_WAIT_FOR_EVENTS();		/* yield the CPU until new event(s) arrive */
}


void 
rkh_assert( RKHROM char * const file, int line )
{
	fprintf( stderr,	"RKH_ASSERT: [%d] line from %s "
						"file\n", line, file );
	RKH_TRC_FLUSH();
	RKH_DIS_INTERRUPT();
	RKH_TR_FWK_ASSERT( (RKHROM char *)file, __LINE__ );
	__debugbreak();
	rkh_fwk_exit();
}


static
void
print_banner( void )
{
	printf(	"\"oven\" example\n\n" );
	printf(	"RKH version      = %s\n", RKH_RELEASE );
	printf(	"Port version     = %s\n", rkh_get_port_version() );
	printf(	"Port description = %s\n\n", rkh_get_port_desc() );
	printf(	"\n\n" );

	printf( "1.- Press 'O'/'o' door { Open  } -> oven.\n" );
	printf( "2.- Press 'C'/'c' door { Close } -> oven.\n" );
	printf( "3.- Press 'S'/'s' panel{ Start } -> oven.\n" );
#if ( __STOP_BUTTON__ == RKH_ENABLED )
	printf( "3.- Press 'P'/'p' panel{ Stop  } -> oven.\n" );
#endif
	printf( "4.- Press 'escape' to quit.\n\n\n" );
}


#if RKH_CFG_TRC_EN == 1

void 
rkh_trc_open( void )
{
	rkh_trc_init();

	FTBIN_OPEN();
	TCP_TRACE_OPEN();
	RKH_TRC_SEND_CFG( BSP_TS_RATE_HZ );
}


void 
rkh_trc_close( void )
{
	FTBIN_CLOSE();
	TCP_TRACE_CLOSE();
}


RKH_TS_T 
rkh_trc_getts( void )
{
	return ( RKH_TS_T )ts_cntr;
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
			FTBIN_FLUSH( blk, nbytes );
			TCP_TRACE_SEND_BLOCK( blk, nbytes );
		}
		else
			break;
	}
}
#endif


static time_t cStart, cStop;

void
bsp_oven_init( void )
{
	printf( " Oven is running\n\n" );
}


void
bsp_emitter_ready( void )
{
	printf( "+- Cook Ready \n" );
}

void
bsp_emitter_on( void )
{
	time(&cStart);
	printf( "     Emitter: ON\n" );
}


void
bsp_emitter_pause( void )
{
	printf( "   Paused\n" );
}


void
bsp_emitter_continue( void )
{
	printf( "   Continue\n" );
}


void
bsp_emitter_off( void )
{
	time(&cStop);
	printf( "     Emitter: OFF\n" );
	printf( "     Cook Time: %5.2f sec\n", difftime(cStop, cStart) );
}


void 
bsp_init( int argc, char *argv[] )
{
	(void)argc;
	(void)argv;

	print_banner();
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
