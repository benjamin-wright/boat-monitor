#include <Arduino.h>
#include <WiFi.h>

#include "../../include/boat-monitor/server.h"
#include "../../include/boat-monitor/utils.h"
#include "pins.h"

RouteParams pinsRouteParams = {
  "GET",
  new String[1] { "/pins" },
  1
};

void PinsRoute::handle(Connection *connection, Request req) {
  Response res = {};

  PinInputs inputs = pins::read();

  res.status = 200;
  res.message = "OK";
  res.type = ResponseType::json;
  res.content = "{\"battery\":" + String(inputs.battery) + ",\"bilge\":" + String(inputs.bilge) + ",\"resetting\":" + (pins::isResetting() ? "true" : "false") + "}";

  connection->Write(req, res);
}

RouteParams PinsRoute::getParams() {
  return pinsRouteParams;
}

