// =====================================================
// PROJECT 9: PRECISION POSITION CONTROLLER
// TINKERCAD VERSION
// DC MOTOR + ENCODER + L293D
// =====================================================

// ---------------- PIN DEFINITIONS ----------------

// L293D motor driver
#define EN_PIN 5
#define IN1_PIN 7
#define IN2_PIN 8

// Encoder
#define ENCODER_A 2

// Buttons
#define CW_BUTTON 3
#define CCW_BUTTON 4
#define HOME_BUTTON 9

// Position indicator LED
#define POSITION_LED 6

// Potentiometer
#define POT_PIN A0

// =====================================================
// ENCODER SETTINGS
// =====================================================

// IMPORTANT:
// Replace this value if your Tinkercad motor has a different
// encoder resolution.
//
// Start with 360 counts per revolution.
#define COUNTS_PER_REV 360.0

// =====================================================
// POSITION VARIABLES
// =====================================================

volatile long encoderCounts = 0;

long targetCounts = 0;

int targetAngle = 0;
float currentAngle = 0;

String direction = "STOP";

// =====================================================
// MOTOR CONTROL SETTINGS
// =====================================================

int motorSpeed = 180;

// =====================================================
// SETUP
// =====================================================

void setup() {

  Serial.begin(9600);

  // Motor driver pins
  pinMode(EN_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);

  // Buttons
  pinMode(CW_BUTTON, INPUT_PULLUP);
  pinMode(CCW_BUTTON, INPUT_PULLUP);
  pinMode(HOME_BUTTON, INPUT_PULLUP);

  // LED
  pinMode(POSITION_LED, OUTPUT);

  // Encoder
  pinMode(ENCODER_A, INPUT);

  // Interrupt for encoder
  attachInterrupt(
    digitalPinToInterrupt(ENCODER_A),
    encoderISR,
    RISING
  );

  // Motor initially stopped
  stopMotor();

  Serial.println("====================================");
  Serial.println("PRECISION POSITION CONTROLLER");
  Serial.println("DC MOTOR + ENCODER + L293D");
  Serial.println("====================================");

  Serial.println("System Ready");
  Serial.println();
}

// =====================================================
// MAIN LOOP
// =====================================================

void loop() {

  // -----------------------------------------------
  // 1. READ POTENTIOMETER and helps in displaying angle and direction
  // -----------------------------------------------

  int potValue = analogRead(POT_PIN);

  targetAngle = map(
    potValue,
    0,
    1023,
    0,
    360
  );

  // Convert target angle to encoder counts
  targetCounts =
    (long)((targetAngle / 360.0) * COUNTS_PER_REV);


  // -----------------------------------------------
  // 2. UPDATE CURRENT ANGLE
  // -----------------------------------------------

  noInterrupts();

  long currentCounts = encoderCounts;

  interrupts();

  currentAngle =
    (currentCounts / COUNTS_PER_REV) * 360.0;


  // -----------------------------------------------
  // 3. BUTTON CONTROL
  // -----------------------------------------------

  if (digitalRead(CW_BUTTON) == LOW) {

    direction = "CW";

    moveClockwise();

    delay(250);
  }


  if (digitalRead(CCW_BUTTON) == LOW) {

    direction = "CCW";

    moveCounterClockwise();

    delay(250);
  }


  if (digitalRead(HOME_BUTTON) == LOW) {

    setHome();

    delay(250);
  }


  // -----------------------------------------------
  // 4. AUTOMATIC POSITION CONTROL
  // -----------------------------------------------

  long positionError =
    targetCounts - currentCounts;


  // Dead zone prevents constant vibration
  if (abs(positionError) <= 3) {

    stopMotor();

    direction = "STOP";
  }

  else if (positionError > 0) {

    direction = "CW";

    moveClockwise();
  }

  else if (positionError < 0) {

    direction = "CCW";

    moveCounterClockwise();
  }


  // -----------------------------------------------
  // 5. POSITION LED
  // -----------------------------------------------

  if (abs(positionError) <= 3) {

    digitalWrite(POSITION_LED, LOW);
  }

  else {

    digitalWrite(POSITION_LED, HIGH);
  }


  // -----------------------------------------------
  // 6. DISPLAY STATUS
  // -----------------------------------------------

  static unsigned long lastDisplay = 0;

  if (millis() - lastDisplay >= 500) {

    printStatus();

    lastDisplay = millis();
  }

  delay(10);
}

// =====================================================
// ENCODER INTERRUPT
// =====================================================

void encoderISR() {

  // Channel A pulse detected.
  // Direction is determined by the motor command.
  if (direction == "CW") {

    encoderCounts++;
  }

  else if (direction == "CCW") {

    encoderCounts--;
  }
}

// =====================================================
// MOVE CLOCKWISE
// =====================================================

void moveClockwise() {

  digitalWrite(IN1_PIN, HIGH);

  digitalWrite(IN2_PIN, LOW);

  analogWrite(
    EN_PIN,
    motorSpeed
  );
}

// =====================================================
// MOVE COUNTER-CLOCKWISE
// =====================================================

void moveCounterClockwise() {

  digitalWrite(IN1_PIN, LOW);

  digitalWrite(IN2_PIN, HIGH);

  analogWrite(
    EN_PIN,
    motorSpeed
  );
}

// =====================================================
// STOP MOTOR
// =====================================================

void stopMotor() {

  analogWrite(
    EN_PIN,
    0
  );

  digitalWrite(IN1_PIN, LOW);

  digitalWrite(IN2_PIN, LOW);
}

// =====================================================
// SET HOME POSITION
// =====================================================

void setHome() {

  stopMotor();

  noInterrupts();

  encoderCounts = 0;

  interrupts();

  direction = "HOME";

  Serial.println();
  Serial.println("HOME POSITION SET");
  Serial.println("Current position = 0 degrees");
  Serial.println();
}

// =====================================================
// PRINT STATUS
// =====================================================

void printStatus() {

  noInterrupts();

  long counts = encoderCounts;

  interrupts();

  float angle =
    (counts / COUNTS_PER_REV) * 360.0;

  Serial.println("--------------------------------");

  Serial.print("Current Angle: ");

  Serial.print(angle, 1);

  Serial.println(" degrees");

  Serial.print("Target Angle: ");

  Serial.print(targetAngle);

  Serial.println(" degrees");

  Serial.print("Encoder Counts: ");

  Serial.println(counts);

  Serial.print("Target Counts: ");

  Serial.println(targetCounts);

  Serial.print("Direction: ");

  Serial.println(direction);

  Serial.println("--------------------------------");
}
