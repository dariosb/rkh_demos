/*
 *	scevt.h
 *	
 *	\brief
 *	Server-Client (SC) event definitions.
 */


#ifndef __SCEVT_H__
#define __SCEVT_H__


#include "rkh.h"


/**
 * 	Signals
 */

typedef enum ov_sigs_t
{
	OPEN,	/* door is open  */
	CLOSE,	/* door is close */
	START,	/* dtart button pressed */
	TOUT,	/* timer expired */
	TERM,   /* to close application in x86 */
} OV_SIGS_T;



#endif
