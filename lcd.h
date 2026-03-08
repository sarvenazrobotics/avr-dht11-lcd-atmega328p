
// lcd.h
#ifndef LCD_H
#define LCD_H

// LCD Connections based on your image
// RS  -> PORTD.4
// RW  -> GND (connected to ground - always write mode)
// EN  -> PORTD.5
// D4  -> PORTD.6
// D5  -> PORTD.7
// D6  -> PORTB.0
// D7  -> PORTB.1

// Define LCD ports and pins
#define LCD_RS_PORT PORTD
#define LCD_RS_DDR  DDRD
#define LCD_RS_PIN  4

#define LCD_EN_PORT PORTD
#define LCD_EN_DDR  DDRD
#define LCD_EN_PIN  5

#define LCD_D4_PORT PORTD
#define LCD_D4_DDR  DDRD
#define LCD_D4_PIN  6

#define LCD_D5_PORT PORTD
#define LCD_D5_DDR  DDRD
#define LCD_D5_PIN  7

#define LCD_D6_PORT PORTB
#define LCD_D6_DDR  DDRB
#define LCD_D6_PIN  0

#define LCD_D7_PORT PORTB
#define LCD_D7_DDR  DDRB
#define LCD_D7_PIN  1


// Function prototypes - use lowercase 'l' to match your implementation
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_init(void);
void lcd_gotoxy(unsigned char x, unsigned char y);
void lcd_puts(char *str);
void lcd_clear(void);
void lcd_pulse_enable(void);
void lcd_send_nibble(unsigned char nibble);

#endif