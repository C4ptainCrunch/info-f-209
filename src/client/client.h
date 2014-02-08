#ifndef CLIENT_H
#define CLIENT_H

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

#include <string>
#include "Socket.h"

#define PORT 8000
#define BUFFERSIZE 200


class Client{
public:
    Client();
    void connectToName(std::string name);
    void disconnect();
private:
    Socket socket_;
    bool connected;
};

#endif //CLIENT_H
