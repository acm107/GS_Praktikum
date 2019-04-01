;*******************************************************************************
;* File Name          : TI_Board_IO.s
;* Author             : Tobias Jaehnichen
;* Version            : V1.0
;* Date               : 21.03.2017
;* Description        : Definition of memory-adresses for use of GPIO and ADC
;					  : of the TI-C-Board in assembler projects
;  27.03.2017         : Silke Behn, timer Einstellungen ergaenzt
;
;*******************************************************************************
    PRESERVE8

    IMPORT TFT_cursor_off
    IMPORT TFT_cls	


	GLOBAL GPIO_G_SET	[WEAK]
	GLOBAL GPIO_G_CLR	[WEAK]
	GLOBAL GPIO_G_PIN	[WEAK]
	GLOBAL GPIO_E_PIN	[WEAK]
	GLOBAL ADC3_DR		[WEAK]
	GLOBAL timer	    [WEAK]

    
PERIPH_BASE     equ      0x40000000
APB2PERIPH_BASE equ      (PERIPH_BASE + 0x00010000)
AHB1PERIPH_BASE equ      (PERIPH_BASE + 0x00020000)

RCC_BASE            equ 0x40023800
APB1ENR             equ 0x40
RCC_APB1Periph_TIM7 equ 0x20

	
;blaue LEDs: output
GPIOG_BASE      equ      (AHB1PERIPH_BASE + 0x1800)
GPIO_G_SET		equ      GPIOG_BASE + 0x18
GPIO_G_CLR		equ      GPIOG_BASE + 0x1A
GPIO_G_PIN		equ      GPIOG_BASE + 0x10

;rote LEDs / Taster: input
GPIOE_BASE      equ      (AHB1PERIPH_BASE + 0x1000)
GPIO_E_PIN      equ      GPIOE_BASE + 0x10
	
	
;
ADC3_BASE       equ      (APB2PERIPH_BASE + 0x2200)
ADC3_DR         equ      ADC3_BASE + 0x4C
	
; Timer	
timer7_base     equ      0x40001400
TIMx_CR1        equ      0x00
TIMx_CR2        equ      0x04
TIMx_DIER       equ      0x0C
TIMx_SR         equ      0x10
TIMx_EGR        equ      0x14
TIMx_CNT        equ      0x24
TIMx_PSC        equ      0x28
TIMx_ARR        equ      0x2C
	
timer           equ      timer7_base+TIMx_CNT	
	
	    AREA mycode,CODE
;
; Unterprogramm zum Initialisieren der Hardware
; LCD: Loeschen und Ausschalten des Cursors
; TIMER2: Starten, Kontinuierliches Zaehlen mit einer Frequenz von 100kHz
; Ueberlauf nach 715 Minuten
;

        GLOBAL initHW


initHW PROC
        push   {lr}


;
; Init Timer7
;
        ldr    r0,=RCC_BASE
        ldr    r1,[r0,#APB1ENR]
        orr    r1,#RCC_APB1Periph_TIM7
        str    r1,[r0,#APB1ENR]

        ldr    r0,=timer7_base
        ldr    r1,=168000000/2/100000 - 1
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
		
		ENDP

	ALIGN
	
	END
		