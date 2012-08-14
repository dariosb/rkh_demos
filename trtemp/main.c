/*
 *	file: main.c
 *	Last updated for version: 1.0.00
 *	Date of the last update:  May 20, 2012
 *	Contact information:
 *		e-mail:	dariosb@gmail.com
 */

/**
 * 	\file main.c
 *
 *	\brief
 *	Tracking Temperature Controler:
 *		RKH demo based on a real world experience, it show how RKH
 *		help solve common problems related to the embedded systems development.
 *		Refer to \Doc to find detailed information about this demo project.
 */


#include "rkh.h"
#include "rkhtrc.h"
#include "bsp.h"
#include "gmgr.h"
#include "tctrl.h"
#include "trk.h"


#define QGMGR_STO_SIZE	4

static RKHEVT_T *qe_gmgr[ QGMGR_STO_SIZE ];


#define QTCTRL_STO_SIZE	4

static RKHEVT_T *qe_tctrl[ QTCTRL_STO_SIZE ];


#define QTRK_STO_SIZE	4

static RKHEVT_T *qe_trk[ QTRK_STO_SIZE ];


void
trtemp_trace_filters( void )
{
	RKH_FILTER_ON_GROUP( RKH_TRC_ALL_GROUPS );
	RKH_FILTER_ON_EVENT( RKH_TRC_ALL_EVENTS );

	RKH_FILTER_OFF_GROUP_EVENT( RKH_TRCG_RKH, RKH_TRCE_OBJ );
	RKH_FILTER_OFF_GROUP_EVENT( RKH_TRCG_RKH, RKH_TRCE_SIG );	

	RKH_FILTER_OFF_GROUP_EVENT( RKH_TRCG_SM, RKH_TRCE_SM_DCH );
	RKH_FILTER_OFF_GROUP_EVENT( RKH_TRCG_SM, RKH_TRCE_SM_STATE );
#if 0
	RKH_FILTER_OFF_SMA( tctrl );
	RKH_FILTER_OFF_GROUP_EVENT( RKH_TRCG_SM, RKH_TRCE_SM_NENEX );
	RKH_FILTER_OFF_GROUP_EVENT( RKH_TRCG_SM, RKH_TRCE_SM_ENSTATE );
	RKH_FILTER_OFF_GROUP_EVENT( RKH_TRCG_SM, RKH_TRCE_SM_EXSTATE );
#endif
}


void
trtemp_trace_sigobj( void )
{
	/*
	 * Signals
	 */
	RKH_TRCR_RKH_SIG( TERM );
	RKH_TRCR_RKH_SIG( TSMP );
	RKH_TRCR_RKH_SIG( CMP_FAILURE );
	RKH_TRCR_RKH_SIG( CMP_FAILURE_RST );
	RKH_TRCR_RKH_SIG( SEND_EVT_REQ );
	RKH_TRCR_RKH_SIG( SEND_EVT_CFM );
	RKH_TRCR_RKH_SIG( SEND_EVT_REJ );
	RKH_TRCR_RKH_SIG( GPSFRM );
	RKH_TRCR_RKH_SIG( EPOS_TOUT );
	RKH_TRCR_RKH_SIG( ESTOP_TOUT );
	
	/*
	 * tctrl objects
	 */
	RKH_TRCR_RKH_OBJ( tctrl );
	RKH_TRCR_RKH_OBJ( &tctrl_ready );
	RKH_TRCR_RKH_OBJ( &tctrl_on_failure );
	RKH_TRCR_RKH_OBJ( &cmp_on );
	RKH_TRCR_RKH_OBJ( &cmp_off );
	
	/*
	 * trk objects
	 */
	RKH_TRCR_RKH_OBJ( trk );
	RKH_TRCR_RKH_OBJ( &gps_online );
	RKH_TRCR_RKH_OBJ( &gps_offline );
	RKH_TRCR_RKH_OBJ( &gps_stop );
	RKH_TRCR_RKH_OBJ( &gps_vmax );
	RKH_TRCR_RKH_OBJ( &gps_moving );

	/*
	 * gmgr objects
	 */
	RKH_TRCR_RKH_OBJ( gmgr );
	RKH_TRCR_RKH_OBJ( &gmgr_idle );
	RKH_TRCR_RKH_OBJ( &gmgr_in_progress );

}


int
main( int argc, char *argv[] )
{
	bsp_init( argc, argv );

	trtemp_trace_filters();

	rkh_init();

	RKH_TRC_OPEN();
	
	trtemp_trace_sigobj();

	rkh_sma_activate( gmgr, qe_gmgr, QGMGR_STO_SIZE, CV(0), 0 );
	rkh_sma_activate( tctrl, qe_tctrl, QTCTRL_STO_SIZE, CV(0), 0 );
	rkh_sma_activate( trk, qe_trk, QTRK_STO_SIZE, CV(0), 0 );

	rkh_enter();

	RKH_TRC_CLOSE();

	return 0;
}
