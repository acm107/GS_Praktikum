#ifndef __SIM_Board_IO_H
#define __SIM_Board_IO_H
 
/**
  * @brief  Initializes the timer tick to 1 ms
  * @param  none
  * @retval none
  */
 void Init_System_Clock(void);
 
/**
  * @brief  Initializes the PORT G 0..15 as output
  *         and PORT E 0..7 as input
  * @param  none
  * @retval none
  */
 void Init_IO(void);
 
/**
  * @brief  Initializes SPI2 for IO to touch screen
  * @param  none
  * @retval none
  */
 void Init_SPI(void);

#endif
