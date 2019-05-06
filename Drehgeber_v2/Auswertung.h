
#ifndef _Auswertung_H
#define _Auswertung_H

#include <stdint.h>
#include <stdio.h>
#include "timer.h"

#define MAX_PULSE_COUNT 1200
#define WINKEL_360_GRAD 360
#define MODEL_CPR 3 


int8_t berechne_Winkel(int16_t counter, int32_t* winkel, int8_t* nachKomma); 

void berechne_Winkelgeschwindigkeit(int16_t winkel, int16_t *geschwindigkeit); 




#endif
