/*----------------------------------------------------------------------------
 * Name:    	Usart.c
 * Purpose: 	USART usage for STM32
 * Note(s):  	Alfred Lohmann
 *        	  HAW-Hamburg
 *          	Labor für technische Informatik
 *          	Berliner Tor  7
 *          	D-20099 Hamburg
 * 						version V1.0
 *         		adapted to the HAW TI-Borad
 * Date:   		23.05.2013
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2011 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include <stdio.h>
//#include "main.h"
#include "TI_Lib.h"
#include "usart.h"
#include "misc.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"



/* USART Mode Selected */
#define USART_MODE_TRANSMITTER           0x00
#define USART_MODE_RECEIVER              0x01      


/* Definition for USARTx resources ********************************************/
#define USARTxx                           USART1
#define USARTxx_CLK                       RCC_APB2Periph_USART1
#define USARTxx_CLK_INIT                  RCC_APB2PeriphClockCmd
#define USARTxx_IRQn                      USART1_IRQn
#define USARTxx_IRQHandler                USART1_IRQHandler

#define USARTxx_TX_PIN                    GPIO_Pin_9
#define USARTxx_TX_GPIO_PORT              GPIOA                 
#define USARTxx_TX_GPIO_CLK               RCC_AHB1Periph_GPIOA
#define USARTxx_TX_SOURCE                 GPIO_PinSource9
#define USARTxx_TX_AF                     GPIO_AF_USART1

#define USARTxx_RX_PIN                    GPIO_Pin_10       
#define USARTxx_RX_GPIO_PORT              GPIOA              
#define USARTxx_RX_GPIO_CLK               RCC_AHB1Periph_GPIOA
#define USARTxx_RX_SOURCE                 GPIO_PinSource10
#define USARTxx_RX_AF                     GPIO_AF_USART1


/*----------------------------------------------------------------------------
  Notes:
  The length of the receive and transmit buffers must be a power of 2.
  Each buffer has a next_in and a next_out index.
  If next_in = next_out, the buffer is empty.
  (next_in - next_out) % buffer_size = the number of characters in the buffer.
 *----------------------------------------------------------------------------*/
#define TBUF_SIZE   256	     /*** Must be a power of 2 (2,4,8,16,32,64,128,256,512,...) ***/
#define RBUF_SIZE   256      /*** Must be a power of 2 (2,4,8,16,32,64,128,256,512,...) ***/

/*----------------------------------------------------------------------------

 *----------------------------------------------------------------------------*/
#if TBUF_SIZE < 2
#error TBUF_SIZE is too small.  It must be larger than 1.
#elif ((TBUF_SIZE & (TBUF_SIZE-1)) != 0)
#error TBUF_SIZE must be a power of 2.
#endif

#if RBUF_SIZE < 2
#error RBUF_SIZE is too small.  It must be larger than 1.
#elif ((RBUF_SIZE & (RBUF_SIZE-1)) != 0)
#error RBUF_SIZE must be a power of 2.
#endif

/*----------------------------------------------------------------------------

 *----------------------------------------------------------------------------*/
struct buf_st {
  unsigned int in;                        /* Next In Index                    */
  unsigned int out;                       /* Next Out Index                   */
  char buf [RBUF_SIZE];                   /* Buffer                           */
};

static struct buf_st rbuf = { 0, 0, };
#define SIO_RBUFLEN ((unsigned short)(rbuf.in - rbuf.out))

static struct buf_st tbuf = { 0, 0, };
#define SIO_TBUFLEN ((unsigned short)(tbuf.in - tbuf.out))

static unsigned int tx_restart = 1;       /* NZ if TX restart is required     */


/*----------------------------------------------------------------------------
  Initialize UART pins, Baudrate
 *----------------------------------------------------------------------------*/
void USART1_Init (void) {

  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(USARTxx_TX_GPIO_CLK | USARTxx_RX_GPIO_CLK, ENABLE);
  
  /* Enable USART clock */
  USARTxx_CLK_INIT(USARTxx_CLK, ENABLE);
  
  /* Connect USART pins to AF7 */
  GPIO_PinAFConfig(USARTxx_TX_GPIO_PORT, USARTxx_TX_SOURCE, USARTxx_TX_AF);
  GPIO_PinAFConfig(USARTxx_RX_GPIO_PORT, USARTxx_RX_SOURCE, USARTxx_RX_AF);
  
  /* Configure USART Tx and Rx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin = USARTxx_TX_PIN;
  GPIO_Init(USARTxx_TX_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = USARTxx_RX_PIN;
  GPIO_Init(USARTxx_RX_GPIO_PORT, &GPIO_InitStructure);

  /* Enable the USART OverSampling by 8 */
  USART_OverSampling8Cmd(USARTxx, ENABLE);  

  /* USARTx configuration ----------------------------------------------------*/
  /* USARTx configured as follow:
        - BaudRate = 5250000 baud
		   - Maximum BaudRate that can be achieved when using the Oversampling by 8
		     is: (USART APB Clock / 8) 
			 Example: 
			    - (USART3 APB1 Clock / 8) = (42 MHz / 8) = 5250000 baud
			    - (USART1 APB2 Clock / 8) = (84 MHz / 8) = 10500000 baud
		   - Maximum BaudRate that can be achieved when using the Oversampling by 16
		     is: (USART APB Clock / 16) 
			 Example: (USART3 APB1 Clock / 16) = (42 MHz / 16) = 2625000 baud
			 Example: (USART1 APB2 Clock / 16) = (84 MHz / 16) = 5250000 baud
        - Word Length = 8 Bits
        - one Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */ 
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USARTxx, &USART_InitStructure);
  
  /* NVIC configuration */
  /* Configure the Priority Group to 2 bits */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* Enable the USARTx Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USARTxx_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* Enable USART */
  USART_Cmd(USARTxx, ENABLE);
  USART1->CR1 |= USART_SR_RXNE; 

}


/*----------------------------------------------------------------------------
  USART1_IRQHandler
  Handles USART1 global interrupt request.
 *----------------------------------------------------------------------------*/
void USART1_IRQHandler (void) {
  volatile unsigned int IIR;
  struct buf_st *p;

    IIR = USART1->SR;
    if (IIR & USART_SR_RXNE) {            /* read interrupt                   */
      USART1->SR &= ~USART_SR_RXNE;	      /* clear interrupt                  */

      p = &rbuf;

      if (((p->in - p->out) & ~(RBUF_SIZE-1)) == 0) {
        p->buf [p->in & (RBUF_SIZE-1)] = (USART1->DR & 0x1FF);
        p->in++;
      }
    }

    if (IIR & USART_SR_TXE) {
      USART1->SR &= ~USART_SR_TXE;	      /* clear interrupt                    */

      p = &tbuf;

      if (p->in != p->out) {
        USART1->DR = (p->buf [p->out & (TBUF_SIZE-1)] & 0x1FF);
        p->out++;
        tx_restart = 0;
      }
      else {
        tx_restart = 1;
        USART1->CR1 &= ~USART_SR_TXE;     /* disable TX IRQ if nothing to send  */

      }
    }
}

/*------------------------------------------------------------------------------
  USART1_Buffer_Init
  initialize the buffers
 *------------------------------------------------------------------------------*/
void USART1_Buffer_Init (void) {

  tbuf.in = 0;                            /* Clear com buffer indexes           */
  tbuf.out = 0;
  tx_restart = 1;

  rbuf.in = 0;
  rbuf.out = 0;
}

/*------------------------------------------------------------------------------
  SenChar
  transmit a character
 *------------------------------------------------------------------------------*/
int USART1_SendChar (int c) {
  struct buf_st *p = &tbuf;

  if (SIO_TBUFLEN >= TBUF_SIZE)           /* If the buffer is full              */
    return (-1);                          /* return an error value              */
                                                  
  p->buf [p->in & (TBUF_SIZE - 1)] = c;   /* Add data to the transmit buffer.   */
  p->in++;

  if (tx_restart) {                       /* If TX interrupt is disabled        */
    tx_restart = 0;                       /*     enable it                      */
    USART1->CR1 |= USART_SR_TXE;          /* enable TX interrupt                */
  }

  return (0);
}

/*------------------------------------------------------------------------------
  GetKey
  receive a character
 *------------------------------------------------------------------------------*/
int USART1_GetKey (void) {
  struct buf_st *p = &rbuf;

  if (SIO_RBUFLEN == 0)
    return (-1);

  return (p->buf [(p->out++) & (RBUF_SIZE - 1)]);
}



