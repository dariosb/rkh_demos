/**
 *	file		LedRKH.c
 */

/* -------------------------- Development history -------------------------- */
/*
 * 24-08-2018 11:09:58 v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 * Nahuel
 */

/* --------------------------------- Notes --------------------------------- */


/* ----------------------------- Include files ----------------------------- */
#include "rkh.h" 
#include "LedRKH.h" 
#include "bsp.h" 

/* ----------------------------- Local macros ------------------------------ */
#define DELAY   RKH_TIME_SEC(2)

/* ......................... Declares active object ........................ */
typedef struct LedRKH LEDRKH;

RKH_DCLR_BASIC_STATE apagado, encendido;

/* ........................ Declares initial action ........................ */
static void init(LEDRKH *const me);

/* ........................ Declares effect actions ........................ */
static void EncenderLed (LEDRKH *const me, RKH_EVT_T *pe);
static void ApagarLed (LEDRKH *const me, RKH_EVT_T *pe);

/* ......................... Declares entry actions ........................ */

/* ......................... Declares exit actions ......................... */

/* ............................ Declares guards ............................ */

/* ........................ States and pseudostates ........................ */
RKH_CREATE_BASIC_STATE(apagado, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(apagado)
	RKH_TRREG(evTeclaPrender, NULL,EncenderLed, &encendido),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(encendido, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(encendido)
	RKH_TRREG(evTeclaApagar, NULL,ApagarLed, &apagado),
RKH_END_TRANS_TABLE


/* ............................. Active object ............................. */
struct LedRKH
{
	RKH_SMA_T sma;
};
RKH_SMA_CREATE(LEDRKH, LedRKH, 0, FLAT, &apagado, init, NULL);
RKH_SMA_DEF_PTR(LedRKH);

/* ------------------------------- Constants ------------------------------- */

/* ---------------------------- Local data types --------------------------- */

/* ---------------------------- Global variables --------------------------- */

/* ---------------------------- Local variables ---------------------------- */

/* ----------------------- Local function prototypes ----------------------- */

/* ---------------------------- Local functions ---------------------------- */

/* ............................ Initial action ............................. */

static void
init(LEDRKH * const me)
{
	(void)me;

	bsp_ApagarLed();

	/* send objects to trazer */
	RKH_TR_FWK_AO(LedRKH);
	RKH_TR_FWK_STATE(LedRKH, &apagado);
	RKH_TR_FWK_STATE(LedRKH, &encendido);
	RKH_TR_FWK_FUN(&init);
	RKH_TR_FWK_FUN(&EncenderLed);
	RKH_TR_FWK_FUN(&ApagarLed);
}

/* ............................ Effect actions ............................. */
static void 
EncenderLed (LEDRKH *const me, RKH_EVT_T *pe)
{
	(void)me;
	(void)pe;

	bsp_EncenderLed();
}

static void 
ApagarLed (LEDRKH *const me, RKH_EVT_T *pe)
{
	(void)me;
	(void)pe;

	bsp_ApagarLed();
}

/* ............................. Entry actions ............................. */

/* ............................. Exit actions .............................. */

/* ................................ Guards ................................. */

/* ---------------------------- Global functions --------------------------- */


/* ------------------------------ End of file ------------------------------ */
