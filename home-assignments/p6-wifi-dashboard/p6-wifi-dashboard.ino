#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BMP280.h>

// ================= WIFI =================
const char* ssid = "wifi name";
const char* password = "wifi password";

// ================= DHT11 =================
#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// ================= BMP280 =================
Adafruit_BMP280 bmp;

// ================= LDR =================
#define LDR_PIN 34


// Calibrated limits used to convert the LDR reading into a percentage.
// Update these values after measuring the actual dark and bright readings.
int LDR_DARK = 0;
int LDR_BRIGHT = 4095;

// ================= OLED =================
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

// ================= WEB SERVER =================
WebServer server(80);

// ================= SENSOR VARIABLES =================
float temperature = 0;
float humidity = 0;
float pressure = 0;
float altitude = 0;

int lightPercent = 0;
bool bmpFound = false;

// ================= TIMERS =================
unsigned long lastSensorRead = 0;
unsigned long lastWiFiCheck = 0;

const unsigned long SENSOR_INTERVAL = 5000;
const unsigned long WIFI_INTERVAL = 30000;

// ================= HTML PAGE =================
String buildHtmlPage() {

  String html = R"rawliteral(

<!DOCTYPE html>
<html>

<head>

<meta charset="UTF-8">

<meta name="viewport"
content="width=device-width, initial-scale=1">

<title>ESP32 Wi-Fi Weather Dashboard</title>

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
  max-width: 900px;
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

  box-shadow:
  0 4px 10px rgba(0,0,0,0.15);
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

.info {
  margin-top: 25px;
  font-size: 16px;
}

</style>

</head>

<body>

<div class="container">

<h1>ESP32 Wi-Fi Weather Dashboard</h1>

<p>Live Local Weather Station</p>

<div class="cards">

<div class="card" id="temperatureCard">

<h2>Temperature</h2>

<div class="value" id="temperature">
-- °C
</div>

</div>


<div class="card">

<h2>Humidity</h2>

<div class="value" id="humidity">
-- %
</div>

</div>


<div class="card">

<h2>Pressure</h2>

<div class="value" id="pressure">
-- hPa
</div>

</div>


<div class="card">

<h2>Altitude</h2>

<div class="value" id="altitude">
-- m
</div>

</div>


<div class="card">

<h2>Light Level</h2>

<div class="value" id="light">
-- %
</div>

</div>

</div>

<div class="info">

<p>
<b>Wi-Fi:</b>
)rawliteral";

  html += WiFi.SSID();

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
.innerHTML =
data.temp.toFixed(1) + " °C";

document.getElementById("humidity")
.innerHTML =
data.humidity.toFixed(1) + " %";

document.getElementById("pressure")
.innerHTML =
data.pressure.toFixed(1) + " hPa";

document.getElementById("altitude")
.innerHTML =
data.altitude.toFixed(1) + " m";

document.getElementById("light")
.innerHTML =
data.light + " %";


let temperatureCard =
document.getElementById("temperatureCard");


if (data.temp >= 30) {

temperatureCard.className =
"card hot";

}

else {

temperatureCard.className =
"card cool";

}

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

// ================= JSON DATA =================
String buildJson() {

  String json = "{";

  json += "\"temp\":" + String(temperature, 2) + ",";
  json += "\"humidity\":" + String(humidity, 2) + ",";
  json += "\"pressure\":" + String(pressure, 2) + ",";
  json += "\"altitude\":" + String(altitude, 2) + ",";
  json += "\"light\":" + String(lightPercent);

  json += "}";

  return json;
}

// ================= OLED DISPLAY =================
void updateOLED() {

  display.clearDisplay();

  display.setTextSize(1);

  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);

  display.println("WEATHER STATION");

  display.println();

  display.print("Temp: ");
  display.print(temperature, 1);
  display.println(" C");

  display.print("Hum:  ");
  display.print(humidity, 1);
  display.println(" %");

  display.print("Light: ");
  display.print(lightPercent);
  display.println(" %");

  display.println();

  display.print("IP:");

  display.println(WiFi.localIP());

  display.display();
}

// ================= READ SENSORS =================
// Read all connected sensors and update the OLED and Serial Monitor
void readSensors() {

  // DHT11
  float newTemp = dht.readTemperature();

  float newHumidity = dht.readHumidity();

  if (!isnan(newTemp)) {
    temperature = newTemp;
  }

  if (!isnan(newHumidity)) {
    humidity = newHumidity;
  }


  // BMP280
  if (bmpFound) {

    pressure =
      bmp.readPressure() / 100.0;

    altitude =
      bmp.readAltitude(1013.25);
  }


  // LDR
  int rawLight =
    analogRead(LDR_PIN);


  lightPercent =
    map(
      rawLight,
      LDR_DARK,
      LDR_BRIGHT,
      0,
      100
    );


  lightPercent =
    constrain(
      lightPercent,
      0,
      100
    );


  // Serial Monitor
  Serial.println();

  Serial.println(
    "========== WEATHER DATA =========="
  );

  Serial.print("Temperature: ");

  Serial.print(temperature);

  Serial.println(" C");


  Serial.print("Humidity: ");

  Serial.print(humidity);

  Serial.println(" %");


  Serial.print("Pressure: ");

  Serial.print(pressure);

  Serial.println(" hPa");


  Serial.print("Altitude: ");

  Serial.print(altitude);

  Serial.println(" m");


  Serial.print("LDR Raw Value: ");

  Serial.println(rawLight);


  Serial.print("Light: ");

  Serial.print(lightPercent);

  Serial.println(" %");


  Serial.println(
    "=================================="
  );


  updateOLED();
}

// ================= WIFI RECONNECTION =================
void checkWiFi() {

  if (WiFi.status() != WL_CONNECTED) {

    Serial.println(
      "Wi-Fi disconnected. Reconnecting..."
    );

    WiFi.disconnect();

    WiFi.begin(
      ssid,
      password
    );

    unsigned long startTime =
      millis();

    while (
      WiFi.status() != WL_CONNECTED &&
      millis() - startTime < 10000
    ) {

      delay(500);

      Serial.print(".");
    }

    Serial.println();

    if (WiFi.status() == WL_CONNECTED) {

      Serial.println(
        "Wi-Fi reconnected!"
      );

      Serial.print(
        "IP Address: "
      );

      Serial.println(
        WiFi.localIP()
      );
    }
  }
}

// ================= SETUP =================
void setup() {

  Serial.begin(115200);

  delay(1000);

  Serial.println();

  Serial.println(
    "ESP32 Wi-Fi Weather Dashboard"
  );


  // DHT
  dht.begin();


  // I2C
  Wire.begin(
    21,
    22
  );


  // OLED
  if (
    !display.begin(
      SSD1306_SWITCHCAPVCC,
      OLED_ADDRESS
    )
  ) {

    Serial.println(
      "OLED not found!"
    );
  }

  else {

    display.clearDisplay();

    display.setTextSize(1);

    display.setTextColor(
      SSD1306_WHITE
    );

    display.setCursor(0, 0);

    display.println(
      "Starting..."
    );

    display.display();
  }


  // BMP280
  if (
    bmp.begin(0x76)
  ) {

    bmpFound = true;

    Serial.println(
      "BMP280 found at 0x76"
    );
  }

  else if (
    bmp.begin(0x77)
  ) {

    bmpFound = true;

    Serial.println(
      "BMP280 found at 0x77"
    );
  }

  else {

    Serial.println(
      "BMP280 not found!"
    );
  }


  // Wi-Fi
  WiFi.begin(
    ssid,
    password
  );

  Serial.print(
    "Connecting to Wi-Fi"
  );

  while (
    WiFi.status() != WL_CONNECTED
  ) {

    delay(500);

    Serial.print(".");
  }

  Serial.println();

  Serial.println(
    "Wi-Fi connected!"
  );

  Serial.print(
    "SSID: "
  );

  Serial.println(
    WiFi.SSID()
  );

  Serial.print(
    "IP Address: "
  );

  Serial.println(
    WiFi.localIP()
  );


  // Webpage
  server.on(
    "/",
    HTTP_GET,
    []() {

      server.send(
        200,
        "text/html",
        buildHtmlPage()
      );
    }
  );


  // JSON endpoint
  server.on(
    "/data",
    HTTP_GET,
    []() {

      server.send(
        200,
        "application/json",
        buildJson()
      );
    }
  );


  server.begin();

  Serial.println(
    "Web server started!"
  );


  // First sensor reading
  readSensors();
}

// ================= LOOP =================
void loop() {

  server.handleClient();


  if (
    millis() - lastSensorRead >=
    SENSOR_INTERVAL
  ) {

    readSensors();

    lastSensorRead =
      millis();
  }


  if (
    millis() - lastWiFiCheck >=
    WIFI_INTERVAL
  ) {

    checkWiFi();

    lastWiFiCheck =
      millis();
  }
}
