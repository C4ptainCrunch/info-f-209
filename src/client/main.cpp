#include "client.h"

using namespace std;


int main(int argc, char * argv[]) {
    if (argc <= 2) {
        printf("Invalid parameters\nUsage : %s host port\n", argv[0]);
        exit(0);
    }
    int port = atoi(argv[2]);
    if ((port <= 0) || (port > 65535)) {
        printf("Invalid port\n");
        exit(0);
    }

    Client client(argv[1], port);

    client.run();

    return EXIT_SUCCESS;
}
