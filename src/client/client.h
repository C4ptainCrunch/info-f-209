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
#include "GameState.h"

#define PORT 8000

class Client{
public:
    Client();
    ~Client();
    virtual void run(const std::string name);
    virtual void setNextState(const int newState);

private:
    virtual void connectToName(const std::string name);
    virtual void disconnect();
    virtual int send(const std::string & message); //Renvoie 0 si succès, 1 si erreur.
    virtual int recv(std::string & message); //idem. Modifie param message en lui donnant la valeur du message lu.

    virtual void changeState();

    Socket socket_;
    bool connected_;

    int currentStateID_;
    int nextStateID_;
    GameState * currentState_;
};

#endif //CLIENT_H
