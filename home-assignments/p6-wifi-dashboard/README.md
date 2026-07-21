# Project 6: Wi-Fi Weather Dashboard

## Overview

This project is a local IoT weather monitoring system built using an ESP32.

The ESP32 collects environmental data from multiple sensors and hosts a live weather dashboard over a local Wi-Fi network. The dashboard can be accessed through a web browser by entering the ESP32's local IP address.

No cloud platform or subscription is required.

The system monitors:

- Temperature
- Humidity
- Atmospheric Pressure
- Altitude
- Light Status
- Wi-Fi SSID
- ESP32 Local IP Address

---

## Components Used

- ESP32 Dev Board
- DHT11 Temperature and Humidity Sensor
- BMP280 Pressure and Altitude Sensor
- 3-Pin LDR Sensor Module
- 0.96-inch OLED Display (I2C)
- Breadboard
- Jumper Wires

---

# Modification Due to Component Unavailability

The original project specification required a bare LDR and a 10kΩ resistor connected as an analog voltage divider.

The original setup would be:

    3.3V
      |
     LDR
      |
      |------ GPIO34 (Analog Input)
      |
    10kΩ Resistor
      |
     GND

This setup would allow the ESP32 to read a continuous analog light level and convert it into a percentage from 0–100%.

However, a bare LDR and the required analog voltage-divider setup were unavailable. The available component was a 3-pin LDR sensor module with:

- VCC
- GND
- DO (Digital Output)

Therefore, the light sensing part of the project was modified.

### Original Requirement

    Bare LDR + 10kΩ Resistor
              ↓
       Analog Voltage Divider
              ↓
          ESP32 GPIO34
              ↓
        Light Level: 0–100%

### Modified Implementation

    3-Pin LDR Module
              ↓
       DO → ESP32 GPIO35
              ↓
      Digital Light Detection
              ↓
       Light Status: BRIGHT/DARK

The 3-pin LDR module contains its own sensor circuit and comparator. Its onboard potentiometer can be used to adjust the threshold at which the module changes between bright and dark.

Since the available module provides only a digital output and does not provide an analog output pin, the light reading was modified from a numerical percentage to a digital BRIGHT/DARK status.

This modification was made due to the unavailability of the exact component specified in the assignment.

---

# Wiring Connections

## DHT11 Sensor

| DHT11 Pin | ESP32 Pin |
|---|---|
| VCC | 3.3V |
| GND | GND |
| DATA | GPIO4 |

---

## BMP280 Sensor

| BMP280 Pin | ESP32 Pin |
|---|---|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO21 |
| SCL | GPIO22 |

---

## OLED Display

| OLED Pin | ESP32 Pin |
|---|---|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO21 |
| SCL | GPIO22 |

The OLED and BMP280 share the same I2C bus.

GPIO21 is used for SDA and GPIO22 is used for SCL.

I2C allows multiple devices to use the same SDA and SCL lines as long as they have different I2C addresses.

---

## 3-Pin LDR Sensor Module

| LDR Module Pin | ESP32 Pin |
|---|---|
| VCC | 3.3V |
| GND | GND |
| DO | GPIO35 |

The 10kΩ resistor is not used because the available LDR module already contains its own internal circuit and threshold comparator.

The LDR module provides a digital output:

- BRIGHT
- DARK

The small onboard potentiometer is used to adjust the detection threshold.

---

# Libraries Used

The following libraries are required:

- DHT sensor library by Adafruit
- Adafruit Unified Sensor
- Adafruit BMP280 Library
- Adafruit GFX Library
- Adafruit SSD1306

The following libraries are included with the ESP32 Arduino core:

```cpp
#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
