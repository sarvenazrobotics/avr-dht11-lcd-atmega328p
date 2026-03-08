// display_utils.c
#include <mega328p.h>
#include <stdio.h>
#include "lcd.h"
#include "display_utils.h"

void display_temp_hum(unsigned char temp, unsigned char hum)
{
    char buffer[17];
    
    // Clear both lines first
    lcd_gotoxy(0, 0);
    lcd_puts("                ");  // 16 spaces
    
    lcd_gotoxy(0, 1);
    lcd_puts("                ");  // 16 spaces
    
    // Display temperature
    lcd_gotoxy(0, 0);
    sprintf(buffer, "Temp:%3d C", temp);
    lcd_puts(buffer);
    
    // Display humidity
    lcd_gotoxy(0, 1);
    sprintf(buffer, "Hum:%3d %%", hum);
    lcd_puts(buffer);
}

void display_error(unsigned char error_code)
{
    lcd_gotoxy(0, 0);
    lcd_puts("DHT11 Error     ");
    
    lcd_gotoxy(0, 1);
    switch(error_code)
    {
        case 1: lcd_puts("No Response     "); break;
        case 2: lcd_puts("Init timeout    "); break;
        case 3: lcd_puts("Data timeout    "); break;
        case 4: lcd_puts("Read timeout    "); break;
        case 5: lcd_puts("Bit timeout     "); break;
        case 6: lcd_puts("Checksum error  "); break;
        default: lcd_puts("Unknown error   "); break;
    }
}