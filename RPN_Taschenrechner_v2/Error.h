/**
  ******************************************************************************
  * @file    	Error.h
  * @author  	Faissal Farid, Ehsan Sajadi
  * @version V1.0
  * @date    04.04.2019
  ******************************************************************************
  */
	
#ifndef	_ERROR_H
#define	_ERROR_H

#endif

#include "tft.h"
#include "string.h"

#define	STACKFULL			1000
#define	STACKEMPTY		1001
#define NEEDSTWO 			1003
#define INTOVERFLOW 	1004
#define NOTDIV0 			1005
#define INTUNDERFLOW 	1006
#define FAIL					-1

// Parameter für die Displayausgabe fuer den Error Code
#define FONTE			 2
#define	ERRORX		 4
#define	ERRORY		 1
#define	WIDTHE 		35  //groesse
#define	ROWSE			 1  //line

extern int error_code;
extern int ERROR_ON ;
/**
* @brief zum !!
*/
void setMessag(void);
/**
* @brief zum print des Errors.
*/
void printErrorMessag(void);
/**
* @brief zum Clear des Errorzeile.
*/
void errorZeile_cls(void);
