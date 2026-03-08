// dht11.c
#include <mega328p.h>
#include <delay.h>
#include "dht11.h"

unsigned char dht11_read(unsigned char *temperature, unsigned char *humidity)
{
    unsigned char i, j;
    unsigned char data[5] = {0, 0, 0, 0, 0};
    unsigned int timeout = 0;

    // Send start signal to DHT11
    DHT11_DDR |= (1 << DHT11_PIN);      // Set as output
    DHT11_PORT &= ~(1 << DHT11_PIN);    // Pull low
    delay_ms(18);                        // Wait at least 18ms
    
    DHT11_PORT |= (1 << DHT11_PIN);     // Pull high
    delay_us(30);                        // Wait 20-40us
    DHT11_DDR &= ~(1 << DHT11_PIN);     // Set as input
    delay_us(10);                        

    // Check for DHT11 response
    timeout = 0;
    while ((DHT11_INPUT & (1 << DHT11_PIN)))  // Wait for LOW
    {
        delay_us(1);
        timeout++;
        if(timeout > 100) return 1;  // Timeout error
    }
    
    timeout = 0;
    while (!(DHT11_INPUT & (1 << DHT11_PIN))) // Wait for HIGH
    {
        delay_us(1);
        timeout++;
        if(timeout > 100) return 2;  // Timeout error
    }
    
    timeout = 0;
    while ((DHT11_INPUT & (1 << DHT11_PIN)))  // Wait for LOW (data start)
    {
        delay_us(1);
        timeout++;
        if(timeout > 100) return 3;  // Timeout error
    }

    // Read 40 bits (5 bytes) of data
    for(j = 0; j < 5; j++)
    {
        for(i = 0; i < 8; i++)
        {
            // Wait for pin to go high (start of bit transmission)
            timeout = 0;
            while (!(DHT11_INPUT & (1 << DHT11_PIN)))
            {
                delay_us(1);
                timeout++;
                if(timeout > 100) return 4;
            }
            
            // Wait 40us to sample (middle of bit)
            delay_us(40);
            
            // If still high after 40us, it's a '1', else it's a '0'
            if (DHT11_INPUT & (1 << DHT11_PIN))
                data[j] |= (1 << (7 - i));  // Set bit as '1'
            
            // Wait for pin to go low before next bit
            timeout = 0;
            while (DHT11_INPUT & (1 << DHT11_PIN))
            {
                delay_us(1);
                timeout++;
                if(timeout > 100) return 5;
            }
        }
    }

    // Verify checksum
    if((data[0] + data[1] + data[2] + data[3]) == data[4])
    {
        *humidity = data[0];
        *temperature = data[2];
        return 0;  // Success
    }
    
    return 6;  // Checksum error
}