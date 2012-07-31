/*
 *	file: trtemp.h
 *	Last updated for version: 1.0.00
 *	Date of the last update:  Jul 20, 2012
 *	Contact information:
 *		e-mail:	dariosb@gmail.com
 */

/**
 * 	\file trtemp.h
 *
 *	\brief
 *	Because events are explicitly shared among most of the application 
 *	components, it is convenient to declare them in the separate header 
 *	file trtemp.h.	
 */


#ifndef __TRTEMP_H__
#define __TRTEMP_H__


#include "rkh.h"
#include "gps.h"


/**
 * 	Macros for casting.
 */


/**
 * 	\brief
 * 	TRTEMP Events ID's
 */

enum trtemp_sigs
{
	TERM,
	TSMP,
	CMP_FAILURE,
	CMP_FAILURE_RST,
	SEND_EVT_REQ,
	SEND_EVT_CFM,
	SEND_EVT_REJ,
	GPSFRM,
	EPOS_TOUT,
	ESTOP_TOUT,

	NUM_TRTEMP_EVT
};


/**
 * trtemp events class definition
 */

typedef struct
{
	/** 
	 * 	\brief
	 * 	RKH event base struct.
	 */

	RKHEVT_T e;

	/**
	 * 	\brief
	 * 	Temperature value.
	 */

	rkhi8_t temp;
} TSMP_T;

#define CTS(p)	((TSMP_T*)p)


typedef struct
{
	/** 
	 * 	\brief
	 * 	Temperature at change.
	 */

	rkhi8_t temp;

	/**
	 * 	\brief
	 * 	Compresor state.
	 */

	rkhui8_t state;
} CMPCHG_T;


typedef struct
{
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
} STOP_T;


typedef struct
{
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
} VMAX_T;


typedef struct
{
	/** 
	 * 	\brief
	 * 	RKH event base struct.
	 */

	RKHEVT_T e;

	/** 
	 * 	\brief
	 * 	GPS Frame.
	 */

	GPSFRM_T frm;
} EGPSFRM_T;

#define CEGF(p)	((EGPSFRM_T*)p)


/**
 *	\brief
 *	Reportable event constitution definitions
 *	SEND_EVT_REQ is used by publishers aos ( tempmgr, trk )
 *	to request to emgr a new GPRS transmision request.
 *	SEND_EVT_REQ data type is SEND_EVT_REQ_T:
 *	
 *	typedef struct
 *	{	
 *		RKHEVT_T e;
 *		rkhui8_t type;
 *		EVENT_DATA_T data;
 *
 *	} SEND_EVT_REQ_T;
 *	
 *	where
 *
 *	e:		RKH event base struct.
 *	type: 	Event type.
 *	data: 	Event data.
 *	
 */


/**
 *	\brief
 *	TrTemp event types codes
 */

enum TRT_EVENT_TYPES
{
	TRT_EVT_POSITION,
	TRT_EVT_STOP,
	TRT_EVT_VMAX,
	TRT_EVT_COMPRESSOR,
	TRT_NUM_EVT_TYPES
};


/** 
 * 	\brief
 * 	TrTemp event data.
 * 	Is a union of all event data types
 * 	that are transmited to the server.
 */

typedef union
{

	GPSFRM_T pos;
	STOP_T stop;
	VMAX_T vmax;
	CMPCHG_T cmp;

} EVENT_DATA_T;


/** 
 * 	\brief
 * 	Time Stamp size.
 */

typedef rkhui16_t ts_t;


/**
 *	\brief
 *	Message to request to emgr send an reportable event
 */

typedef struct
{	
	/** 
	 * 	\brief
	 * 	RKH event base struct.
	 */

	RKHEVT_T e;

	/**
	 *	\brief
	 *	Time stamp
	 */
	ts_t ts;

	/** 
	 * 	\brief
	 * 	Event type.
	 */

	rkhui8_t type;

	/**
	 *	\brief
	 *	Event Data
	 */

	EVENT_DATA_T data;

} SEND_EVT_REQ_T;

#define CSREQ(p)	((SEND_EVT_REQ_T*)p)


/**
 *	\brief
 *	SMA's priority is defined in order to this enumeration
 */

enum smaprio
{
	EMGR_PRIO,
	TCTRL_PRIO,
	TRK_PRIO,
	SIMU_PRIO
};


#endif
