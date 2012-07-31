/*
 *	file: bsp.h
 *	Last updated for version: 2.0
 *	Date of the last update:  Feb 28, 2012
 *	Contact information:
 *		e-mail:	dariosb@gmail.com
 */


#ifndef __BSP_H__
#define __BSP_H__


#define BSP_TICKS_PER_SEC   	100

#define RKH_TIM_MS(x)			(x*BSP_TICKS_PER_SEC)/1000

void bsp_init( int argc, char *argv[] );


#endif
