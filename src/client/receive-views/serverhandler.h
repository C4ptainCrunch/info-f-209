#ifndef CLIENT_RECIEVE_VIEWS_H
#define CLIENT_RECIEVE_VIEWS_H

#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "../../common/lib/socket/Socket.h"
#include "../../common/lib/json/json.h"
#include "../../common/lib/exception/BadRequest.h"
#include "../../common/lib/json/helpers.h"
#include "views.h"
#include "../gui/mainwindow.h"

class ServerHandler;

typedef void (* view_ptr)(JsonValue *, ServerHandler *, MainWindow * window);


class ServerHandler {
public:
    ServerHandler(std::string host, const int port);
    ~ServerHandler();
    bool connect_socket(const int timeout = 2);
    void send(std::string message);
    int recieve(std::string & message);
    int loop();
    MainWindow * getWindow();

private:
    Socket * s_;
    std::string host_;
    int port_;
    MainWindow * window_;

    void handleMessage(std::string message);
    static const std::map<std::string, view_ptr> viewmap;
};

std::string split_message(std::string * key, std::string message);
//CLIENT_RECIEVE_VIEWS_H
#endif
