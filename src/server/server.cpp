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
    
    // chargement du fichiers avec les infos des users
    // des infos dans un json, pointé par une variable (const JsonObject * usersInfos)

    int new_fd;
    sockaddr_storage their_addr;
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
        pool.push_back(std::thread(connection, new_fd));  //à remplacer par la ligne en dessous (après test premiers tests client-server)
        //pool.push_back(std::thread(connection, new_fd, usersInfos))
        // should join somewhere
    }

    return 0;
}
