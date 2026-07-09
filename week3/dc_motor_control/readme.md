# DC Motor Control using Arduino and L293D Motor Driver

## Project Description
This project controls the speed and direction of a DC motor using an Arduino Uno and an L293D motor driver (used as an alternative to the L298N in Tinkercad). A potentiometer is used to control the motor speed through PWM, while two push buttons are used to change the motor direction and start/stop the motor. The current motor direction, speed percentage, and running state are displayed on the Serial Monitor.

## Features
- Potentiometer controls motor speed (PWM: 0–255).
- Speed displayed as a percentage (0–100%).
- Push button to toggle motor direction (Forward/Reverse).
- Push button to start or stop the motor.
- Serial Monitor displays:
  - Motor Direction
  - Motor Speed (%)
  - Motor State (Running/Stopped)

## Components Used
- Arduino Uno
- L293D Motor Driver (Alternative to L298N in Tinkercad)
- DC Motor
- 10kΩ Potentiometer
- 2 Push Buttons
- 9V Battery (Motor Supply)
- Breadboard
- Jumper Wires

## Pin Connections

| Component | Arduino Pin |
|-----------|-------------|
| Potentiometer (Middle Pin) | A0 |
| Direction Button | D2 |
| Start/Stop Button | D3 |
| L293D 1A | D7 |
| L293D 2A | D8 |
| L293D Enable (1,2 EN) | D9 (PWM) |

### L293D Connections

| L293D Pin | Connection |
|------------|------------|
| VCC1 | Arduino 5V |
| VCC2 | 9V Battery (+) |
| GND | Arduino GND & Battery (-) |
| 1A | Arduino D7 |
| 2A | Arduino D8 |
| 1,2 EN | Arduino D9 (PWM) |
| 1Y | Motor Terminal 1 |
| 2Y | Motor Terminal 2 |

**Note:** The direction and start/stop buttons use `INPUT_PULLUP`, so no external resistors are required.

## Working
1. Rotate the potentiometer to adjust the motor speed.
2. Press the **Direction** button to switch between Forward and Reverse rotation.
3. Press the **Start/Stop** button to toggle the motor between Running and Stopped states.
4. The Serial Monitor continuously displays the current motor direction, speed percentage, and running state.

## Example Serial Monitor Output

```
Direction: Forward | Speed: 75% | State: Running
Direction: Reverse | Speed: 75% | State: Running
Direction: Reverse | Speed: 40% | State: Running
Direction: Reverse | Speed: 40% | State: Stopped
Direction: Forward | Speed: 100% | State: Running
```

## Software Used
- Arduino IDE
- Tinkercad Circuits (Simulation)

## Note
Tinkercad does not provide an L298N motor driver module. Therefore, the **L293D motor driver** is used as an equivalent H-Bridge motor driver to implement the required functionality.

## Author
Lakshay Sharma
