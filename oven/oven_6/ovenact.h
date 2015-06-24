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

void cook_init( void );
void cook_start( void );
void cook_pause( void );
void cook_continue( void );
void cook_stop( void );


/*
 * Defines actions functions
 */

void inc_start( void );
void cook_restart( void );

/*
 * Defines guard functions
 */

rbool_t chk_start_cnt( void );
rbool_t chk_restart( void );



#endif
