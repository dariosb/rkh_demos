/*
 * PR_Teclado.c
 *
 *  Created on: 11/07/2013
 *      Author: Pablo
 */

#include "FW_IO.h"
#include "FW_Teclado.h"
#include "PR_Teclado.h"

uint8_t Teclado_GetKey(void)
{
	uint8_t aux = NO_KEY;

	if (Teclado_Key != NO_KEY )
	{
		aux = Teclado_Key;
		Teclado_Key = NO_KEY;
	}
	return aux;
}

uint8_t Teclas_GetKey(void)
{
	uint8_t aux = NO_KEY;

	if (Teclas_Key != NO_KEY )
	{
		aux = Teclas_Key;
		Teclas_Key = NO_KEY;
	}
	return aux;
}
