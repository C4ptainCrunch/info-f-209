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

#define PORT 8000
#define BUFFERSIZE 200


class Client{
public:
    Client();
    void connectToName(std::string name);
    void stringToBuff(std::string message);
    void disconnect();
    int defaultRecv();
    int defaultSend();
private:
/*defaultRecv et defaultSend sont des raccourcis pour ne pas préciser les para csts.*/
    int sockFd;
    bool connected;
    char buffer[BUFFERSIZE];
    struct sockaddr_in theirAddr;
    struct hostent *he;
    socklen_t addrSize;
};

#endif //CLIENT_H
