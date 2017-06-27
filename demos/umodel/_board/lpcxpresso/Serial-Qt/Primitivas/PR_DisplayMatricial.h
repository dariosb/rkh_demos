/*
 * PR_DisplayMatricial.h
 *
 *  Created on: 25/07/2013
 *      Author: Pablo
 */

#ifndef PR_DISPLAYMATRICIAL_H_
#define PR_DISPLAYMATRICIAL_H_

#include "regs.h"

#define EX4_BUFFER 20

#define	ROTAR_DERECHA	0
#define	ROTAR_IZQUIERDA	1
#define	ROTAR_ARRIBA	2
#define	ROTAR_ABAJO		3
#define	NO_ROTAR		4

uint8_t DisplayMatricial(char *msg);
void DisplayRotacion(uint8_t modo, uint32_t ms);
void DisplayRotarArriba( void );
void DisplayRotarAbajo( void );
void DisplayRotarIzquierda( void );
void DisplayRotarDerecha( void );

#endif /* PR_DISPLAYMATRICIAL_H_ */
