/*
 *	file: tctrl.h
 *	Last updated for version: 1.0.00
 *	Date of the last update:  May 20, 2012
 *	Contact information:
 *		e-mail:	dariosb@gmail.com
 */

/**
 * 	\file tctrl.h
 *
 *	\brief
 *	Temperature Control AO:
 *		- Simple ON/OFF Temperature Controller.
 *		- Publish refrigerator state on change.
 */


#ifndef __TCTRL_H__
#define __TCTRL_H__


#include "rkh.h"


/*
 *	Declare SMA.
 */

RKH_SMA_DCLR( tctrl );


/*
 *	Declare states and pseudostates.
 */

RKH_DCLR_COMP_STATE		tctrl_ready;

RKH_DCLR_BASIC_STATE	tctrl_on_failure,
						cmp_off,
						cmp_on;


/*
 * SMA configuration definitions
 */


/**
 *	\brief
 *	Temperatur Low Threshold.
 */

#define TCTRL_TMP_LOW_TH	10


/**
 *	\brief
 *	Temperatur High Threshold.
 */

#define TCTRL_TMP_HIGH_TH	20


/**
 *	\brief
 *	Compressor States codes.
 */

enum CMP_STATES
{
	COMPRESSOR_IDLE,
	COMPRESSOR_RUNNING,
	COMPRESSOR_FAILURE,
	COMPRESSOR_FAILRST,
	NUM_CMPSTS
};

#endif
