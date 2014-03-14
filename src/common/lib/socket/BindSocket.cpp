#include "BindSocket.h"

// using namespace std;


BindSocket::BindSocket(std::string hostname, int port) {
    mutex_init();

    int sockfd;
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;
    int yes = 1;

    if ((sockfd = socket(PF_INET,
                         SOCK_STREAM, 0)) == -1) {
        perror("Serveur: socket");
        throw 1;
    }

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("Serveur: setsockopt");
        throw 1;
    }

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(port);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(my_addr.sin_zero), '\0', 8);

    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
        perror("Serveur: bind");
        throw 1;
    }

    if (listen(sockfd, BACKLOG) == -1) {
        perror("Serveur: listen");
        throw 1;
    }

    fd_ = sockfd;
}

ClientSocket * BindSocket::accept_client() {
    char new_fd = -2;
    sockaddr_storage remote_addr;
    socklen_t address_len;

    address_len = sizeof remote_addr;
    while (new_fd < 0) {
        new_fd = accept(fd_, (struct sockaddr *)&remote_addr, &address_len);
        if (new_fd == -1) {
            perror("accept");
        }
    }

    return new ClientSocket(new_fd, remote_addr);
}


ClientSocket::ClientSocket(const int fd, sockaddr_storage remote): Socket(fd) {
    remote_addr_ = remote;
}

std::string ClientSocket::remote() {
    char s[INET6_ADDRSTRLEN];
    inet_ntop(remote_addr_.ss_family, get_in_addr((struct sockaddr *)&remote_addr_), s, sizeof s);
    return std::string(s);
}
