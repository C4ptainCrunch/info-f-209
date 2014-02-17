#include <sys/socket.h>

#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <iostream>
#include <string>
#include <string.h>

using namespace std;

#define BUFF_SIZE 32
#define MESSAGE_END "\n\n"

#include "Socket.h"


Socket::Socket() {
    buffer = new char[BUFF_SIZE];
}

Socket::Socket(const int fd) {
    buffer = new char[BUFF_SIZE];
    setFd(fd);
}

Socket::~Socket() {
    close(fd_);
    delete[] buffer;
}


int Socket::write(string message) {
    const char * msg;
    int len, bytes_sent;

    message += "\n\n";
    msg = message.c_str();
    len = strlen(msg);
    bytes_sent = 0;

    while(len > 0){
        bytes_sent = send(fd_, msg, len, 0);
        if(bytes_sent == -1)
            return -1; // socket error, could not write
        len -= bytes_sent;
        msg = msg + bytes_sent;
    }

    return 0;
}

string Socket::popFromBuffer() {
    string partial;
    size_t nextStop;

    partial = buffer;
    nextStop = partial.find(MESSAGE_END);
    if (nextStop == string::npos) {
        buffer[0] = '\0';
    }
    else {
        buffer = buffer + nextStop + 2;
        partial = partial.substr(0, nextStop + 2);
    }

    return partial;
}

int Socket::read(string & message) {
    bool isComplete;
    int len;

    message = popFromBuffer();
    isComplete = (message.find(MESSAGE_END) != string::npos);

    while(!isComplete){
        len = recv(fd_, buffer, BUFF_SIZE - 1, 0);
        if (len == -1)
            return -1; // socket error, could not read
        else if(len == 0)
            return 0; // connection closed from other side

        buffer[len] = '\0'; // prevent buffer overflow
        message += popFromBuffer();
        isComplete = (message.find(MESSAGE_END) != string::npos);
    }

    message = message.substr(0, message.length() - 2); // remove MESSAGE_END
    return 1;
}

int Socket::getFd() const {
    return fd_;
}

void Socket::setFd(const int fd) {
    fd_ = fd;
}
