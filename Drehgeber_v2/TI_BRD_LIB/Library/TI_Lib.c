/**
  ******************************************************************************
  * @file    TI_Board.c 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    30-August-2012
  * @brief   TI Board Utility
	* Note(s):  Alfred Lohmann
	*        	  HAW-Hamburg
	*          	Labor für technische Informatik
	*          	Berliner Tor  7
	*          	D-20099 Hamburg
	* 					version V1.0
	*         	adapted to the HAW TI-Bord
	* Date:   	18.07.2013
	* 10.10.2016	Nils Schoenherr: clean-up + new structure + SysTickHandler
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 HAW-Hamburg</center></h2>
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
/* defines -------------------------------------------------------------------*/
#include "TI_Lib.h"

/* Private variables ---------------------------------------------------------*/
static __IO uint32_t TimingDelay;
static __IO uint32_t uptime = 0;

void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
	uptime++;
}

void SysTick_Handler(void)
{
  TimingDelay_Decrement();
}

uint32_t get_uptime(void){
		return uptime;
}


void Init_TI_Board(void){
  Init_System_Clock();
  Init_IO();
	Init_SPI();
#ifndef SIMULATION
  USART1_Buffer_Init();                          /* init RX / TX buffers             */
  USART1_Init();
#else
	SER_Init ();
#endif
  TFT_Init();
  Delay(1); 
}

