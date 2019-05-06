/**
  ******************************************************************************
  * @file    	input.c
  * @author  	Faissal Farid, Ehsan Sajadi ; Isam Karrar , Martin Sazgar
  * @version V1.0
  * @date    27.03.2019
  ******************************************************************************
  */
  

#include "input.h"


bool givePinA(void)
{
	bool gpio_Pin0_pressed = ( IDR_MASK_PIN_0 != (GPIOE -> IDR & IDR_MASK_PIN_0) );
	return gpio_Pin0_pressed;
}

bool givePinB(void)
{
	bool gpioe_Pin1_pressed = IDR_MASK_PIN_1 != (GPIOE -> IDR & IDR_MASK_PIN_1);
  return gpioe_Pin1_pressed;
}


int8_t signalLesen (uint8_t *dg_state, bool* s6, bool* s7)
{
	
	*s6 = pin6_Pressed();
	*s7 = pin7_Pressed();
	
	bool A = givePinA();
	bool B = givePinB();
	
	if ( !A && !B )          // (A == 0 && B == 0)
	{
		*dg_state = 0 ;        // Phase a
	}
  else if ( !A && B )           // (A == 0 && B == 1 ) 
	{
		*dg_state = 1 ;        // Phase b
	}
  else if ( A && !B )           // ( A == 1 && B == 0)
	{
		*dg_state = 2;         // Phase c
	}
  else if ( A && B )            // ( A == 1 && B == 1 )
	{
		*dg_state = 3 ;        // Phase d
	}
	
	return 0;
}

bool pin6_Pressed(void)
{
	return (IDR_MASK_PIN_6 != (GPIOE->IDR & IDR_MASK_PIN_6));
}

bool pin7_Pressed(void)
{
	return (IDR_MASK_PIN_7 != (GPIOE->IDR & IDR_MASK_PIN_7));
}





//int8_t signalLesen (void);
