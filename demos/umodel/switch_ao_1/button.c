/**
 *  \file       button.c
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
#include "button.h"
#include "bsp.h"

/* ----------------------------- Local macros ------------------------------ */
#define DELAY   RKH_TIME_SEC(2)

/* ......................... Declares active object ........................ */
typedef struct Button Button;

/* ................... Declares states and pseudostates .................... */
RKH_DCLR_BASIC_STATE open, closing, closed;

/* ........................ Declares initial action ........................ */
static void init(Button *const me);

/* ........................ Declares effect actions ........................ */
static void buttonClosing(Button *const me, RKH_EVT_T *pe);
static void buttonOpen(Button *const me, RKH_EVT_T *pe);
static void buttonClose(Button *const me, RKH_EVT_T *pe);
static void buttonIsClosed(Button *const me, RKH_EVT_T *pe);
static void buttonIsOpen(Button *const me, RKH_EVT_T *pe);

/* ......................... Declares entry actions ........................ */
/* ......................... Declares exit actions ......................... */
/* ............................ Declares guards ............................ */
static rbool_t isClose(Button *const me, RKH_EVT_T *pe);
static rbool_t isOpen(Button *const me, RKH_EVT_T *pe);

/* ........................ States and pseudostates ........................ */
RKH_CREATE_BASIC_STATE(open, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(open)
RKH_TRREG(evClose,     NULL,    buttonClosing,      &closing),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(closing, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(closing)
RKH_TRINT(evOpen,      NULL,    buttonOpen),
RKH_TRINT(evClose,     NULL,    buttonClose),
RKH_TRREG(evTimeout,   isOpen,  NULL,               &open),
RKH_TRREG(evTimeout,   isClose, buttonIsClosed,     &closed),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(closed, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(closed)
RKH_TRREG(evOpen,      NULL,    buttonIsOpen,       &open),
RKH_END_TRANS_TABLE

/* ............................. Active object ............................. */
struct Button
{
    RKH_SMA_T sma;
    RKH_TMR_T timer;
    rui8_t st;
};

RKH_SMA_CREATE(Button, button, 0, FLAT, &open, init, NULL);
RKH_SMA_DEF_PTR(button);

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RKH_ROM_STATIC_EVENT(e_timeout, evTimeout);

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ............................ Initial action ............................. */
static void
init(Button *const me)
{
    bsp_button(OPEN);

    /* send objects to trazer */
    RKH_TR_FWK_AO(button);
    RKH_TR_FWK_STATE(button, &open);
    RKH_TR_FWK_STATE(button, &closing);
    RKH_TR_FWK_STATE(button, &closed);
    RKH_TR_FWK_FUN(&init);
    RKH_TR_FWK_FUN(&buttonIsOpen);
    RKH_TR_FWK_FUN(&buttonClosing);
    RKH_TR_FWK_FUN(&buttonIsClosed);
    RKH_TR_FWK_FUN(&buttonOpen);
    RKH_TR_FWK_FUN(&buttonClose);
    RKH_TR_FWK_FUN(&isClose);
    RKH_TR_FWK_FUN(&isOpen);
    RKH_TR_FWK_SIG(evOpen);
    RKH_TR_FWK_SIG(evClose);
    RKH_TR_FWK_SIG(evTimeout);
    RKH_TR_FWK_OBJ(&me->timer);

    RKH_TMR_INIT(&me->timer, &e_timeout, NULL);
}

/* ............................ Effect actions ............................. */
static void
buttonClosing(Button *const me, RKH_EVT_T *pe)
{
    (void)pe;

    me->st = CLOSE; 
    RKH_TMR_ONESHOT(&me->timer, RKH_UPCAST(RKH_SMA_T, me), DELAY);
}

static void
buttonOpen(Button *const me, RKH_EVT_T *pe)
{
    (void)pe;

    me->st = OPEN; 
}

static void
buttonClose(Button *const me, RKH_EVT_T *pe)
{
    (void)pe;

    me->st = CLOSE; 
}

static void
buttonIsClosed(Button *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;

    bsp_button(CLOSE);
}

static void
buttonIsOpen(Button *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;

    bsp_button(OPEN);
}

/* ............................. Entry actions ............................. */
/* ............................. Exit actions .............................. */
/* ................................ Guards ................................. */
static rbool_t
isClose(Button *const me, RKH_EVT_T *pe)
{
    (void)pe;

    return me->st == CLOSE ? RKH_GTRUE : RKH_GFALSE;
}

static rbool_t
isOpen(Button *const me, RKH_EVT_T *pe)
{
    (void)pe;

    return me->st == OPEN ? RKH_GTRUE : RKH_GFALSE;
}

/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */

