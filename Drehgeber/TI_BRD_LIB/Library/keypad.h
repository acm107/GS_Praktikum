/* 
 * File:   keypad.h
 * Author: Alfred Lohmann
 *
 * Created: 26.03.2014
*/
#ifndef KEYPAD_H
#define	KEYPAD_H

#ifdef	__cplusplus
extern "C" {
#endif
	
void Make_Touch_Pad(void);
int Get_Touch_Pad_Input(void);
void Display_value(int value);	
void Clear_Line(void);

#ifdef	__cplusplus
}
#endif

#endif	/* KEYPAD_H */

