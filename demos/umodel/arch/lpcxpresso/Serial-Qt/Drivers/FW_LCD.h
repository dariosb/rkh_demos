/*
 * FW_lcd.h
 *
 *  Created on: 10/07/2013
 *      Author: Pablo
 */

#ifndef FW_LCD_H_
#define FW_LCD_H_

#include "regs.h"

void InitLCD (void);
void ConfigLCD(void);
uint8_t PushLCD (uint8_t dato, uint8_t control);
int PopLCD (void);
void Dato_LCD(void);

extern volatile uint32_t Demora_LCD;

#endif /* FW_LCD_H_ */
