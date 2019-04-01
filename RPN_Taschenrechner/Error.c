/**
  ******************************************************************************
  * @file    	Error.c
  * @author  	Faissal Farid, Ehsan Sajadi
  * @version V1.0
  * @date    30.03.2019
  ******************************************************************************
  */

#include "Error.h"
#include "tft.h"
#include "string.h"
#include <stdbool.h>

// Parameter für die Displayausgabe fuer den Error Code
#define FONTE			 2
#define	ERRORX		 4
#define	ERRORY		 1
#define	WIDTHE 		35  //groesse
#define	ROWSE			 1  //line

static char messag[35]; 
int error_code = 0;
int ERROR_ON = 0;

void setMessag(void){
	switch(error_code)
		{
		case(0): strcpy(messag, " "); break;
		case(STACKFULL):  strcpy(messag, "1000 STACk IST FULL"); break;
		case(STACKEMPTY): strcpy(messag, "1001 STACk IST LEER "); break;
		case(NEEDSTWO):   strcpy(messag, "1002 NICHT GENUG ZAHL VORHANDEN "); break;
		case(INTOVERFLOW): strcpy(messag, "1003 ZAHL UEBERSCHREIEN "); break;
		case(NOTDIV0):    strcpy(messag, "1004 UNMOEGLIG");break;
		case(INTUNDERFLOW): strcpy(messag, "1003 ZAHL UEBERSCHREIEN ");break;
		case(FAIL): strcpy(messag, "FAIL"); break;
	}
}

void printErrorMessag(void){
	setMessag();	
	int index = 0;	
	
	TFT_set_window( FONTE, ERRORX, ERRORY, WIDTHE, ROWSE); 
	TFT_cls();
	
	TFT_set_font_color(3);
	do{
		TFT_putc(messag[index]);
		index++;
	}while(messag[index] != 0);
}

void errorZeile_cls(){
	TFT_set_window( FONTE, ERRORX, ERRORY, WIDTHE, ROWSE); 
	TFT_cls();
}
