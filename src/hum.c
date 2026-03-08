#include <mega328p.h>
#include <delay.h>
#include "lcd.h"
#include "dht11.h"
#include "display_utils.h"

unsigned char temp, hum;
unsigned char result;
void main(void)
{
    

    // Initialize LCD
    lcd_init();
    lcd_clear();
    
    // Display startup message
    lcd_gotoxy(0, 0);
    lcd_puts("DHT11 Reader");
    lcd_gotoxy(0, 1);
    lcd_puts("Initializing...");
    delay_ms(2000);

    while(1)
    {
        result = dht11_read((unsigned char *)&temp, (unsigned char *)&hum);
        
        if(result == 0)
        {
            display_temp_hum(temp, hum);
        }
        else
        {
            display_error(result);
        }

        delay_ms(2000);
    }
}