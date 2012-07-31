/*
 *	file: emgr.c
 *	Last updated for version: 1.0.00
 *	Date of the last update:  May 20, 2012
 *	Contact information:
 *		e-mail:	dariosb@gmail.com
 */

/**
 * 	\file emgr.c
 *
 *	\brief
 *	Event manager AO:
 *		- Manages GPRS/GSM resource.
 *		- Admin event publishing.
 */

#include "rkh.h"


/*
 *	Include file of event definitions.
 */

#include "trtemp.h"


/*
 *	Include file of SMA definitions.
 */

#include "emgr.h"


/*
 *	Include file of action/guard definitions
 */

#include "emgract.h"


/*
 *	Defines SMA "emgr".
 */

RKH_SMA_CREATE( RKHSMA_T, 0, emgr, EMGR_PRIO, HCAL, &emgr_idle, emgr_init, NULL );


/*
 *	Defines states and pseudostates
 */

RKH_CREATE_BASIC_STATE( emgr_idle, 1, NULL, NULL, RKH_ROOT, NULL );
RKH_CREATE_TRANS_TABLE( emgr_idle )

	RKH_TRINT( TERM, 			NULL, 	emgr_term ),

	RKH_TRREG( SEND_EVT_REQ, 	NULL, 	emgr_send_req, 	&emgr_in_progress ),

RKH_END_TRANS_TABLE


RKH_CREATE_BASIC_STATE( emgr_in_progress, 1, NULL, recall_events, RKH_ROOT, NULL );
RKH_CREATE_TRANS_TABLE( emgr_in_progress )

	RKH_TRINT( TERM, 			NULL, 			emgr_term ),
	RKH_TRINT( SEND_EVT_REQ, 	room_in_dfq,	emgr_defer_evt ),
	RKH_TRINT( SEND_EVT_REJ, 	NULL,			emgr_send_last ),

	RKH_TRREG( SEND_EVT_CFM, 	NULL,	emgr_send_cfm, 	&emgr_idle ),

RKH_END_TRANS_TABLE


