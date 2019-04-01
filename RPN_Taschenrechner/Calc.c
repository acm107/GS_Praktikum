/**
  ******************************************************************************
  * @file    	Calc.c
  * @author  	Faissal Farid, Ehsan Sajadi
  * @version V1.0
  * @date    27.03.2019
  ******************************************************************************
  */
	
#include "Calc.h"
#include "Stack.h"
#include "Error.h"
#include "Output.h"
#include <stdint.h>

	/**
  * @brief  Funktion * nimmt zwei Werte vom Stack, multipliziert sie und legt das Ergebnis
	*					wieder auf dem Stack ab.
  * @return  0 Wenn Erfolgreich; -1 Wenn Fehler.
  */
void multiplizieren(void){
	if(!containsTwo()){
			error_code = NEEDSTWO;
			printErrorMessag();
		return;
	}
	int num1 = pop();
	int num2 = pop();
	push(num2 * num1);
	print_Stack(p());
}

/**
  * @brief  Funktion / nimmt zwei Werte vom Stack, teilt den zweiten Wert durch den ersten
	*					(ganzzahlige Division) und legt das Ergebnis wieder auf dem Stack ab.
  * @return  0 Wenn Erfolgreich; -1 Wenn Fehler.
  */
void dividieren(void){
	if(!containsTwo()){
			error_code = NEEDSTWO;
			printErrorMessag();
		return;
	}
	int num1 = pop();
	int num2 = pop();
	if(num1 == 0){
		error_code = NOTDIV0;
		printErrorMessag();
		return;
	}
	push(num2 / num1);
	print_Stack(p());
}

/**
  * @brief  Funktion + nimmt zwei Werte vom Stack, addiert sie und legt das Ergebnis wieder
	*					auf dem Stack ab.
  * @return  0 Wenn Erfolgreich; -1 Wenn Fehler.
  */
void addieren(void){
	if(!containsTwo()){
		error_code = NEEDSTWO;
			printErrorMessag();
		return;
	}
	if(top()> 0 && sec() > 0){
		int a = INT32_MAX - top();
		int b=sec();
		if(a <b)
		{
			error_code = INTOVERFLOW;
			printErrorMessag();
			return;
		}
	}else if(top() < 0 &&  sec() < 0){
		if(INT32_MIN - top() > sec())
		{
			error_code = INTOVERFLOW;
		printErrorMessag();
			return;
		}
	}
	int num1 = pop();
	int num2 = pop();
		
	push(num2 + num1);
	print_Stack(p());
	
	
}

/**
  * @brief  Funktion - nimmt zwei Werte vom Stack, subtrahiert den ersten (oberen) Wert
  *         vom zweiten und legt das Ergebnis wieder auf dem Stack ab.
  * @return  0 Wenn Erfolgreich; -1 Wenn Fehler.
  */
void subtrahieren(void){
	if(!containsTwo()){
			error_code = NEEDSTWO;
			printErrorMessag();
		return;
	}

	if(top()> 0 && sec() > 0){
		if(INT32_MIN + sec() < top())
		{
		error_code = INTOVERFLOW;
		printErrorMessag();
		}
	}
	else if(top() < 0 &&  sec() < 0)
	{
		if(INT32_MIN - top() < sec())
		{
		error_code = INTOVERFLOW;
		printErrorMessag();
		}
	}
	int num1 = pop();
	int num2 = pop();
		
	push(num2 - num1);
	print_Stack(p());
	
}
