#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// ---------- PIN DEFINITIONS ----------
#define RELAY1 26
#define RELAY2 27
#define BUZZER 25 
#define STATUS_LED 2

#define BUTTON1 0
#define BUTTON2 35

// Relay modules are usually active-LOW
#define RELAY_ON HIGH
#define RELAY_OFF LOW

// ---------- LIGHT STATES ----------
bool light1State = false;
bool light2State = false;

// ---------- BUTTON STATES ----------
bool lastButton1State = HIGH;
bool lastButton2State = LOW;

// ---------- TIMERS ----------
unsigned long lastButton1Press = 0;
unsigned long lastButton2Press = 0;
unsigned long lastBluetoothCommand = 0;

const unsigned long debounceTime = 250;
const unsigned long autoOffTime = 30UL * 60UL * 1000UL; // 30 minutes

// ---------- FUNCTIONS ----------

void updateRelays() {
  digitalWrite(RELAY1, light1State ? RELAY_ON : RELAY_OFF);
  digitalWrite(RELAY2, light2State ? RELAY_ON : RELAY_OFF);
}

void beep() {
  digitalWrite(BUZZER, HIGH);
  delay(50);
  digitalWrite(BUZZER, LOW);
}

void sendStatus() {
  String status = "L1:";
  status += light1State ? "ON" : "OFF";

  status += " L2:";
  status += light2State ? "ON" : "OFF";

  SerialBT.println(status);
  Serial.println(status);
}

void toggleLight1() {
  light1State = !light1State;
  updateRelays();
  beep();
  sendStatus();
}

void toggleLight2() {
  light2State = !light2State;
  updateRelays();
  beep();
  sendStatus();
}

void allLightsOn() {
  light1State = true;
  light2State = true;

  updateRelays();
  beep();
  sendStatus();
}

void allLightsOff() {
  light1State = false;
  light2State = false;

  updateRelays();
  beep();
  sendStatus();
}

void processCommand(char command) {

  lastBluetoothCommand = millis();

  switch (command) {

    case '1':
      light1State = true;
      updateRelays();
      beep();
      sendStatus();
      break;

    case '2':
      light1State = false;
      updateRelays();
      beep();
      sendStatus();
      break;

    case '3':
      light2State = true;
      updateRelays();
      beep();
      sendStatus();
      break;

    case '4':
      light2State = false;
      updateRelays();
      beep();
      sendStatus();
      break;

    case '5':
      allLightsOn();
      break;

    case '6':
      allLightsOff();
      break;

    case '?':
      sendStatus();
      break;

    default:
      SerialBT.println("Invalid command");
      Serial.println("Invalid command");
      break;
  }
}

// ---------- SETUP ----------

void setup() {

  Serial.begin(115200);

  SerialBT.begin("IIT_IoT_HomeCtrl");

  // Relay pins
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);

  // Buzzer
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  // Built-in LED
  pinMode(STATUS_LED, OUTPUT);
  digitalWrite(STATUS_LED, LOW);

  // Button 1
  pinMode(BUTTON1, INPUT_PULLUP);

  // GPIO35 needs external 10kΩ pull-down resistor
  pinMode(BUTTON2, INPUT);

  // Start with both lights OFF
  light1State = false;
  light2State = false;
  updateRelays();

  lastBluetoothCommand = millis();

  Serial.println("Bluetooth Home Light Controller Started");
  Serial.println("Bluetooth Name: IIT_IoT_HomeCtrl");
  Serial.println("Commands:");
  Serial.println("1 = Light 1 ON");
  Serial.println("2 = Light 1 OFF");
  Serial.println("3 = Light 2 ON");
  Serial.println("4 = Light 2 OFF");
  Serial.println("5 = ALL ON");
  Serial.println("6 = ALL OFF");
  Serial.println("? = STATUS");
}

// ---------- LOOP ----------

void loop() {

  // Bluetooth connection indicator
  if (SerialBT.hasClient()) {
    digitalWrite(STATUS_LED, HIGH);
  } else {
    digitalWrite(STATUS_LED, LOW);
  }

  // Read Bluetooth commands
  if (SerialBT.available()) {

    char command = SerialBT.read();

    // Ignore newline and carriage return
    if (command != '\n' && command != '\r') {
      processCommand(command);
    }
  }

  // ---------- BUTTON 1: GPIO0 ----------
  bool button1State = digitalRead(BUTTON1);

  if (button1State == LOW &&
      lastButton1State == HIGH &&
      millis() - lastButton1Press > debounceTime) {

    toggleLight1();
    lastButton1Press = millis();
  }

  lastButton1State = button1State;

  // ---------- BUTTON 2: GPIO35 ----------
  bool button2State = digitalRead(BUTTON2);

  if (button2State == HIGH &&
      lastButton2State == LOW &&
      millis() - lastButton2Press > debounceTime) {

    toggleLight2();
    lastButton2Press = millis();
  }

  lastButton2State = button2State;

  // ---------- AUTO TIMEOUT ----------
  if (millis() - lastBluetoothCommand >= autoOffTime) {

    if (light1State || light2State) {

      light1State = false;
      light2State = false;

      updateRelays();

      Serial.println("30-minute timeout: All lights OFF");
      SerialBT.println("30-minute timeout: All lights OFF");
    }

    lastBluetoothCommand = millis();
  }
}
