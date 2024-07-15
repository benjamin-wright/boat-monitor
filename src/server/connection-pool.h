#ifndef CONNECTIONS_H
#define CONNECTIONS_H

class ConnectionPool {
  int capacity;
  int length;
  Connection** connections;

  public:
    ConnectionPool();
    ~ConnectionPool();
    void AddConnection(Connection *connection);
    Connection* HasData();
    void Remove(Connection *connection);
};

#endif