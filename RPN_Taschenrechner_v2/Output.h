/**
  ******************************************************************************
  * @file    	Output.h
  * @author  	Faissal Farid, Ehsan Sajadi
  * @version V1.0
  * @date    04.04.2019
  ******************************************************************************
  */

#include "tft.h"
#include "keypad.h"
#include <stdio.h>
#include "Error.h"

// Parameter für die Displayausgabe des Inputs
#define FONTI 		 2
#define	INPUTX		 4
#define	INPUTY		 4
#define	WIDTHI 		20
#define	ROWSI			 1

// Parameter für die Displayausgabe des Stacks
#define FONTS 		 2
#define	STACKX		 4
#define	STACKY		 2
#define	WIDTHS 		35
#define	ROWSS			 2

#ifndef _OUTPUT_H
#define _OUTPUT_H

#endif

//void print_of_display(int);
void print_Input_zeile(int);
void print_Stack_zeile(int);
void inputZeile_cls(void);
void stackZeile_cls(void);
void print_stack_f(int);
