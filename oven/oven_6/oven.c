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


RKH_CREATE_BASIC_STATE( ready, cook_init, NULL,  &close, NULL );
RKH_CREATE_TRANS_TABLE( ready )

	RKH_TRREG( START,	NULL,	NULL,	&cooking ),

RKH_END_TRANS_TABLE


RKH_CREATE_COMP_STATE( cooking, NULL, NULL,  &close, &on, NULL );
RKH_CREATE_TRANS_TABLE( cooking )

	RKH_TRREG( STOP,	NULL,	NULL,	&ready ),
	RKH_TRREG( TOUT,	NULL,	NULL,	&cooking_cnd ),

RKH_END_TRANS_TABLE


RKH_CREATE_BASIC_STATE( on, cook_start, cook_stop,  &cooking, NULL );
RKH_CREATE_TRANS_TABLE( on )

	RKH_TRINT( START,	chk_start_cnt,	inc_start ),
	RKH_TRREG( STOP,	NULL,	NULL,	&pause ),

RKH_END_TRANS_TABLE


RKH_CREATE_BASIC_STATE( pause, cook_pause, cook_continue,  &cooking, NULL );
RKH_CREATE_TRANS_TABLE( pause )

	RKH_TRREG( START,	NULL,	NULL,	&on ),

RKH_END_TRANS_TABLE


RKH_CREATE_COND_STATE( cooking_cnd );
RKH_CREATE_BRANCH_TABLE( cooking_cnd )

	RKH_BRANCH( chk_restart, 	NULL,			&ready ),
	RKH_BRANCH( ELSE,			cook_restart,	&on ),

RKH_END_BRANCH_TABLE


