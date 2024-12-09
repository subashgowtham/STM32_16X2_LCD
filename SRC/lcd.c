#include "lcd.h"


#define LCD_RS_HIGH GPIOA->ODR |= (1 << 5)  // PA5 for RS HIGH
#define LCD_RS_LOW  GPIOA->ODR &= ~(1 << 5) // PA5 for RS LOW

#define LCD_EN_HIGH GPIOA->ODR |= (1 << 4)  // PA4 for Enable HIGH
#define LCD_EN_LOW  GPIOA->ODR &= ~(1 << 4) // PA4 for Enable LOW

//=================================================================================================
//                             CONNECTIONS - 4bit mode
//		LCD_D4	-> 	PA0
//		LCD_D5	->	PA1
//		LCD_D6	->	PA2
//		LCD_D7	-> 	PA3
//		LCD_EN	->	PA4
//		LCD_RS	->	PA5
//==================================================================================================


void lcd_send(unsigned char data) {
  GPIOA -> ODR &= ~(0x0F);                  // Clear D4-D7 bits (PA1-PA4)
  GPIOA -> ODR |= ((data >> 4) & 0x0F);     // Set higher nibble to D4-D7
	
// Enable the LCD to latch the data
  LCD_EN_HIGH;
  delay_ms(1);
  LCD_EN_LOW;
  delay_ms(1);

  GPIOA -> ODR &= ~(0x0F);                 // Clear D4-D7 bits (PA1-PA4)
  GPIOA -> ODR |= (data & 0x0F);           // Set lower nibble to D4-D7

  LCD_EN_HIGH;
  delay_ms(1);
  LCD_EN_LOW;
  delay_ms(1);
}

// Sends a command to the LCD
void lcd_cmd(unsigned char cmd) {
  LCD_RS_LOW;
  lcd_send(cmd);
}

// Sends data (character) to the LCD
void lcd_data(unsigned char data) {
  LCD_RS_HIGH;
  lcd_send(data);
}

// Clears the LCD screen
void lcd_clear(void) {
  lcd_cmd(0x01);
}

// Displays a string on the LCD
void lcd_string(char * data) {
  while ( *data) {												//Loop through each character in the string
    lcd_data( *data++);
  }
}

// Sets the cursor position on the LCD
void lcd_put_cur(uint8_t row, uint8_t col) {

  if (row > 3 || col > 15) {
    return; 															// Invalid row or column
  }

  switch (row) {
  case 0:
    col |= 0x80;
    break;
  case 1:
    col |= 0xC0;
    break;
  }
  lcd_cmd(col);
}

// Initializes the LCD in 4-bit mode
void lcd_init(void) {

// PORTA CLOCK ENABLE
  RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;

// PA0-PA7 GENERAL PURPOSE OUTPUT PUSH PULL
  GPIOA -> CRL &= ~0xFFFFFFF;           //	CLEAR BITS
  GPIOA -> CRL |= 0x333333;             //  MODE:= OUTPUT, MAX SPEED (50Mhz) CNF:= PUSH PULL
  

  delay_ms(20);                         // Wait for LCD to power up

  lcd_cmd(0x03);
  delay_ms(5);
  lcd_cmd(0x03);
  delay_ms(1);
  lcd_cmd(0x03);
  delay_ms(1);
  lcd_cmd(0x02);                        // Initialize to 4-bit mode

  lcd_cmd(0x28);                        // 4-bit mode, 2 lines, 5x7 font
  lcd_cmd(0x0C);                        // Display ON, Cursor OFF
  lcd_cmd(0x06);                        // Increment cursor
  lcd_cmd(0x01);                        // Clear display
}