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

	RKH_TRREG( CLOSE,	NULL,	NULL,	&close ),

RKH_END_TRANS_TABLE


RKH_CREATE_COMP_STATE( close, NULL, NULL,  RKH_ROOT, &ready, &close_hist );
RKH_CREATE_TRANS_TABLE( close )
	
	RKH_TRREG( OPEN,	NULL,	NULL,	&open ),

RKH_END_TRANS_TABLE


RKH_CREATE_BASIC_STATE( ready, cook_ready, NULL,  &close, NULL );
RKH_CREATE_TRANS_TABLE( ready )

	RKH_TRREG( START,	NULL,	NULL,	&cooking ),

RKH_END_TRANS_TABLE


RKH_CREATE_BASIC_STATE( cooking, cook_start, cook_stop,  &close, NULL );
RKH_CREATE_TRANS_TABLE( cooking )

	RKH_TRINT( START,	NULL,	cook_restart ),
	RKH_TRREG( TOUT,	NULL,	NULL,	&ready ),

RKH_END_TRANS_TABLE

