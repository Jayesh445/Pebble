#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <math.h>

// Prototype values only. Measure and adjust limits for your exact servos.
constexpr uint8_t SDA_PIN = 21, SCL_PIN = 22;
constexpr uint16_t MIN_US = 1000, MAX_US = 2000;
constexpr unsigned long COMMAND_TIMEOUT_MS = 30000;
Adafruit_PWMServoDriver pwm(0x40);
bool armed = false;
unsigned long lastCommand = 0;
char line[80];
size_t used = 0;
bool overflow = false;

void disableAll() {
  for (uint8_t channel = 0; channel < 16; ++channel) pwm.setPWM(channel, 0, 4096);
  armed = false;
}

void handle(const char *input) {
  if (strcmp(input, "help") == 0) {
    Serial.println("Commands: arm | set CHANNEL DEGREES | off | help");
    Serial.println("Channels 0-7, degrees 45-135. Arm only with robot supported.");
  } else if (strcmp(input, "off") == 0) {
    disableAll(); Serial.println("Outputs off. Servos may still have power.");
  } else if (strcmp(input, "arm") == 0) {
    armed = true; lastCommand = millis();
    Serial.println("Armed. No motion until a set command.");
  } else {
    int channel; float angle; char extra;
    if (sscanf(input, "set %d %f %c", &channel, &angle, &extra) != 2 ||
        channel < 0 || channel > 7 || !isfinite(angle) || angle < 45 || angle > 135) {
      Serial.println("Invalid command. Type help."); return;
    }
    if (!armed) { Serial.println("Not armed."); return; }
    const float pulse = MIN_US + (MAX_US - MIN_US) * angle / 180.0f;
    const uint16_t ticks = (uint16_t)(pulse * 4096.0f * 50.0f / 1000000.0f + 0.5f);
    pwm.setPWM(channel, 0, ticks);
    lastCommand = millis();
    Serial.printf("Channel %d -> %.1f degrees (nominal)\n", channel, angle);
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.beginTransmission(0x40);
  if (Wire.endTransmission() != 0) {
    Serial.println("PCA9685 not found at 0x40. Check wiring; reset to retry.");
    while (true) delay(1000);
  }
  pwm.begin(); pwm.setPWMFreq(50); disableAll();
  Serial.println("Pebble servo tester ready; outputs off. Type help.");
}
void loop() {
  while (Serial.available()) {
    char c = (char)Serial.read();
    if (c == '\n' || c == '\r') {
      if (overflow) { Serial.println("Command too long."); overflow = false; used = 0; }
      else if (used) { line[used] = '\0'; handle(line); used = 0; }
    } else if (!overflow) {
      if (used < sizeof(line) - 1) line[used++] = c;
      else { overflow = true; used = 0; }
    }
  }
  if (armed && millis() - lastCommand >= COMMAND_TIMEOUT_MS) {
    disableAll(); Serial.println("Timed out; outputs off.");
  }
}
