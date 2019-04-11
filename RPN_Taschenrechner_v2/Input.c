/**
  ******************************************************************************
  * @file    	Input.c
  * @author  	Faissal Farid, Ehsan Sajadi
  * @version V1.0
  * @date    27.03.2019
  ******************************************************************************
  */

#include "Input.h"

int zahl =0;
int inputZ = 0;


int getInput(void){
	return Get_Touch_Pad_Input(); 
}

int reactToInput(int wert){
		int _ret = 0;
	  int _ret2 = 0;
	if (ASCII0 <= wert && wert <= ASCII9)	{
		inputZ = 1;
		wert -= ASCII0;
		
		if((zahl <= (INT32_MAX - wert)/10)){
	   	zahl = zahl * 10 + wert;
			print_Input_zeile(zahl);
			return 0;
		}
		else{
		 error_code = INTOVERFLOW;
		 return -1;
		}
	}

	errorZeile_cls();
	
	switch(wert)
	{	
	
		case '+': _ret =input_check(); _ret2 = addieren() ; break; /*finish*/
		case '-': _ret =input_check();_ret2 =subtrahieren(); break; /*finish*/
		case '*': _ret =input_check();_ret2 =multiplizieren();break; /*finish*/
		case '/': _ret =input_check();_ret2 = dividieren(); break;  /*finish*/
		case 'r': _ret =input_check(); _ret2 =r(); break; /*finish*/
		case 'd': _ret =input_check();_ret2 = d(); break; /*finish*/
		case 'p': print_Stack_zeile(p()); break; /*finish*/
		case 'c': c();TFT_cls(); zahl = 0; break; /*finish*/
		case 'f': _ret =input_check();_ret2 = f(); break;
		case ' ': zahl = -zahl; break;
		case 'e': if(inputZ == 1){	
					push(zahl);
					print_Stack_zeile(zahl);					/*finish*/
					inputZeile_cls();
					zahl =0 ; inputZ = 0; break;				
					}	
	}	
	 if(_ret == -1 || _ret2 ==-1){
	     return -1;
	 }
	 else {
	     return 0;
	 }
}

int input_check(void){
	if(inputZ == 1){
			if(push(zahl) ==  -1){
				return  -1;
			}
		print_Stack_zeile(zahl);
		inputZeile_cls();
		zahl =0 ; inputZ = 0;
		return 0;
	}
	return 0;
}


int p(void){
	if(get_sp() == 0){
		error_code = STACKEMPTY;
		return -1;
	}
		int value;
		if(pop(&value) == -1){
			return -1;
		}
		push(value);
		return value;
	
}

int d(void){
	if(get_sp() == 0){
		error_code = STACKEMPTY;
		return -1;
	}
	
	int value;
	if(pop(&value) == -1){
			return -1;
		}
		push(value);
		push(value);
		return 0;
}

int r(void){
	if(get_sp() < 1){
		error_code = NEEDSTWO;
		return -1;
	}
		int erste ;
		int zweite;

		if(pop(&erste) == -1 || pop(&zweite) == -1){
			return -1;
		}
	
	push(erste);
	push(zweite);
	int a = p();
	print_Stack_zeile(a);
	return 0;
}

int f(void){
	stackZeile_cls();
	if(get_sp() == 0){
		error_code = STACKEMPTY;
		return -1;
	}
	for(int i = 0 ;i<get_sp();i++){
		int a;
		get_elm(i,&a);
		print_stack_f(a);
	}
	return 0;
}

void make_Lines(void){
	int ft = 2;	
	int t_x	= 1;
	int t_y = 1;
	int column = 2;
	int lines = 4;
	
	TFT_set_window( ft, t_x, t_y, column,lines); 
	TFT_cls();
	
	TFT_set_font_color(RED);

	TFT_putc('E');
	TFT_putc(':');

	TFT_set_font_color(YELLOW);
	
	TFT_putc('S');
	TFT_putc(':');
	
	TFT_set_font_color(GREEN);
  TFT_putc(' '); // dritte Zeile
	TFT_putc(' '); // dritte zeile
	TFT_putc('I');
	TFT_putc(':');
}
