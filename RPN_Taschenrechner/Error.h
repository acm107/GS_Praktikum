/**
  ******************************************************************************
  * @file    	Error.h
  * @author  	Faissal Farid, Ehsan Sajadi
  * @version V1.0
  * @date    27.03.2019
  ******************************************************************************
  */

#ifndef	_ERROR_H
#define	_ERROR_H

#endif

#include <stdbool.h>

#define	STACKFULL		1000
#define	STACKEMPTY	1001
#define NEEDSTWO 		1003
#define INTOVERFLOW 1004
#define NOTDIV0 		1005
#define INTUNDERFLOW 1006
#define FAIL				-1
extern int error_code;
extern int ERROR_ON ;

void setMessag(void);
/**
* @brief zum print des Errors.
*/
void printErrorMessag(void);

void errorZeile_cls(void);
