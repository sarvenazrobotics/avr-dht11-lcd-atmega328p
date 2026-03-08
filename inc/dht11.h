// dht11.h
#ifndef DHT11_H
#define DHT11_H

// DHT11 Pin definition (connected to PD2)
#define DHT11_PIN   2
#define DHT11_DDR   DDRD
#define DHT11_PORT  PORTD
#define DHT11_INPUT PIND

// Function prototypes
unsigned char dht11_read(unsigned char *temperature, unsigned char *humidity);

#endif