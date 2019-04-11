/**
  ******************************************************************************
  * @file    	Calc.c
  * @author  	Faissal Farid, Ehsan Sajadi
  * @version  V2.0
  * @date     04.04.2019
  ******************************************************************************
  */
	
#include "Calc.h"
#include "Input.h"

int multiplizieren(void){
		//genug elemente vorhanden test
		if(get_sp() < 2){
			error_code = NEEDSTWO;
			return -1;
		}
		int num1;
		int num2;
		//werte lesen
		if (pop(&num1)== -1 || pop(&num2) == -1){
			return -1;
		}
		
		//Overflow test
		if(num1 > INT32_MAX/num2){
			error_code = INTOVERFLOW;
			return -1;
		}
		//underflow test
		if(num1 < INT32_MIN/num2){
			error_code = INTUNDERFLOW;
			return -1;
		}
		push(num2 * num1);
		print_Stack_zeile(p());
		return 0;
		
}

int dividieren(void){
	//genug elemente vorhanden test
		if(get_sp() < 2){
			error_code = NEEDSTWO;
			return -1;
		}
		int num1;
		int num2;
		
		if (pop(&num1)== -1 || pop(&num2) == -1){
			return -1;
		}
		
		//Nenner darf nicht 0 sein
		if(num1 == 0){
			error_code = NOTDIV0;
			return -1;
	  }
		push(num2 / num1);
		print_Stack_zeile(p());	
		return 0;
}
int addieren(void){
		//genug elemente vorhanden test
		if(get_sp() < 2){
			error_code = NEEDSTWO;
			return -1;
		}
		//werte lesen
		int num1 ;
		int num2 ;
		
		if (pop(&num1)== -1 || pop(&num2) == -1){
			return -1;
		}		
		//Overflow & Underflow test
		if(num1> 0 && num2 > 0){
			if(num1 >INT32_MAX -num2){
				error_code = INTOVERFLOW;
				return -1;
				}
		}else if(num2 < 0 &&  num1 < 0){
			if(INT32_MIN - num1 > num2){
				error_code = INTUNDERFLOW;
				return -1;
				}
		}
		push(num2 + num1);
		print_Stack_zeile(p());
		return 0;
}

int subtrahieren(void){
		//genug elemente vorhanden test
		if(get_sp() <	2){
			error_code = NEEDSTWO;
			return -1;
		}
		//werte lesen
		int num1;
		int num2;
		
		if (pop(&num1)== -1 || pop(&num2) == -1){
			return -1;
		}			
		
		//Overflow & Underflow test
		if(num1> 0 && num2 > 0){
				if(num1 >INT32_MAX -num2){
					error_code = INTOVERFLOW;
					return -1;
					}
		}else if(num2 < 0 &&  num1 < 0){
				if(INT32_MIN - num1 > num2)	{
					error_code = INTUNDERFLOW;
					return -1;
				}
		}
		
	push(num2 - num1);
	print_Stack_zeile(p());
		return 0;
}
