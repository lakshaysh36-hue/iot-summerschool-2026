
#include <WiFi.h>
#include <WebServer.h>

#include <DHT.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// =========================
// Wi-Fi credentials
// =========================

const char* ssid = "wifi name";
const char* password = "wifi password";

// =========================
// Pin definitions
// =========================

#define DHT_PIN 4
#define DHT_TYPE DHT11

#define LDR_DO_PIN 35

#define SDA_PIN 21
#define SCL_PIN 22

// =========================
// OLED
// =========================

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

// =========================
// Sensors
// =========================

DHT dht(DHT_PIN, DHT_TYPE);
Adafruit_BMP280 bmp;

// =========================
// Web server
// =========================

WebServer server(80);

// =========================
// Sensor variables
// =========================

float temperature = 0;
float humidity = 0;
float pressure = 0;
float altitude = 0;

bool isBright = false;

unsigned long lastSensorRead = 0;
unsigned long lastWiFiCheck = 0;

const unsigned long SENSOR_INTERVAL = 5000;
const unsigned long WIFI_RETRY_INTERVAL = 30000;

// =========================
// Read sensors
// =========================

void readSensors() {

  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  pressure = bmp.readPressure() / 100.0F;

  altitude = bmp.readAltitude(1013.25);

  // 3-pin LDR module
  // DO gives a digital light/dark signal
  int ldrState = digitalRead(LDR_DO_PIN);

  // Most modules give LOW in bright conditions
  if (ldrState == LOW) {
    isBright = true;
  } else {
    isBright = false;
  }

  Serial.println();
  Serial.println("========== WEATHER DATA ==========");

  if (isnan(temperature) || isnan(humidity)) {

    Serial.println("DHT11 reading failed");

  } else {

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Serial.print("Altitude: ");
  Serial.print(altitude);
  Serial.println(" m");

  Serial.print("Light: ");
  Serial.println(isBright ? "BRIGHT" : "DARK");

  Serial.println("==================================");
}

// =========================
// OLED display
// =========================

void updateOLED() {

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println("WiFi Weather Station");

  display.setCursor(0, 12);
  display.print("Temp: ");

  if (isnan(temperature)) {
    display.println("Error");
  } else {
    display.print(temperature, 1);
    display.println(" C");
  }

  display.setCursor(0, 24);
  display.print("Humidity: ");

  if (isnan(humidity)) {
    display.println("Error");
  } else {
    display.print(humidity, 1);
    display.println("%");
  }

  display.setCursor(0, 36);
  display.print("Light: ");
  display.println(isBright ? "BRIGHT" : "DARK");

  display.setCursor(0, 48);
  display.print("IP: ");
  display.println(WiFi.localIP());

  display.display();
}

// =========================
// HTML dashboard
// =========================

String buildHtmlPage() {

  String html = R"rawliteral(
<!DOCTYPE html>
<html>

<head>

  <meta charset="UTF-8">

  <meta http-equiv="refresh" content="10">

  <meta name="viewport"
        content="width=device-width, initial-scale=1">

  <title>ESP32 Weather Dashboard</title>

  <style>

    body {
      font-family: Arial, sans-serif;
      text-align: center;
      margin: 0;
      padding: 20px;
      background: #eaf6ff;
    }

    h1 {
      color: #222;
    }

    .container {
      max-width: 800px;
      margin: auto;
    }

    .cards {
      display: grid;
      grid-template-columns:
        repeat(auto-fit, minmax(200px, 1fr));

      gap: 20px;
      margin-top: 25px;
    }

    .card {
      background: white;
      padding: 25px;
      border-radius: 15px;
      box-shadow: 0 4px 10px rgba(0,0,0,0.15);
    }

    .value {
      font-size: 28px;
      font-weight: bold;
      margin-top: 10px;
    }

    .cool {
      background: #dff3ff;
    }

    .hot {
      background: #ffe0c2;
    }

    .bright {
      background: #fff6b3;
    }

    .dark {
      background: #d9d9d9;
    }

    .info {
      margin-top: 25px;
      font-size: 16px;
    }

  </style>

</head>

<body>

  <div class="container">

    <h1>ESP32 Wi-Fi Weather Dashboard</h1>

    <p>Live local weather station</p>

    <div class="cards">

      <div class="card" id="temperatureCard">
        <h2>Temperature</h2>
        <div class="value" id="temperature">-- C</div>
      </div>

      <div class="card">
        <h2>Humidity</h2>
        <div class="value" id="humidity">-- %</div>
      </div>

      <div class="card">
        <h2>Pressure</h2>
        <div class="value" id="pressure">-- hPa</div>
      </div>

      <div class="card">
        <h2>Altitude</h2>
        <div class="value" id="altitude">-- m</div>
      </div>

      <div class="card" id="lightCard">
        <h2>Light</h2>
        <div class="value" id="light">--</div>
      </div>

    </div>

    <div class="info">

      <p>
        <b>Connected Wi-Fi:</b>
)rawliteral";

  html += ssid;

  html += R"rawliteral(
      </p>

      <p>
        <b>ESP32 IP:</b>
)rawliteral";

  html += WiFi.localIP().toString();

  html += R"rawliteral(
      </p>

    </div>

  </div>

  <script>

    function updateData() {

      fetch('/data')

        .then(response => response.json())

        .then(data => {

          document.getElementById("temperature")
            .innerHTML = data.temp.toFixed(1) + " C";

          document.getElementById("humidity")
            .innerHTML = data.humidity.toFixed(1) + " %";

          document.getElementById("pressure")
            .innerHTML = data.pressure.toFixed(1) + " hPa";

          document.getElementById("altitude")
            .innerHTML = data.altitude.toFixed(1) + " m";

          document.getElementById("light")
            .innerHTML = data.light;

          let tempCard =
            document.getElementById("temperatureCard");

          if (data.temp >= 30) {
            tempCard.className = "card hot";
          } else {
            tempCard.className = "card cool";
          }

          let lightCard =
            document.getElementById("lightCard");

          if (data.light == "BRIGHT") {
            lightCard.className = "card bright";
          } else {
            lightCard.className = "card dark";
          }

        })

        .catch(error => {
          console.log("Error:", error);
        });

    }

    updateData();

    setInterval(updateData, 5000);

  </script>

</body>

</html>
)rawliteral";

  return html;
}

// =========================
// JSON endpoint
// =========================

String buildJson() {

  String json = "{";

  json += "\"temp\":" + String(temperature, 1) + ",";
  json += "\"humidity\":" + String(humidity, 1) + ",";
  json += "\"pressure\":" + String(pressure, 1) + ",";
  json += "\"altitude\":" + String(altitude, 1) + ",";
  json += "\"light\":\"";

  json += isBright ? "BRIGHT" : "DARK";

  json += "\"}";

  return json;
}

// =========================
// Wi-Fi connection
// =========================

void connectWiFi() {

  Serial.print("Connecting to Wi-Fi");

  WiFi.begin(ssid, password);

  int attempts = 0;

  while (WiFi.status() != WL_CONNECTED && attempts < 30) {

    delay(500);

    Serial.print(".");

    attempts++;
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {

    Serial.println("Wi-Fi connected!");

    Serial.print("SSID: ");
    Serial.println(ssid);

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

  } else {

    Serial.println("Wi-Fi connection failed.");

  }
}

// =========================
// Setup
// =========================

void setup() {

  Serial.begin(115200);

  delay(1000);

  Serial.println();
  Serial.println("ESP32 Wi-Fi Weather Dashboard");

  pinMode(LDR_DO_PIN, INPUT);

  Wire.begin(SDA_PIN, SCL_PIN);

  dht.begin();

  // Initialize OLED

  if (!display.begin(
        SSD1306_SWITCHCAPVCC,
        OLED_ADDRESS)) {

    Serial.println("OLED not found!");

  } else {

    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(0, 0);
    display.println("Starting Weather");

    display.display();

  }

  // Initialize BMP280

  bool bmpStarted = false;

  if (bmp.begin(0x76)) {

    bmpStarted = true;

  } else if (bmp.begin(0x77)) {

    bmpStarted = true;

  }

  if (!bmpStarted) {

    Serial.println("BMP280 not found!");

  } else {

    Serial.println("BMP280 detected.");

  }

  connectWiFi();

  readSensors();

  updateOLED();

  // Main webpage

  server.on("/", []() {

    server.send(
      200,
      "text/html",
      buildHtmlPage()
    );

  });

  // JSON data endpoint

  server.on("/data", []() {

    server.send(
      200,
      "application/json",
      buildJson()
    );

  });

  server.begin();

  Serial.println("Web server started!");

  if (WiFi.status() == WL_CONNECTED) {

    Serial.print("Open this IP in your browser: ");

    Serial.println(WiFi.localIP());

  }

}

// =========================
// Main loop
// =========================

void loop() {

  // Required for WebServer
  server.handleClient();

  unsigned long currentMillis = millis();

  // Read sensors every 5 seconds

  if (currentMillis - lastSensorRead >= SENSOR_INTERVAL) {

    lastSensorRead = currentMillis;

    readSensors();

    updateOLED();

  }

  // Check Wi-Fi every 30 seconds

  if (currentMillis - lastWiFiCheck >= WIFI_RETRY_INTERVAL) {

    lastWiFiCheck = currentMillis;

    if (WiFi.status() != WL_CONNECTED) {

      Serial.println("Wi-Fi disconnected.");

      Serial.println("Trying to reconnect...");

      WiFi.disconnect();

      WiFi.begin(ssid, password);

    }

  }

}
