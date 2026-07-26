# Project 8: IoT Pressure & Altitude Logger

## Overview

This project is an IoT pressure and altitude logging system built using an ESP32, BMP280 pressure sensor, OLED display, potentiometer, and LEDs.

The system measures atmospheric pressure and temperature, calculates altitude-related values, tracks pressure changes over time, and determines whether the pressure trend is **Rising**, **Falling**, or **Stable**.

A 24-reading circular buffer is used to store recent pressure readings. For demonstration purposes, the system takes a new reading every 30 seconds instead of every hour.

---

## Components Used

* ESP32 Development Board
* BMP280 Pressure and Temperature Sensor
* 0.96-inch I2C OLED Display (SSD1306)
* 10 kΩ Potentiometer
* Green LED
* Red LED
* 220 Ω Resistors × 2
* Breadboard
* Jumper Wires

---

## Wiring Summary

### BMP280 Sensor

| BMP280 Pin | ESP32 Pin |
| ---------- | --------- |
| VCC        | 3.3V      |
| GND        | GND       |
| SDA        | GPIO 21   |
| SCL        | GPIO 22   |

**I2C Address:** `0x76`

> The BMP280 is powered using 3.3V. The sensor should not be connected to 5V.

---

### OLED Display

| OLED Pin | ESP32 Pin |
| -------- | --------- |
| VCC      | 3.3V      |
| GND      | GND       |
| SDA      | GPIO 21   |
| SCL      | GPIO 22   |

**I2C Address:** `0x3C`

The BMP280 and OLED share the same I2C bus because they have different I2C addresses.

---

### Potentiometer

| Potentiometer Connection | ESP32   |
| ------------------------ | ------- |
| One outer pin            | 3.3V    |
| Middle pin (wiper)       | GPIO 34 |
| Other outer pin          | GND     |

The potentiometer is used to set a simulated local altitude between approximately **0 m and 2000 m**.

---

### Green LED

```text
ESP32 GPIO 25
      ↓
   220 Ω Resistor
      ↓
Green LED long leg (+)

Green LED short leg (-)
      ↓
     GND
```

The green LED indicates **Stable or Rising pressure**.

---

### Red LED

```text
ESP32 GPIO 26
      ↓
   220 Ω Resistor
      ↓
Red LED long leg (+)

Red LED short leg (-)
      ↓
     GND
```

The red LED indicates **Falling pressure**.

---

## How to Run

### 1. Install the Required Libraries

Install these libraries through the Arduino IDE Library Manager:

* Adafruit GFX Library
* Adafruit SSD1306
* Adafruit BMP280 Library
* Adafruit Unified Sensor

---

### 2. Connect the Hardware

Connect the BMP280, OLED, potentiometer, and LEDs according to the wiring table above.

The I2C connections are:

```text
SDA → GPIO 21
SCL → GPIO 22
```

---

### 3. Upload the Code

1. Connect the ESP32 to the computer.
2. Select the correct ESP32 board in Arduino IDE.
3. Select the correct COM port.
4. Upload the program.

The code uses the confirmed I2C addresses:

```text
OLED  → 0x3C
BMP280 → 0x76
```

---

### 4. Open Serial Monitor

Set the Serial Monitor baud rate to:

```text
115200 baud
```

The system takes a pressure reading every **30 seconds**.

The OLED display automatically switches between two pages every **5 seconds**.

---

## Expected Output

### Serial Monitor

The Serial Monitor displays values similar to:

```text
----------------------------------------
NEW PRESSURE READING
----------------------------------------
Pressure       : 1008.42 hPa
Temperature    : 29.31 C
Altitude       : 850.00 m
Sea-Level P    : 1112.52 hPa
Trend          : STABLE
Reading Number : 1/24
----------------------------------------
```

After additional readings, the trend may become:

```text
Trend: RISING
```

or:

```text
Trend: FALLING
```

depending on the pressure difference.

---

### OLED Page 1: Sensor Data

The first OLED page displays:

```text
PRESSURE LOGGER

P: 1008.4 hPa
T: 29.3 C
Alt: 850 m
SLP: 1112.5 hPa
```

It shows:

* Atmospheric pressure
* Temperature
* Potentiometer-set altitude
* Calculated sea-level pressure

---

### OLED Page 2: Pressure Trend

The second page displays the pressure trend:

```text
PRESSURE TREND

^ RISING

Readings: 10/24
```

The trend states are:

* `^ RISING` — pressure increasing
* `v FALLING` — pressure decreasing
* `-> STABLE` — pressure change is small

---

## Pressure Trend Calculation

The project stores the last **24 pressure readings** in an array.

The newest pressure value is compared with the oldest stored value:

```text
Difference = Newest Pressure - Oldest Pressure
```

The assignment threshold is:

```text
Difference > +50 Pa  → RISING
Difference < -50 Pa  → FALLING
Otherwise             → STABLE
```

Because the program stores pressure in hPa:

```text
50 Pa = 0.5 hPa
```

Therefore, the code uses:

```text
Difference > +0.5 hPa → RISING
Difference < -0.5 hPa → FALLING
```

---

## Circular Buffer

The system stores up to 24 pressure readings:

```text
pressureLog[24]
```

When the array becomes full, the next reading replaces the oldest reading.

For example:

```text
Reading 1  → Index 0
Reading 2  → Index 1
...
Reading 24 → Index 23
Reading 25 → Index 0 again
```

This allows the system to continuously maintain the latest 24 pressure measurements without requiring unlimited memory.

---

# Sea-Level Pressure Formula

The project uses the following formula to calculate pressure adjusted to sea level:

```text
P₀ = P / (1 - h / 44330)⁵·²⁵⁵
```

In the code:

```cpp
P0 = P / pow(1 - altitude / 44330.0, 5.255);
```

Where:

* `P₀` = calculated sea-level pressure
* `P` = measured atmospheric pressure
* `h` = altitude in metres
* `44330` = standard atmospheric height constant
* `5.255` = standard atmospheric exponent

---

## How Altitude Affects the Reading

Atmospheric pressure decreases as altitude increases because there is less air above a location.

For example:

```text
At lower altitude:
Pressure is generally higher
```

```text
At higher altitude:
Pressure is generally lower
```

The BMP280 measures the local pressure at the sensor's location. The system uses the altitude value set by the potentiometer to estimate what the pressure would be at sea level.

Therefore, when the potentiometer increases the altitude:

```text
Altitude increases
        ↓
Local measured pressure is compensated
        ↓
Sea-level pressure is recalculated
```

This allows pressure readings from different elevations to be compared more meaningfully.

---

## LED Indicators

| Pressure Trend | LED       |
| -------------- | --------- |
| Rising         | Green LED |
| Stable         | Green LED |
| Falling        | Red LED   |

A falling pressure trend may indicate changing weather conditions and can sometimes be associated with a higher possibility of rain.

---

# MQTT Bonus Challenge

Pressure and trend data can also be published to a public MQTT broker.

### Broker

```text
broker.hivemq.com
```

### Port

```text
1883
```

### Topic

```text
iitjammu/lakshay/pressure
```

### Example MQTT Payload

```json
{
  "pressure": 1008.42,
  "trend": "RISING"
}
```

The message can be published using the Mosquitto command-line tool:

```cmd
"C:\Program Files\Mosquitto\mosquitto_pub.exe" -h broker.hivemq.com -p 1883 -t "iitjammu/lakshay/pressure" -m "{\"pressure\":1008.42,\"trend\":\"RISING\"}"
```

The message can then be viewed using MQTT Explorer by subscribing to:

```text
iitjammu/lakshay/pressure
```

---

## Project Demonstration

The demonstration should show:

1. The complete hardware setup.
2. Pressure and temperature readings on the OLED.
3. The trend page on the OLED.
4. The potentiometer changing the altitude value.
5. The red and green LED indicators.
6. Multiple pressure readings in the Serial Monitor.
7. MQTT messages received in MQTT Explorer for the bonus challenge.

---

## Conclusion

This project demonstrates how a BMP280 pressure sensor can be used to monitor atmospheric conditions, calculate altitude-related pressure compensation, store historical pressure data, and identify pressure trends.

The combination of the BMP280, OLED display, circular buffer, trend calculation, LED indicators, and MQTT communication forms a basic atmospheric pressure monitoring and logging system.
