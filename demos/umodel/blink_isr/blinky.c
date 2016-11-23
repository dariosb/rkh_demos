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
    RKH_TRREG(STOP, NULL,   stop,   &idle),
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
RKH_SM_CREATE(Blinky, blinky, 0, FLAT, &idle, init, NULL);
RKH_SM_DEF_PTR(blinky);

/* ---------------------------- Local variables ---------------------------- */

rui8_t blink, led;
rui32_t led_tick;
RKH_EVT_T evt;

/* ---------------------------- Local functions ---------------------------- */
/* ============================ Initial action ============================= */
static
void
init(void)
{
    blink = 0;
    led = 0;
    bsp_set_led(led);
}

/* ============================ Effect actions ============================= */
static
void
start(void)
{
    led_tick = DELAY;
    led = 1;
    bsp_set_led(led);
}

static
void
stop(void)
{
    led = 0;
    bsp_set_led(led);
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
void
blinky_tick(void)
{
   if( led_tick && (--led_tick == 0) )
   {
       if( blink )
       {
		   led_tick = DELAY;
           MK_SET_EVT(&evt, TOGGLE);
       }
       else
       {
           MK_SET_EVT(&evt, STOP);
       }

       rkh_sm_dispatch(blinky, &evt );
   }
}

void
blinky_blink(void)
{
   blink ^= 1;

   if( blink )
   {
       led_tick = DELAY;
       MK_SET_EVT(&evt, BLINK);
       rkh_sm_dispatch(blinky, &evt );
   }

}

/* ------------------------------ End of file ------------------------------ */
