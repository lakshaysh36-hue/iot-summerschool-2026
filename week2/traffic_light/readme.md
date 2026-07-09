# Arduino Traffic Light System

## Project Description
This project simulates a traffic light system using three LEDs (Red, Yellow, and Green). The traffic lights operate in a fixed sequence, and a pedestrian push button allows immediate activation of the red light for safe crossing. The current traffic light state along with the timestamp (`millis()`) is displayed on the Serial Monitor.

## Features
- Automatic traffic light sequence:
  - Red ON for 5 seconds
  - Yellow ON for 2 seconds
  - Green ON for 4 seconds
- Pedestrian push button:
  - Forces Red light immediately
  - Holds Red light for 8 seconds
- Displays current light state with timestamp on the Serial Monitor.

## Components Used
- Arduino Uno
- 3 LEDs (Red, Yellow, Green)
- 3 × 220Ω Resistors
- Push Button
- Breadboard
- Jumper Wires

## Pin Connections

| Component | Arduino Pin |
|-----------|-------------|
| Red LED | D8 |
| Yellow LED | D9 |
| Green LED | D10 |
| Pedestrian Push Button | D7 |

**Note:** The push button uses `INPUT_PULLUP`, so no external resistor is required.

## Working
1. The system starts with the **Red LED** ON for **5 seconds**.
2. It switches to the **Yellow LED** for **2 seconds**.
3. Then the **Green LED** turns ON for **4 seconds**.
4. The sequence repeats continuously.
5. If the pedestrian button is pressed at any time:
   - The system immediately switches to the **Red LED**.
   - The Red LED remains ON for **8 seconds**.
   - The normal traffic light sequence then resumes.
6. Every state change is printed on the Serial Monitor with the current timestamp using `millis()`.

## Example Serial Monitor Output

```
5000 ms : RED
7000 ms : YELLOW
11000 ms : GREEN
15000 ms : RED
22000 ms : PEDESTRIAN CROSSING
30000 ms : RED
```

## Software Used
- Arduino IDE
- Tinkercad Circuits (Simulation)

## Author
Lakshay Sharma
