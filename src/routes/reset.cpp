#include <Arduino.h>
#include <WiFi.h>

#include "../../include/boat-monitor/server.h"
#include "../../include/boat-monitor/utils.h"
#include "reset.h"

RouteParams resetRouteParams = {
  "PUT",
  new String[1] { "/reset" },
  1
};

void ResetRoute::handle(Connection *connection, Request req) {
  Response res = {};
  
  if (pins::isResetting()) {
    res.status = 400;
    res.message = "Bad Request";
    res.type = ResponseType::json;
    res.content = "{\"error\":\"Resetting\"}";

    connection->Write(req, res);
    return;
  }

  pins::resetCameras();\

  res.status = 201;
  res.message = "OK";
  res.type = ResponseType::json;

  connection->Write(req, res);
}

RouteParams ResetRoute::getParams() {
  return resetRouteParams;
}

