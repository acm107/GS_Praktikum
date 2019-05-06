/*
 * File:   tft.c
 * Author: Alfred Lohmann
 *         HAW-Hamburg
 *         Labor für technische Informatik
 *         Berliner Tor  7
 *         D-20099 Hamburg
 * Version: 1.1
 *
 * Created on 12. Juli 2013, 08:10
 *
 * 30. March 2015, Hans H. Heitmann: * beep off for touch display added
 * 20.11.2015 Silke Behn  TFT_bigString + TFT_bigText 
 * 10.10.2016	Nils Schoenherr: clean-up + bugfix
 * 08.06.2017 Silke Behn  TFT_getProtocollSettings / TFT_setTimeout / 
 *            TFT_send_data: wenn weder ACK noch NAK dann timeout warten
 *			  TFT_Init: timout setzen
 * 15.03.2018 TFT_get_data  am Ende ein Delay, wegen Prell Verhalten
 */
 
 /* Includes -----------------------------------------------------------------*/
#include <string.h>
#include "TI_memory_map.h"
#include "tft.h"
#include "TI_Lib.h"






/* Implementation---- --------------------------------------------------------*/

/**
  * @brief  Setzt das Timeout und die Paketgroesse
  * @autor  Silke Behn 09.06.2017
  * @param  packSize    Max Package Size  (1..128) (Standard 128)
  *         timeout     in 1/100s, (1..255)(Standard 200=2s)
  * @retval 1 = OK, 0 = not OK
  */
int TFT_setTimeout(int packsize, int timeout ){
    
	int bcc = 0;
	int ack = 0;

	GPIOB->BSRRH = (1<<12);

   //Send Command DC2 => 0x12
	SPI2->DR =  DC2;
	while( (SPI2->SR & (1<<0))==0 ){
	}
	SPI2->DR;
	
	 //Send Anzahl Parameter => 3
	SPI2->DR =  0x03;
	while( (SPI2->SR & (1<<0))==0 ){
	}
	SPI2->DR;
	
	//Send D => 0x44
	SPI2->DR =  0x44;
	while( (SPI2->SR & (1<<0))==0 ){
	}
	SPI2->DR;
	  
	//Send Package Size
	SPI2->DR =  packsize;
	while( (SPI2->SR & (1<<0))==0 ){
	}
	SPI2->DR;

	 //Send timeout
	SPI2->DR =  timeout;
	while( (SPI2->SR & (1<<0))==0 ){
	}
	SPI2->DR;

	//Send bcc
	bcc = ( DC2 + 0x03 + 0x44 + packsize + timeout ) % 0xFF;
	SPI2->DR =  bcc;
	while( (SPI2->SR & (1<<0))==0 ){
	}
	SPI2->DR;
		
		
	 //Read  ACK
	SPI2->DR =  0xFF;
	while( (SPI2->SR & (1<<0))==0 ){
	}
	ack = SPI2->DR;
	
	GPIOB->BSRRL = (1<<12);	
	
	return ack;
}	


/**
  * @brief  Gibt die Einstellungen des Protocol Settings zurück
  * @autor  Silke Behn 08.06.2017
  * @param  
  * @retval Protocol Settings
  */
TFTProtocolSettings TFT_getProtocolSettings( void ){
	int j;
	int bcc = 0;
	
	TFTProtocolSettings ps = {0};
	
	
	GPIOB->BSRRH = (1<<12);

	//Send Request for protocol settings ------------------------------
	//Send Command DC2 => 0x12
	SPI2->DR =  DC2;
	while( (SPI2->SR & (1<<0))==0 ){ }
	SPI2->DR;

	//Send anz Param => 0x01
	SPI2->DR = 0x01;
	while( (SPI2->SR & (1<<0))==0 ){}
	SPI2->DR;

	//Send P => 0x50
	SPI2->DR = 0x50;
	while( (SPI2->SR & (1<<0))==0 ){}
	SPI2->DR;

	//Send checksum => sum all bytes incl DC2 Modulo 256
	bcc = DC2 + 0x01 + 0x50;
	SPI2->DR = bcc & 0xff;
	while( (SPI2->SR & (1<<0))==0 ){}
	SPI2->DR;
		
			
	//Warte auf Antwort-Byte
	for( j=0; j < TFT_RESPONSE_WAIT; j++ ){	}
		
		
	// Read ACK --------------------------------------------------------
	SPI2->DR = 0xff;
	while( (SPI2->SR & (1<<0))==0 ){}
	ps.ack = SPI2->DR;
     
	if (ps.ack == ACK) {	
		
		//Warte auf Antwort-Byte
		for( j=0; j < TFT_RESPONSE_WAIT; j++ ){ }

        //Read Protocol Settings ---------------------------------------- 
		
		//Read DC2 
		SPI2->DR = 0xff;
		while( (SPI2->SR & (1<<0))==0 ){}
		ps.dc2 = SPI2->DR;
				

		//Warte auf Antwort-Byte
		for( j=0; j < TFT_RESPONSE_WAIT; j++ ){ }
		
		//read num of data 
		SPI2->DR = 0xff;
		while( (SPI2->SR & (1<<0))==0 ){}
		ps.sum = SPI2->DR;
		
		
		//Warte auf Antwort-Byte
		for( j=0; j < TFT_RESPONSE_WAIT; j++ ){	}
			
		//read Max Pack Size		
		SPI2->DR = 0xff;
		while( (SPI2->SR & (1<<0))==0 ){}
		ps.maxPackSize = SPI2->DR;
				
		
		//Warte auf Antwort-Byte
		for( j=0; j < TFT_RESPONSE_WAIT; j++ ){	}
				
		//read Akt send Pack Size
		SPI2->DR = 0xff;
		while( (SPI2->SR & (1<<0))==0 ){	}
		ps.aktSendPackSize = SPI2->DR;
		
				
		//Warte auf Antwort-Byte
		for( j=0; j < TFT_RESPONSE_WAIT; j++ ){	}
				
		//read timeout 
		SPI2->DR = 0xff;
		while( (SPI2->SR & (1<<0))==0 ){}
		ps.aktTimeout  = SPI2->DR;
				
		//Warte auf Antwort-Byte
		for( j=0; j < TFT_RESPONSE_WAIT; j++ ){	}


		//read bcc
		bcc = (ps.dc2 + ps.sum +  ps.maxPackSize +   ps.aktSendPackSize +  ps.aktTimeout ) & 0xFF;
		SPI2->DR = 0xff;
		while( (SPI2->SR & (1<<0))==0 ){}
		ps.bcc = SPI2->DR;
		if ( bcc == ps.bcc ) {
		    ps.bccOK = 1;
		} else {
            ps.bccOK = 0;					
		}
				
	}
		  
		
	GPIOB->BSRRL = (1<<12);		
	
	
	return ps;
}





/**
  * @brief  Outputs a data to TFT using SMALL PROTOCOL
  * @param  len .. number of characet to send
	*         data . data to send
  * @retval count of tries to send data
  */
int TFT_send_data( int len, char* data ){
	int rc;
	int chksum = 0;
	int i, j;
	int loops = 0;
	
	// avoid sending packages without payload
	if (0 == len) { return loops; }
	
	do{
	
		GPIOB->BSRRH = (1<<12);

		SPI2->DR = 0x11;  //DC1
		while( (SPI2->SR & (1<<0))==0 ){
		}
		SPI2->DR;

		SPI2->DR = len;
		while( (SPI2->SR & (1<<0))==0 ){
		}
		SPI2->DR;

		chksum = 0x11 + len;
		for( i=0; i<len; i++ ){
			chksum += data[i];
			SPI2->DR = data[i];
			while( (SPI2->SR & (1<<0))==0 ){
			}
			SPI2->DR;
		}


		SPI2->DR = chksum & 0xff;
		while( (SPI2->SR & (1<<0))==0 ){
		}
		SPI2->DR;
		

		
		//Warte auf Antwort-Byte
		for( j=0; j < TFT_RESPONSE_WAIT; j++ ){
		}
		

		SPI2->DR = 0xff;
		while( (SPI2->SR & (1<<0))==0 ){
		}
		rc = SPI2->DR;

		GPIOB->BSRRL = (1<<12);		
		loops++;
		
		
		//Wenn nicht ACK und nicht NAK dann timeout warten
		if ( (rc != 0x06) & ( rc != 0x15) ){
			 for( j=0; j < (DELAY1_100S * TFT_TIMEOUT) ; j++){};
		}	
		
		
	}while( rc != 0x06 );
	
	return loops;
}

/**
  * Silke Behn / 06.11.2015
  * Stellt den String str an der Koordinate x/y in grosser Schrift da
  * 
**/
void TFT_bigString(int x, int y, char * str){
   int i=0;
	 char cmd[9];
	 TFT_set_font(6);

   cmd[0] = ESC;
   cmd[1] = 'F';
   cmd[2] = 'Z';
   cmd[3] = 4;
   cmd[4] = 1;
  
   TFT_send_data(5, cmd);	 
  
	
   cmd[0] = ESC;
   cmd[1] = 'Z';
   cmd[2] = 'L';

   cmd[4] = 0;

   cmd[6] = 0;
   
   cmd[8] = 0;
  
   TFT_send_data(9, cmd);
	while ( str[i] != '\0' ) {
	    cmd[3] = x*20;
      cmd[5] = y*25;
      cmd[7] = str[i];
      TFT_send_data(9, cmd);
		
	    i += 1;
        x += 1;		
	    //Es passen nur 11 Zeichen in eine Zeile	
	    if ( x == 11 ) {
           x = 0;
           y += 1;
        }		   
    }		
}

/**
  * Silke Behn / 06.11.2015
  * Stellt das Zeichen b an der Koordinate x/y in grosser Schrift da
**/
void TFT_bigText(int x, int y, char b){
   char cmd[9];
   
   TFT_set_font(6);

   cmd[0] = ESC;
   cmd[1] = 'F';
   cmd[2] = 'Z';
   cmd[3] = 4;
   cmd[4] = 1;
  
   TFT_send_data(5, cmd);	 
  
	
   cmd[0] = ESC;
   cmd[1] = 'Z';
   cmd[2] = 'L';
   cmd[3] = x*20;
   cmd[4] = (x*20)>>8;
   cmd[5] = y*29;
   cmd[6] = (y*29)>>8;
   cmd[7] = b;
   cmd[8] = 0;
  
   TFT_send_data(9, cmd);
}

int TFT_get_data(int n, char *buffer){
	
	char len;
	char lenPrell;
  char datPrell[4]; 
	char *d = datPrell; 
    int anz_leseversuch = 4;
	int i = 0;
	
	len =  TFT_get_dat(n,buffer);

	 //Wenn touchpad gedrückt, daten rauslesen, falls geprellt	
    if ( len > 0) {
	
	    for (i=0; i < anz_leseversuch; i++){
		     lenPrell = TFT_get_dat(n, d );
	    }	 
	}
	return len;	
	
}

/**
  * @brief  Read data from TFT
  * @param  n .. buffer size
  *         *buffer .. pointer to buffer 
  * @retval number of data read
  */
int TFT_get_dat(int n, char *buffer){
    
    char buf[4];
    char len, len_saved;
    int data;
		int i;
    
    buf[0] = DC2;
    buf[1] = 1;
    buf[2] = 'S';
    buf[3] = buf[0] + buf[1] +buf[2];

	GPIOB->BSRRH = (1<<12);					// set select line

	do{
		for( i = 0; i < 4; i++ ){					// send command to get buffer
			SPI2->DR = buf[i];
			while( (SPI2->SR & (1<<0))==0 ){
			}
			SPI2->DR;
		}

		//Warte auf Antwort-Byte ACK
		for( i=0; i < TFT_RESPONSE_WAIT; i++ ){
		}

		SPI2->DR = 0xff;
		while( (SPI2->SR & (1<<0))==0 ){
		}
		data = SPI2->DR;
	
	}while (data != 6);							// wait for ACK

		
	for( i=0; i < TFT_RESPONSE_WAIT; i++ ){
	}
	//Warte auf Antwort-Byte DC1
	SPI2->DR = 0xff;
	while( (SPI2->SR & (1<<0))==0 ){
	}
	data = SPI2->DR;	
	
	if (data != 0x11){
			return 0;
	}
	
	for( i=0; i < TFT_RESPONSE_WAIT; i++ ){
	}
	//Warte auf Antwort-Byte len
	SPI2->DR = 0xff;
	while( (SPI2->SR & (1<<0))==0 ){
	}
	len = SPI2->DR;	
	len_saved = len;
		
    if (len != 0){
        do{
					 for( i=0; i < TFT_RESPONSE_WAIT; i++ ){
					 }
           SPI2->DR = 0xff;
					 while( (SPI2->SR & (1<<0))==0 ){
					}
					*buffer = SPI2->DR;
					buffer++;
					len--;
        }while (len > 0);
    }

	for( i=0; i < TFT_RESPONSE_WAIT; i++ ){
	}

    //Warte auf Antwort-Byte bcc
	SPI2->DR = 0xff;
	while( (SPI2->SR & (1<<0))==0 ){
	}
	data = SPI2->DR;

	GPIOB->BSRRL = (1<<12);									// clear select line

	Delay(5);
    return len_saved;

}


/**
  * @brief  Initialize TFT, TI-Board has to be initialized
  * @param  none
  * @retval none
  */
void TFT_Init(void){

  TFT_terminal_on();
	TFT_cls();
  TFT_touch_key_feedback(0,1);
#ifndef SIMULATION
	TFT_setTimeout(128,TFT_TIMEOUT);         // max 128 Bytes pro Package, timeout nach 2/100 s
#endif
}


/**
  * @brief  Close TFT connection
  * @param  none
  * @retval none
  */
void TFT_release(void){
    
    return;
}


/**
  * @brief  Turns ASCII-Terminal on
  * @param  none
  * @retval none
  */
void TFT_terminal_on(void){
   char cmd[3];
   
   cmd[0] = ESC;
   cmd[1] = 'T';
   cmd[2] = 'E';
   
   TFT_send_data(3, cmd);
}


/**
  * @brief  Turns ASCII-Terminal off
  * @param  none
  * @retval none
  */
void TFT_terminal_off(void){
   char cmd[3];
   
   cmd[0] = ESC;
   cmd[1] = 'T';
   cmd[2] = 'A';
   
   TFT_send_data(3, cmd);
}


/**
  * @brief  Turns ASCII-Terminal cursor on
  * @param  none
  * @retval none
  */
void TFT_cursor_on(void){
   char cmd[4];
   
   cmd[0] = ESC;
   cmd[1] = 'T';
   cmd[2] = 'C';
   cmd[3] = 1;
   
   TFT_send_data(4, cmd);
}


/**
  * @brief  Turns ASCII-Terminal cursor off
  * @param  none
  * @retval none
  */
void TFT_cursor_off(void){
   char cmd[4];
   
   cmd[0] = ESC;
   cmd[1] = 'T';
   cmd[2] = 'C';
   cmd[3] = 0;
   
   TFT_send_data(4, cmd);
}


/**
  * @brief  Position cursor
  * @param  x .. character position 1 ...
  *         y .. line 1 ...
  * @retval none
  */
void TFT_gotoxy(int x, int y){
   char cmd[5];
   
   cmd[0] = ESC;
   cmd[1] = 'T';
   cmd[2] = 'P';
   cmd[3] = x;
   cmd[4] = y;
   
   TFT_send_data(5, cmd);
    
}


/**
  * @brief  Sets TFT brightness 
  * @param  bright .. 0 .. 100
  * @retval none
  */
void TFT_set_brightness(int bright){
   char cmd[5];
   
   cmd[0] = ESC;
   cmd[1] = 'Y';
   cmd[2] = 'H';
   cmd[3] = bright;
   
   TFT_send_data(4, cmd);
    
}



/**
  * @brief  Turns buzzer on 
  * @param  duration .. in 1/10 sec, 1 means unlimites
  * @retval none
  */

void TFT_buzzer_on(int duration){
   char cmd[4];
   
   cmd[0] = ESC;
   cmd[1] = 'Y';
   cmd[2] = 'S';
   cmd[3] = duration;
   
   TFT_send_data(4, cmd);
    
}


/**
  * @brief  Turns buzzer off
  * @param  none
  * @retval none
  */
void TFT_buzzer_off(void){
   char cmd[4];
   
   cmd[0] = ESC;
   cmd[1] = 'Y';
   cmd[2] = 'S';
   cmd[3] = 0;
   
   TFT_send_data(4, cmd);

}


/**
  * @brief  Clears ASCII-Terminal
  * @param  none
  * @retval none
  */
void TFT_cls(void){
    TFT_putc(12);               // clears screen, cursor 1,1
}


/**
  * @brief  Position cursor to a next line
  * @param  none
  * @retval none
  */
void TFT_newline(void){
    TFT_putc(10);               // cursor to next line
}


/**
  * @brief  Position cursor to beginning of line
  * @param  none
  * @retval none
  */
void TFT_carriage_return(void){
    TFT_putc(13);               // cursor to beginn of line
}



/**
  * @brief  Selects font to be used
  * @param  font .. font number
  * @retval none
  */
void TFT_set_font(int font){
   
   char cmd[6];
   cmd[0] = ESC;
   cmd[1] = 'Z';
   cmd[2] = 'F';
   cmd[3] = font;
  
   TFT_send_data(4, cmd);
}


/**
  * @brief  Selects font color to be used
  * @param  clr .. color 1 .. 32
  * @retval none
  */
void TFT_set_font_color(int clr){
   
   char cmd[6];
   cmd[0] = ESC;
   cmd[1] = 'F';
   cmd[2] = 'T';
   cmd[3] = clr;
   cmd[4] = 1;
   
   TFT_send_data(5, cmd);
}



/**
  * @brief  Defines ASCII window
  * @param  font .. font number
  *         x_start ... start character position 
  *         y_start ... start line 
  *         num_x ..... width number of character
  *         num_y ..... width number of lines
  * @retval none
  */
void TFT_set_window(int font, int x_start, int y_start, int num_x, int num_y){
    char cmd[9];
    
    cmd[0] = ESC;
    cmd[1] ='T';
    cmd[2] ='W';
    cmd[3] = font;         // font 8*8
    cmd[4] = x_start;
    cmd[5] = y_start;
    cmd[6] = num_x;
    cmd[7] = num_y;
    
    TFT_send_data(8, cmd);
}


/**
  * @brief  Defines color used by GRAPHIC
  * @param  clr ... color 1 .. 32
  * @retval none
  */
void TFT_set_graphic_color(int clr){
   
   char cmd[6];
   cmd[0] = ESC;
   cmd[1] = 'F';
   cmd[2] = 'D';
   cmd[3] = clr;
   cmd[4] = 1;
   
   TFT_send_data(5, cmd);
}


/**
  * @brief  Defines color used by GRAPHIC
  * @param  clr ... color 1 .. 32
  * @retval none
  */
void TFT_set_pixel_color(int clr){
   
   char cmd[6];
   cmd[0] = ESC;
   cmd[1] = 'F';
   cmd[2] = 'G';
   cmd[3] = clr;
   cmd[4] = 1;
   
   TFT_send_data(5, cmd);
}


/**
  * @brief  Clears GRAPHIC
  * @param  none
  * @retval none
  */

void TFT_graphic_cls(void){
    
   char cmd[6];
   cmd[0] = ESC;
   cmd[1] = 'D';
   cmd[2] = 'L';
   
   TFT_send_data(3, cmd);
}


/**
  * @brief  Defines color used by GRAPHIC TEXT
  * @param  clr ... color 1 .. 32
  * @retval none
  */
void TFT_set_graphic_text_color(int clr){
   
   char cmd[6];
   cmd[0] = ESC;
   cmd[1] = 'F';
   cmd[2] = 'Z';
   cmd[3] = clr;
   cmd[4] = 1;
   
  TFT_send_data(5, cmd);
}


/**
  * @brief  Defines font used by GRAPHIC TEXT
  * @param  clr ... font
  * @retval none
  */
void TFT_set_graphic_text_font(int font){
   
   char cmd[6];
   cmd[0] = ESC;
   cmd[1] = 'Z';
   cmd[2] = 'F';
   cmd[3] = font;
   
   TFT_send_data(4, cmd);
}


/**
  * @brief  Output GRAPHIC TEXT string
  * @param  x ........ x position
	*         y ........ y position
  *         position .. left, centered or right
  * @retval none
  */
void TFT_graphic_puts(int x, int y, int position, char *s){
    char cmd[TFT_BUFFER_SIZE+3];
    int i=0;
    
    cmd[i++] = ESC;
    cmd[i++] = 'Z';
    
    if (position == TEXT_LEFT)
        cmd[i++] = 'L';
    else if (position == TEXT_CENTERED)
        cmd[i++] = 'C';
    else       
        cmd[i++] = 'R';
                
    cmd[i++] = x & 0x00ff;              // high byte of position
    cmd[i++] = (x >> 8) & 0x0ff;        // low byte
    cmd[i++] = y & 0x00ff;              // high byte of position
    cmd[i++] = (y >> 8) & 0x0ff;        // low byte
    
    while(((cmd[i] = *s)!=0) && (i < TFT_BUFFER_SIZE)){
        i++;
        s++;
        
    };
    cmd[i] = 0;
    i++;
    TFT_send_data(i, cmd);
    
}


/**
  * @brief  Output GRAPHIC TEXT string to an aread
  * @param  x ........ x position upper left corner
	*         y ........ y position upper left corner
  *         x2 ....... x position lower left corner
	*         y2 ....... y position lower left corner
  *         position .. position in area
  * @retval none
  */
void TFT_graphic_puts_area(int x, int y, int x2, int y2, int position, char *s){
    char cmd[TFT_BUFFER_SIZE+3];
    int i=0;
    
    cmd[i++] = ESC;
    cmd[i++] = 'Z';
		cmd[i++] = 'B';								//
    
    cmd[i++] = x & 0x00ff;              // high byte of position
    cmd[i++] = (x >> 8) & 0x0ff;        // low byte
    cmd[i++] = y & 0x00ff;              // high byte of position
    cmd[i++] = (y >> 8) & 0x0ff;        // low byte
	
		cmd[i++] = x2 & 0x00ff;              // high byte of position
    cmd[i++] = (x2 >> 8) & 0x0ff;        // low byte
    cmd[i++] = y2 & 0x00ff;              // high byte of position
    cmd[i++] = (y2 >> 8) & 0x0ff;        // low byte
    
		cmd[i++] = position;
	
    while(((cmd[i] = *s)!=0) && (i < TFT_BUFFER_SIZE)){
        i++;
        s++;
        
    };
    cmd[i] = 0;
    i++;
    TFT_send_data(i, cmd);
    
}

/**
  * @brief  Sets a point on graphic display
  * @param  x ........ x position
	*         y ........ y position
  * @retval none
  */
void TFT_graphic_set_point(int x, int y){
    char cmd[TFT_BUFFER_SIZE+3];
    int i=0;
    
    cmd[i++] = ESC;
    cmd[i++] = 'G';
    cmd[i++] = 'P';
                
    cmd[i++] = x & 0x00ff;              // high byte of position
    cmd[i++] = (x >> 8) & 0x0ff;        // low byte
    cmd[i++] = y & 0x00ff;              // high byte of position
    cmd[i++] = (y >> 8) & 0x0ff;        // low byte
    i++;
    TFT_send_data(i, cmd);
    
}


/**
  * @brief  Output one charater to ASCII-Terminal
  * @param  c .. charater to output
  * @retval none
  */
void TFT_putc(char c){
 
    char s[3];
    s[0] = c;
    s[1] = '~';
    s[2] = 0;
    TFT_send_data(1, s);
    
}


/**
  * @brief  Output one stringto ASCII-Terminal
  * @param  *s .. ascii string
  * @retval none
  */
void TFT_puts(char *s){
    
    TFT_send_data(strlen(s), s);
}


/**
  * @brief  Defines a bargraph
  * @param   
  * @retval none
  */
void TFT_bargraph_define(int nr, int bar_direction,
                         int x1, int y1, int x2, int y2, 
                         int start_value, int end_value, int type ){
    
    char cmd[20];
    int i=0;
    
    cmd[i++] = ESC;
    cmd[i++] = 'B';
    
    if (bar_direction == BARGRAPH_RIGHT)
        cmd[i++] = 'R';
    else if (bar_direction == BARGRAPH_LEFT)
        cmd[i++] = 'L';
    else if (bar_direction == BARGRAPH_TOP)
        cmd[i++] = 'O';
    else       
        cmd[i++] = 'U';
    
    cmd[i++]             = nr;
    cmd[i++] = x1 & 0x00ff;              // high byte of position
    cmd[i++] = (x1 >> 8) & 0x0ff;        // low byte
    cmd[i++] = y1 & 0x00ff;              // high byte of position
    cmd[i++] = (y1 >> 8) & 0x0ff;        // low byte
    cmd[i++] = x2 & 0x00ff;              // high byte of position
    cmd[i++] = (x2 >> 8) & 0x0ff;        // low byte
    cmd[i++] = y2 & 0x00ff;              // high byte of position
    cmd[i++] = (y2 >> 8) & 0x0ff;        // low byte
    cmd[i++] = start_value;
    cmd[i++] = end_value;
    cmd[i++] = type;
    
    TFT_send_data(i, cmd);
        
}


/**
  * @brief  Sends a new values to bargraph
  * @param  nr ..... bargraph id (as set TFT_bargraph_define) 
  *         value .. range start_value to end_values
  * @retval none
  */
void TFT_bargraph_value(int nr, int value){
    char cmd[5];
    
    cmd[0] = ESC;
    cmd[1] = 'B';
    cmd[2] = 'A';
    cmd[3] = nr;
    cmd[4] = value;
    
    TFT_send_data(5, cmd);
}

// only valid for bargraph type 0..3
void TFT_bargraph_fill_pattern(int pattern){
    
    char cmd[4];
    
    cmd[0] = ESC;
    cmd[1] = 'B';
    cmd[2] = 'M';
    cmd[3] = pattern;
   
    TFT_send_data(4, cmd);
}

// only valid for bargraph type 4..7
void TFT_bargraph_frame(int frame){
    
    char cmd[4];
    
    cmd[0] = ESC;
    cmd[1] = 'B';
    cmd[2] = 'E';
    cmd[3] = frame;
   
    TFT_send_data(4, cmd);
}


/**
  * @brief  Defines a bargraph color
  * @param  fg ..... foreground color
  *         bg ..... background color
	*         frame .. frame type used
  * @retval none
  */
void TFT_bargraph_color(int fg, int bg, int frame){
    
    char cmd[6];
    
    cmd[0] = ESC;
    cmd[1] = 'F';
    cmd[2] = 'B';
    cmd[3] = fg;
    cmd[4] = bg;
    cmd[5] = frame;
   
    TFT_send_data(6, cmd);
}


/**
  * @brief  Defines a GRAPHIC LINE color
  * @param  fg ..... foreground color
  *         bg ..... background color
  * @retval none
  */
void TFT_line_color(int fg, int bg){
    
    char cmd[5];
    
    cmd[0] = ESC;
    cmd[1] = 'F';
    cmd[2] = 'G';
    cmd[3] = fg;
    cmd[4] = bg;
  
   
    TFT_send_data(5, cmd);
}


/**
  * @brief  Draw a GRAPHIC LINE
  * @param  x1 ... start position x
  *         y1 ... start position y
  *         x2 ... end position x
  *         y2 ... end position y
  * @retval none
  */
void TFT_draw_line(int x1, int y1, int x2, int y2){
    
    char cmd[12];
    int i=0;
    
    cmd[i++] = ESC;
    cmd[i++] = 'G';
    cmd[i++] = 'D';
    cmd[i++] = x1 & 0x00ff;              // high byte of position
    cmd[i++] = (x1 >> 8) & 0x0ff;        // low byte
    cmd[i++] = y1 & 0x00ff;              // high byte of position
    cmd[i++] = (y1 >> 8) & 0x0ff;        // low byte
    cmd[i++] = x2 & 0x00ff;              // high byte of position
    cmd[i++] = (x2 >> 8) & 0x0ff;        // low byte
    cmd[i++] = y2 & 0x00ff;              // high byte of position
    cmd[i++] = (y2 >> 8) & 0x0ff;        // low byty
    
    TFT_send_data(i, cmd);
    
    return;
}


/**
  * @brief  Draw a GRAPHIC rectangle
  * @param  x1 ....... x position upper left corner
	*         y1 ....... y position upper left corner
  *         x2 ....... x position lower left corner
	*         y2 ....... y position lower left corner
  * @retval none
  */
void TFT_draw_rectangle(int x1, int y1, int x2, int y2){
    
    char cmd[12];
    int i=0;
    
    cmd[i++] = ESC;
    cmd[i++] = 'G';
    cmd[i++] = 'R';
    cmd[i++] = x1 & 0x00ff;              // high byte of position
    cmd[i++] = (x1 >> 8) & 0x0ff;        // low byte
    cmd[i++] = y1 & 0x00ff;              // high byte of position
    cmd[i++] = (y1 >> 8) & 0x0ff;        // low byte
    cmd[i++] = x2 & 0x00ff;              // high byte of position
    cmd[i++] = (x2 >> 8) & 0x0ff;        // low byte
    cmd[i++] = y2 & 0x00ff;              // high byte of position
    cmd[i++] = (y2 >> 8) & 0x0ff;        // low byty
    
    TFT_send_data(i, cmd);
    
    return;
}


/**
  * @brief  Defines the FRAME for TOUCH area
  * @param  frame ... frame 1 .. 20
  *         angle ... angle to display 0, 90, 180,270
  * @retval none
  */
void TFT_touch_area_frame(int frame, int angle ){
    
    char cmd[5];
    
    cmd[0] = ESC;
    cmd[1] = 'A';
    cmd[2] = 'E';
    cmd[3] = frame;
    cmd[4] = angle;
   
    TFT_send_data(5, cmd);
    
    return;
}


/**
  * @brief  Selects font used in TOUCH area
  * @param  font ... font to use
  * @retval none
  */
void TFT_touch_area_font(int font ){
    
    char cmd[4];
    
    cmd[0] = ESC;
    cmd[1] = 'A';
    cmd[2] = 'F';
    cmd[3] = font;
   
    TFT_send_data(4, cmd);
    
    return;
}


/**
  * @brief  Defines a TOUCH font color
  * @param  fg ..... foreground color
  *         bg ..... background color
  * @retval none
  */
void TFT_touch_area_font_color(int fg, int bg ){
    
    char cmd[5];
    
    cmd[0] = ESC;
    cmd[1] = 'F';
    cmd[2] = 'A';
    cmd[3] = fg;
    cmd[4] = bg;
   
    TFT_send_data(5, cmd);
    
    return;
}

 //#FE=Set touchborder colors: #FE n1,n2,n3,s1,s2,s3  (n1..n3=normal s1..s3=for selection (0..32);
void TFT_touch_area_color(int n1, int n2, int n3, int s1, int s2, int s3){
    
    char cmd[9];
    
    cmd[0] = ESC;
    cmd[1] = 'F';
    cmd[2] = 'E';
    cmd[3] = n1;
    cmd[4] = n2;
    cmd[5] = n3;
    cmd[6] = s1;
    cmd[7] = s2;
    cmd[8] = s3;
    
    TFT_send_data(9, cmd);
    
    return;
}


/**
  * @brief  Defines a TOUCH area
  * @param  x1 .............. x position upper left corner
	*         y1 .............. y position upper left corner
  *         x2 .............. x position lower left corner
	*         y2 .............. y position lower left corner
  *         code_pressed .... code returned when aread is pressed
  *         code_preleased .. code returned when aread is released
  *         *s .............. pointer to text displayed in area
  * @retval none
  */
void TFT_touch_area(int x1, int y1, int x2, int y2,
                    int code_pressed, int code_released, char *s ){
    
    static char cmd[262];
    int i=0;
    
    cmd[i++] = ESC;
    cmd[i++] = 'A';
    cmd[i++] = 'T';
    cmd[i++] = x1 & 0x00ff;              // high byte of position
    cmd[i++] = (x1 >> 8) & 0x0ff;        // low byte
    cmd[i++] = y1 & 0x00ff;              // high byte of position
    cmd[i++] = (y1 >> 8) & 0x0ff;        // low byte
    cmd[i++] = x2 & 0x00ff;              // high byte of position
    cmd[i++] = (x2 >> 8) & 0x0ff;        // low byte
    cmd[i++] = y2 & 0x00ff;              // high byte of position
    cmd[i++] = (y2 >> 8) & 0x0ff;        // low byty
    cmd[i++] = code_pressed;
    cmd[i++] = code_released;
    
    while(*s != 0){
        cmd[i++] = *s++;
    }
    
    cmd[i++] = 0;
    TFT_send_data(i, cmd);
    
    return;
}


/**
  * @brief  Clears TOUCH area
  * @param  none
  * @retval none
  */
void TFT_touch_area_clear(void){

    char cmd[5];

    cmd[0] = ESC;
    cmd[1] = 'A';
    cmd[2] = 'L';
    cmd[3] = 0;
    cmd[4] = 1;

    TFT_send_data(5, cmd);

    return;
}

/**
  * @brief  Make peep off
  * @param  none
  * @retval none
  */
void TFT_touch_key_feedback(int beep, int invert){

    char cmd[4];

    cmd[0] = ESC;
    cmd[1] = 'A';
    cmd[2] = 'S';
    cmd[3] = beep;

    TFT_send_data(4, cmd);

   
    cmd[0] = ESC;
    cmd[1] = 'A';
    cmd[2] = 'I';
    cmd[3] = invert;

    TFT_send_data(4, cmd);

    return;
}




