# PWM Night Light using Arduino

## Project Description
This project implements an automatic night light using PWM. An LED continuously performs a breathing (fade in/fade out) effect. A push button is used to switch between three operating modes.

## Features
- LED breathing effect using PWM.
- Three operating modes:
  - Mode 1: Slow Breathing (3-second cycle)
  - Mode 2: Fast Pulse (0.5-second cycle)
  - Mode 3: SOS Pattern (... --- ...)
- Push button switches between the three modes.
- Current mode is displayed on the Serial Monitor.

## Components Used
- Arduino Uno
- LED
- 220Ω Resistor
- Push Button
- Breadboard
- Jumper Wires

## Pin Connections

| Component | Arduino Pin |
|-----------|-------------|
| LED (Anode) | D9 (PWM) |
| LED (Cathode) | GND through 220Ω resistor |
| Push Button | D2 |
| Other Button Terminal | GND |

**Note:** The push button is configured using `INPUT_PULLUP`, so no external resistor is required.

## Working
1. When the simulation starts, the LED performs a slow breathing effect.
2. Press the push button once to switch to Fast Pulse mode.
3. Press the button again to switch to SOS mode.
4. Press the button again to return to Slow Breathing mode.
5. The current mode is continuously displayed on the Serial Monitor.

## Software Used
- Arduino IDE
- Tinkercad Circuits (Simulation)

## Author
Lakshay Sharma
