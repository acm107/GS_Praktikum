/**
  ******************************************************************************
  * @file    	Input.h
  * @author  	Faissal Farid, Ehsan Sajadi
  * @version V1.0
  * @date    04.04.2019
  ******************************************************************************
  */

#ifndef _INPUT_H
#define _INPUT_H

#endif


#include "Stack.h"
#include "Error.h"
#include "keypad.h"
#include "Output.h"
#include <stdint.h>
#include "Calc.h"



#define ASCII0 48 // Konstante für den Beginn(0) der Zahlen in ASCII
#define ASCII9 57 // Konstante für das Ende(9) der Zahlen in ASCII
	
int reactToInput(int wert);
int getInput(void);
void make_Lines(void);
int input_check(void);

int p(void);
int d(void);
int r(void);
int f(void);

void last_zahl_del(void);
