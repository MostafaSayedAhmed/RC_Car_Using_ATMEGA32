/*
 * LCD_config.h
 *
 *  Created on: Sep 11, 2022
 *      Author: Mostafa Sayed
 */

#ifndef HAL_LCD_LCD_CONFIG_H_
#define HAL_LCD_LCD_CONFIG_H_

#define RS PORTB_1
#define RW PORTB_2
#define E  PORTB_3
#define D4 PORTB_4
#define D5 PORTB_5
#define D6 PORTB_6
#define D7 PORTB_7

#define CLEAR_DISPLAY 0x01
#define CURSOR_MOVE_RIGHT 0x06
#define CURSOR_BLINK_ON 0x0f
#define BIT4MODE 0x32


#endif /* HAL_LCD_LCD_CONFIG_H_ */
