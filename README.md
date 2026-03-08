##  Table of Contents

-  [Overview](#overview)
-  [Features](#features)
-  [Hardware Requirements](#hardware-requirements)
-  [Wiring Diagram](#wiring-diagram)
-  [How It Works](#how-it-works)
-  [Usage](#usage)
- [Code Structure](#code-structure)
- [Troubleshooting](#troubleshooting)
- [Summary](#summary)
- [Project Author](#project-author)

## Overview
This project is a temperature and humidity monitoring system built around the ATmega328P microcontroller. It uses a DHT11 sensor to capture environmental data and displays the readings on a 16x2 LCD screen. The code is written in C using CodeVisionAVR and features a modular architecture with separate libraries for LCD control, DHT11 communication, and display utilities, making it ideal for learning embedded systems programming and sensor interfacing.

## Features
- Real-time Monitoring: Reads temperature (°C) and humidity (%) every 2 seconds

- 16x2 LCD Display: Clear visual output with 4-bit mode operation to minimize pin usage

- Error Handling: Comprehensive error detection with specific error codes displayed on LCD

- Modular Design: Separated code into reusable libraries (LCD, DHT11, display utilities)

- Pull-up Resistor Support: Includes proper timing for DHT11 communication with external pull-up

- CodeVisionAVR Compatible: Full project structure ready for compilation in CodeVisionAVR IDE

## Hardware Requirement

- Microcontroller: ATmega328P (Arduino Uno compatible)

- Sensor: DHT11 temperature and humidity sensor

- Display: 16x2 character LCD (HD44780 compatible)

- Resistor: 4.7kΩ pull-up resistor for DHT11 data line

- Power Supply: 5V DC regulated power supply

- Additional Components: Breadboard, jumper wires, AVR programmer (USBasp or similar)

- Optional: Crystal oscillator (16MHz) and capacitors if not using internal oscillator

## Wiring Diagram
```
LCD Connections (4-bit mode):
  Pin 4 (RS)  → PORTD.4
  Pin 5 (RW)  → GND (ground - always write mode)
  Pin 6 (EN)  → PORTD.5
  Pin 11 (D4) → PORTD.6
  Pin 12 (D5) → PORTD.7
  Pin 13 (D6) → PORTB.0
  Pin 14 (D7) → PORTB.1
  Pin 1 (VSS) → GND
  Pin 2 (VDD) → +5V
  Pin 3 (VEE) → Contrast (potentiometer to GND)
  Pin 15 (LED+) → +5V through resistor
  Pin 16 (LED-) → GND

DHT11 Connections:
  Pin 1 (VCC)  → +5V
  Pin 2 (DATA) → PD2 with 4.7kΩ pull-up to +5V
  Pin 4 (GND)  → GND
```
## How It Works
The system operates by first initializing the LCD in 4-bit mode and configuring the DHT11 data pin. The DHT11 sensor communicates using a single-wire protocol: the microcontroller sends a start signal by pulling the data line low for 18ms, then releases it. The sensor responds with a 40-bit data packet containing humidity (16 bits), temperature (16 bits), and an 8-bit checksum. The microcontroller reads these bits by measuring pulse durations—a short pulse (26-28µs) represents logic 0, while a longer pulse (70µs) represents logic 1. After verifying the checksum, the valid temperature and humidity values are formatted and displayed on the LCD. If any step fails, appropriate error messages appear on the screen.

## Code Structure
```
Project Root/
│
├── 📁 header/                 # Header files with function declarations
│   ├── lcd.h                 # LCD function prototypes and pin definitions
│   ├── dht11.h               # DHT11 function prototypes and pin definitions
│   └── display_utils.h       # Display utility function prototypes
│
├── 📁 src/                    # Source files with function implementations
│   ├── main.c                # Main program loop and initialization
│   ├── lcd.c                 # LCD control functions (init, command, data, etc.)
│   ├── dht11.c               # DHT11 communication protocol implementation
│   └── display_utils.c       # Display formatting and error message functions
│
└── 📄 dht11_lcd.prj           # CodeVisionAVR project file
```

## Troubleshooting
- LCD shows nothing: Check contrast potentiometer, verify power connections, and ensure all LCD pins are correctly wired

- DHT11 Error: No Response: Verify the 4.7kΩ pull-up resistor is connected, check DATA pin connection to PD2, and ensure sensor is powered with 5V

- DHT11 Error: Checksum Error: This indicates data corruption—check for loose connections, add a decoupling capacitor (100nF) near the sensor, and ensure no nearby electrical noise sources

- LCD shows garbage characters: Clean the LCD data lines by adding pull-up resistors (10kΩ) to +5V on D4-D7, and verify timing delays in the initialization sequence

- Intermittent readings: Add a 100nF capacitor between VCC and GND near the DHT11, and ensure the delay after the start signal is exactly 18ms

- Temperature reads 0°C: The sensor may be damaged or the checksum verification is failing—check for proper timing in the bit reading loop

## Summary
This DHT11 LCD monitoring project successfully demonstrates how to interface a digital temperature and humidity sensor with an AVR microcontroller and display data on an LCD screen. The modular code structure separates hardware-specific drivers from application logic, making it easy to adapt for different microcontrollers or display types. Key learning outcomes include understanding single-wire communication protocols, implementing precise software timing delays, handling sensor data validation with checksums, and creating reusable library modules. The project serves as a solid foundation for more advanced environmental monitoring systems, data loggers, or home automation projects.

## Project Author
**Sarvenaz Ashoori**

GitHub: @sarvenazrobotics

Email: sarvenazrobotics@gmail.com

LinkedIn: **Sarvenaz Ashoori**
