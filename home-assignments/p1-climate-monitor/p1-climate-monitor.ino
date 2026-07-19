#include <Wire.h>
#include <DHTesp.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---------------- PIN DEFINITIONS ----------------
#define DHT_PIN       4
#define RED_LED       25
#define GREEN_LED     26
#define BUZZER_SIGNAL 27

// ---------------- OLED ----------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

DHTesp dht;

// ---------------- TIMING ----------------
unsigned long lastSensorRead = 0;
unsigned long lastCSVLog = 0;
unsigned long lastScreenChange = 0;
unsigned long buzzerStartTime = 0;

const unsigned long SENSOR_INTERVAL = 2000;
const unsigned long CSV_INTERVAL = 5000;
const unsigned long SCREEN_INTERVAL = 5000;
const unsigned long BUZZER_DURATION = 1000;

// ---------------- SENSOR DATA ----------------
float temperature = 0;
float humidity = 0;

float maxTemperature = -100;
float minTemperature = 100;

String status = "STARTING";

int currentScreen = 0;
bool buzzerActive = false;

// =================================================
// SETUP
// =================================================

void setup() {

  Serial.begin(115200);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER_SIGNAL, OUTPUT);

  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BUZZER_SIGNAL, LOW);

  dht.setup(DHT_PIN, DHTesp::DHT11);

  Wire.begin(21, 22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {

    Serial.println("OLED initialization failed!");

    while (true);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  display.setCursor(0, 0);
  display.println("SMART CLIMATE");
  display.println();
  display.println("Starting...");

  display.display();

  delay(2000);

  Serial.println("millis,temperature,humidity,status");
}

// =================================================
// MAIN LOOP
// =================================================

void loop() {

  unsigned long currentMillis = millis();

  // ---------------- SENSOR READING ----------------

  if (currentMillis - lastSensorRead >= SENSOR_INTERVAL) {

    lastSensorRead = currentMillis;

    TempAndHumidity data = dht.getTempAndHumidity();

    temperature = data.temperature;
    humidity = data.humidity;

    if (isnan(temperature) || isnan(humidity)) {

      Serial.println("DHT11 reading failed!");

      return;
    }

    // Update min/max temperature
    if (temperature < minTemperature) {
      minTemperature = temperature;
    }

    if (temperature > maxTemperature) {
      maxTemperature = temperature;
    }

    // ---------------- ALERT LOGIC ----------------

    if (temperature > 38 || humidity > 80) {

      status = "DANGER";

      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);

      if (!buzzerActive) {

        digitalWrite(BUZZER_SIGNAL, HIGH);

        buzzerActive = true;
        buzzerStartTime = currentMillis;
      }
    }

    else if (temperature > 32 || humidity > 70) {

      status = "HOT";

      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
    }

    else if (temperature >= 20 && temperature <= 30 &&
             humidity >= 40 && humidity <= 70) {

      status = "COMFORT";

      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
    }

    else {

      status = "COOL";

      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
    }

    updateOLED();
  }

  // ---------------- BUZZER TIMER ----------------

  if (buzzerActive &&
      currentMillis - buzzerStartTime >= BUZZER_DURATION) {

    digitalWrite(BUZZER_SIGNAL, LOW);

    buzzerActive = false;
  }

  // ---------------- CSV LOGGING ----------------

  if (currentMillis - lastCSVLog >= CSV_INTERVAL) {

    lastCSVLog = currentMillis;

    Serial.print(millis());
    Serial.print(",");

    Serial.print(temperature, 1);
    Serial.print(",");

    Serial.print(humidity, 1);
    Serial.print(",");

    Serial.println(status);
  }

  // ---------------- SCREEN SWITCHING ----------------

  if (currentMillis - lastScreenChange >= SCREEN_INTERVAL) {

    lastScreenChange = currentMillis;

    currentScreen++;

    if (currentScreen > 1) {
      currentScreen = 0;
    }

    updateOLED();
  }
}

// =================================================
// OLED DISPLAY
// =================================================

void updateOLED() {

  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);

  if (currentScreen == 0) {

    display.setTextSize(1);

    display.setCursor(0, 0);
    display.println("SMART CLIMATE");

    display.setTextSize(2);

    display.setCursor(0, 15);
    display.print("T:");
    display.print(temperature, 1);
    display.println(" C");

    display.setCursor(0, 35);
    display.print("H:");
    display.print(humidity, 0);
    display.println(" %");

    display.setTextSize(1);

    display.setCursor(0, 55);
    display.print(status);
  }

  else {

    display.setTextSize(1);

    display.setCursor(0, 0);
    display.println("TEMP STATISTICS");

    display.setCursor(0, 18);
    display.print("Current: ");
    display.print(temperature, 1);
    display.println(" C");

    display.setCursor(0, 32);
    display.print("Maximum: ");
    display.print(maxTemperature, 1);
    display.println(" C");

    display.setCursor(0, 46);
    display.print("Minimum: ");
    display.print(minTemperature, 1);
    display.println(" C");
  }

  display.display();
}
