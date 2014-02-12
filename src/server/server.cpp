#include "server.h"

int main(int argc, char *argv[])
{
    if(argc <= 1){
        printf("Invalid parameters\nUsage : %s port\n", argv[0]);
        exit(0);
    }
    if(atoi(argv[1]) <= 0 || atoi(argv[1]) > 65535){
        printf("Invalid port\n");
        exit(0);
    }

    int sockfd; // socket to bind to
    int new_fd; // "accepted" socket
    sockaddr_storage remote_addr;
    socklen_t address_len;
    char s[INET6_ADDRSTRLEN];
    std::vector<std::thread> pool;

    sockfd = bindTo(argv[1]);

    printf("Waiting for connections...\n");

    while(1) {
        address_len = sizeof remote_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&remote_addr, &address_len);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(remote_addr.ss_family, get_in_addr((struct sockaddr *)&remote_addr), s, sizeof s);
        printf("Got connection from %s\n", s);
        pool.push_back(std::thread(connection, new_fd));
    }

    return 0;
}
