/*
 * Modul zur einfachen Zeitmessung GS WS 2016
 * Franz Korf
 * file timerInt.h
 */
 
#ifndef _TIMERINT_H
#define _TIMERINT_H

#include <stdint.h>

/**
 * @brief  Diese Funktion initialisiert das Timer-Modul fuer Int Behandlung
 *         Das Modul verwendet den Timer TIM2
 * @param  None
 * @retval None
 */
void initTimerInt(void);

void maskTimerInt(void);
void unmaskTimerInt(void);
void updatePreScalerReloadRegNow(uint16_t psc, uint32_t reloadVal);

#endif
// EOF
