#include "Socket.h"

using namespace std;


Socket::Socket() {
    fd_ = 0;
    buffer[0] = '\0';
}

Socket::Socket(const int fd) {
    buffer[0] = '\0';
    setFd(fd);
}

Socket::~Socket() {
    if (fd_ != 0) {
        close(fd_);
    }
}


int Socket::write(string message) {
    char * msg;//const?
    int len, bytes_sent;

    message += "\n\n";
    msg = message.c_str();
    len = strlen(msg);
    bytes_sent = 0;

    while (len > 0) {
        bytes_sent = send(fd_, msg, len, 0);
        if (bytes_sent == -1) {
            return -1; // socket error, could not write
        }
        len -= bytes_sent;
        msg = msg + bytes_sent;
    }

    return 0;
}

string Socket::popFromBuffer() {
    string partial;
    size_t nextStop;
    partial = buffer;
    nextStop = partial.find(MESSAGE_END);
    if (nextStop == string::npos) {
        buffer[0] = '\0';
    }
    else {
        strcpy(buffer, buffer + nextStop + 2);
        partial = partial.substr(0, nextStop + 2);
    }
    return partial;
}

int Socket::read(string & message) {
    bool isComplete;

    message = popFromBuffer();
    isComplete = (message.find(MESSAGE_END) != string::npos);

    while (!isComplete) {
        int len;
        len = recv(fd_, buffer, sizeof(buffer) - 1, 0);
        cout << "BUFFER : " << buffer << endl;
        if (len == -1) {
            return -1; // socket error, could not read
        }
        else if (len == 0) {
            return 0; // connection closed from other side

        }
        buffer[len] = '\0'; // prevent buffer overflow
        message += popFromBuffer();
        isComplete = (message.find(MESSAGE_END) != string::npos);
    }

    message = message.substr(0, message.length() - 2); // remove MESSAGE_END
    return 1;
}

int Socket::getFd() const {
    return fd_;
}

void Socket::setFd(const int fd) {
    fd_ = fd;
}
