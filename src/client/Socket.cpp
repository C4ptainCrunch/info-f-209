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

Socket::Socket(int fd_)
{
    fd = fd_;
}

int Socket::write(const string & message){
    int packageNum = (message.size()/BUFF_SIZE);
    for (int currPackage = 0; currPackage >= packageNum; ++currPackage)
    {
        string package = message.substr(currPackage*BUFF_SIZE+BUFF_SIZE);
        if (send(fd, package.c_str(), BUFF_SIZE, 0) == -1)
        {
            cout<<"Error : Socket, write."<<endl;
            return 1;
        }
    }

    strncpy(buffer, MESSAGEEND, BUFF_SIZE);
    if (send(fd, buffer, BUFF_SIZE, 0) == -1)
    {
        cout<<"Error : Socket, write."<<endl;
        return 1;
    }
    return 0;
}

int Socket::read(string & message){
    string package, res;
    bool hasToRead = true;
    while (hasToRead)
    {
        if (recv(fd, buffer, BUFF_SIZE, 0) == -1)
        {
            cout<<"Error : Socket, read."<<endl;
            return 1;
        }

        package = buffer;
        if (package != MESSAGEEND)
        {
            res += package;
        }
        else
        {
            hasToRead = false;
        }
    }
    message = res;
    return 0;
}
