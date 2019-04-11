/**
  ******************************************************************************
  * @file    TI_Lib.h 
  * @author  Alfred Lohmann
  * @version V1.0.1
  * @date    30-August-2012
  * @brief   Header TI-Board Library
	* 10.10.2016	Nils Schoenherr: DoxyGen + only dependend on TI_memory_map
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TI_LIB_H
#define __TI_LIB_H

/* Includes ------------------------------------------------------------------*/
#include "TI_memory_map.h"
#ifdef SIMULATION
#include "SIM_Board_IO.h"
#include "serial.h"
#else
#include "usart.h"
#include "TI_Board_IO.h"
#endif

#include "tft.h"

/* Exported functions ------------------------------------------------------- */

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void);

  /**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in 1 ms.
  * @retval None
  */
void Delay(__IO uint32_t nTime);

/**
  * @brief  Getter of system_uptime
  * @param  None
  * @retval system_uptime
  */
uint32_t get_uptime(void);

/**
  * @brief  Initializes the TI-Board
  * @param  None
  * @retval None
  */
void Init_TI_Board(void);   // initialize the TI-Board IO

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void);

/*  not used anywhere?! 
void Buffer_Init (void);    // Initialize Transmit- Receivebuffer
int SendChar (int c);       // Transmit one character
int GetKey (void);          // Receive one character
*/

#endif /* __TI_LIB_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
