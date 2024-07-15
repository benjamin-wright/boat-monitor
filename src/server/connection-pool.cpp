#include <Arduino.h>
#include <WiFi.h>

#include "connection.h"
#include "connection-pool.h"

ConnectionPool::ConnectionPool() {
  this->capacity = 1;
  this->length = 0;
  this->connections = new Connection*[1];
}

ConnectionPool::~ConnectionPool() {
  delete [] this->connections;
}


void ConnectionPool::AddConnection(Connection *connection) {
  if (this->capacity == this->length) {
    this->capacity *= 2;
    Connection **connections = new Connection*[this->capacity];
    for (int i = 0; i < this->length; i++) {
      connections[i] = this->connections[i];
    }

    delete [] this->connections;
    this->connections = connections;
  }

  this->connections[this->length] = connection;
  this->length++;
  Serial.print("Connections: +");
  Serial.println(this->length);
}

Connection* ConnectionPool::HasData() {
  for (int i = 0; i < this->length; i++) {
    Connection *connection = this->connections[i];
    if (!connection->IsOpen()) {
      this->Remove(connection);
      i = 0;
      continue;
    }

    if (connection->HasData()) {
      return connection;
    }
  }

  return NULL;
}

void ConnectionPool::Remove(Connection *connection) {
  for (int i = 0; i < this->length; i++) {
    if (this->connections[i] == connection) {
      this->connections[i] = this->connections[this->length-1];
      break;
    }
  }

  this->length--;
  if (this->capacity > 1 && this->length < this->capacity / 2) {
    this->capacity /= 2;
    Connection **connections = new Connection*[this->capacity];
    for (int i = 0; i < this->length; i++) {
      connections[i] = this->connections[i];
    }

    delete [] this->connections;
    this->connections = connections;
  }

  Serial.print("Connections: -");
  Serial.println(this->length);
}