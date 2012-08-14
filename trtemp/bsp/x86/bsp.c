/*
 *	file: bsp.c
 *	Last updated for version: 2.0
 *	Date of the last update:  Feb 28, 2012
 *	Contact information:
 *		e-mail:	dariosb@gmail.com
 */


#include "bsp.h"
#include "keymap.h"
#include "trtemp.h"
#include "rkh.h"
#include "tmp.h"
#include "gps.h"
#include "gprs.h"
#include "gmgr.h"
#include "trk.h"
#include "tctrl.h"
#include "critical.h"
#include "debug.h"

#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


/*
 * Tracing options
 */

#define BIN_TRACE		0
#define SOCKET_TRACE	1


/*
 * BSP dynamic memory definitions
 */

#define SIZEOF_EP0_BLOCK		sizeof(EGPSFRM_T)
#define SIZEOF_EP0STO			(8 * sizeof(EGPSFRM_T))

#define SIZEOF_EP1_BLOCK		sizeof(SEND_EVT_REQ_T)
#define EP1_GUARD				3
#define SIZEOF_EP1STO			((EMGR_MAX_DEFER_EVENT+EP1_GUARD)*sizeof(SEND_EVT_REQ_T))


RKH_THIS_MODULE

static DWORD tick_msec;			/* clock tick in msec */
rkhui8_t running;
static RKH_DCLR_STATIC_EVENT( e_term, TERM );
static rkhui8_t ep0sto[ SIZEOF_EP0STO ],
				ep1sto[ SIZEOF_EP1STO ];

CRITICAL_SECTION trt_crt_sec;	/* critical section for this demo aplication */


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

	#define TCP_TRACE_OPEN() \
				if( tcp_trace_open( TRC_TCP_PORT, \
							TRC_IP_ADDR, &tsock ) < 0 ) \
				{ \
					printf( "Can't open socket %s:%u\n", \
								TRC_IP_ADDR, TRC_TCP_PORT ); \
					exit( EXIT_FAILURE ); \
				}
	#define TCP_TRACE_CLOSE() \
				tcp_trace_close( tsock )
	#define TCP_TRACE_SEND( d ) \
				tcp_trace_send( tsock, d )
#else
	#define TCP_TRACE_OPEN()		(void)0
	#define TCP_TRACE_CLOSE()		(void)0
	#define TCP_TRACE_SEND( d )		(void)0
#endif


#if BIN_TRACE == 1
	#define FTBIN_FLUSH( d )				\
				fwrite ( d, 1, 1, ftbin );	\
				fflush( ftbin )
	#define FTBIN_CLOSE() \
				fclose( ftbin )
	#define FTBIN_OPEN() \
				if( ( ftbin = fopen( "../ftbin", "w+b" ) ) == NULL ) \
				{ \
					perror( "Can't open file\n" ); \
					exit( EXIT_FAILURE ); \
				}
#else
	#define FTBIN_FLUSH( d )		(void)0
	#define FTBIN_CLOSE()			(void)0
	#define FTBIN_OPEN()			(void)0
#endif


#define PRINT_STIMULUS_BAR()	printf( "%s\tParametric Variables\n" \
										"%s\t--------------------\n\n", \
										DBG_OFFSET, DBG_OFFSET )	

#define PRINT_GPRS_BAR()		printf( "\tGPRS LINK REPORT LOG\n" 				 \
										"#TStamp - Event Type: Event Data\n" \
										"-------------------------------------------------------\n\n" ) 

static
void
print_help( void )
{
	printf(	"\nKeyboard Reference: \n"
			"\n"
			"   Temperature\n"
			"     -Rgt: Increment Temperature\n"
			"     -Lft: Decrement Temperature\n"
			"     -c:   Switch compresor status Ready/Failure\n"
			"\n"
			"   GPS\n"
			"     -Up: Increment Velocity\n"
			"     -Dw: Decrement Velocity\n"
			"     -g:  Switch GPS satellites coverage\n"
			"\n"
			"   GPRS\n"
			"     -l: Switch GPRS Link status OK/Broken\n"
			"\n"
			"     -h: Print this reference\n"
			"\n\n" );

	PRINT_GPRS_BAR();

	PRINT_STIMULUS_BAR();
}


static 
DWORD WINAPI 
isr_tmr_thread( LPVOID par )	/* Win32 thread to emulate timer ISR */
{
    ( void )par;
    while( running ) 
	{
		rkh_tim_tick();
		tmp_isr();
		gps_isr();
		gprs_isr();
        Sleep( tick_msec );
    }
    return 0;
}


static 
DWORD WINAPI 
isr_kbd_thread( LPVOID par )	/* Win32 thread to emulate keyboard ISR */
{
    ( void )par;

    while( running ) 
	{
		switch( toupper( _getch() ) )
		{
			case ESC_CODE:

				switch ( _getch() )
				{
					case TMP_UP:
						tmp_inc();	
						break;

					case TMP_DW:
						tmp_dec();	
						break;

					case VEL_UP:
						vel_inc();	
						break;

					case VEL_DW:
						vel_dec();	
						break;
				}
				break;
			
			case GPRS_LINK:
				gprs_link_chg();
				break;

			case COMP_STATE:
				cmp_status_chg();
				break;

			case GPS_SATS:
				gps_sats_chg();
				break;

			case HLP_KEY:
				print_help();
				break;

			case EXIT_KEY:
				rkh_sma_post_fifo( gmgr, &e_term );
				break;

			default:
				break;
		}
    }
    return 0;
}


void 
rkh_hk_start( void ) 
{
    DWORD thtmr_id, thkbd_id;
    HANDLE hth_tmr, hth_kbd;

	/* set the desired tick rate */
    tick_msec = 1000UL/BSP_TICKS_PER_SEC;
    running = (rkhui8_t)1;
	
	/* create the ISR timer thread */
    hth_tmr = CreateThread( NULL, 1024, &isr_tmr_thread, 0, 0, &thtmr_id );
    RKHASSERT( hth_tmr != (HANDLE)0 );
    SetThreadPriority( hth_tmr, THREAD_PRIORITY_TIME_CRITICAL );

	/* create the ISR keyboard thread */
    hth_kbd = CreateThread( NULL, 1024, &isr_kbd_thread, 0, 0, &thkbd_id );
    RKHASSERT( hth_kbd != (HANDLE)0 );
    SetThreadPriority( hth_kbd, THREAD_PRIORITY_NORMAL );
	
	rkh_epool_register( ep0sto, SIZEOF_EP0STO, SIZEOF_EP0_BLOCK  );
	rkh_epool_register( ep1sto, SIZEOF_EP1STO, SIZEOF_EP1_BLOCK  );
}


void 
rkh_hk_exit( void ) 
{
	RKH_TRC_FLUSH();
    running = 0;
}


void 
rkh_hk_idle( void )				/* called within critical section */
{
    RKH_EXIT_CRITICAL( dummy );
	RKH_TRC_FLUSH();
    RKH_WAIT_FOR_EVENTS();		/* yield the CPU until new event(s) arrive */
}


void 
rkh_assert( RKHROM char * const file, int line )
{
	fprintf( stderr,	"RKHASSERT: [%d] line from %s "
						"file\n", line, file );
	__debugbreak();
	rkh_exit();
}


static
void
print_banner( void )
{
	printf(	"RKH Demo: Tracking Tempereature Controller\n\n" );
	printf(	"RKH version      = %s\n", RKH_RELEASE );
	printf(	"Port version     = %s\n", rkh_get_port_version() );
	printf(	"Port description = %s\n\n", rkh_get_port_desc() );
	printf(	"Description: \n\n"
			"RKH demo based on a real world experience, it show how RKH\n"
			"help solve common problems related to the embedded systems development.\n"
			"\\Doc Directory contain detailed information about this demo project.\n"
			"\n\n" );
}

static
void
print_settings( void )
{
	printf(	"Predefined Demo Settings: \n\n" );
	printf(	" Temperature Controller\n" );
	printf( "   T Max Threshold [C]: %d\n", TCTRL_TMP_HIGH_TH );
	printf( "   T Min Threshold [C]: %d\n", TCTRL_TMP_LOW_TH );
	printf(	" Tracking Controller\n" );
	printf( "   V Max Threshold [Km/h]: %d\n", TRK_MAX_VELOCITY );
	printf( "   V Min Threshold [Km/h]: %d\n", TRK_MIN_VELOCITY );
	printf( "   Position Period [ms]:   %d\n", TRK_POS_PRD );
	printf( "   Max Detention [ms]:     %d\n", TRK_STOP_TIME );
	printf( "\n\n" );
}


#if RKH_TRC_EN == 1

void 
rkh_trc_open( void )
{
	rkh_trc_init();
	rkh_trc_control( RKH_TRC_START );

	FTBIN_OPEN();
	TCP_TRACE_OPEN();
}


void 
rkh_trc_close( void )
{
	FTBIN_CLOSE();
	TCP_TRACE_CLOSE();
}


RKHTS_T 
rkh_trc_getts( void )
{
	return ( RKHTS_T )clock();
}


void 
rkh_trc_flush( void )
{
	rkhui8_t *d;

	while( ( d = rkh_trc_get() ) != ( rkhui8_t* )0 )
	{
		FTBIN_FLUSH( d );
		TCP_TRACE_SEND( *d );		
	}
}

#endif


void 
bsp_init( int argc, char *argv[] )
{
	(void)argc;
	(void)argv;

	srand( ( unsigned )time( NULL ) );

	init_critical();
	print_banner();
	print_settings();
	print_help();
}
