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
 *  \file       bsp.h
 *  \ingroup    bsp
 *
 *  \brief      BSP for FRDK64F120 using Freescale KSDK Bare Metal
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
#ifndef __BSP_H__
#define __BSP_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "board.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
#define BSP_TICKS_PER_SEC       RKH_CFG_FWK_TICK_RATE_HZ

#ifdef RKH_DEBUG
#define reset_now()     __asm volatile ("	bkpt 0x00FF\n")
#else
#define reset_now()     cpu_reset()
#endif

/* -------------------------------- Constants ------------------------------ */
#define SERIAL_TRACE            1

#define BSP_KERNEL_IRQ_PRIO     6
#define BSP_UART_IRQ_PRIO       7
#define BSP_HIGHEST_IRQ_PRI     5

/**
 *  \brief
 *  This macro represents the number of timestamp clock ticks per second.
 *  Dividing a count of timestamp ticks by this macro yields the number
 *  of seconds.
 */

#define BSP_TS_RATE_HZ          10000

/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */

/* -------------------------- Function prototypes -------------------------- */
void bsp_init(int argc, char *argv[]);

void bsp_pub_sw_evt(ruint s, ruint debsw);

void bsp_door_open(void);
void bsp_oven_init(void);
void bsp_emitter_ready(void);
void bsp_emitter_on(void);
void bsp_emitter_off(void);
void bsp_emitter_pause(void);
void bsp_emitter_continue(void);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
