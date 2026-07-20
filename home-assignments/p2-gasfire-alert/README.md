# Project 2: Gas & Fire Safety Alert System

## IoT Summer School 2026

**Difficulty:** Beginner  
**Time Required:** 1–2 Hours  
**Marks:** 10  
**Mode:** Solo

---

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

```text
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
