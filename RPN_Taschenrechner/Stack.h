/**
  ******************************************************************************
  * @file    	Stack.h
  * @author  	Faissal Farid, Ehsan Sajadi
  * @version V1.0
  * @date    26.03.2019
  ******************************************************************************
  */

#include <stdbool.h>

#ifndef		_STACK_H
#define		_STACK_H

/**
*@brief zum schreiben auf dem stack.
*/
void push(int);

/**
*@brief zum Lesen und entfernen vom Stack.
*/
int pop(void);

/**
*@brief Sagt ob der Stack leer ist.
*@return zahl, 0 ist false und 1 ist true
*/
bool isEmpty(void);

/**
*@brief Sagt ob der Stack bereits voll ist.
*@return zahl, 0 ist false und 1 ist true
*/
bool isFull(void);

/**
*@brief liefert den topesten zahl vom Stack.
*@return zahl, obersten Zahl
*/
int top(void);

/**
*@brief liefert den zweite zahl vom Stack.
*@return zahl, zweite Zahl
*/
int secendValue(void);

/**
*@brief ob es zwei Zahl auf dem Stack gibt.
*@return zahl,  0 ist false und 1 ist true
*/
bool containsTwo(void);

/**
*@brief druckt den obersten Wert des Stacks aus.
*@return zahl,  0 ist false und 1 ist true
*/
int p(void);

/**
*@brief druckt den gesamten Stack aus.
*@return zahl,  0 ist false und 1 ist true
*/
void f(void);

/**
*@brief löscht alle Einträge des Stacks
*@return zahl,  0 ist false und 1 ist true
*/
void c(void);

/**
*@brief dupliziert den obersten Eintrag
*@return zahl,  0 ist false und 1 ist true
*/
void d(int);

/**
*@brief vertauscht die Reihenfolge 
*       der beiden obersten Einträge.
*@return zahl,  0 ist false und 1 ist true
*/
void r(void);


#endif
