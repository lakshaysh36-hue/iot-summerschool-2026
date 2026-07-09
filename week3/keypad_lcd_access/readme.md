# Password-Protected Access System using Arduino

## Project Description
This project implements a password-protected access system using a 4×4 membrane keypad and a 16×2 LCD. The user enters a 4-digit PIN through the keypad. If the entered PIN matches the predefined password, access is granted and a green LED turns on. If the PIN is incorrect, access is denied, a red LED lights up, and a buzzer sounds. After three consecutive incorrect attempts, the system locks for 10 seconds before allowing another attempt.

## Features
- 4×4 membrane keypad for PIN entry.
- 16×2 LCD displays system messages.
- Predefined 4-digit password stored in the code.
- Green LED indicates successful authentication.
- Red LED and buzzer indicate incorrect password.
- System locks for 10 seconds after 3 consecutive failed attempts.
- Entered PIN is masked using `*` characters on the LCD.

## Components Used
- Arduino Uno
- 4×4 Membrane Keypad
- 16×2 LCD Display
- 10kΩ Potentiometer (LCD Contrast)
- Green LED
- Red LED
- Piezo Buzzer
- 2 × 220Ω Resistors
- Breadboard
- Jumper Wires

## Pin Connections

### LCD

| LCD Pin | Arduino |
|----------|----------|
| VSS (GND) | GND |
| VDD (VCC) | 5V |
| V0 | Middle pin of Potentiometer |
| RS | D13 |
| RW | GND |
| E | D12 |
| DB4 | D11 |
| DB5 | D10 |
| DB6 | A0 |
| DB7 | A1 |
| LED+ (A) | 5V (through 220Ω resistor) |
| LED− (K) | GND |

### Potentiometer

| Potentiometer Pin | Connection |
|-------------------|------------|
| Left | 5V |
| Middle | LCD V0 |
| Right | GND |

### Keypad

| Keypad Pin | Arduino |
|-------------|----------|
| 1 | D9 |
| 2 | D8 |
| 3 | D7 |
| 4 | D6 |
| 5 | D5 |
| 6 | D4 |
| 7 | D3 |
| 8 | D2 |

### LEDs and Buzzer

| Component | Arduino Pin |
|-----------|-------------|
| Green LED | A2 |
| Red LED | A3 |
| Buzzer | A4 |

## Working
1. The LCD displays **ENTER PIN:** when the system starts.
2. The user enters a 4-digit PIN using the keypad.
3. Each entered digit is displayed as `*` on the LCD.
4. If the entered PIN matches the stored password:
   - LCD displays **ACCESS GRANTED**.
   - Green LED turns ON for a few seconds.
5. If the PIN is incorrect:
   - LCD displays **ACCESS DENIED**.
   - Red LED turns ON.
   - Buzzer sounds.
6. After three incorrect attempts:
   - LCD displays **LOCKED** and **Wait 10 sec**.
   - The system ignores keypad input for 10 seconds.
7. After the lock period, the system returns to **ENTER PIN:** and accepts new entries.

## Default Password

```
1234
```

## Software Used
- Arduino IDE
- Tinkercad Circuits (Simulation)
- Arduino Libraries:
  - Keypad
  - LiquidCrystal

## Author
Lakshay Sharma
