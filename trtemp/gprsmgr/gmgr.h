/*
 *	file: gmgr.h
 *	Last updated for version: 1.0.00
 *	Date of the last update:  May 20, 2012
 *	Contact information:
 *		e-mail:	dariosb@gmail.com
 */

/**
 * 	\file gmgr.h
 *
 *	\brief
 *	Event manager AO:
 *		- Manages GPRS/GSM resource.
 *		- Admin event publishing.
 */


#ifndef __EMGR_H__
#define __EMGR_H__


#include "rkh.h"
#include "trtemp.h"


/*
 *	Declare SMA.
 */

RKH_SMA_DCLR( gmgr );


/*
 *	Declare states and pseudostates.
 */

RKH_DCLR_BASIC_STATE	gmgr_idle, gmgr_in_progress;


/*
 * SMA configuration definitions
 */


/**
 *	\brief
 *	Max. defered event.
 */

#define EMGR_MAX_DEFER_EVENT	8


/*
 * Define sma public functions
 */

/**
 * 	\brief
 * 	Alloc SEND_EVT_REQ_T in dynamic memory.
 * 	\return
 *	if defer queue is not full return a pointer to 
 *	allocated memory, else return NULL.
 */

SEND_EVT_REQ_T *gmgr_evt_req( void );


/**
 * 	\brief
 * 	Post an SEND_EVT_REQ_T in gmgr evt queue.
 * 	\param
 *	e: Posted event.
 */

void gmgr_evt_post( SEND_EVT_REQ_T *e );

#endif
