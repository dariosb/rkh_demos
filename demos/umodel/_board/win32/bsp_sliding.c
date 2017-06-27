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
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 *  DaBa  Darío Baliña  dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include <conio.h>
#include <stdio.h>

#include "rkh.h"
#include "rkhfwk_dynevt.h"
#include "rkhfwk_sched.h"
#include "trace_io_cfg.h"
#include "bsp.h"
#include "sliding.h"

RKH_THIS_MODULE

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
#define ESC                         0x1B

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RKH_ROM_STATIC_EVENT(evTerm, evTerminate);
static RKH_ROM_STATIC_EVENT(e_open, evDoorOpen);
static RKH_ROM_STATIC_EVENT(e_close, evDoorClose);
static RKH_ROM_STATIC_EVENT(e_strig, evSensorTriggered);
static RKH_ROM_STATIC_EVENT(e_srel, evSensorReleased);

#if defined(RKH_USE_TRC_SENDER)
static rui8_t keyb;
#endif

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static
void
print_banner(void)
{
    printf("\"Sliding\" example\n\n");
    printf("RKH version      = %s\n", RKH_RELEASE);
    printf("Port version     = %s\n", rkhport_get_version());
    printf("Port description = %s\n\n", rkhport_get_desc());
    printf("\n\n");

    printf("1.- Press 'O'/'o' door is open\n");
    printf("1.- Press 'C'/'c' door is close\n");
    printf("1.- Press 'S'/'s' sensor triggered\n");
    printf("1.- Press 'R'/'r' sensor released\n");
    printf("2.- Press 'escape' to quit.\n\n\n");
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
			RKH_SMA_POST_FIFO(sliding, &evTerm, &keyb);
            rkhport_fwk_stop();
            break;

        case 'c':
            RKH_SMA_POST_FIFO(sliding, &e_close, &keyb);
            break;

        case 'o':
            RKH_SMA_POST_FIFO(sliding, &e_open, &keyb);
            break;

        case 's':
            RKH_SMA_POST_FIFO(sliding, &e_strig, &keyb);
            break;

        case 'r':
            RKH_SMA_POST_FIFO(sliding, &e_srel, &keyb);
            break;

        default:
            break;
    }
}

void
bsp_setMotor(rui8_t open, rui8_t close)
{
    printf("Motor - Open:%s | Close:%s\n", 
                    open ? "ON" : "OFF",
                    close ? "ON" : "OFF");
}

void
bsp_init(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    print_banner();
    
    trace_io_setConfig(argc, argv);

    rkh_fwk_init();

    RKH_FILTER_OFF_SMA(sliding);
    RKH_FILTER_OFF_EVENT(RKH_TE_SMA_LIFO);
    RKH_FILTER_OFF_EVENT(RKH_TE_SMA_FIFO);
    RKH_FILTER_OFF_EVENT(RKH_TE_SM_DCH);
    RKH_FILTER_OFF_EVENT(RKH_TE_SM_STATE);
    RKH_FILTER_OFF_EVENT(RKH_TE_SM_EXE_ACT);
    RKH_FILTER_OFF_GROUP_ALL_EVENTS(RKH_TG_TMR);

    RKH_FILTER_OFF_ALL_SIGNALS();

    RKH_TRC_OPEN();

#if defined(RKH_USE_TRC_SENDER)
    RKH_TR_FWK_OBJ(&keyb);
    RKH_TR_FWK_OBJ(&rkh_tick);
#endif
}

/* ------------------------------ End of file ------------------------------ */
