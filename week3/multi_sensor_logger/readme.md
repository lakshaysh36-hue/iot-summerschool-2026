# Multi Sensor Data Logger using Arduino

## Project Description
This project simulates a mini sensor monitoring system using Arduino. It simultaneously reads temperature, humidity, light intensity, and distance values, then displays the readings in a structured format on the Serial Monitor every 5 seconds.

Since Tinkercad does not provide a DHT11 sensor, a TMP36 temperature sensor and a potentiometer are used to simulate temperature and humidity respectively.

## Features
- Reads temperature using TMP36 sensor.
- Simulates humidity using a potentiometer.
- Reads light intensity using an LDR.
- Measures distance using an HC-SR04 ultrasonic sensor.
- Displays all sensor readings every 5 seconds.
- Light level is shown as both percentage and status (Bright, Normal, Dark).
- Outputs data in a structured log format.

## Components Used
- Arduino Uno
- TMP36 Temperature Sensor
- LDR (Light Dependent Resistor)
- 10kΩ Potentiometer (Humidity Simulation)
- HC-SR04 Ultrasonic Sensor
- 10kΩ Resistor (for LDR voltage divider)
- Breadboard
- Jumper Wires

## Pin Connections

| Component | Arduino Pin |
|-----------|-------------|
| TMP36 Output | A1 |
| LDR Output | A0 |
| Potentiometer (Humidity) | A2 |
| HC-SR04 Trigger | D8 |
| HC-SR04 Echo | D9 |

### Power Connections

| Component | Connection |
|-----------|------------|
| TMP36 Left Pin | 5V |
| TMP36 Right Pin | GND |
| Potentiometer Left Pin | 5V |
| Potentiometer Right Pin | GND |
| HC-SR04 VCC | 5V |
| HC-SR04 GND | GND |
| LDR | Voltage Divider with 10kΩ Resistor |

## Working
1. The TMP36 measures the ambient temperature.
2. The potentiometer simulates humidity values from 0–100%.
3. The LDR measures ambient light intensity and converts it to a percentage.
4. The HC-SR04 measures the distance to nearby objects.
5. Every 5 seconds, the Arduino prints all sensor readings in a structured format on the Serial Monitor.

## Example Serial Monitor Output

```
=== SENSOR LOG ===
Time      : 5000 ms
Temp      : 28.5 C | Humidity: 65%
Light     : 73% (Bright)
Distance  : 42 cm
==================

=== SENSOR LOG ===
Time      : 10000 ms
Temp      : 29.1 C | Humidity: 70%
Light     : 45% (Normal)
Distance  : 35 cm
==================
```

## Files Included
- `sensor_logger.ino` – Arduino source code
- `sensor_log.txt` – 20 lines of captured Serial Monitor output

## Software Used
- Arduino IDE
- Tinkercad Circuits (Simulation)

## Note
The original assignment specifies a **DHT11** sensor for temperature and humidity. As Tinkercad does not include a DHT11 sensor, the following alternatives were used:
- **TMP36** → Temperature
- **Potentiometer** → Humidity simulation

## Author
Lakshay Sharma
