/**
 *  \file       blinky.c
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2016.03.17  DaBa  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 *  DaBa  Dar�o Bali�a       dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "blinky.h"
#include "bsp.h"

/* ------------------------------- Data types ------------------------------ */

/* ---------------------- Local functions prototypes ----------------------- */
static void init(Blinky *const me);
static void turnOffLed(Blinky *const me, RKH_EVT_T *pe);
static void toggleLed(Blinky *const me, RKH_EVT_T *pe);

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
#define DELAY   RKH_TIME_SEC(2)

/* ======================== States and pseudostates ======================== */
RKH_DCLR_BASIC_STATE idle, blinking, waitForNextTout;

RKH_CREATE_BASIC_STATE(idle, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(idle)
RKH_TRREG(evBlink,     NULL,        toggleLed,      &blinking),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(blinking, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(blinking)
RKH_TRINT(evTimeout,   NULL,        toggleLed),
RKH_TRREG(evBlink,     NULL,        NULL,       &waitForNextTout),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(waitForNextTout, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(waitForNextTout)
RKH_TRREG(evTimeout,   NULL,        turnOffLed, &idle),
RKH_END_TRANS_TABLE

/* ---------------------------- Local data types --------------------------- */
struct Blinky
{
    RKH_SMA_T sma;
    RKH_TMR_T timer;
    rui8_t led;
};

/* ---------------------------- Global variables --------------------------- */
/* ============================= Active object ============================= */
RKH_SMA_CREATE(Blinky, blinky, 0, FLAT, &idle, init, NULL);
RKH_SMA_DEF_PTR(blinky);

/* ---------------------------- Local variables ---------------------------- */
static RKH_ROM_STATIC_EVENT(e_timeout, evTimeout);

/* ---------------------------- Local functions ---------------------------- */
/* ============================ Initial action ============================= */
static void
init(Blinky *const me)
{
    me->led = 0;
    bsp_set_led(me->led);

    /* send objects to trazer */
    RKH_TR_FWK_AO(blinky);
    RKH_TR_FWK_STATE(blinky, &idle);
    RKH_TR_FWK_STATE(blinky, &blinking);
    RKH_TR_FWK_STATE(blinky, &waitForNextTout);
    RKH_TR_FWK_FUN(&init);
    RKH_TR_FWK_FUN(&turnOffLed);
    RKH_TR_FWK_FUN(&toggleLed);

    RKH_TMR_INIT(&me->timer, &e_timeout, NULL);
}

/* ============================ Effect actions ============================= */
static void
turnOffLed(Blinky *const me, RKH_EVT_T *pe)
{
    (void)pe;

    me->led = 0;
    bsp_set_led(me->led);
}

static void
toggleLed(Blinky *const me, RKH_EVT_T *pe)
{
    (void)pe;

    me->led ^= 1;
    bsp_set_led(me->led);

    RKH_TMR_ONESHOT(&me->timer, RKH_UPCAST(RKH_SMA_T, me), DELAY);
}

/* ============================= Entry actions ============================= */
/* ============================= Exit actions ============================== */
/* ================================ Guards ================================= */
/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */

