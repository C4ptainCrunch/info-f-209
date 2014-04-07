#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>

#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <pthread.h>

#include <iostream>
#include <string>
#include <string.h>

#include "../exception/SocketError.h"


#define SBUFF_SIZE 32
#define MESSAGE_END "\n\n"

class Socket {
public:
    Socket();
    Socket(const int fd);
    Socket(std::string hostname, int port);
    ~Socket();
    virtual int write(std::string message);
    virtual int read(std::string & message);
    virtual int getFd() const;
    virtual void setFd(const int fd);

protected:
    char buffer[SBUFF_SIZE];
    int fd_;
    virtual std::string popFromBuffer();
    virtual void mutex_init();
    pthread_mutex_t read_lock;
    pthread_mutex_t write_lock;

};

//SOCKET_H
#endif
