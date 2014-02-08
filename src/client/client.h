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


class Client{
public:
    Client();
    void connectToName(std::string name);
    void disconnect();
    int send(const std::string & message); //Renvoie 0 si succès, 1 si erreur.
    int recv(std::string & message); //idem. Modifie param message en lui donnant la valeur du message lu.
private:
    Socket socket_;
    bool connected;
};

#endif //CLIENT_H
