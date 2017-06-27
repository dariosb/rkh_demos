/*
 * FW_DisplayMatricial.h
 *
 *  Created on: 25/07/2013
 *      Author: Pablo
 */

#ifndef FW_DISPLAYMATRICIAL_H_
#define FW_DISPLAYMATRICIAL_H_

#include "regs.h"

#define EX4_DIGITOS 4

struct Matriz
{
	unsigned char Fila[7];
};

void EX4_BarridoMatriz( void );
void EX4_ShiftDato( uint8_t fila );

extern struct Matriz EX4_BufferMatriz[];
extern volatile uint32_t ticks_matricial;
extern volatile uint32_t recarga_ticks_matricial;
extern volatile uint8_t matricial_modo_rotacion;

#endif /* FW_DISPLAYMATRICIAL_H_ */
