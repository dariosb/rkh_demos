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
#include "bsp.h"
#include "aircon.h"
#include "rkh.h"

#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>

RKH_THIS_MODULE

/* ----------------------------- Local macros ------------------------------ */
/*
 *  For socket trace feature.
 */

#if SOCKET_TRACE == 1

#include "tcptrc.h"

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
    #define TCP_TRACE_CLOSE() \
    tcp_trace_close(tsock)
    #define TCP_TRACE_SEND(d) \
    tcp_trace_send(tsock, d, (int)1)
    #define TCP_TRACE_SEND_BLOCK(buf_, len_) \
    tcp_trace_send(tsock, (const char *)(buf_), (int)(len_))
#else
    #define TCP_TRACE_OPEN()                    (void)0
    #define TCP_TRACE_CLOSE()                   (void)0
    #define TCP_TRACE_SEND(d)                 (void)0
    #define TCP_TRACE_SEND_BLOCK(buf_, len_)  (void)0
#endif

/* ------------------------------- Constants ------------------------------- */
#define ESC                         0x1B
#define FAN_SPEED_UP                '+'
#define FAN_SPEED_DOWN              '-'
#define POWER_BUTTON                'p'
#define MODE_BUTTON                 'm'
#define X_OFFSET                    2
#define Y_OFFSET                    20


/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
rui8_t running;

/* ---------------------------- Local variables ---------------------------- */
static RKH_ROM_STATIC_EVENT( e_powerButton, evPowerButton );
static RKH_ROM_STATIC_EVENT( e_modeButton, evModeButton );
static RKH_ROM_STATIC_EVENT( e_FanSpeedUp, evFanSpeedUp );
static RKH_ROM_STATIC_EVENT( e_FanSpeedDown, evFanSpeedDown );

static ruint l_pannel;

static DWORD tick_msec;         /* clock tick in msec */

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static
DWORD WINAPI
isr_kbd_thread(LPVOID par)      /* Win32 thread to emulate keyboard ISR */
{
    int c;

    (void)par;
    while (running)
    {
        c = _getch();
        switch(tolower(c))
        {
            case ESC:
                running = 0;
                break;

            case POWER_BUTTON:
                RKH_SMA_POST_FIFO( airCon, &e_powerButton, &l_pannel );
                break;

            case MODE_BUTTON:
                RKH_SMA_POST_FIFO( airCon, &e_modeButton, &l_pannel );
                break;

            case FAN_SPEED_UP:
                RKH_SMA_POST_FIFO( airCon, &e_FanSpeedUp, &l_pannel );
                break;

            case FAN_SPEED_DOWN:
                RKH_SMA_POST_FIFO( airCon, &e_FanSpeedDown, &l_pannel );
                break;
        }
    }
    return 0;
}

static void
gotoxy(short x, short y)
{
    COORD coord;

    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

static
void
print_banner(void)
{
    printf("AirCon: a very simple state machine example.\n\n");
    printf("RKH version      = %s\n", RKH_RELEASE);
    printf("Port version     = %s\n", rkh_get_port_version());
    printf("Port description = %s\n\n", rkh_get_port_desc());
    printf("Description: \n\n"
           "The goal of this demo application is to explain how to \n"
           "represent a \"hierarchical\" state machine using RKH framework\n"
           "This is the 'hello world' of RKH programming!.\n\n\n");

    printf("To simulate panel buttons press:\n");
    printf("\t 'P' or 'p' - Power Button\n");
    printf("\t 'M' or 'm' - Mode Button\n");
    printf("\t '+' or '-' - Fan speed up/down\n");
}

/* ---------------------------- Global functions --------------------------- */
void
rkh_hook_start(void)
{
    DWORD thkbd_id;
    HANDLE hth_kbd;

    running = (rui8_t)1;

    /* create the ISR keyboard thread */
    hth_kbd = CreateThread(NULL, 1024, &isr_kbd_thread, 0, 0, &thkbd_id);
    RKH_ASSERT(hth_kbd != (HANDLE)0);
    SetThreadPriority(hth_kbd, THREAD_PRIORITY_NORMAL);
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
    RKH_WAIT_FOR_EVENTS();      /* yield the CPU until new event(s) arrive */
}

void
rkh_assert(RKHROM char * const file, int line)
{
    fprintf(stderr,    "RKH_ASSERT: [%d] line from %s "
            "file\n", line, file);
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
    TCP_TRACE_OPEN();
    RKH_TRC_SEND_CFG(BSP_TS_RATE_HZ);
}

void
rkh_trc_close(void)
{
    TCP_TRACE_CLOSE();
}

RKH_TS_T
rkh_trc_getts(void)
{
    return (RKH_TS_T)clock();
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

        if ((blk != (rui8_t *)0))
        {
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
bsp_init(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    srand((unsigned)time(NULL));
    print_banner();
    rkh_fwk_init();

    RKH_FILTER_ON_GROUP(RKH_TRC_ALL_GROUPS);
    RKH_FILTER_ON_EVENT(RKH_TRC_ALL_EVENTS);
    RKH_FILTER_OFF_EVENT(RKH_TE_TMR_TOUT);
    RKH_FILTER_OFF_EVENT(RKH_TE_SM_STATE);
    RKH_FILTER_OFF_SMA(airCon);
    RKH_FILTER_OFF_ALL_SIGNALS();

    RKH_TRC_OPEN();

    BSP_setPowerOff();
    BSP_setCoolerOff();
    BSP_setHeaterOff();
    BSP_setFanSpeed(0);
}

void 
BSP_AirConPower(setOnOff_t set)
{
    gotoxy(X_OFFSET, Y_OFFSET+0);
    printf("Power: %-3s", (set == SET_ON) ? "ON" : "OFF");
}

void 
BSP_setCooler(setOnOff_t set)
{
    gotoxy(X_OFFSET, Y_OFFSET+1);
    printf("Cooler: %-3s", (set == SET_ON) ? "ON" : "OFF");
}

void 
BSP_setHeater(setOnOff_t set)
{
    gotoxy(X_OFFSET, Y_OFFSET+2);
    printf("Heater: %-3s", (set == SET_ON) ? "ON" : "OFF");
}

void
BSP_setFanSpeed(ruint speed)
{
    gotoxy(X_OFFSET, Y_OFFSET+3);
    printf("Fan Speed: %d", speed);
}


/* ------------------------------ End of file ------------------------------ */

