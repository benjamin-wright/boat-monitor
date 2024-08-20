#ifndef CONNECTION_H
#define CONNECTION_H

const unsigned long MAX_REQUEST_TIME = 2000;

struct Request {
  String method;
  String path;
  String body;

  // Return a pretty string version of the request
  String toString();
  static Request fromString(String line);
};

enum ResponseType { html, json };

struct Response {
  int status;
  String message;
  ResponseType type;
  String content;
};

class Connection {
  private:
    WiFiClient client;
    String readLine();
    String readRest();

  public:
    Connection(WiFiClient client);
    bool IsOpen();
    bool HasData();
    Request Read();
    void Write(Request request, Response response);
    bool operator=(Connection *connection);
};

#endif