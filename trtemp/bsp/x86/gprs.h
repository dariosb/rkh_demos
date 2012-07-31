/*
 *	file: gprs.h
 *	Last updated for version: 1.0.00
 *	Date of the last update:  May 20, 2012
 *	Contact information:
 *		e-mail:	dariosb@gmail.com
 */

/**
 * 	\file gprs.h
 *
 *	\brief
 *	GPRS link emulation.
 */


#ifndef __GPRS_H__
#define __GPRS_H__


#include "rkh.h"
#include "trtemp.h"


/**
 *	\brief
 *	GPRS sampling period [ms].
 */

#define GPRS_RESP_TIME		500


/**
 *	\brief
 *	Must be called at timer isr.
 *	Simulates GPRS link responce delay time.
 *	Allow to emulat a broken link.
 */

void gprs_isr( void );


/*
 *	\brief
 *	Change link state.
 */

void gprs_link_chg( void );


/**
 *	\brief
 *	Send reportable events through GPRS link.
 *	\param p:	request event with data to xmit.
 */

void gprs_send( SEND_EVT_REQ_T *p );

/**
 *	\brief
 *	Init GPRS emulatio.
 */

void gprs_init( void );

#endif
