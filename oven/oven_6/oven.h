/*
 *	oven.h
 */


#ifndef __OVEN_H__
#define __OVEN_H__


#include "rkh.h"


#define COOKING_TIME		RKH_TIME_SEC( 5 )	/* Cook cycle duration time */
#define RESTRT_COOK_ALLOW	2					/* Max consecutive cycles */
#define __STOP_BUTTON__ 	RKH_ENABLED			/* Enable STOP button */


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

RKH_DCLR_BASIC_STATE open, ready, on, pause;
RKH_DCLR_COMP_STATE close, cooking;
RKH_DCLR_COND_STATE cooking_cnd;
RKH_DCLR_SHIST_STATE close_hist;


/*
 * Declare Public variables
 */

extern RKH_TMR_T oventim;

#endif
