/*
 *  \file       led.h
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2016.03.17  LeFr  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __BLINKY_H__
#define __BLINKY_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
#define DELAY   RKH_TIME_SEC(2)

/* ================================ Signals ================================ */
typedef enum bl_sigs_t
{
    BLINK, 
    TOGGLE,
    STOP,
    TERM
} OV_SIGS_T;

/* ======================== Declares active object ========================= */
RKH_SMA_DCLR(blinky);

/* =================== Declares states and pseudostates ==================== */
RKH_DCLR_BASIC_STATE idle, blinking;

/* ------------------------------- Data types ------------------------------ */
//typedef struct Blinky Blinky;

/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
void blinky_sm_tick(void);
void blinky_sm_blink(void);

/* ============================ Initial action ============================= */
/* ============================ Effect actions ============================= */
/* ============================= Entry actions ============================= */
/* ============================= Exit actions ============================== */
/* ================================ Guards ================================= */

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */

