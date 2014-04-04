#include "Socket.h"

using namespace std;

Socket::Socket() {
    mutex_init();

    fd_ = 0;
    buffer[0] = '\0';
}

Socket::Socket(const int fd) {
    mutex_init();

    buffer[0] = '\0';
    setFd(fd);
}

void Socket::mutex_init() {
    pthread_mutex_init(&write_lock, NULL);
    pthread_mutex_init(&read_lock, NULL);
}

Socket::Socket(string hostname, int port) {
    mutex_init();

    int sockfd;
    struct sockaddr_in their_addr;
    struct hostent * he;

    if ((he = gethostbyname(hostname.c_str())) == NULL) {
        throw SocketError("gethostbyname : " + std::string(strerror(errno)));
    }

    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        throw SocketError("socket : " + std::string(strerror(errno)));
    }

    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(port);
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(&(their_addr.sin_zero), '\0', 8);


    if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1) {
        throw SocketError("connect : " + std::string(strerror(errno)));
    }

    buffer[0] = '\0';
    fd_ = sockfd;
}

Socket::~Socket() {
    if (fd_ != 0) {
        close(fd_);
    }
}

int Socket::write(string message) {
    pthread_mutex_lock(&write_lock);
    const char * msg; //const?
    int len, bytes_sent;

    message += "\n\n";
    msg = message.c_str();
    len = strlen(msg);
    bytes_sent = 0;

    while (len > 0) {
        bytes_sent = send(fd_, msg, len, 0);
        if (bytes_sent == -1) {
            perror("");
            return -1; // socket error, could not write
        }
        len -= bytes_sent;
        msg = msg + bytes_sent;
    }
    pthread_mutex_unlock(&write_lock);
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
    pthread_mutex_lock(&read_lock);
    bool isComplete;

    message = popFromBuffer();
    isComplete = (message.find(MESSAGE_END) != string::npos);

    while (!isComplete) {
        int len;
        len = recv(fd_, buffer, sizeof(buffer) - 1, 0);
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
    pthread_mutex_unlock(&read_lock);
    return 1;
}

int Socket::getFd() const {
    return fd_;
}

void Socket::setFd(const int fd) {
    fd_ = fd;
}
