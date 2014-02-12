#include <iostream>

#include "server.h"
using namespace std;


void thread_loop(UserHandler * handler){
    while(!handler->isReady()){
        usleep(10000);
    }

    handler->loop();
    delete handler;
}

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
    std::vector<UserHandler *> * handlers_list = new std::vector<UserHandler *>();

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

        UserHandler * current_handler = new UserHandler(handlers_list);
        std::thread * current_thread = new std::thread(thread_loop, current_handler);
        // TODO should delete current_thread sometimes
        current_handler->start(new_fd, current_thread);
        handlers_list->push_back(current_handler);
    }
    delete handlers_list;

    return 0;
}
