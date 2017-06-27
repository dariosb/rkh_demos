/*
 * PR_IO.h
 *
 *  Created on: 14/07/2013
 *      Author: Pablo
 */

#ifndef PR_IO_H_
#define PR_IO_H_

#include "regs.h"

#define	NO_KEY		0xFF

//Base
void LEDs_Relays (uint8_t n, uint8_t estado);
void RGB_Buzzer (uint8_t pin, uint8_t estado);
uint8_t GetEntradas (void);

//Expansion 1
void LEDs (uint8_t n, uint8_t estado);
uint8_t GetEntradasDIP (void);

#endif /* PR_IO_H_ */
