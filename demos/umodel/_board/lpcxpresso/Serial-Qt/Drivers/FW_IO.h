/*
 * FW_IO.h
 *
 *  Created on: 15/07/2013
 *      Author: Pablo
 */

#ifndef FW_IO_H_
#define FW_IO_H_

#include "regs.h"

#define REBOTES			4
#define ACEPTAR_ESTADO	5

#define IO_LED1		0
#define IO_LED2		1
#define IO_LED3		2
#define IO_LED4		3

#define IO_RGBR		0
#define IO_RGBG		1
#define IO_RGBB		2
#define IO_BUZZER	3

void BarridoSalidas (void);
void DriverTeclas (void);
void DriverTeclasSW (uint8_t codigoActual);
uint8_t DriverTeclasHW (void);
void Entradas_Debounce (void);

extern volatile uint8_t BufferLED_Relay;
extern volatile uint8_t BufferRGB_Buzzer;
extern volatile uint8_t EntradasDigitales;
extern volatile uint32_t Teclas_Key;

#endif /* FW_IO_H_ */
