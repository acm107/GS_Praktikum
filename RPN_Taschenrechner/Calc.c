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
	if(num1 > INT32_MAX/num2){
		error_code = INTOVERFLOW;
		printErrorMessag();
		return;
	}
	if(num1 < INT32_MIN/num2){
		error_code = INTOVERFLOW;
		printErrorMessag();
		return;
	}
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
	int num1 = pop();
	int num2 = pop();
	
	if(num1> 0 && num2 > 0){
		if(num1 >INT32_MAX -num2)
		{
			error_code = INTOVERFLOW;
			printErrorMessag();
			return;
		}
	}else if(num2 < 0 &&  num1 < 0){
		if(INT32_MIN - num1 > num2)
		{
			error_code = INTOVERFLOW;
		printErrorMessag();
			return;
		}
	}
		
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
	int num1 = pop();
	int num2 = pop();
	
	if(num1> 0 && num2 > 0){
		if(num1 >INT32_MAX -num2)
		{
			error_code = INTOVERFLOW;
			printErrorMessag();
			return;
		}
	}else if(num2 < 0 &&  num1 < 0){
		if(INT32_MIN - num1 > num2)
		{
			error_code = INTOVERFLOW;
		printErrorMessag();
			return;
		}
	}
		
	push(num2 - num1);
	print_Stack(p());
	
}
