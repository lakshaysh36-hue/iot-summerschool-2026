# Ultrasonic Parking Distance Alert System using Arduino

## Project Description
This project implements a parking assistance system using an HC-SR04 ultrasonic sensor. The system measures the distance between the vehicle and an obstacle and provides visual and audible alerts based on the measured distance. The distance is calculated using the formula:

**Distance (cm) = (Duration × 0.034) / 2**

The system also displays the measured distance and safety status on the Serial Monitor.

## Features
- Measures distance using the HC-SR04 ultrasonic sensor.
- Displays distance in centimeters on the Serial Monitor.
- Safety indications based on distance:
  - **Distance > 50 cm:** SAFE (No alert)
  - **Distance 20–50 cm:** Yellow LED ON, buzzer beeps every 500 ms
  - **Distance 10–20 cm:** Red LED ON, buzzer beeps every 200 ms
  - **Distance < 10 cm:** Red and Yellow LEDs flash rapidly, buzzer sounds continuously
- Uses `millis()` for non-blocking timing (bonus implementation).

## Components Used
- Arduino Uno
- HC-SR04 Ultrasonic Sensor
- Yellow LED
- Red LED
- Piezo Buzzer
- 2 × 220Ω Resistors
- Breadboard
- Jumper Wires

## Pin Connections

| Component | Arduino Pin |
|-----------|-------------|
| HC-SR04 Trigger | D9 |
| HC-SR04 Echo | D10 |
| Yellow LED | D6 |
| Red LED | D7 |
| Buzzer | D8 |

### Power Connections

| Component | Connection |
|-----------|------------|
| HC-SR04 VCC | 5V |
| HC-SR04 GND | GND |
| Yellow LED Cathode | GND through 220Ω resistor |
| Red LED Cathode | GND through 220Ω resistor |
| Buzzer Negative | GND |

## Working
1. The HC-SR04 measures the distance to the nearest object.
2. The Arduino calculates the distance using:

```
Distance = (Duration × 0.034) / 2
```

3. Based on the measured distance:
   - **> 50 cm:** No LEDs or buzzer are active. Serial Monitor displays **SAFE**.
   - **20–50 cm:** Yellow LED turns ON and the buzzer beeps every 500 ms.
   - **10–20 cm:** Red LED turns ON and the buzzer beeps every 200 ms.
   - **< 10 cm:** Both LEDs flash rapidly while the buzzer remains continuously ON.
4. The system continuously updates the distance and alert status on the Serial Monitor.

## Example Serial Monitor Output

```
Distance: 72 cm | SAFE
Distance: 43 cm | CAUTION
Distance: 18 cm | WARNING
Distance: 7 cm | STOP
Distance: 65 cm | SAFE
```

## Software Used
- Arduino IDE
- Tinkercad Circuits (Simulation)

## Files Included
- `parking_alert.ino` – Arduino source code
- `README.md` – Project documentation

## Author
Lakshay Sharma
