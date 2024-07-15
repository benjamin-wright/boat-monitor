#ifndef SERVER_H
#define SERVER_H

extern WiFiServer server;

struct RouteParams {
  String method;
  String *paths;
  int length;
};

class Route {
  public:
  bool match(String method, String path) {
    RouteParams params = this->getParams();

    if (method != params.method) {
      return false;
    }

    for (size_t i = 0; i < params.length; i++) {
      if (path == params.paths[i]) {
        return true;
      }
    }

    return false;
  }

  virtual RouteParams getParams();
  virtual void handle(Connection *connection, Request req) = 0;
};

class MiniServer {
  private:
    ConnectionPool* pool;
    Route** routes;
    int length;
  
  public:
    MiniServer();
    static void init(const char* ssid, const char* password);
    MiniServer(Route** routes, int length);
    void listen();
};

#endif