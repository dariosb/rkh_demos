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
 *  \brief      Shared BSP for EduCIAA.
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
#include "ciaaPOSIX_stdio.h"  /* <= device handler header */
#include "ciaaPOSIX_string.h" /* <= string header */
#include "ciaak.h"            /* <= ciaa kernel header */

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/**
 *  \brief
 *  This macro represents the number of timestamp clock ticks per second.
 *  Dividing a count of timestamp ticks by this macro yields the number
 *  of seconds.
 */

#define BSP_TS_RATE_HZ              RKH_CFG_FWK_TICK_RATE_HZ

/* -------------------------------- Constants ------------------------------ */
#define SERIAL_TRACE                1

/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
#if RKH_CFG_TRC_EN == 1
extern rui8_t trace_open;
#endif

/* -------------------------- Function prototypes -------------------------- */
void bsp_init(int argc, char *argv[]);

rui32_t  bsp_rand(void);

void bsp_cli_wait_req(rui8_t clino, RKH_TNT_T req_time);
void bsp_cli_req(rui8_t clino);
void bsp_cli_using(rui8_t clino, RKH_TNT_T using_time);
void bsp_cli_paused(rui8_t clino);
void bsp_cli_resumed(rui8_t clino);
void bsp_cli_done(rui8_t clino);

void bsp_svr_recall(rui8_t clino);
void bsp_svr_paused(rui32_t ntot, rui32_t *ncr);
void bsp_svr_start(rui8_t clino);
void bsp_svr_end(void);
void bsp_svr_resume(void);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
