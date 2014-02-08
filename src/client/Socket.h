#ifndef SOCKET_H
#define SOCKET_H

#include <string>

#define BUFF_SIZE 32
#define MESSAGEEND "\n\n\0"

class Socket {
    public:
        Socket(int fd);
        int write(const std::string & message); //Renvoie 0 si succès, 1 si erreur.
        int read(std::string & message); //idem. Modifie param message en lui donnant la valeur du message lu.
        int getFd();
    private:
        char buffer[BUFF_SIZE];
        int fd;
};

#endif //SOCKET_H
