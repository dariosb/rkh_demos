/*
 *  --------------------------------------------------------------------------
 *
 *                                Framework RKH
 *                                -------------
 *
 *            State-machine framework for reactive embedded systems
 *
 *                      Copyright (C) 2010 Leandro Francucci.
 *          All rights reserved. Protected by international copyright laws.
 *
 *
 *  RKH is free software: you can redistribute it and/or modify it under the
 *  terms of the GNU General Public License as published by the Free Software
 *  Foundation, either version 3 of the License, or (at your option) any
 *  later version.
 *
 *  RKH is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with RKH, see copying.txt file.
 *
 *  Contact information:
 *  RKH web site:   http://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail:         francuccilea@gmail.com
 *  ---------------------------------------------------------------------------
 */

/**
 *  \file       bsp.c
 *  \ingroup    bsp
 *
 *  \brief      BSP for EduCIAA NXP.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.10.24  DaBa  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 *  DaBa  Darío Baliña  dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "bsp.h"
#include "oven.h"
#include "rkh.h"
#include "leds.h"
#include "switch.h"

#include "ciaaPOSIX_stdio.h"  /* <= device handler header */
#include "ciaaPOSIX_string.h" /* <= string header */
#include "ciaak.h"            /* <= ciaa kernel header */

RKH_THIS_MODULE

/* ----------------------------- Local macros ------------------------------ */
#if SERIAL_TRACE == 1

static int32_t utrc;
    #define TRACE_UART_FD   "/dev/serial/uart/1"
    #define TRACE_UART_BAUD (void *)ciaaBAUDRATE_115200

/* Trazer Tool COM Port */
    #define SERIAL_TRACE_OPEN()                                              \
    {                                                                        \
        utrc = ciaaPOSIX_open(TRACE_UART_FD, ciaaPOSIX_O_WRONLY);            \
        ciaaPOSIX_ioctl(utrc,                                                \
                        ciaaPOSIX_IOCTL_SET_BAUDRATE, TRACE_UART_BAUD);      \
        ActivateTask(RkhTraceTask);                                          \
    }

    #define SERIAL_TRACE_CLOSE()  \
    {                             \
        ciaaPOSIX_close(utrc);    \
    }

    #define SERIAL_TRACE_SEND_BLOCK(buf_, len_)     \
            ciaaPOSIX_write(utrc, buf_, len_)
#else
    #define SERIAL_TRACE_OPEN()                     (void)0
    #define SERIAL_TRACE_CLOSE()                    (void)0
    #define SERIAL_TRACE_SEND(d)                    (void)0
    #define SERIAL_TRACE_SEND_BLOCK(buf_, len_)     (void)0
#endif

/* ------------------------------- Constants ------------------------------- */
#define BLINK_LED_MASK  0x20;

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
#if RKH_CFG_TRC_EN == 1
rui8_t trace_open;
#endif

/* ---------------------------- Local variables ---------------------------- */
#if defined(RKH_USE_TRC_SENDER)
static rui8_t door;
static rui8_t panel;
#endif

static RKH_ROM_STATIC_EVENT( e_start, START );
static RKH_ROM_STATIC_EVENT( e_open, OPEN );
static RKH_ROM_STATIC_EVENT( e_close, CLOSE );
static RKH_ROM_STATIC_EVENT( e_term, TERM );
#if ( __STOP_BUTTON__ == RKH_ENABLED )
static RKH_ROM_STATIC_EVENT( e_stop, STOP );
#endif

#if RKH_CFG_TRC_EN == 1
static RKH_TS_T bsp_tstamp;
#endif

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void
rkh_hook_timetick(void)
{
#if RKH_CFG_TRC_EN == 1
    ++bsp_tstamp;
#endif
  	switch_tick();
}

void
rkh_hook_start(void)
{
}

void
rkh_hook_exit(void)
{
    RKH_TRC_FLUSH();
}

void
rkh_assert(RKHROM char * const file, int line)
{
    ciaaPOSIX_printf("RKH_ASSERT: [%d] line from %s "
                     "file\n", line, file);
    RKH_DIS_INTERRUPT();
    RKH_TR_FWK_ASSERT((RKHROM char *)file, __LINE__);
    rkh_fwk_exit();
}

#if RKH_CFG_TRC_EN == 1

void
rkh_trc_open(void)
{
    trace_open = (rui8_t)1;
    rkh_trc_init();
    SERIAL_TRACE_OPEN()
    RKH_TRC_SEND_CFG(BSP_TS_RATE_HZ);
}

void
rkh_trc_close(void)
{
    trace_open = (rui8_t)0;
    SERIAL_TRACE_CLOSE();
}

RKH_TS_T
rkh_trc_getts(void)
{
    return bsp_tstamp;
}

void
rkh_trc_flush(void)
{
    rui8_t *blk;
    TRCQTY_T nbytes;
    RKH_SR_ALLOC();

    FOREVER
    {
        nbytes = 128;

        RKH_ENTER_CRITICAL_();
        blk = rkh_trc_get_block(&nbytes);
        RKH_EXIT_CRITICAL_();

        if ((blk != (rui8_t *)0))
        {
        	while( nbytes )
        	{
               nbytes -= SERIAL_TRACE_SEND_BLOCK(blk, nbytes);
        	}
        }
        else
        {
            break;
        }
    }
}
#endif

void
bsp_pub_sw_evt( ruint s, ruint debsw )
{
 	switch( s )
	{
		case START_SW:
			RKH_SMA_POST_FIFO( oven, &e_start, &panel );
			break;

#if ( __STOP_BUTTON__ == RKH_ENABLED )			
		case STOP_SW:
			RKH_SMA_POST_FIFO( oven, &e_stop, &panel );
			break;
#endif

		case DOOR_SW:
			if( debsw == SW_PRESS )
				RKH_SMA_POST_FIFO( oven, &e_close, &door );
			else
				RKH_SMA_POST_FIFO( oven, &e_open, &door );
			break;			
	}
}

void
bsp_door_open( void )
{
	set_rgb_led( RGB_BLACK );	
}

void
bsp_oven_init( void )
{

}

void
bsp_emitter_ready( void )
{
	set_rgb_led( RGB_LIME );
}

void
bsp_emitter_on( void )
{
	set_rgb_led( RGB_RED );
}

void
bsp_emitter_pause( void )
{
	set_rgb_led( RGB_YELLOW );
}

void
bsp_emitter_continue( void )
{
	set_rgb_led( RGB_RED );
}

void
bsp_emitter_off( void )
{
	set_rgb_led( RGB_BLACK );
}

void
bsp_init(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    rkh_fwk_init();

    init_leds();
    init_switch();

	RKH_FILTER_OFF_SMA( oven );
	RKH_FILTER_OFF_EVENT( RKH_TE_SMA_LIFO );
	RKH_FILTER_OFF_EVENT( RKH_TE_SMA_FIFO );
	RKH_FILTER_OFF_EVENT( RKH_TE_SMA_DCH );
	RKH_FILTER_OFF_EVENT( RKH_TE_SM_STATE );
//	RKH_FILTER_OFF_EVENT( RKH_TE_SM_TS_STATE );
	RKH_FILTER_OFF_EVENT( RKH_TE_FWK_DEFER );
	RKH_FILTER_OFF_EVENT( RKH_TE_FWK_RCALL );
//	RKH_FILTER_OFF_GROUP_ALL_EVENTS( RKH_TG_SM );

	RKH_FILTER_OFF_ALL_SIGNALS();

	RKH_TRC_OPEN();

#if defined( RKH_USE_TRC_SENDER )
	RKH_TR_FWK_OBJ( &panel );
	RKH_TR_FWK_OBJ( &door );
#endif	    
}

/* ------------------------------ End of file ------------------------------ */
