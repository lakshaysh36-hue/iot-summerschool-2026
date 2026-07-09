# Servo Motor Control using Arduino

## Project Description
This project controls an SG90 servo motor using a potentiometer. The potentiometer position (0–1023) is mapped to a servo angle ranging from 0° to 180°. The current servo angle is displayed on the Serial Monitor. A push button is used to trigger a full servo sweep from 0° to 180° and back to 0°.

## Features
- Control SG90 servo motor using a potentiometer.
- Maps potentiometer values (0–1023) to servo angles (0°–180°).
- Displays the current servo angle on the Serial Monitor.
- Push button initiates one complete servo sweep (0° → 180° → 0°).
- After the sweep, the servo resumes following the potentiometer position.

## Components Used
- Arduino Uno
- SG90 Micro Servo Motor
- 10kΩ Potentiometer
- Push Button
- Breadboard
- Jumper Wires

## Pin Connections

| Component | Arduino Pin |
|-----------|-------------|
| Servo Signal | D9 |
| Potentiometer Middle Pin | A0 |
| Push Button | D2 |

### Power Connections

| Component | Connection |
|-----------|------------|
| Servo VCC (Red) | 5V |
| Servo GND (Brown/Black) | GND |
| Potentiometer Left Pin | 5V |
| Potentiometer Right Pin | GND |
| Push Button | GND (using INPUT_PULLUP) |

## Working
1. Rotate the potentiometer to control the servo angle.
2. The Arduino maps the potentiometer reading to a servo angle between **0° and 180°**.
3. The current angle is displayed on the Serial Monitor.
4. Press the push button to perform a complete servo sweep:
   - 0° → 180°
   - 180° → 0°
5. After the sweep, the servo returns to potentiometer control.

## Example Serial Monitor Output

```
Servo Angle: 0 degrees
Servo Angle: 35 degrees
Servo Angle: 78 degrees
Servo Angle: 120 degrees
Servo Angle: 180 degrees
```

## Software Used
- Arduino IDE
- Tinkercad Circuits (Simulation)
- Servo Library (`Servo.h`)

## Files Included
- `servo_control.ino` – Arduino source code
- `README.md` – Project documentation

## Author
Lakshay Sharma
