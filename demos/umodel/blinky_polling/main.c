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
#include <stdio.h>
#include <conio.h>

#include "rkh.h"
#include "rkhtrc.h"
#include "blinky.h"
#include "bsp.h"

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
    rui8_t running, sw;
    
    bsp_init(argc, argv);

    rkh_sm_init(blinky);

    running = 1;

    while (running)
    {
        bsp_wait_tickRate(BSP_TICKS_PER_SEC);

        blinky_sm_tick();

        switch( sw = bsp_getSw() )
        {
            case BLINK_SW:
                blinky_sm_blink();
                break;

            case TERMINATE_SW:
               running = 0; 
               break;

            case NO_SW:
            default:
               break;
        }

        bsp_idle();
    }

    bsp_exit();

    return 0;
}

/* ------------------------------ End of file ------------------------------ */
