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

/* ---------------------------- Local data types --------------------------- */
typedef struct AirCon AirCon;
struct AirCon
{
    RKH_SMA_T base;
    ruint fanSpeed;
};

/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ============================ Initial action ============================= */
static void init(AirCon *const me);
/* ============================ Effect actions ============================= */
static void setPowerOn(AirCon *const me);
static void setPowerOff(AirCon *const me);
static void fanSpeed_inc(AirCon *const me);
static void fanSpeed_dec(AirCon *const me);

/* ============================= Entry actions ============================= */
static void setCoolerOn(AirCon *const me);
static void setHeaterOn(AirCon *const me);

/* ============================= Exit actions ============================== */
static void setCoolerOff(AirCon *const me);
static void setHeaterOff(AirCon *const me);

/* ================================ Guards ================================= */
static rbool_t fanSpeed_isInRange(AirCon *const me);
static rbool_t fanSpeed_isNotZero(AirCon *const me);

/* ------------------------------- Statechart  ----------------------------- */
/* ======================== States and pseudostates ======================== */
RKH_DCLR_BASIC_STATE off, cooler, heater;
RKH_DCLR_COMP_STATE on;

RKH_CREATE_BASIC_STATE(off, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(off)
    RKH_TRREG(evPowerButton, NULL, setPowerOn, &on),
RKH_END_TRANS_TABLE

RKH_CREATE_COMP_STATE(on, NULL, NULL, RKH_ROOT, &cooler, NULL);
RKH_CREATE_TRANS_TABLE(on)
    RKH_TRINT(evFanSpeedUp, fanSpeed_isInRange, fanSpeed_inc),
    RKH_TRINT(evFanSpeedDown, fanSpeed_isNotZero, fanSpeed_dec),
    RKH_TRREG(evPowerButton, NULL, setPowerOff, &off),
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

/* ---------------------------- Local functions ---------------------------- */
/* ============================ Initial action ============================= */
static void
init(AirCon *const me)
{
    BSP_AirConInit();
    me->fanSpeed = 0;
}

/* ============================ Effect actions ============================= */
static void
setPowerOn(AirCon *const me)
{
    BSP_AirConPower(SET_ON);
}

static void
setPowerOff(AirCon *const me)
{
    me->fanSpeed=0;

    BSP_AirConPower(SET_OFF);
    BSP_setFanSpeed(me->fanSpeed);    
}

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
setCoolerOn(AirCon *const me)
{
    BSP_setCooler(SET_ON);
}

static void
setHeaterOn(AirCon *const me)
{
    BSP_setHeater(SET_ON);
}

/* ============================= Exit actions ============================== */
static void
setCoolerOff(AirCon *const me)
{
    BSP_setCooler(SET_OFF);
}

static void
setHeaterOff(AirCon *const me)
{
    BSP_setHeater(SET_OFF);
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
/* ------------------------------ End of file ------------------------------ */
