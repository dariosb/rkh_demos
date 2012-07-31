/*
 *	file: emgr.h
 *	Last updated for version: 1.0.00
 *	Date of the last update:  May 20, 2012
 *	Contact information:
 *		e-mail:	dariosb@gmail.com
 */

/**
 * 	\file emgr.h
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

RKH_SMA_DCLR( emgr );


/*
 *	Declare states and pseudostates.
 */

RKH_DCLR_BASIC_STATE	emgr_idle, emgr_in_progress;


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

SEND_EVT_REQ_T *emgr_evt_req( void );


/**
 * 	\brief
 * 	Post an SEND_EVT_REQ_T in emgr evt queue.
 * 	\param
 *	e: Posted event.
 */

void emgr_evt_post( SEND_EVT_REQ_T *e );

#endif
