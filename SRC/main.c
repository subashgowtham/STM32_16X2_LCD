#include "stm32f10x.h"
#include "delay.h"
#include "lcd.h"


int main(void) 
{

  delayInit();
  lcd_init();
	
  lcd_clear();        // Clear display
  lcd_put_cur(0,5);   // Move cursor to the first line, 5th column
  lcd_string("16x2");
  lcd_put_cur(1,3);   // Move cursor to the second line, 3rd column
  lcd_string("LCD TEST");
  while (1);

}