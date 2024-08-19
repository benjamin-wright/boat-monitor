#include <Arduino.h>
#include <WiFi.h>

#include "../../include/boat-monitor/server.h"
#include "../../include/data/index.h"
#include "index.h"

RouteParams indexRouteParams = {
  "GET",
  new String[2] { "/", "/index.html" },
  2
};

void IndexRoute::handle(Connection *connection, Request req) {
  Response res = {};
  res.status = 200;
  res.message = "OK";
  res.type = ResponseType::html;
  res.content = String(data_index_html, data_index_html_len);

  connection->Write(req, res);
}

RouteParams IndexRoute::getParams() {
  return indexRouteParams;
}

