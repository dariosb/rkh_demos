/*
 * main.c
 */


#include "rkh.h"
#include "rkhtrc.h"
#include "bsp.h"
#include "oven.h"
#include "ovenevt.h"
#include "ovenact.h"


#define QSTO_SIZE			4

static RKH_EVT_T *qsto[ QSTO_SIZE ];

	
int
main( int argc, char *argv[] )
{
	/* invoke the rkh_fwk_init() function */
	bsp_init( argc, argv );

	/* send objects to trazer */
	RKH_TR_FWK_AO( oven );
	RKH_TR_FWK_QUEUE( &oven->equeue );
	RKH_TR_FWK_STATE( oven, &opened );
	RKH_TR_FWK_STATE( oven, &closed );
	RKH_TR_FWK_STATE( oven, &ready );
	RKH_TR_FWK_STATE( oven, &cooking );
	RKH_TR_FWK_OBJ(	&oventim );
	RKH_TR_FWK_FUN(	&oven_init );
	RKH_TR_FWK_FUN(	&door_open );
	RKH_TR_FWK_FUN(	&cook_ready );
	RKH_TR_FWK_FUN(	&cook_start );
	RKH_TR_FWK_FUN(	&cook_stop );
	

	/* send signals to trazer */
	RKH_TR_FWK_SIG( OPEN );
	RKH_TR_FWK_SIG( CLOSE );
	RKH_TR_FWK_SIG( START );
	RKH_TR_FWK_SIG( TMREVT );
	RKH_TR_FWK_SIG( TERM );

	RKH_SMA_ACTIVATE( oven, qsto, QSTO_SIZE, 0, 0 );

	rkh_fwk_enter();

	RKH_TRC_CLOSE();
	return 0;
}
