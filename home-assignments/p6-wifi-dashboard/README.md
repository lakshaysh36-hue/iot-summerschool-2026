# Project 6: Wi-Fi Weather Dashboard
DRIVE LINK-https://drive.google.com/file/d/1_3uDe-TcyDTDJjWvdOtNRlx7OBlEeILI/view?usp=sharing
## Components Used
//done on both mobile and laptop
* ESP32 Development Board
* DHT11 Temperature and Humidity Sensor
* BMP280 Barometric Pressure Sensor
* LDR Light Sensor Module
* Breadboard
* Jumper Wires
* USB Cable
* Wi-Fi Network

## Wiring Summary

### DHT11 → ESP32

| DHT11 Pin | ESP32  |
| --------- | ------ |
| VCC       | 3.3V   |
| GND       | GND    |
| DATA      | GPIO 4 |

### BMP280 → ESP32 (I2C)

| BMP280 Pin | ESP32   |
| ---------- | ------- |
| VCC        | 3.3V    |
| GND        | GND     |
| SDA        | GPIO 21 |
| SCL        | GPIO 22 |

### LDR Module → ESP32

| LDR Pin | ESP32                             |
| ------- | --------------------------------- |
| VCC     | 3.3V                              |
| GND     | GND                               |
| AO      | Analog input pin used in the code |

> The LDR module's analog output is used to measure the surrounding light level.

## How to Run

1. Connect the DHT11, BMP280, and LDR sensor to the ESP32 according to the wiring summary.
2. Install the required libraries in Arduino IDE:

   * `DHT sensor library`
   * `Adafruit Unified Sensor`
   * `Adafruit BMP280 Library`
3. Enter the correct Wi-Fi network name and password in the code.
4. Connect the ESP32 to the computer using USB.
5. Select:

   * **Board:** ESP32 development board
   * **Port:** Correct ESP32 COM port
6. Upload the code.
7. Open the Serial Monitor at the baud rate specified in the program.
8. Note the IP address printed by the ESP32 after connecting to Wi-Fi.
9. Open that IP address in a web browser connected to the same Wi-Fi network.
10. View the live weather dashboard displaying:

    * Temperature
    * Humidity
    * Atmospheric pressure
    * Approximate altitude
    * Light condition

## Expected Output

### Serial Monitor

After connecting to Wi-Fi, the ESP32 prints sensor readings similar to:

```text id="b6d8d8"
WiFi connected
IP Address: 192.168.x.x

Temperature: 29.70 C
Humidity: 83.60 %
Pressure: 1206.35 hPa
Altitude: 415.59 m
Light: BRIGHT
```

The exact values depend on the environment and sensor readings.

### Web Dashboard

When the IP address is opened in a browser, the dashboard displays updated environmental data.

Example:

```text id="7s6n8h"
Temperature: 29.7 °C
Humidity: 83.6 %
Pressure: 1206.35 hPa
Altitude: 415.59 m
Light: BRIGHT
```

The values update automatically as the sensors detect changes.

### Sensor Behavior

#### Temperature and Humidity

The DHT11 provides:

* Temperature in degrees Celsius
* Relative humidity percentage

#### Atmospheric Pressure

The BMP280 provides:

* Atmospheric pressure in hPa
* Approximate altitude calculated from pressure

#### Light Level

The LDR measures ambient light conditions.

Example:

```text id="2af5qz"
Light: BRIGHT
```

or:

```text id="uk8h2f"
Light: DARK
```

depending on the surrounding light level.

## Project Working

The Wi-Fi Weather Dashboard combines multiple sensors with the ESP32's Wi-Fi capability. The DHT11 measures temperature and humidity, the BMP280 measures atmospheric pressure and estimates altitude, and the LDR detects the surrounding light level. The ESP32 processes the sensor readings and hosts a web dashboard that allows the data to be monitored remotely from a browser on the same Wi-Fi network.
