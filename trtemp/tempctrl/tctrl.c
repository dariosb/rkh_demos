/*
 *	file: tctrl.c
 *	Last updated for version: 1.0.00
 *	Date of the last update:  May 20, 2012
 *	Contact information:
 *		e-mail:	dariosb@gmail.com
 */

/**
 * 	\file tctrl.c
 *
 *	\brief
 *	Temperature Control AO:
 *		- Simple ON/OFF Temperature Controller.
 *		- Publish refrigerator state on change.
 */

#include "rkh.h"


/*
 *	Include file of event definitions.
 */

#include "trtemp.h"


/*
 *	Include file of SMA definitions.
 */

#include "tctrl.h"


/*
 *	Include file of action/guard definitions
 */

#include "tctrlact.h"


/*
 *	Defines SMA "tctrl".
 */

RKH_SMA_CREATE( RKHSMA_T, 0, tctrl, TCTRL_PRIO, HCAL, &tctrl_ready, tctrl_init, NULL );


/*
 *	Defines states and pseudostates
 */

RKH_CREATE_COMP_STATE( tctrl_ready, 1, NULL, NULL, RKH_ROOT, &cmp_off, NULL );
RKH_CREATE_TRANS_TABLE( tctrl_ready )

	RKH_TRREG( CMP_FAILURE, 	NULL, 	compressor_failure,	&tctrl_on_failure ),

RKH_END_TRANS_TABLE


RKH_CREATE_BASIC_STATE( cmp_off, 1, NULL, NULL, &tctrl_ready, NULL );
RKH_CREATE_TRANS_TABLE( cmp_off )

	RKH_TRREG( TSMP, 	upper2tmax, 	compressor_start, 	&cmp_on ),

RKH_END_TRANS_TABLE


RKH_CREATE_BASIC_STATE( cmp_on, 1, NULL, NULL, &tctrl_ready, NULL );
RKH_CREATE_TRANS_TABLE( cmp_on )

	RKH_TRREG( TSMP, 	lower2tmin, 	compressor_stop, 	&cmp_off ),

RKH_END_TRANS_TABLE


RKH_CREATE_BASIC_STATE( tctrl_on_failure, 1, NULL, NULL, RKH_ROOT, NULL );
RKH_CREATE_TRANS_TABLE( tctrl_on_failure )

	RKH_TRREG( CMP_FAILURE_RST, NULL, 	compressor_failrst,	&tctrl_ready ),

RKH_END_TRANS_TABLE

