/**
 	\file PR_LCD.c
 	\brief Primitiva del LCD
 	\details Validas para LCD de 2 lineas
 	\author Pablo Irrera Condines
 	\date 2013.05.08
*/
#include "PR_LCD.h"
#include "FW_LCD.h"

void DisplayLCD( char * msg, uint8_t r , uint8_t pos )
{
	uint8_t i ;

	switch ( r )
	{
		case RENGLON_1:
			PushLCD( pos + 0x80 , LCD_CONTROL );
			break;
		case RENGLON_2:
			PushLCD( pos + 0xc0 , LCD_CONTROL );
			break;
	}
	for( i = 0 ; msg[ i ] != '\0' ; i++ )
		PushLCD( msg [ i ] , LCD_DATA );
}
