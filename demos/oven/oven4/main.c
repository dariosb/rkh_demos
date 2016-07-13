/*
 * main.c
 */


#include "rkh.h"
#include "rkhtrc.h"
#include "bsp.h"
#include "oven.h"


#define QSTO_SIZE			4

static RKH_EVT_T *qsto[ QSTO_SIZE ];

int
main( int argc, char *argv[] )
{
	/* invoke the rkh_fwk_init() function */
	bsp_init( argc, argv );

	RKH_SMA_ACTIVATE( oven, qsto, QSTO_SIZE, 0, 0 );

	rkh_fwk_enter();

	RKH_TRC_CLOSE();

	return 0;
}
