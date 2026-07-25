#include <WiFi.h>
#include <WebServer.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// =================================================
// DHT11
// =================================================

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// =================================================
// SENSOR PINS
// =================================================

#define MQ2_PIN 35
#define LDR_PIN 34

#define TRIG_PIN 18
#define ECHO_PIN 19

// =================================================
// OUTPUT PINS
// =================================================

#define RELAY_FAN 26
#define RELAY_LIGHT 27

#define BUZZER_PIN 14

#define RED_LED 25
#define GREEN_LED 2
#define YELLOW_LED 33

// =================================================
// BUTTON PINS
// =================================================

#define FAN_BUTTON 0
#define LIGHT_BUTTON 32

// =================================================
// OLED
// =================================================

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

// =================================================
// WIFI
// =================================================

const char* ssid = "Airtel_mada_0849";
const char* password = "air60558";

// =================================================
// MQTT
// =================================================

const char* mqtt_server = "broker.hivemq.com";

const char* mqtt_topic =
  "iitjammu/lakshay/home";

// =================================================
// WEB SERVER
// =================================================

WebServer server(80);

// =================================================
// MQTT
// =================================================

WiFiClient espClient;

PubSubClient mqttClient(espClient);

// =================================================
// SENSOR VALUES
// =================================================

float temperature = 0.0;

float humidity = 0.0;

int gasRaw = 0;

int gasPercent = 0;

int ldrRaw = 0;

int lightPercent = 0;

float distance = 0.0;

bool presenceDetected = false;

// =================================================
// SYSTEM STATES
// =================================================

bool fanOn = false;

bool lightOn = false;

bool gasAlert = false;

// =================================================
// TIMERS
// =================================================

unsigned long lastSensorRead = 0;

unsigned long lastMQTTPublish = 0;

unsigned long lastOLEDUpdate = 0;

unsigned long lastUltrasonicRead = 0;

unsigned long lastMotionDetected = 0;

unsigned long fanOverrideStart = 0;

unsigned long lightOverrideStart = 0;

unsigned long lastFanButtonPress = 0;

unsigned long lastLightButtonPress = 0;

// =================================================
// TIMING CONSTANTS
// =================================================

const unsigned long SENSOR_INTERVAL = 5000;

const unsigned long MQTT_INTERVAL = 30000;

const unsigned long OLED_INTERVAL = 5000;

const unsigned long ULTRASONIC_INTERVAL = 500;

const unsigned long NO_PRESENCE_TIME = 180000;

const unsigned long OVERRIDE_TIME = 600000;

const unsigned long BUTTON_DEBOUNCE = 500;

// =================================================
// OVERRIDE STATES
// =================================================

bool fanManualOverride = false;

bool lightManualOverride = false;

// =================================================
// OLED SCREEN
// =================================================

int oledScreen = 0;

// =================================================
// READ ULTRASONIC SENSOR
// =================================================

void readUltrasonic() {

  digitalWrite(TRIG_PIN, LOW);

  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);

  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(
    ECHO_PIN,
    HIGH,
    30000
  );

  if (duration == 0) {

    distance = 999;

    presenceDetected = false;

    return;
  }

  distance = duration * 0.0343 / 2.0;

  // Presence threshold: 150 cm

  if (distance < 150) {

    presenceDetected = true;

    lastMotionDetected = millis();
  }

  else {

    presenceDetected = false;
  }
}

// =================================================
// READ ALL SENSORS
// =================================================

void readSensors() {

  // DHT11

  float newTemperature =
    dht.readTemperature();

  float newHumidity =
    dht.readHumidity();

  if (!isnan(newTemperature)) {

    temperature = newTemperature;
  }

  if (!isnan(newHumidity)) {

    humidity = newHumidity;
  }

  // MQ-2

  gasRaw = analogRead(MQ2_PIN);

  gasPercent = map(
    gasRaw,
    0,
    4095,
    0,
    100
  );

  gasPercent = constrain(
    gasPercent,
    0,
    100
  );

  // LDR

  ldrRaw = analogRead(LDR_PIN);

  lightPercent = map(
    ldrRaw,
    0,
    4095,
    0,
    100
  );

  lightPercent = constrain(
    lightPercent,
    0,
    100
  );

  Serial.println();

  Serial.println("====================");

  Serial.println("SENSOR DATA");

  Serial.println("====================");

  Serial.print("Temperature: ");

  Serial.print(temperature);

  Serial.println(" C");

  Serial.print("Humidity: ");

  Serial.print(humidity);

  Serial.println(" %");

  Serial.print("Gas Raw: ");

  Serial.println(gasRaw);

  Serial.print("Gas: ");

  Serial.print(gasPercent);

  Serial.println(" %");

  Serial.print("LDR Raw: ");

  Serial.println(ldrRaw);

  Serial.print("Light: ");

  Serial.print(lightPercent);

  Serial.println(" %");

  Serial.print("Distance: ");

  Serial.print(distance);

  Serial.println(" cm");

  Serial.print("Presence: ");

  Serial.println(
    presenceDetected
    ? "DETECTED"
    : "NOT DETECTED"
  );
}

// =================================================
// APPLY AUTOMATION RULES
// =================================================

void applyAutomationRules() {

  // =================================================
  // GAS SAFETY SHUTDOWN
  // =================================================

  if (gasPercent > 60) {

    gasAlert = true;

    setFan(false);

    setLight(false);

    digitalWrite(
      BUZZER_PIN,
      HIGH
    );

    digitalWrite(
      RED_LED,
      HIGH
    );

    digitalWrite(
      GREEN_LED,
      LOW
    );

    Serial.println();

    Serial.println("!!! GAS ALERT !!!");

    Serial.println(
      "ALL RELAYS FORCED OFF"
    );

    return;
  }

  else {

    gasAlert = false;

    digitalWrite(
      BUZZER_PIN,
      LOW
    );

    digitalWrite(
      RED_LED,
      LOW
    );

    digitalWrite(
      GREEN_LED,
      HIGH
    );
  }

  // =================================================
  // FAN AUTOMATION WITH HYSTERESIS
  // =================================================

  if (!fanManualOverride) {

    if (
      !fanOn &&
      temperature > 32
    ) {

      setFan(true);

      Serial.println(
        "FAN AUTO ON"
      );
    }

    if (
      fanOn &&
      temperature < 28
    ) {

      setFan(false);

      Serial.println(
        "FAN AUTO OFF"
      );
    }
  }

  // =================================================
  // LIGHT AUTOMATION
  // =================================================

  if (!lightManualOverride) {

    // Dark + presence detected

    if (
      lightPercent < 20 &&
      presenceDetected
    ) {

      setLight(true);

      Serial.println(
        "LIGHT AUTO ON"
      );

      Serial.println(
        "DARK + PRESENCE DETECTED"
      );
    }

    // Daylight

    if (
      lightPercent > 60
    ) {

      setLight(false);

      Serial.println(
        "LIGHT AUTO OFF - DAYLIGHT"
      );
    }

    // No presence for 3 minutes

    if (
      millis() - lastMotionDetected
      >= NO_PRESENCE_TIME
    ) {

      setLight(false);

      Serial.println(
        "LIGHT AUTO OFF - NO PRESENCE"
      );
    }
  }
}

// =================================================
// FAN CONTROL
// =================================================

void setFan(bool state) {

  fanOn = state;

  if (fanOn) {

    // Active LOW relay

    digitalWrite(
      RELAY_FAN,
      LOW
    );
  }

  else {

    digitalWrite(
      RELAY_FAN,
      HIGH
    );
  }
}

// =================================================
// LIGHT CONTROL
// =================================================

void setLight(bool state) {

  lightOn = state;

  if (lightOn) {

    digitalWrite(
      RELAY_LIGHT,
      LOW
    );
  }

  else {

    digitalWrite(
      RELAY_LIGHT,
      HIGH
    );
  }
}

// =================================================
// BUTTON HANDLING
// =================================================

void checkButtons() {

  // Fan button

  if (
    digitalRead(FAN_BUTTON) == LOW &&
    millis() - lastFanButtonPress
    > BUTTON_DEBOUNCE
  ) {

    lastFanButtonPress = millis();

    fanManualOverride = true;

    fanOverrideStart = millis();

    setFan(!fanOn);

    digitalWrite(
      YELLOW_LED,
      HIGH
    );

    Serial.println(
      "FAN MANUAL OVERRIDE"
    );
  }

  // Light button

  if (
    digitalRead(LIGHT_BUTTON) == LOW &&
    millis() - lastLightButtonPress
    > BUTTON_DEBOUNCE
  ) {

    lastLightButtonPress = millis();

    lightManualOverride = true;

    lightOverrideStart = millis();

    setLight(!lightOn);

    digitalWrite(
      YELLOW_LED,
      HIGH
    );

    Serial.println(
      "LIGHT MANUAL OVERRIDE"
    );
  }

  // Fan override timeout

  if (
    fanManualOverride &&
    millis() - fanOverrideStart
    >= OVERRIDE_TIME
  ) {

    fanManualOverride = false;

    Serial.println(
      "FAN OVERRIDE EXPIRED"
    );
  }

  // Light override timeout

  if (
    lightManualOverride &&
    millis() - lightOverrideStart
    >= OVERRIDE_TIME
  ) {

    lightManualOverride = false;

    Serial.println(
      "LIGHT OVERRIDE EXPIRED"
    );
  }

  if (
    !fanManualOverride &&
    !lightManualOverride
  ) {

    digitalWrite(
      YELLOW_LED,
      LOW
    );
  }
}

// =================================================
// GET UPTIME
// =================================================

String getUptime() {

  unsigned long seconds =
    millis() / 1000;

  unsigned long days =
    seconds / 86400;

  seconds %= 86400;

  unsigned long hours =
    seconds / 3600;

  seconds %= 3600;

  unsigned long minutes =
    seconds / 60;

  return String(days) +
         "d " +
         String(hours) +
         "h " +
         String(minutes) +
         "m";
}

// =================================================
// OLED
// =================================================

void updateOLED() {

  display.clearDisplay();

  display.setTextColor(
    SSD1306_WHITE
  );

  display.setCursor(
    0,
    0
  );

  if (oledScreen == 0) {

    display.setTextSize(2);

    display.println(
      "CLIMATE"
    );

    display.setTextSize(1);

    display.print(
      "Temp: "
    );

    display.print(
      temperature
    );

    display.println(
      " C"
    );

    display.print(
      "Hum: "
    );

    display.print(
      humidity
    );

    display.println(
      " %"
    );
  }

  else if (oledScreen == 1) {

    display.setTextSize(2);

    display.println(
      "SENSORS"
    );

    display.setTextSize(1);

    display.print(
      "Gas: "
    );

    display.print(
      gasPercent
    );

    display.println(
      " %"
    );

    display.print(
      "Light: "
    );

    display.print(
      lightPercent
    );

    display.println(
      " %"
    );

    display.print(
      "Dist: "
    );

    display.print(
      distance
    );

    display.println(
      " cm"
    );

    display.print(
      "Person: "
    );

    display.println(
      presenceDetected
      ? "YES"
      : "NO"
    );
  }

  else {

    display.setTextSize(2);

    display.println(
      "SYSTEM"
    );

    display.setTextSize(1);

    display.print(
      "Fan: "
    );

    display.println(
      fanOn
      ? "ON"
      : "OFF"
    );

    display.print(
      "Light: "
    );

    display.println(
      lightOn
      ? "ON"
      : "OFF"
    );

    display.print(
      "Up: "
    );

    display.println(
      getUptime()
    );
  }

  display.display();

  oledScreen++;

  if (
    oledScreen > 2
  ) {

    oledScreen = 0;
  }
}

// =================================================
// MQTT PUBLISH
// =================================================

void publishMQTT() {

  String payload = "{";

  payload += "\"temp\":";

  payload += String(
    temperature,
    1
  );

  payload += ",\"humidity\":";

  payload += String(
    humidity,
    1
  );

  payload += ",\"gas\":";

  payload += String(
    gasPercent
  );

  payload += ",\"distance\":";

  payload += String(
    distance,
    1
  );

  payload += ",\"presence\":";

  payload += presenceDetected
    ? "true"
    : "false";

  payload += ",\"light\":";

  payload += String(
    lightPercent
  );

  payload += ",\"fan\":";

  payload += fanOn
    ? "true"
    : "false";

  payload += ",\"light_relay\":";

  payload += lightOn
    ? "true"
    : "false";

  payload += ",\"alert\":";

  payload += gasAlert
    ? "true"
    : "false";

  payload += "}";

  Serial.println();

  Serial.println(
    "MQTT PAYLOAD:"
  );

  Serial.println(
    payload
  );

  mqttClient.publish(
    mqtt_topic,
    payload.c_str()
  );
}

// =================================================
// WIFI
// =================================================

void connectWiFi() {

  Serial.print(
    "Connecting to WiFi"
  );

  WiFi.begin(
    ssid,
    password
  );

  while (
    WiFi.status()
    != WL_CONNECTED
  ) {

    delay(500);

    Serial.print(
      "."
    );
  }

  Serial.println();

  Serial.println(
    "WiFi Connected"
  );

  Serial.print(
    "IP Address: "
  );

  Serial.println(
    WiFi.localIP()
  );
}

// =================================================
// MQTT CONNECTION
// =================================================

void connectMQTT() {

  while (
    !mqttClient.connected()
  ) {

    Serial.print(
      "Connecting to MQTT..."
    );

    String clientID =
      "ESP32HomeHub-";

    clientID += String(
      random(0xffff),
      HEX
    );

    if (
      mqttClient.connect(
        clientID.c_str()
      )
    ) {

      Serial.println(
        "Connected"
      );
    }

    else {

      Serial.print(
        "Failed, State: "
      );

      Serial.println(
        mqttClient.state()
      );

      delay(2000);
    }
  }
}

// =================================================
// WEB DASHBOARD
// =================================================

void handleRoot() {

  String html = R"rawliteral(

<!DOCTYPE html>

<html>

<head>

<meta name="viewport"
content="width=device-width,
initial-scale=1">

<meta http-equiv="refresh"
content="5">

<title>IoT Home Hub</title>

<style>

body {
  font-family: Arial;
  text-align: center;
  background: #f2f2f2;
}

.card {
  background: white;
  padding: 20px;
  margin: 15px auto;
  max-width: 500px;
  border-radius: 12px;
  box-shadow: 0 0 10px #aaa;
}

.value {
  font-size: 20px;
  margin: 10px;
}

button {
  padding: 12px 20px;
  margin: 5px;
  font-size: 16px;
}

.alert {
  color: red;
  font-weight: bold;
}

.normal {
  color: green;
  font-weight: bold;
}

</style>

</head>

<body>

<h1>
IoT Home Automation Hub
</h1>

<div class="card">

<h2>
Environment
</h2>

<div class="value">

Temperature:
)rawliteral";

  html += String(
    temperature,
    1
  );

  html += R"rawliteral(
 °C
</div>

<div class="value">

Humidity:
)rawliteral";

  html += String(
    humidity,
    1
  );

  html += R"rawliteral(
 %
</div>

</div>

<div class="card">

<h2>
Gas Sensor
</h2>

<div class="value">

Gas:
)rawliteral";

  html += String(
    gasPercent
  );

  html += R"rawliteral(
 %
</div>

<div class="value">

Status:
<span class=")rawliteral";

  html += gasAlert
    ? "alert"
    : "normal";

  html += R"rawliteral(">

)rawliteral";

  html += gasAlert
    ? "DANGER"
    : "SAFE";

  html += R"rawliteral(

</span>

</div>

</div>

<div class="card">

<h2>
Presence Sensor
</h2>

<div class="value">

Distance:
)rawliteral";

  html += String(
    distance,
    1
  );

  html += R"rawliteral(
 cm
</div>

<div class="value">

Person:
)rawliteral";

  html += presenceDetected
    ? "DETECTED"
    : "NOT DETECTED";

  html += R"rawliteral(

</div>

</div>

<div class="card">

<h2>
Light Sensor
</h2>

<div class="value">

Light Level:
)rawliteral";

  html += String(
    lightPercent
  );

  html += R"rawliteral(
 %
</div>

</div>

<div class="card">

<h2>
Relay States
</h2>

<div class="value">

Fan:
)rawliteral";

  html += fanOn
    ? "ON"
    : "OFF";

  html += R"rawliteral(

</div>

<div class="value">

Light Relay:
)rawliteral";

  html += lightOn
    ? "ON"
    : "OFF";

  html += R"rawliteral(

</div>

<a href="/fan">

<button>
Toggle Fan
</button>

</a>

<a href="/light">

<button>
Toggle Light
</button>

</a>

</div>

<div class="card">

<h2>
System
</h2>

<div class="value">

Uptime:
)rawliteral";

  html += getUptime();

  html += R"rawliteral(

</div>

<div class="value">

IP:
)rawliteral";

  html += WiFi.localIP().toString();

  html += R"rawliteral(

</div>

</div>

</body>

</html>

)rawliteral";

  server.send(
    200,
    "text/html",
    html
  );
}

// =================================================
// WEB FAN CONTROL
// =================================================

void handleFan() {

  if (
    !gasAlert
  ) {

    fanManualOverride = true;

    fanOverrideStart =
      millis();

    setFan(
      !fanOn
    );
  }

  server.sendHeader(
    "Location",
    "/"
  );

  server.send(
    303
  );
}

// =================================================
// WEB LIGHT CONTROL
// =================================================

void handleLight() {

  if (
    !gasAlert
  ) {

    lightManualOverride = true;

    lightOverrideStart =
      millis();

    setLight(
      !lightOn
    );
  }

  server.sendHeader(
    "Location",
    "/"
  );

  server.send(
    303
  );
}

// =================================================
// SETUP
// =================================================

void setup() {

  Serial.begin(
    115200
  );

  delay(
    1000
  );

  Serial.println();

  Serial.println(
    "FULL IoT HOME AUTOMATION HUB"
  );

  Serial.println(
    "HC-SR04 PRESENCE SENSOR"
  );

  // Output pins

  pinMode(
    RELAY_FAN,
    OUTPUT
  );

  pinMode(
    RELAY_LIGHT,
    OUTPUT
  );

  pinMode(
    BUZZER_PIN,
    OUTPUT
  );

  pinMode(
    RED_LED,
    OUTPUT
  );

  pinMode(
    GREEN_LED,
    OUTPUT
  );

  pinMode(
    YELLOW_LED,
    OUTPUT
  );

  // Ultrasonic

  pinMode(
    TRIG_PIN,
    OUTPUT
  );

  pinMode(
    ECHO_PIN,
    INPUT
  );

  // Buttons

  pinMode(
    FAN_BUTTON,
    INPUT_PULLUP
  );

  pinMode(
    LIGHT_BUTTON,
    INPUT_PULLUP
  );

  // Safe initial states

  digitalWrite(
    RELAY_FAN,
    HIGH
  );

  digitalWrite(
    RELAY_LIGHT,
    HIGH
  );

  digitalWrite(
    BUZZER_PIN,
    LOW
  );

  digitalWrite(
    RED_LED,
    LOW
  );

  digitalWrite(
    GREEN_LED,
    HIGH
  );

  digitalWrite(
    YELLOW_LED,
    LOW
  );

  // ADC

  analogReadResolution(
    12
  );

  // DHT

  dht.begin();

  // OLED

  Wire.begin(
    21,
    22
  );

  if (
    !display.begin(
      SSD1306_SWITCHCAPVCC,
      0x3C
    )
  ) {

    Serial.println(
      "OLED not found"
    );

    while (
      true
    );
  }

  display.clearDisplay();

  display.setTextColor(
    SSD1306_WHITE
  );

  display.setTextSize(
    2
  );

  display.setCursor(
    0,
    20
  );

  display.println(
    "IoT HUB"
  );

  display.display();

  delay(
    2000
  );

  // WiFi

  connectWiFi();

  // MQTT

  mqttClient.setServer(
    mqtt_server,
    1883
  );

  connectMQTT();

  // Web server

  server.on(
    "/",
    handleRoot
  );

  server.on(
    "/fan",
    handleFan
  );

  server.on(
    "/light",
    handleLight
  );

  server.begin();

  Serial.println();

  Serial.println(
    "WEB SERVER STARTED"
  );

  Serial.print(
    "Open: http://"
  );

  Serial.println(
    WiFi.localIP()
  );

  Serial.println();

  Serial.println(
    "SYSTEM READY"
  );
}

// =================================================
// MAIN LOOP
// =================================================

void loop() {

  server.handleClient();

  if (
    !mqttClient.connected()
  ) {

    connectMQTT();
  }

  mqttClient.loop();

  // Ultrasonic reading

  if (
    millis() -
    lastUltrasonicRead
    >= ULTRASONIC_INTERVAL
  ) {

    lastUltrasonicRead =
      millis();

    readUltrasonic();
  }

  // Buttons

  checkButtons();

  // All sensor readings every 5 seconds

  if (
    millis() -
    lastSensorRead
    >= SENSOR_INTERVAL
  ) {

    lastSensorRead =
      millis();

    readSensors();

    applyAutomationRules();
  }

  // MQTT every 30 seconds

  if (
    millis() -
    lastMQTTPublish
    >= MQTT_INTERVAL
  ) {

    lastMQTTPublish =
      millis();

    publishMQTT();
  }

  // OLED every 5 seconds

  if (
    millis() -
    lastOLEDUpdate
    >= OLED_INTERVAL
  ) {

    lastOLEDUpdate =
      millis();

    updateOLED();
  }
}
