/**
 *  \file       aircon.c
 *
 *  \brief      Air Conditioner Active object specification.
 *
 *  This file implements the active object and frequently its own state 
 *  machine. Please correlate this implementation with the corresponding 
 *  state diagram.
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
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "aircon.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
typedef struct AirCon AirCon;
struct AirCon
{
    RKH_SMA_T base;
};

/* ---------------------------- Global variables --------------------------- */


/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */

/* ============================ Initial action ============================= */
static void init(AirCon *const me);

/* ============================ Effect actions ============================= */
static void fanOnOff(AirCon *const me);
static void setHeater(AirCon *const me);
static void setCooler(AirCon *const me);

/* ============================= Entry actions ============================= */
static void setOn(AirCon *const me);

/* ============================= Exit actions ============================== */
static void setOff(AirCon *const me);

/* ================================ Guards ================================= */

/* -------------------------- Active object --------------------------- */
/* ============================= Active object ============================= */
/* ======================== States and pseudostates ======================== */
RKH_DCLR_BASIC_STATE off, cooler, heater;
RKH_DCLR_COMP_STATE on;

RKH_CREATE_BASIC_STATE(off, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(off)
    RKH_TRREG(evPowerButton, NULL, NULL, &on),
RKH_END_TRANS_TABLE

RKH_CREATE_COMP_STATE(on, setOn, setOff, RKH_ROOT, &cooler, NULL);
RKH_CREATE_TRANS_TABLE(on)
    RKH_TRINT(evFanButton, NULL, fanOnOff),
    RKH_TRREG(evPowerButton, NULL, NULL, &off),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(cooler, NULL, NULL, &on, NULL);
RKH_CREATE_TRANS_TABLE(cooler)
    RKH_TRREG(evModeButton, NULL, setHeater, &heater),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(heater, NULL, NULL, &on, NULL);
RKH_CREATE_TRANS_TABLE(heater)
    RKH_TRREG(evModeButton, NULL, setCooler, &cooler),
RKH_END_TRANS_TABLE

/* ============================= Active object ============================= */
RKH_SMA_CREATE(AirCon, airCon, 0, HCAL, &off, init, NULL);
RKH_SMA_DEF_PTR(airCon);

/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */

/* ============================ Initial action ============================= */
static void
init(AirCon *const me)
{
}

/* ============================ Effect actions ============================= */
static void
fanOnOff(AirCon *const me)
{
}

static void
setHeater(AirCon *const me)
{
}

static void
setCooler(AirCon *const me)
{
}

/* ============================= Entry actions ============================= */
static void
setOn(AirCon *const me)
{
}

/* ============================= Exit actions ============================== */
static void
setOff(AirCon *const me)
{
}

/* ================================ Guards ================================= */


/* ------------------------------ End of file ------------------------------ */
