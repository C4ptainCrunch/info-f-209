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

Socket::Socket(int fd)
{
    setFd(fd);
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
    //Note : version crade, doit passer plusieurs bout de code en fonction et néttoyer.
    static string rest; //buffer, sert à sauvegarder des morceaux de texte entre deux read.
    string fullMessage; //message qui sera copié dans 'message'
    bool hasToRead = true;

    //Gestion du reste du message précédent.
    if (rest.empty() == false) //S'il reste du reste.
    {
        size_t nextStop = rest.find(MESSAGEEND);
        if (nextStop == string::npos) //Si le reste ne contient pas de message d'arrêt (il est donc un morceau d'un autre message)
        {
            fullMessage = rest;
            rest = "";
        }
        else //Si le reste contient au moins un message entier.
        {
            fullMessage = rest.substr(0, nextStop);
            rest.erase(0, nextStop+sizeof(MESSAGEEND)); //On néttoie pour la lecture du reste du reste.
            hasToRead = false; //On n'itère alors pas dans la boucle qui suit.
        }
    }
    //

    while (hasToRead)
    {
        string package;
        if (recv(fd, buffer, BUFF_SIZE, 0) == -1) //s'attend à des package de bytes défini dans le header.
        {
            cout<<"Error : Socket, read."<<endl;
            return 1;
        }

        package.assign(buffer, BUFF_SIZE); //le buffer est passé dans un string

        size_t stop = package.find(MESSAGEEND);
        if (stop == string::npos)
        {
            fullMessage += package;
        }
        else
        {
            fullMessage += package.substr(0, stop);
            package.erase(0, stop+sizeof(MESSAGEEND));
            rest = package; //On place tout ce qui suit le message d'erreur dans le buffer rest.
        }

    }
    message = fullMessage; //message est copié dans le string passé en paramètre
    return 0;
}

int Socket::getFd()
{
    return fd;
}

void Socket::setFd(int fd_)
{
    fd = fd_;
}
