#ifndef ROUTES_INDEX_H
#define ROUTES_INDEX_H

class IndexRoute: public Route {
  public:
  void handle(Connection *connection, Request req);
  RouteParams getParams();
};

#endif