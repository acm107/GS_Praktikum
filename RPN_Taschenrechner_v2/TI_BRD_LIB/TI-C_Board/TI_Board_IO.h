/*
*----------------------------------------------------------------------------
 * Name:    	Usart.c
 * Purpose: 	USART usage for STM32
 * Note(s):  	Alfred Lohmann
 *        	  HAW-Hamburg
 *          	Labor für technische Informatik
 *          	Berliner Tor  7
 *          	D-20099 Hamburg
 * 						version V1.0
 *         		adapted to the HAW TI-Bord
 * Date:   		18.07.2013
 *----------------------------------------------------------------------------
 */
 #ifndef __TI_BOARD_IO_H
 #define __TI_BOARD_IO_H
 
  
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
 
 void Init_System_Clock(void);
 void Init_IO(void);
 void Init_SPI(void);
 
 #endif 
 /************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
