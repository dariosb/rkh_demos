/*
 * debug.c
 */

#include "dbgcfg.h"
#include "debug.h"
#include <stdio.h>
#include <stdarg.h>
#include <conio.h>
#include <stdlib.h>

static FILE *fdbg;

void
_dprintf( const char* fmt, ...)
{
    va_list args;

	if( fdbg == NULL )
	{
		if( ( fdbg = fopen( "../fdbg", "w+b" ) ) == NULL )
		{
			perror( "Can't create debug file\n" );
			exit( EXIT_FAILURE );
		}
	}
	
	va_start(args, fmt);

    vfprintf( stdout, fmt, args);

	vfprintf( fdbg, fmt, args );
	fflush( fdbg );

    va_end(args);

}

void
_mdebug( int i, const char *mn, const char *fn )
{
	_dprintf( DBG_OFFSET );
	while( i-- )
		_dprintf( "---" );
	
	_dprintf( "| %s: %s |\r\n", mn, fn );
}


