/*
=========================================================
Project : Relay Controlled AC Device Simulation
Author  : Lakshay Sharma

Description:
This project simulates an AC controlled by a relay.
An LED is used instead of a real AC appliance.

Features:
1. Read temperature from DHT11 sensor.
2. If temperature > 32°C:
      Relay turns ON (AC ON)
3. If temperature < 28°C:
      Relay turns OFF (AC OFF)
4. Hysteresis prevents frequent switching.
5. Manual Override Button toggles relay state.
6. Every relay state change is logged on the
   Serial Monitor along with the temperature.
=========================================================
*/

#include <DHT.h>

//--------------- DHT11 Configuration ----------------

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

//--------------- Pin Definitions ----------------

const int RELAY_PIN = 8;        // LED simulates relay
const int BUTTON_PIN = 7;

//--------------- Variables ----------------

bool relayState = false;
bool manualOverride = false;

bool lastButtonState = HIGH;

void setup()
{
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  digitalWrite(RELAY_PIN, LOW);

  Serial.begin(9600);

  dht.begin();

  Serial.println("Relay Controlled AC Simulation Started");
}

void loop()
{
  // Read temperature
  float temperature = dht.readTemperature();

  // Check if sensor reading failed
  if (isnan(temperature))
  {
    Serial.println("Failed to read DHT11!");
    delay(2000);
    return;
  }

  // Read button
  bool currentButton = digitalRead(BUTTON_PIN);

  // Manual Override
  if (lastButtonState == HIGH && currentButton == LOW)
  {
    manualOverride = !manualOverride;
    relayState = !relayState;

    digitalWrite(RELAY_PIN, relayState);

    Serial.print("Manual Override -> Relay ");

    if (relayState)
      Serial.print("ON");
    else
      Serial.print("OFF");

    Serial.print(" | Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");
  }

  lastButtonState = currentButton;

  // Automatic Control (only if manual override is OFF)
  if (!manualOverride)
  {
    // Turn AC ON
    if (temperature > 32 && !relayState)
    {
      relayState = true;

      digitalWrite(RELAY_PIN, HIGH);

      Serial.print("Relay ON (AC ON) | Temperature: ");
      Serial.print(temperature);
      Serial.println(" C");
    }

    // Turn AC OFF
    else if (temperature < 28 && relayState)
    {
      relayState = false;

      digitalWrite(RELAY_PIN, LOW);

      Serial.print("Relay OFF (AC OFF) | Temperature: ");
      Serial.print(temperature);
      Serial.println(" C");
    }
  }

  delay(1000);
}
//
Working
The DHT11 continuously measures the temperature.
If the temperature exceeds 32°C, the relay (simulated by the LED) turns ON.
The relay remains ON until the temperature drops below 28°C, implementing hysteresis to avoid rapid switching.
Pressing the manual override button toggles the relay ON/OFF regardless of temperature.
Every relay state change is logged to the Serial Monitor with the current temperature.


//serial monitor output
Relay Controlled AC Simulation Started

Relay ON (AC ON) | Temperature: 33.4 C

Relay OFF (AC OFF) | Temperature: 27.6 C

Manual Override -> Relay ON | Temperature: 29.1 C

Manual Override -> Relay OFF | Temperature: 29.1 C


