#include <DHTesp.h>

#define DHT_PIN 4

DHTesp dht;

void setup() {
  Serial.begin(115200);

  dht.setup(DHT_PIN, DHTesp::DHT11);

  Serial.println("DHT11 Climate Monitor");
  Serial.println("Temperature,Humidity");
}

void loop() {

  TempAndHumidity data = dht.getTempAndHumidity();

  if (isnan(data.temperature) || isnan(data.humidity)) {
    Serial.println("Sensor reading failed");
    delay(2000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(data.temperature, 1);
  Serial.print(" C | Humidity: ");
  Serial.print(data.humidity, 1);
  Serial.println(" %");

  delay(2000);
}
