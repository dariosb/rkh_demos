/**
 	\file FW_Timertick.c
 	\brief Drivers del systick
 	\details Barrido de displays y teclados, entradas, lcd y timers
 	\author Pablo Irrera Condines
 	\date 2013.05.08
*/

#include "FW_Display7Seg.h"
#include "FW_LCD.h"
#include "FW_Teclado.h"
#include "FW_IO.h"
#include "FW_EXP1IO.h"
#include "PR_DisplayMatricial.h"
#include "FW_DisplayMatricial.h"
#include "PR_Timer.h"

volatile uint8_t f_1seg, f_100ms;

#define CENTESIMAS  4
#define DECIMAS		10
#define SEGUNDOS	10

void InitSystick (uint32_t useg)
{
	uint32_t value;

	// N = t / (1/fclk ) = t * fclk
	// si fclk = 100MHz -->  N = t (en us) * 100*/
	// Para temporizaciones repetitivas se debe cargar N-1
	value = useg * 100 - 1;

	STRELOAD = value;
	//Hago que se dispare la interrupcion al habilitar:
	STCURR = 0;
	//Disparo el SysTick:
	STCTRL = 0x00000007;
}

void SysTick_Handler(void)
{
	static uint32_t centesimas = CENTESIMAS, decimas = DECIMAS;

	DriverTeclas();
	Entradas_Debounce();
	Dato_LCD();
	if ( Demora_LCD )
		Demora_LCD--;
	BarridoSalidas();

#ifdef	KITINFOII_EXPANSION1

	EX1_BarridoLEDs();
	EX1_EntradasDebounce();

#elif defined KITINFOII_EXPANSION2

	EX2_BarridoDisplay();

#elif defined KITINFOII_EXPANSION3

	EX3_BarridoDisplay();
	EX3_DriverTeclado();

#elif defined  KITINFOII_EXPANSION4

	EX4_BarridoMatriz();
	EX4_DriverTeclado();

#endif

	centesimas--;
	if(!centesimas)
	{
		centesimas = CENTESIMAS;
		decimas--;
		if(!decimas)
		{
			decimas = DECIMAS;
			TimerCheck();
		}


		#ifdef KITINFOII_EXPANSION4

		if( ticks_matricial)	//en centesimas de segundo
		{
			ticks_matricial--;
			if( !ticks_matricial)
			{
				ticks_matricial = recarga_ticks_matricial;
				switch ( matricial_modo_rotacion )
				{
					case ROTAR_DERECHA:
						DisplayRotarDerecha( );
						break;
					case ROTAR_IZQUIERDA:
						DisplayRotarIzquierda( );
						break;
					case ROTAR_ABAJO:
						DisplayRotarAbajo( );
						break;
					case ROTAR_ARRIBA:
						DisplayRotarArriba( );
						break;
				}
			}
		}
		#endif
	}
}

