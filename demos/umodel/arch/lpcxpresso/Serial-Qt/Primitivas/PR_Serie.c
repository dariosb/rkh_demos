/**
 	\file PR_serie.c
 	\brief Primitiva de comunicación serie
 	\details buffers de RX y TX protegidos
 	\author Pablo Irrera Condines
 	\date 2013.05.08
*/

#include "PR_Serie.h"
#include "PR_Serie.h"

// Buffer de Transmision
uint8_t bufferTx[TXBUFFER_SIZE];
// Buffer de Recepcion
uint8_t bufferRx[RXBUFFER_SIZE];

// Indices de Transmision
uint8_t tx_in,tx_out;
// Indices de Recepcion
uint8_t rx_in,rx_out;
// Flags de estado de los buffers
uint8_t tx_buffer_full = 0, tx_buffer_empty = 1;
uint8_t rx_buffer_full = 0, rx_buffer_empty = 1;

uint8_t PushTx(uint8_t dato)
{
	if(tx_buffer_full)
		return 1;	//buffer lleno

	bufferTx[tx_in] = dato;
	tx_in++;
	tx_in %= TXBUFFER_SIZE;
	tx_buffer_empty = 0;	//si agrego un dato el buffer ya no esta vacio

	if(tx_in == tx_out)
		tx_buffer_full = 1;	//se lleno el buffer

	if (txStart == 0)
	{
		txStart = 1;
		START_TX();
	}
	return 0;	//dato agregado al buffer
}

uint8_t PopTx( uint8_t *dato )
{
	if(tx_buffer_empty)
		return 1;	//buffer vacio

	*dato = (uint8_t) bufferTx[tx_out];
	tx_out++;
	tx_out %= TXBUFFER_SIZE;
	tx_buffer_full = 0;	//si saco un dato el buffer ya no esta lleno

	if(tx_out == tx_in)
		tx_buffer_empty = 1;	//se vacio el buffer

	return 0;	//dato sacado del buffer
}

uint8_t PushRx( uint8_t dato )
{
	if(rx_buffer_full)
		return 1;	//buffer lleno

	bufferRx[rx_in] = dato;
	rx_in ++;
	rx_in %= RXBUFFER_SIZE;
	rx_buffer_empty = 0;	//si agrego un dato el buffer ya no esta vacio

	if(rx_in == rx_out)
		rx_buffer_full = 1;	//se lleno el buffer

	return 0;	//dato agregado al buffer
}

uint8_t PopRx( uint8_t *dato )
{
	if(rx_buffer_empty)
		return 1;	//buffer vacio

	*dato = (uint8_t) bufferRx[rx_out];
	rx_out++;
	rx_out %= RXBUFFER_SIZE;
	rx_buffer_full = 0;	//si saco un dato el buffer ya no esta lleno

	if(rx_out == rx_in)
		rx_buffer_empty = 1;	//se vacio el buffer

	return 0;	//dato sacado del buffer
}

void EnviarString (const char *str)
{
	uint32_t i;
	for( i = 0 ; str[i] ; i++ )
		PushTx( str[i] );
}
