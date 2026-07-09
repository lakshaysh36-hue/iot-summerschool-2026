# Smart Street Light Controller using Arduino

## Project Description
This project implements an intelligent street light controller using Arduino. An LDR (Light Dependent Resistor) detects ambient light, while a PIR motion sensor detects movement. During daylight, the street light remains OFF. At night, the system enters motion detection mode. When motion is detected, the LED turns ON at full brightness for 30 seconds. If no motion is detected during this period, the LED automatically dims to 20% brightness using PWM. All events are logged to the Serial Monitor with timestamps.

## Features
- Automatic day and night detection using an LDR.
- Motion detection using a PIR sensor.
- LED OFF during daylight.
- LED ON at 100% brightness for 30 seconds when motion is detected at night.
- LED dims to 20% brightness after 30 seconds of no motion.
- Serial Monitor logs all events with timestamps.
- PWM used for brightness control.

## Components Used
- Arduino Uno
- LDR (Light Dependent Resistor)
- 10kΩ Resistor (Voltage Divider)
- PIR Motion Sensor
- LED
- 220Ω Resistor
- Breadboard
- Jumper Wires

## Pin Connections

| Component | Arduino Pin |
|-----------|-------------|
| LDR Output | A0 |
| PIR OUT | D2 |
| LED (PWM) | D9 |

### Power Connections

| Component | Connection |
|-----------|------------|
| LDR | 5V and 10kΩ resistor to GND (Voltage Divider) |
| PIR VCC | 5V |
| PIR GND | GND |
| LED Cathode | GND through 220Ω resistor |

## Working
1. The LDR continuously measures ambient light.
2. During daylight (light level above threshold), the LED remains OFF.
3. During darkness (light level below threshold), the system enables motion detection.
4. If the PIR sensor detects motion at night:
   - The LED turns ON at full brightness (100%).
   - The LED remains ON for 30 seconds.
5. If no motion is detected after 30 seconds:
   - The LED dims to approximately 20% brightness using PWM.
6. Every important event is logged on the Serial Monitor with a timestamp.

## Example Serial Monitor Output

```
[00:00:10] EVENT: Daylight detected - LED OFF
[00:00:35] EVENT: Night detected - Motion Detection Enabled
[00:00:42] EVENT: Motion Detected - LED ON
[00:01:12] EVENT: No Motion - LED Dimmed to 20%
[00:02:05] EVENT: Motion Detected - LED ON
```

## Software Used
- Arduino IDE
- Tinkercad Circuits (Simulation)

## Files Included
- `smart_street_light.ino` – Arduino source code
- `README.md` – Project documentation
- `schematics/` – Circuit diagram (hand-drawn or Tinkercad screenshot)

## Note
In Tinkercad, the LDR is connected as a voltage divider with a 10kΩ resistor to provide an analog voltage proportional to ambient light intensity. PWM on pin D9 is used to control LED brightness.

## Author
Lakshay Sharma
