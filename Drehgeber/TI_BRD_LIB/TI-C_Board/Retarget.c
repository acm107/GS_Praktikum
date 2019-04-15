/*----------------------------------------------------------------------------
 * Name:    Retarget.c
 * Purpose: 'Retarget' layer for target-dependent low level functions
 * Note(s):  	Alfred Lohmann
 *        	  HAW-Hamburg
 *          	Labor für technische Informatik
 *          	Berliner Tor  7
 *          	D-20099 Hamburg
 * 						version V1.0
 *         		adapted to the HAW TI-Bord
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2012 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/
#ifndef SIMULATION

#include <stdio.h>
#include <rt_misc.h>
#include "TI_Lib.h"

//#pragma import(__use_no_semihosting_swi)
extern int USART1_GetKey (void);
extern int USART1_SendChar (int c);


struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;


/**
  * @brief  Outputs a character to USART1
  * @param  c .. charater to output
  *         *f . not checked in this implementation
  * @retval error .. not used
  */
int fputc(int c, FILE *f) {
  int err;
 
	if (c == '\n')  {
    do{
			err = USART1_SendChar('\r');
		}while (err != 0);
  }
  
  do{
    err = USART1_SendChar(c);
  }while (err != 0);
    
  return (err);
}


/**
  * @brief  Reads one character from USART1
  * @param  file .. not used in this implementation
  * @retval character read
  */
int fgetc(FILE *f) {
  int ch;
  
  do{
    ch = USART1_GetKey();
  }while (ch == (-1));
  
  if( ch == '\r' ){
      ch = '\n';
  }
  
  fputc(ch, &__stdout);
	
  return (ch);
}


/**
  * @brief  Outputs to ferror
  * @param  file .. not implemented
  * @retval EOF .. 
  */
int ferror(FILE *f) {
  /* Your implementation of ferror */
  return EOF;
}


/**
  * @brief  Outputs a character to USART1
  * @param  c .. charater to output
  * @retval none
  */
void _ttywrch(int c) {
   int err;
  
  do{
    err = USART1_SendChar(c);
  }while (err != 0);
}


/**
  * @brief  Action when main() returns
  * @param  return code .. not used
  * @retval none
  */
void _sys_exit(int return_code) {
label:  goto label;  /* endless loop */
}


/**
  * @brief  retrieves the command line used to invoke the current application from the environment that called the application.
	* This function is needed b/c a main function in assembler would get the arguments for the command line, which by default provides the debugger.
	* If the program should run w/o debugger we have to implement this function without semihosting_swi functionality.
	*
	* @param  cmd: is a pointer to a buffer that can be used to store the command line. It is not required that the command line is stored in cmd.
	*	@param	len: is the length of the buffer.
  * @retval Nullpointer so no command line is passed to main()
  */
char *_sys_command_string(char *cmd, int len){
    return 0;
}

#endif
