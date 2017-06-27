/**
 	\file FW_Display.c
 	\brief Drivers de conversor A/D
 	\details Manejado por interrupcion
 	\author Pablo Irrera Condines
 	\date 2013.05.08
*/

#include "regs.h"
#include "UtilesInfo2.h"

volatile uint16_t ADC_ValorMedido;

void InitADC (void)
{
	//1.- Activo la alimentacion del dispositivo desde el registro PCONP:
	PCONP |= 1<<12;
	//2.- Selecciono el clock del ADC como 25MHz:
	PCLKSEL0 &= ~(0x03<<24);
	//3.- Y el divisor como 1, para muestrear a //200kHz:
	//AD0CR &= 0x00000100;
	AD0CR = 0xFF00;
	//4.- Configuro los pines del ADC0
	//ADC0.5 (pote) : P1[31]->PINSEL3: 30:31
	SetPINSEL(P1,31,PINSEL_FUNC3);
	//5.- Activo interrupcion del canal 5:
	AD0INTEN = 0x00000020;
	//6.- Selecciono que voy a tomar muestras del canal AD0.5:
	AD0CR |= 0x00000020;
	//7.- Activo el ADC (PDN = 1):
	AD0CR |= 1<<21;
	//8.- Selecciono que el ADC muestree solo, con BURST = 1 y START = 000:
	AD0CR &= ~(0x0F<<24);
	AD0CR |= 1<<16;
	//9.- Activo interrupcion en el NVIC:
	ISER0 |= (1<<22);
}

void ADC_IRQHandler(void)
{
	static uint32_t promedio;
	static uint32_t cont;

	promedio += (AD0DR5 >> 4) & 0xFFF;
	cont ++;

	if ( cont >= 50 )
	{
		ADC_ValorMedido = promedio / 50;
		promedio = 0;
		cont = 0;
	}
}
