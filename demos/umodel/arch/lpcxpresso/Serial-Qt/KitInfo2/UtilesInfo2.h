/*
 * UtilesInfo2.h
 *
 *  Created on: 30/03/2013
 *      Author: Marcelo
 */

#ifndef UTILESINFO2_H_
#define UTILESINFO2_H_

#include "regs.h"

//Prototipos de las funciones utilitarias
void SetPINSEL (uint8_t puerto, uint8_t pin, uint8_t modo);
void SetDIR(registro* puerto,uint8_t pin,uint8_t direccion);
void SetPIN(registro* puerto,uint8_t pin,uint8_t estado);
uint8_t GetPIN(registro* puerto,uint8_t pin);

// dirección en FIODIR
#define 	ENTRADA			0
#define 	SALIDA			1

// identificadores de los puertos
#define 	P0			0
#define 	P1			1
#define 	P2			2
#define 	P3			3
#define 	P4			4

#endif /* UTILESINFO2_H_ */
