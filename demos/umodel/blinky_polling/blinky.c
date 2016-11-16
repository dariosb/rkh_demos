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
#include "oven.h"
#include "bsp.h"

/* ---------------------- Local functions prototypes ----------------------- */
static void start(void);
static void stop(void);
static void toggle(void);


/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ======================== States and pseudostates ======================== */
RKH_CREATE_BASIC_STATE(idle, NULL, NULL,  RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(idle)
    RKH_TRREG(START,   NULL,   start,   &blinking),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(blinking, NULL, NULL,  RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(blinking)
    RKH_TRINT(TOGGLE,   NULL,  toggle),
    RKH_TRREG(STOP,    NULL,   stop,   &idle),
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
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
/* ============================ Initial action ============================= */
static
void
init(void)
{
    bsp_oven_init();

}

/* ============================ Effect actions ============================= */
static
void
start(void)
{

}

static
void
stop(void)
{

}

static
void 
toggle(void)
{

}

/* ============================= Entry actions ============================= */
/* ============================= Exit actions ============================== */
/* ================================ Guards ================================= */
/* ------------------------------ End of file ------------------------------ */
