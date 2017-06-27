/*
 * FW_RTC.h
 *
 *  Created on: 14/03/2012
 *      Author: Pablo
 */

#ifndef FW_RTC_H_
#define FW_RTC_H_

#include "regs.h"

// Definiciones RTC
#define RTC_INT_SEG			0x01
#define RTC_INT_MIN			0x02
#define RTC_INT_HORA		0x04
#define RTC_INT_DIAMES		0x08
#define RTC_INT_DIASEM		0x10
#define RTC_INT_DIAANIO		0x20
#define RTC_INT_MES			0x40
#define RTC_INT_ANIO		0x80

#define RTC_AL_SEG			0x01
#define RTC_AL_MIN			0x02
#define RTC_AL_HORA			0x04
#define RTC_AL_DIAMES		0x08
#define RTC_AL_DIASEM		0x01
#define RTC_AL_DIAANIO		0x20
#define RTC_AL_MES			0x40
#define RTC_AL_ANIO			0x80

typedef struct {
	uint8_t seg;
	uint8_t min;
	uint8_t hora;
	uint8_t dia_mes;
	uint8_t dia_semana;
	uint16_t dia_anio;
	uint8_t mes;
	uint16_t anio;
} RTC_HoraFecha;


// Prototipos
void InitRTC(void);
void RTC_HabilitaIntIncremento(uint32_t);
void RTC_HabilitaIntAlarma(uint32_t);
void RTC_SetHoraFecha(const RTC_HoraFecha*);
void RTC_GetHoraFecha(RTC_HoraFecha*);
void RTC_SetAlarma(const RTC_HoraFecha*);
void RTC_GetAlarma(RTC_HoraFecha*);

#endif /* FW_RTC_H_ */
