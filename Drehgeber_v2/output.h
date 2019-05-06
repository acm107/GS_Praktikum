
#ifndef _OUTPUT_H
#define _OUTPUT_H


#include "tft.h"
#include "stdint.h"

#define FONT 		   2  //Paramenter für die Wertefenster
#define	INPUTX		 21
#define	INPUTY2		 7
#define	WIDTH 		 6
#define	ROWS	     2

#define	INPUTXI	 	 1 //Parameter für die Display Initzialisierung
#define	INPUTYI		 6
#define	WIDTHI 		 40
#define	ROWSI		   7

#define	RIGHT      1 // Richtung der Drehgeber
#define LEFT      2

#define MASK_PIN_8_15		  (0xFFU << 8)
#define MASK_PIN_7   (0x01U << 7)
#define MASK_PIN_6   (0x01U << 6)

#define MINUS 45
#define MAX 10
#define NUL 0

void init_display(void);
void print_speed(void);

void turnOnLED(void);

void LEDs_Richtung(uint8_t);
void counter_LED_8_15(int16_t);





void gibAus(int16_t winkel, int16_t geschwindigkeit, uint8_t nachKomma);


/*
Wandelt eine Integer Zahl in einen String.

@param zahl Diese Zahl wird umgewandelt in einen String.
@param str  In diesem String wird die Zahl gespeichert.
*/
void myItoa (int16_t zahl,int16_t length , char* str);

/*
zählt die Länge einer Integer Zahl.

@param zahl Zahl die gezählt werden soll
@param int_laenge Länge wird hier rein gespeichert
*/
void zaehle_int_laenge (int16_t zahl, int8_t* int_laenge);

/*
Leert einen String. 

@param string Dieser String soll geleert werden.
@paran str_laenge Die Länge des Strings
*/
void leereString (char* string, int8_t str_laenge);

#endif

