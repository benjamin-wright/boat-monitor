#ifndef ROUTES_RESET_H
#define ROUTES_RESET_H

class ResetRoute: public Route {
  private:
  const char* password;

  public:
  ResetRoute(const char* password);
  void handle(Connection *connection, Request req);
  RouteParams getParams();
};

#endif