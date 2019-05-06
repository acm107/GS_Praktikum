/*
 * Implementation des timer Modules.
 *  GS WS 2016
 * Franz Korf
 * file timerInt.c
 */
 
 /*
  * Das System verfuegt über 256 Interrupt Quellen  / Leitungen.
	* Jeder Interrupt Quelle wird ein 8 Bit Wert, der seine Priorität
	* definiert zugeordnet.
	* Dieser Wert ins in zwei Bereiche geteilt.
	*   - Der linke / obrere Bereich definiert group priority
	*   - Der rechte / untere Bereich definiert die subpriority
	* Interrupts mit der selben Group Priority unterbrechen sich
	* sind. Bei unterschiedlichen Group Priorities wird das nested
	* Interrupt Konzept anwendet.
	* Stehen Interrupts mit der selben group priority gleichzeitig
	* an, so definiert die subpriority die Reihenfolge der Abarbeitung.
	* 
	* Für alle Interrupts wird einheitlich definiert, wieviele Bits des
	* 8 Bit Prioritätenwerts für die sub priority genutzt wird. Dies
	* geschieht über die Funktion NVIC_SetPriorityGrouping(x).
	* Ist das Argument x zum Beispiel 2, definieren die beiden hinteren Bits
	* die subpriority. In diesem Fall gibt pro group priority vier sub
	* priorities. 
	* Dies linken sechs Bit werden für die group priority genutzt - somit 
	* gibt es 2^6 = 64 group priorities.
	
	* Vorgehensweise Interrupt Behandlung:
	*  - Lasse den Timer stets durchlaufen
	*  - Nutze URS und UDIS zum Update der Timer Variablen
	*  - Steuere das Ein- und Ausschalten ueber den Interrupt Controller / Maskiere
	*/
 
#include "timerInt.h"
#include "TI_memory_map.h"

#define TIM2_CLOCK      84  /* Mhz */
// 84 Timer Ticks == 1 us

void updatePreScalerReloadRegNow(uint16_t psc, uint32_t reloadVal) {
	 // Update shadow Registers of PreScaler and ReloadReg
	 TIM2->PSC = psc;
   TIM2->ARR = reloadVal;	
	
	 TIM2->EGR  = (TIM2->EGR | TIM_EGR_UG); 
}

void unmaskTimerInt(void) {
   TIM2->SR = TIM2->SR & !TIM_SR_UIF; // Loesche alte noch anstehende Interrupts
	 NVIC_EnableIRQ(TIM2_IRQn);         // Enable in Interrupt Controller - Timer laeuft durch
}

void maskTimerInt(void) {
	 NVIC_DisableIRQ(TIM2_IRQn);      // Diesalbe im Interrupt Controller - Timer laeuft durch
}

void initTimerInt(void) {
	TIM2->SR = 0x00;
    TIM2->DIER = 0x00;
    TIM2->EGR = 0x00;
	 
	  /* Interrupt Controller einstellen */
	  //NVIC_SetPriorityGrouping(2);    // Setup interrupt controller: 4 subpriority for each priority
      //NVIC_SetPriority(TIM2_IRQn, 8); // Setup TIM2 interrupt:  priority = 2, subpriority = 0
      //maskTimerInt();       
	
	  // Stelle Timer ein
      RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; /* Takt fuer Timer 2 einschalten     */
	  TIM2->CR1 = 0;
	  TIM2->CR2 = 0;
	  TIM2->CR1 = (TIM2->CR1 | TIM_CR1_CEN);/* Schalte den Counter des Timers an */
	  TIM2->DIER  = (TIM2->DIER | TIM_DIER_UIE);     //  Enable Timer interrupt, laueft durch      
	  /* Setup for update of PreScaler and ReloadReg via TIM_EGR_UG flag */
	  TIM2->CR1  = TIM2->CR1 & ~TIM_CR1_UDIS; 
	  TIM2->CR1  = TIM2->CR1 | TIM_CR1_URS; // TIM_EGR_UG does not generate an interrupt 
	  updatePreScalerReloadRegNow(84, 1000000);
}
// EOF


