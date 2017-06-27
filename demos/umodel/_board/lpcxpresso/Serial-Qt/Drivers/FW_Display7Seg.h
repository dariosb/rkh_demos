/*
 * FW_EXP3Display.h
 *
 *  Created on: 10/07/2013
 *      Author: Pablo
 */

#ifndef FW_EXP3DISPLAY_H_
#define FW_EXP3DISPLAY_H_

#include "regs.h"
#include "KitInfo2_Expansiones.h"

#define DIGITOS		6

void EX2_BarridoDisplay(void);
void EX3_BarridoDisplay(void);

extern volatile uint8_t Digitos[];

#endif /* FW_EXP3DISPLAY_H_ */
