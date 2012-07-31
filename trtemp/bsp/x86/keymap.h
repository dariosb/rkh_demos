/*
 *	file: keymap.h
 *	Last updated for version: 1.0.00
 *	Date of the last update:  May 20, 2012
 *	Contact information:
 *		e-mail:	dariosb@gmail.com
 */

/**
 * 	\file keymap.h
 *
 *	\brief
 *	Keyboard mapp for trtemp x86 demo
 *
 */

#ifndef __KEYMAP_H__
#define __KEYMAP_H__


/**
 * Special Scan codes definitions
 */

#define ESC_KEY		0x1B
#define ESC_CODE	0xE0
#define UP_KEY		0x48
#define LFT_KEY		0x4B
#define RGT_KEY		0x4D
#define DW_KEY		0x50


/**
 * Aplication keys map
 */

#define TMP_UP		RGT_KEY
#define TMP_DW		LFT_KEY

#define VEL_UP		UP_KEY
#define VEL_DW		DW_KEY

#define GPRS_LINK	'L'

#define COMP_STATE	'C'

#define GPS_SATS	'G'

#define HLP_KEY		'H'

#define EXIT_KEY	ESC_KEY


#endif
