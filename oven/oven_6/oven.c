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

RKH_SMA_CREATE( OVEN_T, oven, 0, HCAL, &open, oven_init, NULL );


/*
 *	Defines states and pseudostates.
 */

RKH_CREATE_BASIC_STATE( open, NULL, NULL,  RKH_ROOT, NULL );
RKH_CREATE_TRANS_TABLE( open )

	RKH_TRREG( CLOSE,	NULL,	NULL,	&close_hist ),

RKH_END_TRANS_TABLE


RKH_CREATE_COMP_STATE( close, NULL, NULL,  RKH_ROOT, &ready, &close_hist );
RKH_CREATE_TRANS_TABLE( close )
	
	RKH_TRREG( OPEN,	NULL,	NULL,	&open ),

RKH_END_TRANS_TABLE


RKH_CREATE_SHALLOW_HISTORY_STATE( close_hist, &close );


RKH_CREATE_BASIC_STATE( ready, NULL, NULL,  &close, NULL );
RKH_CREATE_TRANS_TABLE( ready )

	RKH_TRREG( START,	NULL,	NULL,	&cooking ),

RKH_END_TRANS_TABLE


RKH_CREATE_COMP_STATE( cooking, NULL, NULL,  &close, &on, NULL );
RKH_CREATE_TRANS_TABLE( cooking )

	RKH_TRREG( TOUT,	NULL,		recall_evts,	&ready ),

RKH_END_TRANS_TABLE


RKH_CREATE_BASIC_STATE( on, start_cooking, stop_cooking,  &cooking, NULL );
RKH_CREATE_TRANS_TABLE( on )

	RKH_TRREG( START,	NULL,	inc_start,		&cooking_cnd ),

RKH_END_TRANS_TABLE


RKH_CREATE_COND_STATE( cooking_cnd );
RKH_CREATE_BRANCH_TABLE( cooking_cnd )

	RKH_BRANCH( chk_restart_cnt,	defer_start,	&on ),
	RKH_BRANCH( ELSE, 				NULL,			&off ),

RKH_END_BRANCH_TABLE


RKH_CREATE_BASIC_STATE( off, NULL, NULL,  &cooking, NULL );
RKH_CREATE_TRANS_TABLE( off )


RKH_END_TRANS_TABLE

