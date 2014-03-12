#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>

#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <iostream>
#include <string>
#include <string.h>


#define SBUFF_SIZE 32
#define MESSAGE_END "\n\n"

class Socket {
public:
    Socket();
    ~Socket();
    Socket(const int fd);
    virtual int write(std::string message);
    virtual int read(std::string & message);
    virtual int getFd() const;
    virtual void setFd(const int fd);

private:
    char buffer[SBUFF_SIZE];
    int fd_;
    virtual std::string popFromBuffer();
};

//SOCKET_H
#endif
