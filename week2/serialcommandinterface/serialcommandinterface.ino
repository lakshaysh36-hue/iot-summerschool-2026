/*
-------------------------------------------------------
Project : Serial Command Controlled LED
Author  : Lakshay Sharma

Description:
This program receives commands from the Serial Monitor
and controls the built-in LED accordingly.

Supported Commands:
1. LED_ON    -> Turns LED ON
2. LED_OFF   -> Turns LED OFF
3. BLINK_X   -> Blinks LED X times (X = 1 to 9)
4. STATUS    -> Displays LED state and blink count
5. RESET     -> Resets blink counter

Any invalid command prints:
ERROR: Unknown command
-------------------------------------------------------
*/

// Built-in LED pin (Pin 13 on Arduino Uno)
const int ledPin = LED_BUILTIN;

// Variable to store the received command
String command = "";

// Counts total number of LED blinks
int blinkCounter = 0;

// Stores current LED state
bool ledState = LOW;

void setup()
{
    // Configure LED pin as OUTPUT
    pinMode(ledPin, OUTPUT);

    // Start Serial Communication at 9600 baud rate
    Serial.begin(9600);

    // Display available commands to the user
    Serial.println("===== Serial LED Controller =====");
    Serial.println("Available Commands:");
    Serial.println("LED_ON");
    Serial.println("LED_OFF");
    Serial.println("BLINK_X (Example: BLINK_5)");
    Serial.println("STATUS");
    Serial.println("RESET");
    Serial.println();
}

void loop()
{
    // Check whether any data is received from Serial Monitor
    if (Serial.available())
    {
        // Read the complete command until Enter is pressed
        command = Serial.readStringUntil('\n');

        // Remove unwanted spaces/newline characters
        command.trim();

        // ---------------- LED ON ----------------
        if (command == "LED_ON")
        {
            // Turn LED ON
            digitalWrite(ledPin, HIGH);

            // Save LED state
            ledState = HIGH;

            Serial.println("LED Turned ON");
        }

        // ---------------- LED OFF ----------------
        else if (command == "LED_OFF")
        {
            // Turn LED OFF
            digitalWrite(ledPin, LOW);

            // Save LED state
            ledState = LOW;

            Serial.println("LED Turned OFF");
        }

        // ---------------- BLINK COMMAND ----------------
        // Check if command starts with "BLINK_"
        else if (command.startsWith("BLINK_"))
        {
            // Extract number after BLINK_
            // Example:
            // BLINK_5 -> 5
            String number = command.substring(6);

            // Convert string into integer
            int times = number.toInt();

            // Validate the blink count
            if (times >= 1 && times <= 9)
            {
                Serial.print("Blinking ");
                Serial.print(times);
                Serial.println(" times");

                // Blink LED specified number of times
                for (int i = 0; i < times; i++)
                {
                    digitalWrite(ledPin, HIGH);
                    delay(500);

                    digitalWrite(ledPin, LOW);
                    delay(500);

                    // Increase blink counter
                    blinkCounter++;
                }

                // LED is OFF after blinking
                ledState = LOW;
            }
            else
            {
                // Invalid blink value
                Serial.println("ERROR: Blink value must be between 1 and 9");
            }
        }

        // ---------------- STATUS COMMAND ----------------
        else if (command == "STATUS")
        {
            Serial.println("----- STATUS -----");

            // Print LED state
            Serial.print("LED State : ");

            if (ledState)
                Serial.println("ON");
            else
                Serial.println("OFF");

            // Print total blink count
            Serial.print("Blink Counter : ");
            Serial.println(blinkCounter);

            Serial.println("------------------");
        }

        // ---------------- RESET COMMAND ----------------
        else if (command == "RESET")
        {
            // Reset blink counter to zero
            blinkCounter = 0;

            Serial.println("Blink Counter Reset");
        }

        // ---------------- UNKNOWN COMMAND ----------------
        else
        {
            // Executed when user enters an invalid command
            Serial.println("ERROR: Unknown command");
        }
    }
}
