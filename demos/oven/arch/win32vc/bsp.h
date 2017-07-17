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
 *  \brief      BSP for 80x86 OS win32
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.10.24  DaBa  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 *  DaBa  Darío Baliña       dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
#ifndef __BSP_H__
#define __BSP_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
#define BSP_TICKS_PER_SEC           RKH_CFG_FWK_TICK_RATE_HZ

/**
 *  \brief
 *  This macro represents the number of timestamp clock ticks per second.
 *  Dividing a count of timestamp ticks by this macro yields the number
 *  of seconds.
 */

#define BSP_TS_RATE_HZ              RKH_CFG_FWK_TICK_RATE_HZ

/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
#if defined(RKH_USE_TRC_SENDER)
extern rui8_t rkh_tick;
#endif

/* -------------------------- Function prototypes -------------------------- */
void bsp_timeTick(void);
void bsp_keyParser(int c);
void bsp_publishSwitchEvt(ruint s, ruint debsw);
void bsp_init(int argc, char *argv[]);
void bsp_ovenInit(void);
void bsp_ovenInit(void);
void bsp_doorOpen(void);
void bsp_emitterReady(void);
void bsp_emitterPause(void);
void bsp_emitterContinue(void);
void bsp_emitterOn(void);
void bsp_emitterOff(void);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
