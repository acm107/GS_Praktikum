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
#include <stm32f4xx.h>
#include "TI_memory_map.h"
#include "FSM.h"

#define IDR_MASK_PIN_0   (0x01u << 0)
#define IDR_MASK_PIN_1   (0x01u << 1)
#define IDR_MASK_PIN_7   (0x01U << 7)
#define IDR_MASK_PIN_6   (0x01U << 6)

//int8_t signalLesen (void);
int8_t signalLesen (uint8_t*);
void givePinA(void);
void givePinB(void);
//int8_t gib_dg_state(*, *char);
