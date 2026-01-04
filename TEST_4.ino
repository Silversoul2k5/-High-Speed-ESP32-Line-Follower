#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---- FIX DEFAULT MACRO CONFLICT ----
#ifdef DEFAULT
  #undef DEFAULT
#endif

#include "RoboEyes.h"

// =====================================================
// OLED CONFIG
// =====================================================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDR     0x3C

#define I2C_SDA 4
#define I2C_SCL 22

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
RoboEyes<Adafruit_SSD1306> eyes(display);

// =====================================================
// IR SENSOR SETUP
// =====================================================
const int sensorPins[8] = {26, 25, 33, 32, 35, 34, 39, 36};
const int BLACK_THRESHOLD = 3600;

int weights[8] = {-12, -9, -6, -2, 2, 6, 9, 12};

// =====================================================
// MOTOR PINS (TB6612FNG)
// =====================================================
const int PWMA = 18;
const int AIN1 = 19;
const int AIN2 = 21;

const int PWMB = 5;
const int BIN1 = 17;
const int BIN2 = 16;

const int STBY = 23;

// =====================================================
// SPEED & PID SETTINGS
// =====================================================
int FAST_SPEED = 255;
int TURN_SPEED = 230;

int brakeFactor = 3;

// ---- TURN THRESHOLDS ----
int ACUTE_ERROR = 4;   // sharp curve (no reverse)
int PIVOT_ERROR = 9;   // true 90° turn (reverse allowed)

float Kp = 16.0;
float Ki = 0.0;
float Kd = 22.0;

int lastError = 0;

// =====================================================

void setup() {
  Serial.begin(115200);

  Wire.begin(I2C_SDA, I2C_SCL);
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    while (1);
  }

  eyes.begin(SCREEN_WIDTH, SCREEN_HEIGHT, 60);
  eyes.setDisplayColors(0, 1);
  eyes.setAutoblinker(true, 3, 2);
  eyes.setIdleMode(true, 2, 3);
  eyes.setCuriosity(true);

  for (int i = 0; i < 8; i++)
    pinMode(sensorPins[i], INPUT);

  pinMode(PWMA, OUTPUT); pinMode(AIN1, OUTPUT); pinMode(AIN2, OUTPUT);
  pinMode(PWMB, OUTPUT); pinMode(BIN1, OUTPUT); pinMode(BIN2, OUTPUT);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);

  delay(1000);
}

// =====================================================

void loop() {

  // -------- READ SENSORS --------
  bool s[8];
  int activeCount = 0;
  for (int i = 0; i < 8; i++) {
    s[i] = analogRead(sensorPins[i]) >= BLACK_THRESHOLD;
    if (s[i]) activeCount++;
  }

  bool centerLost = !s[3] && !s[4];
  bool edgeSeen   = s[0] || s[1] || s[6] || s[7];

  int error = calculateError(s);

  // -------- BASE SPEED LOGIC --------
  int baseSpeed;

  // --- TRUE 90° TURN ---
  if (centerLost && edgeSeen && abs(error) >= PIVOT_ERROR) {
    baseSpeed = TURN_SPEED - (abs(error) * brakeFactor);
  }
  // --- ACUTE / SHARP CURVE ---
  else if (abs(error) >= ACUTE_ERROR) {
    baseSpeed = TURN_SPEED;
  }
  // --- STRAIGHT / NORMAL ---
  else {
    baseSpeed = FAST_SPEED;
  }

  baseSpeed = constrain(baseSpeed, 60, 255);

  // -------- PID --------
  int D = error - lastError;
  int correction = (Kp * error) + (Kd * D);

  int leftSpeed  = baseSpeed - correction;
  int rightSpeed = baseSpeed + correction;

  setMotor(1, leftSpeed);
  setMotor(2, rightSpeed);

  lastError = error;
  eyes.update();
  delay(1);
}

// =====================================================
// ERROR CALCULATION
// =====================================================
int calculateError(bool s[]) {
  long sum = 0;
  int count = 0;

  for (int i = 0; i < 8; i++) {
    if (s[i]) {
      sum += weights[i];
      count++;
    }
  }

  if (count == 0) {
    return lastError > 0 ? 18 : -18;
  }

  return sum / count;
}

// =====================================================
// MOTOR DRIVER
// =====================================================
void setMotor(int motorID, int speed) {
  speed = constrain(speed, -255, 255);
  bool forward = speed >= 0;
  int pwm = abs(speed);

  if (motorID == 1) {
    digitalWrite(AIN1, forward);
    digitalWrite(AIN2, !forward);
    analogWrite(PWMA, pwm);
  } else {
    digitalWrite(BIN1, forward);
    digitalWrite(BIN2, !forward);
    analogWrite(PWMB, pwm);
  }
}
