#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11
#define LED_PIN 2

const char* ssid = "wifi name";
const char* password = "wifi password";

// You can also use "test.mosquitto.org" if needed
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

const char* tempTopic = "iitjammu/summer26/lakshay/temperature";
const char* humTopic  = "iitjammu/summer26/lakshay/humidity";
const char* ledTopic  = "iitjammu/summer26/lakshay/led_control";

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);

unsigned long lastPublish = 0;

void connectWiFi() {
  Serial.print("Connecting WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {

  String message = "";

  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Message received on ");
  Serial.print(topic);
  Serial.print(": ");
  Serial.println(message);

  if (message == "ON") {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED ON");
  }
  else if (message == "OFF") {
    digitalWrite(LED_PIN, LOW);
    Serial.println("LED OFF");
  }
}

void reconnectMQTT() {

  while (!client.connected()) {

    Serial.print("Connecting MQTT...");

    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {

      Serial.println("Connected!");

      client.subscribe(ledTopic);

      Serial.print("Subscribed to: ");
      Serial.println(ledTopic);

    } else {

      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds");

      delay(5000);
    }
  }
}

void setup() {

  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  dht.begin();

  connectWiFi();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnectMQTT();
  }

  client.loop();

  if (millis() - lastPublish >= 5000) {

    lastPublish = millis();

    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("Failed to read DHT11!");
      return;
    }

    unsigned long timestamp = millis();

    String tempPayload =
      "{\"value\":" +
      String(temperature, 1) +
      ",\"unit\":\"C\",\"ts\":" +
      String(timestamp) +
      "}";

    String humPayload =
      "{\"value\":" +
      String(humidity, 1) +
      ",\"unit\":\"%\",\"ts\":" +
      String(timestamp) +
      "}";

    bool tempSent = client.publish(tempTopic, tempPayload.c_str());
    bool humSent = client.publish(humTopic, humPayload.c_str());

    Serial.println();
    Serial.println("========================================");

    Serial.print("Publishing to: ");
    Serial.println(tempTopic);

    Serial.print("Payload: ");
    Serial.println(tempPayload);

    Serial.print("Temperature Publish Status: ");
    Serial.println(tempSent ? "SUCCESS" : "FAILED");

    Serial.println();

    Serial.print("Publishing to: ");
    Serial.println(humTopic);

    Serial.print("Payload: ");
    Serial.println(humPayload);

    Serial.print("Humidity Publish Status: ");
    Serial.println(humSent ? "SUCCESS" : "FAILED");

    Serial.println("========================================");
    Serial.println();
  }
}
