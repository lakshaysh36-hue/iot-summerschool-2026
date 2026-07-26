#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BMP280.h>
#include <math.h>

// =====================================================
// OLED
// =====================================================

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);


// =====================================================
// BMP280
// =====================================================

Adafruit_BMP280 bmp;

#define BMP280_ADDRESS 0x76


// =====================================================
// PIN DEFINITIONS
// =====================================================

const int POT_PIN = 34;

const int GREEN_LED = 25;
const int RED_LED = 26;


// =====================================================
// PRESSURE LOG
// =====================================================

const int LOG_SIZE = 24;

float pressureLog[LOG_SIZE];

int logIndex = 0;
int readingsStored = 0;


// =====================================================
// TIMING
// =====================================================

// One reading every 30 seconds
const unsigned long READING_INTERVAL = 30000;

// Change OLED page every 5 seconds
const unsigned long PAGE_INTERVAL = 3000;

unsigned long lastReadingTime = 0;
unsigned long lastPageChange = 0;


// =====================================================
// SENSOR VALUES
// =====================================================

float pressure = 0.0;
float temperature = 0.0;
float altitude = 0.0;
float seaLevelPressure = 0.0;

String trend = "STABLE";


// =====================================================
// OLED PAGE
// =====================================================

int currentPage = 0;


// =====================================================
// FUNCTION DECLARATIONS
// =====================================================

void takeReading();
void calculateTrend();
void updateLEDs();
void updateDisplay();
void printSerialData();

float calculateSeaLevelPressure(
  float pressure_hPa,
  float altitude_m
);


// =====================================================
// SETUP
// =====================================================

void setup() {

  Serial.begin(115200);

  delay(1000);

  Serial.println();
  Serial.println("================================");
  Serial.println("IoT PRESSURE & ALTITUDE LOGGER");
  Serial.println("================================");


  // -----------------------------
  // Pin configuration
  // -----------------------------

  pinMode(POT_PIN, INPUT);

  pinMode(GREEN_LED, OUTPUT);

  pinMode(RED_LED, OUTPUT);

  digitalWrite(GREEN_LED, LOW);

  digitalWrite(RED_LED, LOW);


  // -----------------------------
  // I2C initialization
  // -----------------------------

  Wire.begin(21, 22);


  // -----------------------------
  // OLED initialization
  // -----------------------------

  if (!display.begin(
        SSD1306_SWITCHCAPVCC,
        0x3C
      )) {

    Serial.println("OLED initialization failed!");

    while (true);
  }

  Serial.println("OLED initialized successfully");


  // -----------------------------
  // BMP280 initialization
  // -----------------------------

  if (!bmp.begin(0x76)) {

    Serial.println("BMP280 initialization failed!");

    while (true);
  }

  Serial.println("BMP280 initialized successfully");


  // -----------------------------
  // BMP280 configuration
  // -----------------------------

  bmp.setSampling(

    Adafruit_BMP280::MODE_NORMAL,

    Adafruit_BMP280::SAMPLING_X2,

    Adafruit_BMP280::SAMPLING_X16,

    Adafruit_BMP280::FILTER_X16,

    Adafruit_BMP280::STANDBY_MS_500

  );


  // -----------------------------
  // Initialize pressure array
  // -----------------------------

  for (int i = 0; i < LOG_SIZE; i++) {

    pressureLog[i] = 0.0;
  }


  // -----------------------------
  // Startup screen
  // -----------------------------

  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);

  display.setCursor(0, 0);

  display.println("PRESSURE LOGGER");

  display.setCursor(0, 20);

  display.println("SYSTEM READY");

  display.setCursor(0, 40);

  display.println("Starting sensors...");

  display.display();

  delay(2000);


  // Take first reading immediately

  takeReading();

  lastReadingTime = millis();

  lastPageChange = millis();
}


// =====================================================
// LOOP
// =====================================================

void loop() {

  unsigned long currentTime = millis();


  // Take reading every 30 seconds

  if (currentTime - lastReadingTime >= READING_INTERVAL) {

    takeReading();

    lastReadingTime = currentTime;
  }


  // Change OLED page every 5 seconds

  if (currentTime - lastPageChange >= PAGE_INTERVAL) {

    currentPage++;

    if (currentPage > 1) {

      currentPage = 0;
    }

    lastPageChange = currentTime;
  }


  // Update display

  updateDisplay();


  delay(100);
}


// =====================================================
// TAKE SENSOR READING
// =====================================================

void takeReading() {


  // Pressure in hPa

  pressure = bmp.readPressure() / 100.0;


  // Temperature in Celsius

  temperature = bmp.readTemperature();


  // Read potentiometer

  int potValue = analogRead(POT_PIN);


  // Convert potentiometer reading to altitude 0-2000 m

  altitude = map(
    potValue,
    0,
    4095,
    0,
    2000
  );


  // Calculate sea-level pressure

  seaLevelPressure =
    calculateSeaLevelPressure(
      pressure,
      altitude
    );


  // Store pressure in circular buffer

  pressureLog[logIndex] = pressure;

  logIndex++;

  if (logIndex >= LOG_SIZE) {

    logIndex = 0;
  }


  // Count stored readings

  if (readingsStored < LOG_SIZE) {

    readingsStored++;
  }


  // Calculate pressure trend

  calculateTrend();


  // Update LEDs

  updateLEDs();


  // Print to Serial Monitor

  printSerialData();
}


// =====================================================
// CALCULATE TREND
// =====================================================

void calculateTrend() {


  // Cannot calculate trend with only one reading

  if (readingsStored < 2) {

    trend = "STABLE";

    return;
  }


  // Newest reading

  int newestIndex =
    (logIndex - 1 + LOG_SIZE) % LOG_SIZE;


  // Oldest reading

  int oldestIndex;


  if (readingsStored < LOG_SIZE) {

    oldestIndex = 0;
  }

  else {

    oldestIndex = logIndex;
  }


  float newestPressure =
    pressureLog[newestIndex];


  float oldestPressure =
    pressureLog[oldestIndex];


  float difference =
    newestPressure - oldestPressure;


  /*
    Assignment threshold:

    +50 Pa  = RISING
    -50 Pa  = FALLING

    Since pressure is stored in hPa:

    50 Pa = 0.5 hPa
  */


  if (difference > 0.5) {

    trend = "RISING";
  }

  else if (difference < -0.5) {

    trend = "FALLING";
  }

  else {

    trend = "STABLE";
  }
}


// =====================================================
// SEA-LEVEL PRESSURE FORMULA
// =====================================================

float calculateSeaLevelPressure(
  float pressure_hPa,
  float altitude_m
) {


  /*
    P0 = P / pow(1 - altitude / 44330.0, 5.255)

    P0 = sea-level pressure
    P  = measured pressure
    altitude_m = local altitude
  */


  float result =

    pressure_hPa /

    pow(
      1.0 - altitude_m / 44330.0,
      5.255
    );


  return result;
}


// =====================================================
// LED CONTROL
// =====================================================

void updateLEDs() {


  if (trend == "FALLING") {

    digitalWrite(RED_LED, HIGH);

    digitalWrite(GREEN_LED, LOW);
  }

  else {

    // Stable or rising pressure

    digitalWrite(GREEN_LED, HIGH);

    digitalWrite(RED_LED, LOW);
  }
}


// =====================================================
// OLED DISPLAY
// =====================================================

void updateDisplay() {


  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);


  // =================================================
  // PAGE 1: SENSOR DATA
  // =================================================

  if (currentPage == 0) {


    display.setTextSize(1);


    display.setCursor(0, 0);

    display.println("PRESSURE LOGGER");


    display.setCursor(0, 14);

    display.print("P: ");

    display.print(pressure, 1);

    display.println(" hPa");


    display.setCursor(0, 27);

    display.print("T: ");

    display.print(temperature, 1);

    display.println(" C");


    display.setCursor(0, 40);

    display.print("Alt: ");

    display.print(altitude, 0);

    display.println(" m");


    display.setCursor(0, 53);

    display.print("SLP: ");

    display.print(seaLevelPressure, 1);

    display.println(" hPa");
  }


  // =================================================
  // PAGE 2: PRESSURE TREND
  // =================================================

  else {


    display.setTextSize(1);

    display.setCursor(0, 0);

    display.println("PRESSURE TREND");


    display.setTextSize(2);

    display.setCursor(10, 18);


    if (trend == "RISING") {

      display.print("^");
    }

    else if (trend == "FALLING") {

      display.print("v");
    }

    else {

      display.print("->");
    }


    display.setTextSize(1);

    display.setCursor(55, 22);

    display.println(trend);


    display.setCursor(0, 45);

    display.print("Readings: ");

    display.print(readingsStored);

    display.print("/");

    display.println(LOG_SIZE);
  }


  display.display();
}


// =====================================================
// SERIAL MONITOR OUTPUT
// =====================================================

void printSerialData() {


  Serial.println();

  Serial.println("----------------------------------------");

  Serial.println("NEW PRESSURE READING");

  Serial.println("----------------------------------------");


  Serial.print("Pressure       : ");

  Serial.print(pressure, 2);

  Serial.println(" hPa");


  Serial.print("Temperature    : ");

  Serial.print(temperature, 2);

  Serial.println(" C");


  Serial.print("Altitude       : ");

  Serial.print(altitude, 2);

  Serial.println(" m");


  Serial.print("Sea-Level P    : ");

  Serial.print(seaLevelPressure, 2);

  Serial.println(" hPa");


  Serial.print("Trend          : ");

  Serial.println(trend);


  Serial.print("Reading Number : ");

  Serial.print(readingsStored);

  Serial.print("/");

  Serial.println(LOG_SIZE);


  Serial.println("----------------------------------------");
}
