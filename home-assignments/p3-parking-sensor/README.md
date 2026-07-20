# Project 3: Ultrasonic Parking Assistant

## IoT Summer School 2026

**Difficulty:** Beginner–Intermediate  
**Time Required:** 2 Hours  
**Marks:** 10  
**Mode:** Individual / Solo

---

## 1. Project Overview

The Ultrasonic Parking Assistant is a distance-based parking sensor that simulates the parking assistance systems used in modern vehicles.

An HC-SR04 ultrasonic sensor measures the distance between the system and an object. As the object gets closer, the system:

- Changes the LED indication
- Increases the buzzer beep frequency
- Displays the distance on an OLED display
- Shows the current parking zone on the Serial Monitor

The system has four distance zones:

| Distance | Zone | LED Output | Buzzer |
|---|---|---|---|
| Greater than 60 cm | SAFE | Green | OFF |
| 30–60 cm | CAUTION | Yellow | Beep every 800 ms |
| 15–30 cm | CLOSE | Yellow + Red | Beep every 300 ms |
| Less than 15 cm | DANGER | Red | Continuous alarm |

---

# 2. Problem Statement

Parking can be difficult when an object or obstacle is close to a vehicle. This project creates a simple ultrasonic parking assistant that provides visual and audio feedback based on the distance from an obstacle.

The system uses an HC-SR04 ultrasonic sensor to measure distance. The Arduino processes the distance and classifies it into four zones:

```text
SAFE → CAUTION → CLOSE → DANGER







              +----------------------+
              |      HC-SR04         |
              |  Ultrasonic Sensor   |
              +----------+-----------+
                         |
                         | Distance Data
                         v
                  +-------------+
                  |             |
                  |  Arduino    |
                  |    Uno      |
                  |             |
                  +-------------+
                    |     |     |
                    |     |     |
                    v     v     v
                 LEDs   Buzzer OLED
