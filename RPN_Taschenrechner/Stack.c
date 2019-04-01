/**
  ******************************************************************************
  * @file    	Stack.c
  * @author  	Faissal Farid, Ehsan Sajadi
  * @version V1.0
  * @date    26.03.2019
  ******************************************************************************
  */

//Include---------------------------------------
#include "tft.h"
#include "General.h"
#include "Stack.h"
#include "Output.h"
#include "Error.h"
#include <stdio.h>
#include <stdbool.h>
#include "Input.h"

static int stack[STACKSIZE];
static int pointer = 0;

/**
*@brief zum schreiben auf dem stack.
*/
void push(int value){
	errorZeile_cls();
	if(isFull()){
		error_code = STACKFULL;
		printErrorMessag();
		return;
	}
	stack[pointer] = value;
	printf("%d",stack[pointer]);
	pointer++;
}

/**
*@brief zum Lesen und entfernen vom Stack.
*/
int pop(void){
	errorZeile_cls();
		if(isEmpty()){
			error_code = STACKEMPTY;
			printErrorMessag();
			ERROR_ON = 1;
			return ERROR_ON ;
	}else{
			int value = stack[pointer-1];
			stack[pointer-1] = 0;
			pointer--;
			return value;
	}
}

/**
*@brief Sagt ob der Stack leer ist.
*@return zahl, 0 ist false und 1 ist true
*/
bool isEmpty(void){
	return (pointer ==0) ? true : false;
}

/**
*@brief Sagt ob der Stack bereits voll ist.
*@return zahl, 0 ist false und 1 ist true
*/
bool isFull(void){
	return (STACKSIZE == pointer) ? true : false;
}
	
/**
*@brief liefert den topesten zahl vom Stack.
*@return zahl, obersten Zahl
*/
int top(void){
	errorZeile_cls();
	if(isEmpty()){
		error_code = STACKEMPTY;
		printErrorMessag();
		ERROR_ON = 1;
		return ERROR_ON ;
	}else{
		int value = stack[pointer-1];
		return value;
	}
}

int sec(void){
	return stack[pointer -2];
}
/**
*@brief ob es zwei Zahl auf dem Stack gibt.
*@return zahl,  0 ist false und 1 ist true
*/
bool containsTwo(void){
	 return (pointer >= 2) ? true : false;
}


/**
*@brief druckt den obersten Wert des Stacks aus.
*@return zahl,  0 ist false und 1 ist true
*/
int p(void){
	errorZeile_cls();
	if(isEmpty()){
		error_code = STACKEMPTY;
		printErrorMessag();
		ERROR_ON = 1;
		return ERROR_ON;
	}else{
		int value = stack[pointer-1];
		return value;
	}
}



/**
*@brief druckt den gesamten Stack aus.
*@return zahl,  0 ist false und 1 ist true
*/
void f(void){
	errorZeile_cls();
	stack_cls();
	for(int i = 0;i <= (pointer -1);i++){
		print_stack_f(stack[i]);
	}
}


/**
*@brief löscht alle Einträge des Stacks
*@return zahl,  0 ist false und 1 ist true
*/
void c(void){
	pointer = 0;	
	errorZeile_cls();
	input_cls();
	stack_cls();
	ERROR_ON = 0;
}


/**
*@brief dupliziert den obersten Eintrag
*@return zahl,  0 ist false und 1 ist true
*/
void d(int a){
	if(isEmpty()){
		error_code = STACKEMPTY;
		printErrorMessag();
		return;
	}
	int dublicate = top();
	push(dublicate);
}


/**
*@brief overtauscht die Reihenfolge 
*       der beiden obersten Einträge.
*@return zahl,  0 ist false und 1 ist true
*/
void r(void){
	errorZeile_cls();
	if(!containsTwo()){
		error_code = NEEDSTWO;
		printErrorMessag();
		return;
	}
	int erste = pop();
	int zweite = pop();
	push(erste);
	push(zweite);
	print_Stack(p());
}

