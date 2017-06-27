/*
 * PR_Teclado.h
 *
 *  Created on: 11/07/2013
 *      Author: Pablo
 */

#ifndef PR_TECLADO_H_
#define PR_TECLADO_H_

#include "regs.h"

#define	NO_KEY		0xFF

uint8_t Teclado_GetKey(void);
uint8_t Teclas_GetKey(void);

#endif /* PR_TECLADO_H_ */
