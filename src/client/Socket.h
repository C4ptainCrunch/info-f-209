#ifndef SOCKET_H
#define SOCKET_H

#include <string>

#define BUFF_SIZE 32
#define MESSAGE_END "\n\n"

class Socket {
    public:
        Socket();
        ~Socket();
        Socket(const int fd);
        virtual int write(std::string message);
        virtual int read(std::string & message);
        virtual int getFd() const;
        virtual void setFd(const int fd);

    private:
        char * buffer;
        int fd_;
        virtual std::string popFromBuffer();
};

#endif //SOCKET_H
