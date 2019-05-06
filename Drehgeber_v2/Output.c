/**
  ******************************************************************************
  * @file    	output.c
  * @author  	Faissal Farid, Ehsan Sajadi ; Isam Karrar , Martin Sazgar
  * @version V1.0
  * @date    27.03.2019
  ******************************************************************************
  */
  

#include "output.h"
#include "Input.h"
#include "timer.h"


char str_nachKomma [2];

char str_ouput_winkel[5];
size_t sizeouput;

char str_ouput_GS[5];

static 	uint32_t newtime;
static uint32_t timeStamp;

char buffer[12];
void init_display(void)
	

{
	TFT_set_window(FONT, INPUTXI, INPUTYI, WIDTHI, ROWSI);
	TFT_cls();
	TFT_puts("Drehgeschwindigkeit:       Grad/s");
	TFT_puts("                    Winkel:       Grad");
	
	TFT_gotoxy(1,4);
	TFT_puts("S7: Counter Reset\n");
	TFT_gotoxy(1,5);
	TFT_puts("S6: Error Reset\n");
	TFT_cursor_off();
	
	
	TFT_set_window( FONT, INPUTX, INPUTYI, WIDTH, ROWS);
	TFT_set_font_color(3);
}



void LEDs_Richtung(uint8_t dir) //(richtung)
{
	if(dir == LEFT)
	{
		GPIOG->BSRRL = MASK_PIN_7;
		GPIOG->BSRRH = MASK_PIN_6;
	}
	else if(dir == RIGHT)
	{
		GPIOG->BSRRL = MASK_PIN_6;
		GPIOG->BSRRH = MASK_PIN_7;
	}
}

void counter_LED_8_15(int16_t counter)
{
	GPIOG->BSRRH = MASK_PIN_8_15; // LEDs off
	GPIOG->BSRRL = counter << 8; 	// LEDs on
}






void gibAus (int16_t winkel, int16_t geschwindigkeit, uint8_t nachKomma)
{
	
	
  myItoa(winkel, 5, str_ouput_winkel);
	myItoa(geschwindigkeit,5, str_ouput_GS);
	myItoa(nachKomma,2, str_nachKomma);
	
	
	/*------------------------!!! EHSAN Hier aendern !!! ------------*/
	/* die Ausgabe an die richtige Stelle packen. mit gotoxy */
	newtime = getTimeStamp();								
	if((newtime-timeStamp )> 100000){ //ms
	TFT_cls();
	TFT_gotoxy(1,1);
	TFT_puts(str_ouput_GS);
	TFT_gotoxy(1,2);
	TFT_puts(str_ouput_winkel);
	TFT_putc(',');
	TFT_puts(str_nachKomma);
		timeStamp = newtime;
	}
	/*--------------------------------------------------------------*/
	
	
}







void myItoa(int16_t zahl,int16_t length, char* str)
{	
	sizeouput = snprintf(str,length,"%d",zahl);
}




void zaehle_int_laenge (int16_t zahl, int8_t* int_laenge)
{
	
	if(zahl == 0) //sollte die eingabe eine null oder ein leerzeichen sein.
	{   
		*int_laenge = *int_laenge + 1;
	}
	while(zahl!=0)
	{
		zahl /= 10;
		*int_laenge = *int_laenge + 1;
	}
}




void leereString (char* string , int8_t str_laenge)
{
	
	for (int8_t i = 0; i < str_laenge; i++)
	{
		string[i] = NUL;
	}
	
}









