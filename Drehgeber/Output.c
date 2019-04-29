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

#define MASK_PIN_8_15		  (0xFFU << 8)

void init_display(void)
{
	TFT_set_window(FONT, INPUTXI, INPUTYI, WIDTHI, ROWSI);
	TFT_cls();
	TFT_puts("Drehgeschwindigkeit:       Grad/s");
	TFT_puts("             Winkel:       Grad");
	
	TFT_gotoxy(1,4);
	TFT_puts("S7: Counter Reset\n");
	TFT_gotoxy(1,5);
	TFT_puts("S6: Error Reset\n");
	TFT_cursor_off();
	
	
	TFT_set_window( FONT, INPUTX, INPUTYI, WIDTH, ROWS);
	TFT_set_font_color(3);
}


void LEDs_Richtung(//richtung)
{
	if(//richtung == LEFT)
	{
		GPIOG->BSRRL = MASK_PIN_7;
		GPIOG->BSRRH = MASK_PIN_6;
	}
	else if(//richtung == RIGHT)
	{
		GPIOG->BSRRL = MASK_PIN_6;
		GPIOG->BSRRH = MASK_PIN_7;
	}
	else
	{
		GPIOG->BSRRH = MASK_PIN_7;
		GPIOG->BSRRH = MASK_PIN_6;
	}		
}

void counter_LED_8_15(char counter)
{
	GPIOG->BSRRH = MASK_PIN_8_15; // LEDs off
	GPIOG->BSRRL = counter << 8; 	// LEDs on
}


	
}