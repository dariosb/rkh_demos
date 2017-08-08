/**
 *  \file       sliding.c
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2016.03.17  DaBa  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 *  DaBa  Darío Baliña       dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "sliding.h"
#include "bsp.h"

/* ----------------------------- Local macros ------------------------------ */
#define DELAY   RKH_TIME_SEC(2)

/* ......................... Declares active object ........................ */
typedef struct Sliding Sliding;

/* ................... Declares states and pseudostates .................... */
RKH_DCLR_BASIC_STATE closing, closed, opening, open;

/* ........................ Declares initial action ........................ */
static void init(Sliding *const me);

/* ........................ Declares effect actions ........................ */
static void doOpen(Sliding *const me, RKH_EVT_T *pe);
static void doClose(Sliding *const me, RKH_EVT_T *pe);
static void stop(Sliding *const me, RKH_EVT_T *pe);

/* ......................... Declares entry actions ........................ */
/* ......................... Declares exit actions ......................... */
/* ............................ Declares guards ............................ */
/* ........................ States and pseudostates ........................ */
RKH_CREATE_BASIC_STATE(closing, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(closing)
RKH_TRREG(evDoorClose,          NULL,    stop,      &closed),
RKH_TRREG(evSensorTriggered,    NULL,    doOpen,    &opening),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(closed, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(closed)
RKH_TRREG(evSensorTriggered,    NULL,    doOpen,    &opening),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(opening, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(opening)
RKH_TRREG(evDoorOpen,          NULL,     stop,     &open),
RKH_TRREG(evSensorReleased,    NULL,     doClose,  &closing),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(open, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(open)
RKH_TRREG(evSensorReleased,    NULL,    doClose,    &closing),
RKH_END_TRANS_TABLE

/* ............................. Active object ............................. */
struct Sliding
{
    RKH_SMA_T sma;
};

RKH_SMA_CREATE(Sliding, sliding, 0, HCAL, &closing, init, NULL);
RKH_SMA_DEF_PTR(sliding);

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ............................ Initial action ............................. */
static void
init(Sliding *const me)
{
    (void)me;

    bsp_setMotor(OFF, ON);

    /* send objects to trazer */
    RKH_TR_FWK_AO(sliding);
    RKH_TR_FWK_STATE(sliding, &open);
    RKH_TR_FWK_STATE(sliding, &closing);
    RKH_TR_FWK_STATE(sliding, &opening);
    RKH_TR_FWK_STATE(sliding, &closed);
    RKH_TR_FWK_FUN(&init);
    RKH_TR_FWK_FUN(&doOpen);
    RKH_TR_FWK_FUN(&doClose);
    RKH_TR_FWK_FUN(&stop);
    RKH_TR_FWK_SIG(evDoorOpen);
    RKH_TR_FWK_SIG(evDoorClose);
    RKH_TR_FWK_SIG(evSensorTriggered);
    RKH_TR_FWK_SIG(evSensorReleased);
}

/* ............................ Effect actions ............................. */
static void
doOpen(Sliding *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;

    bsp_setMotor(ON, OFF);
}

static void
doClose(Sliding *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;

    bsp_setMotor(OFF, ON);
}

static void
stop(Sliding *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;

    bsp_setMotor(OFF, OFF);
}

/* ............................. Entry actions ............................. */
/* ............................. Exit actions .............................. */
/* ................................ Guards ................................. */
/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */

