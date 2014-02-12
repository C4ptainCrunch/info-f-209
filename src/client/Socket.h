#ifndef SOCKET_H
#define SOCKET_H


class Socket {
    public:
        Socket();
        ~Socket();
        Socket(const int fd);
        virtual int write(string message);
        virtual int read(string & message);
        virtual int getFd() const;
        virtual void setFd(const int fd);

    private:
        char * buffer;
        int fd_;
        virtual string popFromBuffer();
};

//SOCKET_H
#endif
