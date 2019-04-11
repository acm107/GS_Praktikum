/**
  ******************************************************************************
  * @file    	Stack.c
  * @author  	Faissal Farid, Ehsan Sajadi
  * @version V1.0
  * @date    04.04.2019
  ******************************************************************************
  */


#include "Stack.h"

static int stack[STACKSIZE];
static int8_t sp = 0;

int push(int value){ 
	if(sp == STACKSIZE){
		error_code = STACKFULL;
		return -1;
	}
	stack[sp] = value;
	sp++;
	return 0;
}


int pop(int* zahl){
	
		if(sp > 0){
			*zahl = stack[sp-1];
			sp--;
			return 0;
	}else{
		error_code = STACKEMPTY;
			return -1 ;
	}
}


void c(void){
	sp = 0;	
	errorZeile_cls();
	inputZeile_cls();
	stackZeile_cls();
}

int get_sp(void){
	return sp;
}

int get_elm(int _sp,int* p){
	if (_sp > sp ){
		return -1;
	}
	*p= stack[_sp];
	return 0;
}
