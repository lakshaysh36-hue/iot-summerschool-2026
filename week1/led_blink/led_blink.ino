int blinkCount = 0;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(A0);
  int delayTime = map(sensorValue, 0, 1023, 100, 1000);

  digitalWrite(13, HIGH);
  delay(delayTime);

  digitalWrite(13, LOW);
  delay(delayTime);

  blinkCount++;
  Serial.print("Blink count: ");
  Serial.println(blinkCount);
}
