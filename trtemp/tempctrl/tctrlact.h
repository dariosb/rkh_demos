/*
 *	file: tctrlact.h
 *	Last updated for version: 1.0.00
 *	Date of the last update:  May 20, 2012
 *	Contact information:
 *		e-mail:	dariosb@gmail.com
 */


#ifndef __TCTRLACT_H__
#define __TCTRLACT_H__


#include "rkh.h"


/*
 *	Defines SMA init function
 */

void tctrl_init( void );


/*
 *	Defines state entry functions
 */


/*
 *	Defines state exit functions
 */


/*
 *	Defines transition action functions
 */


void	compressor_stop( RKHEVT_T *pe ),
		compressor_start( RKHEVT_T *pe ),
		compressor_failure( RKHEVT_T *pe ),
		compressor_failrst( RKHEVT_T *pe );

/*
 *	Defines branch's guards
 */

HUInt	upper2tmax( RKHEVT_T *pe ),
		lower2tmin( RKHEVT_T *pe );


#endif
