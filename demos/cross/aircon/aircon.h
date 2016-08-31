/**
 *  \file       aircon.h
 *
 *  \brief      Air Conditioner Active object specification.
 *
 *  This file contains the definitions of objet structures (state machine, 
 *  states, and pseudostates) and other facilities shared among the 
 *  components of the application.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2016.08.26  DaBa  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 *  DaBa  Dario Baliña       dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __AIRCON_H__
#define __AIRCON_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ================================ Signals ================================ */
typedef enum
{
    evPowerButton,
    evModeButton,
    evFanSpeedUp,
    evFanSpeedDown
}EvAirCon;

/* ------------------------------- Data types ------------------------------ */
/* ================================= Events ================================ */
/* -------------------------- External variables --------------------------- */
/* ======================== Declares active object ========================= */
RKH_SMA_DCLR(airCon);

/* -------------------------- Function prototypes -------------------------- */
/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
