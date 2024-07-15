#include <Arduino.h>
#include <WiFi.h>

#include "../include/boat-monitor/utils.h"
#include "../include/boat-monitor/server.h"
#include "../include/boat-monitor/routes.h"

#include "credentials.h"
#include "LittleFS.h"

MiniServer* serv;

#define FORMAT_LITTLEFS_IF_FAILED true

void readIndex() {
  File dir = LittleFS.open("/", "r");
  if (!dir) {
    Serial.println("Failed to open file for reading");
    return;
  }

  if(!dir.isDirectory()){
    Serial.println(" - file is not a directory");
    dir.close();
    return;
  }

  Serial.println("Contents:");
  File file = dir.openNextFile();
  while(file){
    Serial.print("  ");
    Serial.println(file.name());
    file.close();
    file = dir.openNextFile();
  }

  dir.close();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial) {
    delay(50);
  }

  if (!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED)) {
    delay(1000);
    Serial.println("LittleFS Mount Failed");
  } else {
    readIndex();
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
