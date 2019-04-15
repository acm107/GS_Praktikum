/**
  ******************************************************************************
  * @file    	input.c
  * @author  	Faissal Farid, Ehsan Sajadi ; Isam Karrar , Martin Sazgar
  * @version V1.0
  * @date    27.03.2019
  ******************************************************************************
  */
  

#include "input.h"

bool A;
bool B;


int8_t signalLesen (uint8_t *dg)
{
	
	givePinA();
	givePinB();
	
	if (!A && !B)   // 00 
	{
		*dg = A_P;
	}
    if (!A && B )   // 01
	{
		*dg = D_P;
	}
    if ( A && !B)   // 10
	{
		*dg = B_P;
	}
    if ( A && B )   // 11 
	{
		*dg = C_P;
	}
	return 0;

}



void givePinA(void)
{
	bool gpioe_Pin_0 = IDR_MASK_PIN_0 != (GPIOE -> IDR & IDR_MASK_PIN_0);
	A = gpioe_Pin_0;   
}

void givePinB(void)
{
    bool gpioe_Pin_1 = IDR_MASK_PIN_1 != (GPIOE -> IDR & IDR_MASK_PIN_1);
    B =  gpioe_Pin_1;
}



//int8_t signalLesen (void);
