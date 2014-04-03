#ifndef BSOCKET_H
#define BSOCKET_H

#include "Socket.h"
#include "../exception/SocketError.h"

#include "helpers.h"

#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <string>
#include <vector>
#include <iostream>

#define BACKLOG 10

class ClientSocket;

class BindSocket: public Socket {
public:
    BindSocket(std::string hostname, int port);
    virtual ClientSocket * accept_client();
};

class ClientSocket: public Socket {
public:
    ClientSocket(const int fd, sockaddr_storage remote);
    std::string remote();

private:
    sockaddr_storage remote_addr_;
};

//BSOCKET_H
#endif
