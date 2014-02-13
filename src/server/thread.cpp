#include "thread.h"

#include <iostream>

using namespace std;

void connection(const int socket){
    Socket s(socket);
    std::string response = "";
    char buffer[RCV_SIZE];

    s.write("Hello, bite!");
    s.read(response);
    s.write(response);
    s.read(response);
    s.write(response);
    s.write("Bye");
    close(socket);

}

/*void connection(const int fd, const JsonNode * usersInfos){
    sendTo(fd, "Hello, bite!\n");
    bool quit=false
    while(! quit)
    {
        std::string ping = recieveFrom(fd);
        sendTo(fd, ping);
        JsonNode json(ping);
        Thread thread=Thread(fd, usersInfos);
        if (json.getKey()=="user.login")
        {
            logIn(&json, &thread)
        }
        else if (json.getKey()=="user.signup")
        {
            signUp(&json, &thread)
        }
        else if (json.getKey()=="user.quit")
        {
            quit=true;
        }
        else
        {
            // erreur à gérer
        }
        if(thread.getConnected()!="~")
        {
            quidditch(); // boucle infinie jusqu'à ce que le user demande de quitter le jeu
            quit=true;
        }
    }
    close(fd);
}*/