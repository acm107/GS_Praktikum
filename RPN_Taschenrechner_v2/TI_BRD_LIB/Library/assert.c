/**
  ******************************************************************************
  * @file    	assert.c 
  * @author  	Schoenher, Nils
  * @version  V1.0
  * @date     10.10.2016
  * @brief    All assert related Code from TI-Library
  ******************************************************************************
  */

#include "assert.h"

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
