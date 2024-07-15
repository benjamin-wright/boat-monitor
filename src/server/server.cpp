#include <Arduino.h>
#include <WiFi.h>

#include "../../include/boat-monitor/utils.h"
#include "connection.h"
#include "connection-pool.h"
#include "server.h"

WiFiServer server(80);

void MiniServer::init(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);
  int state = true;
  while (WiFi.status() != WL_CONNECTED) {
    if (state) {
      leds::green();
    } else {
      leds::off();
    }
    state = !state;
    
    delay(500);
    Serial.print(".");
  }

  leds::off();

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  server.begin();
}

MiniServer::MiniServer(Route** routes, int length) {
  this->length = length;
  this->routes = routes;
  this->pool = new ConnectionPool();
}

void MiniServer::listen() {
  WiFiClient client = server.available();
  if (client) {
    this->pool->AddConnection(new Connection(client));
  }

  Connection *connection = this->pool->HasData();
  if (connection == NULL) {
    return;
  }

  leds::blue();

  Request req = connection->Read();

  bool found = false;
  for (int i = 0; i < this->length; i++) {
    Route *route = this->routes[i];

    if (route->match(req.method, req.path)) {
      route->handle(connection, req);
      found = true;
      break;
    }
  }

  if (!found) {
    Response res = {};
    res.status = 404;
    res.message = "Not Found";
    res.type = ResponseType::html;
    res.content = "<body><p>Yeah, that's not a thing...</p></body>";

    connection->Write(req, res);
  }
  
  leds::off();
}
