/**
  ******************************************************************************
  * @file    	Calc.h
  * @author  	Faissal Farid, Ehsan Sajadi
  * @version V1.0
  * @date    27.03.2019
  ******************************************************************************
  */
	
#ifndef _CALC_H
#define _CALC_H


#endif


/**
  * @brief  Funktion * nimmt zwei Werte vom Stack, multipliziert sie und legt das Ergebnis
	*					wieder auf dem Stack ab.
  * @return  0 Wenn Erfolgreich; -1 Wenn Fehler.
  */
void multiplizieren(void);

/**
  * @brief  Funktion / nimmt zwei Werte vom Stack, teilt den zweiten Wert durch den ersten
	*					(ganzzahlige Division) und legt das Ergebnis wieder auf dem Stack ab.
  * @return  0 Wenn Erfolgreich; -1 Wenn Fehler.
  */
void dividieren(void);

/**
  * @brief  Funktion + nimmt zwei Werte vom Stack, addiert sie und legt das Ergebnis wieder
	*					auf dem Stack ab.
  * @return  0 Wenn Erfolgreich; -1 Wenn Fehler.
  */
void addieren(void);

/**
  * @brief  Funktion - nimmt zwei Werte vom Stack, subtrahiert den ersten (oberen) Wert
  *         vom zweiten und legt das Ergebnis wieder auf dem Stack ab.
  * @return  0 Wenn Erfolgreich; -1 Wenn Fehler.
  */
void subtrahieren(void);
