/**
  ******************************************************************************
  * @file    	keypad.c 
  * @author  	Alfred Lohmann
  *        	  HAW-Hamburg
  *          	Labor für technische Informatik
  *          	Berliner Tor  7
  *          	D-20099 Hamburg
  * @version	V1.0
  * @date   	26.03.2014
  * @brief  	Generates and supports keypad on touch screen
	*						20.10.2016 Nils Schoenherr: cleanup includes
  *******************************************************************
  */
//#include "TI_Lib.h"
#include <stdio.h>
#include "tft.h"
#include "keypad.h"

#define NUMBER_BUTTON_HORIZONTAL 7
#define NUMBER_BUTTON_VERTICAL   4

/**
  * @brief  Displays a keypad on touchscreen
  * @param  none
  * @retval none
  */
void Make_Touch_Pad(void){
	 
	 int t_y = 7;
	 int t_y1;
   int ft = 2;
   int t_x = 4;
   int lines=7;
   int column=20;
	
	 int pitch;
   int ys;                            //terminal is organised in lines 1..30/15, depending on
                                      //selcted font -> to calculate pixelpostion, decrement line and multiplay with font height
   int yh;
   int xw;
   int xs;
   int x;
   int y;
	
	TFT_Init();  

  TFT_cursor_off();
  TFT_graphic_cls();
  TFT_touch_area_clear();
        
//_-------------------------------------------------
//---- 2. Define the small blue terminal window ----
//--------------------------------------------------
  TFT_set_font_color( YELLOW );       // define terminal colors
  
	t_y = 3;
  ft = 2;
  t_x = 4;
  lines=7;
  column=20;
  TFT_set_window( ft, t_x, t_y, column,lines);    // define the font (8x16), origin
                                                  //(5x8=40,7x16=112), width (20 character) and height (7 lines)
                                                  // note: origin is defined as column no.7 and line no.10 (not dots)
  TFT_terminal_on();                              // Terminal on        

  // ----------------------------------------------
  //---- 3. Define a keypad with numbers 0..9 ----
  //---------------------------------------------
  TFT_touch_area_font_color( YELLOW,BLACK );      // define color for touch font
  TFT_touch_area_font(SWISS30B);                  // set font for touch area
  TFT_touch_area_frame(20,0);                     //set border no. 20
  TFT_touch_area_color(WHITE,BLACK,BLUE, WHITE,BLACK,YELLOW);     //set border colors normal and for selection
                                                                  // using a constant for (touch)size and (touch)pitch makes it 
                                                                  //more easy to move the whole key group later
// XPIXEL=320 and YPIXEL=240 
   pitch = 2;
	 t_y1 = 5;												// startline for button
   ys=(t_y1-1)*ft*8;                //terminal is organised in lines 1..30/15, depending on
                                    //selcted font -> to calculate pixelpostion, decrement line and multiplay with font height
   yh=(YPIXEL-ys-3*pitch)/NUMBER_BUTTON_VERTICAL;				// 4 button vertical
   xw = yh;													// width same as hight
   xs = XPIXEL-(NUMBER_BUTTON_HORIZONTAL*xw+2*pitch);			// 7 button in line
   x=xs;														// xs is left start of button
   y=ys;
   TFT_touch_area( x, y, x+xw, y+yh, '1', 0, "1" );   // define a touchkey with number "1". 
   x+=pitch+xw;                                       //while release, touchmacro no. 20 will be executed
   TFT_touch_area( x, y, x+xw, y+yh, '2', 0, "2" );
   x+=pitch+xw;
   TFT_touch_area( x, y, x+xw, y+yh, '3', 0, "3" );
	 x+=pitch+xw;			// empty place
	 x+=pitch+xw;	
	 TFT_touch_area( x, y, x+xw, y+yh, 'r', 0, "r" );
	 x+=pitch+xw;
	 TFT_touch_area( x, y, x+xw, y+yh, 'd', 0, "d" );
	 x+=pitch+xw;
	 TFT_touch_area( x, y, x+xw, y+yh, 's', 0, "st" );
// -- start 2nd row of buttons	 
   x=xs;
   y+=pitch+yh;
   TFT_touch_area( x, y, x+xw, y+yh, '4', 0, "4" );
   x+=pitch+xw;
   TFT_touch_area( x, y, x+xw, y+yh, '5', 0, "5" );
   x+=pitch+xw;
   TFT_touch_area( x, y, x+xw, y+yh, '6', 0, "6" );
	 x+=pitch+xw;			// empty place
	 x+=pitch+xw;
	 TFT_touch_area( x, y, x+xw, y+yh, '+', 0, "+" );
	 x+=pitch+xw;
	 TFT_touch_area( x, y, x+xw, y+yh, '-', 0, "-" );
	 x+=pitch+xw;
	 TFT_touch_area( x, y, x+xw, y+yh, ' ', 0, " " );
	 
// -- start 3rd row of buttons	 	 
   x=xs;
   y+=pitch+yh;
   TFT_touch_area( x, y, x+xw, y+yh, '7', 0, "7" );
   x+=pitch+xw;
   TFT_touch_area( x, y, x+xw, y+yh, '8', 0, "8" );
   x+=pitch+xw;
   TFT_touch_area( x, y, x+xw, y+yh, '9', 0, "9" );
	 x+=pitch+xw;			// empty place
	 x+=pitch+xw;	
	 TFT_touch_area( x, y, x+xw, y+yh, '*', 0, "*" );
	 x+=pitch+xw;
	 TFT_touch_area( x, y, x+xw, y+yh, '/', 0, "/" );
	 x+=pitch+xw;
	 TFT_touch_area( x, y, x+xw, y+yh, 'p', 0, "p" );
// -- start 4th row of button
	 x=xs;
   y+=pitch+yh;
   //TFT_touch_area( x,y,x+xw,y+yh, 0,0, "=" );
   x+=pitch+xw;
   TFT_touch_area( x, y, x+xw, y+yh, '0', 0, "0" );
   x+=pitch+xw;
   //TFT_touch_area( x, y, x+xw, y+yh, 0, 0, "" );
	 x+=pitch+xw;			// empty place
	 //x+=pitch+xw;
	 //TFT_touch_area( x, y, x+xw, y+yh, '=', 0, "=" );
	 x+=pitch+xw;
	 TFT_touch_area( x, y, x+xw, y+yh, 'e', 0, "e" );
	 x+=pitch+xw;
	 TFT_touch_area( x, y, x+xw, y+yh, 'c', 0, "c" );
	 x+=pitch+xw;
	 TFT_touch_area( x, y, x+xw, y+yh, 'f', 0, "f" );
	 
   return;     
	
}


/**
  * @brief  Reads touch screen input
  * @param  none
  * @retval character typed 
  */
int Get_Touch_Pad_Input(void){
	
	int num_read;
	int retval = 0;
	char data_in[256];
	
	do{	
		num_read = TFT_get_data(256, data_in);
		if (num_read > 0){
		  retval = data_in[3];
			if (data_in[3] == '1');
      else if (data_in[3] == '2');
      else if (data_in[3] == '3');
      else if (data_in[3] == '4');
      else if (data_in[3] == '5');
      else if (data_in[3] == '6');
      else if (data_in[3] == '7');
      else if (data_in[3] == '8');
      else if (data_in[3] == '9');
      else if (data_in[3] == '0');
			else if (data_in[3] == '+');
			else if (data_in[3] == '-');
			else if (data_in[3] == '*');
			else if (data_in[3] == '/');
			else if (data_in[3] == 'e');
			else if (data_in[3] == 'c');
			else if (data_in[3] == 's');
			else if (data_in[3] == 'r');
			else if (data_in[3] == 'd');
			else if (data_in[3] == ' ');
			else if (data_in[3] == 'p');
			else if (data_in[3] == 'f');
      else{
				printf("Unknown data received: 0x%02x 0x%02x 0x%02x 0x%02x\n", data_in[0], data_in[1], data_in[2], data_in[3]);
						 retval = 0;
			}
    }    
    else
		{}
       //Delay(100);
 }while (retval <= 0);
	
	return retval;
}


/**
  * @brief  Outputs a number to text window
  * @param  value .. number to output
  * @retval none
  */
void Display_value(int value){
	
	char text[50];
	int index = 0;
	int ft = 2;					//font
	int t_x	= 4;
	int t_y = 2;
	int column = 20;
	int lines = 2;
	
	TFT_set_window( ft, t_x, t_y, column,lines); 
	snprintf(text, 50, "%d", value);
	TFT_cls();
	//TFT_puts("                         ");
	
	do{
		TFT_putc(text[index]);
		index++;
	}while(text[index] != 0);
}


/**
  * @brief  Clears text window
  * @param  none
  * @retval none
  */
void Clear_Line(void){
	
	int ft = 2;					//font
	int t_x	= 4;
	int t_y = 2;
	int column = 20;
	int lines = 2;
	
	TFT_set_window( ft, t_x, t_y, column,lines); 
	TFT_cls();
	
	
}
