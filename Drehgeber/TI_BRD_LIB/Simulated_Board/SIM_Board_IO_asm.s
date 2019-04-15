;*******************************************************************************
;* File Name          : SIM_Board_IO.s
;* Author             : Tobias Jaehnichen
;* Version            : V1.0
;* Date               : 21.03.2017
;* Description        : Definition of memory-adresses for use of GPIO and ADC
;					  : of the Simulated-Board in assembler projects
;
;  27.03.2017         : Silke Behn, timer Einstellungen ergaenzt
;*******************************************************************************

    PRESERVE8

    IMPORT TFT_cursor_off
    IMPORT TFT_cls	

	GLOBAL GPIO_G_SET	[WEAK]
	GLOBAL GPIO_G_CLR	[WEAK]
	GLOBAL GPIO_G_PIN	[WEAK]
	GLOBAL GPIO_E_PIN	[WEAK]
	GLOBAL ADC3_DR		[WEAK]
	GLOBAL ADC3_CH7_DMA_Config [WEAK]
	GLOBAL timer	    [WEAK]

PERIPH_BASE     equ      0x40000000
APB2PERIPH_BASE equ      (PERIPH_BASE + 0x00010000)

RCC_BASE        equ      0x40021000
APB1ENR         equ      0x1c
RCC_APB1Periph_TIM4 equ  0x04
	
	
;blaue LEDs: output
GPIOG_BASE      equ      (APB2PERIPH_BASE + 0x2000)
GPIO_G_SET		equ      GPIOG_BASE + 0x10
GPIO_G_CLR		equ      GPIOG_BASE + 0x12
GPIO_G_PIN		equ      GPIOG_BASE + 0x08

;rote LEDs / Taster: input
GPIOE_BASE      equ      (APB2PERIPH_BASE + 0x1800)
GPIO_E_PIN      equ      GPIOE_BASE + 0x08
	
;ADC Register, Because there is no ADC3 on the STM32f10x we map ADC3_DR to ADC1_DR
ADC1_BASE       equ      (APB2PERIPH_BASE + 0x2400)
ADC1_DR			equ		 ADC1_BASE + 0x4C 

ADC3_BASE       equ      0x94000000
ADC3_DR         equ      ADC3_BASE + 0x4C ; Eigenen Speicher festlegen 0x9.....

;Timer
timer4_base     equ      0x40000800
TIMx_CR1        equ      0x00
TIMx_CR2        equ      0x04
TIMx_DIER       equ      0x0C
TIMx_SR         equ      0x10
TIMx_EGR        equ      0x14
TIMx_CNT        equ      0x24
TIMx_PSC        equ      0x28
TIMx_ARR        equ      0x2C
timer           equ      timer4_base+TIMx_CNT	




	AREA 		MyCode, CODE, readonly, align = 2

ADC3_CH7_DMA_Config PROC
	BX LR
	ENDP



        
;
; Unterprogramm zum Initialisieren der Hardware
; LCD: Loeschen und Ausschalten des Cursors
; TIMER4: Starten, Kontinuierliches Zaehlen mit einer Frequenz von 100kHz
;

        GLOBAL initHW
initHW  proc
        push   {lr}


;
; Init Timer7
;
        ldr    r0,=RCC_BASE
        ldr    r1,[r0,#APB1ENR]
        orr    r1,#RCC_APB1Periph_TIM4
        str    r1,[r0,#APB1ENR]

        ldr    r0,=timer4_base
		ldr    r1,=72000000/100000 - 1    ; 100 kHz //  1 Tick = 10 us 
        str    r1,[r0,#TIMx_PSC]
        ldr    r1,=0xffff
        str    r1,[r0,#TIMx_ARR]
        ldr    r1,=1
        str    r1,[r0,#TIMx_EGR]
        ldr    r1,=1
        str    r1,[r0,#TIMx_CR1]


;
;  Init LCD
;
        bl     TFT_cursor_off
        bl     TFT_cls

        pop    {pc}
        endp
	
	ALIGN
	
	END
