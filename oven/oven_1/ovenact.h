/*
 *	ovenact.h
 */


#ifndef __CLIACT_H__
#define __CLIACT_H__


#include "rkh.h"


/*
 *	Defines HSM init function
 */

void oven_init( void );


/*
 *	Defines state entry/exit functions
 */

void emiter_on( void );
void emiter_off( void );


#endif
