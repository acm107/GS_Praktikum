/**
  ******************************************************************************
  * @file       FSM.c
  * @author     Faissal Farid, Ehsan Sajadi ; Isam Karrar , Martin Sazgar
  * @version V1.0
  * @date    27.03.2019
  ******************************************************************************
  */
  
#include "FSM.h"



/*
FSM Automat.
Aktualisieren die Richtung und den curr_state. Überpruft ob Taste S6 und S7 gedrückt worden sind.  

@param dg_state 
@param ptr_dir        Richtung der Drehung. VW = 1 oder RW = 2 oder nicht bewegt = 0
@param pulse_counter  Anzahl der Phasen 
@param s6
@param s7

*/
int8_t (*state_table[])(uint8_t, uint8_t *, int16_t *, int8_t, int8_t) = {s_p, a_p, b_p, c_p, d_p, e_p}; 

State_Type curr_state = START;  //Anfangs-Zustand des Automaten



uint8_t direction = 0;
int8_t err = 0;





int8_t use_automat (uint8_t dg_state, uint8_t* ptr_dir, int16_t* pulse_count, int8_t s6, int8_t s7)
{
	
        uint16_t	error = state_table[curr_state](dg_state, ptr_dir, pulse_count, s6, s7);
		    
			  //wenn error == 1 dann fehler!
		    if(error == 1) 
				{
			     GPIOG->BSRRL = MASK_PIN_5; //Schalte Pin 5 an
		    }
				return error;
}




int8_t s_p(uint8_t dg_state, uint8_t * dir, int16_t * pulse_count, int8_t s6, int8_t s7){
//logic for curr_state update depends on dg_state
    resetTime();
    
    if(s7) {
        *pulse_count = 0;
        //curr_state = START;
    }
	if(s6) {
		//GPIOG->BSRRH = MASK_PIN_5;
		err = 0;
	}
	
    switch(dg_state){
        
        case 0:curr_state = A_P;            
               break; 
               
        case 1:curr_state = D_P;
               break; 
               
        case 2:curr_state = B_P;        
               break; 
               
        case 3:curr_state = C_P;
               break; 
               
    }
// direction update
*dir = 0;
*pulse_count = 0;
return err;
}

int8_t a_p(uint8_t dg_state, uint8_t * dir, int16_t * pulse_count, int8_t s6, int8_t s7){
//logic for curr_state update depends on dg_state

    if(s7) {
        *pulse_count = 0;
        //curr_state = START;
    }
	if(s6) {
		//GPIOG->BSRRH = MASK_PIN_5;
		err = 0;
	}
    
    switch(dg_state){
        
        case 0:curr_state = A_P;
               direction = 0; 
               break; // ND 
		
        case 1:curr_state = D_P; 
               *pulse_count -= 1; 
               direction = 2; 
               break; // RW
		
        case 2:curr_state = B_P;
               *pulse_count += 1;
               direction = 1;  
               break; // VW
		
        case 3:curr_state = E_P;
               direction = 0; 
			   err = 1;
               break; 

    }
// direction update
*dir = direction;
return err;
}

int8_t b_p(uint8_t dg_state, uint8_t * dir, int16_t * pulse_count, int8_t s6, int8_t s7){
//logic for curr_state update depends on dg_state

    if(s7) {
        *pulse_count = 0;
        //curr_state = START;
    }
	if(s6) {
		//GPIOG->BSRRH = MASK_PIN_5;
		err = 0;
	}
    
    switch(dg_state){
        
        case 0:curr_state = A_P;
               *pulse_count -= 1; 
               direction = 1; 
               break; // RW
		
        case 1:curr_state = E_P;
               direction = 0; 
		       err = 1;
               break; // ND
		
        case 2:curr_state = B_P;
               direction = 0;  
               break; // ND
		
        case 3:curr_state = C_P;
               *pulse_count += 1;
               direction = 2; 
               break; // VW
      
    }
// direction update
*dir = direction;
return err;
}

int8_t c_p(uint8_t dg_state, uint8_t * dir, int16_t * pulse_count, int8_t s6, int8_t s7){
//logic for curr_state update depends on dg_state

    if(s7) {
        *pulse_count = 0;
        //curr_state = START;
    }
	if(s6) {
		//GPIOG->BSRRH = MASK_PIN_5;
		err = 0;
	}
                        
    switch(dg_state){
        
        case 0:curr_state = E_P;
               direction = 0;    
			   err = 1;
               break; // ND 
		
        case 1:curr_state = D_P;
               *pulse_count += 1; 
               direction = 1; 
               break; // VW
		
        case 2:curr_state = B_P;
               *pulse_count -= 1;
               direction = 2;  
               break; // RW
		
        case 3:curr_state = C_P;
               direction = 0; 
               break; // ND
       
    }
// direction update
*dir = direction;
return err;
}

int8_t d_p(uint8_t dg_state, uint8_t * dir, int16_t * pulse_count, int8_t s6, int8_t s7){
//logic for curr_state update depends on dg_state

	if(s7) {
        *pulse_count = 0;
        //curr_state = START;
    }
	if(s6) {
		//GPIOG->BSRRH = MASK_PIN_5;
		err = 0;
	}
	
    switch(dg_state){
        
        case 0:curr_state = A_P;
               *pulse_count += 1;
               direction = 1; 
               break; // VW
		
        case 1:curr_state = D_P;
               direction = 0; 
               break; // ND
		
        case 2:curr_state = E_P;
               direction = 0;  
			   err = 1;	
               break; // ND
		
        case 3:curr_state = C_P;
               *pulse_count -= 1;
               direction = 2; 
               break; // RW

    }
// direction update
*dir = direction;
return err;
}



int8_t e_p(uint8_t dg_state, uint8_t * dir, int16_t * pulse_count, int8_t s6 , int8_t s7){
//logic for curr_state update depends on dg_state
	if(s7) {
        *pulse_count = 0;
        //curr_state = START;
    }
	if(s6) {
		GPIOG->BSRRH = MASK_PIN_5;     //LED D18 aus
		curr_state = START;
		err = 0;
	} else {
		err = 1;
	

		switch(dg_state){
			
			case 0:curr_state = E_P;
				   direction = 0; 
				   break; // ND
			
			case 1:curr_state = E_P;
				   direction = 0; 
				   break; // ND
			
			case 2:curr_state = E_P;
				   direction = 0;  
				   break; // ND
			
			case 3:curr_state = E_P;
				   direction = 0; 
				   break; // ND
			
		}
	}
// direction update
*dir = direction;
return err;
}


