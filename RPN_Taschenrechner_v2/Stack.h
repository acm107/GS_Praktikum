/**
  ******************************************************************************
  * @file    	Stack.h
  * @author  	Faissal Farid, Ehsan Sajadi
  * @version V2.0
  * @date    04.06.2019
  ******************************************************************************
  */

#ifndef		_STACK_H
#define		_STACK_H
#endif

#include <stdint.h>
#include "Error.h"
#include "Output.h"

#define STACKSIZE 20

int push(int);
int pop(int*);
void c(void);
int get_sp(void);
int get_elm(int,int*);
