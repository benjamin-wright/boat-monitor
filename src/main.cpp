#include <Arduino.h>
#include <WiFi.h>

#include "../include/boat-monitor/utils.h"
#include "../include/boat-monitor/server.h"
#include "../include/boat-monitor/routes.h"

#include "credentials.h"

MiniServer* serv;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial) {
    delay(50);
  }

  Serial.println("Initialising...");
  pins::init();
  leds::init();
  leds::off();
  Serial.println("Initialised");

  MiniServer::init(ssid, password);

  Serial.println("Loading routes...");

  Route** routes = new Route*[3];
  routes[0] = new IndexRoute();
  routes[1] = new PinsRoute();
  routes[2] = new ResetRoute();

  Serial.println("Loaded");
  serv = new MiniServer(routes, 3);
}

void loop() {
  serv->listen();
  pins::tick();
}
