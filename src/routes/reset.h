#ifndef ROUTES_RESET_H
#define ROUTES_RESET_H

class ResetRoute: public Route {
  public:
  void handle(Connection *connection, Request req);
  RouteParams getParams();
};

#endif