#include <Arduino.h>
#include "pins.h"

const int BATTERY_PIN = A0;
const int BILGE_PIN = A1;
const int RELAY_PIN = D3;
const int PULSE_LENGTH = 30000;

const int PIN_NEUTRAL = 2048;
const int PIN_RANGE = 2048;
const float BATTERY_MIN = 10.2;
const float BATTERY_MAX = 15.5;
const float BATTERY_FACTOR = (BATTERY_MAX - BATTERY_MIN) / PIN_RANGE;
const float BILGE_MIN = 0.1;
const float BILGE_MAX = 1.0;
const float BILGE_FACTOR = (BILGE_MAX - BILGE_MIN) / PIN_RANGE;

int last_set = 0;
bool resetting = false;

void pins::init() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BATTERY_PIN, INPUT);
  pinMode(BILGE_PIN, INPUT);
}

PinInputs pins::read() {
  int battery = abs(analogRead(BATTERY_PIN) - PIN_NEUTRAL);
  int bilge = abs(analogRead(BILGE_PIN) - PIN_NEUTRAL);

  Serial.print("Battery: ");
  Serial.println(battery);
  Serial.print("Bilge: ");
  Serial.println(bilge);

  PinInputs inputs = {
    BATTERY_MIN + battery * BATTERY_FACTOR,
    BILGE_MIN + bilge * BILGE_FACTOR
  };

  Serial.print("Battery: ");
  Serial.println(inputs.battery);
  Serial.print("Bilge: ");
  Serial.println(inputs.bilge);

  return inputs;
}

void pins::resetCameras() {
  digitalWrite(RELAY_PIN, HIGH);
  resetting = true;
  last_set = millis();
}

bool pins::isResetting() {
  return resetting;
}

void pins::tick() {
  if (resetting && millis() - last_set > PULSE_LENGTH) {
    digitalWrite(RELAY_PIN, LOW);
    resetting = false;
  }
}