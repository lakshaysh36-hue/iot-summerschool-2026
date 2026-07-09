# Serial Command Interface using Arduino

## Project Description
This project controls the built-in Arduino LED through commands entered in the Serial Monitor. The system reads user commands, performs the requested action, and provides appropriate responses.

## Features
- Turn the built-in LED ON using `LED_ON`
- Turn the built-in LED OFF using `LED_OFF`
- Blink the LED a specified number of times using `BLINK_X` (where X = 1–9)
- Display the current LED state using `STATUS`
- Reset the blink counter using `RESET`
- Input validation for unknown commands
- Prints `ERROR: Unknown command` for invalid commands

## Supported Commands

| Command | Description |
|---------|-------------|
| `LED_ON` | Turns the built-in LED ON |
| `LED_OFF` | Turns the built-in LED OFF |
| `BLINK_1` to `BLINK_9` | Blinks the LED the specified number of times |
| `STATUS` | Displays the current LED state |
| `RESET` | Resets the blink counter |
| Any other command | Displays `ERROR: Unknown command` |

## Components Used
- Arduino Uno
- Built-in LED (Pin 13)

**No external components are required.**

## Pin Connections

| Component | Arduino Pin |
|-----------|-------------|
| Built-in LED | D13 |

## Working
1. Open the Serial Monitor.
2. Set the baud rate to **9600**.
3. Enter one of the supported commands and press **Send**.
4. The Arduino executes the command and prints the corresponding response.
5. Invalid commands generate an error message.

## Example Commands

```
LED_ON
STATUS
BLINK_5
LED_OFF
RESET
HELLO
```

## Example Output

```
LED ON
STATUS: ON
Blinking 5 times...
LED OFF
Blink counter reset.
ERROR: Unknown command
```

## Software Used
- Arduino IDE
- Tinkercad Circuits (Simulation)

## Author
Lakshay Sharma
