/**
 	\file PR_DislayMatricial.c
 	\brief Primitiva de display matricial
 	\details para N displays dispuestos en una fila
 	\author Pablo Irrera Condines
 	\date 2013.05.08
*/

#include "PR_DisplayMatricial.h"
#include "FW_DisplayMatricial.h"
#include "FW_Timertick.h"
#include "string.h"

const uint8_t MatrizCaracteres[256][7] =
{
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //' '
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x04}, //'!'
	{0x0A, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00}, //'"'
	{0x0A, 0x0A, 0x1F, 0x0A, 0x1F, 0x0A, 0x0A}, //'#'
	{0x04, 0x0E, 0x10, 0x0E, 0x01, 0x0E, 0x04}, //'$'
	{0x18, 0x19, 0x02, 0x04, 0x08, 0x13, 0x03}, //'%'
	{0x0C, 0x12, 0x12, 0x0C, 0x13, 0x12, 0x0D}, //'&'
	{0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00}, //'''
	{0x02, 0x04, 0x08, 0x08, 0x08, 0x04, 0x02}, //'('
	{0x08, 0x04, 0x02, 0x02, 0x02, 0x04, 0x08}, //')'
	{0x00, 0x04, 0x15, 0x0E, 0x15, 0x04, 0x00}, //'*'
	{0x00, 0x04, 0x04, 0x1F, 0x04, 0x04, 0x00}, //'+'
	{0x00, 0x00, 0x00, 0x00, 0x0C, 0x04, 0x08}, //','
	{0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00}, //'-'
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C}, //'.'
	{0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x00}, //'/'
	{0x0E, 0x11, 0x13, 0x15, 0x19, 0x11, 0x0E}, //'0'
	{0x04, 0x0C, 0x14, 0x04, 0x04, 0x04, 0x0E}, //'1'
	{0x0E, 0x11, 0x01, 0x02, 0x04, 0x08, 0x1F}, //'2'
	{0x0E, 0x11, 0x01, 0x0E, 0x01, 0x11, 0x0E}, //'3'
	{0x02, 0x06, 0x0A, 0x12, 0x1F, 0x02, 0x02}, //'4'
	{0x1F, 0x10, 0x10, 0x1E, 0x01, 0x01, 0x1E}, //'5'
	{0x06, 0x08, 0x10, 0x1E, 0x11, 0x11, 0x0E}, //'6'
	{0x1F, 0x01, 0x02, 0x04, 0x08, 0x08, 0x08}, //'7'
	{0x0E, 0x11, 0x11, 0x0E, 0x11, 0x11, 0x0E}, //'8'
	{0x0E, 0x11, 0x11, 0x0F, 0x01, 0x01, 0x0E}, //'9'
	{0x00, 0x0C, 0x0C, 0x00, 0x0C, 0x0C, 0x00}, //':'
	{0x00, 0x0C, 0x0C, 0x00, 0x0C, 0x04, 0x08}, //';'
	{0x02, 0x04, 0x08, 0x10, 0x08, 0x04, 0x02}, //'<'
	{0x00, 0x00, 0x1F, 0x00, 0x1F, 0x00, 0x00}, //'='
	{0x08, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08}, //'>'
	{0x0E, 0x11, 0x01, 0x02, 0x04, 0x00, 0x04}, //'?'
	{0x0E, 0x11, 0x17, 0x15, 0x17, 0x10, 0x0E}, //'@'
	{0x0E, 0x11, 0x11, 0x11, 0x1F, 0x11, 0x11}, //'A'
	{0x1E, 0x11, 0x11, 0x1E, 0x11, 0x11, 0x1E}, //'B'
	{0x0E, 0x11, 0x10, 0x10, 0x10, 0x11, 0x0E}, //'C'
	{0x1C, 0x12, 0x11, 0x11, 0x11, 0x12, 0x1C}, //'D'
	{0x1F, 0x10, 0x10, 0x1E, 0x10, 0x10, 0x1F}, //'E'
	{0x1F, 0x10, 0x10, 0x1E, 0x10, 0x10, 0x10}, //'F'
	{0x0E, 0x11, 0x10, 0x17, 0x11, 0x11, 0x0E}, //'G'
	{0x11, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11}, //'H'
	{0x0E, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0E}, //'I'
	{0x07, 0x02, 0x02, 0x02, 0x02, 0x12, 0x0C}, //'J'
	{0x11, 0x12, 0x14, 0x18, 0x14, 0x12, 0x11}, //'K'
	{0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F}, //'L'
	{0x11, 0x1B, 0x15, 0x15, 0x11, 0x11, 0x11}, //'M'
	{0x11, 0x11, 0x19, 0x15, 0x13, 0x11, 0x11}, //'N'
	{0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E}, //'O'
	{0x1E, 0x11, 0x11, 0x1E, 0x10, 0x10, 0x10}, //'P'
	{0x0E, 0x11, 0x11, 0x11, 0x15, 0x0E, 0x01}, //'Q'
	{0x1E, 0x11, 0x11, 0x1E, 0x14, 0x12, 0x11}, //'R'
	{0x0E, 0x11, 0x10, 0x0E, 0x01, 0x11, 0x0E}, //'S'
	{0x1F, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04}, //'T'
	{0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E}, //'U'
	{0x11, 0x11, 0x11, 0x11, 0x11, 0x0A, 0x04}, //'V'
	{0x11, 0x11, 0x11, 0x15, 0x15, 0x1B, 0x11}, //'W'
	{0x11, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x11}, //'X'
	{0x11, 0x11, 0x0A, 0x04, 0x04, 0x04, 0x04}, //'Y'
	{0x1F, 0x01, 0x02, 0x04, 0x08, 0x10, 0x1F}, //'Z'
	{0x0E, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0E}, //'['
	{0x00, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00}, //'\'
	{0x0E, 0x02, 0x02, 0x02, 0x02, 0x02, 0x0E}, //']'
	{0x04, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00}, //'^'
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F}, //'_'
	{0x00, 0x08, 0x04, 0x02, 0x00, 0x00, 0x00}, //'`'
	{0x00, 0x00, 0x0E, 0x01, 0x0F, 0x11, 0x0F}, //'a'
	{0x10, 0x10, 0x1E, 0x11, 0x11, 0x11, 0x1E}, //'b'
	{0x00, 0x00, 0x0F, 0x10, 0x10, 0x10, 0x0F}, //'c'
	{0x01, 0x01, 0x0F, 0x11, 0x11, 0x11, 0x0F}, //'d'
	{0x00, 0x00, 0x0E, 0x11, 0x1F, 0x10, 0x0E}, //'e'
	{0x06, 0x08, 0x08, 0x1C, 0x08, 0x08, 0x08}, //'f'
	{0x00, 0x0E, 0x11, 0x11, 0x0F, 0x01, 0x0E}, //'g'
	{0x10, 0x10, 0x16, 0x19, 0x11, 0x11, 0x11}, //'h'
	{0x04, 0x00, 0x0C, 0x04, 0x04, 0x04, 0x0E}, //'i'
	{0x02, 0x00, 0x06, 0x02, 0x02, 0x0A, 0x04}, //'j'
	{0x10, 0x10, 0x12, 0x14, 0x18, 0x14, 0x12}, //'k'
	{0x0C, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0E}, //'l'
	{0x00, 0x00, 0x1A, 0x15, 0x15, 0x15, 0x15}, //'m'
	{0x00, 0x00, 0x16, 0x19, 0x11, 0x11, 0x11}, //'n'
	{0x00, 0x00, 0x0E, 0x11, 0x11, 0x11, 0x0E}, //'o'
	{0x00, 0x00, 0x1C, 0x12, 0x12, 0x1C, 0x10}, //'p'
	{0x00, 0x00, 0x0E, 0x12, 0x12, 0x0E, 0x02}, //'q'
	{0x00, 0x00, 0x16, 0x18, 0x10, 0x10, 0x10}, //'r'
	{0x00, 0x00, 0x0F, 0x10, 0x0E, 0x01, 0x1E}, //'s'
	{0x08, 0x08, 0x1C, 0x08, 0x08, 0x09, 0x06}, //'t'
	{0x00, 0x00, 0x11, 0x11, 0x11, 0x11, 0x0E}, //'u'
	{0x00, 0x00, 0x11, 0x11, 0x11, 0x0A, 0x04}, //'v'
	{0x00, 0x00, 0x11, 0x11, 0x15, 0x15, 0x0A}, //'w'
	{0x00, 0x00, 0x11, 0x0A, 0x04, 0x0A, 0x11}, //'x'
	{0x00, 0x00, 0x11, 0x11, 0x0F, 0x01, 0x0E}, //'y'
	{0x00, 0x00, 0x1F, 0x02, 0x04, 0x08, 0x1F}, //'z'
	{0x02, 0x04, 0x04, 0x08, 0x04, 0x04, 0x02}, //'{'
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04}, //'|'
	{0x08, 0x04, 0x04, 0x02, 0x04, 0x04, 0x08}, //'}'
	{0x00, 0x00, 0x0A, 0x14, 0x00, 0x00, 0x00}, //'~'
};

struct Matriz EX4_BufferDisplay[EX4_BUFFER];
uint32_t Matricial_msglen;

uint8_t DisplayMatricial( char *msg )
{
	uint32_t i ,j;

	if ( msg )
	{
		if ( ( Matricial_msglen = strlen ( msg ) ) > EX4_BUFFER )
			return 1 ;

		if(Matricial_msglen<EX4_DIGITOS)
		{
			for (i = Matricial_msglen ; i < EX4_BUFFER ; i++ )
				msg[i] = ' ';
			msg[EX4_DIGITOS] = '\0';
			Matricial_msglen = EX4_DIGITOS;
		}

		for (i = 0 ; i < Matricial_msglen ; i++ )			//recorro los caracteres del mensaje
			for(j = 0; j < 7; j++)							//recorro las filas correspondientes a cada caracter
			{
				if( msg[i] >= ' ' && msg[i] <= '~' )    //mapa de caracteres actualmente soportado
					EX4_BufferDisplay[ i ].Fila[j] = MatrizCaracteres[ (uint8_t)msg[i] - ' ' ] [ j ];	//cargo buffer con el mensaje completo
				else
					EX4_BufferDisplay[ i ].Fila[j] = 0x00;
			}

		for (i = 0 ; i < EX4_DIGITOS  ; i++ )
			EX4_BufferMatriz[ i ] = EX4_BufferDisplay[ EX4_DIGITOS - i - 1 ] ;
	}

	return 0;
}

void DisplayRotacion(uint8_t modo, uint32_t ms)
{
	matricial_modo_rotacion = modo;
	if (modo == NO_ROTAR)
		ticks_matricial = 0;
	else
	{
		recarga_ticks_matricial = ms/10; //ticks de centesimas de segundo
		ticks_matricial = recarga_ticks_matricial;
	}
}

void DisplayRotarAbajo( void )
{
	int j , i ;
	uint8_t aux;
	for ( j = 0 ; j <  Matricial_msglen ; j ++ )
	{
		aux = EX4_BufferDisplay[ j ].Fila[ 6 ];
		for ( i = 6 ; i ; i-- )
			EX4_BufferDisplay[ j ].Fila[ i ] = EX4_BufferDisplay[ j ].Fila[ i - 1 ] ;

		EX4_BufferDisplay[ j ].Fila[ 0 ] = aux;
	}

	for ( i = 0 ; i < EX4_DIGITOS  ; i++ )
		EX4_BufferMatriz[ i ] = EX4_BufferDisplay[ EX4_DIGITOS - i - 1 ] ;
}

void DisplayRotarArriba( void )
{
	int j , i ;
	uint8_t aux;
	for ( j = 0 ; j <  Matricial_msglen ; j++ )
	{
		aux = EX4_BufferDisplay[ j ].Fila[ 0 ];
		for ( i = 0 ; i < 6  ; i++ )
			EX4_BufferDisplay[ j ].Fila[ i ] = EX4_BufferDisplay[ j ].Fila[ i + 1 ] ;

		EX4_BufferDisplay[ j ].Fila[ 6 ] = aux;
	}

	for ( i = 0 ; i < EX4_DIGITOS  ; i++ )
		EX4_BufferMatriz[ i ] = EX4_BufferDisplay[ EX4_DIGITOS - i - 1 ] ;
}

void DisplayRotarIzquierda( void )
{
	int j , i ;

	for ( j = 0 ; j <  Matricial_msglen ; j ++ )
	{
		for ( i = 0 ; i < 7 ; i++ )
			EX4_BufferDisplay[ j ].Fila[ i ] <<= 1 ;

		if ( j < Matricial_msglen - 1 )
		{
			for ( i = 0 ; i < 7 ; i++ )
				EX4_BufferDisplay[ j ].Fila[ i ] |= ( ( EX4_BufferDisplay[ j + 1 ].Fila[ i ] >> 4 ) & 0x01 ) ;
		}
		else
		{
			for ( i = 0 ; i < 7 ; i++ )
				EX4_BufferDisplay[ j ].Fila[ i ] |= (( EX4_BufferDisplay[ 0 ].Fila[i] >> 5 ) & 0x01 );
		}
	}

	for ( i = 0 ; i < EX4_DIGITOS  ; i++ )
		EX4_BufferMatriz[ i ] = EX4_BufferDisplay[ EX4_DIGITOS - i - 1 ] ;
}

void DisplayRotarDerecha( void )
{
	int j , i ;
	unsigned char b[ 8 ] ;

	for ( i = 0 ; i < 7 ; i++ )
		b[ i ] = ( ( EX4_BufferDisplay[ Matricial_msglen -1 ].Fila[ i ] << 5 ) & 0x20 ) ;

	for (j = 0 ; j <  Matricial_msglen ; j++ )
	{
		for ( i = 0 ; i < 7 ; i ++ )
		{
			EX4_BufferDisplay[ j ].Fila[ i ] &= 0xdf ;
			EX4_BufferDisplay[ j ].Fila[ i ] |= b[i] ;
		}

		for ( i = 0 ; i < 7 ; i ++ )
			b[ i ] = ((EX4_BufferDisplay[ j ].Fila[ i ] << 5 ) & 0x20 ) ;

		for ( i = 0 ; i < 7 ; i++ )
			EX4_BufferDisplay[ j ].Fila[ i ] >>= 1 ;
	}
	for ( i = 0 ; i < EX4_DIGITOS  ; i++ )
		EX4_BufferMatriz[ i ] = EX4_BufferDisplay[ EX4_DIGITOS - i - 1 ] ;
}
