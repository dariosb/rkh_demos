/**
 *  \file       main.c
 *  \brief      uModel Led blinky polling implementation.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2016.03.17  DaBa  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  DaBa  Darío Baliña  dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "rkhtrc.h"
#include "bsp.h"
#include "blinky.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
int
main(int argc, char *argv[])
{
    bsp_init(argc, argv);

    rkh_sm_init(blinky);

    rkh_fwk_enter();

    RKH_TRC_CLOSE();

    return 0;
}

/* ------------------------------ End of file ------------------------------ */
