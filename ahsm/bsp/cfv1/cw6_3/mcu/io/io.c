/*
 *	ioports.c
 *	
 *	Routines for PORTS initialization.
 *
 *	Programmer: Dar�o S. Bali�a.
 *	Date : 26/05/06.
 */

#include "derivative.h"
#include "io.h"

void
io_init(void)
{
	init_leds();
	init_pshbuts();
	init_comen();
}

