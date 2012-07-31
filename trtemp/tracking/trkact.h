/*
 *	file: trkact.h
 *	Last updated for version: 1.0.00
 *	Date of the last update:  May 20, 2012
 *	Contact information:
 *		e-mail:	dariosb@gmail.com
 */


#ifndef __TRKACT_H__
#define __TRKACT_H__


#include "rkh.h"


/*
 *	Defines SMA init function
 */

void trk_init( void );


/*
 *	Defines state entry functions
 */

void	start_epos_tmr( void ),
		start_estop_tmr( void );


/*
 *	Defines state exit functions
 */

void	stop_epos_tmr( void ),
		stop_estop_tmr( void ),
		send_vmax_limit( void );


/*
 *	Defines transition action functions
 */


void	set_curr_pos( RKHEVT_T *pe ),
		set_curr_pos( RKHEVT_T *pe ),

		upd_curr_pos( RKHEVT_T *pe ),
		rel_curr_pos( RKHEVT_T *pe ),

		send_curr_pos( RKHEVT_T *pe ),
		send_in_stop( RKHEVT_T *pe );

/*
 *	Defines branch's guards
 */

HUInt	is_online( RKHEVT_T *pe ),
		in_stop( RKHEVT_T *pe ),
		is_vmax( RKHEVT_T *pe );


#endif
