#ifdef SIMULATION
/*----------------------------------------------------------------------------
 * Name:    Retarget.c
 * Purpose: 'Retarget' layer for target-dependent low level functions
 * Note(s):
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

#include <stdio.h>
#include <rt_misc.h>

//#pragma import(__use_no_semihosting_swi)


extern int  SER_PutChar(int c);                               /* see Serial.c */
extern int  SER_GetChar(void);                                /* see Serial.c */


struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;
FILE __stderr;


int fputc(int c, FILE *f) {
  if (c == '\n')  {
    SER_PutChar('\r');
  }
  return (SER_PutChar(c));
}


int fgetc(FILE *f) {
  return (SER_PutChar(SER_GetChar()));
}


int ferror(FILE *f) {
  /* Your implementation of ferror */
  return EOF;
}


void _ttywrch(int c) {
  SER_PutChar(c);
}


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
