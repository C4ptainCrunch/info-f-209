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
    int packageNum = (message.size()/BUFF_SIZE); //découpe le message en package de bytes défini dans le header.
    for (int currPackage = 0; currPackage >= packageNum; ++currPackage)
    {
        string package = message.substr(currPackage*BUFF_SIZE+BUFF_SIZE);
        if (send(fd, package.c_str(), BUFF_SIZE, 0) == -1) //envoie chaque package un à un.
        {
            cout<<"Error : Socket, write."<<endl;
            return 1;
        }
    }

    strncpy(buffer, MESSAGEEND, BUFF_SIZE); //lorsque fini, envoie la valeur sentinelle de fin.
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
        if (recv(fd, buffer, BUFF_SIZE, 0) == -1) //s'attend à des package de bytes défini dans le header.
        {
            cout<<"Error : Socket, read."<<endl;
            return 1;
        }

        package = buffer; //le buffer est passé dans un string
        if (package != MESSAGEEND) //si différent de sentinelle de fin, le package est alors rajouté au message résultant
        {
            res += package;
        }
        else //si le package est la sentinelle de fin, indique à la boucle de s'arrêter
        {
            hasToRead = false;
        }
    }
    message = res; //message est copié dans le string passé en paramètre
    return 0;
}

int Socket::getFd()
{
    return fd;
}
