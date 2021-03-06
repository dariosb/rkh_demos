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
#include "rkhfwk_dynevt.h"
#include "blinky.h"
#include "bsp.h"

/* ----------------------------- Local macros ------------------------------ */
#define DELAY   RKH_TIME_SEC(2)

/* ......................... Declares active object ........................ */
typedef struct Blinky Blinky;

/* ................... Declares states and pseudostates .................... */
RKH_DCLR_BASIC_STATE idle, blinking;

/* ........................ Declares initial action ........................ */
static void init(Blinky *const me);

/* ........................ Declares effect actions ........................ */
static void startBlinking(Blinky *const me, RKH_EVT_T *pe);
static void toggleBlinking(Blinky *const me, RKH_EVT_T *pe);
static void turnOffLed(Blinky *const me, RKH_EVT_T *pe);
static void toggleLed(Blinky *const me, RKH_EVT_T *pe);

/* ......................... Declares entry actions ........................ */
/* ......................... Declares exit actions ......................... */
/* ............................ Declares guards ............................ */
static rbool_t isBlinking(Blinky *const me, RKH_EVT_T *pe);

/* ........................ States and pseudostates ........................ */
RKH_CREATE_BASIC_STATE(idle, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(idle)
RKH_TRREG(evBlink,     NULL,        startBlinking,   &blinking),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(blinking, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(blinking)
RKH_TRINT(evBlink,     NULL,        toggleBlinking),
RKH_TRINT(evTimeout,   isBlinking,  toggleLed),
RKH_TRREG(evTimeout,   NULL,        turnOffLed,      &idle),
RKH_END_TRANS_TABLE

/* ............................. Active object ............................. */
struct Blinky
{
    RKH_SMA_T sma;
    RKH_TMR_T timer;
    rui8_t led;
    rui8_t blinking;
};

RKH_SMA_CREATE(Blinky, blinky, 0, FLAT, &idle, init, NULL);
RKH_SMA_DEF_PTR(blinky);

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RKH_ROM_STATIC_EVENT(e_timeout, evTimeout);

/* ---------------------------- Local functions ---------------------------- */
/* ............................ Initial action ............................. */
static void
init(Blinky *const me)
{
    me->led = 0;
    me->blinking = 0;
    bsp_set_led(me->led);

    /* send objects to trazer */
    RKH_TR_FWK_AO(blinky);
    RKH_TR_FWK_STATE(blinky, &idle);
    RKH_TR_FWK_STATE(blinky, &blinking);
    RKH_TR_FWK_OBJ(&me->timer);
    RKH_TR_FWK_FUN(&init);
    RKH_TR_FWK_FUN(&startBlinking);
    RKH_TR_FWK_FUN(&toggleBlinking);
    RKH_TR_FWK_FUN(&turnOffLed);
    RKH_TR_FWK_FUN(&toggleLed);
    RKH_TR_FWK_FUN(&isBlinking);
    RKH_TR_FWK_SIG(evBlink);
    RKH_TR_FWK_SIG(evTimeout);

    RKH_TMR_INIT(&me->timer, &e_timeout, NULL);
}

/* ............................ Effect actions ............................. */
static void
startBlinking(Blinky *const me, RKH_EVT_T *pe)
{
    (void)pe;

    me->blinking = 1;
    me->led = 1;
    bsp_set_led(me->led);

    RKH_TMR_ONESHOT(&me->timer, RKH_UPCAST(RKH_SMA_T, me), DELAY);
}

static void
toggleBlinking(Blinky *const me, RKH_EVT_T *pe)
{
    (void)pe;

    me->blinking ^= 1;
}

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

/* ............................. Entry actions ............................. */
/* ............................. Exit actions .............................. */
/* ................................ Guards ................................. */
static rbool_t
isBlinking(Blinky *const me, RKH_EVT_T *pe)
{
    (void)pe;

    return me->blinking == 1 ? RKH_GTRUE : RKH_GFALSE;
}

/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */

