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
	RKH_TR_FWK_STATE( oven, &open );
	RKH_TR_FWK_STATE( oven, &close );
	RKH_TR_FWK_STATE( oven, &close_hist );
	RKH_TR_FWK_STATE( oven, &ready );
	RKH_TR_FWK_STATE( oven, &cooking );
	RKH_TR_FWK_STATE( oven, &cooking_cnd );
	RKH_TR_FWK_STATE( oven, &on );
	RKH_TR_FWK_STATE( oven, &pause );
	RKH_TR_FWK_OBJ(	&oventim );

	/* send signals to trazer */
	RKH_TR_FWK_SIG( OPEN );
	RKH_TR_FWK_SIG( CLOSE );
	RKH_TR_FWK_SIG( START );
	RKH_TR_FWK_SIG( STOP );
	RKH_TR_FWK_SIG( TOUT );
	RKH_TR_FWK_SIG( TERM );

	RKH_SMA_ACTIVATE( oven, qsto, QSTO_SIZE, 0, 0 );

	rkh_fwk_enter();

	RKH_TRC_CLOSE();
	return 0;
}
