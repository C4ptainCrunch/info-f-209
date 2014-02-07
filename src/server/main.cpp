#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#include <arpa/inet.h>
#include <unistd.h>

#include <thread>
#include <vector>

#include "helpers.cpp"
#include "thread.cpp"
#include "bind.cpp"


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

    int new_fd;
    sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    char s[INET6_ADDRSTRLEN];

    int sockfd = bindTo(argv[1]);
    std::vector<std::thread> pool;

    printf("Waiting for connections...\n");

    while(1) {  // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
            get_in_addr((struct sockaddr *)&their_addr),
            s, sizeof s);
        printf("Got connection from %s\n", s);
        pool.push_back(std::thread(connection, new_fd));
        // should join somewhere
    }

    return 0;
}
