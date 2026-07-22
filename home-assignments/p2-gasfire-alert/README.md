# Project 2: Gas & Fire Safety Alert System

## IoT Summer School 2026

**Difficulty:** Beginner  
**Time Required:** 1–2 Hours  
**Marks:** 10  
solo mode

---
DRIVE LINK OF DEMO-https://drive.google.com/file/d/1v0zi7pcU8EpJnnlwp0jCWHvx_erzAeIS/view?usp=drivesdk

## 1. Project Overview

The Gas & Fire Safety Alert System is a dual-sensor safety device designed to detect dangerous gas levels and flames.

The system uses:

- An MQ-2 gas sensor to detect gas/smoke levels
- A flame sensor to detect fire
- Three LEDs to indicate the safety level
- A buzzer to provide audio alerts
- An Arduino Uno R3 as the main controller

The system has three alert levels:

| Condition | Status | LED | Buzzer |
|---|---|---|---|
| Gas below 30% and no flame | SAFE | Green | OFF |
| Gas 30%–60% and no flame | WARNING | Yellow | 1 beep/second |
| Gas above 60% OR flame detected | DANGER | Red | Continuous alarm |

Gas and flame detection work independently. Therefore, either a dangerous gas level or a detected flame can trigger the DANGER state.

---

# 2. Problem Statement

Kitchen fires and gas leaks can cause serious hazards. This project provides an early warning system by monitoring gas concentration and flame detection simultaneously.

The Arduino continuously reads the MQ-2 gas sensor and flame sensor. Based on the readings, it changes the LED indicator and buzzer behavior.

The system can detect:

- Safe environmental conditions
- Increasing gas levels
- Dangerous gas levels
- Flame detection
- Gas and flame occurring simultaneously

---

# 3. Components Used

- Arduino Uno R3
- MQ-2 Gas Sensor
- Flame Sensor
- Active Buzzer
- Green LED
- Yellow LED
- Red LED
- 3 × 220Ω Resistors
- Breadboard
- Jumper Wires
- USB Cable

---

# 4. System Block Diagram


             MQ-2 Gas Sensor
                    |
                    | Analog Signal
                    v
              +-------------+
              |             |
              |  Arduino    |
              |    Uno      |
              |             |
              +-------------+
                    ^
                    |
             Flame Sensor
             Digital Signal

                    |
        +-----------+-----------+
        |           |           |
        v           v           v
    Green LED   Yellow LED   Red LED
        |           |           |
        +-----------+-----------+
                    |
                    v
                 Buzzer




# Gas & Fire Safety Alert System

## Wiring Summary

### MQ-2 Gas Sensor → Arduino/ESP32

| MQ-2 Pin | Microcontroller  |
| -------- | ---------------- |
| VCC      | 5V               |
| GND      | GND              |
| AO       | Analog input pin |

### Flame Sensor → Microcontroller

| Flame Sensor Pin | Microcontroller   |
| ---------------- | ----------------- |
| VCC              | 5V                |
| GND              | GND               |
| DO               | Digital input pin |

### Buzzer → Microcontroller

| Buzzer Pin   | Microcontroller    |
| ------------ | ------------------ |
| Positive (+) | Digital output pin |
| Negative (-) | GND                |

> The exact GPIO/analog pin numbers should match the pin definitions in the submitted code.

## How to Run

1. Connect the MQ-2 gas sensor, flame sensor, and buzzer according to the wiring table.
2. Connect the microcontroller to the computer using USB.
3. Open the project code in Arduino IDE.
4. Select the correct board and COM port.
5. Upload the code.
6. Open the Serial Monitor using the baud rate specified in the code.
7. Allow the MQ-2 sensor to warm up before testing.
8. Observe the gas and flame readings in the Serial Monitor.
9. Introduce a safe test condition near the sensors to verify the alert system.
10. When gas or flame is detected above the configured threshold, the buzzer activates.

## Expected Output

### Normal Condition

The Serial Monitor displays readings indicating that no dangerous gas concentration or flame has been detected.


Gas: SAFE
Flame: SAFE
System Status: NORMAL
Buzzer: OFF


### Gas Detection

When the MQ-2 detects gas above the configured threshold:


Gas: DANGER
Flame: SAFE
System Status: GAS ALERT
Buzzer: ON


The buzzer activates to provide an audible warning.

### Fire/Flame Detection

When the flame sensor detects a flame:


Gas: SAFE
Flame: DETECTED
System Status: FIRE ALERT
Buzzer: ON


The buzzer activates immediately to warn of a possible fire.

### Gas and Flame Detected

If both dangerous conditions are detected:


Gas: DANGER
Flame: DETECTED
System Status: CRITICAL ALERT
Buzzer: ON


The system provides an emergency warning through the buzzer.



### MQ-2 Warm-Up Requirement

The MQ-2 gas sensor requires a warm-up period before its readings become stable and reliable.

After powering on the system:

* Allow the MQ-2 sensor to warm up for approximately **1–2 minutes** before testing.
* During the warm-up period, the sensor readings may fluctuate.
* The initial readings should not be treated as accurate gas measurements.

The code displays the following message during startup:


MQ-2 warming up...
Allow 1-2 minutes for stable readings.


This warm-up period allows the sensor's internal heating element and sensing material to reach a stable operating condition.

### Why the Flame Sensor Is Active-Low

The flame sensor used in this project provides a digital output that is **active-low**.

This means:


Digital Output = HIGH → No flame detected
Digital Output = LOW  → Flame detected


The code checks the sensor using:


bool flameDetected = (digitalRead(FLAME_DIGITAL_PIN) == LOW);


The flame sensor module typically uses an onboard comparator circuit. When infrared radiation from a flame crosses the detection threshold, the comparator changes the digital output state from HIGH to LOW. Therefore, the program treats a LOW signal as a detected flame.

This active-low behavior is important when interpreting the sensor output. Reversing the logic would cause the system to incorrectly report a flame when no flame is present and miss an actual flame when one is detected.


