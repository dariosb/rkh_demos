/**
 *  \file       blinky.c
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
#include "blinky.h"
#include "bsp.h"

/* ------------------------------- Data types ------------------------------ */
typedef struct Blinky Blinky;

/* ---------------------- Local functions prototypes ----------------------- */
static void init(Blinky *const me);
static void turnOffLed(Blinky *const me, RKH_EVT_T *pe);
static void toggleLed(Blinky *const me, RKH_EVT_T *pe);

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ======================== States and pseudostates ======================== */
RKH_CREATE_BASIC_STATE(idle, NULL, NULL,  RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(idle)
    RKH_TRREG(evBlink,    NULL,     toggleLed,   &blinking),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(blinking, NULL, NULL,  RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(blinking)
    RKH_TRINT(evTimeout,   NULL,    toggleLed),
    RKH_TRREG(evBlink,    NULL,     turnOffLed,   &idle),
RKH_END_TRANS_TABLE


/* ---------------------------- Local data types --------------------------- */
struct Blinky
{
    RKH_SMA_T sm;
    rui8_t led;
    RKH_TMR_T timer;
};

/* ---------------------------- Global variables --------------------------- */
/* ============================= Active object ============================= */
RKH_SMA_CREATE(Blinky, blinky, 0, FLAT, &idle, init, NULL);
RKH_SMA_DEF_PTR(blinky);

/* ---------------------------- Local variables ---------------------------- */
static RKH_ROM_STATIC_EVENT(e_timeout, evTimeout);

/* ---------------------------- Local functions ---------------------------- */
/* ============================ Initial action ============================= */
static
void
init(Blinky *const me)
{
    me->led = 0;
    bsp_set_led(me->led);

    /* send objects to trazer */
    RKH_TR_FWK_AO(blinky);
    RKH_TR_FWK_STATE(blinky, &idle);
    RKH_TR_FWK_STATE(blinky, &blinking);
    RKH_TR_FWK_FUN(&init);
    RKH_TR_FWK_FUN(&turnOffLed);
    RKH_TR_FWK_FUN(&toggleLed);
    RKH_TR_FWK_OBJ(&me->timer);

    /* send signals to trazer */
    RKH_TR_FWK_SIG(evBlink);
    RKH_TR_FWK_SIG(evTimeout);
   
    RKH_TMR_INIT(&me->timer, &e_timeout, NULL);
}

/* ============================ Effect actions ============================= */
static
void
turnOffLed(Blinky *const me, RKH_EVT_T *pe)
{
    (void)pe;

    me->led = 0;
    bsp_set_led(me->led);
    rkh_tmr_stop(&me->timer);
}

static
void 
toggleLed(Blinky *const me, RKH_EVT_T *pe)
{
    (void)pe;

    me->led ^= 1;
    bsp_set_led(me->led);
    RKH_TMR_ONESHOT(&me->timer, blinky, DELAY);
}


/* ============================= Entry actions ============================= */
/* ============================= Exit actions ============================== */
/* ================================ Guards ================================= */
/* ---------------------------- Global functions --------------------------- */
void
blinky_sm_tick(void)
{
   if( led_tick && (--led_tick == 0) )
   {
       if( blink )
       {
           led_tick = DELAY;
           MK_SET_EVT(&evt, evToggle);
       }
       else
       {
           MK_SET_EVT(&evt, evBlink);
       }

       rkh_sm_dispatch(blinky, &evt );
   }
}

void
blinky_sm_blink(void)
{
   blink ^= 1;

   if( blink )
   {
       led_tick = DELAY;
       MK_SET_EVT(&evt, evBlink);
       rkh_sm_dispatch(blinky, &evt );
   }

}

/* ------------------------------ End of file ------------------------------ */
