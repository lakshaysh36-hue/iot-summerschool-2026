# Relay-Controlled AC Appliance Simulation using Arduino

## Project Description
This project simulates an automatic air conditioner (AC) control system using Arduino. The system monitors temperature and controls a relay to switch an AC appliance ON or OFF. Since Tinkercad does not provide a relay module or DHT11 sensor, a TMP36 temperature sensor is used to measure temperature and an LED is used to simulate the relay-controlled AC appliance.

The system uses hysteresis to prevent rapid switching:
- Relay turns ON when temperature exceeds **32°C**.
- Relay turns OFF when temperature drops below **28°C**.
- A push button provides manual override to toggle the relay state.

## Features
- Temperature monitoring using TMP36 sensor.
- Automatic relay control with hysteresis.
- Manual override using a push button.
- LED simulates the relay-controlled AC appliance.
- Logs every relay state change with the current temperature on the Serial Monitor.

## Components Used
- Arduino Uno
- TMP36 Temperature Sensor
- LED (Relay/AC Simulation)
- Push Button
- 220Ω Resistor
- Breadboard
- Jumper Wires

## Pin Connections

| Component | Arduino Pin |
|-----------|-------------|
| TMP36 Output | A0 |
| LED (Relay Simulation) | D8 |
| Push Button | D2 |

### Power Connections

| Component | Connection |
|-----------|------------|
| TMP36 Left Pin | 5V |
| TMP36 Right Pin | GND |
| LED Cathode | GND through 220Ω resistor |
| Push Button | GND (using INPUT_PULLUP) |

## Working
1. The TMP36 continuously measures the ambient temperature.
2. If the temperature rises above **32°C**, the relay (LED) turns ON.
3. If the temperature falls below **28°C**, the relay (LED) turns OFF.
4. Temperatures between **28°C and 32°C** do not change the relay state, preventing frequent switching (hysteresis).
5. Pressing the push button toggles the relay manually.
6. Every relay state change is logged on the Serial Monitor with the current temperature.

## Example Serial Monitor Output

```
AUTO | Temp: 33.4 C | Relay ON
AUTO | Temp: 27.8 C | Relay OFF
MANUAL OVERRIDE | Temp: 30.5 C | Relay ON
MANUAL OVERRIDE | Temp: 30.5 C | Relay OFF
```

## Software Used
- Arduino IDE
- Tinkercad Circuits (Simulation)

## Note
The original assignment requires a **DHT11 sensor** and a **relay module**. Since these components are not available in Tinkercad, the following alternatives were used:
- **TMP36** → Temperature Sensor
- **LED** → Relay-controlled AC appliance simulation

The program logic remains the same as the original assignment.

## Author
Lakshay Sharma
