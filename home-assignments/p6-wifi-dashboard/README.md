# Project 6: Wi-Fi Weather Dashboard

## Overview

This project is a local IoT weather monitoring system built using an ESP32.

The ESP32 collects environmental data from multiple sensors and hosts a live weather dashboard over a local Wi-Fi network.

The dashboard can be accessed through a web browser by entering the ESP32's local IP address.

No cloud platform or subscription is required.

The system monitors:

- Temperature
- Humidity
- Atmospheric Pressure
- Altitude
- Light Level
- Wi-Fi SSID
- ESP32 Local IP Address

---

# Components Used

- ESP32 Dev Board
- DHT11 Temperature and Humidity Sensor
- BMP280 Pressure and Altitude Sensor
- Bare LDR (Light Dependent Resistor)
- 10kΩ Resistor
- 0.96-inch OLED Display (I2C)
- Breadboard
- Jumper Wires

---

# System Architecture

```text
             ┌─────────────────────┐
             │       ESP32          │
             │                     │
             │  ┌───────────────┐  │
             │  │ DHT11         │  │
             │  │ Temp/Humidity │  │
             │  └───────────────┘  │
             │                     │
             │  ┌───────────────┐  │
             │  │ BMP280        │  │
             │  │ Pressure      │  │
             │  │ Altitude      │  │
             │  └───────────────┘  │
             │                     │
             │  ┌───────────────┐  │
             │  │ LDR + 10kΩ    │  │
             │  │ Light Level   │  │
             │  └───────────────┘  │
             │                     │
             │  ┌───────────────┐  │
             │  │ OLED Display  │  │
             │  └───────────────┘  │
             │                     │
             │       Wi-Fi         │
             └──────────┬──────────┘
                        │
                        ▼
             ┌─────────────────────┐
             │  Local Web Dashboard│
             │  Browser/Phone      │
             └─────────────────────┘
