/**
  ******************************************************************************
  * @file    	timer.c 
  * @author  	Schoenher, Nils
  * @version  V1.0
  * @date     10.10.2016
  * @brief    Timer related functions
  ******************************************************************************
  */

#include "TI_memory_map.h"
#include "timer.h"

void timerinit(void){
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; /* Takt fuer Timer 2 einschalten */
    TIM2->CR1 = 0;                      /* Timer disabled                */
    TIM2->CR2 = 0;                      /*                               */
    TIM2->PSC = 84;                      /* Prescaler   (84MHz)           */
#ifndef SIMULATION
    TIM2->ARR = 0xf4240;             /* Auto reload register          */
#else
    TIM2->ARR = 0xffff;             		/* Auto reload register          */
#endif
    TIM2->DIER  = 0;                    /* Interrupt ausschalten         */
    TIM2->CR1 = TIM_CR1_CEN;            /* Enable Timer                  */
}

uint32_t getTimeStamp(){
	return (TIM2->CNT);
}


