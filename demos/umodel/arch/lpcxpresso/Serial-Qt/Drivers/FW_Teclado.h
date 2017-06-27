/*
 * FW_EXP3Teclado.h
 *
 *  Created on: 11/07/2013
 *      Author: Pablo
 */

#ifndef FW_EXP3TECLADO_H_
#define FW_EXP3TECLADO_H_

#include "regs.h"

#define REBOTES	4

void DriverTecladoSW (uint8_t codigoActual);
void EX3_DriverTeclado (void);
uint8_t EX3_DriverTecladoHW (void);
void EX4_DriverTeclado (void);
uint8_t EX4_DriverTecladoHW (void);

// Buffer de teclado matricial
extern volatile uint8_t Teclado_Key;

#endif /* FW_EXP3TECLADO_H_ */

