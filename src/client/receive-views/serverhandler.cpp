#include "serverhandler.h"

using namespace std;

ServerHandler::ServerHandler(string host, const int port) {
    host_ = host;
    port_ = port;
    s_ = NULL;
}

ServerHandler::~ServerHandler() {
    if(s_ != NULL){
        delete s_;
    }
}

bool ServerHandler::connect_socket(const int timeout){
    int sockFd;
    struct timeval ctimeout;

    ctimeout.tv_sec = timeout;
    ctimeout.tv_usec = 0;
    if ((sockFd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        // perror("Client: socket ");
        return false;
    }

    setsockopt(sockFd, SOL_SOCKET, SO_RCVTIMEO, (char *)&ctimeout, sizeof(struct timeval));

    s_ = new Socket(sockFd);

    struct sockaddr_in theirAddr;
    struct hostent * he;

    socklen_t addrSize = sizeof(struct sockaddr);

    if ((he = gethostbyname(host_.c_str())) == NULL) {
        // cout << "Could not resolve hostname" << endl;
        return false;
    }

    theirAddr.sin_family = AF_INET;
    theirAddr.sin_port = htons(port_);
    theirAddr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(&(theirAddr.sin_zero), '\0', 8);

    if (connect(s_->getFd(), (struct sockaddr *)&theirAddr, addrSize) == -1) {
        // perror("Connect");
        return false;
    }

    return true;
}

void ServerHandler::send(string message){
    if(s_ == NULL){
        throw 1;
    }
    s_->write(message);
}

int ServerHandler::recieve(string & message){
    if(s_ == NULL){
        throw 1;
    }
    return s_->read(message);
}