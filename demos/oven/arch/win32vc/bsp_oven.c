/*
 *  --------------------------------------------------------------------------
 *
 *                                Framework RKH
 *                                -------------
 *
 *            State-machine framework for reactive embedded systems
 *
 *                      Copyright (C) 2010 Leandro Francucci.
 *          All rights reserved. Protected by international copyright laws.
 *
 *
 *  RKH is free software: you can redistribute it and/or modify it under the
 *  terms of the GNU General Public License as published by the Free Software
 *  Foundation, either version 3 of the License, or (at your option) any
 *  later version.
 *
 *  RKH is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with RKH, see copying.txt file.
 *
 *  Contact information:
 *  RKH web site:   http://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail:         francuccilea@gmail.com
 *  ---------------------------------------------------------------------------
 */

/**
 *  \file       bsp.c
 *  \ingroup    bsp
 *
 *  \brief      BSP for 80x86 OS win32
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.10.24  DaBa  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  DaBa  Darío Baliña  dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include <stdio.h>
#include <conio.h>
#include <time.h>

#include "rkh.h"
#include "rkhfwk_dynevt.h"
#include "rkhfwk_sched.h"
#include "trace_io_cfg.h"
#include "bsp.h"
#include "oven.h"

RKH_THIS_MODULE

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
#define ESC                         0x1B

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RKH_ROM_STATIC_EVENT(e_start, START);
static RKH_ROM_STATIC_EVENT(e_open, OPEN);
static RKH_ROM_STATIC_EVENT(e_close, CLOSE);
static RKH_ROM_STATIC_EVENT(e_term, TERM);
#if (__STOP_BUTTON__ == RKH_ENABLED)
static RKH_ROM_STATIC_EVENT(e_stop, STOP);
#endif

#if defined(RKH_USE_TRC_SENDER)
static rui8_t door;
static rui8_t panel;
#endif

static time_t cStart, cStop;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void
print_banner(void)
{
    printf("\"oven\" example\n\n");
    printf("RKH version      = %s\n", RKH_RELEASE);
    printf("Port version     = %s\n", rkhport_get_version());
    printf("Port description = %s\n\n", rkhport_get_desc());
    printf("\n\n");

    printf("1.- Press 'O'/'o' door { Open  } -> oven.\n");
    printf("2.- Press 'C'/'c' door { Close } -> oven.\n");
    printf("3.- Press 'S'/'s' panel{ Start } -> oven.\n");
#if (__STOP_BUTTON__ == RKH_ENABLED)
    printf("3.- Press 'P'/'p' panel{ Stop  } -> oven.\n");
#endif
    printf("4.- Press 'escape' to quit.\n\n\n");

}

/* ---------------------------- Global functions --------------------------- */
void
bsp_timeTick(void)
{
}

void
bsp_keyParser(int c)
{
    switch (tolower(c))
    {
            case ESC:
                RKH_SMA_POST_FIFO(oven, &e_term, &panel);
                rkhport_fwk_stop();
                break;

            case 's':
                RKH_SMA_POST_FIFO(oven, &e_start, &panel);
                break;

#if (__STOP_BUTTON__ == RKH_ENABLED)
            case 'p':
                RKH_SMA_POST_FIFO(oven, &e_stop, &panel);
                break;
#endif

            case 'o':
                RKH_SMA_POST_FIFO(oven, &e_open, &door);
                break;

            case 'c':
                RKH_SMA_POST_FIFO(oven, &e_close, &door);
                break;

            default:
                break;
    }
}

void
bsp_doorOpen(void)
{
    printf("+- Door Open\n");
}

void
bsp_ovenInit(void)
{
    printf(" Oven is running\n\n");
}

void
bsp_emitterReady(void)
{
    printf("+- Cook Ready \n");
}

void
bsp_emitterOn(void)
{
    time(&cStart);
    printf("     Emitter: ON\n");
}

void
bsp_emitterPause(void)
{
    printf("   Paused\n");
}

void
bsp_emitterContinue(void)
{
    printf("   Continue\n");
}

void
bsp_emitterOff(void)
{
    time(&cStop);
    printf("     Emitter: OFF\n");
    printf("     Cook Time: %5.2f sec\n", difftime(cStop, cStart));
}

void
bsp_init(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    print_banner();

    trace_io_setConfig(argc, argv);

    rkh_fwk_init();

    RKH_FILTER_OFF_SMA(oven);
    RKH_FILTER_OFF_EVENT(RKH_TE_SMA_LIFO);
    RKH_FILTER_OFF_EVENT(RKH_TE_SMA_FIFO);
    RKH_FILTER_OFF_EVENT(RKH_TE_SM_DCH);
    RKH_FILTER_OFF_EVENT(RKH_TE_SM_STATE);
    RKH_FILTER_OFF_EVENT(RKH_TE_SM_EXE_ACT);
    RKH_FILTER_OFF_GROUP_ALL_EVENTS(RKH_TG_TMR);

    RKH_FILTER_OFF_ALL_SIGNALS();

    RKH_TRC_OPEN();

#if defined(RKH_USE_TRC_SENDER)
    RKH_TR_FWK_OBJ(&panel);
    RKH_TR_FWK_OBJ(&door);
#endif
}

/* ------------------------------ End of file ------------------------------ */
