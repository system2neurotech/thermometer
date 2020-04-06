/*
 * lcd.h
 *
 *  Created on: Mar 26, 2020
 *      Author: samtm
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_


void LCD_set_temp(uint16_t temp);
void LCD_set_fahrenheit(uint8_t value);
uint8_t LCD_get_fahrenheit(void);
void LCD_run();

#endif /* INC_LCD_H_ */
