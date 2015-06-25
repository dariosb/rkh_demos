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

RKH_CREATE_BASIC_STATE( opened, NULL, NULL,  RKH_ROOT, NULL );
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


RKH_CREATE_BASIC_STATE( cooking, cook_start, cook_stop,  &closed, NULL );
RKH_CREATE_TRANS_TABLE( cooking )

	RKH_TRINT( START,	chk_start,		inc_start ),
	RKH_TRREG( TOUT,	NULL,	NULL,		&cooking_cnd ),

RKH_END_TRANS_TABLE

RKH_CREATE_COND_STATE( cooking_cnd );
RKH_CREATE_BRANCH_TABLE( cooking_cnd )

	RKH_BRANCH( chk_restart, 	NULL,			&ready ),
	RKH_BRANCH( ELSE,			cook_restart,	&cooking ),

RKH_END_BRANCH_TABLE
