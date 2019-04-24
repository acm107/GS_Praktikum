/**
  ******************************************************************************
  * @file    	output.h
  * @author  	Faissal Farid, Ehsan Sajadi
  * @version V1.0
  * @date    27.03.2019
  ******************************************************************************
  */

#include "tft.h"

#define FONT 		 2  //Paramenter für die Wertefenster
#define	INPUTX		 21
#define	INPUTY2		 7
#define	WIDTH 		 6
#define	ROWS	     2

#define	INPUTXI	 	 1 //Parameter für die Display Initzialisierung
#define	INPUTYI		 6
#define	WIDTHI 		 40
#define	ROWSI		 7

#ifndef _OUTPUT_H
#define _OUTPUT_H

void init_display(void);
void print_speed(void);

void turnOnLED(void);



#endif