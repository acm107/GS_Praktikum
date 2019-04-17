/**
  ******************************************************************************
  * @file    	main.c 
  * @author  	Alfred Lohmann
  *        	  HAW-Hamburg
  *          	Labor für technische Informatik
  *          	Berliner Tor  7
  *          	D-20099 Hamburg
  * @version V1.0
  * @date    23.05.2013
  * @brief   Main program body
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

#include "TI_Lib.h"
#include "tft.h"
#include "FSM.h"
#include "input.h"

//--- For GPIOs -----------------------------
//Include instead of "stm32f4xx.h" for
//compatibility between Simulation and Board
//#include "TI_memory_map.h"

//--- For Touch Keypad ----------------------
//#include "keypad.h"

//--- For Timer -----------------------------
//#include "timer.h"

/**
  * @brief  Main program
  * @param  None
  */
  
int16_t pulse_count = 0;
uint8_t dg_state = 0;
float Geschwindigkeit = 0;
float Dreh_Winkel = 0;
uint8_t ptr_dir = 0;
State_Type curr_state = START;
uint16_t (*state_table[])(uint8_t, uint8_t *) = {s_p, a_p, b_p, c_p, d_p, e_p};


int main(void)
{
	
	Init_TI_Board();
	//init_Disp();
	while(1)
	{
		
	
        //Input
        signalLesen(&dg_state);

        //Auswertung
			
        pulse_count = state_table[curr_state](dg_state, &ptr_dir);
	    
        
        //output
	}

}
// EOF
