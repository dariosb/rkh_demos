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
#define MAX_FAN_SPEED   5

/* ---------------------------- Local data types --------------------------- */
typedef enum
{
    POWER_OFF,
    POWER_ON
} Power_t;

typedef enum
{
    COOLER_MODE,
    HEATER_MODE
} Mode_t;

typedef struct AirCon AirCon;
struct AirCon
{
    RKH_SMA_T base;
    ruint fanSpeed;
    Power_t power;
    Mode_t mode;
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
    me->power = POWER_OFF;
    me->mode = COOLER_MODE;
}

/* ============================ Effect actions ============================= */
static void
setPowerOn(AirCon *const me)
{
    me->power = POWER_ON;
}

static void
setPowerOff(AirCon *const me)
{
    me->power = POWER_OFF;
}

static void
fanSpeed_inc(AirCon *const me)
{
    ++me->fanSpeed;
}

static void
fanSpeed_dec(AirCon *const me)
{
   --me->fanSpeed; 
}

/* ============================= Entry actions ============================= */
static void
setCoolerMode(AirCon *const me)
{
    me->mode = COOLER_MODE;
}

static void
setHeaterMode(AirCon *const me)
{
    me->mode = HEATER_MODE;
}

/* ============================= Exit actions ============================== */
static void
fanSpeed_clear(AirCon *const me)
{
    me->fanSpeed = 0;
}

/* ================================ Guards ================================= */
static rbool_t
fanSpeed_isInRange(AirCon *const me)
{
    return (me->fanSpeed < MAX_FAN_SPEED) ? RKH_GTRUE : RKH_GFALSE;
}

static rbool_t
fanSpeed_isNotZero(AirCon *const me)
{
    return (me->fanSpeed) ? RKH_GTRUE : RKH_GFALSE;
}

/* ---------------------------- Global functions --------------------------- */
/* ------------------------------- Statechart  ----------------------------- */
/* ======================== States and pseudostates ======================== */
RKH_DCLR_BASIC_STATE off, cooler, heater;
RKH_DCLR_COMP_STATE on;

RKH_CREATE_BASIC_STATE(off, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(off)
    RKH_TRREG(evPowerButton, NULL, setPowerOn, &on),
RKH_END_TRANS_TABLE

RKH_CREATE_COMP_STATE(on, NULL, fanSpeed_clear, RKH_ROOT, &cooler, NULL);
RKH_CREATE_TRANS_TABLE(on)
    RKH_TRINT(evFanSpeedUp, fanSpeed_isInRange, fanSpeed_inc),
    RKH_TRINT(evFanSpeedDown, fanSpeed_isNotZero, fanSpeed_dec),
    RKH_TRREG(evPowerButton, NULL, setPowerOff, &off),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(cooler, setCoolerMode, NULL, &on, NULL);
RKH_CREATE_TRANS_TABLE(cooler)
    RKH_TRREG(evModeButton, NULL, NULL, &heater),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(heater, setHeaterMode, NULL, &on, NULL);
RKH_CREATE_TRANS_TABLE(heater)
    RKH_TRREG(evModeButton, NULL, NULL, &cooler),
RKH_END_TRANS_TABLE

/* ----------------------------- Active object ----------------------------- */
RKH_SMA_CREATE(AirCon, airCon, 0, HCAL, &off, init, NULL);
RKH_SMA_DEF_PTR(airCon);

/* ------------------------------ End of file ------------------------------ */
