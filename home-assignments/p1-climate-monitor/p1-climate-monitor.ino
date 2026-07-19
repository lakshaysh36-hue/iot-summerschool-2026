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

float temperature = 0;
float humidity = 0;

String status = "STARTING";

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
}

void loop() {

  TempAndHumidity data = dht.getTempAndHumidity();

  temperature = data.temperature;
  humidity = data.humidity;

  if (isnan(temperature) || isnan(humidity)) {

    Serial.println("DHT11 reading failed!");

    delay(2000);
    return;
  }

  // Alert logic
  if (temperature > 38 || humidity > 80) {

    status = "DANGER";

    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);

    digitalWrite(BUZZER_SIGNAL, HIGH);
    delay(1000);
    digitalWrite(BUZZER_SIGNAL, LOW);
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

  // OLED display
  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);

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

  display.display();

  delay(2000);
}
