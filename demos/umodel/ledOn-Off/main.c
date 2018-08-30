/**
 *	file		main.c
 *	brief		LedRKH - Active Object implementation.
 */

/* -------------------------- Development history -------------------------- */
/*
 * 24-08-2018 11:09:58 v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 * Nahuel
 */

/* --------------------------------- Notes --------------------------------- */

/* ----------------------------- Include files ----------------------------- */
#include "rkh.h" 
#include "rkhtrc.h" 
#include "bsp.h"
#include "LedRKH.h"

/* ----------------------------- Local macros ------------------------------ */

/* ------------------------------- Constants ------------------------------- */
#define QSTO_SIZE	2

/* ---------------------------- Local data types --------------------------- */

/* ---------------------------- Global variables --------------------------- */

/* ---------------------------- Local variables ---------------------------- */
static RKH_EVT_T *qsto[QSTO_SIZE];

/* ----------------------- Local function prototypes ----------------------- */

/* ---------------------------- Local functions ---------------------------- */

/* ---------------------------- Global functions --------------------------- */

int
main(int argc, char *argv[])
{
	bsp_init(argc, argv);
	RKH_SMA_ACTIVATE(LedRKH, qsto, QSTO_SIZE, 0, 0);
	rkh_fwk_enter();
	RKH_TRC_CLOSE();
	return 0;
}

/* ------------------------------ End of file ------------------------------ */
