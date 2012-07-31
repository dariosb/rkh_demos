/*
 *	file: gps.h
 *	Last updated for version: 1.0.00
 *	Date of the last update:  May 20, 2012
 *	Contact information:
 *		e-mail:	dariosb@gmail.com
 */

/**
 * 	\file gps.h
 *
 *	\brief
 *	GPS adquisition emulation.
 */


#ifndef __GPS_H__
#define __GPS_H__


/**
 *	\brief
 *	GPS sampling period [ms].
 */

#define GPS_TICK		1000


/**
 *	\brief
 *	Velocity Variation Delta [Km/h].
 */

#define VEL_DELTA		5


/**
 *	\brief
 *	Velocity Maximum Value [Km/h].
 */

#define VEL_MAX_VALUE	110


/**
 *	\brief
 *	Velocity Minimum Value [Km/h].
 */

#define VEL_MIN_VALUE	0


typedef struct
{
	/** 
	 * 	\brief
	 * 	online /offline state.
	 */

	rkhui32_t state;

	/** 
	 * 	\brief
	 * 	Latitude.
	 */

	rkhui32_t lat;

	/** 
	 * 	\brief
	 * 	Longitud.
	 */

	rkhui32_t lng;

	/** 
	 * 	\brief
	 * 	Velocity.
	 */

	rkhui32_t vel;
} GPSFRM_T;


/**
 *	\brief
 *	Must be called at timer isr.
 *	Simulates GPS adquisition and post it to
 *	trk (Tracking Control AO).
 */

void gps_isr( void );


/**
 *	\brief
 *	Increment current velocity in VEL_DELTA.
 */

void vel_inc( void );


/**
 *	\brief
 *	Decrement current velocity in VEL_DELTA.
 */

void vel_dec( void );


/*
 *	\brief
 *	Change GPS satelites coverage.
 */

void gps_sats_chg( void );


/**
 *	\brief
 *	Init GPS adquisition.
 */

void gps_init( void );

#endif
