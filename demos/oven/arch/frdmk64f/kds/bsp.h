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
//#define BSP_TICKS_PER_SEC       RKH_CFG_FWK_TICK_RATE_HZ
#define BSP_TICK_RATE_MS    (1000/RKH_CFG_FWK_TICK_RATE_HZ)

/* -------------------------------- Constants ------------------------------ */
#define SERIAL_TRACE            1

#define BSP_KERNEL_IRQ_PRIO     6
#define BSP_UART_IRQ_PRIO       7
#define BSP_HIGHEST_IRQ_PRI     5

/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
void bsp_init(int argc, char *argv[]);
void bsp_timeTick(void);

void bsp_publishSwitchEvt(ruint s, ruint debsw);

void bsp_doorOpen(void);
void bsp_ovenInit(void);
void bsp_emitterReady(void);
void bsp_emitterOn(void);
void bsp_emitterOff(void);
void bsp_emitterPause(void);
void bsp_emitterContinue(void);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
