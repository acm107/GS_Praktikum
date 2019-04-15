/*
 * File:   tft.h
 * Author: lohmann
 *
 * Created on 12. Juli 2012, 09:46
 *
 * 30. March 2015, Hans H. Heitmann:  beep off for touch display added
 * 16.06.2017 Silke Behn: verschieden Defines "warten"
 *
 */

#ifndef TFT_H
#define	TFT_H


#ifdef	__cplusplus
extern "C" {
#endif

	
#define DC1 0x11                // start data protokol
#define DC2 0x12                // start command protokol
#define ACK 0x06                // data received OK
#define NAK 0x15                // data received with error

#define TFT_BUFFER_SIZE 259     // max. len of data supported by TFT
                                // 256 byte of data + DC!, len, bcc
#define TFT_RESPONSE_WAIT 500	

//Display timeout nach 1/100s * diesen Wert (2 => 2/100)	
#define TFT_TIMEOUT       2	

//Schleifenzähler, bei dem 1/100 s erreicht wird 		
#define DELAY1_100S       250000  


// define for graph text
#define TEXT_LEFT     0
#define TEXT_CENTERED 1
#define TEXT_RIGHT    2
// define for graph text area
#define TOP_LEFT 			1
#define TOP_CENTERED	2
#define TOP_RIGHT     3
#define MIDDLE_LEFT   4
#define MIDDLE_CENTER 5
#define MIDDLE_RIGHT  6
#define BOTTOM_LEFT   7
#define BOTTOM_CENTER 8
#define BOTTOM_RIGHT  9
// define for bargraph direction
#define BARGRAPH_LEFT   0
#define BARGRAPH_RIGHT  1
#define BARGRAPH_TOP    2
#define BARGRAPH_BOTTOM 0


//define the max length of chars in strings you want to output (take care of your stacksize)
#define MAX_STRING 48

//---------------define constants---------------//
//Dimension

#define XPIXEL  320
#define YPIXEL 	240
#define XMAX    (XPIXEL - 1)
#define YMAX    (YPIXEL - 1)



//control character
#define ESC  27
//#define CR   13
#define LF   10
#define FF   12
//Orientation
#define W0    0
#define W90   1
#define W180  2
#define W270  3

//color constants
#define tTRANSPARENT  0
#define BLACK         1	// RGB:   0   0   0
#define BLUE          2	/* RGB:   0   0 255 */
#define RED           3	// RGB: 255   0   0
#define GREEN         4	// RGB:   0 255   0
#define MAGENTA       5	// RGB: 255   0 255
#define CYAN          6	// RGB:   0 255 255
#define YELLOW        7	// RGB: 255 255   0
#define WHITE         8	// RGB: 255 255 255
#define DARKGREY      9	// RGB: 111 111 111
#define ORANGE       10	// RGB: 255 143   0
#define PURPLE       11	// RGB: 143   0 255
#define DEEPPINK     12	// RGB: 255   0 143
#define MINT         13	// RGB:   0 255 143
#define LAWNGREEN    14	// RGB: 143 255   0
#define SKYBLUE      15	// RGB:   0 143 255
#define GREY         16	// RGB: 175 175 175

#define NOCHANGE     255

//constants for animations
#define NONE          0
#define ONCE          1
#define CYCLIC        2
#define PINGPONG      3
#define ONCEBACK      4
#define CYCLICBACK    5
#define PINGPONGBACK  6
#define TOFRAME       7
#define DEFAULTTIME   255

//fonts (standardfonts)
#define FONT4x6    1
#define FONT6x8    2
#define FONT7x12   3
#define GENEVA10   4
#define CHICAGO14  5
#define SWISS30B   6
#define BIGZIF50   7
#define BIGZIF100  8

typedef struct {
	int ack;
	int dc2;
	int sum;
	int maxPackSize;
	int aktSendPackSize;
	int aktTimeout;
	int bcc;
	int bccOK;
	
} TFTProtocolSettings;



void TFT_Init(void);
void TFT_release(void);
int TFT_get_data(int n, char *buffer);
int TFT_get_dat(int n, char *buffer);
void TFT_bigText(int x, int y, char b);

//x X Koordinate
void TFT_bigString(int x, int y, char * str);

// Terminal commands
void TFT_set_window(int font, int x_start, int y_start, int num_x, int num_y);
void TFT_cls(void);
void TFT_newline(void);
void TFT_carriage_return(void);

void TFT_terminal_on(void);
void TFT_terminal_off(void);

void TFT_cursor_on(void);
void TFT_cursor_off(void);

void TFT_gotoxy(int x, int y);
void TFT_set_brightness(int bright);
void TFT_set_font(int font);
void TFT_set_font_color(int clr);
void TFT_buzzer_on(int duration);       // duration 1=on, 2..255 on for 1/10 msec
void TFT_buzzer_off(void);

void TFT_putc(char c);
void TFT_puts(char *s);


// graphical commands
void TFT_graphic_cls(void);
void TFT_graphic_set_point(int x, int y);
void TFT_set_graphic_color(int clr);
void TFT_set_pixel_color(int clr);
void TFT_set_graphic_text_color(int clr);
void TFT_set_graphic_text_font(int font);
void TFT_graphic_puts(int x, int y, int pos, char *s);
void TFT_graphic_puts_area(int x, int y, int x2, int y2, int position, char *s);

void TFT_bargraph_define(int nr, int bar_direction,
                         int x1, int y1, int x2, int y2,
                         int start_value, int end_value, int type );
void TFT_bargraph_color(int fg, int bg, int frame);
void TFT_bargraph_fill_pattern(int pattern);    // only valid for bargraph type 0..3
void TFT_bargraph_frame(int frame);             // only valid for bargraph type 4..7
void TFT_bargraph_value(int nr, int value);

void TFT_line_color(int fg, int bg);
void TFT_draw_line(int x1, int y1, int x2, int y2);
void TFT_draw_rectangle(int x1, int y1, int x2, int y2);
void TFT_touch_area_frame(int frame, int angle );
void TFT_touch_area_font(int font );
void TFT_touch_area_font_color(int fg, int bg );
void TFT_touch_area_color(int n1, int n2, int n3, int s1, int s2, int s3);
void TFT_touch_area(int x1, int y1, int x2, int y2,
                    int code_pressed, int code_released, char *s );
void TFT_touch_area_clear(void);
void TFT_touch_key_feedback(int beep, int invert);


#ifdef	__cplusplus
}
#endif

#endif	/* TFT_H */
