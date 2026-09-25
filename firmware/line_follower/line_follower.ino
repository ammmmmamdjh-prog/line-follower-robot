/*
 * ═══════════════════════════════════════════════════════════════
 *  LINE-FOLLOWER ROBOT — PID Edition
 *  Author : AmirAli  ·  github.com/ammmmmamdjh-prog
 *  Board  : Arduino UNO / Nano (ATmega328P)
 *  Driver : L298N dual H-bridge
 *  Sensors: 5-channel TCRT5000 IR reflectance array
 *
 *  A classic PID line follower:
 *    error  → how far we are from the line center
 *    PID    → converts error into a steering correction
 *    motors → differential drive response
 * ═══════════════════════════════════════════════════════════════
 */

/* ── Pin map ─────────────────────────────────────────────────── */
// IR sensor array (left → right)
const uint8_t PIN_S[5] = { A0, A1, A2, A3, A4 };

// L298N driver
const uint8_t PIN_ENA = 5;    // left motor PWM
const uint8_t PIN_ENB = 6;    // right motor PWM
const uint8_t PIN_IN1 = 7;    // left motor dir A
const uint8_t PIN_IN2 = 8;    // left motor dir B
const uint8_t PIN_IN3 = 9;    // right motor dir A
const uint8_t PIN_IN4 = 10;   // right motor dir B

/* ── Tuning constants ────────────────────────────────────────── */
float KP        = 35.0;   // reaction strength
float KD        = 120.0;  // damping (anti-oscillation)
float KI        = 0.0;    // integral (leave 0 unless curves drift)
int   BASE_SPEED = 160;   // 0..255 cruise speed
int   MAX_SPEED  = 255;

/* ── Runtime state ───────────────────────────────────────────── */
int   position     = 0;   // weighted line position 0..4000
int   lastError    = 0;
float integral     = 0;
bool  lineDetected = false;

/* ── Setup ───────────────────────────────────────────────────── */
void setup() {
  for (uint8_t i = 0; i < 5; i++)  pinMode(PIN_S[i], INPUT);
  for (uint8_t p = 5; p <= 10; p++) pinMode(p, OUTPUT);

  stopMotors();
  Serial.begin(115200);
  Serial.println(F("LINE FOLLOWER ONLINE"));
}

/* ── Main loop ───────────────────────────────────────────────── */
void loop() {
  readLine();

  if (!lineDetected) {          // line lost → brake and search
    stopMotors();
    integral = 0;
    return;
  }

  int error = position - 2000;  // center = 2000

  // PID math
  integral += error;
  integral  = constrain(integral, -5000, 5000);
  float derivative = error - lastError;
  float correction = KP * error + KI * integral + KD * derivative;
  lastError = error;

  // Differential drive: slow the inner wheel, speed the outer one
  int leftSpeed  = constrain(BASE_SPEED - correction, -MAX_SPEED, MAX_SPEED);
  int rightSpeed = constrain(BASE_SPEED + correction, -MAX_SPEED, MAX_SPEED);

  setMotors(leftSpeed, rightSpeed);

  Serial.print(F("pos="));  Serial.print(position);
  Serial.print(F(" err=")); Serial.print(error);
  Serial.print(F(" L="));   Serial.print(leftSpeed);
  Serial.print(F(" R="));   Serial.println(rightSpeed);
}

/* ── Read & weight the sensor array ──────────────────────────── */
void readLine() {
  long sum   = 0;
  long weighted = 0;
  lineDetected = false;

  // 0 = white, 1 = black (invert if your track is the opposite)
  for (uint8_t i = 0; i < 5; i++) {
    bool onLine = (digitalRead(PIN_S[i]) == HIGH);
    if (onLine) { lineDetected = true; }
    sum      += onLine;
    weighted += (long)onLine * i * 1000;
  }

  if (lineDetected) {
    position = weighted / sum;          // 0..4000, center = 2000
  } else {
    // Line lost: keep the last known side so the search is smarter
    position = (lastError > 0) ? 4000 : 0;
  }
}

/* ── Motor primitives ────────────────────────────────────────── */
void setMotors(int left, int right) {
  // Left motor
  digitalWrite(PIN_IN1, left  >= 0);
  digitalWrite(PIN_IN2, left   < 0);
  analogWrite (PIN_ENA, abs(left));

  // Right motor
  digitalWrite(PIN_IN3, right >= 0);
  digitalWrite(PIN_IN4, right  < 0);
  analogWrite (PIN_ENB, abs(right));
}

void stopMotors() {
  analogWrite(PIN_ENA, 0);
  analogWrite(PIN_ENB, 0);
}
