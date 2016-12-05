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
#include "bsp.h"
#include "rkh.h"
#include "blinky.h"

#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

RKH_THIS_MODULE

/* ----------------------------- Local macros ------------------------------ */
#if SOCKET_TRACE == 1

    #include "tcptrc.h"

/* Trazer Tool IP Address */
    #define TRC_IP_ADDR                 "127.0.0.1"

/* Trazer Tool TCP Port Address */
    #define TRC_TCP_PORT                6602

/* Trace Socket */
static SOCKET tsock;

    #define TCP_TRACE_OPEN() \
    if (tcp_trace_open(TRC_TCP_PORT, \
                       TRC_IP_ADDR, &tsock) < 0) \
    { \
        printf("Can't open socket %s:%u\n", \
               TRC_IP_ADDR, TRC_TCP_PORT); \
        exit(EXIT_FAILURE); \
    }
    #define TCP_TRACE_CLOSE()       tcp_trace_close(tsock)
    #define TCP_TRACE_SEND(d)     tcp_trace_send(tsock, d, (int)1)
    #define TCP_TRACE_SEND_BLOCK(buf_, len_)                  \
    tcp_trace_send(tsock, (const char *)(buf_), (int)(len_))
#else
    #define TCP_TRACE_OPEN()                    (void)0
    #define TCP_TRACE_CLOSE()                   (void)0
    #define TCP_TRACE_SEND(d)                 (void)0
    #define TCP_TRACE_SEND_BLOCK(buf_, len_)  (void)0
#endif

#if BIN_TRACE == 1
    #define FTBIN_FLUSH(buf_, len_) \
    { \
        fwrite ((buf_), 1, (len_), ftbin); \
        fflush(ftbin) \
    }
    #define FTBIN_CLOSE()   fclose(ftbin)
    #define FTBIN_OPEN() \
    if ((ftbin = fopen("../ftbin", "w+b")) == NULL) \
    { \
        perror("Can't open file\n"); \
        exit(EXIT_FAILURE); \
    }
#else
    #define FTBIN_FLUSH(buf_, len_)         (void)0
    #define FTBIN_CLOSE()                   (void)0
    #define FTBIN_OPEN()                    (void)0
#endif

/* ------------------------------- Constants ------------------------------- */
#define ESC                     0x1B

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
rui8_t running;

/* ---------------------------- Local variables ---------------------------- */
static DWORD tick_msec;         /* clock tick in msec */
static RKH_TS_T ts_cntr;        /* time stamp counter */

#if defined(RKH_USE_TRC_SENDER)
static rui8_t rkh_tick;
#endif

#if BIN_TRACE == 1
static FILE *ftbin;
#endif

rui32_t blinkyTick;

static RKH_ROM_STATIC_EVENT(e_blink, evBlink);
static RKH_ROM_STATIC_EVENT(e_timeout, evTimeout);

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static
DWORD WINAPI
isr_tmr_thread(LPVOID par)      /* Win32 thread to emulate timer ISR */
{
    (void)par;
    while (running)
    {
        RKH_TIM_TICK(&rkh_tick);
        Sleep(tick_msec);
    }
    return 0;
}

static
void
print_banner(void)
{
    printf("\"Blinky ISR\" example\n\n");
    printf("RKH version      = %s\n", RKH_RELEASE);
    printf("Port version     = %s\n", rkh_get_port_version());
    printf("Port description = %s\n\n", rkh_get_port_desc());
    printf("\n\n");

    printf("1.- Press 'B'/'b' start/stop blink\n");
    printf("2.- Press 'escape' to quit.\n\n\n");
}

/* ---------------------------- Global functions --------------------------- */
void
rkh_hook_timetick(void)
{
    ++ts_cntr;

    if (_kbhit())
    {
        switch (tolower(_getch()))
        {
            case 'b':
                rkh_sm_dispatch(blinky, (RKH_EVT_T *)&e_blink);
                break;

            case ESC:
                running = 0;
                break;

            default:
                break;
        }
    }

    if (blinkyTick && (--blinkyTick == 0))
    {
        rkh_sm_dispatch(blinky, (RKH_EVT_T *)&e_timeout);
    }
}

void
rkh_hook_start(void)
{
    DWORD thtmr_id;
    HANDLE hth_tmr;

    /* set the desired tick rate */
    tick_msec = 1000UL / BSP_TICKS_PER_SEC;
    ts_cntr = 0;
    running = (rui8_t)1;

    /* create the ISR timer thread */
    hth_tmr = CreateThread(NULL, 1024, &isr_tmr_thread, 0, 0, &thtmr_id);
    RKH_ASSERT(hth_tmr != (HANDLE)0);
    SetThreadPriority(hth_tmr, THREAD_PRIORITY_TIME_CRITICAL);
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
rkh_assert(RKHROM char * const file, int line)
{
    fprintf(stderr,    "RKH_ASSERT: [%d] line from %s "
            "file\n", line, file);
    RKH_TRC_FLUSH();
    RKH_DIS_INTERRUPT();
    RKH_TR_FWK_ASSERT((RKHROM char *)file, __LINE__);
    __debugbreak();
    rkh_fwk_exit();
}

#if RKH_CFG_TRC_EN == 1

void
rkh_trc_open(void)
{
    rkh_trc_init();

    FTBIN_OPEN();
    TCP_TRACE_OPEN();
    RKH_TRC_SEND_CFG(BSP_TS_RATE_HZ);
}

void
rkh_trc_close(void)
{
    FTBIN_CLOSE();
    TCP_TRACE_CLOSE();
}

RKH_TS_T
rkh_trc_getts(void)
{
    return (RKH_TS_T)ts_cntr;
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
            FTBIN_FLUSH(blk, nbytes);
            TCP_TRACE_SEND_BLOCK(blk, nbytes);
        }
        else
        {
            break;
        }
    }
}
#endif

void
bsp_set_led(rui8_t led)
{
    printf("LED %s\n", led ? "ON" : "OFF");
}

void
bsp_init(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    print_banner();
    rkh_fwk_init();

    RKH_FILTER_OFF_SMA(blinky);
    RKH_FILTER_OFF_EVENT(RKH_TE_SMA_LIFO);
    RKH_FILTER_OFF_EVENT(RKH_TE_SMA_FIFO);
    RKH_FILTER_OFF_EVENT(RKH_TE_SMA_DCH);
    RKH_FILTER_OFF_EVENT(RKH_TE_SM_STATE);
    RKH_FILTER_OFF_EVENT(RKH_TE_SM_EXE_ACT);
    RKH_FILTER_OFF_GROUP_ALL_EVENTS(RKH_TG_TMR);

    RKH_FILTER_OFF_ALL_SIGNALS();

    RKH_TRC_OPEN();

    /* send signals to trazer */
    RKH_TR_FWK_SIG(evBlink);
    RKH_TR_FWK_SIG(evTimeout);
}

/* ------------------------------ End of file ------------------------------ */