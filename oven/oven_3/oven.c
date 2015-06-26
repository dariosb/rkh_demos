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

	RKH_TRREG( CLOSE,	NULL,	NULL,	&closed ),

RKH_END_TRANS_TABLE


RKH_CREATE_COMP_STATE( closed, NULL, NULL,  RKH_ROOT, &ready, &close_hist );
RKH_CREATE_TRANS_TABLE( closed )
	
	RKH_TRREG( OPEN,	NULL,	NULL,	&opened ),

RKH_END_TRANS_TABLE


RKH_CREATE_BASIC_STATE( ready, cook_ready, NULL,  &closed, NULL );
RKH_CREATE_TRANS_TABLE( ready )

	RKH_TRREG( START,	NULL,	NULL,	&cooking ),

RKH_END_TRANS_TABLE


RKH_CREATE_BASIC_STATE( cooking, cook_start, cook_stop,  &closed, NULL );
RKH_CREATE_TRANS_TABLE( cooking )

	RKH_TRINT( START,	NULL,	cook_restart ),
	RKH_TRREG( TOUT,	NULL,	NULL,	&ready ),

RKH_END_TRANS_TABLE

