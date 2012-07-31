/*
 *	serial.h
 *
 * 	Manages serial input and output channels
 */


#include "rkh.h"
#include "serdefs.h"


/*
 *	serial_init:
 *
 * 	Initialize a channel 
 */

void serial_init( HUInt channel );

/*
 * 	put_nchar:
 * 	
 * 	Sends n bytes to output serial interface
 * 	conected to channel. Returns number of bytes actually taken
 * 	to send (normally the same as qty). Receives a pointer to first 
 * 	char 'p' and 'qty' to send. 
 * 	Blocks till there is sufficient space
 */

void put_nchar( HUInt channel, const uchar *p, rkhui16_t qty );


/*
 *	put_string:
 * 	
 * 	Send the null-terminated string p to the serial interface 
 * 	connected to channel. Returns number of characters written.
 * 	Blocks till there is place
 */

void put_string( HUInt channel, const char *p );

/*
 *	put_char:
 * 	
 * 	Send the character given by c to the serial interface 
 * 	connected to channel. Returns number of characters written.
 * 	Blocks till there is place. 
 */

void put_char( HUInt channel, const uchar c);


