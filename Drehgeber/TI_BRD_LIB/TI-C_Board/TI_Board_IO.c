/**
  ******************************************************************************
  * @file    	TI_Board_IO.c 
  * @author  	Alfred Lohmann
  *        	  HAW-Hamburg
  *          	Labor für technische Informatik
  *          	Berliner Tor  7
  *          	D-20099 Hamburg
  * @version V1.0
  * @date    23.05.2013
  * @brief   Function to initialize the TI-Board
  *******************************************************************
  */


#include "TI_Lib.h"
#include "TI_Board_IO.h"


/**
  * @brief  Initializes the timer tick to 1 ms
  * @param  none
  * @retval none
  */
void Init_System_Clock(void){
   /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f4xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f4xx.c file
     */
	SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
    while (1);                                  /* Capture error              */
  }
  
  return;
}


/**
  * @brief  Initializes the PORT G 0..15 as output
  *         and PORT E 0..7 as input
  * @param  none
  * @retval none
  */
void Init_IO(void){

  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* Enable enable the trace port*/	
  DBGMCU->CR=0x20;
	
  /* GPIOG Periph clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);     // Port A is my restart knob
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);     // Port E is our digital input bit 0-7
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);     // Port G is our digital output bit 0-15

  /* Configure input lines             */
  /* even beeing input configure OType */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  
  /* Configure PGx in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
  
//    /* Configure PA9 and P10 in output pushpull mode */
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
//   GPIO_Init(GPIOA, &GPIO_InitStructure);

  return;
}


/**
  * @brief  Initializes SPI2 for IO to touch screen
  * @param  none
  * @retval none
  */
void Init_SPI(void){
	int j;
	
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN ;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	//PB12 as SPI2_NSS
	GPIOB->MODER   = (GPIOB->MODER   & ~(3u << (12 * 2)))      | (GPIO_Mode_OUT     << (12 * 2));
	GPIOB->OSPEEDR = (GPIOB->OSPEEDR & ~(3u << (12 * 2)))      | (GPIO_Speed_50MHz << (12 * 2));
	GPIOB->OTYPER  = (GPIOB->OTYPER  & ~(1 << (12)))           | (GPIO_OType_PP    << (12));
	GPIOB->PUPDR   = (GPIOB->PUPDR   & ~(3 << (12 * 2)))       | (GPIO_PuPd_UP     << (12 * 2));
	//GPIOB->AFR[1]  = (GPIOB->AFR[1]  & ~(0xf << ((12 - 8)*4))) | (GPIO_AF_SPI2     << ((12 - 8)*4));
	
	
	//PB13 as SPI2_SCK
	GPIOB->MODER   = (GPIOB->MODER   & ~(3u << (13 * 2)))      | (GPIO_Mode_AF     << (13 * 2));
	GPIOB->OSPEEDR = (GPIOB->OSPEEDR & ~(3u << (13 * 2)))      | (GPIO_Speed_50MHz << (13 * 2));
	GPIOB->OTYPER  = (GPIOB->OTYPER  & ~(1 << (13)))           | (GPIO_OType_PP    << (13));
	GPIOB->PUPDR   = (GPIOB->PUPDR   & ~(3 << (13 * 2)))       | (GPIO_PuPd_UP     << (13 * 2));
	GPIOB->AFR[1]  = (GPIOB->AFR[1]  & ~(0xf << ((13 - 8)*4))) | (GPIO_AF_SPI2     << ((13 - 8)*4));
	
	//PB14 as SPI2_MISO
	GPIOB->MODER   = (GPIOB->MODER   & ~(3u << (14 * 2)))      | (GPIO_Mode_AF    << (14 * 2));
	GPIOB->OSPEEDR = (GPIOB->OSPEEDR & ~(3u << (14 * 2)))      | (GPIO_Speed_50MHz << (14 * 2));
	GPIOB->OTYPER  = (GPIOB->OTYPER  & ~(1 << (14)))           | (GPIO_OType_PP    << (14));
	GPIOB->PUPDR   = (GPIOB->PUPDR   & ~(3 << (14 * 2)))       | (GPIO_PuPd_UP     << (14 * 2));
	GPIOB->AFR[1]  = (GPIOB->AFR[1]  & ~(0xf << ((14 - 8)*4))) | (GPIO_AF_SPI2     << ((14 - 8)*4));
	
	//PB15 as SPI2_MOSI
	GPIOB->MODER   = (GPIOB->MODER   & ~(3u << (15 * 2)))      | ((0u+GPIO_Mode_AF)  << (15 * 2));
	GPIOB->OSPEEDR = (GPIOB->OSPEEDR & ~(3u << (15 * 2)))      | ((unsigned)GPIO_Speed_50MHz << (15 * 2));
	GPIOB->OTYPER  = (GPIOB->OTYPER  & ~(1 << (15)))           | (GPIO_OType_PP    << (15));
	GPIOB->PUPDR   = (GPIOB->PUPDR   & ~(3u << (15 * 2)))      | (GPIO_PuPd_UP     << (15 * 2));
	GPIOB->AFR[1]  = (GPIOB->AFR[1]  & ~(0xfu << ((15 - 8)*4)))| (GPIO_AF_SPI2     << ((15 - 8)*4));
	
	GPIOB->BSRRL = (1<<12);
	
		
	SPI2->CR1 = (0 << 15) |  // BIDIMODE: 2-line unidirectional data mode selected
			   (0 << 14) |  // BIDIOE:   --
			   (0 << 13) |  // CRCEN:    CRC calculation disabled
			   (0 << 12) |  // CRCNEXT:  --
			   (0 << 11) |  // DFF:      8-bit data frame format
			   (0 << 10) |  // RXONLY:   Full duplex
			   (0 <<  9) |  // SSM:      Software slave management enabled
			   (0 <<  8) |  // SSI       not used when bit 9 == 0
			   (1 <<  7) |  // LSBFIRST: LSB transmitted first
			   (0 <<  6) |  // SPE:      Peripheral enabled
			   (7 <<  3) |  // BR[0:2]   PCLK PCLK011: f /16111: f /256
			   (0 <<  2) |  // MSTR:     Master configuration
			   (1 <<  1) |  // CPOL:     CK to 1 when idle
			   (1 <<  0);   // CPHA:     The second clock transition is the first data capture edge

	
	SPI2->CR2 = (0 <<  7) |  // TXEIE:    TXE interrupt masked
							(0 <<  6) |  // RXNEIE:   RXNE interrupt masked
							(0 <<  5) |  // ERRIE:    Error interrupt is masked
							(0 <<  4) |  // FRF   		SPI Motorola mode
							(1 <<  2) |  // SSOE:     SS output is enabled
							(0 <<  1) |  // TXDMAEN:  Tx buffer DMA disabled
							(0 <<  0);   // RXDMAEN:  Rx buffer DMA disabled
							

	SPI2->CR1 = (0 << 15) |  // BIDIMODE: 2-line unidirectional data mode selected
							(0 << 14) |  // BIDIOE:   --
							(0 << 13) |  // CRCEN:    CRC calculation disabled
							(0 << 12) |  // CRCNEXT:  --
							(0 << 11) |  // DFF:      8-bit data frame format
							(0 << 10) |  // RXONLY:   Full duplex
							(0 <<  9) |  // SSM:      Software slave management disabled
							(0 <<  8) |  // SSI       not used when bit 9 == 0
							(1 <<  7) |  // LSBFIRST: LSB transmitted first
							(1 <<  6) |  // SPE:      Peripheral enabled
							(7 <<  3) |  // BR[0:2]   PCLK PCLK011: f /16111: f /256
							(1 <<  2) |  // MSTR:     Master configuration
							(1 <<  1) |  // CPOL:     CK to 1 when idle
							(1 <<  0);   // CPHA:     The second clock transition is the first data capture edge
	
	// just some busy waiting to get SPI stable
	for( j=0; j<2000000; j++ ){
	}
	
	return;
}



