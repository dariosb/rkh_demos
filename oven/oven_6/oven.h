/*
 *	oven.h
 */


#ifndef __OVEN_H__
#define __OVEN_H__


#include "rkh.h"


#define COOK_TIME		RKH_TIME_SEC( 5 )	/* Cook cycle duration time */
#define MAX_RESTART		2					/* Max consecutive cycles */
#define __STOP_BUTTON__ RKH_ENABLED			/* Enable STOP button */


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

RKH_DCLR_BASIC_STATE opened, ready, on, wstart, pause;
RKH_DCLR_COMP_STATE closed, cooking;
RKH_DCLR_COND_STATE cstart;
RKH_DCLR_SHIST_STATE close_hist;


/*
 * Declare Public variables
 */

extern RKH_TMR_T oventim;
extern RKH_RQ_T dfq;

#endif
