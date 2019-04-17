/**
  ******************************************************************************
  * @file    	FSM.c
  * @author  	Faissal Farid, Ehsan Sajadi ; Isam Karrar , Martin Sazgar
  * @version V1.0
  * @date    27.03.2019
  ******************************************************************************
  */
  
#include "FSM.h"
int16_t count = 0;
uint8_t dir = 0;

extern State_Type curr_state;
//State_Type curr_state = START;



uint16_t s_p(uint8_t pulse_state, uint8_t *ptr){
//logic for curr_state update depends on pulse_state
	switch(pulse_state){
		
		case 0:curr_state = A_P;
		       break; 
		case 1:curr_state = D_P;
		       break; 
		case 2:curr_state = B_P;
		       break; 
		case 3:curr_state = C_P;
		       break; 
		default : curr_state = START;// falsche Kodierung
	}
// direction update
*ptr = dir;
count = 0;
return count;
}

uint16_t a_p(uint8_t pulse_state, uint8_t *ptr){
//logic for curr_state update depends on pulse_state
	switch(pulse_state){
		
		case 0:curr_state = A_P;
		       dir = 0; 
		       break; // ND	
		case 1:curr_state = D_P;
		       count--; 
		       dir = 2; 
		       break; // RW
		case 2:curr_state = B_P;
			   count++;
		       dir = 1;  
		       break; // VW
		case 3:curr_state = E_P;
		       dir = 0; 
		       break; // VW
		default : curr_state = START;// falsche Kodierung
	}
// direction update
*ptr = dir;
return count;
}

uint16_t b_p(uint8_t pulse_state, uint8_t *ptr){
//logic for curr_state update depends on pulse_state
	switch(pulse_state){
		
		case 0:curr_state = A_P;
		       count--; 
		       dir = 1; 
		       break; // RW
		case 1:curr_state = E_P;
		       dir = 0; 
		       break; // ND
		case 2:curr_state = B_P;
		       dir = 0;  
		       break; // ND
		case 3:curr_state = C_P;
		       count++;
		       dir = 2; 
		       break; // VW
		default : curr_state = START;// falsche Kodierung
	}
// direction update
*ptr = dir;
return count;
}

uint16_t c_p(uint8_t pulse_state, uint8_t *ptr){
//logic for curr_state update depends on pulse_state
	switch(pulse_state){
		
		case 0:curr_state = E_P;
		       dir = 0; 
		       break; // ND	
		case 1:curr_state = D_P;
		       count++; 
		       dir = 1; 
		       break; // VW
		case 2:curr_state = B_P;
			   count--;
		       dir = 2;  
		       break; // RW
		case 3:curr_state = C_P;
		       dir = 0; 
		       break; // ND
		default : curr_state = START;// falsche Kodierung
	}
// direction update
*ptr = dir;
return count;
}

uint16_t d_p(uint8_t pulse_state, uint8_t *ptr){
//logic for curr_state update depends on pulse_state
	switch(pulse_state){
		
		case 0:curr_state = A_P;
			   count++;
		       dir = 1; 
		       break; // VW
		case 1:curr_state = D_P;
		       dir = 0; 
		       break; // ND
		case 2:curr_state = E_P;
			   dir = 0;  
		       break; // ND
		case 3:curr_state = C_P;
			   count--;
		       dir = 2; 
		       break; // RW
		default : curr_state = START;// falsche Kodierung
	}
// direction update
*ptr = dir;
return count;
}



uint16_t e_p(uint8_t pulse_state, uint8_t *ptr){
//logic for curr_state update depends on pulse_state
	switch(pulse_state){
		
		case 0:curr_state = E_P;
		       dir = 0; 
		       break; // ND
		case 1:curr_state = E_P;
		       dir = 0; 
		       break; // ND
		case 2:curr_state = E_P;
			   dir = 0;  
		       break; // ND
		case 3:curr_state = E_P;
		       dir = 0; 
		       break; // ND
		default : curr_state = START;// falsche Kodierung
	}
// direction update
*ptr = dir;
return count;
}


