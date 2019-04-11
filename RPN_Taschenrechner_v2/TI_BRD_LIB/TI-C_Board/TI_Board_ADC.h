/*
*----------------------------------------------------------------------------
 * Name:    	TI_BOARD_ADC.c
 * Purpose: 	ADC usage for STM32
 * Note(s):  	Silke Behn
 *        	    HAW-Hamburg
 *          	Labor für technische Informatik
 *          	Berliner Tor  7
 *          	D-20099 Hamburg
 * 						version V1.0
 *         		adapted to the HAW TI-Bord
 * Date:   		18.07.2014
 * 10.10.2016	Nils Schoenherr: change to stdint.h for decoupling of stm32f...
 *----------------------------------------------------------------------------
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TI_BOARD_ADC_H
#define __TI_BOARD_ADC_H

#include <stdint.h>

//__IO  uint32_t ADC3ConvertedValue;
//uint32_t ADC3ConvertedValuex;

//ADC3.7
void ADC3_CH7_DMA_Config(void);

uint32_t getADC3ConvertedValue(void);

#endif // __TI_BOARD_ADC_H 
