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
 *  \file       trace_io.c
 *  \brief      Serial support for FRDMK64F120
 *
 *  \ingroup    bsp
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.04.14  DaBa  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  DaBa  Dario Bali�a       dariosb@gmail.com
 */
/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "bsp.h"
#include "board.h"

#if RKH_CFG_TRC_EN == 1
/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
#define TRC_COM_PORT        UART_USB
#define TRC_BAUD_RATE       115200
#define BSP_TS_RATE_HZ      10000

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
RKH_TS_T
rkh_trc_getts(void)
{
    return (RKH_TS_T)rkhtrc_lptmr_read();
}

void
rkh_trc_open(void)
{
    rkh_trc_init();
    rkhtrc_uart_init();
    RKH_TRC_SEND_CFG(BSP_TS_RATE_HZ);
}

void
rkh_trc_close(void)
{
    rkhtrc_uart_deinit();
}

void
rkh_trc_flush(void)
{
    rui8_t *blk;
    TRCQTY_T nbytes;
    RKH_SR_ALLOC();

    FOREVER
    {
        nbytes = (TRCQTY_T)1024;

        RKH_ENTER_CRITICAL_();
        blk = rkh_trc_get_block(&nbytes);
        RKH_EXIT_CRITICAL_();

        if ((blk != (rui8_t *)0))
        {
            rkhtrc_send_block(blk, nbytes);
        }
        else
        {
            break;
        }
    }
}
#endif

/* ------------------------------ File footer ------------------------------ */
