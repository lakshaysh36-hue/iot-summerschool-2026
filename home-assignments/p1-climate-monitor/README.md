# Project 1: Smart Room Climate Monitor

## Project Overview

This project is a smart room climate monitoring system built using an ESP32 and DHT11 temperature and humidity sensor.

The system continuously measures temperature and humidity, displays the readings on an OLED display, and provides visual and audio alerts when the room becomes too hot or humid.

## Components Used

- ESP32 Dev Board
- DHT11 Temperature and Humidity Sensor
- 0.96-inch OLED Display (SSD1306 I2C)
- Active 3-pin Buzzer Module
- Red LED
- Green LED
- 220Ω Resistors
- Breadboard
- Jumper Wires
- USB Cable

## Wiring

### DHT11

| DHT11 Pin | ESP32 |
|---|---|
| VCC (+) | 3.3V |
| DATA | GPIO4 |
| GND (-) | GND |

### OLED SSD1306

| OLED Pin | ESP32 |
|---|---|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO21 |
| SCL | GPIO22 |

### Red LED

GPIO25 → 220Ω resistor → LED positive leg

LED negative leg → GND

### Green LED

GPIO26 → 220Ω resistor → LED positive leg

LED negative leg → GND

### 3-Pin Active Buzzer

| Buzzer Pin | ESP32 |
|---|---|
| S / I/O | GPIO27 |
| + / VCC | 3.3V |
| - / GND | GND |

## Software and Libraries

- Arduino IDE
- ESP32 Board Package
- DHTesp Library
- Adafruit SSD1306 Library
- Adafruit GFX Library

## Working Principle

The DHT11 sensor measures the room temperature and humidity every 2 seconds.

The OLED displays the current temperature, humidity, and comfort status.

The system enters DANGER mode when:

- Temperature exceeds 38°C, OR
- Humidity exceeds 80%

During DANGER mode:

- Red LED turns ON
- Green LED turns OFF
- Buzzer sounds for 1 second
- OLED displays DANGER

During normal conditions, the Green LED remains ON.

## Comfort Status

The system displays one of the following statuses:

- COOL
- COMFORT
- HOT
- DANGER

## Serial Monitor Output

The system logs readings in CSV format every 5 seconds:

millis,temperature,humidity,status

Example:

25000,31.2,82.0,DANGER

## Expected Output

The OLED displays:

Temperature: 31.2°C
Humidity: 82%
Status: DANGER

When humidity exceeds 80%, the red LED and buzzer are activated.

## Demo Video

Google Drive Demo Video:
https://drive.google.com/file/d/14s27s8PyV1y9gnSSWWv24Ov6Avh3aKD1/view?usp=drivesdk


## Project Status

Completed and tested successfully.
