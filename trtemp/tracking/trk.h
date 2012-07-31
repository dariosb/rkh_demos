/*
 *	file: emgr.h
 *	Last updated for version: 1.0.00
 *	Date of the last update:  May 20, 2012
 *	Contact information:
 *		e-mail:	dariosb@gmail.com
 */

/**
 * 	\file emgr.h
 *
 *	\brief
 *	Tracking AO:
 *		- Handle GPS status change.
 *		- Post detention and max vel exceed events.
 */


#ifndef __TRK_H__
#define __TRK_H__


#include "rkh.h"


/*
 *	Declare SMA.
 */

RKH_SMA_DCLR( trk );


/*
 *	Declare states and pseudostates.
 */

RKH_DCLR_COMP_STATE		gps_online;

RKH_DCLR_BASIC_STATE	gps_offline,
						gps_stop,
						gps_vmax,
						gps_moving;


RKH_DCLR_COND_STATE		gps_chk_online,
						gps_chk_vmax;

/*
 * SMA configuration definitions
 */

enum GPS_STATES
{
	GPS_IS_ONLINE,
	GPS_IS_OFFLINE,
	NUM_GPS_STATES
};


/**
 *	\brief
 *	Maximum velocity threshold
 */

#define TRK_MAX_VELOCITY	60


/**
 *	\brief
 *	Minimum velocity threshold to stop
 */

#define TRK_MIN_VELOCITY	5


/**
 *	\brief
 *	Tracking position report period [ms]
 */

#define TRK_POS_PRD			5000


/**
 *	\brief
 *	Stop detection timeout [ms]
 */

#define TRK_STOP_TIME		10000

#endif
