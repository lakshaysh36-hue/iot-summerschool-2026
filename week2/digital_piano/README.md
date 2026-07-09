# Digital Piano using Arduino

## Project Description
This project implements a simple digital piano using Arduino. Four push buttons are used to play musical notes through a passive buzzer. An additional button switches between Major and Minor scale modes.

## Features
- 4 push buttons mapped to musical notes:
  - Do (262 Hz)
  - Re (294 Hz)
  - Mi (330 Hz)
  - Fa (349 Hz)
- Plays the corresponding note while the button is pressed.
- Stops the sound when the button is released.
- If two note buttons are pressed simultaneously, the buzzer plays Sol (392 Hz) as a chord substitute.
- Fifth push button toggles between Major and Minor scale modes.
- Current mode is displayed on the Serial Monitor.

## Components Used
- Arduino Uno
- 5 Push Buttons
- Passive Buzzer
- Breadboard
- Jumper Wires
- 220Ω Resistors (if external pull-down resistors are used)

## Pin Connections

| Component | Arduino Pin |
|-----------|-------------|
| Button 1 (Do) | D2 |
| Button 2 (Re) | D3 |
| Button 3 (Mi) | D4 |
| Button 4 (Fa) | D5 |
| Mode Button | D6 |
| Passive Buzzer | D8 |

## Working
1. Press any one of the four note buttons to play its assigned note.
2. Releasing the button stops the sound.
3. Pressing any two note buttons together plays Sol (392 Hz).
4. Press the mode button to switch between Major and Minor scales.

## Software
- Arduino IDE
- Tinkercad Circuits (Simulation)

## Author
Lakshay Sharma
