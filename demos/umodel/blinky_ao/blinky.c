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

/* ---------------------- Local functions prototypes ----------------------- */
static void init(void);
static void start(void);
static void stop(void);
static void toggle(void);


/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ======================== States and pseudostates ======================== */
RKH_CREATE_BASIC_STATE(idle, NULL, NULL,  RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(idle)
    RKH_TRREG(BLINK,    NULL,   start,   &blinking),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(blinking, NULL, NULL,  RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(blinking)
    RKH_TRINT(TOGGLE,   NULL,   toggle),
    RKH_TRREG(BLINK,    NULL,   stop,   &idle),
RKH_END_TRANS_TABLE


/* ---------------------------- Local data types --------------------------- */
typedef struct Blinky Blinky;
struct Blinky
{
    RKH_SM_T sm;
    int foo;
};

/* ---------------------------- Global variables --------------------------- */
/* ============================= Active object ============================= */
RKH_SMA_CREATE(Blinky, blinky, 0, FLAT, &idle, init, NULL);
RKH_SMA_DEF_PTR(blinky);

/* ---------------------------- Local variables ---------------------------- */
rui8_t led;
static RKH_TMR_T timer;
static RKH_ROM_STATIC_EVENT(e_toggle, TOGGLE);

/* ---------------------------- Local functions ---------------------------- */
/* ============================ Initial action ============================= */
static
void
init(void)
{
    led = 0;
    bsp_set_led(led);

    /* send objects to trazer */
    RKH_TR_FWK_AO(blinky);
    RKH_TR_FWK_STATE(blinky, &idle);
    RKH_TR_FWK_STATE(blinky, &blinking);
    RKH_TR_FWK_FUN(&init);
    RKH_TR_FWK_FUN(&start);
    RKH_TR_FWK_FUN(&stop);
    RKH_TR_FWK_FUN(&toggle);
    RKH_TR_FWK_OBJ(&timer);

    /* send signals to trazer */
    RKH_TR_FWK_SIG(BLINK);
    RKH_TR_FWK_SIG(TOGGLE);
    RKH_TR_FWK_SIG(STOP);
    RKH_TR_FWK_SIG(TERM);
   
    RKH_TMR_INIT(&timer, &e_toggle, NULL);
}

/* ============================ Effect actions ============================= */
static
void
start(void)
{
    led = 1;
    bsp_set_led(led);
    RKH_TMR_PERIODIC(&timer, blinky, DELAY, DELAY);
    
}

static
void
stop(void)
{
    led = 0;
    bsp_set_led(led);
    rkh_tmr_stop(&timer);
}

static
void 
toggle(void)
{
    led ^= 1;
    bsp_set_led(led);
}

/* ============================= Entry actions ============================= */
/* ============================= Exit actions ============================== */
/* ================================ Guards ================================= */
/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
