/*
 *	file: tmp.h
 *	Last updated for version: 1.0.00
 *	Date of the last update:  May 20, 2012
 *	Contact information:
 *		e-mail:	dariosb@gmail.com
 */

/**
 * 	\file tmp.h
 *
 *	\brief
 *	Temperature adquisition emulation.
 */


#ifndef __TMP_H__
#define __TMP_H__


/**
 *	\brief
 *	Temperature sampling period [ms].
 */

#define TEMP_TICK		1000


/**
 *	\brief
 *	Initial Temperature value [C].
 */

#define TEMP_INITIAL	25


/**
 *	\brief
 *	Temperature Variation Delta [C].
 */

#define TEMP_DELTA		5


/**
 *	\brief
 *	Temperature Maximum Value [C].
 */

#define TEMP_MAX_VALUE	25


/**
 *	\brief
 *	Temperature Minimum Value [C].
 */

#define TEMP_MIN_VALUE	0


/**
 *	\brief
 *	Must be called at timer isr.
 *	Simulates temperature adquisition and post it to
 *	tctrl (Temperature Control AO).
 */

void tmp_isr( void );


/**
 *	\brief
 *	Increment current temperature value in TEMP_DELTA.
 */

void tmp_inc( void );


/**
 *	\brief
 *	Decrement current temperature value in TEMP_DELTA.
 */

void tmp_dec( void );


/**
 *	\brief
 *	Return current temperature value.
 */

rkhi8_t get_curr_temp( void );


/*
 *	\brief
 *	Change compressor state.
 */

void cmp_status_chg( void );


/**
 *	\brief
 *	Init temperature sampling.
 */

void tmp_init( void );

#endif
