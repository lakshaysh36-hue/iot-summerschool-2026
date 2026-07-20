// Project 2: Gas & Fire Safety Alert System

// ---------- PIN DEFINITIONS ----------

const int GAS_SENSOR_PIN = A0;
const int FLAME_DIGITAL_PIN = 7;
const int FLAME_ANALOG_PIN = A1;

const int BUZZER_PIN = 9;

const int GREEN_LED = 10;
const int YELLOW_LED = 11;
const int RED_LED = 12;

// ---------- THRESHOLDS ----------

const int WARNING_THRESHOLD = 30;
const int DANGER_THRESHOLD = 60;

// ---------- TIMERS ----------

unsigned long lastBeepTime = 0;
unsigned long lastStatusTime = 0;

const unsigned long WARNING_BEEP_INTERVAL = 1000;
const unsigned long STATUS_INTERVAL = 1000;

// ---------- SETUP ----------

void setup() {

  Serial.begin(9600);

  pinMode(FLAME_DIGITAL_PIN, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  // Start in SAFE state
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.println("==================================");
  Serial.println("GAS & FIRE SAFETY ALERT SYSTEM");
  Serial.println("==================================");
  Serial.println("MQ-2 warming up...");
  Serial.println("Allow 1-2 minutes for stable readings.");
  Serial.println();
}

// ---------- LOOP ----------

void loop() {

  // Read MQ-2 gas sensor
  int gasValue = analogRead(GAS_SENSOR_PIN);

  // Convert gas value from 0-1023 to 0-100%
  int gasPercent = map(gasValue, 0, 1023, 0, 100);

  // Limit value between 0 and 100
  gasPercent = constrain(gasPercent, 0, 100);

  // Read flame sensor
  // Active-low: LOW means flame detected
  bool flameDetected = (digitalRead(FLAME_DIGITAL_PIN) == LOW);

  // Determine gas condition
  bool gasWarning = (gasPercent >= WARNING_THRESHOLD &&
                     gasPercent <= DANGER_THRESHOLD);

  bool gasDanger = (gasPercent > DANGER_THRESHOLD);

  // ---------- DANGER: FLAME + GAS ----------

  if (flameDetected && gasDanger) {

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, HIGH);

    // Combined alarm pattern
    tone(BUZZER_PIN, 2000);

  }

  // ---------- DANGER: FLAME ONLY ----------

  else if (flameDetected) {

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, HIGH);

    // Different flame alarm tone
    tone(BUZZER_PIN, 1500);

  }

  // ---------- DANGER: GAS ONLY ----------

  else if (gasDanger) {

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, HIGH);

    // Continuous gas danger alarm
    tone(BUZZER_PIN, 1000);

  }

  // ---------- WARNING: GAS LEVEL 30-60% ----------

  else if (gasWarning) {

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(RED_LED, LOW);

    // Beep once per second
    if (millis() - lastBeepTime >= WARNING_BEEP_INTERVAL) {

      lastBeepTime = millis();

      tone(BUZZER_PIN, 1000, 200);
    }
  }

  // ---------- SAFE ----------

  else {

    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);

    noTone(BUZZER_PIN);
  }

  // ---------- SERIAL STATUS LOG ----------

  if (millis() - lastStatusTime >= STATUS_INTERVAL) {

    lastStatusTime = millis();

    Serial.print("GAS: ");
    Serial.print(gasPercent);
    Serial.print("% | FLAME: ");

    if (flameDetected) {
      Serial.print("DETECTED");
    } else {
      Serial.print("NONE");
    }

    Serial.print(" | STATUS: ");

    if (flameDetected || gasDanger) {
      Serial.println("DANGER");
    }
    else if (gasWarning) {
      Serial.println("WARNING");
    }
    else {
      Serial.println("SAFE");
    }
  }
}
