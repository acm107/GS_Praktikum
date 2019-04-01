/**
  ******************************************************************************
  * @file    	TI_memory_map.c 
  * @author  	Nils Schoenherr
  * @version	V1.0
  * @date   	10.10.2016
  * @brief  	Decoupling of different memory-maps for simulation
  ******************************************************************************
  */

#ifndef TI_MEMORY_MAP_H
#define TI_MEMORY_MAP_H

#ifdef SIMULATION
	#include "stm32f10x.h"
#else
	#include "stm32f4xx.h"
#endif

#endif
