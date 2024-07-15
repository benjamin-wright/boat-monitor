#include "leds.h"
#include <Arduino.h>

void set(bool builtin, bool red, bool green, bool blue) {
  digitalWrite(LED_BUILTIN, builtin ? HIGH : LOW);
  digitalWrite(LED_RED, red ? LOW : HIGH);
  digitalWrite(LED_GREEN, green ? LOW : HIGH);
  digitalWrite(LED_BLUE, blue ? LOW : HIGH);
}

void leds::init() {
  // Serial.print("[LED] Initialising...");
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  // Serial.println("Done");
}

void leds::red() {
  // Serial.println("[LED] red");
  set(false, true, false, false);
}

void leds::green() {
  // Serial.println("[LED] green");
  set(false, false, true, false);
}

void leds::blue() {
  // Serial.println("[LED] blue");
  set(false, false, false, true);
}

void leds::off() {
  // Serial.println("[LED] off");
  set(false, false, false, false);
}