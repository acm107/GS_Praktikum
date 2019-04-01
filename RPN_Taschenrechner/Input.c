/**
  ******************************************************************************
  * @file    	Input.c
  * @author  	Faissal Farid, Ehsan Sajadi
  * @version V1.0
  * @date    29.03.2019
  ******************************************************************************
  */
	
#include <stdbool.h>
#include "keypad.h"
#include "Stack.h"
#include "Calc.h"
#include "Input.h"
#include "tft.h"
#include <stdlib.h> //atoi()
#include "Output.h"
#include <stdint.h>
#include "math.h"
#include "tft.h"




#define ASCII0 48 // Konstante für den Beginn(0) der Zahlen in ASCII
#define ASCII9 57 // Konstante für das Ende(9) der Zahlen in ASCII
	
	int zahl = 0;

int getInput(void){
	return Get_Touch_Pad_Input(); 
}

void make_Lines(void)
{

	int ft = 2;	
	int t_x	= 1;
	int t_y = 1;
	int column = 2;
	int lines = 4;
	
	TFT_set_window( ft, t_x, t_y, column,lines); 
	TFT_cls();
	TFT_putc(' ');
	TFT_set_font_color(RED);

	TFT_putc('E');
	TFT_putc(':');

	TFT_set_font_color(YELLOW);
	
	TFT_putc('S');
	TFT_putc(':');
	
	TFT_set_font_color(GREEN);

	TFT_putc(' ');
	TFT_putc('I');
	TFT_putc(':');
	
}


// zahl 0 func 1 -1 fehler
void reactToInput(int wert)
{
	if (ASCII0 <= wert && wert <= ASCII9)	{
		wert -= ASCII0;
		zahl = zahl * 10 + wert;
		print_Input(zahl);
		return;
	}
	
	switch(wert)
	{
		case '+': addieren(); break; /*finish*/
		case '-': subtrahieren(); break; /*finish*/
	  case '*': multiplizieren();break; /*finish*/
		case '/': dividieren(); break;  /*finish*/
		case 'r': r(); break; /*finish*/
		case 'd': d(pop()); break; /*finish*/
		case 'p': print_Stack(p()); break; /*finish*/
		case 'c': c();TFT_cls(); zahl = 0; break; /*finish*/
		case 'f': f(); break;
		case ' ': push(zahl);
							print_Stack(zahl);					/*finish*/
							input_cls();
							zahl = 0; break;	
	}	
}




