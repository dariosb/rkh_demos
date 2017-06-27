/*
 * PR_timer.h
 *
 *  Created on: 16/03/2013
 *      Author: Pablo
 */

#ifndef PR_TIMER_H_
#define PR_TIMER_H_

#define N_TIMERS 1

#include "regs.h"

typedef volatile uint32_t Tiempos;
typedef volatile uint32_t Eventos;

void TimerStart(Eventos e, Tiempos t, void (*handler)(void));
void TimerStop(Eventos e);
void TimerClose(void);
void TimerCheck(void);
void TimerEvent(void);

//Definiciones de eventos y tiempos(en decimas de segundos)
/*#define EV_TRANSMITIR		0
#define T_TRANSMITIR		5
*/
#endif /* PR_TIMER_H_ */
