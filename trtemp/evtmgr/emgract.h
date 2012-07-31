/*
 *	file: emgract.h
 *	Last updated for version: 1.0.00
 *	Date of the last update:  May 20, 2012
 *	Contact information:
 *		e-mail:	dariosb@gmail.com
 */


#ifndef __EMGRACT_H__
#define __EMGRACT_H__


#include "rkh.h"


/*
 *	Defines SMA init function
 */

void emgr_init( void );


/*
 *	Defines state entry functions
 */


/*
 *	Defines state exit functions
 */

void recall_events( void );


/*
 *	Defines transition action functions
 */

void	emgr_send_req( RKHEVT_T *pe ),
		emgr_defer_evt( RKHEVT_T *pe ),
		emgr_send_last( RKHEVT_T *pe ),
		emgr_send_cfm( RKHEVT_T *pe ),
		emgr_term( RKHEVT_T *pe );


/*
 *	Defines branch's guards
 */

HUInt room_in_dfq( RKHEVT_T *pe );


#endif
