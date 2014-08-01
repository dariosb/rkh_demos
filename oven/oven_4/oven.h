/*
 *	oven.h
 */


#ifndef __OVEN_H__
#define __OVEN_H__


#include "rkh.h"


#define EMITTER_ON_TIME		RKH_TIME_SEC( 10 )


typedef struct
{
	RKH_SMA_T sma;	/* base structure */
} OVEN_T;			/* SMA derived from RKH_SMA_T structure */


/*
 *	Declare SMA.
 */

RKH_SMA_DCLR( oven );


/*
 *	Declare states and pseudostates.
 */

RKH_DCLR_BASIC_STATE open, ready, cooking;
RKH_DCLR_COMP_STATE close;
RKH_DCLR_SHIST_STATE close_hist;


/*
 * Declares public variables
 */

extern RKH_TMR_T oventim;


#endif