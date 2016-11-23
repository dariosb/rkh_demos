/**
 *  \file       main.c
 *  \brief      uModel Led blinky polling implementation.
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
#include <stdio.h>
#include <conio.h>

#include "rkh.h"
#include "rkhtrc.h"
#include "blinky.h"
#include "bsp.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
#define ESC             0x1B

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
rui8_t running;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static
void
print_banner(void)
{
    printf("\"Blinky Polling\" example\n\n");
    printf("RKH version      = %s\n", RKH_RELEASE);
    printf("Port version     = %s\n", rkh_get_port_version());
    printf("Port description = %s\n\n", rkh_get_port_desc());
    printf("\n\n");

    printf("1.- Press 'B'/'b' blink\n");
    printf("2.- Press 'escape' to quit.\n\n\n");
}

static
int
test_keyboard(int *c)
{
    if(_kbhit())
    {
        *c = tolower(_getch());
        return 1;
    }

    return 0;
}

/* ---------------------------- Global functions --------------------------- */
void
rkh_hook_idle( void )
{
}

void
bsp_set_led( rui8_t led )
{
   printf("LED %s\n", led ? "ON" : "OFF");
}

int
main(int argc, char *argv[])
{
    int c, tick_msec;
    
    (void)argc;
    (void)argv;

    tick_msec = 1000UL / BSP_TICKS_PER_SEC;
    running = 1;

    print_banner();

    rkh_sm_init(blinky);

    while (running)
    {
        Sleep(tick_msec);
        blinky_tick();

        if (test_keyboard(&c))
        {
            switch (c)
            {
                case ESC:
                    running = 0;
                    break;

                case 'b':
                    blinky_blink();
                    break;

                default:
                    break;
            }
        }
    }
    return 0;
}

/* ------------------------------ End of file ------------------------------ */
