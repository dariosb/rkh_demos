/*
 *	oven.c
 */


#include "rkh.h"


/*
 *	Include file of HSM definitions.
 */

#include "oven.h"


/*
 *	Include file of signals definitions
 */

#include "ovenevt.h"


/*
 *	Include file of action/guard definitions
 */

#include "ovenact.h"


/*
 *	Defines SMA (Active Object) "oven".
 */

RKH_SMA_CREATE( OVEN_T, oven, 0, HCAL, &opened, oven_init, NULL );


/*
 *	Defines states and pseudostates.
 */

RKH_CREATE_BASIC_STATE( opened, door_open, NULL,  RKH_ROOT, NULL );
RKH_CREATE_TRANS_TABLE( opened )

	RKH_TRREG( CLOSE,	NULL,	NULL,	&close_hist ),

RKH_END_TRANS_TABLE


RKH_CREATE_COMP_STATE( closed, NULL, NULL,  RKH_ROOT, &ready, &close_hist );
RKH_CREATE_TRANS_TABLE( closed )
	
	RKH_TRREG( OPEN,	NULL,	NULL,	&opened ),

RKH_END_TRANS_TABLE


RKH_CREATE_SHALLOW_HISTORY_STATE( close_hist, &closed );


RKH_CREATE_BASIC_STATE( ready, cook_ready, NULL,  &closed, NULL );
RKH_CREATE_TRANS_TABLE( ready )

	RKH_TRREG( START,	NULL,	NULL,	&cooking ),

RKH_END_TRANS_TABLE

RKH_CREATE_COMP_STATE( cooking, cook_start, cook_stop,  &closed, &on, &close_hist );
RKH_CREATE_TRANS_TABLE( cooking )
	
	RKH_TRREG( OPEN,	NULL,	NULL,	&opened ),

RKH_END_TRANS_TABLE


RKH_CREATE_BASIC_STATE( on, tmr_start, tmr_stop,  &cooking, NULL );
RKH_CREATE_TRANS_TABLE( on )

	RKH_TRINT( START,	chk_room_dfq,	defer_evt ),
	RKH_TRREG( STOP,	NULL,	NULL,	&paused ),
	RKH_TRREG( TMREVT,	NULL,	NULL,	&cstart ),

RKH_END_TRANS_TABLE

RKH_CREATE_COND_STATE( cstart );
RKH_CREATE_BRANCH_TABLE( cstart )

	RKH_BRANCH( chk_dfq, 	NULL,	&wstart ),
	RKH_BRANCH( ELSE,		NULL,	&ready ),

RKH_END_BRANCH_TABLE


RKH_CREATE_BASIC_STATE( wstart, NULL, NULL,  &cooking, NULL );
RKH_CREATE_TRANS_TABLE( wstart )

	RKH_TRREG( START,	NULL,	NULL,	&on ),

RKH_END_TRANS_TABLE


RKH_CREATE_BASIC_STATE( paused, cook_pause, NULL,  &cooking, NULL );
RKH_CREATE_TRANS_TABLE( paused )

	RKH_TRREG( START,	NULL,	cook_continue,	&on ),
	RKH_TRREG( STOP,	NULL,	NULL,			&ready ),

RKH_END_TRANS_TABLE

