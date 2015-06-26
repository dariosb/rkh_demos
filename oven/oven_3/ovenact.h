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


/*
 * Defines actions functions
 */

void cook_restart( void );

#endif
