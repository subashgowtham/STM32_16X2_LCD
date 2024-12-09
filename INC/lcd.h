#ifndef LCD_H
#define LCD_H

#include "stm32f10x.h"
#include "delay.h"
#include "stdint.h"
#include "stdio.h"

void lcd_init(void);
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_clear(void);
void lcd_put_cur(uint8_t row, uint8_t col);
void lcd_string(char *data);

#endif