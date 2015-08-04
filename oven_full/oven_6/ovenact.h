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

void door_open( void );
void cook_ready( void );
void cook_start( void );
void cook_stop( void );
void cook_pause( void );
void tmr_start( void );
void tmr_stop( void );


/*
 * Defines actions functions
 */

void defer_evt( RKH_EVT_T *pe );
void cook_continue( RKH_EVT_T *pe );


/*
 * Defines guard functions
 */

rbool_t chk_room_dfq( void );
rbool_t chk_dfq( void );



#endif
