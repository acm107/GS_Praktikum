/**
  ******************************************************************************
  * @file    	input.h
  * @author  	Faissal Farid, Ehsan Sajadi
  * @version V1.0
  * @date    27.03.2019
  ******************************************************************************
  */
  
#include <stdbool.h>
#include <stdio.h>
//#include <stm32f4xx.h>
//#include <stm32f10x.h>
#include "TI_memory_map.h"
//#include "FSM.h"

#define IDR_MASK_PIN_0   (0x01u << 0)
#define IDR_MASK_PIN_1   (0x01u << 1)
#define IDR_MASK_PIN_7   (0x01U << 7)
#define IDR_MASK_PIN_6   (0x01U << 6)


int8_t signalLesen (uint8_t*, bool*, bool*);
bool givePinA(void);
bool givePinB(void);

bool pin6_Pressed(void);
bool pin7_Pressed(void);
