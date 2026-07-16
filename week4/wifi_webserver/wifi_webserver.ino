#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>
/*
  Project: ESP32 Wi-Fi Weather Monitoring Web Server

  Description:
  This project uses an ESP32 and a DHT11 temperature and humidity
  sensor to create a simple Wi-Fi web server. The ESP32 connects to
  a local Wi-Fi network and hosts a webpage displaying real-time
  temperature, humidity, and system uptime. The webpage refreshes
  automatically every 10 seconds and includes a button to remotely
  toggle the onboard LED through a web browser.

  Author: Lakshay Sharma
  Date: 17 July 2026
*/
#define DHTPIN 4
#define DHTTYPE DHT11
#define LED_PIN 2

const char* ssid = "wifi name";
const char* password = "wifi password";

WebServer server(80);
DHT dht(DHTPIN, DHTTYPE);

bool ledState = false;

String getUptime() {
  unsigned long sec = millis() / 1000;
  int h = sec / 3600;
  int m = (sec % 3600) / 60;
  int s = sec % 60;

  char buf[20];
  sprintf(buf,"%02d:%02d:%02d",h,m,s);
  return String(buf);
}

void handleRoot() {

  float t = dht.readTemperature();
  float h = dht.readHumidity();

  String page = "<!DOCTYPE html><html>";
  page += "<head>";
  page += "<meta http-equiv='refresh' content='10'>";
  page += "<title>ESP32 Weather</title>";
  page += "</head>";

  page += "<body>";
  page += "<h1>ESP32 WiFi Web Server</h1>";

  page += "<h2>Temperature : ";
  page += String(t);
  page += " C</h2>";

  page += "<h2>Humidity : ";
  page += String(h);
  page += " %</h2>";

  page += "<h2>Uptime : ";
  page += getUptime();
  page += "</h2>";

  page += "<form action='/toggle'>";
  page += "<input type='submit' value='Toggle LED'>";
  page += "</form>";

  page += "</body></html>";

  server.send(200,"text/html",page);
}

void handleToggle() {

  ledState = !ledState;

  digitalWrite(LED_PIN, ledState);

  server.sendHeader("Location","/");
  server.send(303);
}

void setup() {

  Serial.begin(115200);

  pinMode(LED_PIN,OUTPUT);

  dht.begin();

  WiFi.begin(ssid,password);

  Serial.print("Connecting");

  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println();

  Serial.print("Connected!");

  Serial.println();

  Serial.print("IP Address: ");

  Serial.println(WiFi.localIP());

  server.on("/",handleRoot);

  server.on("/toggle",handleToggle);

  server.begin();
}

void loop() {

  server.handleClient();

}
