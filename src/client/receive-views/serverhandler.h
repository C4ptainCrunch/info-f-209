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

class ServerHandler;

// typedef void (* view_ptr)(JsonValue *, ServerHandler *);


class ServerHandler {
public:
    ServerHandler(std::string host, const int port);
    ~ServerHandler();
    bool connect_socket(const int timeout = 2);
    void send(std::string message);
    int recieve(std::string & message);

private:
    Socket * s_;
    std::string host_;
    int port_;
};
//CLIENT_RECIEVE_VIEWS_H
#endif
