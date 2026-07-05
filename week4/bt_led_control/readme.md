## Bluetooth Pairing Instructions

1. Power the Arduino and HC-05 module.
2. Turn ON Bluetooth on your Android phone.
3. Search for available devices.
4. Select **HC-05**.
5. Enter the pairing PIN:
   - **1234**
   - or **0000** 
6. Install a Bluetooth Terminal app (e.g., Serial Bluetooth Terminal).
7. Connect to the HC-05.
8. Send the following commands:

- **R** → Red LED ON
- **G** → Green LED ON
- **B** → Blue LED ON
- **X** → All LEDs OFF
- **F** → Flash all LEDs 5 times

- //bluetooth terminal session
- Bluetooth LED Controller Ready

R
Red LED ON

G
Green LED ON

B
Blue LED ON

X
All LEDs OFF

//ckt connections
HC-05 Bluetooth Module
HC-05 Pin	Arduino
VCC	5V
GND	GND
TXD	RX (D0)
RXD	TX (D1) 



LEDs
LED	Arduino Pin
Red LED	D8
Green LED	D9
Blue LED	D10

Connect each LED in series with a 220 Ω resistor, and connect the other end of each LED to GND.




















F
Flashing LEDs
Flash Complete
