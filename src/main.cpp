#include <Arduino.h>
#include <WiFi.h>

#include "../include/boat-monitor/utils.h"
#include "../include/boat-monitor/server.h"
#include "../include/boat-monitor/routes.h"

#include "credentials.h"
#include "LittleFS.h"

MiniServer* serv;

#define FORMAT_LITTLEFS_IF_FAILED true

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial) {
    delay(50);
  }

  if (!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED)) {
    delay(1000);
    Serial.println("LittleFS Mount Failed");
  }


  Serial.println("Initialising...");
  leds::init();
  leds::off();
  Serial.println("Initialised");

  MiniServer::init(ssid, password);

  Serial.println("Loading routes...");

  Route** routes = new Route*[2];
  routes[0] = new IndexRoute();
  routes[1] = new PinsRoute();

  Serial.println("Loaded");
  serv = new MiniServer(routes, 2);
}

void loop() {
  serv->listen();
}
