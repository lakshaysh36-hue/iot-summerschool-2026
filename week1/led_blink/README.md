# LED Blink Project

## Project Title

**Arduino LED Blink with Potentiometer Speed Control**

## Overview

This project demonstrates the basics of Arduino programming by blinking an LED connected to digital pin 13. The project has been enhanced to display the blink count on the Serial Monitor and to adjust the blinking speed using a potentiometer.

---

## Hardware Required

* Arduino Uno (or compatible board)
* USB cable
* LED (optional if using the onboard LED on pin 13)
* 220 Ω resistor (if using an external LED)
* Potentiometer (10 kΩ)
* Breadboard
* Jumper wires
* Computer with Arduino IDE installed

---

## Circuit Diagram Description

### LED Connection

* Connect the LED anode (+) to **Digital Pin 13** through a **220 Ω resistor**.
* Connect the LED cathode (−) to **GND**.

*(If using the onboard LED on an Arduino Uno, no external LED is required.)*

### Potentiometer Connection

* Connect one outer pin of the potentiometer to **5V**.
* Connect the other outer pin to **GND**.
* Connect the center (wiper) pin to **Analog Pin A0**.

---

## How to Upload the Code

1. Connect the Arduino board to your computer using a USB cable.
2. Open the Arduino IDE.
3. Open the `led_blink.ino` sketch.
4. Select **Tools → Board → Arduino Uno** (or your board model).
5. Select the correct COM port from **Tools → Port**.
6. Click the **Verify (✓)** button to compile the sketch.
7. Click the **Upload (→)** button.
8. Wait until the message **"Done uploading"** appears.
9. Open the **Serial Monitor** and set the baud rate to **9600** to view the blink count.

---

## Expected Output

* The LED blinks continuously.
* The potentiometer changes the LED blinking speed.
* The Serial Monitor displays:

  ```
  Blink count: 1
  Blink count: 2
  Blink count: 3
  ...
  ```
* Rotating the potentiometer increases or decreases the delay between blinks.

---

## Troubleshooting Tips

1. Verify that the correct Arduino board and COM port are selected in the Arduino IDE.
2. Ensure all jumper wire connections are secure and match the circuit description.
3. If the LED does not blink, check its polarity (anode and cathode) and the resistor connection.
4. If the upload fails, disconnect and reconnect the USB cable, then try uploading again.
5. If the blink speed does not change, verify that the potentiometer's center pin is connected to **A0**.
6. Make sure the Serial Monitor baud rate is set to **9600** to correctly display the blink count.

---

## Author

**Name:** Lakshay Sharma

**Roll Number:** *YOUR_ROLL_NUMBER*
