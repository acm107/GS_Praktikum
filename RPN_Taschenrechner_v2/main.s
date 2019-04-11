;******************** (C) COPYRIGHT HAW-Hamburg ********************************
;* File Name          : main.s
;* Author             : Alfred Lohmann
;* Author             : Tobias Jaehnichen	
;* Version            : V2.0
;* Date               : 23.04.2017
;* Description        : This is a simple main.
;					  : The output is send to UART 1. Open Serial Window when 
;					  : when debugging. Select UART #1 in Serial Window selection.
;					  :
;					  : Replace this main with yours.
;
;*******************************************************************************

	EXTERN Init_TI_Board		; Initialize the serial line
	EXTERN ADC3_CH7_DMA_Config  ; Initialize the ADC
	;EXTERN	initHW				; Init Timer
	EXTERN	puts				; C output function
	EXTERN	TFT_puts			; TFT output function
	EXTERN  TFT_cls				; TFT clear function
	EXTERN  TFT_gotoxy      	; TFT goto x y function  
	EXTERN  Delay				; Delay (ms) function
	EXTERN GPIO_G_SET			; Set output-LEDs
	EXTERN GPIO_G_CLR			; Clear output-LEDs
	EXTERN GPIO_G_PIN			; Output-LEDs status
	EXTERN GPIO_E_PIN			; Button status
	EXTERN ADC3_DR				; ADC Value (ADC3_CH7_DMA_Config has to be called before)

;********************************************
; Data section, aligned on 4-byte boundery
;********************************************
	
	AREA MyData, DATA, align = 2
	
	GLOBAL text
	
text	DCB	"Hallo TI-Labor!\n\r",0

;********************************************
; Code section, aligned on 8-byte boundery
;********************************************

	AREA |.text|, CODE, READONLY, ALIGN = 3

;--------------------------------------------
; main subroutine
;--------------------------------------------
	EXPORT main [CODE]
	
main	PROC

		BL	Init_TI_Board	; Initialize the serial line to TTY
							; for compatability to out TI-C-Board
		;BL	initHW			; Timer init
		
		LDR	r0,=text
		BL	puts			; call C output method
		
		LDR r0,=text
		BL	TFT_puts		; call TFT output method
		
		
forever	b	forever		; nowhere to retun if main ends		
		ENDP
	
		ALIGN
       
		END