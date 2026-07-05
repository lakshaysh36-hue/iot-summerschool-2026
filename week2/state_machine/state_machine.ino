/*
==========================================================
Project : Vending Machine State Machine
Author  : Lakshay Sharma

Description:
This program simulates a simple vending machine using
a Finite State Machine (FSM).


Buttons
Button 1 -> Insert Coin
Button 2 -> Select Item
Button 3 -> Cancel

LED Indicators
Red LED    -> IDLE
Yellow LED -> COIN_INSERTED
Green LED  -> ITEM_SELECTED & DISPENSING

All state transitions are printed on Serial Monitor.
==========================================================
*/

// ---------------- Pin Definitions ----------------

// LEDs
const int redLED = 10;
const int yellowLED = 9;
const int greenLED = 8;

// Buttons
const int coinButton = 2;
const int selectButton = 3;
const int cancelButton = 4;

// Enumeration makes states easier to understand
enum State
{
    IDLE,
    COIN_INSERTED,
    ITEM_SELECTED,
    DISPENSING
};

// Machine starts in IDLE state
State currentState = IDLE;

void setup()
{
    // Configure LED pins
    pinMode(redLED, OUTPUT);
    pinMode(yellowLED, OUTPUT);
    pinMode(greenLED, OUTPUT);

    // Configure buttons using internal pull-up resistors
    pinMode(coinButton, INPUT_PULLUP);
    pinMode(selectButton, INPUT_PULLUP);
    pinMode(cancelButton, INPUT_PULLUP);

    Serial.begin(9600);

    Serial.println("===== Vending Machine Started =====");

    // Display initial state
    updateLEDs();
}


// Main Loop

void loop()
{
    // Read all buttons
    bool coinPressed = digitalRead(coinButton) == LOW;
    bool selectPressed = digitalRead(selectButton) == LOW;
    bool cancelPressed = digitalRead(cancelButton) == LOW;

    // STATE : IDLE
   
    if (currentState == IDLE)
    {
        // Coin inserted
        if (coinPressed)
        {
            changeState(COIN_INSERTED);
        }
    }


    // STATE : COIN_INSERTED
 
    else if (currentState == COIN_INSERTED)
    {
        // User selects item
        if (selectPressed)
        {
            changeState(ITEM_SELECTED);
        }

        // User cancels transaction
        else if (cancelPressed)
        {
            changeState(IDLE);
        }
    }


    // STATE : ITEM_SELECTED
    else if (currentState == ITEM_SELECTED)
    {
        // Automatically begin dispensing
        changeState(DISPENSING);

        Serial.println("Dispensing Item...");

        delay(3000);

        Serial.println("Item Dispensed");

        changeState(IDLE);
    }

    delay(200);
}


// Function to change machine state

void changeState(State newState)
{
    currentState = newState;

    // Update LEDs whenever state changes
    updateLEDs();

    // Print current state
    Serial.print("Current State : ");

    switch (currentState)
    {
        case IDLE:
            Serial.println("IDLE");
            break;

        case COIN_INSERTED:
            Serial.println("COIN_INSERTED");
            break;

        case ITEM_SELECTED:
            Serial.println("ITEM_SELECTED");
            break;

        case DISPENSING:
            Serial.println("DISPENSING");
            break;
    }
}


// Function to update LEDs based on current state
-
void updateLEDs()
{
    // Turn OFF all LEDs first
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);

    switch (currentState)
    {
        // IDLE -> Red LED
        case IDLE:
            digitalWrite(redLED, HIGH);
            break;

        // Coin inserted -> Yellow LED
        case COIN_INSERTED:
            digitalWrite(yellowLED, HIGH);
            break;

        // Item selected -> Green LED
        case ITEM_SELECTED:
            digitalWrite(greenLED, HIGH);
            break;

        // Dispensing -> Green LED
        case DISPENSING:
            digitalWrite(greenLED, HIGH);
            break;
    }
}
*/Vending Machine Started 

Current State : COIN_INSERTED

Current State : ITEM_SELECTED

Current State : DISPENSING

Dispensing Item...

Item Dispensed

Current State : IDLE
/*


----------------------------------------------------------
STATE TRANSITION DIAGRAM

             Insert Coin
      +----------------------+
      |                      |
      v                      |
    +------+                 |
    | IDLE |-----------------+
    +------+
        |
        | Coin Inserted
        v
+-----------------+
| COIN_INSERTED   |
+-----------------+
   |           |
   |           |
Select      Cancel
Item          |
   |           |
   v           v
+-----------------+       +------+
| ITEM_SELECTED   |------>| IDLE |
+-----------------+       +------+
          |
          | Dispense Item
          v
+-----------------+
|   DISPENSING    |
+-----------------+
          |
          | Finished
          v
        +------+
        | IDLE |
        +------+

----------------------------------------------------------




















