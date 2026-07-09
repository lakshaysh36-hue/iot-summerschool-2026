#  State Machine using Arduino

## Project Description
This project simulates a simple vending machine using a finite state machine (FSM). The system has four states: IDLE, COIN_INSERTED, ITEM_SELECTED, and DISPENSING. Three push buttons are used to control state transitions, while three LEDs indicate the current state. All state transitions are displayed on the Serial Monitor.

## Features
- Four vending machine states:
  - IDLE
  - COIN_INSERTED
  - ITEM_SELECTED
  - DISPENSING
- Three push buttons:
  - Insert Coin
  - Select Item
  - Cancel
- Three LEDs indicate the current state.
- Automatic transition from ITEM_SELECTED → DISPENSING → IDLE.
- Serial Monitor logs every state transition.

## Components Used
- Arduino Uno
- 3 Push Buttons
- 3 LEDs (Red, Yellow, Green)
- 3 × 220Ω Resistors
- Breadboard
- Jumper Wires

## Pin Connections

| Component | Arduino Pin |
|-----------|-------------|
| Insert Coin Button | D2 |
| Select Item Button | D3 |
| Cancel Button | D4 |
| Red LED (IDLE) | D8 |
| Yellow LED (COIN_INSERTED) | D9 |
| Green LED (DISPENSING) | D10 |

**Note:** Buttons are configured using `INPUT_PULLUP`, so no external resistors are required.

## State Diagram

```
                Insert Coin
IDLE ----------------------------> COIN_INSERTED
 ^                                     |
 | Cancel                              | Select Item
 |                                     v
 |<----------------------------- ITEM_SELECTED
 |                                     |
 |                                     | Dispense
 |                                     v
 +----------------------------- DISPENSING
                                       |
                                       | Finish
                                       v
                                     IDLE

Cancel is valid from:
COIN_INSERTED -> IDLE
ITEM_SELECTED -> IDLE
```

## Working
1. Initially, the system starts in the **IDLE** state.
2. Press **Insert Coin** to move to **COIN_INSERTED**.
3. Press **Select Item** to move to **ITEM_SELECTED**.
4. The system automatically enters **DISPENSING** and returns to **IDLE** after dispensing.
5. Press **Cancel** during **COIN_INSERTED** or **ITEM_SELECTED** to return to **IDLE**.
6. Every state transition is displayed on the Serial Monitor.

## Example Serial Monitor Output

```
Current State: IDLE
IDLE -> COIN_INSERTED
COIN_INSERTED -> ITEM_SELECTED
ITEM_SELECTED -> DISPENSING
DISPENSING -> IDLE
```

## Software Used
- Arduino IDE
- Tinkercad Circuits (Simulation)

## Author
Lakshay Sharma
