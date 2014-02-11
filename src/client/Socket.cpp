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
#include <iostream>

#include "Socket.h"

using namespace std;

Socket::Socket() {}

Socket::Socket(const int fd)
{
    setFd(fd);
}


int Socket::write(string message)
{
    message += "\n\n";
    const char * msg = message.c_str();
    int len = strlen(msg);
    int bytes_sent = 0;
    while(len > 0){
        bytes_sent = send(fd_, msg, len, 0);
        len -= bytes_sent;
        msg = msg + bytes_sent;
    }

    return 0;
}

string Socket::popFromBuffer(){

    string partial = buffer;
    size_t nextStop = partial.find(MESSAGE_END);
    if (nextStop == string::npos) {
        buffer[0] = '\0';
    }
    else {
        char *ptr_buffer = buffer + nextStop + 2;
        partial = partial.substr(nextStop + 2);
    }
    cout << "PLOP" << endl;


    return partial;
}

int Socket::read(string & message)
{
    message = popFromBuffer();
    size_t isComplete = (message.find(MESSAGE_END) != string::npos);
    while(!isComplete){
        if (recv(fd_, buffer, BUFF_SIZE, 0) == -1) {
            cout<<"Error : Socket, read."<<endl;
            return -1;
        }
        message = popFromBuffer();
        size_t isComplete = (message.find(MESSAGE_END) != string::npos);
    }

    return 0;
}

int Socket::getFd() const {
    return fd_;
}

void Socket::setFd(const int fd) {
    fd_ = fd;
}
