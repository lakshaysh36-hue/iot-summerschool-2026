# Project 3: Ultrasonic Parking Assistant

## IoT Summer School 2026

**Difficulty:** Beginner–Intermediate  
**Time Required:** 2 Hours  
**Marks:** 10  
**Mode:** Individual / Solo

---
I HAVE USED GREEN LED INSTEAD OF YELLOW HERE AS I DIDNT HAVE IT AT THE TIME
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



The **HC-SR04 uses the basic physics formula**:

[
\text{Distance} = \text{Speed} \times \text{Time}
]

## How it works

The HC-SR04 sends an ultrasonic sound wave toward an object.

```text
HC-SR04 ───────► Object
          ◄───────
          Echo returns
```

The sensor measures the time taken for the sound wave to:

1. Travel from the sensor to the object
2. Reflect from the object
3. Return to the sensor

The Arduino measures this time using:

```cpp
long duration = pulseIn(ECHO_PIN, HIGH);
```

---

## Speed of sound

The speed of sound in air is approximately:

[
343 \text{ m/s}
]

In the units used by the Arduino:

[
0.0343 \text{ cm/µs}
]

So the formula becomes:

[
\text{Total distance} = \text{Time} \times 0.0343
]

However, the measured distance is **twice the actual distance** because the sound travels both ways:

```text
Sensor → Object = actual distance
Object → Sensor = actual distance
```

Therefore:

[
\boxed{\text{Distance} = \frac{\text{Time} \times 0.0343}{2}}
]

In your Arduino code:

```cpp
float distance = duration * 0.034 / 2;
```

---

### Example

Suppose the HC-SR04 measures an echo duration of **1000 µs**:

[
\text{Distance} =
\frac{1000 \times 0.0343}{2}
]

[
= 17.15 \text{ cm}
]

So the object is approximately **17.15 cm away**.


**Short explanation for your README:** The HC-SR04 measures the time taken by an ultrasonic pulse to travel to an object and return as an echo. Using the speed of sound in air (approximately 0.034 cm/µs), the Arduino calculates the total 
