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
#include "aircon.h"

RKH_THIS_MODULE

/* ----------------------------- Local macros ------------------------------ */
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
/* ---------------------------- Local variables ---------------------------- */
static RKH_ROM_STATIC_EVENT( e_powerButton, evPowerButton );
static RKH_ROM_STATIC_EVENT( e_modeButton, evModeButton );
static RKH_ROM_STATIC_EVENT( e_FanSpeedUp, evFanSpeedUp );
static RKH_ROM_STATIC_EVENT( e_FanSpeedDown, evFanSpeedDown );

static ruint l_pannel;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void
print_banner(void)
{
    printf("AirCon: a very simple state machine example.\n\n");
    printf("RKH version      = %s\n", RKH_RELEASE);
    printf("Port version     = %s\n", rkhport_get_version());
    printf("Port description = %s\n\n", rkhport_get_desc());
    printf("Description: \n\n"
           "The goal of this demo application is to explain how to \n"
           "represent a \"hierarchical\" state machine using RKH framework\n"
           "This is the 'hello world' of RKH programming!.\n\n\n");

    printf("To simulate panel buttons press:\n");
    printf("\t 'P' or 'p' - Power Button\n");
    printf("\t 'M' or 'm' - Mode Button\n");
    printf("\t '+' or '-' - Fan speed up/down\n");
}

static void
gotoxy(short x, short y)
{
    COORD coord;

    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/* ---------------------------- Global functions --------------------------- */
void
bsp_timeTick(void)
{
}

void
bsp_keyParser(int c)
{
    switch(tolower(c))
    {
        case ESC:
            rkhport_fwk_stop();
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

void
bsp_init(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    print_banner();

    trace_io_setConfig(argc, argv);

    rkh_fwk_init();

    RKH_FILTER_OFF_SMA(airCon);
    RKH_FILTER_OFF_EVENT(RKH_TE_SMA_LIFO);
    RKH_FILTER_OFF_EVENT(RKH_TE_SMA_FIFO);
    RKH_FILTER_OFF_EVENT(RKH_TE_SM_DCH);
    RKH_FILTER_OFF_EVENT(RKH_TE_SM_STATE);
    RKH_FILTER_OFF_EVENT(RKH_TE_SM_EXE_ACT);
    RKH_FILTER_OFF_GROUP_ALL_EVENTS(RKH_TG_TMR);

    RKH_FILTER_OFF_ALL_SIGNALS();

    RKH_TRC_OPEN();

    BSP_setPowerOff();
    BSP_setCoolerOff();
    BSP_setHeaterOff();
    BSP_setFanSpeed(0);
}

/* ------------------------------ End of file ------------------------------ */
