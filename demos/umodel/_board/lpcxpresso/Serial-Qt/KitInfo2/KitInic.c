/*
 * KitInic.c
 *
 *  Created on: 17/04/2012
 *      Author: Mica y Chor
 */

#include "KitInfo2.h"
#include "FW_Timertick.h"
#include "FW_Serie.h"
#include "FW_ADC.h"
#include "FW_DAC.h"
#include "FW_LCD.h"
#include "FW_RTC.h"

void InicializarKit (void)
{
	//Configuro en primer lugar el PLL:
	//Estabiliza el oscilador interno del micro en 100MHz
	InitPLL();
	//Configuro los puertos de entrada/salida de proposito general (GPIOs), como entrada o salida en funcion a como estan en la placa
	InitGPIOs();
	//Systick en 2.5ms
	InitSystick(2500);
	//Inicializacion de UART0 en 9600-8-N-1
	InitUART0();
	//Inicializacion de ADC en modo burst por interrupcion
	InitADC();
	//Inicializacion de DAC
	InitDAC();
	//Inicializacion del LCD en 4 bits
	InitLCD();
	//Inicializacion RTC con interrupcion por incremento de segundo
	InitRTC();
	RTC_HabilitaIntIncremento(RTC_INT_SEG);
}

/********************************************************************************
	\fn  void InitPLL (void)
	\brief: Este bloque de codigo habilita el oscilador externo como fuente de clk
			del micro, y configura un dispositivo conocido como PLL (Phase Locked Loop)
			para generar un clock interno de 100MHz a partir del oscilador conectado.
			SE RECOMIENDA NO MODIFICAR PARA SU USO EN EL KIT DE INFO2
	\author & date: CATEDRA INFO2- Nov2012
 	\param 	void
	\return void
*/
void InitPLL(void) {
	SCS = SCS_Value;

	if (SCS_Value & (1 << 5)) /* If Main Oscillator is enabled      */
	while ((SCS & (1<<6)) == 0);/* Wait for Oscillator to be ready    */

	CCLKCFG = CCLKCFG_Value; /* Setup Clock Divider                */

	PCLKSEL0 = PCLKSEL0_Value; /* Peripheral Clock Selection         */
	PCLKSEL1 = PCLKSEL1_Value;

	CLKSRCSEL = CLKSRCSEL_Value; /* Select Clock Source for PLL0       */

	PLL0CFG = PLL0CFG_Value; /* configure PLL0                     */
	PLL0FEED = 0xAA;
	PLL0FEED = 0x55;

	PLL0CON = 0x01; /* PLL0 Enable                        */
	PLL0FEED = 0xAA;
	PLL0FEED = 0x55;

	while (!(PLL0STAT & (1<<26)));/* Wait for PLOCK0                    */

	PLL0CON = 0x03; /* PLL0 Enable & Connect              */
	PLL0FEED = 0xAA;
	PLL0FEED = 0x55;

	while (!(PLL0STAT & ((1<<25) | (1<<24))));/* Wait for PLLC0_STAT & PLLE0_STAT */

	PLL1CFG = PLL1CFG_Value;
	PLL1FEED = 0xAA;
	PLL1FEED = 0x55;

	PLL1CON = 0x01; /* PLL1 Enable                        */
	PLL1FEED = 0xAA;
	PLL1FEED = 0x55;

	while (!(PLL1STAT & (1<<10)));/* Wait for PLOCK1                    */

	PLL1CON = 0x03; /* PLL1 Enable & Connect              */
	PLL1FEED = 0xAA;
	PLL1FEED = 0x55;

	while (!(PLL1STAT & ((1<< 9) | (1<< 8))));/* Wait for PLLC1_STAT & PLLE1_STAT */

	PCONP = PCONP_Value; /* Power Control for Peripherals      */

	CLKOUTCFG = CLKOUTCFG_Value; /* Clock Output Configuration         */

	FLASHCFG = (FLASHCFG & ~0x0000F000) | FLASHCFG_Value;
}
/********************************************************************************
	\fn  void InitGPIOs (void)
	\brief: Para cada PIN de un PUERTO de entrada/salida, tengo que configurar 2 registros:
			PINSEL: Selecciona si el pin se comportara como un GPIO o como el pin de un periférico
					Para modificar este registro uso la función SetPINSEL, definida en UtilesInfo2.c
			FIODIR:	Selecciona si el pin se comportara como una entrada o como una salida digital
					Para modificar este registro uso la función SetPIN, definida en UtilesInfo2.c
 
	\author & date: CATEDRA INFO2 - Feb2012
 	\param 	void
	\return void
*/
void InitGPIOs (void)
{	//1°)Selecciono FUNCION del pin en PINSELx.
			//void SetPINSEL (uint8_t puerto, uint8_t pin, uint8_t modo)
	//leds
	SetPINSEL(P2,0,PINSEL_GPIO);	//LED1
	SetPINSEL(P0,23,PINSEL_GPIO);	//LED2
	SetPINSEL(P0,21,PINSEL_GPIO);	//LED3
	SetPINSEL(P0,27,PINSEL_GPIO);	//LED4
	SetPINSEL(P2,1,PINSEL_GPIO);	//RGBR
	SetPINSEL(P2,2,PINSEL_GPIO);	//RGBG
	SetPINSEL(P2,3,PINSEL_GPIO);	//RGBB
	//Buzzer:
	SetPINSEL(P0,28,PINSEL_GPIO);
	//Teclas (teclado 4x1)
	SetPINSEL(P2,10,PINSEL_GPIO);	//Key0
	SetPINSEL(P0,18,PINSEL_GPIO);	//Key1
	SetPINSEL(P0,11,PINSEL_GPIO);	//Key2
	SetPINSEL(P2,13,PINSEL_GPIO);	//Key3
	//PulsadorRC:
	SetPINSEL(P1,26,PINSEL_GPIO);
	//Entradas digitales:
	SetPINSEL(P4,29,PINSEL_GPIO);	//IN0
	SetPINSEL(P2,11,PINSEL_GPIO);	//IN1

	//2°)A aquellos pines configurados como GPIO, les configuro su DIRECCION en FIOxDIR
			//void SetDIR(registro* puerto,uint8_t pin,uint8_t direccion)
//SALIDAS:
	//Leds (Reles)
	SetDIR (LED1, SALIDA);
	SetDIR (LED2, SALIDA);
	SetDIR (LED3, SALIDA);
	SetDIR (LED4, SALIDA);
	//Led RGB:
	SetDIR (RGBR, SALIDA);
	SetDIR (RGBG, SALIDA);
	SetDIR (RGBB, SALIDA);
	//Buzzer:
	SetDIR (BUZZ, SALIDA);
//ENTRADAS
	//teclas
	SetDIR (KEY0, ENTRADA);
	SetDIR (KEY1, ENTRADA);
	SetDIR (KEY2, ENTRADA);
	SetDIR (KEY3, ENTRADA);
	//PulsadorRC:
	SetDIR (KEY_RC, ENTRADA);
	//Entradas digitales:
	SetDIR (IN0, ENTRADA);
	SetDIR (IN1, ENTRADA);

	//Empiezo el programa con los LEDs y el buzzer apagados
	SetPIN(LED1,OFF);
	SetPIN(LED2,OFF);
	SetPIN(LED3,OFF);
	SetPIN(LED4,OFF);
	SetPIN(BUZZ,BUZZ_OFF);
}
