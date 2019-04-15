#include "Auswertung.h"


int8_t gibWinkel(uint8_t counter, float* winkel)
{
	*winkel = Winkel_pro_Puls * counter;
	return 0;
}

