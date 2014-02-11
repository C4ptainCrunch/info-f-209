#ifndef SOCKET_H
#define SOCKET_H

#include <string>

#define BUFF_SIZE 32
#define MESSAGE_END "AA"

class Socket {
    public:
        Socket(); //ne fait rien.
        Socket(const int fd); //appele setFd
        virtual int write(std::string message); //Renvoie 0 si succès, 1 si erreur.
        virtual int read(std::string & message); //idem. Modifie param message en lui donnant la valeur du message lu.
        virtual int getFd() const;
        virtual void setFd(const int fd);

    private:
        char buffer[BUFF_SIZE];
        char *ptr_buffer;
        int fd_;
        virtual std::string popFromBuffer();
};

#endif //SOCKET_H
