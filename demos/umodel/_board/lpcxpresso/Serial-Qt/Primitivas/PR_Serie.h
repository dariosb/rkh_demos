/*
 * PR_Serie.h
 *
 *  Created on: 09/07/2013
 *      Author: Pablo
 */

#ifndef PR_SERIE_H_
#define PR_SERIE_H_

#include <FW_Serie.h>
#include <regs.h>

#define TXBUFFER_SIZE	32
#define RXBUFFER_SIZE	32

uint8_t PushTx(uint8_t dato);
uint8_t PopTx( uint8_t *dato );
uint8_t PushRx(uint8_t dato);
uint8_t PopRx( uint8_t *dato );
void EnviarString (const char *str);

#endif /* PR_SERIE_H_ */
