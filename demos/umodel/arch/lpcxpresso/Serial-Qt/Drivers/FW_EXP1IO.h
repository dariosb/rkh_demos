/*
 * FW_EXP1IO.h
 *
 *  Created on: 19/07/2013
 *      Author: Pablo
 */

#ifndef FW_EXP1IO_H_
#define FW_EXP1IO_H_

#define ACEPTAR_ESTADO	5

#define IOEXP1_LED1		0
#define IOEXP1_LED2		1
#define IOEXP1_LED3		2
#define IOEXP1_LED4		3
#define IOEXP1_LED5		4
#define IOEXP1_LED6		5
#define IOEXP1_LED7		6
#define IOEXP1_LED8		7

void EX1_BarridoLEDs (void);
void EX1_EntradasDebounce (void);

extern uint8_t BufferLED;
extern uint16_t EntradasDIP;

#endif /* FW_EXP1IO_H_ */
