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
 *  DaBa  Dar�o Bali�a       dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "rkhfwk_dynevt.h"
#include "rkhfwk_sched.h"
#include "lpc17xx.h"
#include "bsp.h"
#include "blinky.h"

#include <KitInfo2.h>
#include <KitInfo2_Expansiones.h>
#include <KitInic.h>
#include <KitInic_Expansiones.h>


RKH_THIS_MODULE

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
#define ESC                     0x1B

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
rui8_t running;

/* ---------------------------- Local variables ---------------------------- */
static rui32_t tick_msec;         /* clock tick in msec */
rui32_t blinkyTick;

static RKH_ROM_STATIC_EVENT(e_blink, evBlink);
static RKH_ROM_STATIC_EVENT(e_timeout, evTimeout);

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static
void
print_banner(void)
{
#if 0
    printf("\"Blinky ISR\" example\n\n");
    printf("RKH version      = %s\n", RKH_RELEASE);
    printf("Port version     = %s\n", rkhport_get_version());
    printf("Port description = %s\n\n", rkhport_get_desc());
    printf("\n\n");

    printf("1.- Press 'B'/'b' start/stop blink\n");
    printf("2.- Press 'escape' to quit.\n\n\n");
#endif
}

/* ---------------------------- Global functions --------------------------- */
void
rkh_hook_timetick(void)
{
#if 0
    if (_kbhit())
    {
        switch (tolower(_getch()))
        {
            case 'b':
                rkh_sm_dispatch(blinky, (RKH_EVT_T *)&e_blink);
                break;

            case ESC:
                running = 0;
				rkhport_fwk_stop();
                break;

            default:
                break;
        }
    }
#endif
    if (blinkyTick && (--blinkyTick == 0))
    {
        rkh_sm_dispatch(blinky, (RKH_EVT_T *)&e_timeout);
    }
}

void
rkh_hook_start(void)
{
    /* set the desired tick rate */
    tick_msec = 1000UL / BSP_TICKS_PER_SEC;
}

void
rkh_hook_exit(void)
{
    RKH_TRC_FLUSH();
}

void
rkh_hook_idle(void)                 /* called within critical section */
{
    RKH_EXIT_CRITICAL(dummy);
    RKH_TRC_FLUSH();
}

void
bsp_set_blinkyTick(rui32_t t)
{
    blinkyTick = t;
}

void
bsp_set_led(rui8_t led)
{
//    printf("LED %s\n", led ? "ON" : "OFF");
}

void
bsp_init(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    cpu_init();
    InitGPIOs();

    print_banner();

    rkh_fwk_init();

    RKH_FILTER_ON_GROUP(RKH_TRC_ALL_GROUPS);
    RKH_FILTER_ON_EVENT(RKH_TRC_ALL_EVENTS);
    RKH_FILTER_OFF_EVENT(RKH_TE_TMR_TOUT);
    RKH_FILTER_OFF_EVENT(RKH_TE_SM_STATE);
    RKH_FILTER_OFF_SMA(blinky);

    RKH_FILTER_OFF_ALL_SIGNALS();

    RKH_TRC_OPEN();

	RKH_ENA_INTERRUPT();
    /* send signals to trazer */
    RKH_TR_FWK_SIG(evBlink);
    RKH_TR_FWK_SIG(evTimeout);
}

/* ------------------------------ End of file ------------------------------ */
