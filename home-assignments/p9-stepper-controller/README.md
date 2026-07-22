# Project 9: Precision Motor Positioner

A precision motor position-control system developed for the IoT Summer School Project 9. The system allows a user to set a target angle using a potentiometer and uses encoder feedback to track the actual position of a DC motor.

The project demonstrates the basic principles of precision positioning systems used in CNC machines, 3D printers, robotic arms, and other automated systems.

---

## Simulation Note

This project was implemented using **Tinkercad Circuits**.

The original project specification required a **28BYJ-48 stepper motor with a ULN2003 driver board**. However, these components were not available in the required form in the Tinkercad simulation environment. Therefore, alternative components were used wherever necessary.

### Original Components vs Tinkercad Alternatives

| Original Component | Tinkercad Alternative |
|---|---|
| 28BYJ-48 Stepper Motor | DC Motor with Encoder |
| ULN2003 Driver Board | L293D H-Bridge Motor Driver |
| Step Counting | Encoder Pulse Counting |

The alternative components allow the project to demonstrate the same core concepts of:

- Target angle selection
- Motor direction control
- Position feedback
- Position tracking
- Home position reset
- Closed-loop position control

The Tinkercad version uses encoder feedback to measure the actual motor position.

---

## Components Used in Tinkercad

- Arduino Uno R3
- DC Motor with Encoder
- L293D H-Bridge Motor Driver
- 10kΩ Potentiometer
- 3 Push Buttons
- LED
- 220Ω Resistor
- Breadboard
- Jumper Wires

---

## Project Features

- Potentiometer-controlled target angle from 0° to 360°
- Encoder-based position feedback
- Clockwise motor movement
- Counter-clockwise motor movement
- Home position reset
- L293D H-Bridge motor control
- Position indicator LED
- Serial Monitor position tracking
- Closed-loop position correction

---

# Pin Configuration

| Arduino Pin | Function |
|---|---|
| D2 | Encoder Channel A |
| D3 | CW Button |
| D4 | CCW Button |
| D5 | L293D Enable 1,2 |
| D6 | Position Indicator LED |
| D7 | L293D IN1 |
| D8 | L293D IN2 |
| D9 | Home Button |
| A0 | Potentiometer Wiper |

---

# Wiring Summary

## L293D Motor Driver

The L293D is used to control the direction and speed of the DC motor.

### Power Connections

- L293D Logic VCC → Arduino 5V
- L293D Motor VCC → Arduino 5V
- All L293D GND pins → Arduino GND

Both power inputs of the L293D are connected to 5V in the Tinkercad simulation.

### Control Connections

- L293D Enable 1,2 → Arduino D5
- L293D IN1 → Arduino D7
- L293D IN2 → Arduino D8

### Motor Connections

- Motor Positive → L293D OUT1
- Motor Negative → L293D OUT2

The L293D controls the motor direction by changing the polarity across the motor terminals.

---

## Encoder Connections

The DC motor encoder provides feedback about motor rotation.

- Encoder Power → Arduino 5V
- Encoder GND → Arduino GND
- Encoder Channel A → Arduino D2

Channel A generates pulses as the motor rotates. These pulses are counted using an Arduino external interrupt.

Channel B was not required for the basic implementation because the direction is determined from the commanded motor direction. A full quadrature encoder implementation could use both Channel A and Channel B for independent direction detection.

---

## Potentiometer Connections

The potentiometer is used to select the target angle.

- One outer pin → Arduino 5V
- Other outer pin → Arduino GND
- Middle pin/wiper → Arduino A0

The analog value is mapped to a target angle from:

```text
0° to 360°
```

---

## Push Button Connections

The buttons use Arduino's internal pull-up resistors.

### CW Button

- One terminal → Arduino D3
- Other terminal → GND

### CCW Button

- One terminal → Arduino D4
- Other terminal → GND

### Home Button

- One terminal → Arduino D9
- Other terminal → GND

The buttons use:

```cpp
INPUT_PULLUP
```

Therefore:

```text
Button not pressed = HIGH
Button pressed     = LOW
```

---

## Position LED Connections

- Arduino D6 → 220Ω resistor
- Resistor → LED anode/long leg
- LED cathode/short leg → GND

The LED indicates the position error:

```text
LED ON  → Motor is away from the target
LED OFF → Motor is at or close to the target
```

---

# How the System Works

The potentiometer is continuously read by the Arduino.

The analog value from the potentiometer is mapped to a target angle:

```text
Potentiometer value: 0–1023
Target angle:        0°–360°
```

The encoder generates pulses as the motor rotates. These pulses are counted to determine the current position.

The current angle is calculated using:

```text
Current Angle =
Encoder Counts × 360 / Counts Per Revolution
```

The Arduino then calculates the position error:

```text
Position Error =
Target Position - Current Position
```

The motor is controlled according to the position error:

- If the target is ahead, the motor rotates clockwise.
- If the target is behind, the motor rotates counter-clockwise.
- If the motor reaches the target, it stops.

A small dead zone is used to prevent unnecessary motor vibration near the target position.

---

# Motor Direction Control

The L293D uses two input pins to control motor direction.

### Clockwise

```text
IN1 = HIGH
IN2 = LOW
```

### Counter-Clockwise

```text
IN1 = LOW
IN2 = HIGH
```

### Stop

```text
Enable = LOW
```

The Enable pin is connected to Arduino PWM pin D5 to control the motor speed.

---

# 28BYJ-48: 4096 Steps per Revolution

The original project specification uses a 28BYJ-48 stepper motor.

The commonly used 28BYJ-48 motor has a geared mechanism that provides high positioning resolution.

The motor is commonly specified as having approximately:

```text
64 steps per motor revolution
```

The internal gearbox provides an approximate reduction ratio of:

```text
64:1
```

Therefore, the commonly used calculation is:

```text
64 × 64 = 4096 steps per output shaft revolution
```

Thus:

```text
4096 steps = 360°
```

The theoretical angular resolution is:

```text
360° / 4096
≈ 0.0879° per step
```

This means that one step theoretically corresponds to approximately:

```text
0.0879°
```

of output shaft rotation.

---

# How Gearing Affects Resolution

Without gearing, the motor shaft would directly drive the output shaft. Each motor step would produce a relatively large angular movement.

A gearbox reduces the output speed and increases the number of motor steps required to rotate the output shaft through one complete revolution.

For example:

```text
Without gearbox:
1 motor revolution = 360° output rotation
```

With a gearbox:

```text
Many motor revolutions = 1 output shaft revolution
```

Therefore:

```text
More motor steps per output revolution
              ↓
Smaller movement per step
              ↓
Higher angular resolution
```

The gearbox improves the theoretical positioning resolution of the output shaft.

However, there is a trade-off:

```text
Higher gear reduction
        ↓
Higher resolution
        ↓
Lower output speed
        ↓
Higher available torque
```

This is why geared motors are commonly used in:

- CNC machines
- 3D printers
- Robotic arms
- Camera positioning systems
- Automated control systems

---

# Tinkercad Simulation Limitation

The Tinkercad implementation does not directly use the 28BYJ-48's 4096-step system because the original 28BYJ-48 and ULN2003 driver combination was unavailable in the required simulation environment.

Instead, the following alternatives were used:

```text
DC Motor with Encoder
          +
L293D H-Bridge Driver
```

The DC motor encoder provides position feedback through encoder pulses.

Therefore, the Tinkercad implementation demonstrates the same fundamental precision-positioning concept using:

```text
Target Position
      ↓
Motor Movement
      ↓
Encoder Feedback
      ↓
Position Calculation
      ↓
Motor Correction
```

The encoder resolution is represented in the code using:

```cpp
#define COUNTS_PER_REV 360.0
```

This value should match the actual encoder resolution in a real hardware implementation.

---

# How to Run

1. Open the project in Tinkercad Circuits.
2. Verify all wiring connections.
3. Open the Arduino code editor.
4. Paste the project code.
5. Start the simulation.
6. Open the Serial Monitor.
7. Set the Serial Monitor baud rate to:

```text
9600 baud
```

8. Rotate the potentiometer to select a target angle.
9. Observe the motor moving toward the target.
10. Use the CW, CCW, and Home buttons to test the system.

---

# Expected Output

When the simulation starts, the Serial Monitor displays:

```text
====================================
PRECISION POSITION CONTROLLER
DC MOTOR + ENCODER + L293D
====================================
System Ready
```

During operation, the Serial Monitor displays the current position, target position, encoder counts, and direction.

Example:

```text
--------------------------------
Current Angle: 45.0 degrees
Target Angle: 180 degrees
Encoder Counts: 45
Target Counts: 180
Direction: CW
--------------------------------
```

When the motor reaches the target:

```text
--------------------------------
Current Angle: 179.0 degrees
Target Angle: 180 degrees
Encoder Counts: 179
Target Counts: 180
Direction: STOP
--------------------------------
```

When the Home button is pressed:

```text
HOME POSITION SET
Current position = 0 degrees
```

---

# Button Behavior

| Button | Function |
|---|---|
| CW Button | Moves the motor clockwise |
| CCW Button | Moves the motor counter-clockwise |
| Home Button | Resets the current logical position to 0° |

The potentiometer continuously determines the target angle.

---

# LED Behavior

The position indicator LED shows whether the motor has reached the target position.

```text
LED ON  → Motor is away from target
LED OFF → Motor is at or close to target
```

---

# Expected Demonstration

The demonstration should show:

1. Starting the Tinkercad simulation.
2. Setting a target angle using the potentiometer.
3. The motor moving toward the target.
4. The motor stopping when the target is reached.
5. Clockwise button operation.
6. Counter-clockwise button operation.
7. Home button resetting the logical position.
8. Serial Monitor showing position tracking over multiple movements.

---

# Conclusion

This project demonstrates the fundamentals of precision motor positioning.

Due to Tinkercad component availability limitations, a DC Motor with Encoder and L293D H-Bridge were used as alternatives to the original 28BYJ-48 stepper motor and ULN2003 driver.

The system demonstrates how a target position can be selected, how motor movement can be controlled, and how feedback can be used to track and correct the actual motor position.

These concepts form the foundation of:

- CNC machines
- 3D printers
- Robotic arms
- Automated positioning systems
- Industrial motion-control systems
