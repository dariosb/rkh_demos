/*
 *	file: dbgcfg.h
 *	Last updated for version: 1.0.00
 *	Date of the last update:  May 20, 2012
 *	Contact information:
 *		e-mail:	dariosb@gmail.com
 */

/**
 * 	\file dbgcfg.h
 *
 *	\brief
 *	Debug congiguration
 *
 */

#ifndef __DBFCFG_H__
#define __DBGCFG_H__


/**
 *	\brief
 *	Debugging information module enable macros
 */

#define TMP_DBG_CFG		0	/* Temperature adquisition emulation (ISR) */
#define TCTRL_DBG_CFG	0	/* Temperature Control (AO) */
#define GPS_DBG_CFG		0	/* GPS adquisition emulation (ISR) */
#define TRK_DBG_CFG		0	/* Tracking (AO) */
#define EMGR_DBG_CFG	0	/* Publishing manager (AO) */
#define GPRS_DBG_CFG	0	/* GPRS Link emulation (ISR) */

#endif
