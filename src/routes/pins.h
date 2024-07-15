#ifndef ROUTES_PINS_H
#define ROUTES_PINS_H

class PinsRoute: public Route {
  public:
  void handle(Connection *connection, Request req);
  RouteParams getParams();
};

#endif