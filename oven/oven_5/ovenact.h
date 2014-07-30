/*
 *	ovenact.h
 */


#ifndef __OVENACT_H__
#define __OVENACT_H__


#include "rkh.h"


/*
 *	Defines HSM init function
 */

void oven_init( void );


/*
 *	Defines state entry/exit functions
 */

void start_cooking( void );
void stop_cooking( void );


/*
 * Defines actions functions
 */

void inc_defer_start( const RKH_SMA_T *sma, RKH_EVT_T *pe );
void recall_evts( const RKH_SMA_T *sma, RKH_EVT_T *pe );


/*
 * Defines guard functions
 */

rbool_t chk_restart_cnt( void );




#endif
