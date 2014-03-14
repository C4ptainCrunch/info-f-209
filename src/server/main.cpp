#include "../common/lib/json/json.h"
#include "../common/lib/file/file.h"
#include "server.h"

using namespace std;

int main(int argc, char * argv[]) {
    const char *slash = strrchr(argv[0], '/');
    if (slash){
        std::string clientdir(argv[0], slash-argv[0]);
        chdir(clientdir.c_str());
    }

    string configfile;
    if (argc == 1) {
        configfile = "../../server-config.json";
    }
    else if (argc == 3) {
        configfile = argv[2];
    }
    else {
        printf("Unknown option\n");
        exit(0);
    }
    if (!fileExists(configfile)) {
        printf("Missing configuration file\nSearched at : %s\n", configfile.c_str());
        exit(0);
    }

    string config;
    if (readFile(configfile, config) != 0) {
        printf("Error while reading configuration file");
        exit(0);
    }
    JsonValue * val = JsonValue::fromString(config);
    JsonDict * dict = JDICT(val);
    if (dict == NULL) {
        printf("Error while parsing configuration file");
        exit(0);
    }
    JsonInt * port_p = JINT((*dict)["port"]);
    JsonString * data_p = JSTRING((*dict)["datapath"]);
    string datapath;
    if (port_p == NULL) {
        printf("Error while parsing configuration file");
        exit(0);
    }
    if (data_p != NULL){
        datapath = *data_p;
    }
    else {
        datapath = "../../data/";
    }
    int port = *port_p;

    int sockfd; // socket to bind to

    sockaddr_storage remote_addr;
    socklen_t address_len;
    char s[INET6_ADDRSTRLEN];
    std::vector<UserHandler *> * handlers_list = new std::vector<UserHandler *>();

    sockfd = bindTo(port);

    printf("Waiting for connections...\n");

    while (1) {
        int new_fd; // "accepted" socket

        address_len = sizeof remote_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&remote_addr, &address_len);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(remote_addr.ss_family, get_in_addr((struct sockaddr *)&remote_addr), s, sizeof s);
        printf("Got connection from %s\n", s);

        UserHandler * current_handler = new UserHandler(handlers_list, datapath);
        std::thread * current_thread = new std::thread(thread_loop, current_handler);
        // TODO: should delete current_thread sometimes
        current_handler->start(new_fd, current_thread);
        handlers_list->push_back(current_handler);
    }
    delete handlers_list;

    return 0;
}
