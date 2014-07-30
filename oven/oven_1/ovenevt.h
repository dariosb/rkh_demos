/*
 *	ovenevt.h
 *	
 */


#ifndef __OVENEVT_H__
#define __OVENEVT_H__


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
