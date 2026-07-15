# Bluetooth LED Control using HC-05

## Components

- Arduino UNO
- HC-05 Bluetooth Module
- Red LED
- Green LED
- Blue LED
- 3 × 220Ω Resistors
- Breadboard
- Jumper Wires

---

## Bluetooth Pairing Instructions

1. Power the Arduino and HC-05.
2. Turn on Bluetooth on your Android phone.
3. Search for nearby Bluetooth devices.
4. Select **HC-05**.
5. Enter the pairing PIN:
   - 1234
   - or 0000
6. Open a Bluetooth Terminal app.
7. Connect to HC-05.

---

## Commands

| Command | Action |
|----------|--------|
| R | Red LED ON |
| G | Green LED ON |
| B | Blue LED ON |
| X | Turn all LEDs OFF |
| F | Flash all LEDs 5 times |

---

## Baud Rate

9600 bps

---

## Notes

- Disconnect the HC-05 TX/RX wires while uploading the sketch to the Arduino UNO.
- Reconnect them after the upload is complete.
