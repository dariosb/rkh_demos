/****************************************************************************
 *   $Id:: uart.h 5751 2010-11-30 23:56:11Z usb00423                        $
 *   Project: NXP LPC17xx UART example
 *
 *   Description:
 *     This file contains UART code header definition.
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/
#ifndef __UART_H 
#define __UART_H

uint32_t UARTInit(uint32_t portNum, uint32_t Baudrate);
void UART0_IRQHandler(void);
void UART1_IRQHandler(void);
void UARTSend(uint32_t portNum, uint8_t *BufferPtr, uint32_t Length);
void UARTPutc(uint32_t portNum, uint8_t c);
void UARTPutnc(uint32_t portNum, char *p, uint16_t n);
void UARTPuts(uint32_t portNum, char *p);

#endif /* end __UART_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
