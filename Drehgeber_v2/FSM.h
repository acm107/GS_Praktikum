/**
  ******************************************************************************
  * @file    	FSM.h
  * @author  	Faissal Farid, Ehsan Sajadi
  * @version V1.0
  * @date    27.03.2019
  ******************************************************************************
  */
  
#include <stdint.h>


#ifndef _FSM_H
#define _FSM_H


#include "TI_memory_map.h"
#include "timer.h"


#define MASK_PIN_5 (0x01U << 5) //error laempchen





typedef enum {START = 0, A_P, B_P, C_P, D_P, E_P} State_Type;

//Deklarationen der Zustandsfunktionen
//@param (dg_state,ptr_dir,pulse_conter,s6,s7)
int8_t s_p(uint8_t, uint8_t *, int16_t *, int8_t, int8_t);// Start-Phase.
int8_t a_p(uint8_t, uint8_t *, int16_t *, int8_t, int8_t);// A-Phase-Fkt.
int8_t b_p(uint8_t, uint8_t *, int16_t *, int8_t, int8_t);
int8_t c_p(uint8_t, uint8_t *, int16_t *, int8_t, int8_t);
int8_t d_p(uint8_t, uint8_t *, int16_t *, int8_t, int8_t);
int8_t e_p(uint8_t, uint8_t *, int16_t *, int8_t, int8_t);// Error Phase








/*
Die Funktione geht einen Schritt
*/
int8_t use_automat (uint8_t, uint8_t *, int16_t *, int8_t, int8_t);




#endif

