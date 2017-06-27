/*
 * main.c
 *
 *  Created on: 09/07/2013
 *      Author: Pablo
 */

#include <KitInfo2.h>
#include <KitInfo2_Expansiones.h>
#include <KitInic.h>
#include <KitInic_Expansiones.h>
#include <PR_Teclado.h>
#include <PR_Timer.h>
#include <AP_Mensajes.h>

int main ( void )
{
	uint8_t c = NO_KEY;

	InicializarKit();
	InitEXP();

	EstadoInicial();
	while(1)
	{
		TimerEvent();
		MensajesRX();

		c = Teclas_GetKey();		//Lectura teclas baseboard

		BaseBoard(c);
	#ifdef KITINFOII_EXPANSION1
		Expansion1();
	#elif defined KITINFOII_EXPANSION2
		Expansion2(c);
	#elif defined KITINFOII_EXPANSION3
		Expansion3(c);
	#elif defined KITINFOII_EXPANSION4
		Expansion4();
	#endif
	}
}

