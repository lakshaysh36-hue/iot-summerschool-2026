#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---------------- OLED ----------------

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

// ---------------- PINS ----------------

const int TRIG_PIN = 9;
const int ECHO_PIN = 10;

const int BUZZER_PIN = 6;

const int GREEN_LED = 11;
const int YELLOW_LED = 12;
const int RED_LED = 13;

// ---------------- TIMERS ----------------

unsigned long lastBeepTime = 0;
unsigned long lastDisplayTime = 0;
unsigned long lastSerialTime = 0;

const unsigned long DISPLAY_INTERVAL = 200;
const unsigned long SERIAL_INTERVAL = 500;

// ---------------- DISTANCE FUNCTION ----------------

float measureDistance() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {
    return 400;
  }

  float distance = duration * 0.034 / 2;

  return distance;
}

// ---------------- AVERAGE 5 READINGS ----------------

float getAverageDistance() {

  float total = 0;

  for (int i = 0; i < 5; i++) {

    total += measureDistance();

    // Small delay between ultrasonic measurements
    delay(10);
  }

  return total / 5.0;
}

// ---------------- SETUP ----------------

void setup() {

  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  // Initialize OLED
  if (!display.begin(
        SSD1306_SWITCHCAPVCC,
        0x3C
      )) {

    Serial.println("OLED not found!");

    while (true);
  }

  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(10, 20);
  display.println("PARKING");

  display.setCursor(10, 42);
  display.println("SENSOR");

  display.display();

  delay(1500);

  Serial.println("Ultrasonic Parking Assistant Started");
}

// ---------------- LOOP ----------------

void loop() {

  // Take 5 readings and average them
  float distance = getAverageDistance();

  // ---------------- LED CONTROL ----------------

  if (distance > 60) {

    // SAFE

    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);

    noTone(BUZZER_PIN);
  }

  else if (distance >= 30 && distance <= 60) {

    // CAUTION

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(RED_LED, LOW);

    if (millis() - lastBeepTime >= 800) {

      lastBeepTime = millis();

      tone(BUZZER_PIN, 1000, 100);
    }
  }

  else if (distance >= 15 && distance < 30) {

    // CLOSE

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(RED_LED, HIGH);

    if (millis() - lastBeepTime >= 300) {

      lastBeepTime = millis();

      tone(BUZZER_PIN, 1500, 100);
    }
  }

  else {

    // DANGER

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, HIGH);

    tone(BUZZER_PIN, 2000);
  }

  // ---------------- OLED DISPLAY ----------------

  if (millis() - lastDisplayTime >= DISPLAY_INTERVAL) {

    lastDisplayTime = millis();

    display.clearDisplay();

    // Distance text
    display.setTextSize(3);
    display.setCursor(0, 0);

    if (distance >= 100) {
      display.print((int)distance);
    }
    else {
      display.print(distance, 1);
    }

    display.setTextSize(2);
    display.print(" cm");

    // Zone text
    display.setTextSize(1);
    display.setCursor(0, 35);

    if (distance > 60) {
      display.print("SAFE");
    }
    else if (distance >= 30) {
      display.print("CAUTION");
    }
    else if (distance >= 15) {
      display.print("CLOSE");
    }
    else {
      display.print("DANGER");
    }

    // Proximity bar
    int barWidth = map(
      constrain(distance, 0, 100),
      0,
      100,
      120,
      0
    );

    display.drawRect(0, 48, 128, 12, SSD1306_WHITE);

    display.fillRect(
      2,
      50,
      barWidth,
      8,
      SSD1306_WHITE
    );

    display.display();
  }

  // ---------------- SERIAL MONITOR -----------------

  if (millis() - lastSerialTime >= SERIAL_INTERVAL) {

    lastSerialTime = millis();

    Serial.print("Distance: ");
    Serial.print(distance, 1);
    Serial.print(" cm | Zone: ");

    if (distance > 60) {
      Serial.println("SAFE");
    }
    else if (distance >= 30) {
      Serial.println("CAUTION");
    }
    else if (distance >= 15) {
      Serial.println("CLOSE");
    }
    else {
      Serial.println("DANGER");
    }
  }
}
