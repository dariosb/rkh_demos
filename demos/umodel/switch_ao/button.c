/**
 *  \file       swtich.c
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2016.03.17  DaBa  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  DaBa  Darío Baliña  dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "button.h"
#include "bsp.h"

/* ---------------------- Local functions prototypes ----------------------- */
static void init(void);
static void isOpen(void);
static void closing(void);
static void isClose(void);


/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ======================== States and pseudostates ======================== */
RKH_CREATE_BASIC_STATE(open, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(open)
    RKH_TRREG(evClose,  NULL,   closing,    &debouncing),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(debouncing, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(debouncing)
    RKH_TRREG(evOpen,   NULL,   isOpen,     &open),
    RKH_TRREG(evTout,   NULL,   isClose,    &closed),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(closed, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(closed)
    RKH_TRREG(evOpen,   NULL,   isOpen,     &open),
RKH_END_TRANS_TABLE

/* ---------------------------- Local data types --------------------------- */
typedef struct Button Button;
struct Button
{
    RKH_SM_T sm;
    int foo;
};

/* ---------------------------- Global variables --------------------------- */
/* ============================= Active object ============================= */
RKH_SMA_CREATE(Button, button, 0, FLAT, &open, init, NULL);
RKH_SMA_DEF_PTR(button);

/* ---------------------------- Local variables ---------------------------- */
rui8_t debButton;
static RKH_TMR_T timer;
static RKH_ROM_STATIC_EVENT(e_tout, evTout);

/* ---------------------------- Local functions ---------------------------- */
/* ============================ Initial action ============================= */
static
void
init(void)
{
    debButton = OPEN;
    bsp_debButton(debButton);

    /* send objects to trazer */
    RKH_TR_FWK_AO(button);
    RKH_TR_FWK_STATE(button, &open);
    RKH_TR_FWK_STATE(button, &debouncing);
    RKH_TR_FWK_STATE(button, &closed);
    RKH_TR_FWK_FUN(&init);
    RKH_TR_FWK_FUN(&isOpen);
    RKH_TR_FWK_FUN(&isClose);
    RKH_TR_FWK_FUN(&closing);
    RKH_TR_FWK_OBJ(&timer);

    /* send signals to trazer */
    RKH_TR_FWK_SIG(evOpen);
    RKH_TR_FWK_SIG(evClose);
    RKH_TR_FWK_SIG(evTout);
   
    RKH_TMR_INIT(&timer, &e_tout, NULL);
}

/* ============================ Effect actions ============================= */
static
void
isOpen(void)
{
    debButton = OPEN;
    bsp_debButton(debButton);
    rkh_tmr_stop(&timer);
}

static
void
isClose(void)
{
    debButton = CLOSE;
    bsp_debButton(debButton);
}

static
void 
closing(void)
{
    RKH_TMR_ONESHOT(&timer, button, DELAY);
}

/* ============================= Entry actions ============================= */
/* ============================= Exit actions ============================== */
/* ================================ Guards ================================= */
/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
