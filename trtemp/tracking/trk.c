/*
 *	file: trk.c
 *	Last updated for version: 1.0.00
 *	Date of the last update:  May 20, 2012
 *	Contact information:
 *		e-mail:	dariosb@gmail.com
 */

/**
 * 	\file trk.c
 *
 *	\brief
 *	Tracking AO:
 *		- Handle GPS status change.
 *		- Post detention and max vel exceed events.
 *
 */

#include "rkh.h"


/*
 *	Include file of event definitions.
 */

#include "trtemp.h"


/*
 *	Include file of SMA definitions.
 */

#include "trk.h"


/*
 *	Include file of action/guard definitions
 */

#include "trkact.h"


/*
 *	Defines SMA "trk".
 */

RKH_SMA_CREATE( RKHSMA_T, 0, trk, TRK_PRIO, HCAL, &gps_offline, trk_init, NULL );


/*
 *	Defines states and pseudostates
 */

RKH_CREATE_BASIC_STATE( gps_offline, 1, NULL, NULL, RKH_ROOT, NULL );
RKH_CREATE_TRANS_TABLE( gps_offline )

	RKH_TRREG( GPSFRM, 	is_online, 	set_curr_pos,	&gps_online ),
	
RKH_END_TRANS_TABLE


RKH_CREATE_COMP_STATE( gps_online, 1, start_epos_tmr, stop_epos_tmr, RKH_ROOT, &gps_stop, NULL );
RKH_CREATE_TRANS_TABLE( gps_online )

	RKH_TRINT( EPOS_TOUT, 	NULL, 	send_curr_pos ),

	RKH_TRREG( GPSFRM, 		NULL, 	NULL,	&gps_chk_online ),

RKH_END_TRANS_TABLE


RKH_CREATE_BASIC_STATE( gps_stop, 1, start_estop_tmr, stop_estop_tmr, &gps_online, NULL );
RKH_CREATE_TRANS_TABLE( gps_stop )

	RKH_TRINT( ESTOP_TOUT, 	NULL, 	send_in_stop ),

RKH_END_TRANS_TABLE


RKH_CREATE_BASIC_STATE( gps_vmax, 1, send_vmax_limit, NULL, &gps_online, NULL );
RKH_CREATE_TRANS_TABLE( gps_vmax )

RKH_END_TRANS_TABLE


RKH_CREATE_BASIC_STATE( gps_moving, 1, NULL, NULL, &gps_online, NULL );
RKH_CREATE_TRANS_TABLE( gps_moving )

RKH_END_TRANS_TABLE


RKH_CREATE_COND_STATE( gps_chk_online, 6 );
RKH_CREATE_BRANCH_TABLE( gps_chk_online )

	RKH_BRANCH( is_online, 	upd_curr_pos,	&gps_chk_vmax ),
	RKH_BRANCH( ELSE, 		rel_curr_pos,	&gps_offline ),

RKH_END_BRANCH_TABLE


RKH_CREATE_COND_STATE( gps_chk_vmax, 6 );
RKH_CREATE_BRANCH_TABLE( gps_chk_vmax )

	RKH_BRANCH( in_stop, 	NULL,		&gps_stop ),
	RKH_BRANCH( is_vmax, 	NULL,		&gps_vmax ),
	RKH_BRANCH( ELSE, 		NULL,		&gps_moving ),

RKH_END_BRANCH_TABLE

