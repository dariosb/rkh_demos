/*
 * swhdl.c
 */

#include "derivative.h"
#include "swhdl.h"
#include "io.h"

uchar
rawsw1( void )
{
	return read_iopin( PSHBUTT1 );
}

uchar
rawsw2( void )
{
	return read_iopin( PSHBUTT2 );
}

uchar
rawsw3( void )
{
	return read_iopin( PSHBUTT3 );
}

uchar
rawsw4( void )
{
	return read_iopin( PSHBUTT4 );
}
