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
