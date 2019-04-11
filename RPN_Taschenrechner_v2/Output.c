/**
  ******************************************************************************
  * @file    	Output.c
  * @author  	Faissal Farid, Ehsan Sajadi
  * @version V1.0
  * @date    27.03.2019
  ******************************************************************************
  */

#include "Output.h"


//void print_of_display(int zahl)
//{
//	Display_value(zahl);
//}

void print_Input_zeile(int wert){
	if(ERROR_ON == 1){
		return;
	}
	char inputNumber[20];
	int index = 0;
	TFT_set_font_color(GREEN);
	TFT_set_window( FONTI, INPUTX, INPUTY, WIDTHI, ROWSI); 
	snprintf(inputNumber, 50, "%d", wert);
	TFT_cls();
	do{
		TFT_putc(inputNumber[index]);
		index++;
	}while(inputNumber[index] != 0);
}

void print_Stack_zeile(int wert){
		if(ERROR_ON == 1){
		return;
	}
	char inputNumber[20];
	int index = 0;
	TFT_set_font_color(YELLOW);
	TFT_set_window( FONTS, STACKX, STACKY, WIDTHS, ROWSS); 
	snprintf(inputNumber, 50, "%d", wert);
	TFT_cls();
	do{
		TFT_putc(inputNumber[index]);
		index++;
	}while(inputNumber[index] != 0);
	
}
void inputZeile_cls(){
	TFT_set_window( FONTI, INPUTX, INPUTY, WIDTHI, ROWSI); 
	TFT_cls();
}

void stackZeile_cls(){
	TFT_set_window( FONTS, STACKX, STACKY, WIDTHS, ROWSS);  
	TFT_cls();
}

void print_stack_f(int wert){
int index =0;
	char zahlString[10];
	TFT_set_font_color(YELLOW);
	snprintf(zahlString, 50, "%d", wert);
	
	do{
		TFT_putc(zahlString[index]);
		index++;
	}while(zahlString[index] != 0);
	TFT_putc(',');
	TFT_putc(' ');
}
