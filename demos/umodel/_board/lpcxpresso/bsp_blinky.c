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
 *  \brief      BSP for LPCXpresso board
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.10.24  DaBa  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 *  DaBa  Dar�o Bali�a  dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "rkhfwk_dynevt.h"
#include "rkhfwk_sched.h"
#include "blinky.h"
#include "bsp.h"
#include "lpc17xx.h"
#include "PR_Teclado.h"
#include "FW_IO.h"
#include "KitInfo2.h"
#include "KitInic.h"
#include "uart.h"

RKH_THIS_MODULE

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
enum
{
    SW5, SW4, SW3, SW2, SW1
};

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RKH_ROM_STATIC_EVENT(e_blink, evBlink);

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void
bsp_timeTick(void)
{
    uint8_t k;

    DriverTeclas();
    k = Teclas_GetKey();
    switch( k )
    {
        case SW1:
            RKH_SMA_POST_FIFO(blinky, &e_blink, &rkh_tick);
            break;

        case NO_KEY:
        default:
        	break;
    }    
}

void
bsp_set_led(rui8_t led)
{
    SetPIN(RGBB, led ? ON : OFF);
}

void
bsp_init(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    cpu_init();
    InitGPIOs();

    rkh_fwk_init();

    RKH_FILTER_OFF_SMA(blinky);
    RKH_FILTER_OFF_EVENT(RKH_TE_SMA_LIFO);
    RKH_FILTER_OFF_EVENT(RKH_TE_SMA_FIFO);
    RKH_FILTER_OFF_EVENT(RKH_TE_SM_DCH);
    RKH_FILTER_OFF_EVENT(RKH_TE_SM_STATE);
    RKH_FILTER_OFF_EVENT(RKH_TE_SM_EXE_ACT);
    RKH_FILTER_OFF_GROUP_ALL_EVENTS(RKH_TG_TMR);

    RKH_FILTER_OFF_ALL_SIGNALS();

    RKH_TRC_OPEN();

    RKH_ENA_INTERRUPT();

#if defined(RKH_USE_TRC_SENDER)
    RKH_TR_FWK_OBJ(&rkh_tick);
#endif

    RKH_TR_FWK_SIG(evBlink);
}

/* ------------------------------ End of file ------------------------------ */
