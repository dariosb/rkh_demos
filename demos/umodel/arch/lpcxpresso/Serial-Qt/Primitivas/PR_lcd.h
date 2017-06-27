/*
 * PR_lcd.h
 *
 *  Created on: 10/07/2013
 *      Author: Pablo
 */

#ifndef PR_LCD_H_
#define PR_LCD_H_

#include "regs.h"

#define LCDBUFFER_SIZE	160

#define LARGO_RENGLON	16

#define 	RENGLON_1		0
#define 	RENGLON_2		1
#define		LCD_CONTROL		1
#define		LCD_DATA		0

void DisplayLCD (char * msg, uint8_t r , uint8_t pos);

#endif /* PR_LCD_H_ */
