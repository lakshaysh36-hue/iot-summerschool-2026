# Bluetooth Home Light Controller

## Project 5 - IoT Summer School 2026

A Bluetooth-controlled home light system built using an ESP32. The system allows two lights to be controlled wirelessly from an Android phone using Bluetooth Classic. LEDs are used to simulate household lights.

The system also supports physical manual control using push buttons and provides a short buzzer beep as confirmation for valid commands.

---

## Features

- Bluetooth control using ESP32 Classic Bluetooth SPP
- Control of two independent lights
- Two-channel relay module
- Android phone control using a Bluetooth terminal app
- Manual override buttons
- Buzzer confirmation for valid commands
- Bluetooth connection indicator using the ESP32 built-in LED
- Automatic shutoff after 30 minutes of inactivity

---
DRIVE LINK - 
## Components Used

- ESP32 Dev Board
- 2-Channel 5V Relay Module with Optocoupler
- 2 LEDs
- 2 × 220Ω resistors
- 2-pin active buzzer
- Push button
- 10kΩ resistor
- Breadboard
- Jumper wires
- USB cable

---

## Pin Connections

### Relay Control Connections

| Relay Pin | ESP32 Pin |
|---|---|
| VCC | V5 |
| GND | GND |
| IN1 | GPIO26 |
| IN2 | GPIO27 |

### Relay Output Connections

#### Light 1

```text
V5 → COM1
NO1 → 220Ω resistor → LED 1 positive leg
LED 1 negative leg → GND
