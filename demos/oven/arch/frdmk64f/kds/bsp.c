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
 *  \brief      BSP for FRDMK64F120 using Freescale KSDK Bare Metal
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
#include "bsp.h"
#include "oven.h"
#include "rkh.h"
#include "rkhfwk_sched.h"
#include "rkhfwk_dynevt.h"
#include "fsl_debug_console.h"
#include "fsl_hwtimer_systick.h"
#include "switch.h"

RKH_THIS_MODULE

/* ----------------------------- Local macros ------------------------------ */
#if SERIAL_TRACE == 1
    #define SERIAL_TRACE_OPEN()     rkhtrc_uart_init()
    #define SERIAL_TRACE_CLOSE()    rkhtrc_uart_deinit()
    #define SERIAL_TRACE_SEND_BLOCK(buf_, len_)   \
    rkhtrc_send_block(buf_, len_)
#else
    #define SERIAL_TRACE_OPEN()                     (void)0
    #define SERIAL_TRACE_CLOSE()                    (void)0
    #define SERIAL_TRACE_SEND(d)                  (void)0
    #define SERIAL_TRACE_SEND_BLOCK(buf_, len_)   (void)0
#endif

/* ------------------------------- Constants ------------------------------- */
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

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void
bsp_init(int argc, char *argv[])
{
    rint cn;

    (void)argc;
    (void)argv;

    board_init();
    rkhtrc_lptmr_init();

    rkh_fwk_init();

    RKH_FILTER_OFF_SMA(oven);
    RKH_FILTER_OFF_EVENT(RKH_TE_SMA_LIFO);
    RKH_FILTER_OFF_EVENT(RKH_TE_SMA_FIFO);
    RKH_FILTER_OFF_EVENT(RKH_TE_SM_DCH);
    RKH_FILTER_OFF_EVENT(RKH_TE_SM_STATE);
/*	RKH_FILTER_OFF_EVENT( RKH_TE_SM_TS_STATE ); */
/*	RKH_FILTER_OFF_GROUP_ALL_EVENTS( RKH_TG_SM ); */

    RKH_FILTER_OFF_ALL_SIGNALS();

    RKH_TRC_OPEN();

#if defined(RKH_USE_TRC_SENDER)
    RKH_TR_FWK_OBJ(&panel);
    RKH_TR_FWK_OBJ(&door);
#endif
}

void
bsp_timeTick(void)
{
    switch_tick();
}

void
bsp_publishSwitchEvt(ruint s, ruint debsw)
{
    switch (s)
    {
        case START_SW:
            RKH_SMA_POST_FIFO(oven, &e_start, &panel);
            break;

#if (__STOP_BUTTON__ == RKH_ENABLED)
        case STOP_SW:
            RKH_SMA_POST_FIFO(oven, &e_stop, &panel);
            break;
#endif

        case DOOR_SW:
            if (debsw == SW_PRESS)
            {
                RKH_SMA_POST_FIFO(oven, &e_close, &door);
            }
            else
            {
                RKH_SMA_POST_FIFO(oven, &e_open, &door);
            }
            break;
    }
}

void
bsp_doorOpen(void)
{
    set_rgb_led(RGB_BLACK);
}

void
bsp_ovenInit(void)
{
}

void
bsp_emitterReady(void)
{
    set_rgb_led(RGB_LIME);
}

void
bsp_emitterOn(void)
{
    set_rgb_led(RGB_RED);
}

void
bsp_emitterPause(void)
{
    set_rgb_led(RGB_YELLOW);
}

void
bsp_emitterContinue(void)
{
    set_rgb_led(RGB_RED);
}

void
bsp_emitterOff(void)
{
    set_rgb_led(RGB_BLACK);
}


/* ------------------------------ End of file ------------------------------ */

