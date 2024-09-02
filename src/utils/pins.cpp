#include <Arduino.h>
#include "pins.h"

const int BATTERY_PIN = A0;
const int BILGE_PIN = A1;
const int RELAY_PIN = D3;
const int PULSE_LENGTH = 30000;

const int PIN_NEUTRAL = 0;
const int PIN_RANGE = 4096;
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

  digitalWrite(RELAY_PIN, HIGH);
}

PinInputs pins::read() {
  int initialBattery = analogRead(BATTERY_PIN);
  int initialBilge = analogRead(BILGE_PIN);

  int battery = abs(initialBattery - PIN_NEUTRAL);
  int bilge = abs(initialBilge - PIN_NEUTRAL);


  PinInputs inputs = {
    BATTERY_MIN + battery * BATTERY_FACTOR,
    BILGE_MIN + bilge * BILGE_FACTOR
  };

  return inputs;
}

void pins::resetCameras() {
  digitalWrite(RELAY_PIN, LOW);
  resetting = true;
  last_set = millis();
}

bool pins::isResetting() {
  return resetting;
}

void pins::tick() {
  if (resetting && millis() - last_set > PULSE_LENGTH) {
    digitalWrite(RELAY_PIN, HIGH);
    resetting = false;
  }
}