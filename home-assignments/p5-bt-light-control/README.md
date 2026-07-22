# Project 5: Bluetooth Home Light Controller
DRIVE LINK-https://drive.google.com/file/d/1BkNdmHvL-B2C_ftjyCJTw1BYNoltc-2V/view?usp=drive_link
## Components Used

* ESP32 Development Board
* 2-Channel Relay Module
* 2 LEDs or lamps for demonstration
* 2 Push Buttons
* Active Buzzer
* Resistors
* Breadboard
* Jumper Wires
* USB Cable
* Bluetooth-enabled smartphone

## Wiring Summary

### 2-Channel Relay Module → ESP32

| Relay Pin | ESP32   |
| --------- | ------- |
| VCC       | 5V/VIN  |
| GND       | GND     |
| IN1       | GPIO 26 |
| IN2       | GPIO 27 |

> The relay module is controlled using GPIO 26 and GPIO 27. The code defines the relay output logic using `RELAY_ON` and `RELAY_OFF`.

### Buzzer

| Buzzer Pin   | ESP32   |
| ------------ | ------- |
| Positive (+) | GPIO 25 |
| Negative (-) | GND     |

### Status LED

| LED          | ESP32  |
| ------------ | ------ |
| Built-in LED | GPIO 2 |

The built-in LED turns ON when a Bluetooth client is connected.

### Push Buttons

#### Button 1

| Button Pin     | ESP32  |
| -------------- | ------ |
| One terminal   | GPIO 0 |
| Other terminal | GND    |

GPIO 0 uses the ESP32 internal pull-up resistor.

#### Button 2

| Button Pin     | ESP32   |
| -------------- | ------- |
| One terminal   | GPIO 35 |
| Other terminal | 3.3V    |

GPIO 35 requires an external **10 kΩ pull-down resistor** to GND.

### Relay Output

The relay channels can be connected to LEDs or low-voltage demonstration loads for testing.

* Relay Channel 1 → Light 1
* Relay Channel 2 → Light 2

For safety, use low-voltage loads during demonstrations.

## How to Run

1. Connect the ESP32, relay module, buzzer, push buttons, and other components according to the wiring summary.
2. Open the project code in Arduino IDE.
3. Select:

   * **Board:** ESP32 development board
   * **Port:** Correct ESP32 COM port
4. Upload the code to the ESP32.
5. Open the Serial Monitor at **115200 baud**.
6. Enable Bluetooth on a smartphone.
7. Pair/connect to the Bluetooth device:


IIT_IoT_HomeCtrl


8. Send commands through a Bluetooth serial terminal application.

### Bluetooth Commands

| Command | Function                     |
| ------- | ---------------------------- |
| `1`     | Light 1 ON                   |
| `2`     | Light 1 OFF                  |
| `3`     | Light 2 ON                   |
| `4`     | Light 2 OFF                  |
| `5`     | Turn both lights ON          |
| `6`     | Turn both lights OFF         |
| `?`     | Request current light status |

The push buttons can also be used to toggle the lights locally.

## Expected Output

### Serial Monitor Startup


Bluetooth Home Light Controller Started
Bluetooth Name: IIT_IoT_HomeCtrl
Commands:
1 = Light 1 ON
2 = Light 1 OFF
3 = Light 2 ON
4 = Light 2 OFF
5 = ALL ON
6 = ALL OFF
? = STATUS


### Light 1 ON

Send:


1


Expected result:

* Relay 1 activates
* Light 1 turns ON
* Buzzer gives a short beep
* Status is sent through Bluetooth and Serial Monitor


L1:ON L2:OFF


### Light 2 ON

Send:

3


Expected result:

`
L1:ON L2:ON


Relay 2 activates and Light 2 turns ON.

### Turn All Lights OFF

Send:


6


Expected result:


L1:OFF L2:OFF


Both relay channels are deactivated.

### Bluetooth Connection Indicator

When a Bluetooth device is connected:

* ESP32 built-in LED: ON

When no Bluetooth device is connected:

* ESP32 built-in LED: OFF

### Push Button Control

* Pressing Button 1 toggles Light 1.
* Pressing Button 2 toggles Light 2.
* The buzzer gives a short confirmation beep.
* The updated status is sent through Bluetooth and printed to the Serial Monitor.

### Automatic Safety Timeout

If the system does not receive a Bluetooth command for 30 minutes while a light is ON:


30-minute timeout: All lights OFF


Both lights are automatically turned OFF as a safety feature.

## Project Working

The Bluetooth Home Light Controller uses the ESP32's built-in Bluetooth capability to control two lights wirelessly. Commands received from a smartphone are processed by the ESP32, which controls the relay channels. Physical push buttons provide local control, while the buzzer provides feedback for actions. The built-in LED indicates the Bluetooth connection status, and an automatic 30-minute timeout turns off all lights if no Bluetooth command is received.

