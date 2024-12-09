# 16x2 LCD Interfacing with STM32F103C8 (Bare-Metal)

This repository contains the implementation of interfacing a 16x2 LCD with the STM32F103C8 microcontroller in bare-metal programming using the Keil IDE. The code provides a set of functions for initializing and controlling the LCD.

## Pin Configuration

The following pinout is used to connect the 16x2 LCD to the STM32F103C8:

| LCD Pin  | STM32 Pin |
|----------|-----------|
| LCD_D4   | PA0       |
| LCD_D5   | PA1       |
| LCD_D6   | PA2       |
| LCD_D7   | PA3       |
| LCD_EN   | PA4       |
| LCD_RS   | PA5       |

## Functions

### `void lcd_init(void)`
Initializes the GPIO pins and the LCD in 4-bit mode. This function must be called before using any other LCD functions.

### `void lcd_cmd(unsigned char cmd)`
Sends a command to the LCD. Used for configuring the LCD .
- **Parameters:**
  - `cmd`: Command to be sent to the LCD.

### `void lcd_data(unsigned char data)`
Sends a single character (data) to the LCD for display.
- **Parameters:**
  - `data`: Character to be displayed.

### `void lcd_clear(void)`
Clears the LCD display and resets the cursor to the home position.

### `void lcd_put_cur(uint8_t row, uint8_t col)`
Positions the cursor at a specified row and column on the LCD.
- **Parameters:**
  - `row`: Row number (0 or 1).
  - `col`: Column number (0 to 15).

### `void lcd_string(char *data)`
Displays a string on the LCD starting from the current cursor position.
- **Parameters:**
  - `data`: Pointer to the null-terminated string to display.

## Usage
1. Configure the pins as per the pinout table above in your project.
2. Include the LCD driver source file in your Keil project.
3. Call `lcd_init()` to initialize the LCD.
4. Use the provided functions to control and display data on the LCD.
