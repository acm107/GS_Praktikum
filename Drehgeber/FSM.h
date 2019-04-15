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

typedef enum {START = 0, A_P, B_P, C_P, D_P, E_P} State_Type;
extern State_Type curr_state;

//Deklarationen der Zustandsfunktionen
uint16_t s_p(uint8_t, uint8_t *);// Start-Phase.
uint16_t a_p(uint8_t, uint8_t *);// A-Phase-Fkt.
uint16_t b_p(uint8_t, uint8_t *);
uint16_t c_p(uint8_t, uint8_t *);
uint16_t d_p(uint8_t, uint8_t *);
uint16_t e_p(uint8_t, uint8_t *);// Fehler Phase

// Initialisierung des Pointer-Arrays mit Fkt.-Namen

extern uint16_t (*state_table[])(uint8_t, uint8_t *);
void get_state_table (uint16_t*);

#endif

