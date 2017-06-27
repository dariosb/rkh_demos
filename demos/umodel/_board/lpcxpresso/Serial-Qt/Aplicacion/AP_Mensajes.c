/**
 	\file AP_Mensajes.c
 	\brief Aplicacion para conectar con el software provisto por la catedra
 	\details Manejo del hardware del kit y RX/TX con la PC
 	\author Pablo Irrera Condines
 	\date 2013.05.08
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <KitInfo2_Expansiones.h>
#include <PR_Serie.h>
#include <PR_IO.h>
#include <PR_Teclado.h>
#include <PR_Display7Seg.h>
#include <PR_DisplayMatricial.h>
#include <PR_LCD.h>
#include <FW_DAC.h>
#include <FW_RTC.h>
#include <PR_Timer.h>
#include <AP_Mensajes.h>

//Flag del RTC
extern volatile uint8_t f_tick_rtc;

//Lectura del conversor
extern volatile uint32_t ADC_ValorMedido;


void MensajesRX(void)
{
	static char msg[EX4_BUFFER];
   	static uint8_t inx = 0;
   	uint8_t dato;
   	static uint8_t espera = 0;
   	uint32_t intaux;	//auxiliar para enteros
   	char paux[5];	//auxiliar para strings
   	RTC_HoraFecha horafecha;

   	if( !PopRx(&dato) )
   	{
   		switch(espera)
   		{
			case 0: 				// Espera de mensaje
				espera = dato;		// ID del mensaje
	    		switch (espera)
				{
	    			case MSG_EXPANSION:						//'E'
					case MSG_LCD_SUPERIOR:					//'1'
					case MSG_LCD_INFERIOR:					//'2'
					case MSG_LEDS_RELAYS:					//'3'
					case MSG_RGB_BUZZER:					//'4'
					case MSG_DISPLAY_DERECHA:				//'5'
					case MSG_DISPLAY_IZQUIERDA:				//'6'
					case MSG_DAC:							//'7'
					case MSG_LEDS:							//'8'
					case MSG_DISPLAY_MATRICIAL_VALOR: 		//'9'
					case MSG_DISPLAY_MATRICIAL_ROTACION	:	//'A'
					case MSG_RTC:							//'B'
						break;
					default:
						espera = 0;
						break;
			   	}

	    		inx = 0;
	    		break;

			case MSG_EXPANSION:		// Numero de expansion conectada -------------------------
				msg[inx] = (char)dato;
				if( msg[inx] == '\r' )
				{
				 	TransmitirExpansion();
				 	espera = 0;
				}
				inx++;
				break;
			case MSG_LCD_SUPERIOR:// LCD superior --------------------------------------------
				msg[inx] = (char)dato;
				if( msg[inx] == '\r' )
				{
				 	msg[inx] = '\0';
					DisplayLCD(msg,0,0);
				 	espera = 0;
				}
				inx++;
				break;
			case MSG_LCD_INFERIOR: // LCD inferior --------------------------------------------
				msg[inx] = (char)dato;
				if( msg[inx] == '\r' )
				{
				 	msg[inx] = '\0';
					DisplayLCD(msg,1,0);
				 	espera = 0;
				}
				inx++;
				break;
 			case MSG_DISPLAY_DERECHA :// Display 7 segmentos derecha-----------------------
				msg[inx] = (char)dato;
				if( msg[inx] == '\r' )
				{
				 	msg[inx] = '\0';
					if (strlen ( msg ) < 4 )
					{
						Display ( atoi (msg), DSP1);
						espera = 0;
					}
				}
				inx++;
				break;
 			case MSG_DISPLAY_IZQUIERDA :// Display 7 segmentos izquierda ----------------------
				msg[inx] = (char)dato;
				if( msg[inx] == '\r' )
				{
				 	msg[inx] = '\0';
					if (strlen ( msg ) < 4 )
					{
						Display ( atoi (msg), DSP0);
						espera = 0;
					}
				}
				inx++;
				break;

			case MSG_RGB_BUZZER: // leds -------------------------------------------------------------
				// msg[0] : numero de led
				// msg[1] : '0' apagar , '1' prender
				msg[inx] = (char)dato;
				if( msg[inx] == '\r' )
				{
					RGB_Buzzer (msg[0] - '0', msg[1] - '0');
					espera = 0;
				}
				inx++;
				break;
			case MSG_LEDS_RELAYS:	// LEDS y RELAYS --------------------------------------------------
				// msg[0] : numero de Relay
				// msg[1] : '0' apagar , '1' prender
				msg[inx] = (char)dato;
				if( msg[inx] == '\r' )
				{
					LEDs_Relays (msg[0] - '0' , msg[1] - '0');
					espera = 0;
				}
				inx++;
				break;
			case MSG_DAC:			// DAC ------------------------------------------------------------
				// msg[inx] : cifra decimal del valor del DAC
				msg[inx] = (char)dato;
				if( msg[inx] == '\r' )
				{
					msg[inx] = '\0';
					intaux = atoi(msg);
					if (intaux < 1024 )
					{
						DAC_SetValue(intaux);
						espera = 0;
					}
				}
				inx++;
				break;
			case MSG_LEDS: 			// leds espansion 1 -----------------------------------------------
				// msg[0] : numero de led
				// msg[1] : '0' apagar , '1' prender
				msg[inx] = (char)dato;
				if( msg[inx] == '\r' )
				{
					LEDs ( msg[0] - '0' , msg[1] - '0');
					espera = 0;
				}
				inx++;
				break;
			case MSG_DISPLAY_MATRICIAL_VALOR:		// valor display matricial expansion 4 ------------
				msg[inx] = (char)dato;
				if( msg[inx] == '\r' )
				{
				 	msg[inx] = '\0';
					DisplayMatricial(msg);
				 	espera = 0;
				}
				inx++;
				break;
			case MSG_DISPLAY_MATRICIAL_ROTACION: 	// rotacion display matricial expansion 4 ---------
				// msg[0] : sentido de rotacion
				msg[inx] = (char)dato;
				if( msg[inx] == '\r' )
				{
					switch(msg[0] - '0')
					{
						case ROTAR_DERECHA:
						case ROTAR_IZQUIERDA:
						case NO_ROTAR:
							DisplayRotacion(msg[0] - '0',100);
							break;
						case ROTAR_ARRIBA:
						case ROTAR_ABAJO:
							DisplayRotacion(msg[0] - '0',500);
							break;
					}

				 	espera = 0;
				}
				inx++;
				break;
			case MSG_RTC:
				//msg[0]-msg[1] : segundos
				//msg[2]-msg[3] : minutos
				//msg[4]-msg[5] : horas
				//msg[6]-msg[7] : dia
				//msg[8]-msg[9] : mes
				//msg[10]-msg[13] : anio
				msg[inx] = (char)dato;
				if( msg[inx] == '\r' )
				{
					paux[2] = '\0';
					paux[0] = msg[0]; paux[1] = msg[1];
					horafecha.seg = atoi(paux);
					paux[0] = msg[2]; paux[1] = msg[3];
					horafecha.min = atoi(paux);
					paux[0] = msg[4]; paux[1] = msg[5];
					horafecha.hora = atoi(paux);
					paux[0] = msg[6]; paux[1] = msg[7];
					horafecha.dia_mes = atoi(paux);
					paux[0] = msg[8]; paux[1] = msg[9];
					horafecha.mes = atoi(paux);
					paux[4]='\0';
					paux[0] = msg[10]; paux[1] = msg[11]; paux[2] = msg[12]; paux[3] = msg[13];
					horafecha.anio = atoi(paux);
					RTC_SetHoraFecha(&horafecha);
					espera = 0;
				}
				inx++;
				break;
		}
	}
}

void TransmitirExpansion(void)
{
	char msg[4];
#ifdef KITINFOII_EXPANSION1
	sprintf(msg,"E0\r");
#elif defined KITINFOII_EXPANSION2
	sprintf(msg,"E1\r");
#elif defined KITINFOII_EXPANSION3
	sprintf(msg,"E2\r");
#elif defined KITINFOII_EXPANSION4
	sprintf(msg,"E3\r");
#endif
	EnviarString(msg);
}

void EstadoInicial(void)
{
	char msg[EX4_BUFFER];

	sprintf(msg,"INFORMATICA II");
    DisplayLCD(msg,0,0);
	sprintf(msg,"INFOTRONIC");
	DisplayLCD(msg,1,4);
	TimerStart(EV_TRANSMITIR,T_TRANSMITIR,Transmitir);

#ifdef KITINFOII_EXPANSION2

	Display(123,DSP0);
	Display(456,DSP1);

#elif defined KITINFOII_EXPANSION3

	Display(123,DSP0);
	Display(456,DSP1);

#elif defined KITINFOII_EXPANSION4

	DisplayMatricial("INFO");

#endif

	TransmitirExpansion();		//Se transmite el numero de expansion con el que fue compilado
}

void BaseBoard (uint8_t c)
{
	char msg[17];	//suficiente para el RTC
	static uint8_t entradas_anterior;
	uint8_t aux;
	RTC_HoraFecha horafecha;

	if (c != NO_KEY )
	{
		sprintf(msg,"1%d\r",(int)c);
		EnviarString (msg);
	}

	aux = GetEntradas();
	if(entradas_anterior ^ aux)
	{
		entradas_anterior = aux;
		sprintf(msg,"3%d\r",aux);
		EnviarString(msg);
	}

	if(f_tick_rtc)
	{
		f_tick_rtc = 0;
		RTC_GetHoraFecha(&horafecha);
		sprintf(msg,"B%02d%02d%02d%02d%02d%04d\r",horafecha.seg,horafecha.min,horafecha.hora,horafecha.dia_mes,horafecha.mes,horafecha.anio);
		EnviarString(msg);
	}

}

void Transmitir(void)
{
	char msg[8];
	sprintf(msg,"2%d\r",(int)ADC_ValorMedido);
	EnviarString (msg);
	TimerStart(EV_TRANSMITIR,T_TRANSMITIR,Transmitir);
}

#ifdef KITINFOII_EXPANSION1

void Expansion1 (void)
{
	static uint8_t entradas_anterior;
	uint8_t aux;
	char msg[5];

	aux = GetEntradasDIP();
	if(entradas_anterior ^ aux)
	{
		entradas_anterior = aux;
		sprintf(msg,"4%d\r",aux);
		EnviarString(msg);
	}
}

#elif defined KITINFOII_EXPANSION2

void Expansion2 (uint8_t n)
{
	if ( n != NO_KEY )
		Display(n,DSP1);
}

#elif defined KITINFOII_EXPANSION3

void Expansion3 (uint8_t n)
{
	uint8_t c;
	char msg[7];

	c = Teclado_GetKey();
	if ( c != NO_KEY )
		Display(c,DSP0);
	if ( n != NO_KEY )
		Display(n,DSP1);

	switch ( c )
	{
		case EX3_F0:
			sprintf(msg,"00%03d\r",(int)c);
			EnviarString (msg);
			break;
		case EX3_F1:
			sprintf(msg,"01%03d\r",(int)c);
			EnviarString (msg);
			break;
		case EX3_F2:
			sprintf(msg,"02%03d\r",(int)c);
			EnviarString (msg);
			break;
		case EX3_F3:
			sprintf(msg,"03%03d\r",(int)c);
			EnviarString (msg);
			break;
		case EX3_F4:
			sprintf(msg,"04%03d\r",(int)c);
			EnviarString (msg);
			break;
		case EX3_F5:
			sprintf(msg,"05%03d\r",(int)c);
			EnviarString (msg);
			break;
		case EX3_F6:
			sprintf(msg,"06%03d\r",(int)c);
			EnviarString (msg);
			break;
		case EX3_F7:
			sprintf(msg,"07%03d\r",(int)c);
			EnviarString (msg);
			break;
	}
}

#elif defined KITINFOII_EXPANSION4

void Expansion4 (void)
{
	uint8_t c;
	char msg[7];

	c = Teclado_GetKey();
	switch ( c )
	{
		case EX4_F0:
			sprintf(msg,"00%03d\r",(int)c);
			EnviarString (msg);
			break;
		case EX4_F1:
			DisplayRotacion(ROTAR_ARRIBA,500);
			sprintf(msg,"01%03d\r",(int)c);
			EnviarString (msg);
			break;
		case EX4_F2:
			sprintf(msg,"02%03d\r",(int)c);
			EnviarString (msg);
			break;
		case EX4_F3:
			DisplayRotacion(ROTAR_IZQUIERDA,100);
			sprintf(msg,"03%03d\r",(int)c);
			EnviarString (msg);
			break;
		case EX4_F4:
			DisplayRotacion(NO_ROTAR,100);
			sprintf(msg,"04%03d\r",(int)c);
			EnviarString (msg);
			break;
		case EX4_F5:
			DisplayRotacion(ROTAR_DERECHA,100);
			sprintf(msg,"05%03d\r",(int)c);
			EnviarString (msg);
			break;
		case EX4_F6:
			sprintf(msg,"06%03d\r",(int)c);
			EnviarString (msg);
			break;
		case EX4_F7:
			DisplayRotacion(ROTAR_ABAJO,500);
			sprintf(msg,"07%03d\r",(int)c);
			EnviarString (msg);
			break;
		case EX4_F8:
			sprintf(msg,"08%03d\r",(int)c);
			EnviarString (msg);
			break;
	}
}

#endif

