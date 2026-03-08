// lcd.c
#include <mega328p.h>
#include <delay.h>
#include "lcd.h"

void lcd_pulse_enable(void)
{
    LCD_EN_PORT |= (1 << LCD_EN_PIN);
    delay_us(2);
    LCD_EN_PORT &= ~(1 << LCD_EN_PIN);
    delay_us(2);
}

void lcd_send_nibble(unsigned char nibble)
{
    // Set D4 (PORTD.6)
    if(nibble & 0x10)
        LCD_D4_PORT |= (1 << LCD_D4_PIN);
    else
        LCD_D4_PORT &= ~(1 << LCD_D4_PIN);
    
    // Set D5 (PORTD.7)
    if(nibble & 0x20)
        LCD_D5_PORT |= (1 << LCD_D5_PIN);
    else
        LCD_D5_PORT &= ~(1 << LCD_D5_PIN);
    
    // Set D6 (PORTB.0)
    if(nibble & 0x40)
        LCD_D6_PORT |= (1 << LCD_D6_PIN);
    else
        LCD_D6_PORT &= ~(1 << LCD_D6_PIN);
    
    // Set D7 (PORTB.1)
    if(nibble & 0x80)
        LCD_D7_PORT |= (1 << LCD_D7_PIN);
    else
        LCD_D7_PORT &= ~(1 << LCD_D7_PIN);
    
    lcd_pulse_enable();
}

void lcd_cmd(unsigned char cmd)
{
    LCD_RS_PORT &= ~(1 << LCD_RS_PIN);  // RS = 0 for command
    lcd_send_nibble(cmd & 0xF0);         // Send upper nibble
    lcd_send_nibble((cmd << 4) & 0xF0);  // Send lower nibble
    delay_ms(2);
}

void lcd_data(unsigned char data)
{
    LCD_RS_PORT |= (1 << LCD_RS_PIN);    // RS = 1 for data
    lcd_send_nibble(data & 0xF0);         // Send upper nibble
    lcd_send_nibble((data << 4) & 0xF0);  // Send lower nibble
    delay_us(50);
}

void lcd_init(void)
{
    // Configure all LCD pins as outputs
    LCD_RS_DDR |= (1 << LCD_RS_PIN);
    LCD_EN_DDR |= (1 << LCD_EN_PIN);
    LCD_D4_DDR |= (1 << LCD_D4_PIN);
    LCD_D5_DDR |= (1 << LCD_D5_PIN);
    LCD_D6_DDR |= (1 << LCD_D6_PIN);
    LCD_D7_DDR |= (1 << LCD_D7_PIN);
    
    // Initialize all pins to low
    LCD_RS_PORT &= ~(1 << LCD_RS_PIN);
    LCD_EN_PORT &= ~(1 << LCD_EN_PIN);
    LCD_D4_PORT &= ~(1 << LCD_D4_PIN);
    LCD_D5_PORT &= ~(1 << LCD_D5_PIN);
    LCD_D6_PORT &= ~(1 << LCD_D6_PIN);
    LCD_D7_PORT &= ~(1 << LCD_D7_PIN);
    
    delay_ms(20);  // Wait for LCD to power up
    
    // Initialization sequence for 4-bit mode
    lcd_send_nibble(0x30);
    delay_ms(5);
    lcd_send_nibble(0x30);
    delay_us(150);
    lcd_send_nibble(0x30);
    delay_ms(5);
    lcd_send_nibble(0x20);  // Set to 4-bit mode
    delay_ms(5);
    
    // Configure LCD
    lcd_cmd(0x28);  // 4-bit, 2 lines, 5x7 dots
    delay_ms(1);
    lcd_cmd(0x0C);  // Display on, cursor off
    delay_ms(1);
    lcd_cmd(0x01);  // Clear display
    delay_ms(2);
    lcd_cmd(0x06);  // Entry mode: increment, no shift
    delay_ms(1);
}

void lcd_gotoxy(unsigned char x, unsigned char y)
{
    unsigned char address;
    
    if(y == 0)
        address = 0x80 + x;
    else
        address = 0xC0 + x;
    
    lcd_cmd(address);
}

void lcd_puts(char *str)
{
    while(*str)
    {
        lcd_data(*str++);
    }
}

void lcd_clear(void)
{
    lcd_cmd(0x01);
    delay_ms(2);
}