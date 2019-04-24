
/**
  ******************************************************************************
  * @file    	timer.h 
  * @author  	Schoenher, Nils
  * @version  V1.0
  * @date     10.10.2016
  * @brief    Timer for calculation
  ******************************************************************************
  */

#ifndef __TIMER_H
#define __TIMER_H

#include <stdint.h>

#define CONVERT2US 84 /* Mhz */

/**
* @brief Init hardwareTimer
* @param None
* @retval None
*/
void timerinit(void);

/**
* @brief get Timer ticks
* @param None
* @retval timerTicks
*/
uint32_t getTimeStamp(void);

void resetTime(void);

#endif
