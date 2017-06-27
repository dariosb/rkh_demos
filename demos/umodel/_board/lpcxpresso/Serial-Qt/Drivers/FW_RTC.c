/**
 	\file FW_RTC.c
 	\brief Drivers del RTC
 	\details manejo de interrupciones por incremento y alarma
 	\author Pablo Irrera Condines
 	\date 2013.05.08
*/

#include "FW_RTC.h"

volatile uint8_t f_tick_rtc = 0, f_alarma = 0;

void InitRTC(void)
{
	ILR = 0x00;
	CIIR = 0x00;
	AMR = 0xFF;
	CALIBRATION = 0x00;
	CCR = 0x01;
}

void RTC_HabilitaIntIncremento(uint32_t tipo_int)
{
	CIIR |= tipo_int;	//se habilita el tipo de interrupcion pedido
	ILR = 0x01;			//limpio flag de interrupcion
	ISER0 |= 1<<17;		//habilito interrupcion desde el NVIC
}

void RTC_HabilitaIntAlarma(uint32_t tipo_al)
{
	tipo_al =~ tipo_al;
	AMR &= tipo_al;		//se desenmascara el bit de alarma pedido
	ILR = 0x02;			//limpio flag de interrupcion
	ISER0 |= 1<<17;		//habilito interrupcion desde el NVIC
}

void RTC_SetHoraFecha(const RTC_HoraFecha* horafecha)
{
	SEC = horafecha->seg;
	MIN = horafecha->min;
	HOUR = horafecha->hora;
	DOM = horafecha->dia_mes;
	DOW = horafecha->dia_semana;
	DOY = horafecha->dia_anio;
	MONTH = horafecha->mes;
	YEAR = horafecha->anio;
}

void RTC_GetHoraFecha(RTC_HoraFecha* horafecha)
{
	horafecha->seg = SEC;
	horafecha->min = MIN;
	horafecha->hora = HOUR;
	horafecha->dia_mes = DOM;
	horafecha->dia_semana = DOW;
	horafecha->dia_anio = DOY;
	horafecha->mes = MONTH;
	horafecha->anio = YEAR;
}

void RTC_SetAlarma(const RTC_HoraFecha* horafecha)
{
	ALSEC = horafecha->seg;
	ALMIN = horafecha->min;
	ALHOUR = horafecha->hora;
	ALDOM = horafecha->dia_mes;
	ALDOW = horafecha->dia_semana;
	ALDOY = horafecha->dia_anio;
	ALMON = horafecha->mes;
	ALYEAR = horafecha->anio;
}

void RTC_GetAlarma(RTC_HoraFecha* horafecha)
{
	horafecha->seg = ALSEC;
	horafecha->min = ALMIN;
	horafecha->hora = ALHOUR;
	horafecha->dia_mes = ALDOM;
	horafecha->dia_semana = ALDOW;
	horafecha->dia_anio = ALDOY;
	horafecha->mes = ALMON;
	horafecha->anio = ALYEAR;
}

void RTC_IRQHandler(void)
{
	if(ILR & (1<<0))		//Interrupcion por counter increment
		f_tick_rtc = 1;
	if(ILR & (1<<1))		//Interrupcion por alarma
		f_alarma = 1;
	ILR = ILR;				//limpieza flags de interrupcion
}
