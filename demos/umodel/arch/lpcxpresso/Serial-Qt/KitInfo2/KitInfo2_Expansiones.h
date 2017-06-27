/*
 * KitInfo2_Expansiones.h
 *
 *  Created on: 09/07/2013
 *      Author: Pablo
 */

#ifndef KITINFO2_EXPANSIONES_H_
#define KITINFO2_EXPANSIONES_H_

#include "KitInfo2.h"

/*******************************
Expansion a utilizar. Puede ser:
	KITINFOII_EXPANSION1
	KITINFOII_EXPANSION2
	KITINFOII_EXPANSION3
 	KITINFOII_EXPANSION4
*******************************/
#define KITINFOII_EXPANSION2

/****************** EXPANSION 1 ******************/
#ifdef	KITINFOII_EXPANSION1

#define EX1_LED1		EXPANSION0		//PORT2,7
#define EX1_LED2		EXPANSION1		//PORT1,29
#define EX1_LED3		EXPANSION2		//PORT4,28
#define EX1_LED4		EXPANSION3		//PORT1,23
#define EX1_LED5		EXPANSION4		//PORT1,20
#define EX1_LED6		EXPANSION5		//PORT0,19
#define EX1_LED7		EXPANSION6		//PORT3,26
#define EX1_LED8		EXPANSION7		//PORT1,25

#define EX1_IN1			EXPANSION8		//PORT1,22
#define EX1_IN2			EXPANSION9		//PORT1,19
#define EX1_IN3			EXPANSION10		//PORT0,20
#define EX1_IN4			EXPANSION11		//PORT3,25
#define EX1_IN5			EXPANSION12		//PORT1,27
#define EX1_IN6			EXPANSION13		//PORT1,24
#define EX1_IN7			EXPANSION14		//PORT1,21
#define EX1_IN8			EXPANSION15		//PORT1,18

/****************** EXPANSION 2 ******************/
#elif defined	KITINFOII_EXPANSION2

//Segmentos displays
#define EX2_A			EXPANSION6		//PORT3,26
#define EX2_B			EXPANSION15		//PORT1,18
#define EX2_C			EXPANSION14		//PORT1,21
#define EX2_D			EXPANSION13		//PORT1,24
#define EX2_E			EXPANSION12		//PORT1,27
#define EX2_F			EXPANSION11		//PORT3,25
#define EX2_G			EXPANSION10		//PORT0,20
#define EX2_DP			EXPANSION9		//PORT1,19

//Habilitacion displays
#define EX2_DIGITO0		EXPANSION5		//PORT0,19
#define EX2_DIGITO1		EXPANSION4		//PORT1,20
#define EX2_DIGITO2		EXPANSION3		//PORT1,23
#define EX2_DIGITO3		EXPANSION2		//PORT4,28
#define EX2_DIGITO4		EXPANSION1		//PORT1,29
#define EX2_DIGITO5		EXPANSION0		//PORT2,7


/****************** EXPANSION 3 ******************/
#elif defined	KITINFOII_EXPANSION3

// Displays
#define EX3_BCDA		EXPANSION0		//PORT2,7
#define EX3_BCDB		EXPANSION1		//PORT1,29
#define EX3_BCDC		EXPANSION2		//PORT4,28
#define EX3_BCDD		EXPANSION3		//PORT1,23
#define EX3_DP			EXPANSION4		//PORT1,20
#define EX3_CLK			EXPANSION5		//PORT0,19
#define EX3_RST			EXPANSION6		//PORT3,26

// Teclado 4x2
#define EX3_FILA0		EXPANSION8		//PORT1,22
#define EX3_FILA1		EXPANSION10		//PORT0,20
#define EX3_FILA2		EXPANSION9		//PORT1,19
#define EX3_FILA3		EXPANSION7		//PORT1,25
#define EX3_COL0		EXPANSION11		//PORT3,25
#define EX3_COL1		EXPANSION12		//PORT1,27

/****************** EXPANSION 4 ******************/
#elif defined	KITINFOII_EXPANSION4

// Display matricial
#define EX4_LCLK		EXPANSION9		//PORT1,19
#define EX4_SRCLK		EXPANSION8		//PORT1,22
#define EX4_SER			EXPANSION7		//PORT1,25
#define EX4_DSPFILA1	EXPANSION6		//PORT3,26
#define EX4_DSPFILA2	EXPANSION5		//PORT0,19
#define EX4_DSPFILA3	EXPANSION4		//PORT1,20
#define EX4_DSPFILA4	EXPANSION3		//PORT1,23
#define EX4_DSPFILA5	EXPANSION2		//PORT4,28
#define EX4_DSPFILA6	EXPANSION1		//PORT1,29
#define EX4_DSPFILA7	EXPANSION0		//PORT2,7

// Teclado 3x3
#define EX4_FILA0		EXPANSION12		//PORT1,27
#define EX4_FILA1		EXPANSION11		//PORT3,25
#define EX4_FILA2		EXPANSION10		//PORT0,20
#define EX4_COL0		EXPANSION15		//PORT1,18
#define EX4_COL1		EXPANSION14		//PORT1,21
#define EX4_COL2		EXPANSION13		//PORT1,24

#else
#error	"Error en definicion de expansion"

#endif /* KITINFOII_EXPANSIONn */

#endif /* KITINFO2_EXPANSIONES_H_ */
