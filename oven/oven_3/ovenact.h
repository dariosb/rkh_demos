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

void restart_timer( void );

#endif
