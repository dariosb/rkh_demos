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
#include "bsp.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
#define MAX_FAN_SPEED   5

enum { POWER_OFF, POWER_ON };
enum { COOLER_MODE, HEATER_MODE };

/* ---------------------------- Local data types --------------------------- */
typedef struct AirCon AirCon;
struct AirCon
{
    RKH_SMA_T base;
    unsigned int fanSpeed;
};

/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ============================ Initial action ============================= */
static void
init(AirCon *const me)
{
    me->fanSpeed = 0;
}

/* ============================ Effect actions ============================= */
static void
fanSpeed_inc(AirCon *const me)
{
    BSP_setFanSpeed(++me->fanSpeed);
}

static void
fanSpeed_dec(AirCon *const me)
{
    BSP_setFanSpeed(--me->fanSpeed);
}

/* ============================= Entry actions ============================= */
static void
setPowerOff(AirCon *const me)
{
    BSP_setPowerOff();
}

static void
setPowerOn(AirCon *const me)
{
    BSP_setPowerOn();
}

static void
setCoolerOn(AirCon *const me)
{
    BSP_setCoolerOn();
}

static void
setHeaterOn(AirCon *const me)
{
    BSP_setHeaterOn();
}

/* ============================= Exit actions ============================== */
static void
setCoolerOff(AirCon *const me)
{
    BSP_setCoolerOff();
}

static void
setHeaterOff(AirCon *const me)
{
    BSP_setHeaterOff();
}

/* ================================ Guards ================================= */
static rbool_t
fanSpeed_isNotZero(AirCon *const me)
{
    return (me->fanSpeed != 0) ? RKH_GTRUE : RKH_GFALSE;
}

static rbool_t
fanSpeed_isInRange(AirCon *const me)
{
    return ((0 <= me->fanSpeed) && (me->fanSpeed < MAX_FAN_SPEED)) ? 
            RKH_GTRUE : RKH_GFALSE;
}

/* ---------------------------- Global functions --------------------------- */
/* ------------------------------- Statechart  ----------------------------- */
/* ======================== States and pseudostates ======================== */
RKH_DCLR_BASIC_STATE off, cooler, heater;
RKH_DCLR_COMP_STATE on;

RKH_CREATE_BASIC_STATE(off, setPowerOff, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(off)
    RKH_TRREG(evPowerButton, NULL, NULL, &on),
RKH_END_TRANS_TABLE

RKH_CREATE_COMP_REGION_STATE(on, setPowerOn, NULL, RKH_ROOT, &cooler,
                             NULL, RKH_NO_HISTORY, NULL, NULL, NULL, NULL);
RKH_CREATE_TRANS_TABLE(on)
    RKH_TRINT(evFanSpeedDown, fanSpeed_isNotZero, fanSpeed_dec),
    RKH_TRINT(evFanSpeedUp, fanSpeed_isInRange, fanSpeed_inc),
    RKH_TRREG(evPowerButton, NULL, NULL, &off),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(cooler, setCoolerOn, setCoolerOff, &on, NULL);
RKH_CREATE_TRANS_TABLE(cooler)
    RKH_TRREG(evModeButton, NULL, NULL, &heater),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(heater, setHeaterOn, setHeaterOff, &on, NULL);
RKH_CREATE_TRANS_TABLE(heater)
    RKH_TRREG(evModeButton, NULL, NULL, &cooler),
RKH_END_TRANS_TABLE

/* ----------------------------- Active object ----------------------------- */
RKH_SMA_CREATE(AirCon, airCon, 0, HCAL, &off, init, NULL);
RKH_SMA_DEF_PTR(airCon);

/* ------------------------------ End of file ------------------------------ */
