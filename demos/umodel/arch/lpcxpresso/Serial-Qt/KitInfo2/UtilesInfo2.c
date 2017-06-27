/*
 * UtilesInfo2.c
 *
 *  Created on: 30/03/2013
 *      Author: Marcelo
 */
#include "KitInfo2.h"

/********************************************************************************
	\fn  void SetPINSEL (uint8_t puerto, uint8_t pin, uint8_t modo)
	\brief Selección de modo de los puertos (4 modos).
	\author & date: M. Trujillo - Feb2013
 	\param [in] puerto: port a configurar
 	\param [in] pin:	pin del port a configurar
 	\param [in] modo:	elección del modo [0 - 3]
 			#define		PINSEL_GPIO		0
			#define		PINSEL_FUNC1		1
			#define		PINSEL_FUNC2		2
			#define		PINSEL_FUNC3		3
	\return void
*/
void SetPINSEL (uint8_t puerto, uint8_t pin, uint8_t modo){
	switch (puerto){
		case P0:
			if (pin >= 16){
				pin -=16;
				PINSEL1 &= ~(0x03 << (pin * 2));
				PINSEL1 |= (modo << (pin * 2));
			}
			else {
				PINSEL0 &= ~(0x03 << (pin * 2));
				PINSEL0 |= (modo << (pin * 2));
			}
			break;

		case P1:
			if (pin >= 16){
				pin -=16;
				PINSEL3 &= ~(0x03 << (pin * 2));
				PINSEL3 |= (modo << (pin * 2));
			}
			else{
				PINSEL2 &= ~(0x03 << (pin * 2));
				PINSEL2 |= (modo << (pin * 2));
			}
			break;

		case P2:
			if (pin >= 16){
				pin -=16;
				PINSEL5 &= ~(0x03 << (pin * 2));
				PINSEL5 |= (modo << (pin * 2));
			}
			else{
				PINSEL4 &= ~(0x03 << (pin * 2));
				PINSEL4 |= (modo << (pin * 2));
			}
			break;

		case P3:
			if (pin >= 16){
				pin -=16;
				PINSEL7 &= ~(0x03 << (pin * 2));
				PINSEL7 |= (modo << (pin * 2));
			}
			else{
				PINSEL6 &= ~(0x03 << (pin * 2));
				PINSEL6 |= (modo << (pin * 2));
			}
			break;

		case P4:
			if (pin >= 16){
				pin -=16;
				PINSEL9 &= ~(0x03 << (pin * 2));
				PINSEL9 |= (modo << (pin * 2));
			}
			else{
				PINSEL8 &= ~(0x03 << (pin * 2));
				PINSEL8 |= (modo << (pin * 2));
			}
			break;
	} //fin switch
}

/********************************************************************************
	\fn  void SetDIR (registro* puerto, uint8_t pin, uint8_t direccion)
	\brief Establece si un determinado PIN de un determinado PUERTO (previamente
			configurado como GPIO) es entrada o salida.
	\author & date: M. Giura - Mar2013
 	\param [in] puerto: 	port con el que se va a trabajar
 	\param [in] pin:		pin a configurar sentido
 	\param [in] direccion:	0 = entrada - 1 = salida.
	\return void
*/
void SetDIR(registro* puerto,uint8_t pin,uint8_t direccion){
	( direccion == 1 ) ? ( puerto[0] |= ( 0x01 << pin ) ):( puerto[0] &= ~( 0x01 << pin ) );
}		//puerto[0] == FIODIR

/********************************************************************************
	\fn  void SetPIN (registro* puerto, uint8_t pin, uint8_t estado)
	\brief Establece un ESTADO en un determinado PIN de un determinado PUERTO.
	\author & date: M. Trujillo - Feb2013
 	\param [in] puerto: port con el que se va a trabajar
 	\param [in] pin:	pin a setear estado
 	\param [in] estado:	valor a establecer en el PIN del PUERTO [0-1].
	\return void
*/
void SetPIN(registro* puerto,uint8_t pin,uint8_t estado){
	( estado == 1 ) ? ( puerto[6] |= ( 0x01 << pin ) ):( puerto[7] |= ( 0x01 << pin ) );
}		//puerto[6] == FIOSET - //puerto[7] == FIOCLR

/********************************************************************************
	\fn  void GetPIN (registro* puerto, uint8_t pin)
	\brief Devuelve el ESTADO de un determinado PIN de un determinado PUERTO.
	\author & date: M. Trujillo - Feb2013
 	\param [in] puerto: port con el que se va a trabajar
 	\param [in] pin:	pin a consultar estado
	\return:	estado del pin consultado (uint_8)
*/
uint8_t GetPIN(registro* puerto,uint8_t pin){
	return (puerto[5]>>pin)& 0x01;	//puerto[5] == FIOPIN
}
