/*
 * KitInic_Expansiones.c
 *
 *  Created on: 10/07/2013
 *      Author: Pablo
 */

#include "KitInfo2_Expansiones.h"
#include "KitInic_Expansiones.h"

void InitEXP(void)
{
#ifdef	KITINFOII_EXPANSION1
	InitIO();
#elif defined	KITINFOII_EXPANSION2
	InitDisplay();
#elif defined	KITINFOII_EXPANSION3
	InitDisplay();
	InitTeclado();
#elif defined	KITINFOII_EXPANSION4
	InitDisplayMatricial();
	InitTeclado();
#endif
}

#ifdef	KITINFOII_EXPANSION1

void InitIO(void)
{
	SetPINSEL(P2,7,PINSEL_GPIO);	//EX1_LED1
	SetPINSEL(P1,29,PINSEL_GPIO);	//EX1_LED2
	SetPINSEL(P4,28,PINSEL_GPIO);	//EX1_LED3
	SetPINSEL(P1,23,PINSEL_GPIO);	//EX1_LED4
	SetPINSEL(P1,20,PINSEL_GPIO);	//EX1_LED5
	SetPINSEL(P0,19,PINSEL_GPIO);	//EX1_LED6
	SetPINSEL(P3,26,PINSEL_GPIO);	//EX1_LED7
	SetPINSEL(P1,25,PINSEL_GPIO);	//EX1_LED8

	SetPINSEL(P1,22,PINSEL_GPIO);	//EX1_IN1
	SetPINSEL(P1,19,PINSEL_GPIO);	//EX1_IN2
	SetPINSEL(P0,20,PINSEL_GPIO);	//EX1_IN3
	SetPINSEL(P3,25,PINSEL_GPIO);	//EX1_IN4
	SetPINSEL(P1,27,PINSEL_GPIO);	//EX1_IN5
	SetPINSEL(P1,24,PINSEL_GPIO);	//EX1_IN6
	SetPINSEL(P1,21,PINSEL_GPIO);	//EX1_IN7
	SetPINSEL(P1,18,PINSEL_GPIO);	//EX1_IN8

	SetDIR(EX1_LED1, SALIDA);
	SetDIR(EX1_LED2, SALIDA);
	SetDIR(EX1_LED3, SALIDA);
	SetDIR(EX1_LED4, SALIDA);
	SetDIR(EX1_LED5, SALIDA);
	SetDIR(EX1_LED6, SALIDA);
	SetDIR(EX1_LED7, SALIDA);
	SetDIR(EX1_LED8, SALIDA);
	SetDIR(EX1_IN1, ENTRADA);
	SetDIR(EX1_IN2, ENTRADA);
	SetDIR(EX1_IN3, ENTRADA);
	SetDIR(EX1_IN4, ENTRADA);
	SetDIR(EX1_IN5, ENTRADA);
	SetDIR(EX1_IN6, ENTRADA);
	SetDIR(EX1_IN7, ENTRADA);
	SetDIR(EX1_IN8, ENTRADA);
}

#elif defined	KITINFOII_EXPANSION2

void InitDisplay(void)
{
	SetPINSEL(P3,26,PINSEL_GPIO);	//EX2_A
	SetPINSEL(P1,18,PINSEL_GPIO);	//EX2_B
	SetPINSEL(P4,21,PINSEL_GPIO);	//EX2_C
	SetPINSEL(P1,24,PINSEL_GPIO);	//EX2_D
	SetPINSEL(P1,27,PINSEL_GPIO);	//EX2_E
	SetPINSEL(P3,25,PINSEL_GPIO);	//EX2_F
	SetPINSEL(P0,20,PINSEL_GPIO);	//EX2_G
	SetPINSEL(P1,19,PINSEL_GPIO);	//EX2_DP

	SetPINSEL(P0,19,PINSEL_GPIO);	//EX2_DIGITO0
	SetPINSEL(P1,20,PINSEL_GPIO);	//EX2_DIGITO1
	SetPINSEL(P1,23,PINSEL_GPIO);	//EX2_DIGITO2
	SetPINSEL(P4,28,PINSEL_GPIO);	//EX2_DIGITO3
	SetPINSEL(P1,29,PINSEL_GPIO);	//EX2_DIGITO4
	SetPINSEL(P2,7,PINSEL_GPIO);	//EX2_DIGITO5

	SetDIR(EX2_A, SALIDA);
	SetDIR(EX2_B, SALIDA);
	SetDIR(EX2_C, SALIDA);
	SetDIR(EX2_D, SALIDA);
	SetDIR(EX2_E, SALIDA);
	SetDIR(EX2_F, SALIDA);
	SetDIR(EX2_G, SALIDA);
	SetDIR(EX2_DP, SALIDA);
	SetDIR(EX2_DIGITO0, SALIDA);
	SetDIR(EX2_DIGITO1, SALIDA);
	SetDIR(EX2_DIGITO2, SALIDA);
	SetDIR(EX2_DIGITO3, SALIDA);
	SetDIR(EX2_DIGITO4, SALIDA);
	SetDIR(EX2_DIGITO5, SALIDA);
}

#elif defined	KITINFOII_EXPANSION3

void InitDisplay(void)
{
	SetPINSEL(P2,7,PINSEL_GPIO);	//EX3_BCDA
	SetPINSEL(P1,29,PINSEL_GPIO);	//EX3_BCDA
	SetPINSEL(P4,28,PINSEL_GPIO);	//EX3_BCDA
	SetPINSEL(P1,23,PINSEL_GPIO);	//EX3_BCDA
	SetPINSEL(P1,20,PINSEL_GPIO);	//EX3_DP
	SetPINSEL(P0,19,PINSEL_GPIO);	//EX3_CLK
	SetPINSEL(P3,26,PINSEL_GPIO);	//EX3_RST

	SetDIR(EX3_BCDA, SALIDA);
	SetDIR(EX3_BCDB, SALIDA);
	SetDIR(EX3_BCDC, SALIDA);
	SetDIR(EX3_BCDD, SALIDA);
	SetDIR(EX3_DP, SALIDA);
	SetDIR(EX3_CLK, SALIDA);
	SetDIR(EX3_RST, SALIDA);
}

void InitTeclado(void)
{
	SetPINSEL(P1,25,PINSEL_GPIO);	//EX3_FILA0
	SetPINSEL(P1,22,PINSEL_GPIO);	//EX3_FILA1
	SetPINSEL(P1,19,PINSEL_GPIO);	//EX3_FILA2
	SetPINSEL(P0,20,PINSEL_GPIO);	//EX3_FILA3
	SetPINSEL(P3,25,PINSEL_GPIO);	//EX3_COL0
	SetPINSEL(P1,17,PINSEL_GPIO);	//EX3_COL1

	SetDIR(EX3_FILA0, ENTRADA);
	SetDIR(EX3_FILA1, ENTRADA);
	SetDIR(EX3_FILA2, ENTRADA);
	SetDIR(EX3_FILA3, ENTRADA);
	SetDIR(EX3_COL0, SALIDA);
	SetDIR(EX3_COL1, SALIDA);
}

#elif defined	KITINFOII_EXPANSION4

void InitDisplayMatricial(void)
{
	SetPINSEL(P1,19,PINSEL_GPIO);	//EX4_LCLK
	SetPINSEL(P1,22,PINSEL_GPIO);	//EX4_SRCLK
	SetPINSEL(P1,25,PINSEL_GPIO);	//EX4_SER
	SetPINSEL(P3,26,PINSEL_GPIO);	//EX4_DSPFILA1
	SetPINSEL(P0,19,PINSEL_GPIO);	//EX4_DSPFILA2
	SetPINSEL(P1,20,PINSEL_GPIO);	//EX4_DSPFILA3
	SetPINSEL(P1,23,PINSEL_GPIO);	//EX4_DSPFILA4
	SetPINSEL(P4,28,PINSEL_GPIO);	//EX4_DSPFILA5
	SetPINSEL(P1,29,PINSEL_GPIO);	//EX4_DSPFILA6
	SetPINSEL(P2,7,PINSEL_GPIO);	//EX4_DSPFILA7

	SetDIR(EX4_LCLK, SALIDA);
	SetDIR(EX4_SRCLK, SALIDA);
	SetDIR(EX4_SER, SALIDA);
	SetDIR(EX4_DSPFILA1, SALIDA);
	SetDIR(EX4_DSPFILA2, SALIDA);
	SetDIR(EX4_DSPFILA3, SALIDA);
	SetDIR(EX4_DSPFILA4, SALIDA);
	SetDIR(EX4_DSPFILA5, SALIDA);
	SetDIR(EX4_DSPFILA6, SALIDA);
	SetDIR(EX4_DSPFILA7, SALIDA);
}

void InitTeclado(void)
{
	SetPINSEL(P1,27,PINSEL_GPIO);	//EX4_FILA0
	SetPINSEL(P3,25,PINSEL_GPIO);	//EX4_FILA1
	SetPINSEL(P0,20,PINSEL_GPIO);	//EX4_FILA2
	SetPINSEL(P1,18,PINSEL_GPIO);	//EX4_COL0
	SetPINSEL(P1,21,PINSEL_GPIO);	//EX4_COL1
	SetPINSEL(P1,24,PINSEL_GPIO);	//EX4_COL2

	SetDIR(EX4_FILA0, ENTRADA);
	SetDIR(EX4_FILA1, ENTRADA);
	SetDIR(EX4_FILA2, ENTRADA);
	SetDIR(EX4_COL0, SALIDA);
	SetDIR(EX4_COL1, SALIDA);
	SetDIR(EX4_COL2, SALIDA);
}

#endif