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

void reset_cnts( void );
void start_cooking( void );
void stop_cooking( void );


/*
 * Defines actions functions
 */

void inc_start( const RKH_SMA_T *sma, RKH_EVT_T *pe );
void restart_timer( const RKH_SMA_T *sma, RKH_EVT_T *pe );

/*
 * Defines guard functions
 */

rbool_t chk_start_cnt( void );
rbool_t chk_restart( void );



#endif
