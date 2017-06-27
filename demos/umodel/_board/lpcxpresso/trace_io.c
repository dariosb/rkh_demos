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
 *  \brief      Serial support for Cortex-M3 LpcXpresso
 *
 *  \ingroup    bsp
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.04.14  DaBa  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 *  DaBa  Dario Bali�a       dariosb@gmail.com
 */
/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"

#if RKH_CFG_TRC_EN == 1
/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/*
 *  \brief
 *  This macro represents the number of timestamp clock ticks per second.
 *  Dividing a count of timestamp ticks by this macro yields the number
 *  of seconds.
 */
#define BSP_TS_RATE_HZ              RKH_CFG_FWK_TICK_RATE_HZ


/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void
rkh_trc_open(void)
{
    rkh_trc_init();
#if 0
    if (strlen(config.ftbinName) != 0)
    {
        if ((ftbin = fopen(config.ftbinName, "w+b")) == NULL)
        {
            printf("Can't open trace file %s\n", config.ftbinName);
            exit(EXIT_FAILURE);
        }
    }

    if (trace_io_tcp_open(config.tcpPort, config.tcpIpAddr, &tsock) < 0)
    {
        printf("Can't open socket %s:%u\n",
               config.tcpIpAddr, config.tcpPort);
        exit(EXIT_FAILURE);
    }
#endif
    RKH_TRC_SEND_CFG(BSP_TS_RATE_HZ);
}

void
rkh_trc_close(void)
{
#if 0
    if (ftbin != NULL)
    {
        fclose(ftbin);
    }

    trace_io_tcp_close(tsock);
#endif
}

RKH_TS_T
rkh_trc_getts(void)
{
#if 0
    return (RKH_TS_T)clock();
#else
    return (RKH_TS_T)0;
#endif
}

void
rkh_trc_flush(void)
{
    rui8_t *blk;
    TRCQTY_T nbytes;
    RKH_SR_ALLOC();

    FOREVER
    {
        nbytes = 128;

        RKH_ENTER_CRITICAL_();
        blk = rkh_trc_get_block(&nbytes);
        RKH_EXIT_CRITICAL_();

#if 0
        if ((blk != (rui8_t *)0))
        {
            if (ftbin != NULL)
            {
                fwrite(blk, 1, nbytes, ftbin);
            }

            trace_io_tcp_send(tsock, (char *)blk, nbytes);
        }
        else
        {
            break;
        }
#endif
    }
}
#endif

/* ------------------------------ File footer ------------------------------ */
