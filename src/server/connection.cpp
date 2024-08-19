#include <Arduino.h>
#include <WiFi.h>

#include "connection.h"

String Request::toString() {
  return this->method + " -> " + this->path;
}

Request Request::fromString(String line) {
  int firstSpace = line.indexOf(' ', 0);
  if (firstSpace == -1) {
    return {};
  }

  int secondSpace = line.indexOf(' ', firstSpace + 1);
  if (secondSpace == -1) {
    return {};
  }

  Request req = {};

  req.method = line.substring(0, firstSpace);
  req.path = line.substring(firstSpace+1, secondSpace);

  return req;
}

Connection::Connection(WiFiClient client) {
  this->client = client;
}

bool Connection::IsOpen() {
  return this->client.connected();
}

bool Connection::HasData() {
  return this->client.available() > 0;
}

String Connection::readLine() {
  String line;
  unsigned long start = millis();
  while (this->client.connected()) {
    if (this->client.available()) {
      char c = this->client.read();
      if (c == '\n') {
        break;
      } else if (c != '\r') {
        line += c;
      }
    }

    unsigned long elapsed = millis() - start;

    if (elapsed > MAX_REQUEST_TIME) {
      Serial.println("Request timed out");
      break;
    }
  }

  return line;
}

void Connection::readRest() {
  String currentLine = "start";
  while (this->client.connected()) {
    if (this->client.available()) {
      char c = this->client.read();
      Serial.print(c);
      if (c == '\n') {
        if (currentLine.length() == 0) {
          break;
        } else {
          currentLine = "";
        }
      } else if (c != '\r') {
        currentLine += c;
      }
    }
  }
}

Request Connection::Read() {
  String firstLine = this->readLine();
  if (firstLine == "") {
    return {};
  }

  Request req = Request::fromString(firstLine);
  
  this->readRest();

  return req;
}

void Connection::Write(Request request, Response response) {
  Serial.print(response.status);
  Serial.print(" ");
  Serial.print(request.method);
  Serial.print(": ");
  Serial.println(request.path);

  this->client.print("HTTP/1.1 ");
  this->client.print(response.status);
  this->client.print(" ");
  this->client.println(response.message);

  switch (response.type) {
    case ResponseType::html : this->client.println("Content-type:text/html"); break;
    case ResponseType::json : this->client.println("Content-type:application/json"); break;
  }

  this->client.println("Cache-Control:no-store");
  this->client.print("Content-length:");
  this->client.println(response.content.length() + 2);

  this->client.println();

  // the content of the HTTP response follows the header:
  this->client.print(response.content);

  // The HTTP response ends with another blank line:
  this->client.println();
}
