/**
 	\file PR_timer.c
 	\brief Primitiva de la maquinaria de timers
 	\details 32 eventos como maximo
 	\author Pablo Irrera Condines
 	\date 2013.05.08
*/

#include "PR_Timer.h"
#include "stdio.h"

//Variables de la maquinaria de timers
volatile Tiempos TimerRun[N_TIMERS];
volatile Eventos Events[N_TIMERS];
void (*Handlers[N_TIMERS]) (void);

void TimerStart(Eventos e, Tiempos t, void (*handler)(void))
{
	if(t)	//el tiempo no es 0, lo cargo
	{
		TimerRun[e] = t;
		Events[e] = 0;
		Handlers[e] = handler;
	}
	else	//el tiempo es cero, el timer vence automáticamente
	{
		TimerRun[e] = 0;
		Events[e] = 1;
		Handlers[e] = NULL;
	}
}

void TimerStop(Eventos e)
{
	TimerRun[e] = 0;
	Events[e] = 0;
	Handlers[e] = NULL;
}

void TimerClose(void)
{
	uint32_t i;
	for(i=0;i<N_TIMERS;i++)
	{
		TimerRun[i] = 0;
		Events[i] = 0;
		Handlers[i] = NULL;
	}
}

void TimerCheck(void)
{
	uint32_t i;
	for(i=0;i<N_TIMERS;i++)
	{
		if(TimerRun[i])
		{
			TimerRun[i]--;
			if(!TimerRun[i])
				Events[i] = 1;
		}
	}
}

void TimerEvent()
{
	uint8_t i;
	for(i=0;i<N_TIMERS;i++)
	{
		if(Events[i])
		{
			Handlers[i]();
			Events[i] = 0;
		}

	}
}


