#include "SIM_Board_IO.h"
#include "stm32f10x.h"

void Init_System_Clock(void){
	SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
    while (1);                                  /* Capture error              */
  }
  
  return;
}

void Init_IO(void){
	// ENABLE GPIOE AND GPIOG CLOCK
	RCC->APB2ENR |= RCC_APB2ENR_IOPEEN | RCC_APB2ENR_IOPGEN;
	
	// MAKE GPIOG AS OUTPUT (G0 as open drain for onewire)
	//GPIOG->CRL = 0x33333333;
	GPIOG->CRH = 0x33333333;
	GPIOG->MODER = 0x5555;
	GPIOG->OTYPER = 0x00000000;
}

void Init_SPI(void){
	int j;
	
	// Enable SPI2-Clock
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN ;
	// Enable GPIOB-Clock
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN ;
	
	// Configure GPIO_Pins for SPI2
	GPIOB->CRH = 0xB4BB4444; // settings for SPI on GPIOB
		
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
