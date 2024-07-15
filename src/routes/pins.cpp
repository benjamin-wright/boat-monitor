#include <Arduino.h>
#include <WiFi.h>

#include "../../include/boat-monitor/server.h"
#include "pins.h"

RouteParams pinsRouteParams = {
  "GET",
  new String[1] { "/pins" },
  1
};

void PinsRoute::handle(Connection *connection, Request req) {
  Response res = {};

  res.status = 200;
  res.message = "OK";
  res.type = ResponseType::json;
  res.content = "{\"battery\":" + String(0.25) + ",\"bilge\":" + String(0.8) + "}";

  connection->Write(req, res);
}

RouteParams PinsRoute::getParams() {
  return pinsRouteParams;
}

