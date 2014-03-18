#include "helpers.h"

std::string recieveFrom(const int sock, char * buffer) {
    std::string message;
    int len = RCV_SIZE;
    char lr = 0; // line returns

    while (len != 0 && lr < 2) {
        if ((len = recv(sock, buffer, RCV_SIZE, 0)) == 0) {
            printf("Listen failed : %s\n", strerror(errno));
        }
        else {
            buffer[len] = '\0';
            char * i = buffer;
            for (char c = i[0]; c != '\0'; i++) {
                if ((c == '\n') && (lr < 2)) {
                    lr++;
                }
                else if (c == '\n') {
                    buffer = i + 1;
                    i--;
                    i[0] = '\0';
                }
                else {
                    lr = 0;
                }
            }
            message += buffer;
        }
    }
    return message;
}

std::string split_message(std::string * key, std::string message) {
    std::size_t found = message.find(':');
    *key = message.substr(0, found);
    return message.substr(found + 1, message.length());
}
