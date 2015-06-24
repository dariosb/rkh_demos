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

RKH_SMA_CREATE( OVEN_T, oven, 0, HCAL, &idle, oven_init, NULL );


/*
 *	Defines states and pseudostates.
 */

RKH_CREATE_BASIC_STATE( idle, NULL, NULL,  RKH_ROOT, NULL );
RKH_CREATE_TRANS_TABLE( idle )

	RKH_TRREG( CLOSE,	NULL,	NULL,	&ready ),

RKH_END_TRANS_TABLE


RKH_CREATE_BASIC_STATE( ready, NULL, NULL,  RKH_ROOT, NULL );
RKH_CREATE_TRANS_TABLE( ready )

	RKH_TRREG( OPEN,	NULL,	NULL,	&idle ),
	RKH_TRREG( START,	NULL,	NULL,	&cooking ),

RKH_END_TRANS_TABLE


RKH_CREATE_BASIC_STATE( cooking, cook_start, cook_stop,  RKH_ROOT, NULL );
RKH_CREATE_TRANS_TABLE( cooking )

	RKH_TRREG( OPEN,	NULL,	NULL,	&idle ),
	RKH_TRREG( TOUT,	NULL,	NULL,	&idle ),

RKH_END_TRANS_TABLE

